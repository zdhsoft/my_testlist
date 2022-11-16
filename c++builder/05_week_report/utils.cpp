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
		///�ж��Ƿ�������
		/**
		 * �ж��Ƿ�������
		 * @param [in] paramYear ��������ݣ���Ч�������[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮�䣬��ֵ��[1,9999]֮��
		 * @return �����жϽ��
		 *   - true ��ʾ������
		 *   - false ��ʾ��������
		 * @exception XEXDateTimeError ��������Ч�����׳��쳣
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
        * ����ָ�����µ�����
        * @param [in] paramYear ָ������ݣ���Ч�������[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮��
        * @param [in] paramMonth ָ�����·ݣ���Ч���·���[1,12]֮��
        * @param [in] paramCheck ������±�־,
        *     - true ��ʾҪ���paramYear��paramMonth�Ƿ���Ч
        *     - false ��ʾ����Ҫ���paramYear��paramMonth�Ƿ���Ч
        * @return ���ؼ������ָ���·ݵ�����
        * @exception XEDateTimeError �����ݡ��·���Ч�����׳��쳣
        */
        XInt CalcMonthDays(XInt paramYear, XInt paramMonth, bool paramCheck)
        {
            XInt iRet;
            if( paramCheck ) //���Ҫ�������
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
        * �����Ԫ��1��1�տ�ʼ������
        * @param [in] paramYear ָ������ݣ���Ч�������[MIN_YEAR_IN_DATETIME,MAX_YEAR_IN_DATETIME]֮��
        * @param [in] paramMonth ָ�����·ݣ���Ч���·���[1,12]֮��
		* @param [in] paramDay ָ�������ڣ���Ч��������[1,CalcMonthDays]֮��
		* @return ����ָ�����ڴ�Ԫ��1��1�տ�ʼ������
		* @exception XEDateTimeError �����ݡ��·ݡ�������Ч�����׳��쳣
		*/
		XInt CalcDays(XInt paramYear, XInt paramMonth, XInt paramDay)
		{
			//������
			if( paramYear < MIN_YEAR_IN_DATETIME || paramYear > MAX_YEAR_IN_DATETIME ) return INVALID_DAYS;
			//����·�
			if( paramMonth < MIN_MONTH_IN_YEAR || paramMonth > MAX_MONTH_IN_YEAR ) return INVALID_DAYS;
			//�������
			XInt aMonthDays = CalcMonthDays(paramYear, paramMonth, false);
			if (aMonthDays == INVALID_DAYS) {
				return INVALID_DAYS;
			}

			if( paramDay < MIN_DAY_IN_MONTH || paramDay > aMonthDays ) return INVALID_DAYS;

			XInt iDays = 0;

			for(XInt i=1; i<paramMonth; i++) iDays += CalcMonthDays(paramYear, i, false);

			paramYear --;
			iDays += ( (paramYear*365) + (paramYear/4) - (paramYear/100) + (paramYear/400)); //�������������
			iDays += paramDay;                                                   //���ϵ�ǰ�µ�����
			return iDays;
		}
	}
}
