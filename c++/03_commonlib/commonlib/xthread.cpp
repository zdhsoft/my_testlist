#include "xthread.h"
#if defined(OS_LINUX)
    #include <unistd.h>
#endif
namespace zdh
{
    XCriticalSection GlobalLock;
    XInt XThread::m_ControlThreadCount = 0;
    bool XThread::m_ExitThread = false;

    void XThread::WaitAllThreadExit()
    {
        while(m_ControlThreadCount > 0) XSleep(10);
    }

    bool XThread::GetExitThreadFlag() 
    { 
        return m_ExitThread; 
    }
    void XThread::ExitThread() 
    { 
        m_ExitThread = true; 
    }
#if defined(OS_WINDOWS)
    void XEndThread(int iExitCode);
    HANDLE XBeginThread(XThread * aThreadObject,DWORD * aThreadID);
    DWORD WINAPI XThreadFunction(void * aThreadObject);


    DWORD WINAPI XThreadFunction(void * aThreadObject)
    {
        GlobalLock.Enter();
        XThread::m_ControlThreadCount++;
        GlobalLock.Leave();
        
        XThread * aThread = (XThread *)aThreadObject;
        aThread->m_Finished = false;
        try
        {
            if( !aThread->m_Terminated )
            {
                
                aThread->Execute();
                

            }
        }catch(...)
        {
            aThread->SetReturnValue(-1);
        }
        
        aThread->m_Finished = true;
        DWORD dwResult = aThread->m_ReturnValue;
        if( aThread->m_FreeOnTerminate ) delete aThread;
        GlobalLock.Enter();
        XThread::m_ControlThreadCount--;
        GlobalLock.Leave();
        XEndThread(dwResult);
        return dwResult;
    }
    //开始线程
    HANDLE XBeginThread(XThread * aThreadObject,DWORD * aThreadID)
    {
        return CreateThread(NULL,0,XThreadFunction,(void *)aThreadObject,0,aThreadID);
    }
    //结束线程
    void XEndThread(int iExitCode)
    {
        ExitThread(iExitCode);
    }

//////////////////////////////////////////////////////////////////////////
    XThread::XThread()
        :m_Finished(false),m_Handle(NULL),m_Terminated(false),m_ThreadID(0),m_FreeOnTerminate(false),m_ReturnValue(0),m_Start(false),m_ExitFlag(false)
    {
    }
    XThread::~XThread()
    {

    }
    void XThread::Start()
    {
        if( m_Start ) return;
        m_Start = true;
        m_Handle = XBeginThread(this,&m_ThreadID);
        if( m_Handle == NULL)
        {
            throw "Create Thread Fail!";
        }
    }

//////////////////////////////////////////////////////////////////////////
#elif defined(OS_LINUX)

    void * XThreadFunction(void * arg)
    {
        GlobalLock.Enter();
        XThread::m_ControlThreadCount++;
        GlobalLock.Leave();
        XThread * t = (XThread *)arg;
        t->m_Finished = false;
        t->m_ReturnValue = 0;
        t->m_ErrorCode = 0;
        try
        {
            t->Execute();
        }catch(...)
        {
            t->m_ErrorCode =-1;
        }
        GlobalLock.Enter();
        XThread::m_ControlThreadCount--;
        GlobalLock.Leave();
        t->m_Finished =true;
        int iReturnValue = t->m_ReturnValue;
        if( t->GetFreeOnTerminate() ) delete t;
        pthread_exit((void *)&iReturnValue);
    }

    XThread::XThread()
        :m_FreeOnTerminate(false),
         m_Finished(false),
         m_ReturnValue(0),
         m_ErrorCode(0),
         m_Start(false),
         m_ExitFlag(false)
    {
    }
    XThread::~XThread()
    {
    }
    int XThread::Start()
    {
        if( m_Start ) return 0;
        m_Start = true;
        m_ErrorCode = pthread_create(&m_ThreadID,NULL,XThreadFunction,(void *)this);
        return m_ErrorCode;
    }
#endif
} // end of namespace NSI


