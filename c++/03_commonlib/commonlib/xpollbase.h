#ifndef _X_POLL_BASE_H_
#define _X_POLL_BASE_H_
#include <xos_include.h>
#include <xmemory.h>
#include <FastDelegate.h>
namespace zdh
{
    enum EnumPollConstant
    {
    #if defined(OS_WINDOWS)
        EPC_NONE                = 0x00,
        EPC_IN                  = 0x01,
        EPC_OUT                 = 0x02,
        EPC_PRI                 = 0x04,
        EPC_ERR                 = 0x08,
        EPC_HUP                 = 0x10,
        EPC_ET                  = 0x20,
        EPC_ONESHOT             = 0x40,
        EPC_WOULDBLOCK          = WSAEWOULDBLOCK,
        EPC_INPROGRESS          = WSAEINPROGRESS,
        EPC_TIME                = WSAETIMEDOUT,
        EPC_INTR                = WSAEINTR,
        EPC_CONNRESET           = WSAECONNRESET,
        EPC_INDEFINITELY        = -1,
    #elif defined(OS_LINUX)
        EPC_NONE                = 0x00,
        EPC_IN                  = EPOLLIN,
        EPC_OUT                 = EPOLLOUT,
        EPC_PRI                 = EPOLLPRI,
        EPC_ERR                 = EPOLLERR,
        EPC_HUP                 = EPOLLHUP,
        EPC_ET                  = EPOLLET,
        EPC_ONESHOT             = EPOLLONESHOT,
        EPC_WOULDBLOCK          = EWOULDBLOCK,
        EPC_INPROGRESS          = EINPROGRESS,
        EPC_TIME                = ETIME,
        EPC_INTR                = EINTR,
        EPC_CONNRESET           = ECONNRESET,
        EPC_INDEFINITELY        = -1,
    #endif
        EPC_DWORD_FORCE         = 0x7fffffffL,
    };

    #if defined(OS_WINDOWS)
        //模拟linux的epoll的事件数据
        union UPollData
        {
            xsocket_t   fd;
            XDWord      u32;
            XDDWord     u64;
            void *      ptr;
        };
        struct SPOllEvent
        {
            XDWord      events;
            UPollData   data;
        };
        typedef struct SPOllEvent   TPollEvent;
        typedef XDWord              TPollFlag;
    #elif defined(OS_LINUX)
        typedef struct epoll_event  TPollEvent;
        typedef uint32_t            TPollFlag;
    #endif
    
        //---------------------------------------------------------------------
    ///设置poll的标志位
    inline TPollFlag & SetPollFlagBit(TPollFlag & paramFlag, TPollFlag paramMode, bool paramValue)
    {
        if (paramValue)
        {
            paramFlag |= paramMode;
        }
        else
        {
            paramFlag &= (~paramMode);
        }
        return paramFlag;
    }
    ///取poll的标志位
    inline bool GetPollFlagBit(TPollFlag paramFlag, TPollFlag paramMode)
    {
        return ((paramFlag & paramMode) != 0);
    }
    
    //---------------------------------------------------------------------
    inline bool isPollIn(TPollFlag paramFlag)
    {
        return GetPollFlagBit(paramFlag, EPC_IN);
    }

    //---------------------------------------------------------------------
    inline bool isPollOut(TPollFlag paramFlag)
    {
        return GetPollFlagBit(paramFlag, EPC_OUT);
    }

    //---------------------------------------------------------------------
    inline bool isPollError(TPollFlag paramFlag)
    {
        return GetPollFlagBit(paramFlag, EPC_ERR);
    }
}
#endif
