#ifndef _X_POLL_H_
#define _X_POLL_H_
#include <xpollbase.h>
#include <map>
#include <list>
#include <xsyn.h>
namespace zdh
{
    //基于select对epoll的模拟
    class XSelectPoll
    {
    public:
        struct SOnEvent
        {
            xsocket_t  SocketID;
            TPollEvent PollEvent;
        };
        typedef std::map<xsocket_t, TPollEvent> TMapEvent;
        typedef std::list<SOnEvent> TListEvent;
    public:
        XSelectPoll()
            :m_CreateFlag(false), 
             m_CreateSize(0)
        {}
        ~XSelectPoll()
        {
            Close();
        }
        ///创建poll对象
        /**
            @param [in] paramSize 最大的poll连接数
            @return XInt 创建的结果
                - ERR_OK 创建成功
                - ERR_FAIL 创建失败
         */
        XInt Create(XInt paramSize)
        {
            XInt iRet;
            if (!m_CreateFlag)
            {
                m_CreateFlag = true;
                m_CreateSize = paramSize;
                iRet         = ERR_OK;
            }
            else
            {
                iRet         = ERR_FAIL;
            }
            return iRet;
        }

        xsocket_t getFD() const
        {
            return m_CreateSize;
        }

        XInt getCreateSize() const
        {
            return m_CreateSize;
        }

        bool isCreated() const
        {
            return m_CreateFlag;
        }

        XInt AddEvent(xsocket_t paramFD, TPollFlag paramEventFlag, void * paramPollEvent)
        {
            XInt iRet;
            if (m_CreateFlag)
            {
                if (m_MapEvent.size() >= FD_SETSIZE && m_MapEvent.find(paramFD) == m_MapEvent.end())
                {
                    iRet = ERR_FAIL;
                }
                else
                {
                    TPollEvent stEvent;
                    MemoryZero(stEvent);
                    stEvent.events = paramEventFlag;
                    stEvent.data.ptr = (void *)paramPollEvent;
                    m_MapEvent[paramFD] = stEvent;
                    iRet = ERR_OK;
                }
            }
            else
            {
                iRet = ERR_FAIL;
            }
            return iRet;
        }

        XInt ModEvent(xsocket_t paramFD, TPollFlag paramEventFlag, void * paramPollEvent)
        {
            XInt iRet;
            if (m_CreateFlag)
            {
                if (m_MapEvent.size() >= FD_SETSIZE && m_MapEvent.find(paramFD) == m_MapEvent.end())
                {
                    iRet = ERR_FAIL;
                }
                else
                {
                    TPollEvent stEvent;
                    stEvent.events      = paramEventFlag;
                    stEvent.data.ptr    = (void *)paramPollEvent;
                    m_MapEvent[paramFD] = stEvent;
                    iRet                = ERR_OK;
                }
            }
            else
            {
                iRet = ERR_FAIL;
            }
            return iRet;
        }

        XInt DelEvent(xsocket_t paramFD)
        {
            XInt iRet;
            if (m_CreateFlag)
            {
                m_MapEvent.erase(paramFD);
                for (TListEvent::iterator iter = m_ListEvent.begin(); iter != m_ListEvent.end() ; )
                {
                    if(iter->SocketID == paramFD)
                    {
                        TListEvent::iterator iterRemove = iter;
                        ++iter;
                        m_ListEvent.erase(iterRemove);
                    }
                    else
                    {
                        ++iter;
                    }
                }
                iRet = ERR_OK;
            }
            else
            {
                iRet = ERR_FAIL;
            }
            return iRet;
        }

        XInt Close()
        {
            XInt iRet;
            if (m_CreateFlag)
            {
                m_CreateFlag = false;
                m_CreateSize = 0;
                m_MapEvent.clear();
                m_ListEvent.clear();
                iRet = ERR_OK;
            }
            else
            {
                iRet = ERR_FAIL;
            }
            return iRet;
        }
        XInt Wait(XInt paramMaxEventCount, TPollEvent * paramEventList, XInt paramWaitTime)
        {
            XInt iRetEventCount = 0;
            do
            {
                if(!m_CreateFlag)
                {
                    iRetEventCount = ERR_FAIL;
                    break;
                }
                if (paramMaxEventCount < 1 || isNULL(paramEventList) || paramWaitTime < EPC_INDEFINITELY)
                {
                    iRetEventCount = ERR_FAIL;
                    break;
                }
                iRetEventCount = ReadEvent(paramMaxEventCount, paramEventList);
                if( iRetEventCount > 0)
                {
                    break;
                }
                if (m_MapEvent.empty())
                {
                    XSleep(1);
                    iRetEventCount = 0;
                    break;
                }
                fd_set stReadSet;
                fd_set stWriteSet;
                fd_set stExcepSet;
                FD_ZERO(&stReadSet);
                FD_ZERO(&stWriteSet);
                FD_ZERO(&stExcepSet);
                for (TMapEvent::iterator iter = m_MapEvent.begin(); iter != m_MapEvent.end() ; ++iter )
                {
                    TPollEvent & stEvent = iter->second;
                    xsocket_t stFD = iter->first;
                    if(isPollIn(stEvent.events))
                    {
                        FD_SET(stFD, & stReadSet);
                    }
                    if(isPollOut(stEvent.events))
                    {
                        FD_SET(stFD, & stWriteSet);
                    }
                    if(isPollError(stEvent.events))
                    {
                        FD_SET(stFD, & stExcepSet);
                    }
                }
                timeval stWaitTime;
                if(paramWaitTime != EPC_INDEFINITELY)
                {
                    stWaitTime.tv_sec = paramWaitTime / 1000;
                    stWaitTime.tv_usec = (paramWaitTime % 1000) * 1000;
                }
                XInt iRet = ::select(m_MapEvent.rbegin()->first+1, &stReadSet, &stWriteSet, &stExcepSet, paramWaitTime == EPC_INDEFINITELY?NULL:&stWaitTime);
                if (iRet < 0)
                {
                    iRetEventCount = ERR_FAIL;
                    break;
                }

                if(iRet > 0)
                {
                    SOnEvent stEvent;
                    for(TMapEvent::iterator iter = m_MapEvent.begin(); iter != m_MapEvent.end(); ++iter)
                    {
                        stEvent.SocketID            = iter->first;
                        stEvent.PollEvent.events    = EPC_NONE;
                        stEvent.PollEvent.data.u64  = 0;
                        if(FD_ISSET(stEvent.SocketID, &stReadSet))
                        {
                            stEvent.PollEvent.events |= EPC_IN;
                        }
                        if(FD_ISSET(stEvent.SocketID, &stWriteSet))
                        {
                            stEvent.PollEvent.events |= EPC_OUT;
                        }
                        if(FD_ISSET(stEvent.SocketID, &stExcepSet))
                        {
                            stEvent.PollEvent.events |= EPC_ERR;
                        }

                        if(stEvent.PollEvent.events != EPC_NONE)
                        {
                            stEvent.PollEvent.data.u64 = iter->second.data.u64;
                            m_ListEvent.push_back(stEvent);
                        }
                    }
                    iRetEventCount = ReadEvent(paramMaxEventCount, paramEventList);
                }
                else 
                {
                    iRetEventCount = 0;
                }
            }while(false);
            return iRetEventCount;
        }
    private:
        XInt ReadEvent(XInt paramMaxEventCount, TPollEvent * paramEventList)
        {
            XInt iRet = 0;
            if(!m_ListEvent.empty())
            {
                XInt iCount = 0;
                TListEvent::iterator iter = m_ListEvent.begin();
                for(;iCount < paramMaxEventCount && iter != m_ListEvent.end(); ++iCount)
                {
                    paramEventList[iCount] = iter->PollEvent;
                    TListEvent::iterator iterRemove = iter;
                    ++iter;
                    m_ListEvent.erase(iterRemove);
                }
                iRet = iCount;
            }
            return iRet;
        }
    private:

        bool        m_CreateFlag;   ///<创建标志
        XInt        m_CreateSize;   ///<创建的大小
        TMapEvent   m_MapEvent;     ///<事件映射表
        TListEvent  m_ListEvent;    ///<事件列表
    };

#if defined(OS_LINUX)
    class XEPoll
    {
    public:
        XEPoll()
            :m_CreateFlag(false),
             m_EPollFD(INVALID_SOCKET),
             m_CreateSize(0)
        {}
        ~XEPoll()
        {
            Close();
        }
        XInt Create(XInt paramSize)
        {
            XInt iRet;
            if(!m_CreateFlag)
            {
                xsocket_t ifd = epoll_create(paramSize);
                if(ifd == INVALID_SOCKET)
                {
                    iRet = ERR_FAIL;
                }
                else
                {
                    m_EPollFD       = ifd;
                    m_CreateFlag    = true;
                    m_CreateSize    = paramSize;
                    iRet            = ERR_OK;
                }
            }
            else
            {
                iRet = ERR_FAIL;
            }
            return iRet;
        }

        xsocket_t getFD() const
        {
            return m_EPollFD;
        }

        XInt getCreateSize() const
        {
            return m_CreateSize;
        }

        bool isCreated() const
        {
            return m_CreateFlag;
        }
        XInt AddEvent(xsocket_t paramFD, TPollFlag paramEventFlag, void * paramPollEvent)
        {
            XInt iRet;
            if(m_CreateFlag)
            {
                TPollEvent stEvent;
                stEvent.data.ptr = (void *)paramPollEvent;
                stEvent.events = paramEventFlag;
                iRet = epoll_ctl(m_EPollFD, EPOLL_CTL_ADD, paramFD, &stEvent);
                if(isOK(iRet))
                {
                    iRet = ERR_OK;
                }
                else
                {
                    iRet = ERR_FAIL;
                }
            }
            else
            {
                iRet = ERR_FAIL;
            }
            return iRet = iRet;

        }
        XInt ModEvent(xsocket_t paramFD, TPollFlag paramEventFlag, void * paramPollEvent)
        {
            XInt iRet;
            if(m_CreateFlag)
            {
                TPollEvent stEvent;
                stEvent.data.ptr = (void *)paramPollEvent;
                stEvent.events = paramEventFlag;
                iRet = epoll_ctl(m_EPollFD, EPOLL_CTL_MOD, paramFD, &stEvent);
                if(isOK(iRet))
                {
                    iRet = ERR_OK;
                }
                else
                {
                    iRet = ERR_FAIL;
                }
            }
            else
            {
                iRet = ERR_FAIL;
            }
            return iRet = iRet;

        }
        XInt DelEvent(xsocket_t paramFD)
        {
            XInt iRet;
            if(m_CreateFlag)
            {
                iRet = epoll_ctl(m_EPollFD, EPOLL_CTL_DEL, paramFD, NULL);
                if(isOK(iRet))
                {
                    iRet = ERR_OK;
                }
                else
                {
                    iRet = ERR_FAIL;
                }
            }
            else
            {
                iRet = ERR_FAIL;
            }
            return iRet;
        }
        XInt Close()
        {
            XInt iRet;
            if(m_CreateFlag)
            {
                m_CreateFlag = false;
                m_CreateSize = 0;
                close(m_EPollFD);
                m_EPollFD = -1;
                iRet = ERR_OK;
            }
            else
            {
                iRet = ERR_FAIL;
            }
            return iRet;
        }
        XInt Wait(XInt paramMaxEventCount, TPollEvent * paramEventList, XInt paramWaitTime)
        {
            XInt iRetEventCount;
            if(!m_CreateFlag)
            {
                iRetEventCount = ERR_FAIL;
            }
            else
            {
                iRetEventCount = epoll_wait(m_EPollFD, paramEventList, paramMaxEventCount, paramWaitTime);
            }
            return iRetEventCount;
        }
    private:
        bool m_CreateFlag;
        xsocket_t m_EPollFD;
        XInt m_CreateSize;
    };
#endif
}
#endif
