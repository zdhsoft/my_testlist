#ifndef _X_SHM_IPC_H_
#define _X_SHM_IPC_H_
#include <xshm.h>
#include <xbufferqueue.h>
#include <xpollcontrol.h>
#include <FastDelegate.h>
namespace zdh
{

    typedef fastdelegate::FastDelegate< void ( XBuffer & paramBuffer ) > TOnRecvDataEvent;
    ///共享内存通讯
    class XShm_IPC : public IServiceBase
    {
    public:
        XShm_IPC()
            :m_InitFlag(false),m_MasterFlag(false)
        {
            m_OnRecvEvent.bind(this, &XShm_IPC::OnRecvEvent);
#if defined(OS_LINUX)
            MemoryZero(m_SendAddr);
#endif
        }
        virtual ~XShm_IPC()
        {}

        virtual XInt Register(TPoll * paramPoll)
        {
            if (!m_InitFlag)
            {
                return ECEC_HAS_NOT_BEEN_INITIALISED;
            }
            XInt iRet = paramPoll->AddEvent(m_RecvSocket.getSocketID(), EPC_IN, &m_OnRecvEvent);
            if (isNotOK(iRet))
            {
                ZDH_ERROR("Register Recv Socket Fail:Ret=%d", iRet);
                iRet = ECEC_REGISTER_SOCKET_FAIL;
            }
            return ERR_OK;
        }

        virtual XInt Unregister(TPoll * paramPoll)
        {
            if (!m_InitFlag)
            {
                return ECEC_HAS_NOT_BEEN_INITIALISED;
            }
            XInt iRet = paramPoll->DelEvent(m_RecvSocket.getSocketID());
            if (isNotOK(iRet))
            {
                ZDH_ERROR("Unregister fail! Ret=%",iRet);
                iRet = ECEC_UNREGISTER_SOCKET_FAIL;
            }
            return ERR_OK;
        }

        virtual XInt getServiceType() const 
        {
            return EST_SHM_IPC;
        }


        XInt Init(bool paramMaster, 
                  const char * paramShmKey, XInt paramShmSize,
                  const char * paramSendSocket, const char * paramRecvSocket
            )
        {

            XInt iRet = ERR_OK;
            do 
            {
                if (m_InitFlag)  //如果已经初始化了
                {
                    iRet = ERR_FAIL;
                    break;
                }
                // 初始化前端共享内存
                iRet = m_Shm.Create(paramShmKey, paramShmSize);
                if (iRet)
                {
                    ZDH_ERROR("shm create failed ret = %d. key=%s size=%d", iRet, paramShmKey, paramShmSize);
                    iRet = ECEC_SHM_CREATE_FAIL;
                    break;
                }

                ZDH_INFO("create shmqueue's shm at %p ok. key=%s size=%d", m_Shm.GetBuffer(), paramShmKey, paramShmSize);

                // 初始化消息队列
                XInt iQueueSize = m_Shm.GetSize() / 2;
                m_MasterFlag = paramMaster;
                if (paramMaster)
                {
                    m_SendQueue.Init((XByte *)(m_Shm.GetBuffer()), iQueueSize, true);
                    m_RecvQueue.Init((XByte *)(m_Shm.GetBuffer() + iQueueSize), iQueueSize, false);
                }
                else
                {
                    m_SendQueue.Init((XByte *)(m_Shm.GetBuffer() + iQueueSize), iQueueSize, true);
                    m_RecvQueue.Init((XByte *)(m_Shm.GetBuffer()), iQueueSize, false);
                }

                iRet = RecvSocketListen(paramRecvSocket);
                if (isNotOK(iRet))
                {
                    break;
                }

                iRet = SendSocketConnect(paramSendSocket);
                if (isNotOK(iRet))
                {
                    break;
                }

                iRet = ERR_OK;
                m_InitFlag = true;
            } while (false);
            return iRet;
        }

        TOnRecvDataEvent & getOnRecvDataEvent() 
        {
            return m_OnRecvDataEvent;
        }
        ///发送一个数据包
        XInt SendMsgData(void * paramMsg, XInt paramMsgLength)
        {
            //
            XInt iRet = ERR_OK;
            m_SendQueue.Push(paramMsg, paramMsgLength);
#if defined(OS_LINUX)
            sendto(m_SendSocket.getSocketID(), "1", 1, 0, (const struct sockaddr*)&m_SendAddr, sizeof(m_SendAddr));
#endif
            return iRet;
        }
    private:
        void OnRecvEvent(TPoll * /*paramPoll*/, TPollFlag /*paramFlag*/)
        {
            XInt iRet = ERR_OK;
            //XInt iRecvLen = 0;
            char tmpbuffer[128];

            while (true)
            {
                //iRet = recvfrom(m_iSocket, buf + recvlen, buflen - recvlen, 0, 0, 0);
                iRet = recvfrom(m_RecvSocket.getSocketID(), tmpbuffer, sizeof(tmpbuffer), 0, 0, 0);
                if (iRet == (XInt)sizeof(tmpbuffer))
                {
                    continue;
                }
                if (iRet < 0)
                {
                    ZDH_WARN("Recv failed %d, errno=%d", iRet, xerrno());
                }
                break;
            }
            if(m_RecvQueue.Pop(m_RecvBuffer)>0)
            {
                if(!m_OnRecvDataEvent.empty())
                {
                    m_OnRecvDataEvent(m_RecvBuffer);
                }
                m_RecvBuffer->Clear();
            }
        }
        XInt SendSocketConnect(const char * paramSendSocket)
        {
            XInt iRet = ERR_OK;
#if defined(OS_LINUX)
            do 
            {
                if(isNULL(paramSendSocket))
                {
                    iRet = ERR_FAIL;
                    break;
                }
                iRet = m_SendSocket.Open(AF_LOCAL, SOCK_DGRAM, 0);
                if (isNotOK(iRet))
                {
                    ZDH_ERROR("Open Socket(AF_LOCAL,SOCKET_DGRAM,0) fail ret=%d errno=%d", iRet, xerrno());
                    iRet = ECEC_SOCKET_OPEN_FAIL;
                    break;
                }
               
                m_SendAddr.sun_family = m_SendSocket.getFamily();
                string_utils::StringCopy(m_SendAddr.sun_path, paramSendSocket, sizeof(m_SendAddr.sun_path));
//              这里使用的SOCK_DGRAM模式，不需要连接
//                 iRet = connect(m_SendSocket.getSocketID(), (const struct sockaddr *)&stAddr, sizeof(stAddr));
//                 if (iRet < 0)
//                 {
//                     LOG_ERROR("Connct %s fail ret=%d errno=%d", paramSendSocket, iRet, xerrno());
//                     iRet = ECEC_SOCKET_CONNECED_FAIL;
//                     break;
//                 }
                iRet = ERR_OK;
            }while(false);
#else
            paramSendSocket = NULL;
#endif
            return iRet;
        }
        XInt RecvSocketListen(const char * paramRecvSocket)
        {
            XInt iRet = ERR_OK;
#if defined(OS_LINUX)
            do 
            {
                if (isNULL(paramRecvSocket))
                {
                    iRet = ERR_FAIL;
                    break;
                }

                struct sockaddr_un stAddr;
                MemoryZero(stAddr);
                iRet = m_RecvSocket.Open(AF_LOCAL, SOCK_DGRAM, 0);
                if (isNotOK(iRet))
                {
                    ZDH_ERROR("Open Socket(AF_LOCAL,SOCKET_DGRAM,0) fail ret=%d errno=%d", iRet, xerrno());
                    iRet = ECEC_SOCKET_OPEN_FAIL;
                    break;
                }
                stAddr.sun_family = m_RecvSocket.getFamily();
                string_utils::StringCopy(stAddr.sun_path, paramRecvSocket, sizeof(stAddr.sun_path));
                unlink(paramRecvSocket);
             
                iRet = 1;
                setsockopt(m_RecvSocket.getSocketID(), SOL_SOCKET, SO_REUSEADDR, (const char*)&iRet, sizeof(iRet));
                iRet = bind(m_RecvSocket.getSocketID(), (const struct sockaddr *)&stAddr, sizeof(stAddr));
                if (iRet < 0)
                {
                    ZDH_ERROR("bind %s fail ret=%d, errno=%d", iRet, xerrno());
                    m_RecvSocket.Close();
                    iRet = ECEC_SOCKET_BIND_FAIL;
                    break;
                }
                iRet = ERR_OK;

            } while (false);
#else
            paramRecvSocket = NULL;
#endif
            return iRet;
        }
    private:
        bool m_InitFlag;
        bool m_MasterFlag;
        XShm m_Shm;
        
        XBufferQueue     m_RecvQueue;
        XSocket          m_RecvSocket;
        XBuffer          m_RecvBuffer;

        XBufferQueue     m_SendQueue;
        XSocket          m_SendSocket;
        XBuffer          m_SendBuffer;
        TOnPollEvent     m_OnRecvEvent;
        TOnRecvDataEvent m_OnRecvDataEvent;
#if defined(OS_LINUX)
        struct sockaddr_un m_SendAddr;
#endif
    };
};
#endif
