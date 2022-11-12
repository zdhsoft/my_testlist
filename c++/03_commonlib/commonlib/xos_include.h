//这个文件主要提供OS相关的头文件，如要使用os下专有的，这需要在这里增加响应的头文件
#ifndef _X_OS_INCLUDE_H_
#define _X_OS_INCLUDE_H_
#include <xconfig.h>
#include <xtype.h>

#if defined(OS_WINDOWS)
    #include <WINSOCK2.H>
    #include <windows.h>
    #include <io.h>
    #pragma comment(lib, "ws2_32.lib")
#endif
#if defined(OS_LINUX) 
    #include <pthread.h>
    #include <unistd.h>
    #include <sys/time.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <sys/wait.h>
    #include <arpa/inet.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <sys/epoll.h>
    #include <sys/un.h>
    #include <syslog.h>
#endif
namespace zdh
{
    #if defined(OS_WINDOWS)
        typedef int                     xsocklen_t;
        typedef unsigned    int         xpid_t;
        typedef SOCKET                  xsocket_t;
        #define xerrno()                GetLastError()
        #define xclosesocket(socketid)  closesocket(socketid)
    #elif defined(OS_LINUX)
        typedef socklen_t               xsocklen_t;
        typedef pid_t                   xpid_t;
        typedef int                     xsocket_t;
        #define INVALID_SOCKET          -1
        #define xerrno()                errno
        #define xclosesocket(socketid)  close(socketid)
    #endif
}
#endif
