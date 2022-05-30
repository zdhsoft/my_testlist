//---------------------------------------------------------------------------

#ifndef dtH
#define dtH
//---------------------------------------------------------------------------
#include <windows.h>
#include <vcl.h>
namespace zdh
{

	typedef signed long long XLong;
	typedef signed long XInt;
	typedef signed short XShort;
	typedef unsigned short XWord;
	typedef AnsiString XAnsiString;
	typedef char XChar;
	typedef bool XBool;

    //������ǰ������
    template<class T> class XDateTime;      //����ʱ����
    template<class T> class XTime;          //ʱ����
    template<class T> class XDate;          //������
    template<class T> class XDurationTime;  //ʱ�䳤����
    template<class T> class XWeek;          //������

    //����ʱ����صĳ�������

    const XLong MAX_MILLIS              = 315537984000000LL;    ///<���ĺ�����
    const XLong MIN_MILLIS              = 86400000LL;           ///<��С�ĺ�����
    const XLong MILLIS_PRE_DAY64        = 86400000LL;           ///<ÿ�����ĺ�����64λ�з�������
    const XLong MAX_DURATION            = 315537897600000LL;    ///<���ĳ���ʱ��

    const XInt MILLIS_PRE_DAY           = 86400000;             ///<ÿ��ĺ����� 24:00:00.000
    const XInt MILLIS_PRE_HOUR          = 3600000;              ///<ÿСʱ������ 01:00:00.000
    const XInt MILLIS_PRE_MINUTE        = 60000;                ///<ÿ���Ӻ����� 00:01:00.000
	const XInt MILLIS_PRE_SECOND        = 1000;                 ///<ÿ��ĺ����� 00:00:01.000

	const XInt DAYS_1970_1_1            = 719163;               ///<1970-1-1����ԪԪ�������
	const XLong INVALID_MILLIS_UTC      = 0;                    ///<��Ч��UTCʱ�������
	const XLong INVALID_SECOND_UTC      = 0;                    ///<��Ч��UTCʱ������
	const XLong MILLIS_1970_1_1         = 719163LL * 86400000LL ;               ///<1970-1-1����ԪԪ�������

    const XInt MAX_MILLIS_IN_DAY        = 86400000;             ///<ÿ�����ĺ�����
    const XInt MIN_MILLIS_IN_DAY        = 0;                    ///<ÿ����С�ĺ�����

    const XInt MAX_YEAR_IN_DATETIME     = 9999;                 ///<�������
    const XInt MIN_YEAR_IN_DATETIME     = 1;                    ///<��С�����,��ԪԪ��ӹ�Ԫ1�꿪ʼ

    const XInt MAX_MONTH_IN_YEAR        = 12;                   ///<�����·�
    const XInt MIN_MONTH_IN_YEAR        = 1;                    ///<��С���·�

    const XInt MAX_DAY_IN_MONTH         = 31;                   ///<��������
    const XInt MIN_DAY_IN_MONTH         = 1;                    ///<��С������

	const XInt MAX_DAYS_IN_DATETIME     = 3652059;              ///<���������� 9999-12-31
	const XInt MIN_DAYS_IN_DATETIME     = 1;                    ///<��С�������� 0-1-1

	const XInt TIME_ZONE_CHINA          = -480;                 ///<�й�ʱ�䶫����

    ///����ʱ���쳣ֵ
    enum EnumDateTimeError
    {
        E_DATETIME_INVALIDATION_DATE    = 1,                    ///<��Ч������
        E_DATETIME_INVALIDATION_TIME,                           ///<��Ч��ʱ��
        E_DATETIME_INVALIDATION_YEAR,                           ///<��Ч����
        E_DATETIME_INVALIDATION_MONTH,                          ///<��Ч����
        E_DATETIME_INVALIDATION_DAY,                            ///<��Ч����
        E_DATETIME_INVALIDATION_HOUR,                           ///<��Ч��Сʱ
        E_DATETIME_INVALIDATION_MINUTE,                         ///<��Ч�ķ���
        E_DATETIME_INVALIDATION_SECOND,                         ///<��Ч����
        E_DATETIME_INVALIDATION_MILLIS,                         ///<��Ч�ĺ���
        E_DATETIME_INVALIDATION_DATETIME,                       ///<��Ч������ʱ��
        E_DATETIME_INVALIDATION_DAYS,                           ///<��Ч��������
        E_DATETIME_OUT,                                         ///<����ʱ�����
        E_DATETIME_DAYS_OUT,                                    ///<�������
        E_DATETIME_TIMES_OUT                                    ///<ʱ�����
    };
    ///ʱ�����ڽ���������Ϣ
    enum EnumParseDateTimeErrorCode
    {
        X_DATETIME_ERROR_OK = 0,                                ///<��������
        X_DATETIME_ERROR_INVALID_TIME_FORMAT,                   ///<��Ч��ʱ���ʽ
        X_DATETIME_ERROR_INVALID_DATE_FORMAT,                   ///<��Ч�����ڸ�ʽ
        X_DATETIME_ERROR_INVALID_WEEK_FORMAT,                   ///<��Ч�����ڸ�ʽ
        X_DATETIME_ERROR_INVALID_CHAR,                          ///<������Ч���ַ�
        X_DATETIME_ERROR_INVALID_HOUR,                          ///<������Ч��Сʱ
        X_DATETIME_ERROR_INVALID_MINUTE,                        ///<������Ч�ķ���
        X_DATETIME_ERROR_INVALID_SECOND,                        ///<������Ч����
        X_DATETIME_ERROR_INVALID_MILLIS,                        ///<������Ч�ĺ���
        X_DATETIME_ERROR_INVALID_YEAR,                          ///<������Ч��
        X_DATETIME_ERROR_INVALID_MONTH,                         ///<������Ч��
        X_DATETIME_ERROR_INVALID_DAY,                           ///<������Ч����
        X_DATETIME_ERROR_INVALID_WEEK,                          ///<������Ч���ڸ�ʽ
        X_DATETIME_ERROR_INVALID_DATETIME_FORMAT,               ///<��Ч������ʱ���ʽ
        X_DATETIME_ERROR_INVALID_DURATION_FORMAT,               ///<��Ч��ʱ����
        X_DATETIME_ERROR_INVALID_DURATION_DAYS,                 ///<��Ч��ʱ������
    };
    //������صĳ���
    enum EnumWeekDay
    {
        WEEKDAY_SUNDAY              = 0,                        ///<������
        WEEKDAY_MONDAY              = 1,                        ///<����һ
        WEEKDAY_TUESDAY             = 2,                        ///<���ڶ�
        WEEKDAY_WEDNESDAY           = 3,                        ///<������
        WEEKDAY_THURSDAY            = 4,                        ///<������
        WEEKDAY_FRIDAY              = 5,                        ///<������
        WEEKDAY_SATURDAY            = 6,                        ///<������
    };
    ///����ʱ��ṹ
    struct SSystemDateTime
    {
        XInt Year;          ///<��
        XInt Month;         ///<��
        XInt Day;           ///<��
        XInt WeekDay;       ///<����
        XInt Hour;          ///<ʱ
        XInt Minute;        ///<��
        XInt Second;        ///<��
        XInt Milliseconds;  ///<����
        XShort Zone;        ///<ʱ��,��λ����
    };
    ///���ڽṹ��
    struct SDate
    {
        XInt Year;  ///<���
        XInt Month; ///<�·�
        XInt Day;   ///<����
    };
    ///ʱ�乹����
    struct STime
    {
        XInt Hour;      ///<Сʱ
        XInt Minute;    ///<��
        XInt Second;    ///<��
        XInt Millis;    ///<����
    };

    //---------------------------------------------------------------------------------------------------
    ///�쳣�����
    class EException
    {
    public:
        ///Ĭ�Ϲ��캯��
        EException()
            :m_HelpContext(0)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        EException(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :m_Message(paramMessage),
             m_HelpContext(paramHelpContext)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        EException(const XChar* paramMessage, XInt paramHelpContext = 0)
            :m_Message(paramMessage),
            m_HelpContext(paramHelpContext)
        {}
        ///��������
        virtual ~EException()
        {}
        ///ȡ�쳣��Ϣ
        const XAnsiString getMessage() const
        {
            return m_Message;
        }
        ///�����쳣��Ϣ
        void setMessage(const XChar * paramMessage)
        {
            m_Message = paramMessage;
        }
        ///�����쳣��Ϣ
        void setMessage(const XAnsiString & paramMessage)
        {
            m_Message = paramMessage;
        }
        ///ȡ������ϢID
        XInt getHelpContext() const
        {
            return m_HelpContext;
        }
        ///���ð�����ϢID
        void setHelpContext(XInt paramHelpContext)
        {
            m_HelpContext = paramHelpContext;
        }
        ///ת�����ַ���ָ��
        operator const XChar *() const
        {
            return m_Message.c_str();
        }
    private:
        XAnsiString m_Message;  ///<�쳣��Ϣ
        XInt m_HelpContext;     ///<������ϢID
    };

    #define MESSAGE_OUT_OF_MEMORY "out of memory"
    #define MESSAGE_NOT_EXISTS "not exists object!"
    #define MESSAGE_IS_ZERO "is zero"
    #define MESSAGE_LESS_THAN_ZERO "less than zero"
    #define MESSAGE_CONVERT_FAIL "Type convert fail"
    #define MESSAGE_GREATER_THAN_ZERO "greater than zero"
    #define MESSAGE_OUT_OF_RANGE "out of range:index=%d,length=%d"

    ///�ڴ�����쳣
    class XEOutOfMemory : public EException
    {
    public:
        ///Ĭ�Ϲ��캯��
        XEOutOfMemory()
            :EException(MESSAGE_OUT_OF_MEMORY)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        XEOutOfMemory(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        XEOutOfMemory(const XChar* paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///��������
        ~XEOutOfMemory()
        {
        }
    };
    //---------------------------------------------------------------------
    class XEConvert : public EException
    {
    public:
        ///Ĭ�Ϲ��캯��
        XEConvert()
            :EException(MESSAGE_CONVERT_FAIL)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        XEConvert(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        XEConvert(const XChar* paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///��������
        ~XEConvert()
        {
        }
    };


    ///����Խ���쳣
    class XEOutOfRange : public EException
    {
    public:
        ///����Խ���쳣���캯��
        /**
            @param [in] paramIndex Խ����±�ֵ
            @param [in] aLength ��Խ�������ĳ���
        */
        XEOutOfRange(XInt paramIndex = 0,XInt aLength = 0)
            :m_Index(paramIndex),m_Length(aLength)
        {
            MakeMsg();
        }
        ///��������
        ~XEOutOfRange(){}
        ///����Խ����Ϣ
        /**
            @param [in] paramIndex Խ����±�ֵ
            @param [in] aLength ��Խ�������ĳ���
        */
        void setInfo(XInt paramIndex,XInt aLength)
        {
            m_Index = paramIndex;
            m_Length = aLength;
            MakeMsg();
        }
        ///ȡԽ����±�ֵ
        /**
            @return ����Խ����±�ֵ
         */
        XInt getIndex() const { return m_Index; }
        ///ȡ��Խ�������ĳ���
        /**
            @return ���ر�Խ��ĳ���
         */
        XInt getLength() const { return m_Length; }
    protected:
        ///�����쳣��Ϣ
        void MakeMsg()
        {
            XAnsiString strMsg;
            strMsg.printf(MESSAGE_OUT_OF_RANGE,m_Index,m_Length);
            setMessage(strMsg);
        }
    private:
        XInt m_Index;  ///<Խ����±�
        XInt m_Length; ///<��Խ���������±�
    };
    ///ֵΪ���쳣��
    class XEIsZero : public EException
    {
    public:
        XEIsZero()
            :EException(MESSAGE_IS_ZERO)
        {}
    };
    ///ֵС�����쳣��
    class XELessThanZero : public EException
    {
    public:
        XELessThanZero()
            :EException(MESSAGE_LESS_THAN_ZERO)
        {}
    };
    ///ֵ�������쳣��
    class XEGreatherThanZero : public EException
    {
    public:
        XEGreatherThanZero()
            :EException(MESSAGE_GREATER_THAN_ZERO)
        {}
    };
    ///�������쳣��
    class XENotExists : public EException
    {
    public:
        XENotExists()
            :EException(MESSAGE_NOT_EXISTS)
        {}
    };

    //============================================================================
    /**
     * ����һ�������׳�ʱ���쳣����
     * @par sample
     * @code
     * XEXDateTimeError Example;
     * cout<<Example.getMsg()<<endl;
     * @endcode
     * @author ף����
     * @version 4.0
     * @date 2008-04-06
     */
    class EDateTimeError : public EException
    {
    public:
        ///���캯��
        /**
         * @param paramInvalidation ��Ч��ԭ��
         * @param paramInvalidValue ��Ч��ֵ
         * @param iHelpContext ����ID
         */
        EDateTimeError(EnumDateTimeError paramInvalidation = E_DATETIME_INVALIDATION_DATETIME, XInt paramInvalidValue = 0)
            :m_Invalidation(paramInvalidation), m_InvalidValue(paramInvalidValue)
        {
            ResetErrorMsg();
        }
        ///ȡ��Ч��ֵ
        XInt getInvalidValue() const
        {
            return m_InvalidValue;
        }
        ///ȡ��Ч��ԭ��
        /**
         * @return ������Ч��ԭ��
         */
        EnumDateTimeError getInvalidation() const
        {
            return m_Invalidation;
        }
        ///������Ч����
        /**
         * @param paramInvalidation ��Ч��ԭ��
         * @param paramInvalidValue ��Ч��ֵ
         */
        void SetInvalidation(EnumDateTimeError paramInvalidation, XInt paramInvalidValue = 0)
        {
            m_Invalidation = paramInvalidation;
            m_InvalidValue = paramInvalidValue;
            ResetErrorMsg();
        }
    private:
        ///���������Ϣ
        void ResetErrorMsg()
        {
            XAnsiString strMsg;
            //strMsg.ensureCapacity(64);

            //���ݲ�ͬԭ�����ɴ�����Ϣ
            switch(m_Invalidation)
            {
            case E_DATETIME_INVALIDATION_DATE:
                strMsg << "Invalidation Date";
                break;
            case E_DATETIME_INVALIDATION_TIME:
                strMsg << "Invalidation Time";
                break;
            case E_DATETIME_INVALIDATION_YEAR:
				strMsg = "Invalidation Year:";
				strMsg += m_InvalidValue;
				break;
			case E_DATETIME_INVALIDATION_MONTH:
				strMsg = "Invalidation Month:";
				strMsg += m_InvalidValue;
				break;
			case E_DATETIME_INVALIDATION_DAY:
				strMsg = "Invalidation Day:" ;
				strMsg += m_InvalidValue;
				break;
			case E_DATETIME_INVALIDATION_HOUR:
				strMsg = "Invalidation Hour:";
				strMsg += m_InvalidValue;
				break;
			case E_DATETIME_INVALIDATION_MINUTE:
				strMsg = "Invalidation Minute:";
				strMsg += m_InvalidValue;
				break;
			case E_DATETIME_INVALIDATION_SECOND:
				strMsg = "Invalidation Second:";
				strMsg += m_InvalidValue;
				break;
			case E_DATETIME_INVALIDATION_MILLIS:
				strMsg = "Invalidation Millis:";
				strMsg += m_InvalidValue;
				break;
			case E_DATETIME_INVALIDATION_DATETIME:
				strMsg = "Invalidation DateTime";
				break;
			case E_DATETIME_INVALIDATION_DAYS:
				strMsg = "Invalidation Days:";
				strMsg += m_InvalidValue;
				break;
			case E_DATETIME_OUT:
				strMsg = "Out of DateTime";
				break;
			case E_DATETIME_DAYS_OUT:
				strMsg = "Out of Days";
				strMsg += m_InvalidValue;
				break;
			case E_DATETIME_TIMES_OUT:
				strMsg = "Out of Times";
				strMsg += m_InvalidValue;
				break;
			default:
				strMsg = "Unknow DateTime Error:";
				strMsg += m_InvalidValue ;
				break;
			}
			setMessage(strMsg); //���ɴ�����Ϣ
		}
	private:
		EnumDateTimeError m_Invalidation;       ///<��Ч��ԭ��
        XInt m_InvalidValue;                ///<��Ч��ֵ
    };

    //����ǰ������
    XLong GetNowDateTime();
    void  GetSystemDateTime(SSystemDateTime & paramST);
    void  SetSystemDateTime(const SSystemDateTime & paramST);
    void  DaysToDate(XInt paramDays, XInt &paramYear, XInt &paramMonth, XInt & paramDay);
    void  DaysToDate(XInt paramDays, SDate & paramDate);
    XInt  CalcMonthDays(XInt paramYear, XInt paramMonth, bool bCheck);
    XInt  CalcDays(XInt paramYear, XInt paramMonth, XInt paramDay);
    XBool IsRawYear(XInt paramYear);
    XInt  CalcMillisByTime(XInt paramHour,XInt paramMinute, XInt paramSecond,XInt paramMillis);
    XLong CalcMillis(XInt paramYear, XInt paramMonth, XInt paramDay, XInt paramHour, XInt paramMinute, XInt paramSecond, XInt paramMillis);
    void  MillisToTime(XInt paramMillisCount, XInt &paramHour, XInt &paramMinute, XInt &paramSecond, XInt &paramMillis);
    void  MillisToTime(XInt paramMillisCount, STime & paramTime);
    void  DateTimeMillisToDateTime(XLong paramMillisCount, XInt &paramYear, XInt & paramMonth, XInt & paramDay,XInt & paramHour, XInt & paramMinute, XInt & paramSecond, XInt & paramMillis);

    namespace detail
    {
        //������ƿռ�ĺ�������������������ר�õĺ������벻Ҫֱ��ʹ��������ĺ���
        ///ȡ��ǰʱ�������
        inline XLong GetNowDateTime()
        {
				SYSTEMTIME st;
				GetSystemTime(&st);
				XLong lngNow = CalcMillis(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
				TIME_ZONE_INFORMATION tz;
				if(GetTimeZoneInformation(&tz) == TIME_ZONE_ID_STANDARD )
					lngNow -= (tz.StandardBias * MILLIS_PRE_MINUTE);
				else
					lngNow -= (-480*MILLIS_PRE_MINUTE);
				return lngNow;
		}



        //----------------------------------------------------------------------------
        /**
        * ȡϵͳʱ��
        * @param [out] paramST ���ڱ���ȡ�õ�����ʱ��
        */
        inline void GetSystemDateTime(SSystemDateTime & paramST)
        {
			SYSTEMTIME st;
			GetSystemTime(&st);
			paramST.Year = st.wYear;
			paramST.Month = st.wMonth;
			paramST.Day = st.wDay;
			paramST.WeekDay = st.wDayOfWeek;
			paramST.Hour = st.wHour;
			paramST.Minute = st.wMinute;
			paramST.Second = st.wSecond;
			paramST.Milliseconds = st.wMilliseconds;
			paramST.Zone = TIME_ZONE_CHINA; //Ĭ��ʱ��Ϊ������
			TIME_ZONE_INFORMATION tz;
			if(GetTimeZoneInformation(&tz) == TIME_ZONE_ID_STANDARD )
			{
				paramST.Zone = (XShort)tz.StandardBias;
			}
		}

        //----------------------------------------------------------------------------
        /**
            ���õ�ǰϵͳʱ��,�����Linux��,û��RootȨ��,��������ʧ��,�Ѿ���������
            @param [in] paramST ��ǰҪ���õ�ʱ��
        */
        inline void SetSystemDateTime(const SSystemDateTime & paramST)
        {
			SYSTEMTIME st;
			st.wYear = (XWord)paramST.Year;
			st.wMonth = (XWord)paramST.Month;
			st.wDay =(XWord) paramST.Day;
			st.wDayOfWeek = (XWord)paramST.WeekDay;
			st.wHour = (XWord)paramST.Hour;
			st.wMinute = (XWord)paramST.Minute;
			st.wSecond = (XWord)paramST.Second;
			st.wMilliseconds = (XWord)paramST.Milliseconds;
			SetSystemTime(&st);
		}

        //----------------------------------------------------------------------------
        /**
        * ����ָ�����µ�����
        * @param [in] paramYear ָ������ݣ���Ч�������[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮��
        * @param [in] paramMonth ָ�����·ݣ���Ч���·���[1,12]֮��
        * @param [in] paramCheck ������±�־,
        *     - true ��ʾҪ���paramYear��paramMonth�Ƿ���Ч
        *     - false ��ʾ����Ҫ���paramYear��paramMonth�Ƿ���Ч
        * @return ���ؼ������ָ���·ݵ�����
        * @exception XEDateTimeError �����ݡ��·���Ч�����׳��쳣
        */
        inline XInt CalcMonthDays(XInt paramYear, XInt paramMonth, bool paramCheck)
		{
            XInt iRet;
            if( paramCheck ) //���Ҫ�������
            {
                if( paramYear < MIN_YEAR_IN_DATETIME || paramYear > MAX_YEAR_IN_DATETIME ) throw EDateTimeError(E_DATETIME_INVALIDATION_YEAR,paramYear);
                if( paramMonth < MIN_MONTH_IN_YEAR || paramMonth > MAX_MONTH_IN_YEAR ) throw EDateTimeError(E_DATETIME_INVALIDATION_MONTH,paramMonth);
            }

            static XInt MonthDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

            if( paramMonth == 2 )
            {
                if( IsRawYear(paramYear) ) iRet =  MonthDays[1]+1;
                else iRet = MonthDays[1];
            }
            else iRet =  MonthDays[paramMonth-1];
            return iRet;
        }
        //---------------------------------------------------------------------
        /**
        * �����Ԫ��1��1�տ�ʼ������
        * @param [in] paramYear ָ������ݣ���Ч�������[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮��
        * @param [in] paramMonth ָ�����·ݣ���Ч���·���[1,12]֮��
        * @param [in] paramDay ָ�������ڣ���Ч��������[1,CalcMonthDays]֮��
        * @return ����ָ�����ڴ�Ԫ��1��1�տ�ʼ������
        * @exception XEDateTimeError �����ݡ��·ݡ�������Ч�����׳��쳣
        */
        inline XInt CalcDays(XInt paramYear, XInt paramMonth, XInt paramDay)
		{
            //������
            if( paramYear < MIN_YEAR_IN_DATETIME || paramYear > MAX_YEAR_IN_DATETIME ) throw EDateTimeError(E_DATETIME_INVALIDATION_YEAR,paramYear);
            //����·�
            if( paramMonth < MIN_MONTH_IN_YEAR || paramMonth > MAX_MONTH_IN_YEAR ) throw EDateTimeError(E_DATETIME_INVALIDATION_MONTH,paramMonth);
            //�������
            XInt aMonthDays = CalcMonthDays(paramYear, paramMonth, false);

            if( paramDay < MIN_DAY_IN_MONTH || paramDay > aMonthDays ) throw EDateTimeError(E_DATETIME_INVALIDATION_DAY,paramDay);

            XInt iDays = 0;

            for(XInt i=1; i<paramMonth; i++) iDays += CalcMonthDays(paramYear, i, false);

            paramYear --;
            iDays += ( (paramYear*365) + (paramYear/4) - (paramYear/100) + (paramYear/400)); //�������������
            iDays += paramDay;                                                   //���ϵ�ǰ�µ�����
            return iDays;
        }

        //----------------------------------------------------------------------------
        /**
            ������ת����������
            @param [in] paramDays Ҫת��������
            @param [out] paramYear ת��������
            @param [out] paramMonth ת������·�
            @param [out] aday ת���������
        */
        inline void DaysToDate(XInt paramDays,XInt &paramYear,XInt &paramMonth,XInt & paramDay)
		{
            if( paramDays < MIN_DAYS_IN_DATETIME || paramDays > MAX_DAYS_IN_DATETIME) throw EDateTimeError(E_DATETIME_DAYS_OUT,paramDays);
            XInt N400 = paramDays / 146097; //400�������
            XInt D = paramDays % 146097;
            XInt N100 = D / 36524;      //100�������
            D %= 36524;
            XInt N4 = D / 1461;         //ÿ���������
            D %= 1461;
            XInt N = D / 365;           //��������
            D %= 365;
            XInt NYear = N400 * 400 + N100 * 100 + N4 * 4 + N;  //���������
            XInt TDays = 0;

            if( D > 0)
            {
                NYear ++;
                paramYear = NYear;
                for(XInt i=1; i<13; i++)
                {
                    TDays += CalcMonthDays(NYear, i, true);
                    if( D <= TDays )
                    {
                        paramMonth = i;
                        paramDay = D - TDays + CalcMonthDays(NYear, i, true);
                        break;
                    }
                }
            }
            else
            {
                paramYear = NYear;
                paramMonth = 12;
                paramDay = (CalcDays(NYear,12,31) == paramDays)?31:30;
            }
        }

        //---------------------------------------------------------------------
        //datetime˽�еĺ���,�벻Ҫ������ļ�֮��ʹ��
        ///����Ƿ�Ϊ���ڵķָ���
        template<class T>
        inline bool __isDateSplit(T paramV)
        {
            return ( paramV == '-' || paramV =='\\' || paramV =='/' );
        }
        //---------------------------------------------------------------------
        ///����Ƿ�Ϊ���ڵĽ����ַ�
        template<class T>
        inline bool __isEnd(T paramV)
        {
            return ( paramV == 0 || paramV == ' ');
        }
        //---------------------------------------------------------------------
        /**
            ��������ʱ���������ת��Ϊ�ַ���.
            �������������XDateTime.cpp����ļ���,������ָ����Ĵ�,���Ҳ��Ὣ�����ַ���Ϊ0.
            ������������ر���Ż�
            @param [in] paramBuffer ָ���Ļ�����
            @param [in] paramValue Ҫת��������
            @param [in] paramWidth ת�����ַ����Ŀ�ȣ����㲹��
         */
        template<class T>
        static void __XX__FastToDateTimeString(T * paramBuffer, XInt paramValue, XInt paramWidth)
        {
            paramBuffer += paramWidth;

            while(paramValue > 0 && paramWidth > 0)
            {
                *--paramBuffer = (T)(paramValue % 10 + '0');
                paramValue /= 10;
                paramWidth --;
            }

            while( paramWidth > 0 )
            {
                * --paramBuffer = '0';
                paramWidth --;
            }
        }
        //---------------------------------------------------------------------
        /**
            ��������ʱ������ַ���ת��Ϊ�����ĺ���.
            �������������XDateTime.cpp����ļ���,��ת��ָ����ȵ��ַ���.
            ������������ر���Ż�
            @param [in] paramBuffer ָ���Ļ�����
            @param [in] paramWidth ָ���������Ŀ��,��ֵ��[1,4]֮��
            @return ����ת����Ľ��
         */
        template<class T>
        inline XInt __XX__FastStringToNumber(const T * paramBuffer, XInt paramWidth)
        {
            XInt iRet;
            if( paramWidth == 2) iRet = (*paramBuffer - '0') * 10 + (paramBuffer[1] - '0');
            else if( paramWidth == 3 ) iRet = (*paramBuffer - '0') * 100 + (paramBuffer[1] - '0') * 10 + (paramBuffer[2] - '0');
            else if( paramWidth == 4) iRet = (*paramBuffer - '0') * 1000 + (paramBuffer[1] - '0') * 100 + (paramBuffer[2] - '0')*10 + (paramBuffer[3]-'0');
            else if( paramWidth == 1) iRet = *paramBuffer - '0';
            else iRet = -1;
            return iRet;
        }
        //---------------------------------------------------------------------
        /**
            ���ٽ���ʱ��ĺ���,������HH:MM:SS.mmm��HH:MM��HH:MM:SS��ʽ��ʱ��
            @param [in] paramTime ָ���Ļ�����
            @param [out] paramTimeRet ��Ž����Ľ��
            @return ���ش�����Ϣ
                - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
                - X_DATETIME_ERROR_INVALID_TIME_FORMAT ��ʾ������ʧ��,����Ч��ʱ���ʽ
         */
        template<class T>
        static EnumParseDateTimeErrorCode __XX__FastParseTime(const T * paramTime, STime & paramTimeRet)
        {
            XInt iWidth = 0;
            const T * p  = paramTime;
            for(;;) //����Сʱ
            {
                T ch = *p++;
                if( string_utils::isDigit(ch) )
                {
                    iWidth ++;
                    if( iWidth > 2) return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( ch == ':' )
                {
                    if( iWidth > 0 && iWidth <= 2)
                    {
                        paramTimeRet.Hour = __XX__FastStringToNumber(paramTime, iWidth);
                        paramTime = p;
                        iWidth = 0;
                        break;
                    }
                    return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
            }
            for(;;) //�������
            {
                T ch = *p++;
                if( string_utils::isDigit(ch) )
                {
                    iWidth ++;
                    if( iWidth > 2) return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( ch == ':' )
                {
                    if( iWidth > 0 && iWidth <= 2)
                    {
                        paramTimeRet.Minute = __XX__FastStringToNumber(paramTime, iWidth);
                        paramTime = p;
                        iWidth = 0;
                        break;
                    }
                    return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( __isEnd(ch) ) //���û������,��ǰ������
                {
                    if( iWidth > 0 && iWidth <= 2)
                    {
                        paramTimeRet.Minute = __XX__FastStringToNumber(paramTime, iWidth);
                        paramTimeRet.Second = paramTimeRet.Millis = 0;
                        return X_DATETIME_ERROR_OK;
                    }
                    return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
            }
            for(;;) //������
            {
                T ch = *p++;
                if( string_utils::isDigit(ch) )
                {
                    iWidth ++;
                    if( iWidth > 2) return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( ch == '.' )
                {
                    if( iWidth > 0 && iWidth <= 2)
                    {
                        paramTimeRet.Second = __XX__FastStringToNumber(paramTime, iWidth);
                        paramTime = p;
                        iWidth = 0;
                        break;
                    }
                    return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( __isEnd(ch) ) //���û�к�����
                {
                    if( iWidth > 0 && iWidth <= 2)
                    {
                        paramTimeRet.Second = __XX__FastStringToNumber(paramTime, iWidth);
                        paramTimeRet.Millis = 0;
                        return X_DATETIME_ERROR_OK;
                    }
                    return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
            }
            for(;;) //�������
            {
                T ch = *p++;
                if( string_utils::isDigit(ch) )
                {
                    iWidth ++;
                    if( iWidth > 3) return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( __isEnd(ch) ) //���û�к�����
                {
                    if( iWidth > 0 && iWidth <= 3)
                    {
                        paramTimeRet.Millis = __XX__FastStringToNumber(paramTime, iWidth);
                        return X_DATETIME_ERROR_OK;
                    }
                    return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
            }
        }
        //--------------------------------------------------------------------------------
        /**
            ���ٽ������ڵĺ���,������YYYY-MM-DD,YYYY/MM/DD,YYYY\MM\DD�ȸ�ʽ������
            @param [in] paramDate ָ�������ڴ�
            @param [out] paramDateEnd �������ڴ���ָ���λ��
            @param [out] paramDateRet ��Ž����Ľ��
            @return ���ش�����Ϣ
                - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
                - X_DATETIME_ERROR_INVALID_DATE_FORMAT ��ʾ������ʧ��,����Ч�����ڸ�ʽ
         */
        template<class T>
        static EnumParseDateTimeErrorCode __XX__FastParseDate(const T * paramDate, const T * & paramDateEnd, SDate & paramDateRet)
        {
            XInt iWidth = 0;
            const T * p = paramDate;
            T chSplit;
            for(;;) //�������
            {
                T ch = *p++;
                if( string_utils::isDigit(ch) )
                {
                    iWidth ++;
                    if( iWidth > 4) return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( __isDateSplit(ch) )
                {
                    if( iWidth > 0 && iWidth <= 4)
                    {
                        paramDateRet.Year = __XX__FastStringToNumber(paramDate, iWidth);
                        chSplit = ch;
                        paramDate = p;
                        iWidth = 0;
                        break;
                    }
                    return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
                }
                else return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
            }
            for(;;) //�����·�
            {
                T ch = *p++;
                if( string_utils::isDigit(ch) )
                {
                    iWidth ++;
                    if( iWidth > 2) return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( ch == chSplit )
                {
                    if( iWidth > 0 && iWidth <= 2)
                    {
                        paramDateRet.Month = __XX__FastStringToNumber(paramDate, iWidth);
                        paramDate = p;
                        iWidth = 0;
                        break;
                    }
                    return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
                }
                else return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
            }
            for(;;) //��������
            {
                T ch = *p++;
                if( string_utils::isDigit(ch) )
                {
					iWidth ++;
                    if( iWidth > 2) return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( __isEnd(ch) )
                {
                    if( iWidth > 0 && iWidth <= 2)
                    {
                        paramDateRet.Day = __XX__FastStringToNumber(paramDate, iWidth);
                        paramDateEnd = p;
                        return X_DATETIME_ERROR_OK; //���ؽ��
                    }
                    return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
                }
                else return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
            }
		}
	}

	//============================================================================
	//ȫ�ֺ���
	//----------------------------------------------------------------------------
	///ȡ��ǰʱ�������
	/**
	 * ȡ��ǰ�ĺ�����
	 * @return ���ص�ǰ����ʱ��ĺ�����
	 */
	inline XLong GetNowDateTime()
	{
		return detail::GetNowDateTime();
	}



	//----------------------------------------------------------------------------
	///ȡϵͳʱ��
	inline void GetSystemDateTime(SSystemDateTime & paramST)
    {
        detail::GetSystemDateTime(paramST);
    }
    //----------------------------------------------------------------------------
    ///����ϵͳʱ��
    inline void SetSystemDateTime(const SSystemDateTime & paramST)
    {
        detail::SetSystemDateTime(paramST);
    }
    //----------------------------------------------------------------------------
    ///������ת����������
    /**
        ������ת����������
        @param [in] paramDays Ҫת��������
        @param [out] paramYear ת��������
        @param [out] paramMonth ת������·�
        @param [out] paramDay ת���������
        @exception XEDateTimeError ���ڳ�����Ч��Χ�����׳��쳣
    */
    inline void DaysToDate(XInt paramDays, XInt &paramYear, XInt &paramMonth, XInt & paramDay)
    {
        detail::DaysToDate(paramDays, paramYear, paramMonth, paramDay);
    }
    //----------------------------------------------------------------------------
    ///������ת��������
    /**
        ������ת��������
        @param [in] paramDays Ҫת��������
        @param [out] paramDate ת���������
        @exception XEDateTimeError ���ڳ�����Ч��Χ�����׳��쳣
    */
    inline void DaysToDate(XInt paramDays, SDate & paramDate)
    {
        DaysToDate(paramDays, paramDate.Year, paramDate.Month, paramDate.Day);
    }
    //----------------------------------------------------------------------------
    ///����ָ�����µ�����
    /**
     * ����ָ�����µ�����
     * @param [in] paramYear ָ������ݣ���Ч�������[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮�䣬��ֵ��[1,9999]֮��
     * @param [in] paramMonth ָ�����·ݣ���Ч���·���[1,12]֮��
     * @param [in] bCheck ������±�־,
     *     - true ��ʾҪ���paramYear��paramMonth�Ƿ���Ч
     *     - false ��ʾ����Ҫ���paramYear��paramMonth�Ƿ���Ч
     * @return ���ؼ������ָ���·ݵ�����
     * @exception XEDateTimeError �����ݡ��·���Ч�����׳��쳣
     */
    inline XInt CalcMonthDays(XInt paramYear, XInt paramMonth, bool bCheck = true)
    {
        return detail::CalcMonthDays(paramYear,paramMonth,bCheck);
    }
    //----------------------------------------------------------------------------
    ///�����Ԫ��1��1�տ�ʼ������
    /**
     * �����Ԫ��1��1�տ�ʼ������
     * @param [in] paramYear ָ������ݣ���Ч�������[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮�䣬��ֵ��[1,9999]֮��
     * @param [in] paramMonth ָ�����·ݣ���Ч���·���[1,12]֮��
     * @param [in] paramDay ָ�������ڣ���Ч��������[1,CalcMonthDays]֮��
     * @return ����ָ�����ڴ�����1��1�տ�ʼ������
     * @exception XEDateTimeError �����ݡ��·ݡ�������Ч�����׳��쳣
     */
    inline XInt CalcDays(XInt paramYear, XInt paramMonth, XInt paramDay)
    {
        return detail::CalcDays(paramYear,paramMonth,paramDay);
    }
    //----------------------------------------------------------------------------
    ///�ж��Ƿ�������
    /**
     * �ж��Ƿ�������
     * @param [in] paramYear ��������ݣ���Ч�������[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮�䣬��ֵ��[1,9999]֮��
     * @return �����жϽ��
     *   - true ��ʾ������
     *   - false ��ʾ��������
     * @exception XEXDateTimeError ��������Ч�����׳��쳣
     */
	inline XBool IsRawYear(XInt paramYear)
	{
        if( paramYear < MIN_YEAR_IN_DATETIME || paramYear > MAX_YEAR_IN_DATETIME ) throw EDateTimeError(E_DATETIME_INVALIDATION_YEAR,paramYear);
        XBool bFlag;
        if( paramYear % 4 == 0 )
        {
            if( paramYear % 100 == 0 )
            {
                if( paramYear % 400 == 0 ) bFlag = true;
                else bFlag = false;
            }
            else bFlag = true;
        }
        else bFlag = false;
        return bFlag;
    }
    //----------------------------------------------------------------------------
    ///����ָ��ʱ��ĺ�����
    /**
     * ����ָ��ʱ��ĺ�����
     * @param [in] paramHour Сʱ����ֵ��[0,23]֮��
     * @param [in] paramMinute ���ӣ���ֵ��[0,59]֮��
     * @param [in] paramSecond �룬��ֵ��[0,59]֮��
     * @param [in] paramMillis ���룬��ֵ��[0,999]֮��
     * @return ���ؼ���������ܺ�����
     * @exception XEXDateTimeError ����������׳��쳣��
     */
    inline XInt CalcMillisByTime(XInt paramHour,XInt paramMinute = 0, XInt paramSecond = 0,XInt paramMillis = 0)
	{
        if( paramHour < 0 || paramHour > 23 ) throw EDateTimeError(E_DATETIME_INVALIDATION_HOUR, paramHour);
        if( paramMinute < 0 || paramMinute > 59 ) throw EDateTimeError(E_DATETIME_INVALIDATION_MINUTE, paramMinute);
        if( paramSecond < 0 || paramSecond > 59 ) throw EDateTimeError(E_DATETIME_INVALIDATION_SECOND, paramSecond);
        if( paramMillis < 0 || paramMillis > 999 ) throw EDateTimeError(E_DATETIME_INVALIDATION_MILLIS, paramMillis);
        return paramHour * MILLIS_PRE_HOUR + paramMinute * MILLIS_PRE_MINUTE + paramSecond * MILLIS_PRE_SECOND + paramMillis;
    }
    //----------------------------------------------------------------------------
    ///����ָ������ʱ��ĺ�����
    /**
     * ����ָ��ʱ��ĺ�����
     * @param [in] paramYear ��ݣ���ֵ��[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮��,��ֵ��[1,9999]֮��
     * @param [in] paramMonth �·ݣ���ֵ��[1,12]֮��
     * @param [in] paramDay ���ڣ���ֵ��[1,31]֮�䣬���廹Ҫ�Ӳ�ͬ���·ݺ���������
     * @param [in] paramHour Сʱ����ֵ��[0,23]֮��
     * @param [in] paramMinute ���ӣ���ֵ��[0,59]֮��
     * @param [in] paramSecond �룬��ֵ��[0,59]֮��
     * @param [in] paramMillis ���룬��ֵ��[0,999]֮��
     * @return ���ؼ���������ܺ�����
     * @exception XEXDateTimeError ����������׳��쳣��
     */
    inline XLong CalcMillis(XInt paramYear, XInt paramMonth, XInt paramDay,
        XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0)
    {
        return CalcDays(paramYear, paramMonth, paramDay) * MILLIS_PRE_DAY64
            + CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis);
    }
    //----------------------------------------------------------------------------
    ///��������ת��Ϊʱ���֡��롢����
    /**
     * ��������ת��Ϊʱ���֡��롢����
     * @param [in] paramMillisCount �ܺ���������ֵ�ķ�Χ��[0,MILLIS_PRE_DAY)
     * @param [out] paramHour ���ؼ��������Сʱ
     * @param [out] paramMinute ���ؼ�������ķ���
     * @param [out] paramSecond ���ؼ����������
     * @param [out] paramMillis ���ؼ�������ĺ���
     * @exception XEXDateTimeError ���������Ч�ĺ��뷶Χ�����׳��쳣
     */
    inline void MillisToTime(XInt paramMillisCount, XInt &paramHour, XInt &paramMinute, XInt &paramSecond, XInt &paramMillis)
	{
        if( paramMillisCount < 0 || paramMillisCount >= MILLIS_PRE_DAY) throw EDateTimeError(E_DATETIME_TIMES_OUT,paramMillisCount);

        paramMillis = paramMillisCount % MILLIS_PRE_SECOND;
        paramMillisCount /= MILLIS_PRE_SECOND;

        paramSecond = paramMillisCount % 60;
        paramMillisCount /= 60;

        paramMinute = paramMillisCount % 60;

        paramHour = paramMillisCount / 60;
    }
    //----------------------------------------------------------------------------
    ///��������ת��Ϊʱ�乹����STime
    /**
     * ��������ת��Ϊʱ�乹����STime
     * @param [in] paramMillisCount �ܺ���������ֵ�ķ�Χ��[0,MILLIS_PRE_DAY)
     * @param [out] paramTime ���ؼ��������ʱ��
     * @exception XEXDateTimeError ���������Ч�ĺ��뷶Χ�����׳��쳣
     */
    inline void MillisToTime(XInt paramMillisCount, STime & paramTime)
    {
        MillisToTime(paramMillisCount, paramTime.Hour, paramTime.Minute, paramTime.Second, paramTime.Millis);
    }
    //----------------------------------------------------------------------------
    ///������ʱ��ת��Ϊ�ꡢ�¡��ա�ʱ���֡��롢����
    /**
     * @param [in] paramMillisCount ����ʱ��ĺ�����
     * @param [out] paramYear ���ؼ�������
     * @param [out] paramMonth ���ؼ�������·�
     * @param [out] paramDay ���ؼ����������
     * @param [out] paramHour ���ؼ��������Сʱ
     * @param [out] paramMinute ���ؼ�������ķ���
     * @param [out] paramSecond ���ؼ����������
     * @param [out] paramMillis ���ؼ�������ĺ���
     * @exception XEXDateTimeError ���������Ч�ĺ��뷶Χ�����׳��쳣
     */
    inline void DateTimeMillisToDateTime(XLong paramMillisCount, XInt &paramYear, XInt & paramMonth, XInt & paramDay,
        XInt & paramHour, XInt & paramMinute, XInt & paramSecond, XInt & paramMillis)
    {

		if( paramMillisCount < MIN_MILLIS || paramMillisCount >= MAX_MILLIS ) throw EDateTimeError(E_DATETIME_OUT);

        DaysToDate(XInt(paramMillisCount / MILLIS_PRE_DAY64), paramYear, paramMonth, paramDay);

        MillisToTime(XInt(paramMillisCount % MILLIS_PRE_DAY64), paramHour, paramMinute, paramSecond, paramMillis);
    }


    //---------------------------------------------------------------------
    /**
        ��������ʱ��
        @param [in] paramDateTime ����ʱ�䴮,������YYYY-MM-DD HH:MM:SS.mmm �� YYYY/MM/DD HH:MM:SS.mmm ��ʽ������ʱ�䴮
        @param [out] paramDate ��������������: YYYY, MM, DD
        @param [out] paramTime ����������ʱ��: HH, MM, SS, mmm
        @return ���ؽ�����
            - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
            - ����ֵ ��ʾ����ʧ��
     */
    template<class T>
    static EnumParseDateTimeErrorCode ParseDateTime(const T * paramDateTime, SDate & paramDate, STime & paramTime)
    {
        SDate tmpDate;
        STime tmpTime;
        const T * TimeStart;
        for(;;) //ȥ����ǰ�ո�
        {
            T ch = *paramDateTime;
            if( string_utils::isSpace(ch) ) paramDateTime++;
            else if( string_utils::isZero(ch) ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
            else break;
        }
        //��������
        if( detail::__XX__FastParseDate(paramDateTime, TimeStart, tmpDate) != X_DATETIME_ERROR_OK ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
        //�������
        //������
        if( tmpDate.Year < MIN_YEAR_IN_DATETIME || tmpDate.Year > MAX_YEAR_IN_DATETIME ) return X_DATETIME_ERROR_INVALID_YEAR;
        //����·�
        if( tmpDate.Month < MIN_MONTH_IN_YEAR || tmpDate.Month > MAX_MONTH_IN_YEAR ) return X_DATETIME_ERROR_INVALID_MONTH;
        //�������
        if( tmpDate.Day < MIN_DAY_IN_MONTH || tmpDate.Day > CalcMonthDays(tmpDate.Year,tmpDate.Month) ) return X_DATETIME_ERROR_INVALID_DAY;
        //����ʱ��
        if( detail::__XX__FastParseTime(TimeStart,tmpTime) != X_DATETIME_ERROR_OK ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
        //���Сʱ
        if( tmpTime.Hour > 23 ) return X_DATETIME_ERROR_INVALID_HOUR;
        //������
        if( tmpTime.Minute > 59 ) return X_DATETIME_ERROR_INVALID_MINUTE;
        //�����
        if( tmpTime.Second > 59 ) return X_DATETIME_ERROR_INVALID_SECOND;
        //������
        if( tmpTime.Millis > 999) return X_DATETIME_ERROR_INVALID_MILLIS;
        paramDate = tmpDate;
        paramTime = tmpTime;
        return X_DATETIME_ERROR_OK;
    }
    //---------------------------------------------------------------------
    /**
        ��������
        @param [in] paramDate ����ʱ�䴮,������YYYY-MM-DD HH:MM:SS.mmm ��YYYY-MM-DD �� YYYY/MM/DD ��ʽ������ʱ�䴮
        @param [out] paramDateRet ��������������: YYYY, MM, DD
        @return ���ؽ�����
            - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
            - ����ֵ ��ʾ����ʧ��
     */
    template<class T>
    static EnumParseDateTimeErrorCode ParseDate(const T * paramDate, SDate & paramDateRet)
    {
        SDate tmpDate;
        const T * TimeStart;
        for(;;) //ȥ����ǰ�ո�
        {
            T ch = *paramDate;
            if( string_utils::isSpace(ch) ) paramDate++;
            else if( string_utils::isZero(ch) ) return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
            else break;
        }
        //��������
        if( detail::__XX__FastParseDate(paramDate, TimeStart, tmpDate) != X_DATETIME_ERROR_OK ) return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
        //�������
        //������
        if( tmpDate.Year < MIN_YEAR_IN_DATETIME || tmpDate.Year > MAX_YEAR_IN_DATETIME ) return X_DATETIME_ERROR_INVALID_YEAR;
        //����·�
        if( tmpDate.Month < MIN_MONTH_IN_YEAR || tmpDate.Month > MAX_MONTH_IN_YEAR ) return X_DATETIME_ERROR_INVALID_MONTH;
        //�������
        if( tmpDate.Day < MIN_DAY_IN_MONTH || tmpDate.Day > CalcMonthDays(tmpDate.Year, tmpDate.Month) ) return X_DATETIME_ERROR_INVALID_DAY;
        paramDateRet = tmpDate;
        return X_DATETIME_ERROR_OK;
    }
    //---------------------------------------------------------------------
    /**
        ����ʱ��
        @param [in] paramTime ʱ�䴮,������HH:MM:SS.mmm ��HH:MM:SS �� HH:MM��ʽ��ʱ�䴮
        @param [out] paramTimeRet ����������ʱ��: HH, MM, SS, mmm
        @return ���ؽ�����
            - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
            - ����ֵ ��ʾ����ʧ��
     */
    template<class T>
    static EnumParseDateTimeErrorCode ParseTime(const T * paramTime, STime & paramTimeRet)
    {
        STime tmpTime;
        for(;;) //ȥ����ǰ�ո�
        {
            T ch = *paramTime;
            if( string_utils::isSpace(ch) ) paramTime++;
            else if( string_utils::isZero(ch) ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
            else break;
        }
        if( detail::__XX__FastParseTime(paramTime, tmpTime) != X_DATETIME_ERROR_OK ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
        //���Сʱ
        if( tmpTime.Hour > 23 ) return X_DATETIME_ERROR_INVALID_HOUR;
        //������
        if( tmpTime.Minute > 59 ) return X_DATETIME_ERROR_INVALID_MINUTE;
        //�����
        if( tmpTime.Second > 59 ) return X_DATETIME_ERROR_INVALID_SECOND;
        //������
        if( tmpTime.Millis > 999) return X_DATETIME_ERROR_INVALID_MILLIS;
        paramTimeRet = tmpTime;
        return X_DATETIME_ERROR_OK;
    }
    //---------------------------------------------------------------------
    ///ȡָ�������ĺ�����
    /**
        ���鷽������Days,Hours,Minutes,Seconds�ĸ�������ͨ��������������ǿ���ʹ��
        XDateTime��+=��-=�����Ӻͼ���ָ����ʱ��
        <code>
            XDateTime dt;
            dt.SetNow();
            dt += Days(2);      //���������ʱ��
            dt += Hours(2);     //������Сʱ��ʱ��
            dt += Minutes(2);   //���������ӵ�ʱ��
            dt += Seconds(2);
        <endcode>
     */
    inline XLong Days(XInt paramDays = 1)
    {
        return MILLIS_PRE_DAY64 * paramDays;
    }
    //---------------------------------------------------------------------
    ///ȡָ��Сʱ���ĺ�����
    /**
        ���鷽������Days,Hours,Minutes,Seconds�ĸ�������ͨ��������������ǿ���ʹ��
        XDateTime��+=��-=�����Ӻͼ���ָ����ʱ��
        <code>
            XDateTime dt;
            dt.SetNow();
            dt += Days(2);      //���������ʱ��
            dt += Hours(2);     //������Сʱ��ʱ��
            dt += Minutes(2);   //���������ӵ�ʱ��
            dt += Seconds(2);
        <endcode>
     */
    inline XInt Hours(XInt paramHour = 1)
    {
        return MILLIS_PRE_HOUR * paramHour;
    }
    //---------------------------------------------------------------------
    ///ȡָ���������ĺ�����
    /**
        ���鷽������Days,Hours,Minutes,Seconds�ĸ�������ͨ��������������ǿ���ʹ��
        XDateTime��+=��-=�����Ӻͼ���ָ����ʱ��
        <code>
            XDateTime dt;
            dt.SetNow();
            dt += Days(2);      //��������
            dt += Hours(2);     //������Сʱ��ʱ��
            dt += Minutes(2);   //���������ӵ�ʱ��
            dt += Seconds(2);
        <endcode>
     */
    inline XInt Minutes(XInt paramMinute = 1)
    {
        return MILLIS_PRE_MINUTE * paramMinute;
    }
    //---------------------------------------------------------------------
    ///ȡָ�������ĺ�����
    /**
        ���鷽������Days,Hours,Minutes,Seconds�ĸ�������ͨ��������������ǿ���ʹ��
        XDateTime��+=��-=�����Ӻͼ���ָ����ʱ��
        <code>
            XDateTime dt;
            dt.SetNow();
            dt += Days(2);      //���������ʱ��
            dt += Hours(2);     //������Сʱ��ʱ��
            dt += Minutes(2);   //���������ӵ�ʱ��
            dt += Seconds(2);
        <endcode>
     */
    inline XInt Seconds(XInt paramSecond = 1)
    {
        return MILLIS_PRE_SECOND * paramSecond;
    }

    namespace utc
    {
        ///ȡ��ǰ������־ʱ�������
        inline XLong GetUTCTimeLong()
        {
            return XLong(time(NULL));
		}
        ///ȡ������־�ĺ�����
        inline XLong GetUTCTimeMillisLong()
        {
				SYSTEMTIME st;
				GetSystemTime(&st);
				XLong lngNow = CalcMillis(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
				return lngNow - DAYS_1970_1_1 * MILLIS_PRE_DAY64;
		}

		///ȡʱ����Ϣ
		inline XLong getTimeZone()
		{
			return 8*3600;
			//return timezone;
		}

		inline XLong UTCToLocal(XLong paramUTCSeconds)
		{
			return (paramUTCSeconds + getTimeZone()) * MILLIS_PRE_SECOND + MILLIS_1970_1_1;
		}

		inline XLong LocalToUTC(XLong paramLocalMillis)
		{

			return (paramLocalMillis - MILLIS_1970_1_1) / MILLIS_PRE_SECOND - getTimeZone();
		}

        ///1970����UTC����
        class XUTCTime
        {
        public:
            XUTCTime(XLong a_Time = INVALID_SECOND_UTC)
                :m_Time(a_Time)
            {}
            XUTCTime(const XUTCTime & a_UTCTime)
                :m_Time(a_UTCTime.m_Time)
            {}
            bool isInvalid() const
            {
                return m_Time == INVALID_SECOND_UTC;
            }
            XLong getTime() const
            {
                return m_Time;
            }
            void setTime(const XLong & a_Time)
            {
                m_Time = a_Time;
            }
            void setTimeByNow()
            {
                m_Time = GetUTCTimeLong();
            }
            //��ֵ
            XUTCTime & operator = (const XUTCTime & a_Time)
            {
                m_Time = a_Time.m_Time;
                return *this;
            }
            XUTCTime & operator = (XLong a_Time)
            {
                m_Time = a_Time;
                return *this;
            }
            //�Ƚ���ĺ���
            bool operator == (const XUTCTime & a_Time) const
            {
                return m_Time == a_Time.m_Time;
            }
            bool operator <= (const XUTCTime & a_Time) const
            {
                return m_Time <= a_Time.m_Time;
            }
            bool operator >= (const XUTCTime & a_Time) const
            {
                return m_Time >= a_Time.m_Time;
            }
            bool operator != (const XUTCTime & a_Time) const
            {
                return m_Time != a_Time.m_Time;
            }
            bool operator < (const XUTCTime & a_Time) const
            {
                return m_Time < a_Time.m_Time;
            }
            bool operator > (const XUTCTime & a_Time) const
            {
                return m_Time > a_Time.m_Time;
            }
        private:
            XLong m_Time;
        };

        ///ȡ��ǰ��UTCʱ��
		inline XUTCTime GetUTCTime()
        {
			return XUTCTime(GetUTCTimeLong());
		}

        ///1970����UTC������
        class XUTCTimeMillis
        {
        public:
            XUTCTimeMillis(XLong a_Time = INVALID_MILLIS_UTC)
                :m_Time(a_Time)
            {}
            XUTCTimeMillis(const XUTCTimeMillis & a_UTCTimeMillis)
                :m_Time(a_UTCTimeMillis.m_Time)
            {}
            bool isInvalid() const
            {
                return m_Time == INVALID_MILLIS_UTC;
            }
            XLong getTime() const
            {
                return m_Time;
            }
            void setTime(const XLong & a_Time)
            {
                m_Time = a_Time;
            }
            void setTimeByNow()
            {
                m_Time = GetUTCTimeMillisLong();
            }
            //��ֵ
            XUTCTimeMillis & operator = (const XUTCTimeMillis & a_Time)
            {
                m_Time = a_Time.m_Time;
                return *this;
            }
            XUTCTimeMillis & operator = (XLong a_Time)
            {
                m_Time = a_Time;
                return *this;
            }
            //�Ƚ���ĺ���
            bool operator == (const XUTCTimeMillis & a_Time) const
            {
                return m_Time == a_Time.m_Time;
            }
            bool operator <= (const XUTCTimeMillis & a_Time) const
            {
                return m_Time <= a_Time.m_Time;
            }
            bool operator >= (const XUTCTimeMillis & a_Time) const
            {
                return m_Time >= a_Time.m_Time;
            }
            bool operator != (const XUTCTimeMillis & a_Time) const
            {
                return m_Time != a_Time.m_Time;
            }
            bool operator < (const XUTCTimeMillis & a_Time) const
            {
                return m_Time < a_Time.m_Time;
            }
            bool operator > (const XUTCTimeMillis & a_Time) const
            {
                return m_Time > a_Time.m_Time;
            }
        private:
            XLong m_Time;
        };
        ///ȡ��ǰ��UTCʱ�䣬������
        inline XUTCTimeMillis GetUTCTimeMillis()
        {
            return XUTCTimeMillis(GetUTCTimeMillisLong());
        }
    }
    ///����ʱ����
    /**
        һ����ȷ�����������ʱ���ࡣʵ��������Ŀ����Ҫ�Ƿ�������ʱ���ʹ�úͼ��㡣
        �������ʱ�����һ��64λ��������λ���롣SetNowDateTime()������ȡ��ϵͳ�ĵ�ǰ����ʱ�䡣SetDateTimeToOS�����Խ�ϵͳ������ʱ����Ϊ������ʱ�䡣
     */
    template<class T = XAnsiString>
    class XDateTime
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///ָ������ʱ��������Ĺ��캯��
        /**
            @param [in] paramDateTime ָ��������ʱ�������
         */
        XDateTime(XLong paramDateTime = DAYS_1970_1_1 * MILLIS_PRE_DAY64 )
            :m_DateTime(paramDateTime)
        {
            RoundDateTime();
        }
        ///Ĭ�Ͽ������캯��
        /**
            @param [in] paramDateTime Ĭ�Ͽ���������ʱ��
         */
        XDateTime(const XDateTime<T> & paramDateTime)
            :m_DateTime(paramDateTime.m_DateTime)
        {}
        ///ָ��ʱ������ʱ��Ĺ��캯��
        /**
         * @param [in] paramYear ��ݣ���ֵ��[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮��
         * @param [in] paramMonth �·ݣ���ֵ��[1,12]֮��
         * @param [in] paramDay ���ڣ���ֵ��[1,31]֮�䣬���廹Ҫ�Ӳ�ͬ���·ݺ���������
         * @param [in] paramHour Сʱ����ֵ��[0,23]֮��
         * @param [in] paramMinute ���ӣ���ֵ��[0,59]֮��
         * @param [in] paramSecond �룬��ֵ��[0,59]֮��
         * @param [in] paramMillis ���룬��ֵ��[0,999]֮��
         * @exception XEXDateTimeError �д������׳��쳣
         */
        XDateTime(XInt paramYear, XInt paramMonth, XInt paramDay,
            XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0 )
            :m_DateTime(CalcMillis(paramYear, paramMonth, paramDay,
                paramHour, paramMinute, paramSecond, paramMillis))
        {
        }
        ///ָ�����ڵĹ��캯��
        XDateTime(const XDate<T> & paramDate);
        ///ָ�����ں�ʱ�乹�캯��
        XDateTime(const XDate<T> & paramDate, const XTime<T> & paramTime);
        ///������ʱ��ת��Ϊ64λ�����ĺ�����
        operator XLong() const { return m_DateTime; }
        ///����ָ����ʱ��,���ڲ���
        /**
         * @param [in] paramHour Сʱ����ֵ��[0,23]֮��
         * @param [in] paramMinute ���ӣ���ֵ��[0,59]֮��
         * @param [in] paramSecond �룬��ֵ��[0,59]֮��
         * @param [in] paramMillis ���룬��ֵ��[0,999]֮��
         * @exception XEXDateTimeError �д������׳��쳣
         */
        void SetTime(XInt paramHour = 0,XInt paramMinute = 0,XInt paramSecond = 0,XInt paramMillis = 0)
        {
            m_DateTime = m_DateTime - m_DateTime % MILLIS_PRE_DAY
                + CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///����ָ����ʱ��,���ڲ���
        /**
         * @param [in] paramTime ��Ч��ʱ��
         * @exception XEXDateTimeError �д������׳��쳣
         */
        void SetTime(const STime & paramTime)
        {
            m_DateTime = m_DateTime - m_DateTime % MILLIS_PRE_DAY
                + CalcMillisByTime(paramTime.Hour, paramTime.Minute, paramTime.Second, paramTime.Millis);
        }
        ///����ָ����ʱ��,���ڲ���
        void SetTime(const XTime<T> & paramTime);
        ///����ָ�������ڣ�ʱ�䲻��
        /**
         * @param [in] paramYear ��ݣ���ֵ��[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮��
         * @param [in] paramMonth �·ݣ���ֵ��[1,12]֮��
         * @param [in] paramDay ���ڣ���ֵ��[1,31]֮�䣬���廹Ҫ�Ӳ�ͬ���·ݺ���������
         * @exception XEXDateTimeError �д������׳��쳣
         */
        void SetDate(XInt paramYear, XInt paramMonth, XInt paramDay)
        {
            m_DateTime = CalcDays(paramYear, paramMonth, paramDay) * MILLIS_PRE_DAY64
                + m_DateTime % MILLIS_PRE_DAY64;
        }
        ///����ָ�������ڣ�ʱ�䲻��
        /**
         * @param [in] paramDate ��Ч������
         * @exception XEXDateTimeError �д������׳��쳣
         */
        void SetDate(const SDate & paramDate)
        {
            m_DateTime = CalcDays(paramDate.Year, paramDate.Month, paramDate.Day) * MILLIS_PRE_DAY64
                + m_DateTime % MILLIS_PRE_DAY64;
        }
        ///����ָ�������ڣ�ʱ�䲻��
        void SetDate(const XDate<T> & paramDate);
        ///����ָ��������ʱ��
        /**
         * @param [in] paramYear ��ݣ���ֵ��[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮��
         * @param [in] paramMonth �·ݣ���ֵ��[1,12]֮��
         * @param [in] paramDay ���ڣ���ֵ��[1,31]֮�䣬���廹Ҫ�Ӳ�ͬ���·ݺ���������
         * @param [in] paramHour Сʱ����ֵ��[0,23]֮��
         * @param [in] paramMinute ���ӣ���ֵ��[0,59]֮��
         * @param [in] paramSecond �룬��ֵ��[0,59]֮��
         * @param [in] paramMillis ���룬��ֵ��[0,999]֮��
         * @exception XEXDateTimeError �д������׳��쳣
         */
        void SetDateTime(XInt paramYear, XInt paramMonth, XInt paramDay, XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0)
        {
            m_DateTime = CalcMillis(paramYear, paramMonth, paramDay, paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///����ָ��������ʱ��
        /**
         * @param [in] paramDate ��Ч������
         * @param [in] paramTime ��Ч��ʱ��
         * @exception XEXDateTimeError �д������׳��쳣
         */
        void SetDateTime(const SDate & paramDate,const STime & paramTime)
        {
            m_DateTime = CalcMillis(paramDate.Year, paramDate.Month, paramDate.Day,
                paramTime.Hour, paramTime.Minute, paramTime.Second, paramTime.Millis);
        }
        ///����ָ��������ʱ��
        void SetDateTime(const XDate<T> & paramDate, const XTime<T> & paramTime);
        ///��������ʱ��Ϊ��ǰʱ��
        void SetNowDateTime()
        {
            m_DateTime = GetNowDateTime();
        }
        ///��ϵͳʱ�䣬��Ϊ��ǰ����ʱ��
        void SetDateTimeToOS() const;
        ///ȡ��ǰ����ʱ��ĺ�����
        XLong GetDateTime() const
        {
            return m_DateTime;
        }
        ///ȡ��ǰ����ʱ���ʱ��
        XTime<T> GetTime() const;
        ///ȡ��ǰ����ʱ�������
        XDate<T> GetDate() const;
        ///ȡ��ǰ����ʱ���ܵ�������
        XInt  GetDays() const
        {
            return XInt(m_DateTime / MILLIS_PRE_DAY64);
        }
        ///ȡ��ǰ����ʱ���ܵĺ�����
        XLong GetAllMillis() const
        {
            return m_DateTime;
        }
        ///ȡ��ǰ����ʱ������
        XInt getYear() const
        {
            SDate d;
            DecodeDate(d);
            return d.Year;
        }
        ///ȡ��ǰ����ʱ����·�
        XInt getMonth() const
        {
            SDate d;
            DecodeDate(d);
            return d.Month;
        }
        ///ȡ��ǰ����ʱ�������
        XInt getDay() const
        {
            SDate d;
            DecodeDate(d);
            return d.Day;
        }
        ///ȡ��ǰ����ʱ���Сʱ
        XInt getHour() const
        {
            STime t;
            DecodeTime(t);
            return t.Hour;
        }
        ///ȡ��ǰ����ʱ��ķ���
        XInt getMinute() const
        {
            STime t;
            DecodeTime(t);
            return t.Minute;
        }
        ///ȡ��ǰ����ʱ�������
        XInt getSecond() const
        {
            STime t;
            DecodeTime(t);
            return t.Second;
        }
        ///ȡ��ǰ����ʱ��ĺ�����
        XInt getMillis() const
        {
            STime t;
            DecodeTime(t);
            return t.Millis;
        }
        ///����ʱ��
        /**
         * @param [out] paramHour ���ؼ��������Сʱ
         * @param [out] paramMinute ���ؼ�������ķ���
         * @param [out] paramSecond ���ؼ����������
         * @param [out] paramMillis ���ؼ�������ĺ���
         */
        void DecodeTime(XInt &paramHour, XInt &paramMinute, XInt &paramSecond, XInt &paramMillis) const
        {
            MillisToTime(XInt(m_DateTime % MILLIS_PRE_DAY64), paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///����ʱ��
        /**
         * @param [out] paramTime ���ؼ������ʱ��Ľṹ��
         */
        void DecodeTime(STime & paramTime) const
        {
            MillisToTime(XInt(m_DateTime % MILLIS_PRE_DAY64), paramTime);
        }
        ///��������
        /**
         * @param [out] paramYear ���ؼ�������
         * @param [out] paramMonth ���ؼ�������·�
         * @param [out] paramDay ���ؼ����������
         */
        void DecodeDate(XInt &paramYear, XInt & paramMonth, XInt & paramDay) const
        {
            DaysToDate(XInt(m_DateTime / MILLIS_PRE_DAY64), paramYear, paramMonth, paramDay);
        }
        ///��������
        /**
         * @param [out] paramDate ���������
         */
        void DecodeDate(SDate & paramDate) const
        {
            DaysToDate(XInt(m_DateTime / MILLIS_PRE_DAY64), paramDate);
        }

        ///��������ʱ��
        /**
         * @param [out] paramYear ���ؼ�������
         * @param [out] paramMonth ���ؼ�������·�
         * @param [out] paramDay ���ؼ����������
         * @param [out] paramHour ���ؼ��������Сʱ
         * @param [out] paramMinute ���ؼ�������ķ���
         * @param [out] paramSecond ���ؼ����������
         * @param [out] paramMillis ���ؼ�������ĺ���
         */
        void DecodeDateTime(XInt &paramYear, XInt & paramMonth, XInt & paramDay,
            XInt &paramHour, XInt &paramMinute, XInt &paramSecond, XInt &paramMillis) const
        {
            DaysToDate(XInt(m_DateTime / MILLIS_PRE_DAY64), paramYear, paramMonth, paramDay);
            MillisToTime(XInt(m_DateTime % MILLIS_PRE_DAY64), paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///��ֵ��������
        /**
         * @param [in] paramDateTime ����ֵ������ʱ��
         * @return ���ص�ǰ���������
         */
        XDateTime<T> & operator = (const XDateTime<T> & paramDateTime)
        {
            m_DateTime = paramDateTime.m_DateTime;
            return *this;
        }
        ///��ֵ����
        /**
         * @param [in] paramDateTime Ҫ��ֵ������ʱ�������
         * @return ���ص�ǰ����ʱ�������
         */
        XDateTime<T> & operator = (XLong paramDateTime)
        {
            m_DateTime = paramDateTime;
            RoundDateTime();
            return *this;
        }
        ///��������ʱ��
        /**
        * @param [out] paramDate ����������
        * @param [out] paramTime ����������
        */
        void DecodeDateTime(SDate & paramDate, STime & paramTime) const
        {
            DaysToDate(XInt(m_DateTime / MILLIS_PRE_DAY64), paramDate);
            MillisToTime(XInt(m_DateTime % MILLIS_PRE_DAY64), paramTime);
        }

        //һ������ڱȽϺ���
        bool operator == (const XDateTime<T> & paramDateTime) const { return m_DateTime == paramDateTime.m_DateTime; }
        bool operator != (const XDateTime<T> & paramDateTime) const { return m_DateTime != paramDateTime.m_DateTime; }
        bool operator >= (const XDateTime<T> & paramDateTime) const { return m_DateTime >= paramDateTime.m_DateTime; }
        bool operator <= (const XDateTime<T> & paramDateTime) const { return m_DateTime <= paramDateTime.m_DateTime; }
        bool operator >  (const XDateTime<T> & paramDateTime) const { return m_DateTime >  paramDateTime.m_DateTime; }
        bool operator <  (const XDateTime<T> & paramDateTime) const { return m_DateTime <  paramDateTime.m_DateTime; }
        //һ����������Ƚϵĺ���
        bool operator == (const XLong & paramDateTime) const { return m_DateTime == paramDateTime; }
        bool operator != (const XLong & paramDateTime) const { return m_DateTime != paramDateTime; }
        bool operator >= (const XLong & paramDateTime) const { return m_DateTime >= paramDateTime; }
        bool operator <= (const XLong & paramDateTime) const { return m_DateTime <= paramDateTime; }
        bool operator >  (const XLong & paramDateTime) const { return m_DateTime >  paramDateTime; }
        bool operator <  (const XLong & paramDateTime) const { return m_DateTime <  paramDateTime; }
        ///����ָ���ĺ�����
        void AddMillis(XLong paramDuration)
        {
            m_DateTime += paramDuration;
            RoundDateTime();
        }
        ///����ָ���ĺ�����
        void SubMillis(XLong paramDuration)
        {
            m_DateTime -= paramDuration;
            RoundDateTime();
        }
        ///����+=�����:ʱ������
        /**
            @param [in] paramDuration ���ӵ�ʱ�䣬��λ������
            @return ���ص�ǰ����ʱ�������
         */
        XDateTime & operator += (XLong paramDuration)
        {
            m_DateTime += paramDuration;
            RoundDateTime();
            return *this;
        }
        ///����-=�����:ʱ�����
        /**
            @param [in] paramDuration ���ٵ�ʱ�䣬��λ������
            @return ���ص�ǰ����ʱ�������
         */
        XDateTime & operator -= (XLong paramDuration)
        {
            m_DateTime -= paramDuration;
            RoundDateTime();
            return *this;
        }
        ///����ʱ���ʽ���ַ���: ��ʽΪ: HH:MM:SS.mmm
        T & ToTimeString(T & paramString) const;
        ///����ʱ���ʽ���ַ���: ��ʽΪ: HH:MM:SS.mmm
        T ToTimeString() const
        {
            T strRet;
            ToTimeString(strRet);
            return strRet;
        }
        ///�������ڸ�ʽ���ַ���: ��ʽΪ: YYYY-MM-DD
        T & ToDateString(T & paramString) const;
        ///�������ڸ�ʽ���ַ���: ��ʽΪ: YYYY-MM-DD
        T ToDateString() const
        {
            T strRet;
            ToDateString(strRet);
            return strRet;
        }
        ///������ʱ��ת�����ַ���
        T ToString() const
        {
            T strRet;
            ToString(strRet);
            return strRet;
        }
        //YYYY-MM-DD HH:mm:ss.mmm
        StringChar * ToString(StringChar paramString[24]) const
        {
            XInt iYear, iMonth, iDay, iHour, iMinute, iSecond, iMillis;
            DecodeDateTime(iYear, iMonth, iDay, iHour, iMinute, iSecond, iMillis);
            StringChar * p = paramString;
            detail::__XX__FastToDateTimeString(p, iYear, 4);
            p += 4;
            *p++='-';
            detail::__XX__FastToDateTimeString(p, iMonth, 2);
            p += 2;
            *p++='-';
            detail::__XX__FastToDateTimeString(p, iDay, 2);
            p += 2;
            *p++=' ';
            detail::__XX__FastToDateTimeString(p, iHour, 2);
            p += 2;
            *p++=':';
            detail::__XX__FastToDateTimeString(p, iMinute, 2);
            p += 2;
            *p++=':';
            detail::__XX__FastToDateTimeString(p, iSecond, 2);
            p += 2;
            *p++='.';
            detail::__XX__FastToDateTimeString(p, iMillis, 3);
            p += 3;
            *p = 0;
            return paramString;
        }
        ///������ʱ��ת�����ַ���
        /**
            �����������Ҫ�ⲿ�ṩһ���ַ�������
            @param [out] paramString ����ת�����ַ����Ķ���
            @return ����ת����Ķ�������
         */
        T & ToString(T & paramString) const;
        ///������ʱ��ת��Ϊ����, ����ת��
        operator XDate<T>() const;
        ///������ʱ��ת��Ϊʱ��, ����ת��
        operator XTime<T>() const;
        ///������ʱ��ת��Ϊ����, ����ת��
        operator XWeek<T>() const;
        ///��������ʱ��
        XDurationTime<T> operator - (const XDateTime<T> & paramDateTime) const;
        ///����XAnsiStringת�������
        operator T() const
        {
            T strRet;
            ToString(strRet);
            return strRet;
        }
        ///����++���������ǰ����ʱ���Լ�1
        /**
         * ��ǰ����ʱ���Լ�1
         * @return ���ؼ�1��ǰ��������
         */
        XDateTime<T> & operator++()
        {
            ++ m_DateTime;
            RoundDateTime();
            return *this;
        }
        ///����++���������ǰ����ʱ���Լ�1
        /**
         * ��ǰ����ʱ���Լ�1
         * @return ���ؼ�1ǰ����ʱ����
         */
        XDateTime<T> operator++(int)
        {
            XDateTime<T> t(*this);
            ++ m_DateTime;
            RoundDateTime();
            return t;
        }
        ///����--���������ǰ����ʱ���Լ�1
        /**
         * ��ǰ����ʱ���Լ�1
         * @return ���ؼ�1��ǰ��������
         */
        XDateTime<T> & operator--()
        {
            --m_DateTime;
            RoundDateTime();
            return *this;
        }
        ///����--���������ǰ����ʱ���Լ�1
        /**
         * ��ǰ����ʱ���Լ�1
         * @return ���ؼ�1ǰ����ʱ����
         */
		XDateTime<T> operator--(int)
        {
            XDateTime<T> t(*this);
            --m_DateTime;
            RoundDateTime();
            return t;
        }
        ///����+���������ǰ����ʱ���v
        /**
         * ��ǰ����ʱ���v
         * @param [in] v ��ǰ����ʱ��ӵ�ֵ����λ����
         * @return ���ص�ǰ����ʱ�����Ӻ����ʱ����
         */
        XDateTime<T> operator + (XLong v) const
        {
            return XDateTime(m_DateTime + v);
        }
        ///����-���������ǰ����ʱ���v
        /**
         * ��ǰ����ʱ���v
         * @param [in] v ��ǰ����ʱ�����ֵ����λ����
         * @return ���ص�ǰ����ʱ����ٺ����ʱ����
         */
        XDateTime<T> operator - (XLong v) const
        {
            return XDateTime<T>(m_DateTime - v);
        }
        ///���ַ����н�������ʱ��
        /**
         * @param [in] paramDateTime ����ʱ�䴮
         * @return ���ؽ������
         *    - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
         *    - ����ֵ��ʾ����ʧ��
         */
        EnumParseDateTimeErrorCode Parse(const StringChar * paramDateTime)
        {
            SDate dtDate;
            STime tTime;
            EnumParseDateTimeErrorCode eRet = ParseDateTime(paramDateTime, dtDate, tTime);
            if( eRet == X_DATETIME_ERROR_OK ) SetDateTime(dtDate, tTime);
            return eRet;
        }
        ///���ַ����н�������ʱ��
        /**
         * @param [in] paramDateTime ����ʱ�䴮
         * @return ���ؽ������
         *    - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
         *    - ����ֵ��ʾ����ʧ��
         */
        EnumParseDateTimeErrorCode Parse(const T & paramDateTime)
        {
            return Parse(paramDateTime.c_str());
        }
    private:
        ///Բ�س�����ʱ��
        void RoundDateTime()
        {
            if( m_DateTime < MIN_MILLIS || m_DateTime >= MAX_MILLIS)
            {
                m_DateTime = (m_DateTime - MIN_MILLIS) % MAX_DURATION;
                if( m_DateTime < 0 ) m_DateTime += MAX_DURATION;
                m_DateTime += MIN_MILLIS;
            }
        }
    private:
        XLong m_DateTime; ///<����ʱ��ĺ�����
    };
    //=====================================================================
    template<class T = XAnsiString>
    class XTime
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///ָ��ʱ��Ĺ��캯��
        XTime(XInt paramTime = MIN_MILLIS_IN_DAY)
            :m_Millis(paramTime)
        {
            RoundTime();
        }
        ///Ĭ�Ͽ������캯��
        XTime(const XTime<T> & paramTime)
            :m_Millis(paramTime.m_Millis)
        {}
        ///ָ��ʱ��Ĺ��캯��
        XTime(XInt paramHour,XInt paramMinute, XInt paramSecond = 0, XInt paramMillis = 0)
            :m_Millis(CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis))
        {}
        ///ָ������ʱ��Ĺ��캯��
        XTime(const XDateTime<T> & paramDateTime)
            :m_Millis(XInt(XLong(paramDateTime) % MILLIS_PRE_DAY64))
        {
        }
        ///����ʱ��
        /**
         * @param [out] paramHour ���ؼ��������Сʱ
         * @param [out] paramMinute ���ؼ�������ķ���
         * @param [out] paramSecond ���ؼ����������
         * @param [out] paramMillis ���ؼ�������ĺ���
         */
        void Decode(XInt & paramHour, XInt & paramMinute, XInt & paramSecond, XInt & paramMillis) const
        {
            MillisToTime(m_Millis, paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///����ʱ��
        /**
         * @param [out] paramTime ���ؼ��������ʱ��
         */
        void Decode(STime & paramTime) const
        {
            MillisToTime(m_Millis, paramTime);
        }
        ///����ʱ��
        /**
         * @param [out] paramHour ���ؼ��������Сʱ
         * @param [out] paramMinute ���ؼ�������ķ���
         * @param [out] paramSecond ���ؼ����������
         */
        void Decode(XInt & paramHour, XInt & paramMinute, XInt & paramSecond) const
        {
            XInt iMillis;
            MillisToTime(m_Millis, paramHour, paramMinute, paramSecond, iMillis);
        }
        ///����ָ����������ʱ��
        /**
            @param [in] paramMillis ָ���ĺ�����
         */
        void SetTime(XInt paramMillis)
        {
            m_Millis = paramMillis;
            RoundTime();
        }
        ///����ָ��ʱ���֡��롢�����ʱ��
        /**
         * @param [in] paramHour Сʱ����ֵ��[0,23]֮��
         * @param [in] paramMinute ���ӣ���ֵ��[0,59]֮��
         * @param [in] paramSecond �룬��ֵ��[0,59]֮��
         * @param [in] paramMillis ���룬��ֵ��[0,999]֮��
         * @exception XEXDateTimeError �д������׳��쳣
         */
        void SetTime(XInt paramHour, XInt paramMinute, XInt paramSecond = 0, XInt paramMillis = 0)
        {
            m_Millis = CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///����ָ��ʱ���ʱ��
        /**
         * @param [in] paramTime ָ����ʱ��
         */
        void SetTime(const XTime<T> & paramTime)
        {
            m_Millis = paramTime.m_Millis;
        }
        ///����ָ��ʱ���ʱ��
        /**
         * @param [in] paramTime ��Ч��ʱ��
         */
        void SetTime(const STime & paramTime)
        {
            m_Millis = CalcMillisByTime(paramTime.Hour, paramTime.Minute, paramTime.Second, paramTime.Millis);
        }
        ///����ָ������ʱ���ʱ��
        /**
         * @param [in] paramDateTime ָ��������ʱ��
         */
        void SetTime(const XDateTime<T> & paramDateTime)
        {
            m_Millis = XInt(XLong(paramDateTime) % MAX_MILLIS_IN_DAY);
        }
        ///����ʱ��Ϊ��ǰϵͳʱ��
        void SetNowTime()
        {
            m_Millis = XInt(GetNowDateTime() % MILLIS_PRE_DAY64);
        }
        ///����ǰʱ����Ϊϵͳʱ��
        void SetTimeToOS() const
        {
            XDateTime<T> dt;
            dt.SetNowDateTime();
            dt.SetTime(*this);
            dt.SetDateTimeToOS();
        }
        ///ȱʡ��ֵ����
        XTime<T> & operator = (const XTime<T> & paramTime)
        {
            m_Millis = paramTime.m_Millis;
            return *this;
        }
        ///ȱʡ��ֵ����
        XTime<T> & operator = (const STime & paramTime)
        {
            SetTime(paramTime);
            return *this;
        }

        ///ָ���������ĸ�ֵ����
        XTime<T> & operator = (XInt paramTime)
        {
            m_Millis = paramTime;
            RoundTime();
            return *this;
        }
        ///ָ������ʱ��ĸ�ֵ����
        XTime<T> & operator = (const XDateTime<T> & paramDateTime)
        {
            m_Millis = XInt(XLong(paramDateTime) % MILLIS_PRE_DAY64);
            return *this;
        }
        ///����ָ���ĺ�����
        /**
            @param [in] paramMillis ָ�����ӵĺ�����
         */
        void AddMillis(XInt paramMillis)
        {
            m_Millis += paramMillis;
            RoundTime();
        }
        ///����ָ���ĺ�����
        /**
            @param [in] paramMillis ָ�����ٺ�����
         */
        void SubMillis(XInt paramMillis)
        {
            m_Millis -= paramMillis;
            RoundTime();
        }
        ///����ָ���ĺ�����
        /**
            @param [in] paramMillis ָ�����ӵĺ�����
         */
        XTime<T> & operator += (XInt paramMillis)
        {
            m_Millis += paramMillis;
            RoundTime();
            return *this;
        }
        ///����ָ���ĺ�����
        /**
            @param [in] paramMillis ָ�����ٺ�����
         */
        XTime<T> & operator -= (XInt paramMillis)
        {
            m_Millis -= paramMillis;
            RoundTime();
            return *this;
        }

        ///����++���������ǰʱ���Լ�1
        /**
         * ��ǰʱ���Լ�1
         * @return ���ؼ�1��ǰ��������
         */
        XTime<T> & operator++()
        {
            ++ m_Millis;
            RoundTime();
            return *this;
        }
        ///����++���������ǰʱ���Լ�1
        /**
         * ��ǰʱ���Լ�1
         * @return ���ؼ�1ǰ����ʱ����
         */
		XTime<T> operator++(int)
		{
            XTime<T> t(*this);
            ++ m_Millis;
            RoundTime();
            return t;
        }
        ///����--���������ǰʱ���Լ�1
        /**
         * ��ǰ�����Լ�1
         * @return ���ؼ�1��ǰ��������
         */
        XTime<T> & operator--()
        {
            --m_Millis;
            RoundTime();
            return *this;
        }
        ///����--���������ǰʱ���Լ�1
        /**
         * ��ǰʱ���Լ�1
         * @return ���ؼ�1ǰ����ʱ����
		 */
        XTime<T> operator--(int)
		{
            XTime<T> t(*this);
            --m_Millis;
            RoundTime();
            return t;
        }
        ///��ʱ��ת��Ϊ32λ�����ĺ�����
        operator XInt() const { return m_Millis; }
        ///�����ַ���ת������
        operator T() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }
        ///����ʱ���ַ���
        T & ToString(T & paramString) const;
        StringChar * ToString(StringChar paramString[16]) const
        {
            XInt iHour, iMinute, iSecond, iMillis;
            Decode(iHour, iMinute, iSecond, iMillis);
            StringChar * p = paramString;
            detail::__XX__FastToDateTimeString(p, iHour, 2);
            p += 2;
            *p++=':';
            detail::__XX__FastToDateTimeString(p, iMinute, 2);
            p += 2;
            *p++=':';
            detail::__XX__FastToDateTimeString(p, iSecond, 2);
            p += 2;
            *p++='.';
            detail::__XX__FastToDateTimeString(p, iMillis, 3);
            p += 3;
            *p = 0;
            return paramString;
        }
        ///����ʱ���ַ���
        T ToString() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }
        //һ��ȽϺ���
        bool operator == (const XTime<T> & paramTime) const { return m_Millis == paramTime.m_Millis; }
        bool operator >= (const XTime<T> & paramTime) const { return m_Millis >= paramTime.m_Millis; }
        bool operator <= (const XTime<T> & paramTime) const { return m_Millis <= paramTime.m_Millis; }
        bool operator != (const XTime<T> & paramTime) const { return m_Millis != paramTime.m_Millis; }
        bool operator >  (const XTime<T> & paramTime) const { return m_Millis >  paramTime.m_Millis; }
        bool operator <  (const XTime<T> & paramTime) const { return m_Millis <  paramTime.m_Millis; }
        //һ��ȽϺ���
        bool operator == (XInt paramTime) const { return m_Millis == paramTime; }
        bool operator >= (XInt paramTime) const { return m_Millis >= paramTime; }
        bool operator <= (XInt paramTime) const { return m_Millis <= paramTime; }
        bool operator != (XInt paramTime) const { return m_Millis != paramTime; }
        bool operator >  (XInt paramTime) const { return m_Millis >  paramTime; }
        bool operator <  (XInt paramTime) const { return m_Millis <  paramTime; }
        ///����-�����,���ؼ��ٺ�������ʱ��
        XTime<T> operator - (XInt paramMillis) const { return XTime(m_Millis - paramMillis); }
        ///����+�����,�������Ӻ�������ʱ��
        XTime<T> operator + (XInt paramMillis) const { return XTime(m_Millis + paramMillis); }
        ///����ʱ����ʱ��
        //XDurationTime operator - (const XTime & paramTime);
        ///ȡ��ǰʱ����ܵĺ�����
        XInt getAllMillis() const
        {
            return m_Millis;
        }
        ///ȡ��ǰʱ���Сʱ��
        XInt getHour() const
        {
            STime t;
            Decode(t);
            return t.Hour;
        }
        ///ȡ��ǰʱ��ķ�����
        XInt getMinute() const
        {
            STime t;
            Decode(t);
            return t.Minute;
        }
        ///ȡ��ǰʱ�������
        XInt getSecond() const
        {
            STime t;
            Decode(t);
            return t.Second;
        }
        ///ȡ��ǰʱ��ĺ�����
        XInt getMillis() const
        {
            STime t;
            Decode(t);
            return t.Millis;
        }
        ///���ַ����н���ʱ��
        /**
         * @param [in] paramTime ʱ�䴮
         * @return ���ؽ������
         *    - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
         *    - ����ֵ��ʾ����ʧ��
         */
        EnumParseDateTimeErrorCode Parse(const StringChar * paramTime)
        {
            STime tTime;
            EnumParseDateTimeErrorCode eRet = ParseTime(paramTime, tTime);
            if( eRet == X_DATETIME_ERROR_OK ) SetTime(tTime);
            return eRet;
        }
        ///���ַ����н���ʱ��
        /**
         * @param [in] paramTime ʱ�䴮
         * @return ���ؽ������
         *    - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
         *    - ����ֵ��ʾ����ʧ��
         */
        EnumParseDateTimeErrorCode Parse(const T & paramTime)
        {
            return Parse(paramTime.c_str());
        }
    private:
        ///Բ�س�����ʱ��
        void RoundTime()
        {
            if( m_Millis < MIN_MILLIS_IN_DAY || m_Millis >= MAX_MILLIS_IN_DAY )
            {
                m_Millis %= MILLIS_PRE_DAY;
                if( m_Millis < 0 ) m_Millis += MILLIS_PRE_DAY;
            }
        }
    private:
        XInt m_Millis;    ///<ʱ��ĺ�����
    };
    //=====================================================================
    template<class T = XAnsiString>
    class XDate
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///ָ�������Ĺ��캯��
        /**
         * @param [in] paramDays ָ��������
         */
        XDate(XInt paramDays = DAYS_1970_1_1)
            :m_Days(DAYS_1970_1_1)
        {
            m_Days = paramDays;
            RoundDate();
        }
        ///Ĭ�Ͽ������캯��
        /**
         * @param [in] paramDate ָ��������
         */
        XDate(const XDate<T> & paramDate)
            :m_Days(paramDate.m_Days)
        {}
        ///ָ������ʱ��Ĺ��캯��
        /**
         * @param [in] paramDateTime ָ��������ʱ��
         */
        XDate(const XDateTime<T> & paramDateTime)
            :m_Days(paramDateTime.GetDays())
        {
        }
        ///ָ�������յĹ��캯��,ת����ָ�����ڴ�Ԫ��1��1�տ�ʼ������
        /**
         * @param [in] paramYear ָ�������
		 * @param [in] paramMonth ָ������
         * @param [in] paramDay ָ��������
         */
        XDate(XInt paramYear, XInt paramMonth, XInt paramDay)
            :m_Days(CalcDays(paramYear, paramMonth, paramDay))
        {}
        ///����ǰ����ת��Ϊ�ꡢ�¡���
        /**
         * @param [out] paramYear ���ڷ��ؽ������
         * @param [out] paramMonth ���ڷ��ؽ������
         * @param [out] paramDay ���ڷ��ؽ������
         */
        void Decode(XInt & paramYear,XInt & paramMonth,XInt & paramDay) const
        {
            DaysToDate(m_Days, paramYear, paramMonth, paramDay);
        }
        ///����ǰ����ת��Ϊ����
        /**
         * @param [out] paramDate ���ڷ��ؽ��������, Ŀǰת���ķ�Χ[0001-01-01, 9999-12-30]
         */
        void Decode(SDate & paramDate) const
        {
            DaysToDate(m_Days, paramDate);
        }
        ///������ת��Ϊ32λ����������
        operator XInt() const { return m_Days; }
        ///����������Ϊϵͳ����
        void SetNowDate()
        {
            SSystemDateTime s;
            GetSystemDateTime(s);
            m_Days = CalcDays(s.Year, s.Month, s.Day);
        }
        ///��ϵͳ��������Ϊ��ǰ������
        void SetDateToOS() const
        {
            XDateTime<T> dt;
            dt.SetNowDateTime();
            dt.SetDate(*this);
            dt.SetDateTimeToOS();
        }
        ///�������ڣ�ָ������
        /**
         * @param [in] paramDays ָ��������
         */
        void SetDate(XInt paramDays)
        {
            m_Days = paramDays;
            RoundDate();
        }
        ///�������ڣ�ָ��������
        /**
         * @param [in] paramYear ָ������
         * @param [in] paramMonth ָ������
         * @param [in] paramDay ָ��������
         */
        void SetDate(XInt paramYear, XInt paramMonth, XInt paramDay)
        {
            m_Days = CalcDays(paramYear, paramMonth, paramDay);
        }
        ///�������ڣ�ָ������ʱ��
        /**
         * @param [in] paramDateTime ָ��������ʱ��
         */
        void SetDate(const XDateTime<T> & paramDateTime)
        {
            m_Days = paramDateTime.GetDays();
        }
        ///�������ڣ�ָ������
        /**
         * @param [in] paramDate ָ��������
         */
        void SetDate(const SDate & paramDate)
        {
            m_Days = CalcDays(paramDate.Year, paramDate.Month, paramDate.Day);
        }
        ///�������ڣ�ָ������
        /**
         * @param [in] paramDate ָ��������
         */
        void SetDate(const XDate<T> & paramDate)
        {
            m_Days = paramDate.m_Days;
        }
        ///���ڸ�ֵ��ָ������
        /**
         * @param [in] paramDays ָ��������
         * @return ���ص�ǰ���������
         */
        XDate<T> & operator = (XInt paramDays)
        {
            m_Days = paramDays;
            RoundDate();
            return *this;
        }
        ///���ڸ�ֵ��ָ������
        /**
         * @param [in] paramDate ָ��������
         * @return ���ص�ǰ���������
         */
        XDate<T> & operator = (const XDate<T> & paramDate)
        {
            m_Days = paramDate.m_Days;
            return *this;
        }
        ///���ڸ�ֵ��ָ������
        /**
         * @param [in] paramDate �Ϸ�������
         * @return ���ص�ǰ���������
         */
        XDate<T> & operator = (const SDate & paramDate)
        {
            SetDate(paramDate);
            return *this;
        }
        ///���ڸ�ֵ��ָ������ʱ��
        /**
         * @param [in] paramDateTime ָ��������
         * @return ���ص�ǰ���������
         */
        XDate<T> & operator = (const XDateTime<T> & paramDateTime)
        {
            m_Days = paramDateTime.GetDays();
            return *this;
        }
        ///������ת��Ϊ�ַ���
        /**
         * @param [out] paramString ���ڱ��������ַ���
         * @return ���������ַ���������
         */
        T & ToString(T & paramString) const;
        StringChar * ToString(StringChar paramString[16]) const
        {
            XInt iYear, iMonth, iDay;
            Decode(iYear, iMonth, iDay);
            StringChar * p = paramString;
            detail::__XX__FastToDateTimeString(p, iYear, 4);
            p += 4;
            *p++='-';
            detail::__XX__FastToDateTimeString(p, iMonth, 2);
            p += 2;
            *p++='-';
            detail::__XX__FastToDateTimeString(p, iDay, 2);
            p += 2;
            *p = 0;
            return paramString;
        }
        ///������ת��Ϊ�ַ���
        /**
         * @return ���������ַ���
         */
        T ToString() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }
        ///Tת������,������ת��Ϊ�����ַ���
        operator T() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }

        //һ�����ڱȽϺ���
        bool operator == (const XDate<T> & paramDate) const { return m_Days == paramDate.m_Days; }
        bool operator >= (const XDate<T> & paramDate) const { return m_Days >= paramDate.m_Days; }
        bool operator <= (const XDate<T> & paramDate) const { return m_Days <= paramDate.m_Days; }
        bool operator != (const XDate<T> & paramDate) const { return m_Days != paramDate.m_Days; }
        bool operator >  (const XDate<T> & paramDate) const { return m_Days >  paramDate.m_Days; }
        bool operator <  (const XDate<T> & paramDate) const { return m_Days <  paramDate.m_Days; }
        //һ��ȽϺ���
        bool operator == (XInt paramDate) const { return m_Days == paramDate; }
        bool operator >= (XInt paramDate) const { return m_Days >= paramDate; }
        bool operator <= (XInt paramDate) const { return m_Days <= paramDate; }
        bool operator != (XInt paramDate) const { return m_Days != paramDate; }
        bool operator >  (XInt paramDate) const { return m_Days >  paramDate; }
        bool operator <  (XInt paramDate) const { return m_Days <  paramDate; }

        ///����ָ��������
        /**
            @param [in] paramDays ָ�����ӵ�����
         */
        void AddDays(XInt paramDays)
        {
            m_Days += paramDays;
            RoundDate();
        }
        ///����ָ��������
        /**
            @param [in] paramDays ָ����������
         */
        void SubDays(XInt paramDays)
        {
            m_Days -= paramDays;
            RoundDate();
        }
        ///����ָ��������
        /**
            @param [in] paramDays ָ�����ӵ�����
         */
        XDate<T> & operator += (XInt paramDays)
        {
            m_Days += paramDays;
            RoundDate();
            return *this;
        }
        ///����ָ��������
        /**
            @param [in] paramDays ָ����������
         */
        XDate<T> & operator -= (XInt paramDays)
        {
            m_Days -= paramDays;
            RoundDate();
            return *this;
        }

        ///����++���������ǰ�����Լ�1
        /**
         * ��ǰ�����Լ�1
         * @return ���ؼ�1��ǰ��������
         */
        XDate<T> & operator++()
        {
            ++ m_Days;
            RoundDate();
            return *this;
        }
        ///����++���������ǰ�����Լ�1
        /**
         * ��ǰ�����Լ�1
         * @return ���ؼ�1ǰ����ʱ����
         */
		XDate<T> operator++(int)
        {
            XDate<T> d(*this);
            ++ m_Days;
            RoundDate();
            return d;
        }
        ///����--���������ǰ�����Լ�1
        /**
         * ��ǰ�����Լ�1
         * @return ���ؼ�1��ǰ��������
         */
        XDate<T> & operator--()
        {
            --m_Days;
            RoundDate();
            return *this;
        }
        ///����--���������ǰ�����Լ�1
        /**
         * ��ǰ�����Լ�1
         * @return ���ؼ�1ǰ����ʱ����
         */
		XDate<T> operator--(int)
		{
            XDate<T> d(*this);
            --m_Days;
            RoundDate();
            return d;
        }
        ///ȡ��ǰ���ڵ�����
        /**
         * @return ��������
         */
        XInt GetDays() const
        {
            return m_Days;
        }
        ///ȡ��ǰ������
        XInt getDay() const
        {
            SDate s;
            Decode(s);
            return s.Day;
        }
        ///ȡ��ǰ���·�
        XInt getMonth() const
        {
            SDate s;
            Decode(s);
            return s.Month;
        }
        ///ȡ��ǰ�����
        XInt getYear() const
        {
            SDate s;
            Decode(s);
            return s.Year;
        }
        ///��������
        /**
         * @param [in] paramDate ���ڴ�
         * @return ���ؽ������
         *    - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
         *    - ����ֵ ��ʾ����ʧ��
         */
        EnumParseDateTimeErrorCode Parse(const StringChar * paramDate)
        {
            SDate dtDate;
            EnumParseDateTimeErrorCode eRet = ParseDate(paramDate, dtDate);
            if( eRet == X_DATETIME_ERROR_OK ) SetDate(dtDate);
            return eRet;
        }
        ///��������
        /**
         * @param [in] paramDate ���ڴ�
         * @return ���ؽ������
         *    - X_DATETIME_ERROR_OK ��ʾ�����ɹ�
         *    - ����ֵ ��ʾ����ʧ��
         */
        EnumParseDateTimeErrorCode Parse(const T & paramDate)
        {
            return Parse(paramDate.c_str());
        }
    private:
        ///Բ������
        void RoundDate()
        {
            if( m_Days < MIN_DAYS_IN_DATETIME || m_Days > MAX_DAYS_IN_DATETIME )
            {
                m_Days = (m_Days - MIN_DAYS_IN_DATETIME) % (MAX_DAYS_IN_DATETIME - MIN_DAYS_IN_DATETIME);
                if( m_Days < 0 ) m_Days += (MAX_DAYS_IN_DATETIME - MIN_DAYS_IN_DATETIME);
                m_Days += MIN_DAYS_IN_DATETIME;
            }
        }
    private:
        XInt m_Days;      ///<���ڵ�����
    };
    //=====================================================================
    /**
        ʱ���࣬����Ϊ����Ҳ����Ϊ������
     */
    template<class T = XAnsiString>
    class XDurationTime
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///ָ��ʱ���Ĺ��캯��
        /**
         * @param [in] paramDuration ָ����ʱ��,��λ����
         */
        XDurationTime(XLong paramDuration = 0 )
            :m_Duration(paramDuration)
        {
            RoundDuration();
        }
        ///Ĭ�Ͽ������캯��
        /**
         * @param [in] paramDuration ָ��ʱ������
         */
        XDurationTime(const XDurationTime<T> & paramDuration)
            :m_Duration(paramDuration.m_Duration)
        {}
        ///ָ������,Сʱ�ȹ��캯��
        /**
         * @param [in] paramSign ʱ���ķ���
         *      -1 <0 ��ʾʱ��Ϊ����
         *      1 >=0 ��ʾʱ��Ϊ����
         * @param [in] paramDays ʱ�������� > 0
         * @param [in] paramHour ʱ����Сʱ��[0,23]
         * @param [in] paramMinute ʱ���ķ���[0,59]
         * @param [in] paramSecond ʱ��������[0,59]
         * @param [in] paramMillis ʱ���ĺ�����[0,999]
         */
        XDurationTime(XInt paramSign, XInt paramDays,
            XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0)
        {
            SetDuration(paramSign, paramDays, paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///����ʱ��
        /**
         * @param [in] paramDuration ָ����ʱ��
         */
        void SetDuration(XLong paramDuration = 0 )
        {
            m_Duration = paramDuration;
            RoundDuration();
        }
        ///����ʱ��
        /**
         * @param [in] paramDuration ָ����ʱ��
         */
        void SetDuration(const XDurationTime<T> & paramDuration)
        {
            m_Duration = paramDuration.m_Duration;
        }
        ///����ʱ��
        /**
         * @param [in] paramSign ʱ���ķ���
         *      - <0 ��ʾʱ��Ϊ����
         *      0 >=0 ��ʾʱ��Ϊ����
         * @param [in] paramDays ʱ�������� >= 0
         * @param [in] paramHour ʱ����Сʱ��[0,23]
         * @param [in] paramMinute ʱ���ķ���[0,59]
         * @param [in] paramSecond ʱ��������[0,59]
         * @param [in] paramMillis ʱ���ĺ�����[0,999]
         */
        void SetDuration(XInt paramSign, XInt paramDays, XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0)
		{
            if( paramDays < 0 ) throw XELessThanZero();
            m_Duration = paramDays * MILLIS_PRE_DAY64 + CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis);
            if( paramSign < 0 ) m_Duration = - m_Duration;
        }
        ///ָ��ʱ����ֵ
        /**
         * @param [in] paramDuration ָ����ʱ��
         * @return ���ص�ǰʱ�����������
         */
        XDurationTime<T> & operator = (XLong paramDuration)
        {
            m_Duration = paramDuration;
            RoundDuration();
            return *this;
        }
        ///Ĭ�ϸ�ֵ����
        /**
         * @param [in] paramDuration ָ����ʱ������
         * @return ���ص�ǰʱ�����������
         */
        XDurationTime<T> & operator = (const XDurationTime<T> & paramDuration)
        {
            m_Duration = paramDuration.m_Duration;
            return *this;
        }
        ///����ʱ��
        /**
         * @param [in] paramMillis ���ӵĺ�����
         */
        void AddMillis(XLong & paramMillis)
        {
            m_Duration += paramMillis;
            RoundDuration();
        }
        ///����ʱ��
        /**
         * @param [in] paramMillis ���ٵĺ�����
         */
        void SubMillis(XLong & paramMillis)
        {
            m_Duration -= paramMillis;
            RoundDuration();
        }
        ///����ʱ��
        /**
         * @param [in] paramMillis ���ӵĺ�����
         */
        void AddDuration(const XDurationTime<T> & paramDuration)
        {
            m_Duration += paramDuration.m_Duration;
            RoundDuration();
        }
        ///����ʱ��
        /**
         * @param [in] paramMillis ���ٵĺ�����
         */
        void SubDuration(const XDurationTime<T> & paramDuration)
        {
            m_Duration -= paramDuration.m_Duration;
            RoundDuration();
        }

        ///����ʱ��
        /**
         * @param [in] paramDuration ���ӵĺ�����
         * @return ���ص�ǰʱ�����������
         */
        XDurationTime<T> & operator += (XLong paramDuration)
        {
            m_Duration += paramDuration;
            RoundDuration();
            return *this;
        }
        ///����ʱ��
        /**
         * @param [in] paramDuration ���ӵ�ʱ��
         * @return ���ص�ǰʱ�����������
         */
        XDurationTime<T> & operator += (const XDurationTime<T> & paramDuration)
        {
            m_Duration += paramDuration.m_Duration;
            RoundDuration();
            return *this;
        }
        ///����ʱ��
        /**
         * @param [in] paramDuration ���ٵĺ�����
         * @return ���ص�ǰʱ�����������
         */
        XDurationTime<T> & operator -= (XLong paramDuration)
        {
            m_Duration -= paramDuration;
            RoundDuration();
            return *this;
        }
        ///����ʱ��
        /**
         * @param [in] paramDuration ���ٵ�ʱ��
         * @return ���ص�ǰʱ�����������
         */
        XDurationTime<T> & operator -= (const XDurationTime<T> & paramDuration)
        {
            m_Duration -= paramDuration.m_Duration;
            RoundDuration();
            return *this;
        }
        ///����ʱ�����
        /**
         * @param [in] paramDuration ��ӵ�ʱ��
         * @return ��������ʱ����ӵĽ��
         */
        XDurationTime<T> operator + (const XDurationTime<T> & paramDuration) const
        {
            return XDurationTime<T>(m_Duration + paramDuration.m_Duration);
        }
        ///����ʱ�����
        /**
         * @param [in] paramDuration ��ӵĺ�����
         * @return ��������ʱ����ӵĽ��
         */
        XDurationTime<T> operator + (XLong paramDuration) const
        {
            return XDurationTime<T>(m_Duration + paramDuration);
        }
        ///����ʱ�����
        /**
         * @param [in] paramDuration ��ӵ�ʱ��
         * @return ��������ʱ������Ľ��
         */
        XDurationTime<T> operator - (const XDurationTime<T> & paramDuration) const
        {
            return XDurationTime<T>(m_Duration - paramDuration.m_Duration);
        }
        ///����ʱ�����
        /**
         * @param [in] paramDuration ����ĺ�����
         * @return ��������ʱ������Ľ��
         */
        XDurationTime<T> operator - (XLong paramDuration) const
        {
            return XDurationTime<T>(m_Duration - paramDuration);
        }
        ///��ʱ���������,ʱ,��,��,����
        /**
         * @param [out] paramSign ����ʱ������
         * @param [out] paramDays ����ʱ��������
         * @param [out] paramHour ����ʱ����Сʱ
         * @param [out] paramMinute ����ʱ���ķ���
         * @param [out] paramSecond ����ʱ��������
         * @param [out] paramMillis ����ʱ���ĺ�����
         */
        void Decode(XInt & paramSign, XInt & paramDays, XInt & paramHour, XInt & paramMinute, XInt & paramSecond, XInt & paramMillis) const
        {
            XLong aTmp = m_Duration;
            if( m_Duration < 0 )
            {
                paramSign = -1;
                aTmp = -aTmp;
            }else paramSign = 1;
            paramDays = XInt(aTmp / MILLIS_PRE_DAY64);
            MillisToTime(XInt(aTmp % MILLIS_PRE_DAY64), paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///��ʱ���������,ʱ,��,��
        /**
         * @param [out] paramSign ����ʱ������
         * @param [out] paramDays ����ʱ��������
         * @param [out] paramHour ����ʱ����Сʱ
         * @param [out] paramMinute ����ʱ���ķ���
         * @param [out] paramSecond ����ʱ��������
         */
        void Decode(XInt & paramSign,XInt & paramDays,XInt & paramHour,XInt & paramMinute,XInt & paramSecond) const
        {
            XInt paramMillis;
            Decode(paramSign, paramDays, paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///��ʱ��ת��Ϊ�ַ���
        /**
         * ת���ĸ�ʽ�� Days HH:MM:SS.mmm �� -Days HH:MM:SS.mmm
         * @param [out] paramString ���ת�����ַ������ַ���
         * @return ����ת������ַ���
         */
        T & ToString(T & paramString) const
        {
            StringChar buffer[40];
            paramString = ToString(buffer);
            return paramString;
        }
        StringChar * ToString(StringChar paramString[40]) const
        {
            XInt iSign, iDays, iHour, iMinute, iSecond, iMillis;
            Decode(iSign, iDays, iHour, iMinute, iSecond, iMillis);
            StringChar * p = paramString;
            if( iSign == -1 ) *p++ = '-';
            string_utils::IntToStr(iDays,p);
            p += string_utils::Length(p);
            *p ++ = ' ';
            detail::__XX__FastToDateTimeString(p, iHour, 2);
            p += 2;
            *p++=':';
            detail::__XX__FastToDateTimeString(p, iMinute, 2);
            p += 2;
            *p++=':';
            detail::__XX__FastToDateTimeString(p, iSecond, 2);
            p += 2;
            *p++='.';
            detail::__XX__FastToDateTimeString(p, iMillis, 3);
            p += 3;
            *p = 0;
            return paramString;
        }
        ///��ʱ��ת��Ϊ�ַ���
        /**
         * ת���ĸ�ʽ�� Days HH:MM:SS.mmm �� -Days HH:MM:SS.mmm
         * @return ����ת������ַ���
         */
        T ToString() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }
        ///����++���������ǰʱ���Լ�1����
        /**
         * ��ǰʱ���Լ�1����
         * @return ���ؼ�1�����ǰ��������
         */
        XDurationTime<T> & operator++()
        {
            ++ m_Duration;
            RoundDuration();
            return *this;
        }
        ///����++���������ǰʱ���Լ�1����
        /**
         * ��ǰʱ���Լ�1����
         * @return ���ؼ�1����ǰ����ʱ����
         */
		XDurationTime operator++(int)
        {
            XDurationTime d(*this);
            ++ m_Duration;
            RoundDuration();
            return d;
        }
        ///����--���������ǰʱ���Լ�1����
        /**
         * ��ǰʱ���Լ�1����
         * @return ���ؼ�1�����ǰ��������
         */
        XDurationTime & operator--()
        {
            --m_Duration;
            RoundDuration();
            return *this;
        }
        ///����--���������ǰʱ���Լ�1����
        /**
         * ��ǰʱ���Լ�1����
         * @return ���ؼ�1����ǰ����ʱ����
         */
		XDurationTime operator--(int)
		{
            XDurationTime d(*this);
            --m_Duration;
            RoundDuration();
            return d;
        }
        ///��ʱ��ת��Ϊ64λ�����ĺ�����
        operator XLong() const { return m_Duration; }
        ///��ʱ��ת��Ϊ32λ�����ĺ�����
        operator XInt() const  { return XInt(m_Duration); }
        //һ��ȽϺ���
        bool operator == (const XDurationTime & paramDuration) const { return m_Duration == paramDuration.m_Duration; }
        bool operator >= (const XDurationTime & paramDuration) const { return m_Duration >= paramDuration.m_Duration; }
        bool operator <= (const XDurationTime & paramDuration) const { return m_Duration <= paramDuration.m_Duration; }
        bool operator != (const XDurationTime & paramDuration) const { return m_Duration != paramDuration.m_Duration; }
        bool operator >  (const XDurationTime & paramDuration) const { return m_Duration >  paramDuration.m_Duration; }
        bool operator <  (const XDurationTime & paramDuration) const { return m_Duration <  paramDuration.m_Duration; }
        //һ��ȽϺ���
        bool operator == (XInt paramDuration) const { return m_Duration == paramDuration; }
        bool operator >= (XInt paramDuration) const { return m_Duration >= paramDuration; }
        bool operator <= (XInt paramDuration) const { return m_Duration <= paramDuration; }
        bool operator != (XInt paramDuration) const { return m_Duration != paramDuration; }
        bool operator >  (XInt paramDuration) const { return m_Duration >  paramDuration; }
        bool operator <  (XInt paramDuration) const { return m_Duration <  paramDuration; }
        ///���ַ���ת��Ϊʱ��
        /**
         * ת���ĸ�ʽ��[-|+]Days HH:MM:SS.mmm
         * @param [in] paramDuration ʱ���ַ���
         * @return ���ؽ������
         *     - X_DATETIME_ERROR_OK ��ʾ��������
         *     - ����ֵ ��ʾ����ʧ��
         */
        EnumParseDateTimeErrorCode Parse(const StringChar * paramDuration);
        ///���ַ���ת��Ϊʱ��
        /**
         * ת���ĸ�ʽ��[-|+]Days HH:MM:SS.mmm
         * @param [in] paramDuration ʱ���ַ���
         * @return ���ؽ������
         *     - X_DATETIME_ERROR_OK ��ʾ��������
         *     - ����ֵ ��ʾ����ʧ��
         */
        EnumParseDateTimeErrorCode Parse(const T & paramDuration)
        {
            return Parse(paramDuration.c_str());
        }
    private:
        ///Բ��ʱ��
        void RoundDuration()
        {
            m_Duration %= MAX_DURATION;
        }
    private:
        XLong m_Duration; ///<�����ĺ�����
    };
    //=====================================================================
    //���������ַ�����ģʽ
    const XInt XWEEK_MODE_ENGLISH = 0;          ///<Ӣ������ģʽ Sunday
    const XInt XWEEK_MODE_CHINESE = 1;          ///<��������ģʽ ������
    const XInt XWEEK_MODE_SHORT_ENGLISH = 2;    ///<Ӣ�Ķ�����ģʽ Sun.
    const XInt XWEEK_MODE_NUMBER = 3;           ///<Ӣ������       0
    const XInt XWEEK_MODE_SHORT_CHINESE = 4;    ///<���Ķ�����ģʽ ��
    ///������
    template<class T = XAnsiString>
    class XWeek
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///ָ�����ڵĹ��캯��
        /**
         * @param [in] paramWeek ָ��������
         */
        XWeek(XInt paramWeek = WEEKDAY_SUNDAY)
            :m_WeekDay(paramWeek)
        {
            RoundWeek();
        }
        ///ָ������ʱ��Ĺ��캯��
        /**
         * @param [in] paramDateTime ָ��������ʱ��
         */
        XWeek(const XDateTime<T> & paramDateTime)
            :m_WeekDay(paramDateTime.GetDays())
        {
            RoundWeek();
        }
        ///ָ�����ڵĹ��캯��
        /**
         * @param [in] aData ָ��������
         */
        XWeek(const XDate<T> & paramDate)
            :m_WeekDay(paramDate.GetDays())
        {
            RoundWeek();
        }
        ///Ĭ�Ϲ��캯��
        XWeek(const XWeek<T> & paramWeek)
            :m_WeekDay(paramWeek.m_WeekDay)
        {
        }
        ///���ָ��������
        void SetWeek(XInt paramWeek = WEEKDAY_SUNDAY)
        {
            m_WeekDay = paramWeek;
            RoundWeek();
        }
        ///���ָ��������
        void SetWeek(const XWeek<T> & paramWeek)
        {
            m_WeekDay = paramWeek.m_WeekDay;
        }
        ///���ָ�����ڵ�����
        void SetWeek(const XDate<T> & paramDate)
        {
            m_WeekDay = paramDate.GetDays() % 7;
        }
        ///���ָ������ʱ�������
        void SetWeek(const XDateTime<T> & paramDateTime)
        {
            m_WeekDay = paramDateTime.GetDays() % 7;
        }
        ///��ɵ�ǰϵͳ������
        void SetNowWeek()
        {
            XDate<T> paramDate;
            paramDate.SetNowDate();
            m_WeekDay = paramDate.GetDays() % 7;
        }
        ///������ת��Ϊָ��ģʽ���ַ���
        /**
         * @param [in] paramMode ָ��������ģʽ
         * @param [out] paramString ����ת����������ַ���
         */
        T & ToString(T & paramString, XInt paramMode = XWEEK_MODE_ENGLISH) const;
        ///������ת��Ϊָ��ģʽ���ַ���
        /**
         * @param [in] paramMode ָ��������ģʽ
         * @return ����ת����������ַ���
         */
        T ToString(XInt paramMode = XWEEK_MODE_ENGLISH) const
        {
            T paramString;
            ToString(paramString,paramMode);
            return paramString;
        }
        ///������ת��ΪĬ��ģʽ(Ӣ������ģʽ)���ַ���
        operator T() const
        {
            T paramString;
            ToString(paramString, XWEEK_MODE_ENGLISH);
            return paramString;
        }
        ///������ת��ΪXInt
        operator XInt() const
        {
            return m_WeekDay;
        }
        ///�����ڸ�ֵΪָ��������
        XWeek<T> & operator = (XInt paramWeek)
        {
            SetWeek(paramWeek);
            return *this;
        }
        ///�����ڸ�ֵΪָ��������
        XWeek<T> & operator = (const XWeek<T> & paramWeek)
        {
            SetWeek(paramWeek);
            return *this;
        }
        ///�����ڸ�ֵΪָ�����ڵ�����
        XWeek<T> & operator = (const XDate<T> & paramDate)
        {
            SetWeek(paramDate);
            return *this;
        }
        ///�����ڸ�ֵΪָ������ʱ�������
        XWeek<T> & operator = (const XDateTime<T> & paramDateTime)
        {
            SetWeek(paramDateTime);
            return *this;
        }
        //һ��ȽϺ���
        bool operator == (const XWeek<T> & paramWeek) const { return m_WeekDay == paramWeek.m_WeekDay; }
        bool operator >= (const XWeek<T> & paramWeek) const { return m_WeekDay >= paramWeek.m_WeekDay; }
        bool operator <= (const XWeek<T> & paramWeek) const { return m_WeekDay <= paramWeek.m_WeekDay; }
        bool operator != (const XWeek<T> & paramWeek) const { return m_WeekDay != paramWeek.m_WeekDay; }
        bool operator >  (const XWeek<T> & paramWeek) const { return m_WeekDay >  paramWeek.m_WeekDay; }
        bool operator <  (const XWeek<T> & paramWeek) const { return m_WeekDay <  paramWeek.m_WeekDay; }
        //һ��ȽϺ���
        bool operator == (XInt paramWeek) const { return m_WeekDay == paramWeek; }
        bool operator >= (XInt paramWeek) const { return m_WeekDay >= paramWeek; }
        bool operator <= (XInt paramWeek) const { return m_WeekDay <= paramWeek; }
        bool operator != (XInt paramWeek) const { return m_WeekDay != paramWeek; }
        bool operator >  (XInt paramWeek) const { return m_WeekDay >  paramWeek; }
        bool operator <  (XInt paramWeek) const { return m_WeekDay <  paramWeek; }

        ///����ָ��������
        /**
            @param [in] paramDays ָ�����ӵ�����
         */
        void AddDays(XInt paramDays)
        {
            m_WeekDay += paramDays;
            RoundWeek();
        }
        ///����ָ��������
        /**
            @param [in] paramDays ָ����������
         */
        void SubDays(XInt paramDays)
        {
            m_WeekDay -= paramDays;
            RoundWeek();
        }
        ///����ָ��������
        /**
            @param [in] paramDays ָ�����ӵ�����
         */
        XWeek<T> & operator += (XInt paramDays)
        {
            m_WeekDay += paramDays;
            RoundWeek();
            return *this;
        }
        ///����ָ��������
        /**
            @param [in] paramDays ָ����������
         */
        XWeek<T> & operator -= (XInt paramDays)
        {
            m_WeekDay -= paramDays;
            RoundWeek();
            return *this;
        }

        ///����++���������ǰ�����Լ�1��
        /**
         * ��ǰ�����Լ�1��
         * @return ���ؼ�1��ǰ��������
         */
        XWeek<T> & operator++()
        {
            ++ m_WeekDay;
            RoundWeek();
            return *this;
        }
        ///����++���������ǰ�����Լ�1��
        /**
         * ��ǰ�����Լ�1��
         * @return ���ؼ�1ǰ����ʱ����
         */
		XWeek<T> operator++(int)
		{
            XWeek<T> w(*this);
            ++ m_WeekDay;
            RoundWeek();
            return w;
        }
        ///����--���������ǰ�����Լ�1��
        /**
         * ��ǰ�����Լ�1��
         * @return ���ؼ�1��ǰ��������
         */
        XWeek<T> & operator--()
        {
            --m_WeekDay;
            RoundWeek();
            return *this;
        }
        ///����--���������ǰ�����Լ�1��
        /**
         * ��ǰ�����Լ�1��
         * @return ���ؼ�1��ǰ��������
         */
        XWeek<T> operator--(int)
        {
            XWeek<T> w(*this);
            --m_WeekDay;
            RoundWeek();
            return w;
        }
        ///ȡ��ǰ���ڵ�����ֵ
        /**
         * @return ��������ֵ
         */
        XInt GetWeekDay() const
        {
            return m_WeekDay;
        }
    private:
        ///Բ������
        void RoundWeek()
        {
            if( m_WeekDay < WEEKDAY_SUNDAY || m_WeekDay > WEEKDAY_SATURDAY )
            {
                m_WeekDay %= 7;
                if( m_WeekDay < 0 ) m_WeekDay += 7;
            }
        }
    private:
        XInt m_WeekDay; ///<����ֵ��0��6֮��
    };



    //---------------------------------------------------------------------
    /**
        ָ�����ڵĹ��캯��
        @param [in] paramDate ָ��������
     */
    template<class T>
    XDateTime<T>::XDateTime(const XDate<T> & paramDate)
        :m_DateTime( XInt(paramDate) * MILLIS_PRE_DAY64 )
    {}


    //---------------------------------------------------------------------
    /**
        ָ�����ں�ʱ�乹�캯��
        @param [in] paramDate ָ��������
        @param [in] paramTime ָ����ʱ��
     */
    template<class T>
    XDateTime<T>::XDateTime(const XDate<T> & paramDate, const XTime<T> & paramTime)
        :m_DateTime( XInt(paramDate) * MILLIS_PRE_DAY64 + XInt(paramTime))
    {}
    //---------------------------------------------------------------------
    ///����ָ����ʱ��,���ڲ���
    /**
        @param [in] paramTime ָ����ʱ��
     */
    template<class T>
    void XDateTime<T>::SetTime(const XTime<T> & paramTime)
    {
        m_DateTime = m_DateTime - m_DateTime % MILLIS_PRE_DAY + XInt(paramTime);
    }
    //---------------------------------------------------------------------
    ///����ָ�������ڣ�ʱ�䲻��
    /**
      @param [in] paramDate ָ��������
     */
    template<class T>
    void XDateTime<T>::SetDate(const XDate<T> & paramDate)
    {
        m_DateTime = XInt(paramDate) * MILLIS_PRE_DAY64 + m_DateTime % MILLIS_PRE_DAY;
    }
    //---------------------------------------------------------------------
    /**
        ����ָ��������ʱ��
        @param [in] paramDate ָ��������
        @param [in] paramTime ָ����ʱ��
    */
    template<class T>
    void XDateTime<T>::SetDateTime(const XDate<T> & paramDate, const XTime<T> & paramTime)
    {
        m_DateTime = XInt(paramDate) * MILLIS_PRE_DAY64 + XInt(paramTime);
    }
    //---------------------------------------------------------------------
    /**
        ȡ��ǰ����ʱ���ʱ��
     */
    template<class T>
    XTime<T> XDateTime<T>::GetTime() const
    {
        return XTime<T>(XInt(m_DateTime % MILLIS_PRE_DAY64));
    }
    //---------------------------------------------------------------------
    /**
        ȡ��ǰ����ʱ�������
     */
    template<class T>
    XDate<T> XDateTime<T>::GetDate() const
    {
        return XDate<T>(XInt(m_DateTime / MILLIS_PRE_DAY64));
    }
    //---------------------------------------------------------------------
    /**
        ���������ַ���
     */
    template<class T>
    T & XDateTime<T>::ToDateString(T & paramString) const
    {
        XDate<T> dtDate(*this);
        return dtDate.ToString(paramString);
    }
    //---------------------------------------------------------------------
    /**
        ����ʱ���ַ���
     */
    template<class T>
    T & XDateTime<T>::ToTimeString(T & paramString) const
    {
        XTime<T> t(*this);
        return t.ToString(paramString);
    }


    /**
        ������ʱ��ת��Ϊ�ַ���
        YYYY-MM-DD HH:mm:ss.mmm
     */
    template<class T>
    T & XDateTime<T>::ToString(T & paramString) const
    {
        StringChar buff[24];
        paramString = ToString(buff);
        return paramString;
    }
    //---------------------------------------------------------------------
    /**
        ��ϵͳʱ�䣬��Ϊ��ǰ����ʱ��
     */
    template<class T>
    void XDateTime<T>::SetDateTimeToOS() const
    {
        SSystemDateTime s;
        GetSystemDateTime(s);

        XLong lngMillis = m_DateTime + s.Zone * MILLIS_PRE_MINUTE;

        DaysToDate(XInt(lngMillis / MILLIS_PRE_DAY64), s.Year, s.Month, s.Day);
        MillisToTime(XInt(lngMillis % MILLIS_PRE_DAY64), s.Hour, s.Minute, s.Second, s.Milliseconds);
        SetSystemDateTime(s);
    }
    //---------------------------------------------------------------------
    template<class T>
    XDateTime<T>::operator XDate<T>() const
    {
        XDate<T> dt(*this);
        return dt;
    }
    //---------------------------------------------------------------------
    template<class T>
    XDateTime<T>::operator XTime<T>() const
    {
        XTime<T> t(*this);
        return t;
    }
    //---------------------------------------------------------------------
    template<class T>
    XDateTime<T>::operator XWeek<T>() const
    {
        XWeek<T> w(*this);
        return w;
    }
    //---------------------------------------------------------------------
    /**
     * ���������ڵ�ʱ��
     * @param [in] paramDateTime ������ʱ��
     * @return ��������ʱ���ʱ��
     */
    template<class T>
    XDurationTime<T> XDateTime<T>::operator - (const XDateTime<T> & paramDateTime) const
    {
        return XDurationTime<T>(m_DateTime - paramDateTime.m_DateTime );
    }
    //==========================================================================
    //---------------------------------------------------------------------
    /**
     * ����ʱ���ַ���
     */
    //---------------------------------------------------------------------
    template<class T>
    T & XTime<T>::ToString(T & paramString) const
    {
        XInt iHour, iMinute, iSecond, iMillis;
        Decode(iHour, iMinute, iSecond, iMillis);
        StringChar buff[16]; //HH:mm:ss.mmm
        StringChar * p = buff;
        detail::__XX__FastToDateTimeString(p, iHour, 2);
        p += 2;
        *p++=':';
        detail::__XX__FastToDateTimeString(p, iMinute, 2);
        p += 2;
        *p++=':';
        detail::__XX__FastToDateTimeString(p, iSecond, 2);
        p += 2;
        *p++='.';
        detail::__XX__FastToDateTimeString(p, iMillis, 3);
        p += 3;
        *p = 0;
        paramString = buff;
        return paramString;
    }
    //---------------------------------------------------------------------
    /**
     * ���������ַ���
     * @param [out] paramString ���������ַ�������
     * @param [in] aMode �����ַ�����ģʽ
     * @return ���ر��������ַ�������
     */
    template<class T>
    T & XWeek<T>::ToString(T & paramString,XInt aMode) const
    {
        static const XChar * WeekString_1[5][7] =
        {
            {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"},
            {"������", "����һ", "���ڶ�", "������", "������", "������", "������"},
            {"Sun.", "Mon.", "Tues.", "Wed.", "Thurs.", "Fri.", "Sat."},
            {"0", "1", "2", "3", "4", "5", "6"},
            {"��", "һ", "��", "��", "��", "��", "��"}
        };

		paramString =  (const StringChar *)WeekString_1[aMode][m_WeekDay];
		return paramString;
    }
    //--------------------------------------------------------------------------
    template<class T>
    EnumParseDateTimeErrorCode XDurationTime<T>::Parse(const typename XDurationTime<T>::StringChar * paramDuration)
    {
        STime tmpTime;
        XInt iSign;
        StringChar ch;
        for(;;)
        {
            ch = * paramDuration;
            if( string_utils::isSpace(ch) ) paramDuration ++;
            else if( string_utils::isZero(ch)) return X_DATETIME_ERROR_INVALID_DURATION_FORMAT;
            else break;
        }
        //�ж�������
        if( ch == '-' )
        {
            iSign = -1;
            paramDuration ++;
        }
        else if( ch == '+' )
        {
            iSign = 1;
            paramDuration ++;
        }
        else iSign = 1;
        XInt iDays = 0;  //����
        for(;;)
        {
            ch = * paramDuration++;
            if( string_utils::isDigit(ch) )
            {
                iDays *= 10;
                iDays += XInt(ch - '0');
                if( iDays > MAX_DAYS_IN_DATETIME ) return X_DATETIME_ERROR_INVALID_DURATION_DAYS;
            }
            else if( string_utils::isSpace(ch) ) break;
            else return X_DATETIME_ERROR_INVALID_DURATION_FORMAT;
        }
        //����ʱ�䲿��
        if( detail::__XX__FastParseTime(paramDuration, tmpTime) != X_DATETIME_ERROR_OK ) return X_DATETIME_ERROR_INVALID_DURATION_FORMAT;

        if( tmpTime.Hour > 23 ) return X_DATETIME_ERROR_INVALID_HOUR;
        if( tmpTime.Minute > 59 ) return X_DATETIME_ERROR_INVALID_MINUTE;
        if( tmpTime.Second > 59) return X_DATETIME_ERROR_INVALID_SECOND;
        if( tmpTime.Millis > 999) return X_DATETIME_ERROR_INVALID_MILLIS;

        m_Duration = iDays * MILLIS_PRE_DAY64 + (tmpTime.Hour * MILLIS_PRE_HOUR + tmpTime.Minute * MILLIS_PRE_MINUTE + tmpTime.Second * MILLIS_PRE_SECOND + tmpTime.Millis);
        if( iSign < 0 ) m_Duration = - m_Duration;
        return X_DATETIME_ERROR_OK;
    }
    /**
    ���������ַ���
    */
    template<class T>
    T & XDate<T>::ToString(T & paramString) const
    {
        XInt iYear, iMonth, iDay;
        Decode(iYear, iMonth, iDay);
        StringChar buff[16]; //YYYY-MM-DD
        StringChar * p = buff;
        detail::__XX__FastToDateTimeString(p, iYear, 4);
        p += 4;
        *p++='-';
        detail::__XX__FastToDateTimeString(p, iMonth, 2);
        p += 2;
        *p++='-';
        detail::__XX__FastToDateTimeString(p, iDay, 2);
        p += 2;
        *p = 0;
        paramString = buff;
        return paramString;
    }
}




#endif
