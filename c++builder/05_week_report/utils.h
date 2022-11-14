//---------------------------------------------------------------------------

#ifndef utilsH
#define utilsH
#include <cstdio>
#include "typedef.h"
//---------------------------------------------------------------------------
namespace zdh {
	namespace utils {
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

	}
}
#endif
