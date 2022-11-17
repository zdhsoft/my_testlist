//---------------------------------------------------------------------------

#ifndef utilsH
#define utilsH
#include <cstdio>
#include "typedef.h"
#include "vcl.h"
//---------------------------------------------------------------------------
namespace zdh {
	namespace utils {
		const XLong MAX_MILLIS              = 315537984000000LL;    ///<最大的毫秒数
		const XLong MIN_MILLIS              = 86400000LL;           ///<最小的毫秒数
		const XLong MILLIS_PRE_DAY64        = 86400000LL;           ///<每天最大的毫秒数64位有符号整数
		const XLong MAX_DURATION            = 315537897600000LL;    ///<最大的持续时间

        const XInt TIME_ZONE_CHINA          = -480;                 ///<中国时间东八区
		const XInt TIME_ZONE_CHINA_SECOND   = -480 * 60;                 ///<中国时间东八区
		const XInt TIME_ZONE_CHINA_MILLIS   = -480 * 60000;                 ///<中国时间东八区

		const XInt MILLIS_PRE_DAY           = 86400000;             ///<每天的毫秒数 24:00:00.000
		const XInt MILLIS_PRE_HOUR          = 3600000;              ///<每小时毫秒数 01:00:00.000
		const XInt MILLIS_PRE_MINUTE        = 60000;                ///<每分钟毫秒数 00:01:00.000
		const XInt MILLIS_PRE_SECOND        = 1000;                 ///<每秒的毫秒数 00:00:01.000

		const XInt MAX_YEAR_IN_DATETIME     = 9999;                 ///<最大的年份
		const XInt MIN_YEAR_IN_DATETIME     = 1;                    ///<最小的年份,公元元年从公元1年开始
		const XInt MAX_MONTH_IN_YEAR        = 12;                   ///<最大的月份
		const XInt MIN_MONTH_IN_YEAR        = 1;                    ///<最小的月份

		const XInt MAX_DAY_IN_MONTH         = 31;                   ///<最大的日期
		const XInt MIN_DAY_IN_MONTH         = 1;                    ///<最小的日期

		const XInt MAX_DAYS_IN_DATETIME     = 3652059;              ///<最大的日期数 9999-12-31
		const XInt MIN_DAYS_IN_DATETIME     = 1;                    ///<最小的日期数 0-1-1

		const XInt DAYS_1970_1_1            = 719163;               ///<1970-1-1到公元元年的天数
		const XLong MILLIS_1970_1_1         =  MILLIS_PRE_DAY64 * DAYS_1970_1_1;

		const XInt INVALID_DAYS             = -1;                   ///< 无效的天数
		const XInt INVALID_TIMES            = -1;
        const XLong INVALID_MILLIS          = -1;

		const XInt ERR_OK = 0;
        const XInt ERR_FAIL = -1;

		template<class T>
		class XCommonRet {
		private:
			XInt m_Ret = ERR_OK;
			String m_Msg;
			T m_Data;
		public:
			XCommonRet(const XInt & paramRet = ERR_OK): m_Ret(paramRet) {
				//
			}
			XCommonRet(const XInt & paramRet, const String & paramMsg):
				m_Ret(paramRet), m_Msg(paramMsg) {
				//
			}
			XCommonRet(const XInt & paramRet, const String & paramMsg, const T & paramData):
				m_Ret(paramRet), m_Msg(paramMsg), m_Data(paramData) {
				//
			}

			XInt & getRet() {
                return m_Ret;
			}

			void setRet(const XInt & paramRet) {
				m_Ret = paramRet;
			}

			String & getMsg() {
				return m_Msg;
			}

			void setMsg(const String & paramMsg) {
				m_Msg = paramMsg;
            }

			T & getData() {
                return m_Data;
			}

			void setData(const T & paramData) {
                m_Data = paramData;
			}

			bool getIsOK() {
                return m_Ret == ERR_OK;
			}

			void setError(const XInt & paramRet, const wchar_t * format, ...) {
				va_list paramList;
				va_start(paramList, format);
				m_Msg.vprintf(format, paramList);
				m_Ret = paramRet;
			}

			void setOK(const T & paramData) {
				m_Data = paramData;
				m_Ret = ERR_OK;
                m_Msg = "";
			}
			__property XInt Ret = { read = getRet, write = setRet };
			__property String Msg = { read = getMsg, write = setMsg };
			__property T Data = { read = getData, write = setData };
			__property bool IsOK = { read = getIsOK };
            __property void OK = { write = setOK };
        };


		void log(const wchar_t * format, ...);
		XInt CalcDays(XInt paramYear, XInt paramMonth, XInt paramDay);
		XInt CalcMonthDays(XInt paramYear, XInt paramMonth, bool paramCheck);
		XInt CalcMillisByTime(XInt paramHour,XInt paramMinute = 0, XInt paramSecond = 0,XInt paramMillis = 0);
		XLong CalcMillis(XInt paramYear , XInt paramMonth = 1, XInt paramDay = 1, XInt paramHour = 0, XInt paramMinute = 0, XInt paramSecond = 0, XInt paramMillis = 0);
		XBool IsRawYear(XInt paramYear);
        XLong CalcTimestamp(XInt paramYear , XInt paramMonth, XInt paramDay, XInt paramHour, XInt paramMinute, XInt paramSecond, XInt paramMillis);
		//-----------------------------------------------------------------------------------------------------
		///判断指针值是否为空
		template<class T>
		inline bool IsNULL(const T * param_pointer)
		{
			return param_pointer == NULL || param_pointer == nullptr;
		}
        ///取字符串的长度
        /**
            @param [in] paramValue 要取得长度的字符串指针
            @return 返回取得长度
        */
        template<class T>
        static XInt Length(const T * paramValue)
        {
			XInt iRet = 0;
			if (IsNULL(paramValue)) {
                return 0;
            }
            while( *paramValue != 0 )
            {
                paramValue ++;
                iRet ++;
            }
            return iRet;
        }
        //----------------------------------------------------------------------------
        /**
              尝试将字符串转换为64位有符号整数，能够自动识别十进制和十六进制数。
              @param [in] paramNumberString 被转换的数值字符串
              @param [out] paramValue 用于保存转换后的数值
              @return 返回尝试转换的状态
                - true 表示转换成功
                - false 表示转换失败，这个时候aValue的值为0
         */
        template<class T>
		static bool TryStringToLong(const T * paramNumberString, XLong & paramValue)
        {

            paramValue = 0;

			if( IsNULL(paramNumberString) )
            {
                return true;
            }

            bool NegativeFlag = false;
            bool HexFlag = false;

            const T * p = paramNumberString;
            //跳过空格
            while(*p == ' ')
            {
                p++;
            }

            switch(*p)
            {
            case 0:
                return false;
            case '+':
                ++p;
                break;
            case '-':
                NegativeFlag = true;
                ++p;
                break;
            case '$':
            case 'x':
            case 'X':
                HexFlag = true;
                ++p;
                break;
            case '0':
                HexFlag = ((*(p+1) == 'x') || (*(p+1) == 'X'));
                if (HexFlag) p += 2;
                break;
            }

            if (*p == 0)
            {
                return false;
            }
            XLong lngValue = 0;
            if (HexFlag)
            {
                // INT64的十六进制字符串最多有16个字节
                if (Length(p) > 16)
                {
                    return false;
                }

                while (*p != 0)
                {
                    XByte v;
                    T chNumber = * p;
                    if (chNumber >= '0' && chNumber <= '9')
                    {
                        v = chNumber - '0';
                    }
                    else if (chNumber >= 'a' && chNumber <= 'f')
                    {
                        v = chNumber - 'a' + 10;
                    }
                    else if (chNumber >= 'A' && chNumber <= 'F')
                    {
                        v = chNumber - 'A' + 10;
                    }
                    else
                    {
                        return false;
                    }
                    //lngValue = lngValue * 16 + v;
                    lngValue *= 16;
                    lngValue += v;
                    ++p;
                }
            }
            else
            {
                //  整数最小值是 -9223372036854775808LL (0x8000000000000000), 最大值是 9223372036854775807LL (0x7FFFFFFFFFFFFFFF)
                const XLong ABS_MIN_LONG_INT_DIV10 = 922337203685477580LL;
                const XLong ABS_MIN_LONG_INT_MOD10 = 8LL;
                const XLong ABS_MAX_LONG_INT_DIV10 = 922337203685477580LL;
                const XLong ABS_MAX_LONG_INT_MOD10 = 7LL;
                const XLong ABS_MIN_LONG_INT_VALUE = 0x8000000000000000LL;

                while (*p != 0)
                {
                    T chNumber = * p;
                    if (chNumber < '0' || chNumber > '9')
                    {
                            return false;
                    }

                    XByte v = *p - '0';

                    if (NegativeFlag)
                    {
                        if (lngValue > ABS_MIN_LONG_INT_DIV10)
                        {
                            return false;
                        }

                        if (lngValue == ABS_MIN_LONG_INT_DIV10)
                        {
                            if (v > ABS_MIN_LONG_INT_MOD10)
                            {
                                return false;
                            }

                            // 因为需要intValue始终是正整数, 其最大值是 2147483647
                            // 如果此时v=8, 将导致其溢出
                            if (v == ABS_MIN_LONG_INT_MOD10)
                            {
                                // 如果后面没有字符了, 说明这个是最后一个字符, 那么这个数是整型最小值
                                // 之所以在这里退出, 是为了防止整型最大值溢出
                                if (*(p+1) == 0)
                                {
                                    paramValue = ABS_MIN_LONG_INT_VALUE;
                                    return true;
                                }
                                else return false;
                            }
                        }
                    }
                    else
                    {
                        if (lngValue > ABS_MAX_LONG_INT_DIV10)
                        {
                            return false;
                        }
                        if (lngValue == ABS_MAX_LONG_INT_DIV10 && v > ABS_MAX_LONG_INT_MOD10)
                        {
                            return false;
                        }
                    }
                    lngValue *= 10;
					lngValue += v;
					++p;
				}
			}
			paramValue = NegativeFlag ? -lngValue : lngValue;
			return true;
		}
	   //-----------------------------------------------------------------------------------------------------
		///尝试将字符串转换为32位有符号整数模板
		/**
		 　 尝试将字符串转换为32位有符号整数，能够自动识别十进制和十六进制数。
			@param [in] paramNumberString 被转换的数值字符串
			@param [out] paramValue 用于保存转换后的数值
			@return 返回尝试转换的状态
				- true 表示转换成功
				- false 表示转换失败，这个时候aValue的值为0
		 */
		template<class T>
		static bool TryStringToInt(const T * paramNumberString, XInt & paramValue)
		{
			//先初始化为0
			paramValue = 0;
			if( IsNULL(paramNumberString) )
			{
				return true;
			}

			bool bNegativeFlag = false; //负数标志
			bool bHexFlag = false;      //十六进制标志

			const T *p = paramNumberString;
			//跳过空格
			while(*p == ' ')
			{
				p++;
			}

			//检查符号位
			switch(*p)
			{
			case 0:
				return false;
			case '+':
				++p;
				break;
			case '-':
				bNegativeFlag = true;
				++p;
				break;
			case '$': //if $..,x..,X..开头的数字为十六进制
			case 'x':
			case 'X':
				bHexFlag = true;
				++p;
				break;
			case '0': //if 0x..,0X..开头的数字为十六进制
				bHexFlag = ((*(p+1) == 'x') || (*(p+1) == 'X')); //(Length(s) > I) and (UpCase(s[I+1]) = 'X');
				if (bHexFlag)
				{
					p += 2;
				}
				break;
			}

			if (*p == 0)
			{
				return false;
			}

			if (bHexFlag)
			{
				// INT32的十六进制字符串最多有8个字节
				if (Length(p) > 8)
				{
					return false;
				}
				XInt iValue = 0;
				while (*p != 0)
				{
					XInt v;
					T chNumber = *p;
					if (chNumber >= '0' && chNumber <= '9') //如果是0..9
					{
						v = chNumber - '0';
					}
					else if (chNumber >= 'a' && chNumber <= 'f') //如果是a..f
					{
						v = chNumber - 'a' + 10;
					}
					else if (chNumber >= 'A' && chNumber <= 'F') //如果是A..F
					{
						v = chNumber - 'A' + 10;
					}
					else  //遇到非法数字退出
					{
						return false;
					}
					iValue *= 16;
					iValue += v;
					++p;
				}
				paramValue = iValue;
			}
			else
			{
				//  整数最小值是 -2147483648 (0x80000000), 最大值是 2147483647 (0x7FFFFFFF)
				const XInt ABS_MIN_INT_DIV10 = 214748364;
				const XInt ABS_MIN_INT_MOD10 = 8;
				const XInt ABS_MAX_INT_DIV10 = 214748364;
				const XInt ABS_MAX_INT_MOD10 = 7;

				XInt iValue = 0;

				while (*p != 0)
				{
					T chNumber = *p;
					if (chNumber < '0' ||chNumber > '9') //如果发现超出有效的字符，则表示转换失败
					{
						return false;
					}

					XInt v = chNumber - '0';

					if (bNegativeFlag) //如果是负数
					{
						if (iValue > ABS_MIN_INT_DIV10)
						{
							return false;
						}
						if (iValue == ABS_MIN_INT_DIV10)
						{
							if (v > ABS_MIN_INT_MOD10)
							{
								return false;
							}

							// 因为需要intValue始终是正整数, 其最大值是 2147483647
							// 如果此时v=8, 将导致其溢出
							if (v == ABS_MIN_INT_MOD10)
							{
								// 如果后面没有字符了, 说明这个是最后一个字符, 那么这个数是整型最小值
								// 之所以在这里退出, 是为了防止整型最大值溢出
								if (*(p+1) == 0)
								{
									paramValue = 0x80000000;
									return true;
								}
								else
								{
									return false;
								}
							}
						}
					}
					else //如果是非负数
					{
						if (iValue > ABS_MAX_INT_DIV10)
						{
							return false;
						}
						if (iValue == ABS_MAX_INT_DIV10 && v > ABS_MAX_INT_MOD10)
						{
							return false;
						}
					}
					iValue *= 10;
					iValue += v;
					++p;
				}
				if( bNegativeFlag )
				{
					paramValue = -iValue;
				}
				else
				{
					paramValue = iValue;
				}
			}
			return true;
		}


	}

}
#endif
