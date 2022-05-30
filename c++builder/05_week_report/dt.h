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

    //相关类的前置申明
    template<class T> class XDateTime;      //日期时间类
    template<class T> class XTime;          //时间类
    template<class T> class XDate;          //日期类
    template<class T> class XDurationTime;  //时间长度类
    template<class T> class XWeek;          //星期类

    //日期时间相关的常量定义

    const XLong MAX_MILLIS              = 315537984000000LL;    ///<最大的毫秒数
    const XLong MIN_MILLIS              = 86400000LL;           ///<最小的毫秒数
    const XLong MILLIS_PRE_DAY64        = 86400000LL;           ///<每天最大的毫秒数64位有符号整数
    const XLong MAX_DURATION            = 315537897600000LL;    ///<最大的持续时间

    const XInt MILLIS_PRE_DAY           = 86400000;             ///<每天的毫秒数 24:00:00.000
    const XInt MILLIS_PRE_HOUR          = 3600000;              ///<每小时毫秒数 01:00:00.000
    const XInt MILLIS_PRE_MINUTE        = 60000;                ///<每分钟毫秒数 00:01:00.000
	const XInt MILLIS_PRE_SECOND        = 1000;                 ///<每秒的毫秒数 00:00:01.000

	const XInt DAYS_1970_1_1            = 719163;               ///<1970-1-1到公元元年的天数
	const XLong INVALID_MILLIS_UTC      = 0;                    ///<无效的UTC时间毫秒数
	const XLong INVALID_SECOND_UTC      = 0;                    ///<无效的UTC时间秒数
	const XLong MILLIS_1970_1_1         = 719163LL * 86400000LL ;               ///<1970-1-1到公元元年的天数

    const XInt MAX_MILLIS_IN_DAY        = 86400000;             ///<每天最大的毫秒数
    const XInt MIN_MILLIS_IN_DAY        = 0;                    ///<每天最小的毫秒数

    const XInt MAX_YEAR_IN_DATETIME     = 9999;                 ///<最大的年份
    const XInt MIN_YEAR_IN_DATETIME     = 1;                    ///<最小的年份,公元元年从公元1年开始

    const XInt MAX_MONTH_IN_YEAR        = 12;                   ///<最大的月份
    const XInt MIN_MONTH_IN_YEAR        = 1;                    ///<最小的月份

    const XInt MAX_DAY_IN_MONTH         = 31;                   ///<最大的日期
    const XInt MIN_DAY_IN_MONTH         = 1;                    ///<最小的日期

	const XInt MAX_DAYS_IN_DATETIME     = 3652059;              ///<最大的日期数 9999-12-31
	const XInt MIN_DAYS_IN_DATETIME     = 1;                    ///<最小的日期数 0-1-1

	const XInt TIME_ZONE_CHINA          = -480;                 ///<中国时间东八区

    ///日期时间异常值
    enum EnumDateTimeError
    {
        E_DATETIME_INVALIDATION_DATE    = 1,                    ///<无效的日期
        E_DATETIME_INVALIDATION_TIME,                           ///<无效的时间
        E_DATETIME_INVALIDATION_YEAR,                           ///<无效的年
        E_DATETIME_INVALIDATION_MONTH,                          ///<无效的月
        E_DATETIME_INVALIDATION_DAY,                            ///<无效的日
        E_DATETIME_INVALIDATION_HOUR,                           ///<无效的小时
        E_DATETIME_INVALIDATION_MINUTE,                         ///<无效的分钟
        E_DATETIME_INVALIDATION_SECOND,                         ///<无效的秒
        E_DATETIME_INVALIDATION_MILLIS,                         ///<无效的毫秒
        E_DATETIME_INVALIDATION_DATETIME,                       ///<无效的日期时间
        E_DATETIME_INVALIDATION_DAYS,                           ///<无效的日期数
        E_DATETIME_OUT,                                         ///<日期时间溢出
        E_DATETIME_DAYS_OUT,                                    ///<天数溢出
        E_DATETIME_TIMES_OUT                                    ///<时间溢出
    };
    ///时间日期解析错误信息
    enum EnumParseDateTimeErrorCode
    {
        X_DATETIME_ERROR_OK = 0,                                ///<解析正常
        X_DATETIME_ERROR_INVALID_TIME_FORMAT,                   ///<无效的时间格式
        X_DATETIME_ERROR_INVALID_DATE_FORMAT,                   ///<无效的日期格式
        X_DATETIME_ERROR_INVALID_WEEK_FORMAT,                   ///<无效的星期格式
        X_DATETIME_ERROR_INVALID_CHAR,                          ///<含有无效的字符
        X_DATETIME_ERROR_INVALID_HOUR,                          ///<含有无效的小时
        X_DATETIME_ERROR_INVALID_MINUTE,                        ///<含有无效的分钟
        X_DATETIME_ERROR_INVALID_SECOND,                        ///<含有无效的秒
        X_DATETIME_ERROR_INVALID_MILLIS,                        ///<含有无效的毫秒
        X_DATETIME_ERROR_INVALID_YEAR,                          ///<含有无效年
        X_DATETIME_ERROR_INVALID_MONTH,                         ///<含有无效月
        X_DATETIME_ERROR_INVALID_DAY,                           ///<含有无效天数
        X_DATETIME_ERROR_INVALID_WEEK,                          ///<含有无效星期格式
        X_DATETIME_ERROR_INVALID_DATETIME_FORMAT,               ///<无效的日期时间格式
        X_DATETIME_ERROR_INVALID_DURATION_FORMAT,               ///<无效的时长串
        X_DATETIME_ERROR_INVALID_DURATION_DAYS,                 ///<无效的时长天数
    };
    //星期相关的常量
    enum EnumWeekDay
    {
        WEEKDAY_SUNDAY              = 0,                        ///<星期日
        WEEKDAY_MONDAY              = 1,                        ///<星期一
        WEEKDAY_TUESDAY             = 2,                        ///<星期二
        WEEKDAY_WEDNESDAY           = 3,                        ///<星期三
        WEEKDAY_THURSDAY            = 4,                        ///<星期四
        WEEKDAY_FRIDAY              = 5,                        ///<星期五
        WEEKDAY_SATURDAY            = 6,                        ///<星期六
    };
    ///日期时间结构
    struct SSystemDateTime
    {
        XInt Year;          ///<年
        XInt Month;         ///<月
        XInt Day;           ///<日
        XInt WeekDay;       ///<星期
        XInt Hour;          ///<时
        XInt Minute;        ///<分
        XInt Second;        ///<秒
        XInt Milliseconds;  ///<毫秒
        XShort Zone;        ///<时区,单位分钟
    };
    ///日期结构体
    struct SDate
    {
        XInt Year;  ///<年份
        XInt Month; ///<月份
        XInt Day;   ///<日期
    };
    ///时间构构体
    struct STime
    {
        XInt Hour;      ///<小时
        XInt Minute;    ///<分
        XInt Second;    ///<秒
        XInt Millis;    ///<毫秒
    };

    //---------------------------------------------------------------------------------------------------
    ///异常类基类
    class EException
    {
    public:
        ///默认构造函数
        EException()
            :m_HelpContext(0)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        EException(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :m_Message(paramMessage),
             m_HelpContext(paramHelpContext)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        EException(const XChar* paramMessage, XInt paramHelpContext = 0)
            :m_Message(paramMessage),
            m_HelpContext(paramHelpContext)
        {}
        ///析构函数
        virtual ~EException()
        {}
        ///取异常信息
        const XAnsiString getMessage() const
        {
            return m_Message;
        }
        ///设置异常信息
        void setMessage(const XChar * paramMessage)
        {
            m_Message = paramMessage;
        }
        ///设置异常信息
        void setMessage(const XAnsiString & paramMessage)
        {
            m_Message = paramMessage;
        }
        ///取帮助信息ID
        XInt getHelpContext() const
        {
            return m_HelpContext;
        }
        ///设置帮助信息ID
        void setHelpContext(XInt paramHelpContext)
        {
            m_HelpContext = paramHelpContext;
        }
        ///转换成字符串指针
        operator const XChar *() const
        {
            return m_Message.c_str();
        }
    private:
        XAnsiString m_Message;  ///<异常信息
        XInt m_HelpContext;     ///<帮助信息ID
    };

    #define MESSAGE_OUT_OF_MEMORY "out of memory"
    #define MESSAGE_NOT_EXISTS "not exists object!"
    #define MESSAGE_IS_ZERO "is zero"
    #define MESSAGE_LESS_THAN_ZERO "less than zero"
    #define MESSAGE_CONVERT_FAIL "Type convert fail"
    #define MESSAGE_GREATER_THAN_ZERO "greater than zero"
    #define MESSAGE_OUT_OF_RANGE "out of range:index=%d,length=%d"

    ///内存溢出异常
    class XEOutOfMemory : public EException
    {
    public:
        ///默认构造函数
        XEOutOfMemory()
            :EException(MESSAGE_OUT_OF_MEMORY)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        XEOutOfMemory(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        XEOutOfMemory(const XChar* paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///析构函数
        ~XEOutOfMemory()
        {
        }
    };
    //---------------------------------------------------------------------
    class XEConvert : public EException
    {
    public:
        ///默认构造函数
        XEConvert()
            :EException(MESSAGE_CONVERT_FAIL)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        XEConvert(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        XEConvert(const XChar* paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///析构函数
        ~XEConvert()
        {
        }
    };


    ///数组越界异常
    class XEOutOfRange : public EException
    {
    public:
        ///数组越界异常构造函数
        /**
            @param [in] paramIndex 越界的下标值
            @param [in] aLength 被越界的数组的长度
        */
        XEOutOfRange(XInt paramIndex = 0,XInt aLength = 0)
            :m_Index(paramIndex),m_Length(aLength)
        {
            MakeMsg();
        }
        ///析构函数
        ~XEOutOfRange(){}
        ///设置越界信息
        /**
            @param [in] paramIndex 越界的下标值
            @param [in] aLength 被越界的数组的长度
        */
        void setInfo(XInt paramIndex,XInt aLength)
        {
            m_Index = paramIndex;
            m_Length = aLength;
            MakeMsg();
        }
        ///取越界的下标值
        /**
            @return 返回越界的下标值
         */
        XInt getIndex() const { return m_Index; }
        ///取被越界的数组的长度
        /**
            @return 返回被越界的长度
         */
        XInt getLength() const { return m_Length; }
    protected:
        ///生成异常信息
        void MakeMsg()
        {
            XAnsiString strMsg;
            strMsg.printf(MESSAGE_OUT_OF_RANGE,m_Index,m_Length);
            setMessage(strMsg);
        }
    private:
        XInt m_Index;  ///<越界的下标
        XInt m_Length; ///<被越界的数组的下标
    };
    ///值为零异常类
    class XEIsZero : public EException
    {
    public:
        XEIsZero()
            :EException(MESSAGE_IS_ZERO)
        {}
    };
    ///值小于零异常类
    class XELessThanZero : public EException
    {
    public:
        XELessThanZero()
            :EException(MESSAGE_LESS_THAN_ZERO)
        {}
    };
    ///值大于零异常类
    class XEGreatherThanZero : public EException
    {
    public:
        XEGreatherThanZero()
            :EException(MESSAGE_GREATER_THAN_ZERO)
        {}
    };
    ///不存在异常类
    class XENotExists : public EException
    {
    public:
        XENotExists()
            :EException(MESSAGE_NOT_EXISTS)
        {}
    };

    //============================================================================
    /**
     * 这是一个用于抛出时间异常的类
     * @par sample
     * @code
     * XEXDateTimeError Example;
     * cout<<Example.getMsg()<<endl;
     * @endcode
     * @author 祝冬华
     * @version 4.0
     * @date 2008-04-06
     */
    class EDateTimeError : public EException
    {
    public:
        ///构造函数
        /**
         * @param paramInvalidation 无效的原因
         * @param paramInvalidValue 无效的值
         * @param iHelpContext 帮助ID
         */
        EDateTimeError(EnumDateTimeError paramInvalidation = E_DATETIME_INVALIDATION_DATETIME, XInt paramInvalidValue = 0)
            :m_Invalidation(paramInvalidation), m_InvalidValue(paramInvalidValue)
        {
            ResetErrorMsg();
        }
        ///取无效的值
        XInt getInvalidValue() const
        {
            return m_InvalidValue;
        }
        ///取无效的原因
        /**
         * @return 返回无效的原因
         */
        EnumDateTimeError getInvalidation() const
        {
            return m_Invalidation;
        }
        ///设置无效内容
        /**
         * @param paramInvalidation 无效的原因
         * @param paramInvalidValue 无效的值
         */
        void SetInvalidation(EnumDateTimeError paramInvalidation, XInt paramInvalidValue = 0)
        {
            m_Invalidation = paramInvalidation;
            m_InvalidValue = paramInvalidValue;
            ResetErrorMsg();
        }
    private:
        ///重设错误信息
        void ResetErrorMsg()
        {
            XAnsiString strMsg;
            //strMsg.ensureCapacity(64);

            //根据不同原因，生成错误信息
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
			setMessage(strMsg); //生成错误信息
		}
	private:
		EnumDateTimeError m_Invalidation;       ///<无效的原因
        XInt m_InvalidValue;                ///<无效的值
    };

    //函数前置申明
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
        //这个名称空间的函数，都是这个这个里面专用的函数，请不要直接使用这里面的函数
        ///取当前时间毫秒数
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
        * 取系统时间
        * @param [out] paramST 用于保存取得的日期时间
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
			paramST.Zone = TIME_ZONE_CHINA; //默认时区为东八区
			TIME_ZONE_INFORMATION tz;
			if(GetTimeZoneInformation(&tz) == TIME_ZONE_ID_STANDARD )
			{
				paramST.Zone = (XShort)tz.StandardBias;
			}
		}

        //----------------------------------------------------------------------------
        /**
            设置当前系统时间,如果在Linux下,没有Root权限,将会设置失败,已经经过测试
            @param [in] paramST 当前要设置的时间
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
        * 计算指定年月的天数
        * @param [in] paramYear 指定的年份，有效的年份是[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]之间
        * @param [in] paramMonth 指定的月份，有效的月份是[1,12]之间
        * @param [in] paramCheck 检查年月标志,
        *     - true 表示要检查paramYear和paramMonth是否有效
        *     - false 表示不需要检查paramYear和paramMonth是否有效
        * @return 返回计算出来指定月份的天数
        * @exception XEDateTimeError 如果年份、月份无效，则抛出异常
        */
        inline XInt CalcMonthDays(XInt paramYear, XInt paramMonth, bool paramCheck)
		{
            XInt iRet;
            if( paramCheck ) //如果要检查年月
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
        * 计算从元年1月1日开始的天数
        * @param [in] paramYear 指定的年份，有效的年份是[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]之间
        * @param [in] paramMonth 指定的月份，有效的月份是[1,12]之间
        * @param [in] paramDay 指定的日期，有效的日期是[1,CalcMonthDays]之间
        * @return 返回指定日期从元年1月1日开始的天数
        * @exception XEDateTimeError 如果年份、月份、日期无效，则抛出异常
        */
        inline XInt CalcDays(XInt paramYear, XInt paramMonth, XInt paramDay)
		{
            //检查年份
            if( paramYear < MIN_YEAR_IN_DATETIME || paramYear > MAX_YEAR_IN_DATETIME ) throw EDateTimeError(E_DATETIME_INVALIDATION_YEAR,paramYear);
            //检查月份
            if( paramMonth < MIN_MONTH_IN_YEAR || paramMonth > MAX_MONTH_IN_YEAR ) throw EDateTimeError(E_DATETIME_INVALIDATION_MONTH,paramMonth);
            //检查日期
            XInt aMonthDays = CalcMonthDays(paramYear, paramMonth, false);

            if( paramDay < MIN_DAY_IN_MONTH || paramDay > aMonthDays ) throw EDateTimeError(E_DATETIME_INVALIDATION_DAY,paramDay);

            XInt iDays = 0;

            for(XInt i=1; i<paramMonth; i++) iDays += CalcMonthDays(paramYear, i, false);

            paramYear --;
            iDays += ( (paramYear*365) + (paramYear/4) - (paramYear/100) + (paramYear/400)); //加上往年的天数
            iDays += paramDay;                                                   //加上当前月的天数
            return iDays;
        }

        //----------------------------------------------------------------------------
        /**
            将天数转换成年月日
            @param [in] paramDays 要转换的天数
            @param [out] paramYear 转换后的年份
            @param [out] paramMonth 转换后的月份
            @param [out] aday 转换后的天数
        */
        inline void DaysToDate(XInt paramDays,XInt &paramYear,XInt &paramMonth,XInt & paramDay)
		{
            if( paramDays < MIN_DAYS_IN_DATETIME || paramDays > MAX_DAYS_IN_DATETIME) throw EDateTimeError(E_DATETIME_DAYS_OUT,paramDays);
            XInt N400 = paramDays / 146097; //400年的年数
            XInt D = paramDays % 146097;
            XInt N100 = D / 36524;      //100年的年数
            D %= 36524;
            XInt N4 = D / 1461;         //每四年的年数
            D %= 1461;
            XInt N = D / 365;           //具体年数
            D %= 365;
            XInt NYear = N400 * 400 + N100 * 100 + N4 * 4 + N;  //闰年的天数
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
        //datetime私有的函数,请不要在这个文件之外使用
        ///检查是否为日期的分隔符
        template<class T>
        inline bool __isDateSplit(T paramV)
        {
            return ( paramV == '-' || paramV =='\\' || paramV =='/' );
        }
        //---------------------------------------------------------------------
        ///检查是否为日期的结束字符
        template<class T>
        inline bool __isEnd(T paramV)
        {
            return ( paramV == 0 || paramV == ' ');
        }
        //---------------------------------------------------------------------
        /**
            生成日期时间类的整数转换为字符串.
            这个函数仅用于XDateTime.cpp这个文件中,仅生成指定宽的串,并且不会将最后的字符设为0.
            这个函数用于特别的优化
            @param [in] paramBuffer 指定的缓冲区
            @param [in] paramValue 要转换的整数
            @param [in] paramWidth 转换后字符串的宽度，不足补零
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
            生成日期时间类的字符串转换为整数的函数.
            这个函数仅用于XDateTime.cpp这个文件中,仅转换指定宽度的字符串.
            这个函数用于特别的优化
            @param [in] paramBuffer 指定的缓冲区
            @param [in] paramWidth 指定整数串的宽度,该值在[1,4]之间
            @return 返回转换后的结果
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
            快速解析时间的函数,适用于HH:MM:SS.mmm和HH:MM和HH:MM:SS格式的时间
            @param [in] paramTime 指定的缓冲区
            @param [out] paramTimeRet 存放解析的结果
            @return 返回错误信息
                - X_DATETIME_ERROR_OK 表示解析成功
                - X_DATETIME_ERROR_INVALID_TIME_FORMAT 表示解析成失败,是无效的时间格式
         */
        template<class T>
        static EnumParseDateTimeErrorCode __XX__FastParseTime(const T * paramTime, STime & paramTimeRet)
        {
            XInt iWidth = 0;
            const T * p  = paramTime;
            for(;;) //计算小时
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
            for(;;) //计算分钟
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
                else if( __isEnd(ch) ) //如果没有秒数,提前结束了
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
            for(;;) //计算秒
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
                else if( __isEnd(ch) ) //如果没有毫秒数
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
            for(;;) //计算毫秒
            {
                T ch = *p++;
                if( string_utils::isDigit(ch) )
                {
                    iWidth ++;
                    if( iWidth > 3) return X_DATETIME_ERROR_INVALID_TIME_FORMAT;
                }
                else if( __isEnd(ch) ) //如果没有毫秒数
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
            快速解析日期的函数,适用于YYYY-MM-DD,YYYY/MM/DD,YYYY\MM\DD等格式的日期
            @param [in] paramDate 指定的日期串
            @param [out] paramDateEnd 解析日期串后，指针的位置
            @param [out] paramDateRet 存放解析的结果
            @return 返回错误信息
                - X_DATETIME_ERROR_OK 表示解析成功
                - X_DATETIME_ERROR_INVALID_DATE_FORMAT 表示解析成失败,是无效的日期格式
         */
        template<class T>
        static EnumParseDateTimeErrorCode __XX__FastParseDate(const T * paramDate, const T * & paramDateEnd, SDate & paramDateRet)
        {
            XInt iWidth = 0;
            const T * p = paramDate;
            T chSplit;
            for(;;) //计算年份
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
            for(;;) //计算月份
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
            for(;;) //计算日期
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
                        return X_DATETIME_ERROR_OK; //返回结果
                    }
                    return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
                }
                else return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
            }
		}
	}

	//============================================================================
	//全局函数
	//----------------------------------------------------------------------------
	///取当前时间毫秒数
	/**
	 * 取当前的毫秒数
	 * @return 返回当前日期时间的毫秒数
	 */
	inline XLong GetNowDateTime()
	{
		return detail::GetNowDateTime();
	}



	//----------------------------------------------------------------------------
	///取系统时间
	inline void GetSystemDateTime(SSystemDateTime & paramST)
    {
        detail::GetSystemDateTime(paramST);
    }
    //----------------------------------------------------------------------------
    ///设置系统时间
    inline void SetSystemDateTime(const SSystemDateTime & paramST)
    {
        detail::SetSystemDateTime(paramST);
    }
    //----------------------------------------------------------------------------
    ///将天数转换成年月日
    /**
        将天数转换成年月日
        @param [in] paramDays 要转换的天数
        @param [out] paramYear 转换后的年份
        @param [out] paramMonth 转换后的月份
        @param [out] paramDay 转换后的天数
        @exception XEDateTimeError 日期超过有效范围，会抛出异常
    */
    inline void DaysToDate(XInt paramDays, XInt &paramYear, XInt &paramMonth, XInt & paramDay)
    {
        detail::DaysToDate(paramDays, paramYear, paramMonth, paramDay);
    }
    //----------------------------------------------------------------------------
    ///将天数转换成日期
    /**
        将天数转换成日期
        @param [in] paramDays 要转换的天数
        @param [out] paramDate 转换后的日期
        @exception XEDateTimeError 日期超过有效范围，会抛出异常
    */
    inline void DaysToDate(XInt paramDays, SDate & paramDate)
    {
        DaysToDate(paramDays, paramDate.Year, paramDate.Month, paramDate.Day);
    }
    //----------------------------------------------------------------------------
    ///计算指定年月的天数
    /**
     * 计算指定年月的天数
     * @param [in] paramYear 指定的年份，有效的年份是[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]之间，其值在[1,9999]之间
     * @param [in] paramMonth 指定的月份，有效的月份是[1,12]之间
     * @param [in] bCheck 检查年月标志,
     *     - true 表示要检查paramYear和paramMonth是否有效
     *     - false 表示不需要检查paramYear和paramMonth是否有效
     * @return 返回计算出来指定月份的天数
     * @exception XEDateTimeError 如果年份、月份无效，则抛出异常
     */
    inline XInt CalcMonthDays(XInt paramYear, XInt paramMonth, bool bCheck = true)
    {
        return detail::CalcMonthDays(paramYear,paramMonth,bCheck);
    }
    //----------------------------------------------------------------------------
    ///计算从元年1月1日开始的天数
    /**
     * 计算从元年1月1日开始的天数
     * @param [in] paramYear 指定的年份，有效的年份是[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]之间，其值在[1,9999]之间
     * @param [in] paramMonth 指定的月份，有效的月份是[1,12]之间
     * @param [in] paramDay 指定的日期，有效的日期是[1,CalcMonthDays]之间
     * @return 返回指定日期从无年1月1日开始的天数
     * @exception XEDateTimeError 如果年份、月份、日期无效，则抛出异常
     */
    inline XInt CalcDays(XInt paramYear, XInt paramMonth, XInt paramDay)
    {
        return detail::CalcDays(paramYear,paramMonth,paramDay);
    }
    //----------------------------------------------------------------------------
    ///判断是否是闰年
    /**
     * 判断是否是闰年
     * @param [in] paramYear 被检查的年份，有效的年份是[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]之间，其值在[1,9999]之间
     * @return 返回判断结断
     *   - true 表示是闰年
     *   - false 表示不是闰年
     * @exception XEXDateTimeError 如果年份无效，则抛出异常
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
    ///计算指定时间的毫秒数
    /**
     * 计算指定时间的毫秒数
     * @param [in] paramHour 小时，其值在[0,23]之间
     * @param [in] paramMinute 分钟，其值在[0,59]之间
     * @param [in] paramSecond 秒，其值在[0,59]之间
     * @param [in] paramMillis 毫秒，其值在[0,999]之间
     * @return 返回计算出来的总毫秒数
     * @exception XEXDateTimeError 如果错误，则抛出异常。
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
    ///计算指定日期时间的毫秒数
    /**
     * 计算指定时间的毫秒数
     * @param [in] paramYear 年份，其值在[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]之间,其值在[1,9999]之间
     * @param [in] paramMonth 月份，其值在[1,12]之间
     * @param [in] paramDay 日期，其值在[1,31]之间，具体还要视不同的月份和闰年区分
     * @param [in] paramHour 小时，其值在[0,23]之间
     * @param [in] paramMinute 分钟，其值在[0,59]之间
     * @param [in] paramSecond 秒，其值在[0,59]之间
     * @param [in] paramMillis 毫秒，其值在[0,999]之间
     * @return 返回计算出来的总毫秒数
     * @exception XEXDateTimeError 如果错误，则抛出异常。
     */
    inline XLong CalcMillis(XInt paramYear, XInt paramMonth, XInt paramDay,
        XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0)
    {
        return CalcDays(paramYear, paramMonth, paramDay) * MILLIS_PRE_DAY64
            + CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis);
    }
    //----------------------------------------------------------------------------
    ///将毫秒数转换为时、分、秒、毫秒
    /**
     * 将毫秒数转换为时、分、秒、毫秒
     * @param [in] paramMillisCount 总毫秒数，该值的范围是[0,MILLIS_PRE_DAY)
     * @param [out] paramHour 返回计算出来的小时
     * @param [out] paramMinute 返回计算出来的分钟
     * @param [out] paramSecond 返回计算出来的秒
     * @param [out] paramMillis 返回计算出来的毫秒
     * @exception XEXDateTimeError 如果超出有效的毫秒范围，则抛出异常
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
    ///将毫秒数转换为时间构结体STime
    /**
     * 将毫秒数转换为时间构结体STime
     * @param [in] paramMillisCount 总毫秒数，该值的范围是[0,MILLIS_PRE_DAY)
     * @param [out] paramTime 返回计算出来的时间
     * @exception XEXDateTimeError 如果超出有效的毫秒范围，则抛出异常
     */
    inline void MillisToTime(XInt paramMillisCount, STime & paramTime)
    {
        MillisToTime(paramMillisCount, paramTime.Hour, paramTime.Minute, paramTime.Second, paramTime.Millis);
    }
    //----------------------------------------------------------------------------
    ///将日期时间转换为年、月、日、时、分、秒、毫秒
    /**
     * @param [in] paramMillisCount 日期时间的毫秒数
     * @param [out] paramYear 返回计算出年份
     * @param [out] paramMonth 返回计算出的月份
     * @param [out] paramDay 返回计算出的日期
     * @param [out] paramHour 返回计算出来的小时
     * @param [out] paramMinute 返回计算出来的分钟
     * @param [out] paramSecond 返回计算出来的秒
     * @param [out] paramMillis 返回计算出来的毫秒
     * @exception XEXDateTimeError 如果超出有效的毫秒范围，则抛出异常
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
        解析日期时间
        @param [in] paramDateTime 日期时间串,适用于YYYY-MM-DD HH:MM:SS.mmm 和 YYYY/MM/DD HH:MM:SS.mmm 格式的日期时间串
        @param [out] paramDate 保存解析后的日期: YYYY, MM, DD
        @param [out] paramTime 保存解析后的时间: HH, MM, SS, mmm
        @return 返回结果结果
            - X_DATETIME_ERROR_OK 表示解析成功
            - 其它值 表示解析失败
     */
    template<class T>
    static EnumParseDateTimeErrorCode ParseDateTime(const T * paramDateTime, SDate & paramDate, STime & paramTime)
    {
        SDate tmpDate;
        STime tmpTime;
        const T * TimeStart;
        for(;;) //去除导前空格
        {
            T ch = *paramDateTime;
            if( string_utils::isSpace(ch) ) paramDateTime++;
            else if( string_utils::isZero(ch) ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
            else break;
        }
        //解析日期
        if( detail::__XX__FastParseDate(paramDateTime, TimeStart, tmpDate) != X_DATETIME_ERROR_OK ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
        //检查日期
        //检查年份
        if( tmpDate.Year < MIN_YEAR_IN_DATETIME || tmpDate.Year > MAX_YEAR_IN_DATETIME ) return X_DATETIME_ERROR_INVALID_YEAR;
        //检查月份
        if( tmpDate.Month < MIN_MONTH_IN_YEAR || tmpDate.Month > MAX_MONTH_IN_YEAR ) return X_DATETIME_ERROR_INVALID_MONTH;
        //检查日期
        if( tmpDate.Day < MIN_DAY_IN_MONTH || tmpDate.Day > CalcMonthDays(tmpDate.Year,tmpDate.Month) ) return X_DATETIME_ERROR_INVALID_DAY;
        //解析时间
        if( detail::__XX__FastParseTime(TimeStart,tmpTime) != X_DATETIME_ERROR_OK ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
        //检查小时
        if( tmpTime.Hour > 23 ) return X_DATETIME_ERROR_INVALID_HOUR;
        //检查分钟
        if( tmpTime.Minute > 59 ) return X_DATETIME_ERROR_INVALID_MINUTE;
        //检查秒
        if( tmpTime.Second > 59 ) return X_DATETIME_ERROR_INVALID_SECOND;
        //检查毫秒
        if( tmpTime.Millis > 999) return X_DATETIME_ERROR_INVALID_MILLIS;
        paramDate = tmpDate;
        paramTime = tmpTime;
        return X_DATETIME_ERROR_OK;
    }
    //---------------------------------------------------------------------
    /**
        解析日期
        @param [in] paramDate 日期时间串,适用于YYYY-MM-DD HH:MM:SS.mmm 、YYYY-MM-DD 和 YYYY/MM/DD 格式的日期时间串
        @param [out] paramDateRet 保存解析后的日期: YYYY, MM, DD
        @return 返回结果结果
            - X_DATETIME_ERROR_OK 表示解析成功
            - 其它值 表示解析失败
     */
    template<class T>
    static EnumParseDateTimeErrorCode ParseDate(const T * paramDate, SDate & paramDateRet)
    {
        SDate tmpDate;
        const T * TimeStart;
        for(;;) //去除导前空格
        {
            T ch = *paramDate;
            if( string_utils::isSpace(ch) ) paramDate++;
            else if( string_utils::isZero(ch) ) return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
            else break;
        }
        //解析日期
        if( detail::__XX__FastParseDate(paramDate, TimeStart, tmpDate) != X_DATETIME_ERROR_OK ) return X_DATETIME_ERROR_INVALID_DATE_FORMAT;
        //检查日期
        //检查年份
        if( tmpDate.Year < MIN_YEAR_IN_DATETIME || tmpDate.Year > MAX_YEAR_IN_DATETIME ) return X_DATETIME_ERROR_INVALID_YEAR;
        //检查月份
        if( tmpDate.Month < MIN_MONTH_IN_YEAR || tmpDate.Month > MAX_MONTH_IN_YEAR ) return X_DATETIME_ERROR_INVALID_MONTH;
        //检查日期
        if( tmpDate.Day < MIN_DAY_IN_MONTH || tmpDate.Day > CalcMonthDays(tmpDate.Year, tmpDate.Month) ) return X_DATETIME_ERROR_INVALID_DAY;
        paramDateRet = tmpDate;
        return X_DATETIME_ERROR_OK;
    }
    //---------------------------------------------------------------------
    /**
        解析时间
        @param [in] paramTime 时间串,适用于HH:MM:SS.mmm 、HH:MM:SS 和 HH:MM格式的时间串
        @param [out] paramTimeRet 保存解析后的时间: HH, MM, SS, mmm
        @return 返回结果结果
            - X_DATETIME_ERROR_OK 表示解析成功
            - 其它值 表示解析失败
     */
    template<class T>
    static EnumParseDateTimeErrorCode ParseTime(const T * paramTime, STime & paramTimeRet)
    {
        STime tmpTime;
        for(;;) //去除导前空格
        {
            T ch = *paramTime;
            if( string_utils::isSpace(ch) ) paramTime++;
            else if( string_utils::isZero(ch) ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
            else break;
        }
        if( detail::__XX__FastParseTime(paramTime, tmpTime) != X_DATETIME_ERROR_OK ) return X_DATETIME_ERROR_INVALID_DATETIME_FORMAT;
        //检查小时
        if( tmpTime.Hour > 23 ) return X_DATETIME_ERROR_INVALID_HOUR;
        //检查分钟
        if( tmpTime.Minute > 59 ) return X_DATETIME_ERROR_INVALID_MINUTE;
        //检查秒
        if( tmpTime.Second > 59 ) return X_DATETIME_ERROR_INVALID_SECOND;
        //检查毫秒
        if( tmpTime.Millis > 999) return X_DATETIME_ERROR_INVALID_MILLIS;
        paramTimeRet = tmpTime;
        return X_DATETIME_ERROR_OK;
    }
    //---------------------------------------------------------------------
    ///取指定天数的毫秒数
    /**
        这组方法包括Days,Hours,Minutes,Seconds四个方法，通过这个方法，我们可以使用
        XDateTime的+=和-=来增加和减少指定的时间
        <code>
            XDateTime dt;
            dt.SetNow();
            dt += Days(2);      //增加两天的时间
            dt += Hours(2);     //增加两小时的时间
            dt += Minutes(2);   //增加两分钟的时间
            dt += Seconds(2);
        <endcode>
     */
    inline XLong Days(XInt paramDays = 1)
    {
        return MILLIS_PRE_DAY64 * paramDays;
    }
    //---------------------------------------------------------------------
    ///取指定小时数的毫秒数
    /**
        这组方法包括Days,Hours,Minutes,Seconds四个方法，通过这个方法，我们可以使用
        XDateTime的+=和-=来增加和减少指定的时间
        <code>
            XDateTime dt;
            dt.SetNow();
            dt += Days(2);      //增加两天的时间
            dt += Hours(2);     //增加两小时的时间
            dt += Minutes(2);   //增加两分钟的时间
            dt += Seconds(2);
        <endcode>
     */
    inline XInt Hours(XInt paramHour = 1)
    {
        return MILLIS_PRE_HOUR * paramHour;
    }
    //---------------------------------------------------------------------
    ///取指定分钟数的毫秒数
    /**
        这组方法包括Days,Hours,Minutes,Seconds四个方法，通过这个方法，我们可以使用
        XDateTime的+=和-=来增加和减少指定的时间
        <code>
            XDateTime dt;
            dt.SetNow();
            dt += Days(2);      //增加两天
            dt += Hours(2);     //增加两小时的时间
            dt += Minutes(2);   //增加两分钟的时间
            dt += Seconds(2);
        <endcode>
     */
    inline XInt Minutes(XInt paramMinute = 1)
    {
        return MILLIS_PRE_MINUTE * paramMinute;
    }
    //---------------------------------------------------------------------
    ///取指定秒数的毫秒数
    /**
        这组方法包括Days,Hours,Minutes,Seconds四个方法，通过这个方法，我们可以使用
        XDateTime的+=和-=来增加和减少指定的时间
        <code>
            XDateTime dt;
            dt.SetNow();
            dt += Days(2);      //增加两天的时间
            dt += Hours(2);     //增加两小时的时间
            dt += Minutes(2);   //增加两分钟的时间
            dt += Seconds(2);
        <endcode>
     */
    inline XInt Seconds(XInt paramSecond = 1)
    {
        return MILLIS_PRE_SECOND * paramSecond;
    }

    namespace utc
    {
        ///取当前格林威志时间的秒数
        inline XLong GetUTCTimeLong()
        {
            return XLong(time(NULL));
		}
        ///取格林威志的毫秒数
        inline XLong GetUTCTimeMillisLong()
        {
				SYSTEMTIME st;
				GetSystemTime(&st);
				XLong lngNow = CalcMillis(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
				return lngNow - DAYS_1970_1_1 * MILLIS_PRE_DAY64;
		}

		///取时区信息
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

        ///1970年来UTC秒数
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
            //赋值
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
            //比较类的函数
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

        ///取当前的UTC时间
		inline XUTCTime GetUTCTime()
        {
			return XUTCTime(GetUTCTimeLong());
		}

        ///1970年来UTC毫秒数
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
            //赋值
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
            //比较类的函数
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
        ///取当前的UTC时间，毫秒数
        inline XUTCTimeMillis GetUTCTimeMillis()
        {
            return XUTCTimeMillis(GetUTCTimeMillisLong());
        }
    }
    ///日期时间类
    /**
        一个精确到毫秒的日期时间类。实现这个类的目的主要是方便日期时间的使用和计算。
        这个类存放时间的是一个64位整数，单位毫秒。SetNowDateTime()，可以取得系统的当前日期时间。SetDateTimeToOS，可以将系统的日期时间设为该日期时间。
     */
    template<class T = XAnsiString>
    class XDateTime
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///指定日期时间毫秒数的构造函数
        /**
            @param [in] paramDateTime 指定的日期时间毫秒数
         */
        XDateTime(XLong paramDateTime = DAYS_1970_1_1 * MILLIS_PRE_DAY64 )
            :m_DateTime(paramDateTime)
        {
            RoundDateTime();
        }
        ///默认拷贝构造函数
        /**
            @param [in] paramDateTime 默认拷贝的日期时间
         */
        XDateTime(const XDateTime<T> & paramDateTime)
            :m_DateTime(paramDateTime.m_DateTime)
        {}
        ///指定时间日期时间的构造函数
        /**
         * @param [in] paramYear 年份，其值在[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]之间
         * @param [in] paramMonth 月份，其值在[1,12]之间
         * @param [in] paramDay 日期，其值在[1,31]之间，具体还要视不同的月份和闰年区分
         * @param [in] paramHour 小时，其值在[0,23]之间
         * @param [in] paramMinute 分钟，其值在[0,59]之间
         * @param [in] paramSecond 秒，其值在[0,59]之间
         * @param [in] paramMillis 毫秒，其值在[0,999]之间
         * @exception XEXDateTimeError 有错误，则抛出异常
         */
        XDateTime(XInt paramYear, XInt paramMonth, XInt paramDay,
            XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0 )
            :m_DateTime(CalcMillis(paramYear, paramMonth, paramDay,
                paramHour, paramMinute, paramSecond, paramMillis))
        {
        }
        ///指定日期的构造函数
        XDateTime(const XDate<T> & paramDate);
        ///指定日期和时间构造函数
        XDateTime(const XDate<T> & paramDate, const XTime<T> & paramTime);
        ///将日期时间转换为64位整数的毫秒数
        operator XLong() const { return m_DateTime; }
        ///设置指定的时间,日期不变
        /**
         * @param [in] paramHour 小时，其值在[0,23]之间
         * @param [in] paramMinute 分钟，其值在[0,59]之间
         * @param [in] paramSecond 秒，其值在[0,59]之间
         * @param [in] paramMillis 毫秒，其值在[0,999]之间
         * @exception XEXDateTimeError 有错误，则抛出异常
         */
        void SetTime(XInt paramHour = 0,XInt paramMinute = 0,XInt paramSecond = 0,XInt paramMillis = 0)
        {
            m_DateTime = m_DateTime - m_DateTime % MILLIS_PRE_DAY
                + CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///设置指定的时间,日期不变
        /**
         * @param [in] paramTime 有效的时间
         * @exception XEXDateTimeError 有错误，则抛出异常
         */
        void SetTime(const STime & paramTime)
        {
            m_DateTime = m_DateTime - m_DateTime % MILLIS_PRE_DAY
                + CalcMillisByTime(paramTime.Hour, paramTime.Minute, paramTime.Second, paramTime.Millis);
        }
        ///设置指定的时间,日期不变
        void SetTime(const XTime<T> & paramTime);
        ///设置指定的日期，时间不变
        /**
         * @param [in] paramYear 年份，其值在[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]之间
         * @param [in] paramMonth 月份，其值在[1,12]之间
         * @param [in] paramDay 日期，其值在[1,31]之间，具体还要视不同的月份和闰年区分
         * @exception XEXDateTimeError 有错误，则抛出异常
         */
        void SetDate(XInt paramYear, XInt paramMonth, XInt paramDay)
        {
            m_DateTime = CalcDays(paramYear, paramMonth, paramDay) * MILLIS_PRE_DAY64
                + m_DateTime % MILLIS_PRE_DAY64;
        }
        ///设置指定的日期，时间不变
        /**
         * @param [in] paramDate 有效的日期
         * @exception XEXDateTimeError 有错误，则抛出异常
         */
        void SetDate(const SDate & paramDate)
        {
            m_DateTime = CalcDays(paramDate.Year, paramDate.Month, paramDate.Day) * MILLIS_PRE_DAY64
                + m_DateTime % MILLIS_PRE_DAY64;
        }
        ///设置指定的日期，时间不变
        void SetDate(const XDate<T> & paramDate);
        ///设置指定的日期时间
        /**
         * @param [in] paramYear 年份，其值在[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]之间
         * @param [in] paramMonth 月份，其值在[1,12]之间
         * @param [in] paramDay 日期，其值在[1,31]之间，具体还要视不同的月份和闰年区分
         * @param [in] paramHour 小时，其值在[0,23]之间
         * @param [in] paramMinute 分钟，其值在[0,59]之间
         * @param [in] paramSecond 秒，其值在[0,59]之间
         * @param [in] paramMillis 毫秒，其值在[0,999]之间
         * @exception XEXDateTimeError 有错误，则抛出异常
         */
        void SetDateTime(XInt paramYear, XInt paramMonth, XInt paramDay, XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0)
        {
            m_DateTime = CalcMillis(paramYear, paramMonth, paramDay, paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///设置指定的日期时间
        /**
         * @param [in] paramDate 有效的日期
         * @param [in] paramTime 有效的时间
         * @exception XEXDateTimeError 有错误，则抛出异常
         */
        void SetDateTime(const SDate & paramDate,const STime & paramTime)
        {
            m_DateTime = CalcMillis(paramDate.Year, paramDate.Month, paramDate.Day,
                paramTime.Hour, paramTime.Minute, paramTime.Second, paramTime.Millis);
        }
        ///设置指定的日期时间
        void SetDateTime(const XDate<T> & paramDate, const XTime<T> & paramTime);
        ///设置日期时间为当前时间
        void SetNowDateTime()
        {
            m_DateTime = GetNowDateTime();
        }
        ///将系统时间，设为当前日期时间
        void SetDateTimeToOS() const;
        ///取当前日期时间的毫秒数
        XLong GetDateTime() const
        {
            return m_DateTime;
        }
        ///取当前日期时间的时间
        XTime<T> GetTime() const;
        ///取当前日期时间的日期
        XDate<T> GetDate() const;
        ///取当前日期时间总的日期数
        XInt  GetDays() const
        {
            return XInt(m_DateTime / MILLIS_PRE_DAY64);
        }
        ///取当前日期时间总的毫秒数
        XLong GetAllMillis() const
        {
            return m_DateTime;
        }
        ///取当前日期时间的年份
        XInt getYear() const
        {
            SDate d;
            DecodeDate(d);
            return d.Year;
        }
        ///取当前日期时间的月份
        XInt getMonth() const
        {
            SDate d;
            DecodeDate(d);
            return d.Month;
        }
        ///取当前日期时间的日期
        XInt getDay() const
        {
            SDate d;
            DecodeDate(d);
            return d.Day;
        }
        ///取当前日期时间的小时
        XInt getHour() const
        {
            STime t;
            DecodeTime(t);
            return t.Hour;
        }
        ///取当前日期时间的分钟
        XInt getMinute() const
        {
            STime t;
            DecodeTime(t);
            return t.Minute;
        }
        ///取当前日期时间的秒数
        XInt getSecond() const
        {
            STime t;
            DecodeTime(t);
            return t.Second;
        }
        ///取当前日期时间的毫秒数
        XInt getMillis() const
        {
            STime t;
            DecodeTime(t);
            return t.Millis;
        }
        ///解码时间
        /**
         * @param [out] paramHour 返回计算出来的小时
         * @param [out] paramMinute 返回计算出来的分钟
         * @param [out] paramSecond 返回计算出来的秒
         * @param [out] paramMillis 返回计算出来的毫秒
         */
        void DecodeTime(XInt &paramHour, XInt &paramMinute, XInt &paramSecond, XInt &paramMillis) const
        {
            MillisToTime(XInt(m_DateTime % MILLIS_PRE_DAY64), paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///解码时间
        /**
         * @param [out] paramTime 返回计算出来时间的结构体
         */
        void DecodeTime(STime & paramTime) const
        {
            MillisToTime(XInt(m_DateTime % MILLIS_PRE_DAY64), paramTime);
        }
        ///解码日期
        /**
         * @param [out] paramYear 返回计算出年份
         * @param [out] paramMonth 返回计算出的月份
         * @param [out] paramDay 返回计算出的日期
         */
        void DecodeDate(XInt &paramYear, XInt & paramMonth, XInt & paramDay) const
        {
            DaysToDate(XInt(m_DateTime / MILLIS_PRE_DAY64), paramYear, paramMonth, paramDay);
        }
        ///解码日期
        /**
         * @param [out] paramDate 解码的日期
         */
        void DecodeDate(SDate & paramDate) const
        {
            DaysToDate(XInt(m_DateTime / MILLIS_PRE_DAY64), paramDate);
        }

        ///解码日期时间
        /**
         * @param [out] paramYear 返回计算出年份
         * @param [out] paramMonth 返回计算出的月份
         * @param [out] paramDay 返回计算出的日期
         * @param [out] paramHour 返回计算出来的小时
         * @param [out] paramMinute 返回计算出来的分钟
         * @param [out] paramSecond 返回计算出来的秒
         * @param [out] paramMillis 返回计算出来的毫秒
         */
        void DecodeDateTime(XInt &paramYear, XInt & paramMonth, XInt & paramDay,
            XInt &paramHour, XInt &paramMinute, XInt &paramSecond, XInt &paramMillis) const
        {
            DaysToDate(XInt(m_DateTime / MILLIS_PRE_DAY64), paramYear, paramMonth, paramDay);
            MillisToTime(XInt(m_DateTime % MILLIS_PRE_DAY64), paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///赋值拷贝函数
        /**
         * @param [in] paramDateTime 被赋值的日期时间
         * @return 返回当前对象的引用
         */
        XDateTime<T> & operator = (const XDateTime<T> & paramDateTime)
        {
            m_DateTime = paramDateTime.m_DateTime;
            return *this;
        }
        ///赋值函数
        /**
         * @param [in] paramDateTime 要赋值的日期时间毫秒数
         * @return 返回当前日期时间的引用
         */
        XDateTime<T> & operator = (XLong paramDateTime)
        {
            m_DateTime = paramDateTime;
            RoundDateTime();
            return *this;
        }
        ///解码日期时间
        /**
        * @param [out] paramDate 解码后的日期
        * @param [out] paramTime 解码后的日期
        */
        void DecodeDateTime(SDate & paramDate, STime & paramTime) const
        {
            DaysToDate(XInt(m_DateTime / MILLIS_PRE_DAY64), paramDate);
            MillisToTime(XInt(m_DateTime % MILLIS_PRE_DAY64), paramTime);
        }

        //一组跟日期比较函数
        bool operator == (const XDateTime<T> & paramDateTime) const { return m_DateTime == paramDateTime.m_DateTime; }
        bool operator != (const XDateTime<T> & paramDateTime) const { return m_DateTime != paramDateTime.m_DateTime; }
        bool operator >= (const XDateTime<T> & paramDateTime) const { return m_DateTime >= paramDateTime.m_DateTime; }
        bool operator <= (const XDateTime<T> & paramDateTime) const { return m_DateTime <= paramDateTime.m_DateTime; }
        bool operator >  (const XDateTime<T> & paramDateTime) const { return m_DateTime >  paramDateTime.m_DateTime; }
        bool operator <  (const XDateTime<T> & paramDateTime) const { return m_DateTime <  paramDateTime.m_DateTime; }
        //一组跟毫秒数比较的函数
        bool operator == (const XLong & paramDateTime) const { return m_DateTime == paramDateTime; }
        bool operator != (const XLong & paramDateTime) const { return m_DateTime != paramDateTime; }
        bool operator >= (const XLong & paramDateTime) const { return m_DateTime >= paramDateTime; }
        bool operator <= (const XLong & paramDateTime) const { return m_DateTime <= paramDateTime; }
        bool operator >  (const XLong & paramDateTime) const { return m_DateTime >  paramDateTime; }
        bool operator <  (const XLong & paramDateTime) const { return m_DateTime <  paramDateTime; }
        ///增加指定的毫秒数
        void AddMillis(XLong paramDuration)
        {
            m_DateTime += paramDuration;
            RoundDateTime();
        }
        ///减少指定的毫秒数
        void SubMillis(XLong paramDuration)
        {
            m_DateTime -= paramDuration;
            RoundDateTime();
        }
        ///重载+=运算符:时间增加
        /**
            @param [in] paramDuration 增加的时间，单位毫秒数
            @return 返回当前日期时间的引用
         */
        XDateTime & operator += (XLong paramDuration)
        {
            m_DateTime += paramDuration;
            RoundDateTime();
            return *this;
        }
        ///重载-=运算符:时间减少
        /**
            @param [in] paramDuration 减少的时间，单位毫秒数
            @return 返回当前日期时间的引用
         */
        XDateTime & operator -= (XLong paramDuration)
        {
            m_DateTime -= paramDuration;
            RoundDateTime();
            return *this;
        }
        ///生成时间格式的字符串: 格式为: HH:MM:SS.mmm
        T & ToTimeString(T & paramString) const;
        ///生成时间格式的字符串: 格式为: HH:MM:SS.mmm
        T ToTimeString() const
        {
            T strRet;
            ToTimeString(strRet);
            return strRet;
        }
        ///生成日期格式的字符串: 格式为: YYYY-MM-DD
        T & ToDateString(T & paramString) const;
        ///生成日期格式的字符串: 格式为: YYYY-MM-DD
        T ToDateString() const
        {
            T strRet;
            ToDateString(strRet);
            return strRet;
        }
        ///将日期时间转换成字符串
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
        ///将日期时间转换成字符串
        /**
            这个函数，需要外部提供一个字符串对象
            @param [out] paramString 存贮转换后字符串的对象
            @return 返回转换后的对象引用
         */
        T & ToString(T & paramString) const;
        ///将日期时间转换为日期, 类型转换
        operator XDate<T>() const;
        ///将日期时间转换为时间, 类型转换
        operator XTime<T>() const;
        ///将日期时间转换为星期, 类型转换
        operator XWeek<T>() const;
        ///两个日期时长
        XDurationTime<T> operator - (const XDateTime<T> & paramDateTime) const;
        ///重载XAnsiString转换运算符
        operator T() const
        {
            T strRet;
            ToString(strRet);
            return strRet;
        }
        ///重载++运算符，当前日期时间自加1
        /**
         * 当前日期时间自加1
         * @return 返回加1后当前对象引用
         */
        XDateTime<T> & operator++()
        {
            ++ m_DateTime;
            RoundDateTime();
            return *this;
        }
        ///重载++运算符，当前日期时间自加1
        /**
         * 当前日期时间自加1
         * @return 返回加1前的临时对象
         */
        XDateTime<T> operator++(int)
        {
            XDateTime<T> t(*this);
            ++ m_DateTime;
            RoundDateTime();
            return t;
        }
        ///重载--运算符，当前日期时间自减1
        /**
         * 当前日期时间自减1
         * @return 返回减1后当前对象引用
         */
        XDateTime<T> & operator--()
        {
            --m_DateTime;
            RoundDateTime();
            return *this;
        }
        ///重载--运算符，当前日期时间自减1
        /**
         * 当前日期时间自减1
         * @return 返回减1前的临时对象
         */
		XDateTime<T> operator--(int)
        {
            XDateTime<T> t(*this);
            --m_DateTime;
            RoundDateTime();
            return t;
        }
        ///重载+运算符，当前日期时间加v
        /**
         * 当前日期时间加v
         * @param [in] v 当前日期时间加的值，单位毫秒
         * @return 返回当前日期时间增加后的临时对象
         */
        XDateTime<T> operator + (XLong v) const
        {
            return XDateTime(m_DateTime + v);
        }
        ///重载-运算符，当前日期时间减v
        /**
         * 当前日期时间减v
         * @param [in] v 当前日期时间减的值，单位毫秒
         * @return 返回当前日期时间减少后的临时对象
         */
        XDateTime<T> operator - (XLong v) const
        {
            return XDateTime<T>(m_DateTime - v);
        }
        ///从字符串中解析日期时间
        /**
         * @param [in] paramDateTime 日期时间串
         * @return 返回解析结果
         *    - X_DATETIME_ERROR_OK 表示解析成功
         *    - 其它值表示解析失败
         */
        EnumParseDateTimeErrorCode Parse(const StringChar * paramDateTime)
        {
            SDate dtDate;
            STime tTime;
            EnumParseDateTimeErrorCode eRet = ParseDateTime(paramDateTime, dtDate, tTime);
            if( eRet == X_DATETIME_ERROR_OK ) SetDateTime(dtDate, tTime);
            return eRet;
        }
        ///从字符串中解析日期时间
        /**
         * @param [in] paramDateTime 日期时间串
         * @return 返回解析结果
         *    - X_DATETIME_ERROR_OK 表示解析成功
         *    - 其它值表示解析失败
         */
        EnumParseDateTimeErrorCode Parse(const T & paramDateTime)
        {
            return Parse(paramDateTime.c_str());
        }
    private:
        ///圆回超出的时间
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
        XLong m_DateTime; ///<日期时间的毫秒数
    };
    //=====================================================================
    template<class T = XAnsiString>
    class XTime
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///指定时间的构造函数
        XTime(XInt paramTime = MIN_MILLIS_IN_DAY)
            :m_Millis(paramTime)
        {
            RoundTime();
        }
        ///默认拷贝构造函数
        XTime(const XTime<T> & paramTime)
            :m_Millis(paramTime.m_Millis)
        {}
        ///指定时间的构造函数
        XTime(XInt paramHour,XInt paramMinute, XInt paramSecond = 0, XInt paramMillis = 0)
            :m_Millis(CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis))
        {}
        ///指定日期时间的构造函数
        XTime(const XDateTime<T> & paramDateTime)
            :m_Millis(XInt(XLong(paramDateTime) % MILLIS_PRE_DAY64))
        {
        }
        ///解码时间
        /**
         * @param [out] paramHour 返回计算出来的小时
         * @param [out] paramMinute 返回计算出来的分钟
         * @param [out] paramSecond 返回计算出来的秒
         * @param [out] paramMillis 返回计算出来的毫秒
         */
        void Decode(XInt & paramHour, XInt & paramMinute, XInt & paramSecond, XInt & paramMillis) const
        {
            MillisToTime(m_Millis, paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///解码时间
        /**
         * @param [out] paramTime 返回计算出来的时间
         */
        void Decode(STime & paramTime) const
        {
            MillisToTime(m_Millis, paramTime);
        }
        ///解码时间
        /**
         * @param [out] paramHour 返回计算出来的小时
         * @param [out] paramMinute 返回计算出来的分钟
         * @param [out] paramSecond 返回计算出来的秒
         */
        void Decode(XInt & paramHour, XInt & paramMinute, XInt & paramSecond) const
        {
            XInt iMillis;
            MillisToTime(m_Millis, paramHour, paramMinute, paramSecond, iMillis);
        }
        ///设置指定毫秒数的时间
        /**
            @param [in] paramMillis 指定的毫秒数
         */
        void SetTime(XInt paramMillis)
        {
            m_Millis = paramMillis;
            RoundTime();
        }
        ///设置指定时、分、秒、毫秒的时间
        /**
         * @param [in] paramHour 小时，其值在[0,23]之间
         * @param [in] paramMinute 分钟，其值在[0,59]之间
         * @param [in] paramSecond 秒，其值在[0,59]之间
         * @param [in] paramMillis 毫秒，其值在[0,999]之间
         * @exception XEXDateTimeError 有错误，则抛出异常
         */
        void SetTime(XInt paramHour, XInt paramMinute, XInt paramSecond = 0, XInt paramMillis = 0)
        {
            m_Millis = CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///设置指定时间的时间
        /**
         * @param [in] paramTime 指定的时间
         */
        void SetTime(const XTime<T> & paramTime)
        {
            m_Millis = paramTime.m_Millis;
        }
        ///设置指定时间的时间
        /**
         * @param [in] paramTime 有效的时间
         */
        void SetTime(const STime & paramTime)
        {
            m_Millis = CalcMillisByTime(paramTime.Hour, paramTime.Minute, paramTime.Second, paramTime.Millis);
        }
        ///设置指定日期时间的时间
        /**
         * @param [in] paramDateTime 指定的日期时间
         */
        void SetTime(const XDateTime<T> & paramDateTime)
        {
            m_Millis = XInt(XLong(paramDateTime) % MAX_MILLIS_IN_DAY);
        }
        ///设置时间为当前系统时间
        void SetNowTime()
        {
            m_Millis = XInt(GetNowDateTime() % MILLIS_PRE_DAY64);
        }
        ///将当前时间设为系统时间
        void SetTimeToOS() const
        {
            XDateTime<T> dt;
            dt.SetNowDateTime();
            dt.SetTime(*this);
            dt.SetDateTimeToOS();
        }
        ///缺省赋值函数
        XTime<T> & operator = (const XTime<T> & paramTime)
        {
            m_Millis = paramTime.m_Millis;
            return *this;
        }
        ///缺省赋值函数
        XTime<T> & operator = (const STime & paramTime)
        {
            SetTime(paramTime);
            return *this;
        }

        ///指定毫秒数的赋值函数
        XTime<T> & operator = (XInt paramTime)
        {
            m_Millis = paramTime;
            RoundTime();
            return *this;
        }
        ///指定日期时间的赋值函数
        XTime<T> & operator = (const XDateTime<T> & paramDateTime)
        {
            m_Millis = XInt(XLong(paramDateTime) % MILLIS_PRE_DAY64);
            return *this;
        }
        ///增加指定的毫秒数
        /**
            @param [in] paramMillis 指定增加的毫秒数
         */
        void AddMillis(XInt paramMillis)
        {
            m_Millis += paramMillis;
            RoundTime();
        }
        ///减少指定的毫秒数
        /**
            @param [in] paramMillis 指定减少毫秒数
         */
        void SubMillis(XInt paramMillis)
        {
            m_Millis -= paramMillis;
            RoundTime();
        }
        ///增加指定的毫秒数
        /**
            @param [in] paramMillis 指定增加的毫秒数
         */
        XTime<T> & operator += (XInt paramMillis)
        {
            m_Millis += paramMillis;
            RoundTime();
            return *this;
        }
        ///减少指定的毫秒数
        /**
            @param [in] paramMillis 指定减少毫秒数
         */
        XTime<T> & operator -= (XInt paramMillis)
        {
            m_Millis -= paramMillis;
            RoundTime();
            return *this;
        }

        ///重载++运算符，当前时间自加1
        /**
         * 当前时间自加1
         * @return 返回加1后当前对象引用
         */
        XTime<T> & operator++()
        {
            ++ m_Millis;
            RoundTime();
            return *this;
        }
        ///重载++运算符，当前时间自加1
        /**
         * 当前时间自加1
         * @return 返回加1前的临时对象
         */
		XTime<T> operator++(int)
		{
            XTime<T> t(*this);
            ++ m_Millis;
            RoundTime();
            return t;
        }
        ///重载--运算符，当前时间自减1
        /**
         * 当前日期自减1
         * @return 返回减1后当前对象引用
         */
        XTime<T> & operator--()
        {
            --m_Millis;
            RoundTime();
            return *this;
        }
        ///重载--运算符，当前时间自减1
        /**
         * 当前时间自减1
         * @return 返回减1前的临时对象
		 */
        XTime<T> operator--(int)
		{
            XTime<T> t(*this);
            --m_Millis;
            RoundTime();
            return t;
        }
        ///将时间转换为32位整数的毫秒数
        operator XInt() const { return m_Millis; }
        ///重载字符串转换函数
        operator T() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }
        ///生成时间字符串
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
        ///生成时间字符串
        T ToString() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }
        //一组比较函数
        bool operator == (const XTime<T> & paramTime) const { return m_Millis == paramTime.m_Millis; }
        bool operator >= (const XTime<T> & paramTime) const { return m_Millis >= paramTime.m_Millis; }
        bool operator <= (const XTime<T> & paramTime) const { return m_Millis <= paramTime.m_Millis; }
        bool operator != (const XTime<T> & paramTime) const { return m_Millis != paramTime.m_Millis; }
        bool operator >  (const XTime<T> & paramTime) const { return m_Millis >  paramTime.m_Millis; }
        bool operator <  (const XTime<T> & paramTime) const { return m_Millis <  paramTime.m_Millis; }
        //一组比较函数
        bool operator == (XInt paramTime) const { return m_Millis == paramTime; }
        bool operator >= (XInt paramTime) const { return m_Millis >= paramTime; }
        bool operator <= (XInt paramTime) const { return m_Millis <= paramTime; }
        bool operator != (XInt paramTime) const { return m_Millis != paramTime; }
        bool operator >  (XInt paramTime) const { return m_Millis >  paramTime; }
        bool operator <  (XInt paramTime) const { return m_Millis <  paramTime; }
        ///重载-运算符,返回减少毫秒数的时间
        XTime<T> operator - (XInt paramMillis) const { return XTime(m_Millis - paramMillis); }
        ///重载+运算符,返回增加毫秒数的时间
        XTime<T> operator + (XInt paramMillis) const { return XTime(m_Millis + paramMillis); }
        ///两个时长的时差
        //XDurationTime operator - (const XTime & paramTime);
        ///取当前时间的总的毫秒数
        XInt getAllMillis() const
        {
            return m_Millis;
        }
        ///取当前时间的小时数
        XInt getHour() const
        {
            STime t;
            Decode(t);
            return t.Hour;
        }
        ///取当前时间的分钟数
        XInt getMinute() const
        {
            STime t;
            Decode(t);
            return t.Minute;
        }
        ///取当前时间的秒数
        XInt getSecond() const
        {
            STime t;
            Decode(t);
            return t.Second;
        }
        ///取当前时间的毫秒数
        XInt getMillis() const
        {
            STime t;
            Decode(t);
            return t.Millis;
        }
        ///从字符串中解析时间
        /**
         * @param [in] paramTime 时间串
         * @return 返回解析结果
         *    - X_DATETIME_ERROR_OK 表示解析成功
         *    - 其它值表示解析失败
         */
        EnumParseDateTimeErrorCode Parse(const StringChar * paramTime)
        {
            STime tTime;
            EnumParseDateTimeErrorCode eRet = ParseTime(paramTime, tTime);
            if( eRet == X_DATETIME_ERROR_OK ) SetTime(tTime);
            return eRet;
        }
        ///从字符串中解析时间
        /**
         * @param [in] paramTime 时间串
         * @return 返回解析结果
         *    - X_DATETIME_ERROR_OK 表示解析成功
         *    - 其它值表示解析失败
         */
        EnumParseDateTimeErrorCode Parse(const T & paramTime)
        {
            return Parse(paramTime.c_str());
        }
    private:
        ///圆回超出的时间
        void RoundTime()
        {
            if( m_Millis < MIN_MILLIS_IN_DAY || m_Millis >= MAX_MILLIS_IN_DAY )
            {
                m_Millis %= MILLIS_PRE_DAY;
                if( m_Millis < 0 ) m_Millis += MILLIS_PRE_DAY;
            }
        }
    private:
        XInt m_Millis;    ///<时间的毫秒数
    };
    //=====================================================================
    template<class T = XAnsiString>
    class XDate
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///指定天数的构造函数
        /**
         * @param [in] paramDays 指定的天数
         */
        XDate(XInt paramDays = DAYS_1970_1_1)
            :m_Days(DAYS_1970_1_1)
        {
            m_Days = paramDays;
            RoundDate();
        }
        ///默认拷贝构造函数
        /**
         * @param [in] paramDate 指定的日期
         */
        XDate(const XDate<T> & paramDate)
            :m_Days(paramDate.m_Days)
        {}
        ///指定日期时间的构造函数
        /**
         * @param [in] paramDateTime 指定的日期时间
         */
        XDate(const XDateTime<T> & paramDateTime)
            :m_Days(paramDateTime.GetDays())
        {
        }
        ///指定年月日的构造函数,转换成指定日期从元年1月1日开始的天数
        /**
         * @param [in] paramYear 指定的年份
		 * @param [in] paramMonth 指定的月
         * @param [in] paramDay 指定的日期
         */
        XDate(XInt paramYear, XInt paramMonth, XInt paramDay)
            :m_Days(CalcDays(paramYear, paramMonth, paramDay))
        {}
        ///将当前日期转换为年、月、日
        /**
         * @param [out] paramYear 用于返回解码的年
         * @param [out] paramMonth 用于返回解码的月
         * @param [out] paramDay 用于返回解码的日
         */
        void Decode(XInt & paramYear,XInt & paramMonth,XInt & paramDay) const
        {
            DaysToDate(m_Days, paramYear, paramMonth, paramDay);
        }
        ///将当前日期转换为日期
        /**
         * @param [out] paramDate 用于返回解码的日期, 目前转换的范围[0001-01-01, 9999-12-30]
         */
        void Decode(SDate & paramDate) const
        {
            DaysToDate(m_Days, paramDate);
        }
        ///将日期转换为32位整数的天数
        operator XInt() const { return m_Days; }
        ///将日期设置为系统日期
        void SetNowDate()
        {
            SSystemDateTime s;
            GetSystemDateTime(s);
            m_Days = CalcDays(s.Year, s.Month, s.Day);
        }
        ///将系统日期设置为当前的日期
        void SetDateToOS() const
        {
            XDateTime<T> dt;
            dt.SetNowDateTime();
            dt.SetDate(*this);
            dt.SetDateTimeToOS();
        }
        ///设置日期，指定天数
        /**
         * @param [in] paramDays 指定的日期
         */
        void SetDate(XInt paramDays)
        {
            m_Days = paramDays;
            RoundDate();
        }
        ///设置日期，指定年月日
        /**
         * @param [in] paramYear 指定的年
         * @param [in] paramMonth 指定的月
         * @param [in] paramDay 指定的日期
         */
        void SetDate(XInt paramYear, XInt paramMonth, XInt paramDay)
        {
            m_Days = CalcDays(paramYear, paramMonth, paramDay);
        }
        ///设置日期，指定日期时间
        /**
         * @param [in] paramDateTime 指定的日期时间
         */
        void SetDate(const XDateTime<T> & paramDateTime)
        {
            m_Days = paramDateTime.GetDays();
        }
        ///设置日期，指定日期
        /**
         * @param [in] paramDate 指定的日期
         */
        void SetDate(const SDate & paramDate)
        {
            m_Days = CalcDays(paramDate.Year, paramDate.Month, paramDate.Day);
        }
        ///设置日期，指定日期
        /**
         * @param [in] paramDate 指定的日期
         */
        void SetDate(const XDate<T> & paramDate)
        {
            m_Days = paramDate.m_Days;
        }
        ///日期赋值，指定天数
        /**
         * @param [in] paramDays 指定的天数
         * @return 返回当前对象的引用
         */
        XDate<T> & operator = (XInt paramDays)
        {
            m_Days = paramDays;
            RoundDate();
            return *this;
        }
        ///日期赋值，指定日期
        /**
         * @param [in] paramDate 指定的日期
         * @return 返回当前对象的引用
         */
        XDate<T> & operator = (const XDate<T> & paramDate)
        {
            m_Days = paramDate.m_Days;
            return *this;
        }
        ///日期赋值，指定日期
        /**
         * @param [in] paramDate 合法的日期
         * @return 返回当前对象的引用
         */
        XDate<T> & operator = (const SDate & paramDate)
        {
            SetDate(paramDate);
            return *this;
        }
        ///日期赋值，指定日期时间
        /**
         * @param [in] paramDateTime 指定的日期
         * @return 返回当前对象的引用
         */
        XDate<T> & operator = (const XDateTime<T> & paramDateTime)
        {
            m_Days = paramDateTime.GetDays();
            return *this;
        }
        ///将日期转换为字符串
        /**
         * @param [out] paramString 用于保存结果的字符串
         * @return 返回日期字符串的引用
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
        ///将日期转换为字符串
        /**
         * @return 返回日期字符串
         */
        T ToString() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }
        ///T转换函数,将日期转换为日期字符串
        operator T() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }

        //一组日期比较函数
        bool operator == (const XDate<T> & paramDate) const { return m_Days == paramDate.m_Days; }
        bool operator >= (const XDate<T> & paramDate) const { return m_Days >= paramDate.m_Days; }
        bool operator <= (const XDate<T> & paramDate) const { return m_Days <= paramDate.m_Days; }
        bool operator != (const XDate<T> & paramDate) const { return m_Days != paramDate.m_Days; }
        bool operator >  (const XDate<T> & paramDate) const { return m_Days >  paramDate.m_Days; }
        bool operator <  (const XDate<T> & paramDate) const { return m_Days <  paramDate.m_Days; }
        //一组比较函数
        bool operator == (XInt paramDate) const { return m_Days == paramDate; }
        bool operator >= (XInt paramDate) const { return m_Days >= paramDate; }
        bool operator <= (XInt paramDate) const { return m_Days <= paramDate; }
        bool operator != (XInt paramDate) const { return m_Days != paramDate; }
        bool operator >  (XInt paramDate) const { return m_Days >  paramDate; }
        bool operator <  (XInt paramDate) const { return m_Days <  paramDate; }

        ///增加指定的天数
        /**
            @param [in] paramDays 指定增加的天数
         */
        void AddDays(XInt paramDays)
        {
            m_Days += paramDays;
            RoundDate();
        }
        ///减少指定的天数
        /**
            @param [in] paramDays 指定减少天数
         */
        void SubDays(XInt paramDays)
        {
            m_Days -= paramDays;
            RoundDate();
        }
        ///增加指定的天数
        /**
            @param [in] paramDays 指定增加的天数
         */
        XDate<T> & operator += (XInt paramDays)
        {
            m_Days += paramDays;
            RoundDate();
            return *this;
        }
        ///减少指定的天数
        /**
            @param [in] paramDays 指定减少天数
         */
        XDate<T> & operator -= (XInt paramDays)
        {
            m_Days -= paramDays;
            RoundDate();
            return *this;
        }

        ///重载++运算符，当前日期自加1
        /**
         * 当前日期自加1
         * @return 返回加1后当前对象引用
         */
        XDate<T> & operator++()
        {
            ++ m_Days;
            RoundDate();
            return *this;
        }
        ///重载++运算符，当前日期自加1
        /**
         * 当前日期自加1
         * @return 返回加1前的临时对象
         */
		XDate<T> operator++(int)
        {
            XDate<T> d(*this);
            ++ m_Days;
            RoundDate();
            return d;
        }
        ///重载--运算符，当前日期自减1
        /**
         * 当前日期自减1
         * @return 返回减1后当前对象引用
         */
        XDate<T> & operator--()
        {
            --m_Days;
            RoundDate();
            return *this;
        }
        ///重载--运算符，当前日期自减1
        /**
         * 当前日期自减1
         * @return 返回减1前的临时对象
         */
		XDate<T> operator--(int)
		{
            XDate<T> d(*this);
            --m_Days;
            RoundDate();
            return d;
        }
        ///取当前日期的天数
        /**
         * @return 返回天数
         */
        XInt GetDays() const
        {
            return m_Days;
        }
        ///取当前的日期
        XInt getDay() const
        {
            SDate s;
            Decode(s);
            return s.Day;
        }
        ///取当前的月份
        XInt getMonth() const
        {
            SDate s;
            Decode(s);
            return s.Month;
        }
        ///取当前的年份
        XInt getYear() const
        {
            SDate s;
            Decode(s);
            return s.Year;
        }
        ///解析日期
        /**
         * @param [in] paramDate 日期串
         * @return 返回解析结果
         *    - X_DATETIME_ERROR_OK 表示解析成功
         *    - 其它值 表示解析失败
         */
        EnumParseDateTimeErrorCode Parse(const StringChar * paramDate)
        {
            SDate dtDate;
            EnumParseDateTimeErrorCode eRet = ParseDate(paramDate, dtDate);
            if( eRet == X_DATETIME_ERROR_OK ) SetDate(dtDate);
            return eRet;
        }
        ///解析日期
        /**
         * @param [in] paramDate 日期串
         * @return 返回解析结果
         *    - X_DATETIME_ERROR_OK 表示解析成功
         *    - 其它值 表示解析失败
         */
        EnumParseDateTimeErrorCode Parse(const T & paramDate)
        {
            return Parse(paramDate.c_str());
        }
    private:
        ///圆回日期
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
        XInt m_Days;      ///<日期的天数
    };
    //=====================================================================
    /**
        时长类，可以为负数也可以为正数。
     */
    template<class T = XAnsiString>
    class XDurationTime
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///指定时长的构造函数
        /**
         * @param [in] paramDuration 指定的时长,单位毫秒
         */
        XDurationTime(XLong paramDuration = 0 )
            :m_Duration(paramDuration)
        {
            RoundDuration();
        }
        ///默认拷贝构造函数
        /**
         * @param [in] paramDuration 指定时长对象
         */
        XDurationTime(const XDurationTime<T> & paramDuration)
            :m_Duration(paramDuration.m_Duration)
        {}
        ///指定天数,小时等构造函数
        /**
         * @param [in] paramSign 时长的符号
         *      -1 <0 表示时长为负数
         *      1 >=0 表示时长为正数
         * @param [in] paramDays 时长的天数 > 0
         * @param [in] paramHour 时长的小时数[0,23]
         * @param [in] paramMinute 时长的分钟[0,59]
         * @param [in] paramSecond 时长的秒数[0,59]
         * @param [in] paramMillis 时长的毫秒数[0,999]
         */
        XDurationTime(XInt paramSign, XInt paramDays,
            XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0)
        {
            SetDuration(paramSign, paramDays, paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///设置时长
        /**
         * @param [in] paramDuration 指定的时长
         */
        void SetDuration(XLong paramDuration = 0 )
        {
            m_Duration = paramDuration;
            RoundDuration();
        }
        ///设置时长
        /**
         * @param [in] paramDuration 指定的时长
         */
        void SetDuration(const XDurationTime<T> & paramDuration)
        {
            m_Duration = paramDuration.m_Duration;
        }
        ///设置时长
        /**
         * @param [in] paramSign 时长的符号
         *      - <0 表示时长为负数
         *      0 >=0 表示时长为正数
         * @param [in] paramDays 时长的天数 >= 0
         * @param [in] paramHour 时长的小时数[0,23]
         * @param [in] paramMinute 时长的分钟[0,59]
         * @param [in] paramSecond 时长的秒数[0,59]
         * @param [in] paramMillis 时长的毫秒数[0,999]
         */
        void SetDuration(XInt paramSign, XInt paramDays, XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0)
		{
            if( paramDays < 0 ) throw XELessThanZero();
            m_Duration = paramDays * MILLIS_PRE_DAY64 + CalcMillisByTime(paramHour, paramMinute, paramSecond, paramMillis);
            if( paramSign < 0 ) m_Duration = - m_Duration;
        }
        ///指定时长赋值
        /**
         * @param [in] paramDuration 指定的时长
         * @return 返回当前时长对象的引用
         */
        XDurationTime<T> & operator = (XLong paramDuration)
        {
            m_Duration = paramDuration;
            RoundDuration();
            return *this;
        }
        ///默认赋值函数
        /**
         * @param [in] paramDuration 指定的时长对象
         * @return 返回当前时长对象的引用
         */
        XDurationTime<T> & operator = (const XDurationTime<T> & paramDuration)
        {
            m_Duration = paramDuration.m_Duration;
            return *this;
        }
        ///增加时长
        /**
         * @param [in] paramMillis 增加的毫秒数
         */
        void AddMillis(XLong & paramMillis)
        {
            m_Duration += paramMillis;
            RoundDuration();
        }
        ///减少时长
        /**
         * @param [in] paramMillis 减少的毫秒数
         */
        void SubMillis(XLong & paramMillis)
        {
            m_Duration -= paramMillis;
            RoundDuration();
        }
        ///增加时长
        /**
         * @param [in] paramMillis 增加的毫秒数
         */
        void AddDuration(const XDurationTime<T> & paramDuration)
        {
            m_Duration += paramDuration.m_Duration;
            RoundDuration();
        }
        ///减少时长
        /**
         * @param [in] paramMillis 减少的毫秒数
         */
        void SubDuration(const XDurationTime<T> & paramDuration)
        {
            m_Duration -= paramDuration.m_Duration;
            RoundDuration();
        }

        ///增加时长
        /**
         * @param [in] paramDuration 增加的毫秒数
         * @return 返回当前时长对象的引用
         */
        XDurationTime<T> & operator += (XLong paramDuration)
        {
            m_Duration += paramDuration;
            RoundDuration();
            return *this;
        }
        ///增加时长
        /**
         * @param [in] paramDuration 增加的时长
         * @return 返回当前时长对象的引用
         */
        XDurationTime<T> & operator += (const XDurationTime<T> & paramDuration)
        {
            m_Duration += paramDuration.m_Duration;
            RoundDuration();
            return *this;
        }
        ///减少时长
        /**
         * @param [in] paramDuration 减少的毫秒数
         * @return 返回当前时长对象的引用
         */
        XDurationTime<T> & operator -= (XLong paramDuration)
        {
            m_Duration -= paramDuration;
            RoundDuration();
            return *this;
        }
        ///减少时长
        /**
         * @param [in] paramDuration 减少的时长
         * @return 返回当前时长对象的引用
         */
        XDurationTime<T> & operator -= (const XDurationTime<T> & paramDuration)
        {
            m_Duration -= paramDuration.m_Duration;
            RoundDuration();
            return *this;
        }
        ///两个时长相加
        /**
         * @param [in] paramDuration 相加的时长
         * @return 返回两个时长相加的结果
         */
        XDurationTime<T> operator + (const XDurationTime<T> & paramDuration) const
        {
            return XDurationTime<T>(m_Duration + paramDuration.m_Duration);
        }
        ///两个时长相加
        /**
         * @param [in] paramDuration 相加的毫秒数
         * @return 返回两个时长相加的结果
         */
        XDurationTime<T> operator + (XLong paramDuration) const
        {
            return XDurationTime<T>(m_Duration + paramDuration);
        }
        ///两个时长相减
        /**
         * @param [in] paramDuration 相加的时长
         * @return 返回两个时长相减的结果
         */
        XDurationTime<T> operator - (const XDurationTime<T> & paramDuration) const
        {
            return XDurationTime<T>(m_Duration - paramDuration.m_Duration);
        }
        ///两个时长相减
        /**
         * @param [in] paramDuration 相减的毫秒数
         * @return 返回两个时长相减的结果
         */
        XDurationTime<T> operator - (XLong paramDuration) const
        {
            return XDurationTime<T>(m_Duration - paramDuration);
        }
        ///将时长解码成天,时,分,秒,毫秒
        /**
         * @param [out] paramSign 返回时长符号
         * @param [out] paramDays 返回时长的天数
         * @param [out] paramHour 返回时长的小时
         * @param [out] paramMinute 返回时长的分钟
         * @param [out] paramSecond 返回时长的秒数
         * @param [out] paramMillis 返回时长的毫秒数
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
        ///将时长解码成天,时,分,秒
        /**
         * @param [out] paramSign 返回时长符号
         * @param [out] paramDays 返回时长的天数
         * @param [out] paramHour 返回时长的小时
         * @param [out] paramMinute 返回时长的分钟
         * @param [out] paramSecond 返回时长的秒数
         */
        void Decode(XInt & paramSign,XInt & paramDays,XInt & paramHour,XInt & paramMinute,XInt & paramSecond) const
        {
            XInt paramMillis;
            Decode(paramSign, paramDays, paramHour, paramMinute, paramSecond, paramMillis);
        }
        ///将时长转换为字符串
        /**
         * 转换的格式是 Days HH:MM:SS.mmm 或 -Days HH:MM:SS.mmm
         * @param [out] paramString 存放转换后字符串的字符串
         * @return 返回转换后的字符串
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
        ///将时长转换为字符串
        /**
         * 转换的格式是 Days HH:MM:SS.mmm 或 -Days HH:MM:SS.mmm
         * @return 返回转换后的字符串
         */
        T ToString() const
        {
            T paramString;
            ToString(paramString);
            return paramString;
        }
        ///重载++运算符，当前时长自加1毫秒
        /**
         * 当前时长自加1毫秒
         * @return 返回加1毫秒后当前对象引用
         */
        XDurationTime<T> & operator++()
        {
            ++ m_Duration;
            RoundDuration();
            return *this;
        }
        ///重载++运算符，当前时长自加1毫秒
        /**
         * 当前时长自加1毫秒
         * @return 返回加1毫秒前的临时对象
         */
		XDurationTime operator++(int)
        {
            XDurationTime d(*this);
            ++ m_Duration;
            RoundDuration();
            return d;
        }
        ///重载--运算符，当前时长自减1毫秒
        /**
         * 当前时长自减1毫秒
         * @return 返回减1毫秒后当前对象引用
         */
        XDurationTime & operator--()
        {
            --m_Duration;
            RoundDuration();
            return *this;
        }
        ///重载--运算符，当前时长自减1毫秒
        /**
         * 当前时长自减1毫秒
         * @return 返回减1毫秒前的临时对象
         */
		XDurationTime operator--(int)
		{
            XDurationTime d(*this);
            --m_Duration;
            RoundDuration();
            return d;
        }
        ///将时长转换为64位整数的毫秒数
        operator XLong() const { return m_Duration; }
        ///将时长转换为32位整数的毫秒数
        operator XInt() const  { return XInt(m_Duration); }
        //一组比较函数
        bool operator == (const XDurationTime & paramDuration) const { return m_Duration == paramDuration.m_Duration; }
        bool operator >= (const XDurationTime & paramDuration) const { return m_Duration >= paramDuration.m_Duration; }
        bool operator <= (const XDurationTime & paramDuration) const { return m_Duration <= paramDuration.m_Duration; }
        bool operator != (const XDurationTime & paramDuration) const { return m_Duration != paramDuration.m_Duration; }
        bool operator >  (const XDurationTime & paramDuration) const { return m_Duration >  paramDuration.m_Duration; }
        bool operator <  (const XDurationTime & paramDuration) const { return m_Duration <  paramDuration.m_Duration; }
        //一组比较函数
        bool operator == (XInt paramDuration) const { return m_Duration == paramDuration; }
        bool operator >= (XInt paramDuration) const { return m_Duration >= paramDuration; }
        bool operator <= (XInt paramDuration) const { return m_Duration <= paramDuration; }
        bool operator != (XInt paramDuration) const { return m_Duration != paramDuration; }
        bool operator >  (XInt paramDuration) const { return m_Duration >  paramDuration; }
        bool operator <  (XInt paramDuration) const { return m_Duration <  paramDuration; }
        ///将字符串转换为时长
        /**
         * 转换的格式是[-|+]Days HH:MM:SS.mmm
         * @param [in] paramDuration 时长字符串
         * @return 返回解析结果
         *     - X_DATETIME_ERROR_OK 表示解析正常
         *     - 其它值 表示解析失败
         */
        EnumParseDateTimeErrorCode Parse(const StringChar * paramDuration);
        ///将字符串转换为时长
        /**
         * 转换的格式是[-|+]Days HH:MM:SS.mmm
         * @param [in] paramDuration 时长字符串
         * @return 返回解析结果
         *     - X_DATETIME_ERROR_OK 表示解析正常
         *     - 其它值 表示解析失败
         */
        EnumParseDateTimeErrorCode Parse(const T & paramDuration)
        {
            return Parse(paramDuration.c_str());
        }
    private:
        ///圆回时长
        void RoundDuration()
        {
            m_Duration %= MAX_DURATION;
        }
    private:
        XLong m_Duration; ///<持续的毫秒数
    };
    //=====================================================================
    //生成星期字符串的模式
    const XInt XWEEK_MODE_ENGLISH = 0;          ///<英文星期模式 Sunday
    const XInt XWEEK_MODE_CHINESE = 1;          ///<中文星期模式 星期日
    const XInt XWEEK_MODE_SHORT_ENGLISH = 2;    ///<英文短星期模式 Sun.
    const XInt XWEEK_MODE_NUMBER = 3;           ///<英文数字       0
    const XInt XWEEK_MODE_SHORT_CHINESE = 4;    ///<中文短星期模式 日
    ///星期类
    template<class T = XAnsiString>
    class XWeek
    {
    public:
        typedef typename T::StringChar StringChar;
    public:
        ///指定星期的构造函数
        /**
         * @param [in] paramWeek 指定的星期
         */
        XWeek(XInt paramWeek = WEEKDAY_SUNDAY)
            :m_WeekDay(paramWeek)
        {
            RoundWeek();
        }
        ///指定日期时间的构造函数
        /**
         * @param [in] paramDateTime 指定的日期时间
         */
        XWeek(const XDateTime<T> & paramDateTime)
            :m_WeekDay(paramDateTime.GetDays())
        {
            RoundWeek();
        }
        ///指定日期的构造函数
        /**
         * @param [in] aData 指定的日期
         */
        XWeek(const XDate<T> & paramDate)
            :m_WeekDay(paramDate.GetDays())
        {
            RoundWeek();
        }
        ///默认构造函数
        XWeek(const XWeek<T> & paramWeek)
            :m_WeekDay(paramWeek.m_WeekDay)
        {
        }
        ///设成指定的星期
        void SetWeek(XInt paramWeek = WEEKDAY_SUNDAY)
        {
            m_WeekDay = paramWeek;
            RoundWeek();
        }
        ///设成指定的星期
        void SetWeek(const XWeek<T> & paramWeek)
        {
            m_WeekDay = paramWeek.m_WeekDay;
        }
        ///设成指定日期的星期
        void SetWeek(const XDate<T> & paramDate)
        {
            m_WeekDay = paramDate.GetDays() % 7;
        }
        ///设成指定日期时间的星期
        void SetWeek(const XDateTime<T> & paramDateTime)
        {
            m_WeekDay = paramDateTime.GetDays() % 7;
        }
        ///设成当前系统的星期
        void SetNowWeek()
        {
            XDate<T> paramDate;
            paramDate.SetNowDate();
            m_WeekDay = paramDate.GetDays() % 7;
        }
        ///将星期转换为指定模式的字符串
        /**
         * @param [in] paramMode 指定的星期模式
         * @param [out] paramString 返回转换后的星期字符串
         */
        T & ToString(T & paramString, XInt paramMode = XWEEK_MODE_ENGLISH) const;
        ///将星期转换为指定模式的字符串
        /**
         * @param [in] paramMode 指定的星期模式
         * @return 返回转换后的星期字符串
         */
        T ToString(XInt paramMode = XWEEK_MODE_ENGLISH) const
        {
            T paramString;
            ToString(paramString,paramMode);
            return paramString;
        }
        ///将星期转换为默认模式(英文星期模式)的字符串
        operator T() const
        {
            T paramString;
            ToString(paramString, XWEEK_MODE_ENGLISH);
            return paramString;
        }
        ///将星期转换为XInt
        operator XInt() const
        {
            return m_WeekDay;
        }
        ///将星期赋值为指定的星期
        XWeek<T> & operator = (XInt paramWeek)
        {
            SetWeek(paramWeek);
            return *this;
        }
        ///将星期赋值为指定的星期
        XWeek<T> & operator = (const XWeek<T> & paramWeek)
        {
            SetWeek(paramWeek);
            return *this;
        }
        ///将星期赋值为指定日期的星期
        XWeek<T> & operator = (const XDate<T> & paramDate)
        {
            SetWeek(paramDate);
            return *this;
        }
        ///将星期赋值为指定日期时间的星期
        XWeek<T> & operator = (const XDateTime<T> & paramDateTime)
        {
            SetWeek(paramDateTime);
            return *this;
        }
        //一组比较函数
        bool operator == (const XWeek<T> & paramWeek) const { return m_WeekDay == paramWeek.m_WeekDay; }
        bool operator >= (const XWeek<T> & paramWeek) const { return m_WeekDay >= paramWeek.m_WeekDay; }
        bool operator <= (const XWeek<T> & paramWeek) const { return m_WeekDay <= paramWeek.m_WeekDay; }
        bool operator != (const XWeek<T> & paramWeek) const { return m_WeekDay != paramWeek.m_WeekDay; }
        bool operator >  (const XWeek<T> & paramWeek) const { return m_WeekDay >  paramWeek.m_WeekDay; }
        bool operator <  (const XWeek<T> & paramWeek) const { return m_WeekDay <  paramWeek.m_WeekDay; }
        //一组比较函数
        bool operator == (XInt paramWeek) const { return m_WeekDay == paramWeek; }
        bool operator >= (XInt paramWeek) const { return m_WeekDay >= paramWeek; }
        bool operator <= (XInt paramWeek) const { return m_WeekDay <= paramWeek; }
        bool operator != (XInt paramWeek) const { return m_WeekDay != paramWeek; }
        bool operator >  (XInt paramWeek) const { return m_WeekDay >  paramWeek; }
        bool operator <  (XInt paramWeek) const { return m_WeekDay <  paramWeek; }

        ///增加指定的天数
        /**
            @param [in] paramDays 指定增加的天数
         */
        void AddDays(XInt paramDays)
        {
            m_WeekDay += paramDays;
            RoundWeek();
        }
        ///减少指定的天数
        /**
            @param [in] paramDays 指定减少天数
         */
        void SubDays(XInt paramDays)
        {
            m_WeekDay -= paramDays;
            RoundWeek();
        }
        ///增加指定的天数
        /**
            @param [in] paramDays 指定增加的天数
         */
        XWeek<T> & operator += (XInt paramDays)
        {
            m_WeekDay += paramDays;
            RoundWeek();
            return *this;
        }
        ///减少指定的天数
        /**
            @param [in] paramDays 指定减少天数
         */
        XWeek<T> & operator -= (XInt paramDays)
        {
            m_WeekDay -= paramDays;
            RoundWeek();
            return *this;
        }

        ///重载++运算符，当前星期自加1天
        /**
         * 当前星期自加1天
         * @return 返回加1后当前对象引用
         */
        XWeek<T> & operator++()
        {
            ++ m_WeekDay;
            RoundWeek();
            return *this;
        }
        ///重载++运算符，当前星期自加1天
        /**
         * 当前星期自加1天
         * @return 返回加1前的临时对象
         */
		XWeek<T> operator++(int)
		{
            XWeek<T> w(*this);
            ++ m_WeekDay;
            RoundWeek();
            return w;
        }
        ///重载--运算符，当前星期自减1天
        /**
         * 当前星期自减1天
         * @return 返回减1后当前对象引用
         */
        XWeek<T> & operator--()
        {
            --m_WeekDay;
            RoundWeek();
            return *this;
        }
        ///重载--运算符，当前星期自减1天
        /**
         * 当前星期自减1天
         * @return 返回减1后当前对象引用
         */
        XWeek<T> operator--(int)
        {
            XWeek<T> w(*this);
            --m_WeekDay;
            RoundWeek();
            return w;
        }
        ///取当前星期的星期值
        /**
         * @return 返回星期值
         */
        XInt GetWeekDay() const
        {
            return m_WeekDay;
        }
    private:
        ///圆回星期
        void RoundWeek()
        {
            if( m_WeekDay < WEEKDAY_SUNDAY || m_WeekDay > WEEKDAY_SATURDAY )
            {
                m_WeekDay %= 7;
                if( m_WeekDay < 0 ) m_WeekDay += 7;
            }
        }
    private:
        XInt m_WeekDay; ///<星期值，0～6之间
    };



    //---------------------------------------------------------------------
    /**
        指定日期的构造函数
        @param [in] paramDate 指定的日期
     */
    template<class T>
    XDateTime<T>::XDateTime(const XDate<T> & paramDate)
        :m_DateTime( XInt(paramDate) * MILLIS_PRE_DAY64 )
    {}


    //---------------------------------------------------------------------
    /**
        指定日期和时间构造函数
        @param [in] paramDate 指定的日期
        @param [in] paramTime 指定的时间
     */
    template<class T>
    XDateTime<T>::XDateTime(const XDate<T> & paramDate, const XTime<T> & paramTime)
        :m_DateTime( XInt(paramDate) * MILLIS_PRE_DAY64 + XInt(paramTime))
    {}
    //---------------------------------------------------------------------
    ///设置指定的时间,日期不变
    /**
        @param [in] paramTime 指定的时间
     */
    template<class T>
    void XDateTime<T>::SetTime(const XTime<T> & paramTime)
    {
        m_DateTime = m_DateTime - m_DateTime % MILLIS_PRE_DAY + XInt(paramTime);
    }
    //---------------------------------------------------------------------
    ///设置指定的日期，时间不变
    /**
      @param [in] paramDate 指定的日期
     */
    template<class T>
    void XDateTime<T>::SetDate(const XDate<T> & paramDate)
    {
        m_DateTime = XInt(paramDate) * MILLIS_PRE_DAY64 + m_DateTime % MILLIS_PRE_DAY;
    }
    //---------------------------------------------------------------------
    /**
        设置指定的日期时间
        @param [in] paramDate 指定的日期
        @param [in] paramTime 指定的时间
    */
    template<class T>
    void XDateTime<T>::SetDateTime(const XDate<T> & paramDate, const XTime<T> & paramTime)
    {
        m_DateTime = XInt(paramDate) * MILLIS_PRE_DAY64 + XInt(paramTime);
    }
    //---------------------------------------------------------------------
    /**
        取当前日期时间的时间
     */
    template<class T>
    XTime<T> XDateTime<T>::GetTime() const
    {
        return XTime<T>(XInt(m_DateTime % MILLIS_PRE_DAY64));
    }
    //---------------------------------------------------------------------
    /**
        取当前日期时间的日期
     */
    template<class T>
    XDate<T> XDateTime<T>::GetDate() const
    {
        return XDate<T>(XInt(m_DateTime / MILLIS_PRE_DAY64));
    }
    //---------------------------------------------------------------------
    /**
        生成日期字符串
     */
    template<class T>
    T & XDateTime<T>::ToDateString(T & paramString) const
    {
        XDate<T> dtDate(*this);
        return dtDate.ToString(paramString);
    }
    //---------------------------------------------------------------------
    /**
        生成时间字符串
     */
    template<class T>
    T & XDateTime<T>::ToTimeString(T & paramString) const
    {
        XTime<T> t(*this);
        return t.ToString(paramString);
    }


    /**
        将日期时间转换为字符串
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
        将系统时间，设为当前日期时间
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
     * 求两个日期的时差
     * @param [in] paramDateTime 被求差的时间
     * @return 返回两个时间的时差
     */
    template<class T>
    XDurationTime<T> XDateTime<T>::operator - (const XDateTime<T> & paramDateTime) const
    {
        return XDurationTime<T>(m_DateTime - paramDateTime.m_DateTime );
    }
    //==========================================================================
    //---------------------------------------------------------------------
    /**
     * 生成时间字符串
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
     * 生成星期字符串
     * @param [out] paramString 保存结果的字符串引用
     * @param [in] aMode 星期字符串的模式
     * @return 返回保存结果的字符串引用
     */
    template<class T>
    T & XWeek<T>::ToString(T & paramString,XInt aMode) const
    {
        static const XChar * WeekString_1[5][7] =
        {
            {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"},
            {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"},
            {"Sun.", "Mon.", "Tues.", "Wed.", "Thurs.", "Fri.", "Sat."},
            {"0", "1", "2", "3", "4", "5", "6"},
            {"日", "一", "二", "三", "四", "五", "六"}
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
        //判断正负号
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
        XInt iDays = 0;  //天数
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
        //解析时间部分
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
    生成日期字符串
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
