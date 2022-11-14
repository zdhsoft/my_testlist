//---------------------------------------------------------------------------

#ifndef utilsH
#define utilsH
#include <cstdio>
#include "typedef.h"
//---------------------------------------------------------------------------
namespace zdh {
	namespace utils {
		//-----------------------------------------------------------------------------------------------------
		///�ж�ָ��ֵ�Ƿ�Ϊ��
		template<class T>
		inline bool IsNULL(const T * param_pointer)
		{
			return param_pointer == NULL || param_pointer == nullptr;
		}
        ///ȡ�ַ����ĳ���
        /**
            @param [in] paramValue Ҫȡ�ó��ȵ��ַ���ָ��
            @return ����ȡ�ó���
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
              ���Խ��ַ���ת��Ϊ64λ�з����������ܹ��Զ�ʶ��ʮ���ƺ�ʮ����������
              @param [in] paramNumberString ��ת������ֵ�ַ���
              @param [out] paramValue ���ڱ���ת�������ֵ
              @return ���س���ת����״̬
                - true ��ʾת���ɹ�
                - false ��ʾת��ʧ�ܣ����ʱ��aValue��ֵΪ0
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
            //�����ո�
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
                // INT64��ʮ�������ַ��������16���ֽ�
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
                //  ������Сֵ�� -9223372036854775808LL (0x8000000000000000), ���ֵ�� 9223372036854775807LL (0x7FFFFFFFFFFFFFFF)
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

                            // ��Ϊ��ҪintValueʼ����������, �����ֵ�� 2147483647
                            // �����ʱv=8, �����������
                            if (v == ABS_MIN_LONG_INT_MOD10)
                            {
                                // �������û���ַ���, ˵����������һ���ַ�, ��ô�������������Сֵ
                                // ֮�����������˳�, ��Ϊ�˷�ֹ�������ֵ���
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
