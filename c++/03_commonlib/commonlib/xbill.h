#ifndef _X_BILL_H_
#define _X_BILL_H_
#include <xos_include.h>
#include <xstring.h>
#include <xdatetime.h>
///建议用syslog-ng替换现有的syslog
/**
    基于syslog的账单类
 */
#if !defined(OS_LINUX)
    //模拟Syslog相关的API,让它可以在windows下面正确编译
    namespace zdh
    {
        inline void openlog(const char *, int, int) {}
        inline void syslog(int, const char *, ...) {}
        inline void closelog(void) {}
        inline void vsyslog(int, const char *, va_list){}
        #define LOG_NDELAY  1
        #define LOG_LOCAL3  1
        #define ZDH_INFO    1
    }
#endif
namespace zdh
{
    ///账单日志基类
    /**
        这个类提供了基本的账单接口，这个接口向syslog写入账单信息。
     */
    class XBillBase
    {
    public:

        XBillBase()
            :m_InitFlag(false), m_ServerID(0)
        {}

        virtual ~XBillBase()
        {
            closelog();
        }
        ///初始化
        /**
            @param [in] paramServerID 服务器ID
         */
        XInt Init(const XDWord paramServerID)
        {
            if (!m_InitFlag)              
            {
                m_Conent = "";
                m_IDent = "";
                m_IDent.ensureCapacity(64);
                m_ServerID = paramServerID;
                m_InitFlag = true;
                openlog(m_IDent.c_str(), LOG_NDELAY, LOG_LOCAL3);
            }
            return ERR_OK;
        }

    protected:
        void WriteBill(XDDWord paramUID, XInt paramBillID)
        {
            m_IDent.printf("SVR%02d", (XInt)(paramUID%100));
            char szTime[24];
            m_DateTime.SetNowDateTime();
            m_DateTime.ToString(szTime);
            syslog(ZDH_INFO, "%llu^%s^%u^%d^%s", paramUID, szTime, m_ServerID, paramBillID, m_Conent.c_str());
        }
    public:
        XAnsiString                     m_Conent;       ///<日志缓冲区
    private:
        XAnsiString                     m_IDent;        ///<日志标示
        bool                            m_InitFlag;     ///<初始化标志
        XDWord                          m_ServerID;     ///<服务器ID
        XDateTime<XAnsiString>          m_DateTime;
    };
}
#endif
