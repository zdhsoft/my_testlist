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

    ///socket�����ṩ�����Ķ�д����
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
        ///����һ��socket
        /**
            Ҫ�󴴽�һ��socket��ʱ�򣬻������socket�Ƿ�����Ч�ġ��������Ч�ģ���᷵��-1����ʾ
            socket�Ѿ��Ǵ��˵ġ�
            @param [in] paramFamily     The address family specification @see AF_INET or AF_INET6
            @param [in] paramSocketType The type specification for the new socket. see SOCK_STREAM
            @param [in] paramProtocol   The protocol to be used.
            @return XInt ��socket���
                - ERR_OK �򿪳ɹ�
                - ECEC_SOCKET_IS_OPEDED socket�Ѿ��Ǵ�����
                - ECEC_SOCKET_OPEN_FAIL ����socketʧ��
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

        ///����һ��socket
        /**
            ��������ǽ�һ���Ѿ��򿪵�socket�����õ����socket�����С������ù����У����鵱ǰ��socket�Ƿ�����Ч�ġ�
            �������Ч�ģ��������ʧ�ܡ���������ǰ�����ȹرա�
            @param [in] paramSocketID   Ҫ���õ�socket���
            @param [in] paramFamily     The address family specification @see AF_INET or AF_INET6
            @param [in] paramSocketType The type specification for the new socket. see SOCK_STREAM
            @param [in] paramProtocol   The protocol to be used.
            @param [in] paramBlockStatus ���socket��block״̬
                - true  ��ʾ��������
                - false ��ʾ���첽��������
            @return XInt ��socket���
                - ERR_OK �򿪳ɹ�
                - ECEC_SOCKET_IS_OPEDED socket�Ѿ��Ǵ�����
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

        ///�رյ�ǰsocket
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
        
        ///�жϵ�ǰsocket�Ƿ�����Ч��
        bool isValid()
        {
            return (m_SocketID != INVALID_SOCKET);
        }

        bool getBlockStatus() const
        {
            return m_BlockStatus;
        }
        ///����socket������״̬
        /**
            ��ǰsocket��Ч��ʱ�򣬲ſ��Խ������á�
            @param [in] paramStatusFlag ���ñ�־
                - true ��ʾ����Ϊ����״̬
                - false ��ʾ����Ϊ��������״̬
            @return XInt ���ý��
                - ERR_OK ���óɹ�
                - ECEC_SOCKET_INVALID ��ǰsocket����Ч�ģ�����ʧ��
                - -2 ��ǰsocket����Ч�ģ�������ʧ��
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

        ///��������
        /**
            ����������������socket��Ч���м�飬��ע�⡣
            ���յ��ֽ����ŵ�paramRecvSize�з��ء�
            @param [out] paramRecvBuffer ���յĻ�����
            @param [in]  paramRecvBufferSize ���ջ������Ĵ�С
            @param [out] paramRecvSize ʵ�ʽ��յ����ֽ���
            @return XInt ���ս��
                - ERR_OK ���ճɹ��������ֽ������п�����0
                - EPC_CONNRESET ���ӱ����ã�Ҳ���ǶϿ���
                - ���� �Ƕ�Ӧ�Ĵ�����Ϣ�������ѯ������Ϣ���ŵ���˼
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
        ///��������
        /**
            ����������������socket��Ч���м�飬��ע�⡣
            ���͵��ֽ����ŵ�paramSendSize�з��ء�
            @param [out] paramSendData Ҫ���͵�����
            @param [in]  paramSendDataSize Ҫ���͵��ֽ���
            @param [out] paramSendSize ʵ�ʽӷ��͵��ֽ���
            @return XInt ���ͽ��
                - ERR_OK ���ճɹ��������ֽ������п�����0
                - EPC_CONNRESET ���ӱ����ã�Ҳ���ǶϿ���
                - ���� �Ƕ�Ӧ�Ĵ�����Ϣ�������ѯ������Ϣ���ŵ���˼
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
        xsocket_t   m_SocketID;         ///<socket���
        XInt        m_SocketType;       ///<socket����
        XInt        m_Family;           ///<Э����
        XInt        m_Protocol;         
        bool        m_BlockStatus;      ///<����״̬ true��ʾ����
    };
}
#endif
