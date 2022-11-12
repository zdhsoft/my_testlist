#ifndef _X_SYNC_H_
#define _X_SYNC_H_
#include <xtype.h>
#if defined(OS_LINUX)
    #include <pthread.h>
#elif defined(OS_WINDOWS)
    #include <windows.h>
#endif
#include <cassert>
namespace zdh
{
    template<class Lock>
    class XLockGuard
    {
    public:
        XLockGuard(Lock & paramLock)
            :m_Lock(paramLock)
        {
            m_Lock.Enter();
        }
        ~XLockGuard()
        {
            m_Lock.Leave();
        }
    private:
        Lock & m_Lock;
    };

    class XNullLock
    {
    public:
        void Enter()
        {
        }

        void Leave()
        {
        }

        void Acquire()
        {
        }

        void Release()
        {
        }
    };
    #if defined(OS_WINDOWS)
        inline void XSleep(XDWord dwMillis)
        {
            Sleep(dwMillis);
        }
        class XCriticalSection
        {
        public:
            XCriticalSection()
            {
                InitializeCriticalSection(&m_CriticalSection);
            }

            ~XCriticalSection()
            {
                DeleteCriticalSection(&m_CriticalSection);
            }
            void Acquire()
            {
                EnterCriticalSection(&m_CriticalSection);
            }
            void Release()
            {
                LeaveCriticalSection(&m_CriticalSection);
            }
            void Enter()
            {
                Acquire();
            }
            void Leave()
            {
                Release();
            }
        private:
            CRITICAL_SECTION m_CriticalSection;
        };
    #elif defined(OS_LINUX)
        inline void XSleep(XDWord dwMillis)
        {
            usleep(dwMillis * 1000);
        }

        class XCriticalSection
        {
        public:
            XCriticalSection()
            {
                pthread_mutex_init(&m_lock,NULL);
            }

            ~XCriticalSection()
            {
                pthread_mutex_destroy(&m_lock);
            }
            void Acquire()
            {
                pthread_mutex_lock(&m_lock);
            }
            void Release()
            {
                pthread_mutex_unlock(&m_lock);
            }
            void Enter()
            {
                Acquire();
            }
            void Leave()
            {
                Release();
            }
        private:
            pthread_mutex_t m_lock;
        };
    #endif
}
#endif
