//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace zdh {
	namespace utils {
		void log(const wchar_t * format, ...) {
			String s;
			va_list paramList;
			va_start(paramList, format);
			s.vprintf(format, paramList);
			va_end(paramList);
            OutputDebugStringW(s.c_str());
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
		XBool IsRawYear(XInt paramYear)
		{
			if( paramYear < MIN_YEAR_IN_DATETIME || paramYear > MAX_YEAR_IN_DATETIME ) return false;
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
        XInt CalcMonthDays(XInt paramYear, XInt paramMonth, bool paramCheck)
        {
            XInt iRet;
            if( paramCheck ) //如果要检查年月
            {
                if( paramYear < MIN_YEAR_IN_DATETIME || paramYear > MAX_YEAR_IN_DATETIME ) return INVALID_DAYS;
                if( paramMonth < MIN_MONTH_IN_YEAR || paramMonth > MAX_MONTH_IN_YEAR ) return INVALID_DAYS;
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
		XInt CalcDays(XInt paramYear, XInt paramMonth, XInt paramDay)
		{
			//检查年份
			if( paramYear < MIN_YEAR_IN_DATETIME || paramYear > MAX_YEAR_IN_DATETIME ) return INVALID_DAYS;
			//检查月份
			if( paramMonth < MIN_MONTH_IN_YEAR || paramMonth > MAX_MONTH_IN_YEAR ) return INVALID_DAYS;
			//检查日期
			XInt aMonthDays = CalcMonthDays(paramYear, paramMonth, false);
			if (aMonthDays == INVALID_DAYS) {
				return INVALID_DAYS;
			}

			if( paramDay < MIN_DAY_IN_MONTH || paramDay > aMonthDays ) return INVALID_DAYS;

			XInt iDays = 0;

			for(XInt i=1; i<paramMonth; i++) iDays += CalcMonthDays(paramYear, i, false);

			paramYear --;
			iDays += ( (paramYear*365) + (paramYear/4) - (paramYear/100) + (paramYear/400)); //加上往年的天数
			iDays += paramDay;                                                   //加上当前月的天数
			return iDays;
		}
	}
}
