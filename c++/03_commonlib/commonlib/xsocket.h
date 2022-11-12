#ifndef _X_SOCKET_H_
#define _X_SOCKET_H_
#include <xtype.h>
#include <xos_include.h>
#include <FastDelegate.h>
#include <xpollbase.h>
#include <xlog.h>
#include <xcommon_error_code.h>
namespace zdh
{

    ///socket对象，提供基本的读写功能
    class XSocket
    {
    public:
        XSocket()
            :m_SocketID(INVALID_SOCKET),
             m_SocketType(SOCK_STREAM),
             m_Family(PF_INET),
             m_Protocol(0),
             m_BlockStatus(true)
        {
        }
        ///创建一个socket
        /**
            要求创建一个socket的时候，会检查这个socket是否是有效的。如果是有效的，则会返回-1，表示
            socket已经是打开了的。
            @param [in] paramFamily     The address family specification @see AF_INET or AF_INET6
            @param [in] paramSocketType The type specification for the new socket. see SOCK_STREAM
            @param [in] paramProtocol   The protocol to be used.
            @return XInt 打开socket结果
                - ERR_OK 打开成功
                - ECEC_SOCKET_IS_OPEDED socket已经是创建了
                - ECEC_SOCKET_OPEN_FAIL 创建socket失败
         */
        XInt Open(XInt paramFamily, XInt paramSocketType, XInt paramProtocol)
        {
            if (isValid())
            {
                return ECEC_SOCKET_IS_OPEDED;
            }

            m_SocketID = ::socket(paramFamily, paramSocketType, paramProtocol);
            if (m_SocketID != INVALID_SOCKET)
            {
                m_Family        = paramFamily;
                m_SocketType    = paramSocketType;
                m_Protocol      = paramProtocol;
                return ERR_OK;
            }
            else
            {
                ZDH_ERROR("create socket fail: errno = %d", xerrno());
                return ECEC_SOCKET_OPEN_FAIL;
            }
        }

        ///重置一个socket
        /**
            这个方法是将一个已经打开的socket，设置到这个socket对象中。在设置过程中，会检查当前的socket是否是有效的。
            如果是有效的，则会重置失败。故在设置前，请先关闭。
            @param [in] paramSocketID   要重置的socket句柄
            @param [in] paramFamily     The address family specification @see AF_INET or AF_INET6
            @param [in] paramSocketType The type specification for the new socket. see SOCK_STREAM
            @param [in] paramProtocol   The protocol to be used.
            @param [in] paramBlockStatus 这个socket的block状态
                - true  表示是阻塞的
                - false 表示是异步非阻塞的
            @return XInt 打开socket结果
                - ERR_OK 打开成功
                - ECEC_SOCKET_IS_OPEDED socket已经是创建了
         */
        XInt Reset(xsocket_t paramSocketID, XInt paramFamily, XInt paramSocketType, XInt paramProtocol, bool paramBlockStatus)
        {
            if (isValid())
            {
                return ECEC_SOCKET_IS_OPEDED;
            }
            m_SocketID      = paramSocketID;
            m_Family        = paramFamily;
            m_SocketType    = paramSocketType;
            m_Protocol      = paramProtocol;
            m_BlockStatus   = paramBlockStatus;
            return ERR_OK;
        }

        ///关闭当前socket
        void Close()
        {
            if (isValid())
            {
                xclosesocket(m_SocketID);
                m_SocketID      = INVALID_SOCKET;
                m_Family        = 0;
                m_SocketType    = SOCK_STREAM;
                m_Protocol      = 0;
                m_BlockStatus   = 0;
            }
        }
        
        ///判断当前socket是否是有效的
        bool isValid()
        {
            return (m_SocketID != INVALID_SOCKET);
        }

        bool getBlockStatus() const
        {
            return m_BlockStatus;
        }
        ///设置socket的阻塞状态
        /**
            当前socket有效的时候，才可以进行设置。
            @param [in] paramStatusFlag 设置标志
                - true 表示设置为阻塞状态
                - false 表示设置为非阻塞的状态
            @return XInt 设置结果
                - ERR_OK 设置成功
                - ECEC_SOCKET_INVALID 当前socket是无效的，设置失败
                - -2 当前socket是有效的，但设置失败
         */
        XInt setBlockStatus(bool paramStatusFlag)
        {
            if (!isValid())
            {
                return ECEC_SOCKET_INVALID;
            }
            if (paramStatusFlag == m_BlockStatus)
            {
                return ERR_OK;
            }
            #if defined(OS_WINDOWS)
            if( paramStatusFlag )
            {
                u_long mode = 0;
                if (ioctlsocket(m_SocketID, FIONBIO, &mode) != 0)
                {
                    return ECEC_SOCKET_SET_BLOCK_FAIL;
                }
            }
            else
            {
                u_long mode = 1;
                if (ioctlsocket(m_SocketID,FIONBIO, &mode) != 0)
                {
                    return ECEC_SOCKET_SET_NONBLOCK_FAIL;
                }
            }
            #elif defined(OS_LINUX)
            if( paramStatusFlag )
            {
                XInt val = fcntl(m_SocketID, F_GETFL, 0);
                if( val != -1 ) 
                {
                    val=val & (0xffffffff^O_NONBLOCK);
                    val = fcntl(m_SocketID, F_SETFL, val);
                }
                if (val != 0)
                {
                    return ECEC_SOCKET_SET_BLOCK_FAIL;
                }
            }
            else
            {
                XInt val = fcntl(m_SocketID, F_GETFL, 0);

                if( val != -1 ) 
                {
                    val = val | O_NONBLOCK;
                    val = fcntl(m_SocketID,F_SETFL, val);
                }
                if (val != 0)
                {
                    return ECEC_SOCKET_SET_NONBLOCK_FAIL;
                }
            }
            #endif
            m_BlockStatus = paramStatusFlag;
            return ERR_OK;
        }

        bool isTCP() const
        {
            return m_SocketType == SOCK_STREAM;
        }

        xsocket_t getSocketID() const
        {
            return m_SocketID;
        }

        XInt getSocketType() const
        {
            return m_SocketType;
        }

        XInt getFamily() const
        {
            return m_Family;
        }

        ///接收数据
        /**
            这个函数，并不会对socket有效进行检查，请注意。
            接收到字节数放到paramRecvSize中返回。
            @param [out] paramRecvBuffer 接收的缓冲区
            @param [in]  paramRecvBufferSize 接收缓冲区的大小
            @param [out] paramRecvSize 实际接收到的字节数
            @return XInt 接收结果
                - ERR_OK 接收成功，接收字节数，有可能是0
                - EPC_CONNRESET 连接别重置，也就是断开了
                - 其他 是对应的错误信息，具体查询错误信息代号的意思
         */
        XInt Recv( XChar * paramRecvBuffer, XInt paramRecvBufferSize, XInt& paramRecvSize )
        {
            XInt iRet = ERR_OK;
            paramRecvSize = 0;
            iRet = ::recv(m_SocketID, paramRecvBuffer, paramRecvBufferSize, 0);
            if (iRet > 0)
            {
                paramRecvSize = iRet;
                return ERR_OK;
            }
            else if(iRet == 0)
            {
                return EPC_CONNRESET;
            }
            else
            {
                XInt iErrNo = xerrno();
                if (iErrNo == EPC_INTR || iErrNo == EPC_INPROGRESS || iErrNo == EPC_WOULDBLOCK)
                {
                    return ERR_OK;
                }
                else 
                {
                    return iErrNo;
                }
            }
        }
        ///发送数据
        /**
            这个函数，并不会对socket有效进行检查，请注意。
            发送的字节数放到paramSendSize中返回。
            @param [out] paramSendData 要发送的数据
            @param [in]  paramSendDataSize 要发送的字节数
            @param [out] paramSendSize 实际接发送的字节数
            @return XInt 发送结果
                - ERR_OK 接收成功，接收字节数，有可能是0
                - EPC_CONNRESET 连接别重置，也就是断开了
                - 其他 是对应的错误信息，具体查询错误信息代号的意思
         */
        XInt Send( const char * paramSendData, const int paramSendDataSize, int & paramSendSize )
        {
            XInt iRet = 0;
            paramSendSize = 0;

            while (paramSendSize < paramSendDataSize)
            {

                iRet = ::send(m_SocketID, paramSendData + paramSendSize, paramSendDataSize - paramSendSize, 0);

                if (iRet > 0)
                {
                    paramSendSize += iRet;
                }
                else
                {
                    XInt iErrNo = xerrno();
                    if (iErrNo == EPC_INTR)
                    {
                        continue;
                    }
                    else if (iErrNo == EPC_INPROGRESS || iErrNo == EPC_WOULDBLOCK)
                    {
                        continue;
                    }
                    else
                    {
                        return iErrNo;
                    }
                }
            }

            return 0;
        }
    private:
        xsocket_t   m_SocketID;         ///<socket句柄
        XInt        m_SocketType;       ///<socket类型
        XInt        m_Family;           ///<协议族
        XInt        m_Protocol;         
        bool        m_BlockStatus;      ///<阻塞状态 true表示阻塞
    };
}
#endif
