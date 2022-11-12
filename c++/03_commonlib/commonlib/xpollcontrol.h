#ifndef _X_POLL_CONTROL_H_
#define _X_POLL_CONTROL_H_
#include <xpoll.h>
#include <xsocket.h>
#include <FastDelegate.h>
#include <xdynamic_array.h>
#include <xthread.h>
#include <xlog.h>
#include <xcommon_error_code.h>
#include <xon_timer.h>

namespace zdh
{
    #if defined(OS_LINUX)
        typedef XEPoll TPoll;
    #else
        typedef XSelectPoll TPoll;
    #endif
    ///可Poll的服务类型定义
    enum EnumServiceType
    {
        EST_NETWORK_LISTEN  = 1,    ///<网络侦听类型
        EST_SHM_IPC         = 2,    ///<共享内存通讯类型
        EST_CLIENT          = 3,    ///<客户端连接服务类型
    };
    ///服务类型基类
    class IServiceBase
    {
    public:
        IServiceBase()
        {}
        virtual ~IServiceBase(){}
        virtual XInt Register(TPoll * paramPoll) = 0;
        virtual XInt Unregister(TPoll * paramPoll) = 0;
        virtual XInt getServiceType() const = 0;
    };

    typedef fastdelegate::FastDelegate<void (TPoll * paramPoll, TPollFlag paramFlag)> TOnPollEvent;
    typedef fastdelegate::FastDelegate<bool (TPoll * paramPoll, IServiceBase * paramListenService, xsocket_t paramClientFD, XDWord paramClientIP, XWord paramClientPort)> TOnAcceptEvent;

    ///共享内存通讯服务类
    class XServiceSHM_IPC : public IServiceBase
    {
    public:
        XServiceSHM_IPC()
            :m_Poll(NULL)
        {}
        virtual ~XServiceSHM_IPC(){}

        XInt Register(TPoll * paramPoll)
        {
            m_Poll = paramPoll;
            return ERR_OK;
        }
        XInt Unregister(TPoll * paramPoll) 
        {
            paramPoll = NULL;
            return ERR_OK;
        }  
        virtual XInt getServiceType() const
        {
            return EST_SHM_IPC;
        }
    private:
        TPoll * m_Poll;
    };


    ///客户端连接服务类
    class XServiceClient : public IServiceBase
    {
    public:
        XServiceClient()
            :m_Poll(NULL)
        {}
        virtual ~XServiceClient(){}

        XInt Register(TPoll * paramPoll)
        {
            m_Poll = paramPoll;
            return ERR_OK;
        }
        XInt Unregister(TPoll * paramPoll) 
        {
            paramPoll = NULL;
            return ERR_OK;
        }  
        virtual XInt getServiceType() const
        {
            return EST_CLIENT;
        }
    private:
        TPoll * m_Poll;
    };

    ///线程poll控制对象
    class XThreadPollControl : public XThread
    {
    public:
        ///构造函数
        /**
            @param [in] paramMaxEventCount 每次处理的事件对象个数
         */
        XThreadPollControl(XInt paramMaxEventCount = 1024)
            :m_InitFlag(false), 
             m_EventList(NULL), 
             m_MaxEventCount(paramMaxEventCount)
        {
            m_EventList = new TPollEvent[paramMaxEventCount];
        }
        ///析构函数
        ~XThreadPollControl()
        {
            Close();
            if (isNotNULL(m_EventList))
            {
                delete [] m_EventList;
                m_EventList = NULL;
            }
        }
        ///初始化
        /**
            @param [in] paramMaxPollSize Poll最大可以处理连接的个数
            @return XInt 返回初始化的结果
                - -1 当前control已经是初始化了
                - -2 Poll创建失败
         */
        XInt Init(XInt paramMaxPollSize)
        {
            int iRet = ERR_OK;
            do
            {
                if(m_InitFlag)
                {
                    iRet = ECEC_HAS_ALREADY_BEEN_INITIALIZED;
                    break;
                }

                iRet = m_Poll.Create(paramMaxPollSize);
                if (iRet != ERR_OK)
                {
                    iRet = ECEC_POLL_CREATE_FAIL;
                    break;
                }
                m_InitFlag = true;
                if (iRet != ERR_OK)
                {
                    Close();
                }
            }while(false);
            return iRet;
        }

        ///增加指定类型的服务
        XInt RegisterService(IServiceBase * paramSerivce)
        {
            XInt iRet = ERR_OK;
            do
            {
                if (!m_InitFlag)
                {
                    iRet = ECEC_HAS_NOT_BEEN_INITIALISED;
                    break;
                }
                iRet = paramSerivce->Register(&m_Poll);
                if (isNotOK(iRet))
                {
                    iRet = ECEC_SERVICE_REGISTER_FAIL;
                    //FreeObject(paramSerivce);
                    break;
                }
                else
                {
                    m_ServiceList.Append(paramSerivce);
                }
            }while(false);
            return iRet;
        }
        ///线程执行
        virtual void Execute()
        {
            try
            {
                if(!m_InitFlag)
                {
                    return;
                }
                while(!GetExitFlag())
                {
                    //LOG_TRACE("Wait!!!");
                    XLong lngNow = GetNowDateTime();
                    XInt iCount = m_Poll.Wait(m_MaxEventCount, m_EventList, 1000);
                    if (iCount > 0)
                    {
                        for(int i = 0; i < iCount; ++i)
                        {
                            TPollEvent & stEvent = m_EventList[i];
                            TOnPollEvent * pEvent = (TOnPollEvent *)stEvent.data.ptr;
                            if (!pEvent->empty())
                            {
                                (*pEvent)(&m_Poll, stEvent.events);
                            }
                        }
                    }
                    m_OnTimerManager.DoOnTimer(lngNow);
                }
            }
            catch (std::exception & e)
            {
                ZDH_FATAL("Control Thread exception:%s", e.what());
            }
            catch (EException & e)
            {
                ZDH_FATAL("Control Thread exception:%s", e.getMessage().c_str());
            }
            catch (...)
            {
                ZDH_FATAL("Control Thread exception! unknow exception!");
            }
        }
        ///控制线程关闭
        void Close()
        {
            if (m_InitFlag)
            {
                m_InitFlag = false;
                for(int i = 0; i < m_ServiceList.getLength(); i++)
                {
                    m_ServiceList[i]->Unregister(&m_Poll);
                    delete m_ServiceList[i];
                }
                
                m_ServiceList.Clear();
                m_Poll.Close();
            }
        }
        XOnTimerManager * getOnTimerManager() 
        {
            return & m_OnTimerManager;
        }
        TPoll * getPoll()
        {
            return &m_Poll;
        }
    private:
        bool m_InitFlag;
        TPollEvent * m_EventList;
        XInt m_MaxEventCount;
        TPoll m_Poll;
        XDynamicArray<IServiceBase *> m_ServiceList;    ///<服务类别  主要是IPC同listen服务类型
        XOnTimerManager m_OnTimerManager;
    };


    ///线程poll控制对象
    class XNormalPollControl 
    {
    public:
        ///构造函数
        /**
            @param [in] paramMaxEventCount 每次处理的事件对象个数
         */
        XNormalPollControl(XInt paramMaxEventCount = 1024)
            :m_ExitFlag(true),
             m_InitFlag(false), 
             m_EventList(NULL), 
             m_MaxEventCount(paramMaxEventCount)
        {
            m_EventList = new TPollEvent[paramMaxEventCount];
        }
        ///析构函数
        ~XNormalPollControl()
        {
            Close();
            if (isNotNULL(m_EventList))
            {
                delete [] m_EventList;
                m_EventList = NULL;
            }
        }
        ///初始化
        /**
            @param [in] paramMaxPollSize Poll最大可以处理连接的个数
            @return XInt 返回初始化的结果
                - -1 当前control已经是初始化了
                - -2 Poll创建失败
         */
        XInt Init(XInt paramMaxPollSize)
        {
            int iRet = ERR_OK;
            do
            {
                if(m_InitFlag)
                {
                    iRet = ECEC_HAS_ALREADY_BEEN_INITIALIZED;
                    break;
                }

                iRet = m_Poll.Create(paramMaxPollSize);
                if (iRet != ERR_OK)
                {
                    iRet = ECEC_POLL_CREATE_FAIL;
                    break;
                }
                m_InitFlag = true;
                if (iRet != ERR_OK)
                {
                    Close();
                }
            }while(false);
            return iRet;
        }

        ///增加指定类型的服务
        XInt RegisterService(IServiceBase * paramSerivce)
        {
            XInt iRet = ERR_OK;
            do
            {
                if (!m_InitFlag)
                {
                    iRet = ECEC_HAS_NOT_BEEN_INITIALISED;
                    break;
                }
                iRet = paramSerivce->Register(&m_Poll);
                if (isNotOK(iRet))
                {
                    iRet = ECEC_SERVICE_REGISTER_FAIL;
                    //FreeObject(paramSerivce);
                    break;
                }
                else
                {
                    m_ServiceList.Append(paramSerivce);
                }
            }while(false);
            return iRet;
        }
        ///线程执行
        void run()
        {
            m_ExitFlag = false;
            try
            {
                if(!m_InitFlag)
                {
                    return;
                }
                
                while(!m_ExitFlag)
                {
                    XLong lngNow = GetNowDateTime();
                    XInt iCount = m_Poll.Wait(m_MaxEventCount, m_EventList, 10);
                    if (iCount > 0)
                    {
                        for(int i = 0; i < iCount; ++i)
                        {
                            TPollEvent & stEvent = m_EventList[i];
                            TOnPollEvent * pEvent = (TOnPollEvent *)stEvent.data.ptr;
                            if (!pEvent->empty())
                            {
                                (*pEvent)(&m_Poll, stEvent.events);
                            }
                        }
                    }
                    m_OnTimerManager.DoOnTimer(lngNow);
                }
            }
            catch (std::exception & e)
            {
                ZDH_FATAL("Control exception:%s", e.what());
            }
            catch (EException & e)
            {
                ZDH_FATAL("Control exception:%s", e.getMessage().c_str());
            }
            catch (...)
            {
                ZDH_FATAL("Control exception! unknow exception!");
            }
        }
        ///控制线程关闭
        void Close()
        {
            if (m_InitFlag)
            {
                m_InitFlag = false;
                for(int i = 0; i < m_ServiceList.getLength(); i++)
                {
                    m_ServiceList[i]->Unregister(&m_Poll);
                    delete m_ServiceList[i];
                }
                
                m_ServiceList.Clear();
                m_Poll.Close();
            }
        }
        XOnTimerManager * getOnTimerManager() 
        {
            return &m_OnTimerManager;
        }
        TPoll * getPoll()
        {
            return &m_Poll;
        }
    private:
        bool                m_ExitFlag;
        bool                m_InitFlag;
        TPollEvent *        m_EventList;
        XInt                m_MaxEventCount;
        TPoll               m_Poll;
        XDynamicArray<IServiceBase *> m_ServiceList;    ///<服务类别  主要是IPC同listen服务类型
        XOnTimerManager     m_OnTimerManager;
    };


    ///网络侦听服务类型
    class XServiceNetworkListen : public IServiceBase
    {
    public:
    public:
        XServiceNetworkListen()
            :m_InitFlag(false),
             m_ListenPort(0),
             m_Tag(0)
        {
            m_OnPollEvent.bind(this, &XServiceNetworkListen::OnPollEvent);
        }
        virtual ~XServiceNetworkListen()
        {
            Close();
        }
        void Close()
        {
            if (m_InitFlag)
            {
                m_InitFlag = false;
                m_ListenSocket.Close();
            }
        }
        virtual XInt Register(TPoll * paramPoll)
        {
            if (!m_InitFlag)
            {
                return ECEC_HAS_NOT_BEEN_INITIALISED;
            }
            XInt iRet = paramPoll->AddEvent(m_ListenSocket.getSocketID(), EPC_IN, &m_OnPollEvent);
            if (isNotOK(iRet))
            {
                ZDH_ERROR("Register Listen Socket Fail:Ret=%d", iRet);
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
            XInt iRet = paramPoll->DelEvent(m_ListenSocket.getSocketID());
            if (isNotOK(iRet))
            {
                ZDH_ERROR("Unregister fail! Ret=%",iRet);
                iRet = ECEC_UNREGISTER_SOCKET_FAIL;
            }
            return ERR_OK;
        }

        virtual XInt getServiceType() const
        {
            return EST_NETWORK_LISTEN;
        }

        XInt Init(const char * paramIP, XWord paramPort, const char * paramPolicyFile, XDDWord paramTag)
        {
            XInt iRet = ERR_OK;
            do 
            {
                if (m_InitFlag)
                {
                    iRet = ECEC_HAS_ALREADY_BEEN_INITIALIZED;
                    ZDH_ERROR("Listen has already been initialized!");
                    break;
                }

                m_ListenIP      = paramIP;
                m_ListenPort    = paramPort;
                m_PolicyFile    = paramPolicyFile;
                m_Tag           = paramTag;

                iRet = m_ListenSocket.Open(AF_INET, SOCK_STREAM, 0);
                if(isNotOK(iRet))
                {
                    ZDH_ERROR("Open Listen Object Fail! Ret=%d",iRet);
                    iRet = ECEC_OPEN_LISTEN_SOCKET_FAIL;
                    break;
                }

                int on;
                setsockopt(m_ListenSocket.getSocketID(), SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on));
                iRet = m_ListenSocket.setBlockStatus(false);
                if (isNotOK(iRet))
                {
                    ZDH_ERROR("Set socket NON block fail! Ret=%d errno=%d", iRet, xerrno());
                    iRet = ECEC_SOCKET_SET_BLOCK_STATUS_FAIL;
                    break;
                }

                sockaddr_in stSocketAddr;
                MemoryZero(stSocketAddr);
                stSocketAddr.sin_family = PF_INET;
                if (m_ListenIP.isEmpty())
                {
                    stSocketAddr.sin_addr.s_addr = INADDR_ANY;
                }
                else
                {
                    stSocketAddr.sin_addr.s_addr = inet_addr(m_ListenIP.c_str());
                }

                setsockopt(m_ListenSocket.getSocketID(), SOL_SOCKET, SO_KEEPALIVE, (const char*)&iRet, sizeof(iRet));
                struct linger ling = {0, 0};
                setsockopt(m_ListenSocket.getSocketID(), SOL_SOCKET, SO_LINGER, (const char*)&ling, sizeof(ling));                

                stSocketAddr.sin_port = htons(m_ListenPort);
                iRet = bind(m_ListenSocket.getSocketID(), (const sockaddr *)&stSocketAddr, sizeof(sockaddr_in));
                if (iRet < 0)
                {
                    ZDH_ERROR("listen bind ip =%s port=%d fail ret=%d errno = %d", paramIP, paramPort, iRet, xerrno());
                    iRet = ECEC_SOCKET_BIND_FAIL;
                    break;
                }
                iRet = listen(m_ListenSocket.getSocketID(), 1024);
                if (iRet < 0)
                {
                    ZDH_ERROR("start listen fail! ret=%d errno=%d", iRet,xerrno());
                    iRet = ECEC_LISTEN_FAIL;
                    break;
                }
                m_InitFlag = true;
            } while (false);
            if (isNotOK(iRet))
            {
                m_ListenSocket.Close();
            }
            return ERR_OK;
        }

        bool getInitFlag() const
        {
            return m_InitFlag;
        }

        const XAnsiString & getListenIP() const
        {
            return m_ListenIP;
        }

        XWord getListenPort() const
        {
            return m_ListenPort;
        }

        const XAnsiString & getPolicyFile() const
        {
            return m_PolicyFile;
        }

        XDDWord getTag() const
        {
            return m_Tag;
        }

        TOnAcceptEvent & getOnAcceptEvent()
        {
            return m_OnAcceptEvent;
        }
    private:
        void OnPollEvent(TPoll * paramPoll, TPollFlag paramFlag)
        {
            if (isPollIn(paramFlag))
            {
                struct sockaddr_in stClientAddr;
                xsocklen_t stClientLen = int(sizeof(stClientAddr));
                xsocket_t stClientID = ::accept(m_ListenSocket.getSocketID(), (sockaddr *)&stClientAddr, &stClientLen);
                if (stClientID == INVALID_SOCKET)
                {
                    ZDH_ERROR("Accept client connect fail: socket id=%d", stClientID);
                    return;
                }
                bool bAccept = false;
                if (!m_OnAcceptEvent.empty())
                {
                    bAccept = m_OnAcceptEvent(paramPoll, this, stClientID, ntohl(stClientAddr.sin_addr.s_addr), ntohs(stClientAddr.sin_port));
                }
                if(!bAccept)
                {
                    xclosesocket(stClientID);
                }
            }
            //if (isPollOut(paramFlag))
            //{
                //LOG
            //}
            //if (isPollError(paramFlag))
            //{
                //LOG
            //}
        }
    private:
        TOnPollEvent m_OnPollEvent;     ///<当有poll事件到达时
        bool m_InitFlag;                ///<初始化标志
        XSocket m_ListenSocket;         ///<侦听连接socket对象
        XAnsiString m_ListenIP;         ///<侦听的IP地址
        XWord m_ListenPort;             ///<侦听的端口
        XAnsiString m_PolicyFile;       ///<
        XDDWord m_Tag;                  ///<tag
        TOnAcceptEvent m_OnAcceptEvent; ///<确定是否要接受请求事件
    };
}
#endif
