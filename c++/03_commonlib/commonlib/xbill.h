#ifndef _X_BILL_H_
#define _X_BILL_H_
#include <xos_include.h>
#include <xstring.h>
#include <xdatetime.h>
///������syslog-ng�滻���е�syslog
/**
    ����syslog���˵���
 */
#if !defined(OS_LINUX)
    //ģ��Syslog��ص�API,����������windows������ȷ����
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
    ///�˵���־����
    /**
        ������ṩ�˻������˵��ӿڣ�����ӿ���syslogд���˵���Ϣ��
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
        ///��ʼ��
        /**
            @param [in] paramServerID ������ID
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
        XAnsiString                     m_Conent;       ///<��־������
    private:
        XAnsiString                     m_IDent;        ///<��־��ʾ
        bool                            m_InitFlag;     ///<��ʼ����־
        XDWord                          m_ServerID;     ///<������ID
        XDateTime<XAnsiString>          m_DateTime;
    };
}
#endif
