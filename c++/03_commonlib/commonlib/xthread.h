#ifndef _X_THREAD_H_
#define _X_THREAD_H_

#include <xtype.h>
#include <xos_include.h>
#include <xsyn.h>

namespace zdh{

     #if defined(OS_WINDOWS)
//     inline void XSleep(XDWord dwMillis)
//  {
//      Sleep(dwMillis);
//  }
//     class XCriticalSection
//     {
//     public:
//         XCriticalSection()
//         {
//             InitializeCriticalSection(&m_CriticalSection);
//         }
// 
//         ~XCriticalSection()
//         {
//             DeleteCriticalSection(&m_CriticalSection);
//         }
//         void Acquire()
//         {
//             EnterCriticalSection(&m_CriticalSection);
//         }
//         void Release()
//         {
//             LeaveCriticalSection(&m_CriticalSection);
//         }
//         void Enter()
//         {
//             Acquire();
//         }
//         void Leave()
//         {
//             Release();
//         }
//     private:
//         CRITICAL_SECTION m_CriticalSection;
//     };
    
    class XThread
    {
        friend DWORD WINAPI XThreadFunction(void * aThreadObject);
    public:
        XThread();
        virtual ~XThread();
        
        void Start();

        void SetFreeOnTerminate(bool v) { m_FreeOnTerminate = v; }
        bool GetFreeOnTerminate() const { return m_FreeOnTerminate; }

        bool GetTerminated() const { return m_Terminated; }
        bool GetFinished() const { return m_Finished; }
        int GetReturnValue() const { return m_ReturnValue; }

        bool GetExitFlag() const { return m_ExitFlag; }
        void ExitThisThread() { m_ExitFlag = true; }

        static bool GetExitThreadFlag();
        static void ExitThread();

        static XInt GetControlThreadCount() { return m_ControlThreadCount; }
        static void WaitAllThreadExit();

    protected:
        void SetReturnValue(int v) { m_ReturnValue = v; }
        virtual void Execute() = 0;
    private:
        HANDLE m_Handle;
        DWORD  m_ThreadID;
        bool m_Terminated;
        bool m_FreeOnTerminate;
        bool m_Finished;
        bool m_Start;
        int  m_ReturnValue;
        bool m_ExitFlag;
        static bool m_ExitThread;
        static XInt m_ControlThreadCount;  
    };

    #elif defined(OS_LINUX)
//     inline void XSleep(XDWord dwMillis)
//  {
//      usleep(dwMillis * 1000);
//  }
// 
//     class XCriticalSection
//     {
//     public:
//         XCriticalSection()
//         {
//             pthread_mutex_init(&m_lock,NULL);
//         }
// 
//         ~XCriticalSection()
//         {
//             pthread_mutex_destroy(&m_lock);
//         }
//         void Acquire()
//         {
//             pthread_mutex_lock(&m_lock);
//         }
//         void Release()
//         {
//             pthread_mutex_unlock(&m_lock);
//         }
//         void Enter()
//         {
//             Acquire();
//         }
//         void Leave()
//         {
//             Release();
//         }
//     private:
//         pthread_mutex_t m_lock;
//     };

    class XThread
    {
        friend void * XThreadFunction(void * arg);
    public:
        XThread();
        virtual ~XThread();
        int Start();
        void SetFreeOnTerminate(bool v){ m_FreeOnTerminate = v; }
        void SetErrorCode(int aErrorCode) { m_ErrorCode = aErrorCode; }
        bool GetFinished() const { return m_Finished; }
        bool GetFreeOnTerminate() const { return m_FreeOnTerminate; }
        int  GetReturnValue() const { return m_ReturnValue; }
        int GetErrorCode() const { return m_ErrorCode; }

        bool GetExitFlag() const { return m_ExitFlag; }
        void ExitThisThread() { m_ExitFlag = true; }

        static bool GetExitThreadFlag();
        static void ExitThread();
        static XInt GetControlThreadCount() { return m_ControlThreadCount; }
        static void WaitAllThreadExit();
    protected:
        void SetReturnValue(int v) { m_ReturnValue = v; }
        virtual void Execute() = 0;
    private:
        static bool m_ExitThread;
        bool m_FreeOnTerminate;
        bool m_Finished;
        int  m_ReturnValue;
        int m_ErrorCode;
        bool m_Start;
        bool m_ExitFlag;
        pthread_t m_ThreadID;
        static XInt m_ControlThreadCount;  
    };

#endif
    extern XCriticalSection GlobalLock; //一个全局操作的锁
} // end of namespace zdh

#endif

