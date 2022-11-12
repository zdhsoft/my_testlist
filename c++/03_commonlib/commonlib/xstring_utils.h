///�ַ�����صĺ���
/**
 * �ַ�����صĺ���
 * ����GCC��Unicode֧�ֲ��Ǻܺã����Ϸ�����һ�㲻��ҪUnicode�������Թر�������linux�¶�unicode�ַ����ĺ�����windows�²���Ӱ�졣
 * ע��GCC�е�vswprintf��vsprintf�ĺ�������ʽ�ǲ�һ���ģ�������Բ������
 * zdhsoft 2011 ��Ȩ����
 *
 * @file xstring_utils.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-08
 * company zdhsoft
 */
/**********************************************************************
    �����б�  //��Ҫ��������
    1���ַ�����صĺ���

    ��ʷ:       //��Ҫ�޸ļ�¼
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-08  1.0             ������ʼ�ļ�
***********************************************************************/
#ifndef _X_STRING_UTILS_H_
#define _X_STRING_UTILS_H_
#include <xtype.h>
#include <xmemory.h>
#include <cassert>
#include <string>
#include <clocale>
#include <cstdlib>

#if defined(OS_WINDOWS)
    #include <windows.h>
#elif defined(OS_LINUX)
    #include <wchar.h>
#else
    #error "not supperted"
#endif

#include <cstdio>
#include <cstdarg>

#include <iostream>

namespace zdh
{

    //-----------------------------------------------------------------------------------------------------
    namespace string_utils
    {
        //-----------------------------------------------------------------------------------------------------
        template<class T>
        inline bool isSpaceTab( T paramCh )
        {
            return paramCh == ' ' || paramCh == '\t';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊ��ĸ�ַ�
        template<class T>
        inline bool isLetter( T paramCh )
        {
            return (paramCh >= 'a' && paramCh <='z') || (paramCh >='A' && paramCh <= 'Z');
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊ�����ַ�
        template<class T>
        inline bool isDigit( T paramCh)
        {
            return paramCh >= '0' && paramCh <='9';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊ�س���
        template<class T>
        inline bool isEnter(T paramCh) 
        {
            return paramCh == 13;
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊ���з�
        template<class T>
        inline bool isNewLine(T paramCh)
        {
            return paramCh == 10;
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ��ǿո��
        template<class T>
        inline bool isSpace(T paramCh)
        {
            return paramCh == ' ';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ���tab�Ʊ��
        template<class T>
        inline bool isTab(T paramCh)
        {
            return paramCh == 9;
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ���0�ַ�
        template<class T>
        inline bool isZero(T paramCh) 
        {
            return paramCh == 0;
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ���˫����
        template<class T>
        inline bool isQuote(T paramCh)
        {
            return paramCh == '\"';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�������
        template<class T>
        inline bool isApos(T paramCh)
        {
            return paramCh == '\'';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�ת�����
        template<class T>
        inline bool isTransport(T paramCh)
        {
            return paramCh == '\\';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊ��������
        template<class T>
        inline bool isBracketLeft(T paramCh)
        {
            return paramCh == '[';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊ��������
        template<class T>
        inline bool isBracketRight(T paramCh) 
        {
            return paramCh == ']';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊ#��
        template<class T>
        inline bool isNumbersign(T paramCh)
        {
            return paramCh == '#';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊ�ֺ�
        template<class T>
        inline bool isSemicolon(T paramCh)
        {
            return paramCh == ';';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊ=��
        template<class C>
        bool isEqual(C paramCh)
        {
            return paramCh == '=';
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊini�Ŀո�
        template<class C>
        bool isIniSpaceChar(C paramCh)
        {
            return paramCh == ' ' || paramCh == 9;
        }
        //-----------------------------------------------------------------------------------------------------
        ///����Ƿ�Ϊini��ע���ַ�
        template<class C>
        bool isIniComment(C paramCh)
        {
            return paramCh =='#' || paramCh == ';';
        }
        //-----------------------------------------------------------------------------------------------------
        ///ȡ�ַ����ĳ���
        /**
            @param [in] paramValue Ҫȡ�ó��ȵ��ַ���ָ��
            @return ����ȡ�ó���
        */
        template<class T>
        static XInt Length(const T * paramValue)
        {
            ZDH_ASSERT(paramValue != NULL);
            XInt iRet = 0;
            while( *paramValue != 0 )
            {
                paramValue ++;
                iRet ++;
            }
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///�Ƚ������ַ���
        /**
            @param [in] paramValue1 �ַ���1
            @param [in] paramValue2 �ַ���2
            @return �����ַ����ȽϽ��
                - >0 ��ʾparamValue1 > paramValue2
                - 0 ��ʾparamValue1����paramValue2
                - <0 ��ʾparamValue1 < paramValue2
        */
        template<class T>
        static XInt Compare(const T * paramValue1, const T * paramValue2)
        {
            ZDH_ASSERT(paramValue1 != NULL);
            ZDH_ASSERT(paramValue2 != NULL);
            XInt iRet;
            do 
            {
                iRet = *paramValue1 - *paramValue2;
                if( (iRet == 0) && (*paramValue1 != 0) && (*paramValue2 != 0) )
                {
                    paramValue1 ++;
                    paramValue2 ++;
                }
                else break;
            } while ( !iRet );
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///���ִ�Сд�Ƚ������ַ���
        /**
            @param [in] paramValue1 �ַ���1
            @param [in] paramValue2 �ַ���2
            @return �����ַ����ȽϽ��
                - >0 ��ʾparamValue1 > paramValue2
                - 0 ��ʾparamValue1����paramValue2
                - <0 ��ʾparamValue1 < paramValue2
        */
        template<class T>
        static XInt CompareIC(const T * paramValue1, const T * paramValue2)
        {
            ZDH_ASSERT(paramValue1 != NULL);
            ZDH_ASSERT(paramValue2 != NULL);
            XInt iRet;
            do 
            {
                T ch1 = *paramValue1;
                T ch2 = *paramValue2;
                if( ch1 <= 'Z' && ch1 >= 'A' ) ch1 += 32;
                if( ch2 <= 'Z' && ch2 >= 'A' ) ch2 += 32;
                iRet = ch1 - ch2;

                if( (iRet == 0) && (ch1 != 0) && (ch2 != 0) )
                {
                    paramValue1 ++;
                    paramValue2 ++;
                }
                else break;
            } while ( !iRet );
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///ָ���Ƚϵ��ַ������ַ����Ƚ�
        /**
            @param [in] paramValue1 �ַ���1
            @param [in] paramValue2 �ַ���2
            @param [in] paramN      Ҫ�Ƚϵ��ַ�����Ҫ���ֵ���ڵ���0
            @return �����ַ����ȽϽ��
                - >0 ��ʾparamValue1 > paramValue2
                - 0 ��ʾparamValue1����paramValue2
                - <0 ��ʾparamValue1 < paramValue2
        */
        template<class T>
        static XInt NCompare(const T * paramValue1, const T * paramValue2, XInt paramN)
        {
            ZDH_ASSERT(paramValue1 != NULL);
            ZDH_ASSERT(paramValue2 != NULL);
            ZDH_ASSERT(paramN >= 0);
            if( paramN == 0 ) return 0;
            XInt iRet;
            do 
            {
                iRet = *paramValue1 - *paramValue2;
                paramN --;
                if( (iRet == 0) && (*paramValue1 != 0) && (*paramValue2 != 0) && paramN > 0)
                {
                    paramValue1 ++;
                    paramValue2 ++;
                }
                else break;
            } while ( 1 );
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///ָ���Ƚϵ��ַ������ַ������ִ�С�Ƚ�
        /**
            @param [in] paramValue1 �ַ���1
            @param [in] paramValue2 �ַ���2
            @param [in] paramN      Ҫ�Ƚϵ��ַ�����Ҫ���ֵ���ڵ���0
            @return �����ַ����ȽϽ��
                - >0 ��ʾparamValue1 > paramValue2
                - 0 ��ʾparamValue1����paramValue2
                - <0 ��ʾparamValue1 < paramValue2
        */
        template<class T>
        static XInt NCompareIC(const T * paramValue1, const T * paramValue2, XInt paramN)
        {
            ZDH_ASSERT(paramValue1 != NULL);
            ZDH_ASSERT(paramValue2 != NULL);
            ZDH_ASSERT(paramN >= 0);
            if( paramN == 0 ) return 0;
            XInt iRet;
            do 
            {
                T ch1 = *paramValue1;
                T ch2 = *paramValue2;
                if( ch1 <= 'Z' && ch1 >= 'A' ) ch1 += 32;
                if( ch2 <= 'Z' && ch2 >= 'A' ) ch2 += 32;
                iRet = ch1 - ch2;
                paramN --;
                if( (iRet == 0) && (*paramValue1 != 0) && (*paramValue2 != 0) && paramN > 0)
                {
                    paramValue1 ++;
                    paramValue2 ++;
                }
                else break;
            } while ( 1 );
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///��32λ�޷�������ת��Ϊ16�����ַ���
        /**
            ��32λ�޷�������ת��Ϊ16�����ַ���
            @param [in] paramValue ��ת��������
            @param [out] paramBuffer ������������,Ҫ���С����Ҫ12�ֽ�
            @param [in] paramHexWidth 16���ƵĿ�ȣ���Ч���1��8
            @param [in] paramHexStyle ʮ�����Ƶ���ʽ��A��ʾ�ô�д��a��ʾ��Сд
            @param [in] paramHexPrefix ��ʾ�Ƿ�Ҫ��0xǰ׺,true��ʾ�Ӹ�ǰ׺��false��ʾ���Ӹ�ǰ׺ 
            @return ����ת����Ĵ�ָ��
        */
        template<class T>
        static T * DWordToHex(XDWord paramValue, T * paramBuffer, XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            ZDH_ASSERT( paramBuffer != NULL );
            T * p = paramBuffer;
            //ȷ��ʮ���������ݵĳ���
            XInt iWidth;
            if( paramHexWidth > 8 ) 
            {
                iWidth = 8;
            }
            else if( paramHexWidth < 1) 
            {
                iWidth = 1;
            }
            else 
            {
                iWidth = paramHexWidth;
            }
            //ȷ��ֵ
            XDWord dwValue = paramValue;
            //
            T charArray[8];
            T * d = charArray;
            XInt iRealWidth = 0;
            do 
            {
                *d++ = T(dwValue % 16);
                iRealWidth ++;
                dwValue >>= 4;
                if( dwValue == 0 )
                {
                    break;
                }

            } while (1);

            //�������ȵĵط���0
            for(XInt i = iRealWidth; i < iWidth; i++)   
            {
                *d++ = 0;
            }
            //�����ǰ׺
            if( paramHexPrefix )
            {
                *p++ = '0';
                *p++ = 'x';
            }
            T ch;
            while (d != charArray)
            {
                --d;
                ch = *d;
                if( ch < 10 ) 
                {
                    *p++ = ch + '0';
                }
                else 
                {
                    * p++ = T(ch - 10 + paramHexStyle);
                }
            }
            *p = 0;
            //
            return paramBuffer;
        }
        //-----------------------------------------------------------------------------------------------------
        ///��32λ�з�������ת��Ϊ16�����ַ���
        /**
            ��32λ�з�������ת��Ϊ16�����ַ���
            @param [in] paramValue ��ת��������
            @param [out] paramBuffer ������������,Ҫ���С����Ҫ12�ֽ�
            @param [in] paramHexWidth 16���ƵĿ�ȣ���Ч���1��8
            @param [in] paramHexStyle ʮ�����Ƶ���ʽ��A��ʾ�ô�д��a��ʾ��Сд
            @param [in] paramHexPrefix ��ʾ�Ƿ�Ҫ��0xǰ׺,true��ʾ�Ӹ�ǰ׺��false��ʾ���Ӹ�ǰ׺ 
            @return ����ת����Ĵ�ָ��
        */      
        template<class T>
        inline T * IntToHex(XInt paramValue, T * paramBuffer, XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            return DWordToHex((XDWord)paramValue, paramBuffer, paramHexWidth, paramHexStyle, paramHexPrefix);
        }
        //-----------------------------------------------------------------------------------------------------
        ///��64λ�޷�������ת��Ϊ16�����ַ���
        /**
            ��64λ�޷�������ת��Ϊ16�����ַ���
            @param [in] paramValue ��ת��������
            @param [out] paramBuffer ������������,Ҫ���С����Ҫ12�ֽ�
            @param [in] paramHexWidth 16���ƵĿ�ȣ���Ч���1��16
            @param [in] paramHexStyle ʮ�����Ƶ���ʽ��A��ʾ�ô�д��a��ʾ��Сд
            @param [in] paramHexPrefix ��ʾ�Ƿ�Ҫ��0xǰ׺,true��ʾ�Ӹ�ǰ׺��false��ʾ���Ӹ�ǰ׺ 
            @return ����ת����Ĵ�ָ��
        */
        template<class T>
        static T * DDWordToHex(XDDWord paramValue, T * paramBuffer, XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            ZDH_ASSERT( paramBuffer != NULL );
            T * p = paramBuffer;
            //ȷ��ʮ���������ݵĳ���
            XInt iWidth;
            if( paramHexWidth > 16 ) 
            {
                iWidth = 16;
            }
            else if( paramHexWidth < 1) 
            {
                iWidth = 1;
            }
            else
            {
                iWidth = paramHexWidth;
            }
            //ȷ��ֵ
            XDDWord ddwValue = paramValue;
            //
            T charArray[16];
            T * d = charArray;
            XInt iRealWidth = 0;
            do 
            {
                *d++ = T(ddwValue % 16);
                iRealWidth ++;
                ddwValue >>= 4;
                if( ddwValue == 0 ) 
                {
                    break;
                }

            } while (1);

            //�������ȵĵط���0
            for(XInt i = iRealWidth; i < iWidth; i++)   
            {
                *d++ = 0;
            }
            //�����ǰ׺
            if( paramHexPrefix )
            {
                *p++ = '0';
                *p++ = 'x';
            }
            T ch;
            while (d != charArray)
            {
                --d;
                ch = *d;
                if( ch < 10 ) 
                {
                    *p++ = ch + '0';
                }
                else 
                {
                    * p++ = T(ch - 10 + paramHexStyle);
                }
            }
            *p = 0;
            //
            return paramBuffer;
        }
        //-----------------------------------------------------------------------------------------------------
        ///��64λ�з�������ת��Ϊ16�����ַ���
        /**
            ��64λ�з�������ת��Ϊ16�����ַ���
            @param [in] paramValue ��ת��������
            @param [out] paramBuffer ������������,Ҫ���С����Ҫ12�ֽ�
            @param [in] paramHexWidth 16���ƵĿ�ȣ���Ч���1��16
            @param [in] paramHexStyle ʮ�����Ƶ���ʽ��A��ʾ�ô�д��a��ʾ��Сд
            @param [in] paramHexPrefix ��ʾ�Ƿ�Ҫ��0xǰ׺,true��ʾ�Ӹ�ǰ׺��false��ʾ���Ӹ�ǰ׺ 
            @return ����ת����Ĵ�ָ��
        */      
        template<class T>
        inline T * LongToHex(XLong paramValue, T * paramBuffer, XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            return DDWordToHex((XDDWord)paramValue, paramBuffer, paramHexWidth, paramHexStyle, paramHexPrefix);
        }
        //-----------------------------------------------------------------------------------------------------
        ///��32λ�޷���������ת��Ϊ�ַ���
        /**
            @param [in] paramValue ��Ҫ��ת�����޷�������
            @param [out] paramBuffer ���ڱ������Ļ�������Ҫ�󻺳�������33�ֽڡ�
            @param [in] paramRadix ��ʾת���Ľ��ƣ�Ĭ��Ϊ10����,��Ч���Ʒ�Χ��2��36֮�䡣
            @param [in] paramHexStyle ��ʾ����9�����ֱ�ʾ��ʽ��Ĭ��Ϊ'A'
                - a ��ʾ����10��λ��������Сд�ַ�
                - A ��ʾ����10��λ�������Ǵ�д�ַ�
            @return T * ����ת������ַ�����ʵ��ΪparamBuffer��ָ�롣
        */      
        template<class T>
        static T * DWordToStr(XDWord paramValue, T * paramBuffer, XInt paramRadix = 10, T paramHexStyle = 'A')
        {
            T * p = paramBuffer;
            XDWord dwV;

            if( paramRadix >= 2 && paramRadix <= 36 )
            {
                T _buf[33];
                T *bufp = _buf;
                dwV = (XDWord)paramValue;
                for(;;)
                {
                    *bufp++ = T(dwV % paramRadix);
                    dwV /= paramRadix;
                    if( dwV == 0 ) break;
                }
                T ch;
                while (bufp != _buf)
                {
                    --bufp;
                    ch = *bufp;
                    if( ch < 10 ) *p++ = ch+'0';
                    else *p++ = T(ch - 10 + paramHexStyle);
                }
            }
            *p = '\0';
            return paramBuffer;
        }
        //-----------------------------------------------------------------------------------------------------
        ///��32λ�з���������ת��Ϊ�ַ���
        /**
            @param [in] paramValue ��Ҫ��ת��������
            @param [out] paramBuffer ���ڱ������Ļ�������Ҫ�󻺳�������33�ֽڡ�
            @param [in] paramRadix ��ʾת���Ľ��ƣ�Ĭ��Ϊ10����,��Ч���Ʒ�Χ��2��36֮�䡣
            @param [in] paramHexStyle ��ʾ����9�����ֱ�ʾ��ʽ��Ĭ��Ϊ'A'
                - a ��ʾ����10��λ��������Сд�ַ�
                - A ��ʾ����10��λ�������Ǵ�д�ַ�
            @return T * ����ת������ַ�����ʵ��ΪparamBuffer��ָ�롣
        */
        template<class T>
        static T * IntToStr(XInt paramValue, T * paramBuffer, XInt paramRadix = 10, T paramHexStyle = 'A')
        {
            ZDH_ASSERT(paramBuffer != NULL);
            T * p = paramBuffer;
            XDWord dwV;

            if( paramRadix >= 2 && paramRadix <= 36 )
            {
                //�������
                if( paramValue < 0  && paramRadix == 10 )
                {
                    *p++ = '-';
                    dwV = (XDWord)(-paramValue);
                }
                else 
                {
                    dwV = (XDWord)paramValue;
                }

                T _buf[33];
                T *bufp = _buf;
                for(;;)
                {
                    *bufp++ = T(dwV % paramRadix);
                    dwV /= paramRadix;
                    if( dwV == 0 ) break;
                }
                T ch;
                while (bufp != _buf)
                {
                    --bufp;
                    ch = *bufp;
                    if( ch < 10 ) *p++ = ch+'0';
                    else *p++ = T(ch - 10 + paramHexStyle);
                }
            }
            *p = '\0';
            return paramBuffer;
        }
        //----------------------------------------------------------------------------
        ///��64λ�з�������ת��Ϊ�ַ���
        /**
            @param [in] paramValue ��ת����64λ����
            @param [out] paramBuffer ���ת������ַ���,Ҫ������Ҫ����65���ַ��������п��������
            @param [in] paramRadix ת����Ľ��ƣ�2��ʾ�����ƣ�16��ʾʮ�����ƣ�10��ʾʮ���ƣ���ֵ��Χ��2��36��
            @param [in] paramHexStyle 
                - a ��ʾ����10��λ��������Сд�ַ�
                - A ��ʾ����10��λ�������Ǵ�д�ַ�
            @return ����ת���Ľ����ʵ���Ϸ��ص��ǲ���aBuff��ֵ
        */
        template<class T>
        static T * LongToStr(XLong paramValue,T * paramBuffer,XInt paramRadix = 10,T paramHexStyle = 'A')
        {
            ZDH_ASSERT(paramBuffer!=NULL);
            T * p = paramBuffer;
            XDDWord ddwV;
            //�������Ч�Ľ���
            if( paramRadix >= 2 && paramRadix <= 36 )
            {
                if( paramValue < 0 )
                {
                    *p++ = '-';
                    ddwV = XDDWord(-paramValue);
                }
                else
                {
                    ddwV = XDDWord(paramValue);
                }
                T _buf[65];
                T *bufp = _buf;
                for(;;)
                {
                    *bufp++ = T(ddwV % paramRadix);
                    ddwV /= paramRadix;
                    if( ddwV == 0 ) 
                    {
                        break;
                    }
                }
                T ch;
                while (bufp != _buf)
                {
                    --bufp;
                    ch = *bufp;
                    if( ch < 10 ) *p++ = ch+'0';
                    else *p++ = T( ch - 10 + paramHexStyle);
                }
            }
            *p = '\0';
            return paramBuffer;
        }
        //----------------------------------------------------------------------------
        ///��64λ�з�������ת��Ϊ�ַ���
        /**
            @param [in] paramValue ��ת����64λ����
            @param [out] paramBuffer ���ת������ַ���,Ҫ������Ҫ����65���ַ��������п��������
            @param [in] paramRadix ת����Ľ��ƣ�2��ʾ�����ƣ�16��ʾʮ�����ƣ�10��ʾʮ���ƣ���ֵ��Χ��2��36��
            @param [in] paramHexStyle 
                - a ��ʾ����10��λ��������Сд�ַ�
                - A ��ʾ����10��λ�������Ǵ�д�ַ�
            @return ����ת���Ľ����ʵ���Ϸ��ص��ǲ���aBuff��ֵ
        */
        template<class T>
        static T * DDWordToStr(XDDWord paramValue,T *paramBuffer,XInt paramRadix = 10,T paramHexStyle = 'A' )
        {
            ZDH_ASSERT(paramBuffer != NULL);
            T * p = paramBuffer;
            if( paramRadix >= 2 && paramRadix <=36 )
            {
                T _buf[65];
                T *bufp = _buf;
                for(;;)
                {
                    *bufp++ = T( paramValue % paramRadix);
                    paramValue /= paramRadix;
                    if( paramValue == 0 ) 
                    {
                        break;
                    }
                }
                T ch;
                while (bufp != _buf)
                {
                    --bufp;
                    ch = *bufp;
                    if( ch < 10 ) 
                    {
                        *p++ = ch+'0';
                    }
                    else 
                    {
                        *p++ = XChar(ch-10 + paramHexStyle);
                    }
                }
            }
            *p = '\0';
            return paramBuffer;
        }
        //-----------------------------------------------------------------------------------------------------
        ///���Խ��ַ���ת��Ϊ32λ�з�������ģ��
        /**
         �� ���Խ��ַ���ת��Ϊ32λ�з����������ܹ��Զ�ʶ��ʮ���ƺ�ʮ����������
            @param [in] paramNumberString ��ת������ֵ�ַ���
            @param [out] paramValue ���ڱ���ת�������ֵ
            @return ���س���ת����״̬
                - true ��ʾת���ɹ�
                - false ��ʾת��ʧ�ܣ����ʱ��aValue��ֵΪ0
         */
        template<class T>
        static bool TryStringToInt(const T * paramNumberString, XInt & paramValue)
        {
            //�ȳ�ʼ��Ϊ0
            paramValue = 0;
            if( isNULL(paramNumberString) ) 
            {
                return true;
            }

            bool bNegativeFlag = false; //������־
            bool bHexFlag = false;      //ʮ�����Ʊ�־

            const T *p = paramNumberString;
            //�����ո�
            while(*p == ' ') 
            {
                p++;
            }

            //������λ
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
            case '$': //if $..,x..,X..��ͷ������Ϊʮ������
            case 'x':
            case 'X':
                bHexFlag = true;
                ++p;
                break;
            case '0': //if 0x..,0X..��ͷ������Ϊʮ������
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
                // INT32��ʮ�������ַ��������8���ֽ�
                if (Length(p) > 8) 
                {
                    return false;
                }
                XInt iValue = 0;
                while (*p != 0) 
                {
                    XInt v;
                    T chNumber = *p;
                    if (chNumber >= '0' && chNumber <= '9') //�����0..9
                    {
                        v = chNumber - '0';
                    }
                    else if (chNumber >= 'a' && chNumber <= 'f') //�����a..f
                    {
                        v = chNumber - 'a' + 10;
                    }
                    else if (chNumber >= 'A' && chNumber <= 'F') //�����A..F
                    {
                        v = chNumber - 'A' + 10;
                    }
                    else  //�����Ƿ������˳�
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
                //  ������Сֵ�� -2147483648 (0x80000000), ���ֵ�� 2147483647 (0x7FFFFFFF)
                const XInt ABS_MIN_INT_DIV10 = 214748364;
                const XInt ABS_MIN_INT_MOD10 = 8;
                const XInt ABS_MAX_INT_DIV10 = 214748364;
                const XInt ABS_MAX_INT_MOD10 = 7;

                XInt iValue = 0;

                while (*p != 0)
                {
                    T chNumber = *p;
                    if (chNumber < '0' ||chNumber > '9') //������ֳ�����Ч���ַ������ʾת��ʧ��
                    {
                        return false;
                    }

                    XInt v = chNumber - '0';

                    if (bNegativeFlag) //����Ǹ���
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

                            // ��Ϊ��ҪintValueʼ����������, �����ֵ�� 2147483647
                            // �����ʱv=8, �����������
                            if (v == ABS_MIN_INT_MOD10)
                            {
                                // �������û���ַ���, ˵����������һ���ַ�, ��ô�������������Сֵ
                                // ֮�����������˳�, ��Ϊ�˷�ֹ�������ֵ���
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
                    else //����ǷǸ���
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
        //----------------------------------------------------------------------------
        /**
              ���Խ��ַ���ת��Ϊ32λ�޷����������ܹ��Զ�ʶ��ʮ���ƺ�ʮ����������
              @param [in] paramNumberString ��ת������ֵ�ַ���
              @param [out] paramValue ���ڱ���ת�������ֵ
              @return ���س���ת����״̬
                - true ��ʾת���ɹ�
                - false ��ʾת��ʧ�ܣ����ʱ��aValue��ֵΪ0
         */
        template<class T>
        static bool TryStringToDWord(const T * paramNumberString, XDWord & paramValue)
        {
            paramValue = 0; //���ó�ʼֵ
            if( isNULL(paramNumberString) )
            {
                return true;
            }
            bool HexFlag = false;
            const T *p = paramNumberString;
            //������ǰ�ո�
            while(*p == ' ')
            {
                p++;
            }
            switch(*p) 
            {
            case 0:
                return false;
            case '$':
            case 'x':
            case 'X':
                HexFlag = true;
                ++p;
                break;
            case '0':
                HexFlag = ((*(p+1) == 'x') || (*(p+1) == 'X')); 
                if (HexFlag) 
                {
                    p += 2;
                }
                break;
            }

            if (*p == 0) 
            {
                return false;
            }

            XDWord dwValue = 0;
            if (HexFlag)
            {
                // DWord��ʮ�������ַ��������8���ֽ�
                if (Length(p) > 8) 
                {
                    return false;
                }

                while (*p != 0) 
                {
                    XDWord v;
                    T chNumber = *p;

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
                    dwValue *= 16;
                    dwValue += v;
                    ++p;
                }
            }
            else
            {
                //  ���ֵ�� 4294967295 (0xFFFFFFFF)
                const XDWord ABS_MAX_DWORD_DIV10 = 429496729u;
                const XDWord ABS_MAX_DWORD_MOD10 = 5u;

                while (*p != 0)
                {
                    T chNumber = *p;
                    //�������Ч����
                    if (chNumber < '0' || chNumber > '9')
                    {
                        return false;
                    }
                    //������ᳬ������10����
                    if( dwValue > ABS_MAX_DWORD_DIV10 )
                    {
                        return false;
                    }

                    XDWord v = chNumber - '0';
                    //������ᳬ���������
                    if (dwValue == ABS_MAX_DWORD_DIV10 && v > ABS_MAX_DWORD_MOD10) 
                    {
                        return false;       
                    }
                    //dwValue = dwValue * 10 + v;
                    dwValue *= 10;
                    dwValue += v;
                    ++p;
                }
            }
            paramValue = dwValue;
            return true;
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

            if( isNULL(paramNumberString) ) 
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
        //----------------------------------------------------------------------------
        /**
              ���Խ��ַ���ת��Ϊ64λ�޷����������ܹ��Զ�ʶ��ʮ���ƺ�ʮ����������
              @param [in] paramNumberString ��ת������ֵ�ַ���
              @param [out] paramValue ���ڱ���ת�������ֵ
              @return ���س���ת����״̬
                - true ��ʾת���ɹ�
                - false ��ʾת��ʧ�ܣ����ʱ��aValue��ֵΪ0
         */
        template<class T>
        static bool TryStringToDDWord(const T * paramNumberString, XDDWord & paramValue)
        {
            paramValue = 0; //���ó�ʼֵΪ0

            if( isNULL(paramNumberString) ) 
            {
                return true;
            }
            bool HexFlag = false; //����ʮ�����Ʊ�־����Ĭ��Ϊfalse��
            
            const T *p = paramNumberString;
            //�����ո�
            while(*p == ' ') 
            {
                p++;
            }
            //�ж��ַ���Ϊʮ���ƵĻ���ʮ�����ƣ�����hex��ֵ��
            switch(*p) 
            {
            case 0:
                return false;
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

            XDDWord ddwValue = 0;
                
            if (HexFlag)// ��ʮ�����������ַ�������ת����
            {
                // XDDWord��ʮ�������ַ��������16���ֽ�
                if (Length(p) > 16) 
                {
                    return false;
                }
        
                while (*p != 0) 
                {
                    XByte v;
                    T chNumber = *p;
                    
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
                    ddwValue *= 16;
                    ddwValue += v;
                    ++p;
                }
            }
            else//��ʮ���Ƶ������ַ�������ת����
            {
                // ���ֵ�� 18446744073709551615LL (0xFFFFFFFFFFFFFFFF)

                const XDDWord ABS_MAX_DDWORD_DIV10 = 1844674407370955161ULL;
                const XDDWord ABS_MAX_DDWORD_MOD10 = 5ULL;
                
                while (*p != 0)
                {
                    T chNumber = *p;

                    if (chNumber < '0' || chNumber > '9') 
                    {
                        return false;
                    }
                    
                    XByte v = chNumber - '0';
                    
                    if (ddwValue > ABS_MAX_DDWORD_DIV10) 
                    {
                        return false;//ת���������ֵԽ�磬��ת��ʧ�ܡ�
                    }
                        
                    if (ddwValue == ABS_MAX_DDWORD_DIV10 && v > ABS_MAX_DDWORD_MOD10) 
                    {
                        return false;
                    }
                    ddwValue *= 10;
                    ddwValue += v;
                    ++p;
                }
                //paramValue =  ddwValue;
            }
            paramValue = ddwValue;

            return true;        
        }
        //----------------------------------------------------------------------------
        /**
              ���Խ��ַ���ת��Ϊ32λ�з����������ܹ��Զ�ʶ��ʮ���ƺ�ʮ����������
              @param [in] paramNumberString ��ת������ֵ�ַ���
              @param [in] paramDefault ȱ����ֵ
              @return XInt ����ת���������
         */
        template<class T>
        inline XInt StringToIntDef(const T * paramNumberString, XInt paramDefault = 0)
        {
            XInt iRet;
            if( !TryStringToInt(paramNumberString,iRet) ) 
            {
                iRet = paramDefault;
            }
            return iRet;
        }
        //----------------------------------------------------------------------------
        /**
              ���Խ��ַ���ת��Ϊ32λ�޷����������ܹ��Զ�ʶ��ʮ���ƺ�ʮ����������
              @param [in] paramNumberString ��ת������ֵ�ַ���
              @param [in] paramDefault ȱ����ֵ
              @return XDWord ����ת���������
         */
        template<class T>
        inline XDWord StringToDWordDef(const T * paramNumberString, XDWord paramDefault = 0)
        {
            XDWord dwRet;
            if( !TryStringToDWord(paramNumberString,dwRet) ) 
            {
                dwRet = paramDefault;
            }
            return dwRet;
        }
        //----------------------------------------------------------------------------
        /**
              ���Խ��ַ���ת��Ϊ64λ�з����������ܹ��Զ�ʶ��ʮ���ƺ�ʮ����������
              @param [in] paramNumberString ��ת������ֵ�ַ���
              @param [in] paramDefault ȱ����ֵ
              @return XLong ����ת���������
         */
        template<class T>
        inline XLong StringToLongDef(const T * paramNumberString, XLong paramDefault = 0)
        {
            XLong lngRet;
            if( !TryStringToLong(paramNumberString,lngRet) ) 
            {
                lngRet = paramDefault;
            }
            return lngRet;
        }
        //----------------------------------------------------------------------------
        /**
              ���Խ��ַ���ת��Ϊ64λ�޷����������ܹ��Զ�ʶ��ʮ���ƺ�ʮ����������
              @param [in] paramNumberString ��ת������ֵ�ַ���
              @param [in] paramDefault ȱ����ֵ
              @return XDDWord ����ת���������
         */
        template<class T>
        inline XDDWord StringToDDWordDef(const T * paramNumberString, XDDWord paramDefault = 0)
        {
            XDDWord ddwRet;
            if( !TryStringToDDWord(paramNumberString,ddwRet) ) 
            {
                ddwRet = paramDefault;
            }
            return ddwRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///���ַ����е�Сд�ַ�ת��Ϊ��д�ַ�
        /**
            @param [in,out] ��ת�����ַ���
            @return T * ת������ַ���
                ����ת������ַ���������е��ַ�����ͬ
         */
        template<class T>
        static T * UpperCase(T * paramString)
        {
            ZDH_ASSERT(paramString != NULL);
            T * pString = paramString;
            T ch;
            do
            {
                ch = *pString;
                if( ch <= 'z' && ch >= 'a' )
                {
                    *pString = ch - 32;
                }
                pString++;

            }while(ch != 0);
            return paramString;         
        }
        //-----------------------------------------------------------------------------------------------------
        ///���ַ����еĴ�д�ַ�ת��ΪСд�ַ�
        /**
        @param [in,out] ��ת�����ַ���
        @return T * ת������ַ���
        ����ת������ַ���������е��ַ�����ͬ
        */
        template<class T>
        static T * LowerCase(T * paramString)
        {
            ZDH_ASSERT(paramString != NULL);
            T * pString = paramString;
            T ch;
            do
            {
                ch = *pString;
                if( ch <= 'Z' && ch >= 'A' )
                {
                    *pString = ch + 32;
                }
                pString++;

            }while(ch != 0);
            return paramString; 
        }
        //-----------------------------------------------------------------------------------------------------
        ///ȥ���ַ�������߿ո�
        /**
            ��ע��,����ȷ�����ַ����ĳ���
            @param [in,out] paramString ��ȥ���ո���ַ���
            @param [in] paramLength �����ַ����ĳ���
            @return XInt ����ȥ���ո���ַ����ĳ���
         */
        template<class T>
        static XInt TrimLeft(T * paramString,XInt paramLength)
        {
            ZDH_ASSERT(Length(paramString) == paramLength);
            XInt iRet = 0;
            if( paramLength > 0)
            {
                T * pStart = paramString;
                T * pEnd = paramString + paramLength - 1;
                //�ҵ���һ���ǿո��ַ���            
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pStart) ) break;
                    pStart ++;
                }
                //��������,���������ַ����ĳ���
                T * pDest = paramString;
                iRet = (XInt)(pEnd + 1 - pStart);
                while( pStart <= pEnd )
                {
                    *pDest ++ = *pStart ++;
                }
                //�����ַ�����β��
                *pDest = 0;
            }
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///ȥ���ַ������ұ߿ո�
        /**
            ��ע��,����ȷ�����ַ����ĳ���
            @param [in,out] paramString ��ȥ���ո���ַ���
            @param [in] paramLength �����ַ����ĳ���
            @return XInt ����ȥ���ո���ַ����ĳ���
         */
        template<class T>
        static XInt TrimRight(T * paramString,XInt paramLength)
        {
            ZDH_ASSERT(Length(paramString) == paramLength);
            XInt iRet = 0;
            if( paramLength > 0)
            {
                T * pStart = paramString;
                T * pEnd = paramString + paramLength - 1;
                //�������һ���ǿո��ַ�
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pEnd) ) break;
                    pEnd --;
                }
                *(pEnd + 1) = 0;
                iRet = (XInt)(pEnd + 1 - pStart);
            }
            //�����ַ���
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///����������ߵ��ַ���
        /**
            ��ע��,����ȷ�����ַ����ĳ���
            @param [in,out] paramString ��ȥ���ո���ַ���
            @param [in] paramLength �����ַ����ĳ���
            @return XInt ����ȥ���ո���ַ����ĳ���
         */
        template<class T>
        static XInt Trim(T * paramString,XInt paramLength)
        {
            ZDH_ASSERT(Length(paramString) == paramLength);
            XInt iRet = 0;
            if( paramLength > 0)
            {
                T * pStart = paramString;
                T * pEnd = paramString + paramLength - 1;
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pStart) ) break;
                    pStart ++;
                }
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pEnd) ) break;
                    pEnd --;
                }
                T * pDest = paramString;
                iRet = (XInt)(pEnd + 1 - pStart);
                while( pStart <= pEnd )
                {
                    *pDest ++ = *pStart ++;
                }
                *pDest = 0;
            }
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///ȥ���ַ�������߿ո�
        /**
            @param [in,out] paramString ��ȥ���ո���ַ���
            @return T * ����ȥ���ո����ַ���
         */
        template<class T>
        static T * TrimLeft(T * paramString)
        {
            XInt iLength = Length(paramString);
            if( iLength > 0)
            {
                T * pStart = paramString;
                T * pEnd = paramString + iLength - 1;
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pStart) ) break;
                    pStart ++;
                }
                T * pDest = paramString;
                while( pStart <= pEnd )
                {
                    *pDest ++ = *pStart ++;
                }
                *pDest = 0;
            }
            return paramString;
        }
        //-----------------------------------------------------------------------------------------------------
        ///ȥ���ַ������ұ߿ո�
        /**
            @param [in,out] paramString ��ȥ���ո���ַ���
            @return T * ����ȥ���ո����ַ���
         */
        template<class T>
        static T * TrimRight(T * paramString)
        {
            XInt iLength = Length(paramString);
            if( iLength > 0)
            {
                T * pStart = paramString;
                T * pEnd = paramString + iLength - 1;
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pEnd) ) break;
                    pEnd --;
                }
                *(pEnd + 1) = 0;
            }
            return paramString;
        }
        //-----------------------------------------------------------------------------------------------------
        ///ȥ���ַ������������߿ո�
        /**
            @param [in,out] paramString ��ȥ���ո���ַ���
            @return T * ����ȥ���ո����ַ���
         */
        template<class T>
        static T * Trim(T * paramString)
        {
            XInt iLength = Length(paramString);
            if( iLength > 0)
            {
                T * pStart = paramString;
                T * pEnd = paramString + iLength - 1;
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pStart) ) break;
                    pStart ++;
                }
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pEnd)) break;
                    pEnd --;
                }
                T * pDest = paramString;
                while( pStart <= pEnd )
                {
                    *pDest ++ = *pStart ++;
                }
                *pDest = 0;
            }
            return paramString;
        }
        //-----------------------------------------------------------------------------------------------------
        ///�ַ�������
        /**
            @param [out] paramDest ���Ҫ�����ַ�����ָ��
            @param [in] paramSrc Դ�ַ�����ָ��
            @reutrn T * ���ش�Ÿ����ַ�����ָ��
         */
        template<class T>
        static T * StringCopy(T * paramDest, const T * paramSrc)
        {
            ZDH_ASSERT(paramDest != NULL);
            ZDH_ASSERT(paramSrc != NULL);
            T * pT = paramDest;
            while( *paramSrc )
            {
                *pT ++ = * paramSrc++;
            }
            *pT = 0;
            return paramDest;
        }
        //-----------------------------------------------------------------------------------------------------
        ///�ַ�������(ָ��������ַ���
        /**
            @param [out] paramDest ���Ҫ�����ַ�����ָ��
            @param [in] paramSrc Դ�ַ�����ָ��
            @param [in] paramN ����Ƶ��ַ���
            @reutrn T * ���ش�Ÿ����ַ�����ָ��
         */
        template<class T>
        static T * StringCopy(T * paramDest, const T * paramSrc,const XInt paramN)
        {
            ZDH_ASSERT(paramDest != NULL);
            ZDH_ASSERT(paramSrc != NULL);
            ZDH_ASSERT(paramN >= 0);
            XInt iN = paramN;
            T * pT = paramDest;
            while( *paramSrc && iN > 0 )
            {
                *pT ++ = * paramSrc++;
                iN--;
            }
            *pT = 0;
            return paramDest;
        }
        //-----------------------------------------------------------------------------------------------------
        ///������Unicodeת��ΪAnsi���ֽ��ַ���
        /**
            @param [out] paramDest ����ת������ַ���
            @param [in] paramSource ԭʼ��Unicode�ַ���
            @param [in] paramDestBytes ���ڱ���ת�����ַ������ڴ��ֽ���
            @return XInt ���ر�ת������ַ�����(������β0)
         */
        inline XInt ChineseUnicodeToMultByte(XChar * paramDest, const XWideChar * paramSource, XInt paramDestBytes)
        {
            XChar pCurLocale[50];
            StringCopy(pCurLocale,setlocale(LC_ALL,NULL),49);
            setlocale(LC_ALL,"chs");
            size_t iCharCount = wcstombs(paramDest, paramSource, paramDestBytes);
            setlocale(LC_ALL, pCurLocale);
            return (XInt)iCharCount;
        }
        //-----------------------------------------------------------------------------------------------------
        ///������Ansi���ֽ�ת��ΪUnicode�ַ���
        /**
            @param [out] paramDest ����ת������ַ���
            @param [in] paramSource ԭʼ��Unicode�ַ���
            @param [in] paramDestBytes ���ڱ���ת�����ַ������ڴ��ֽ���
            @return XInt ���ر�ת������ַ�����(������β0)
         */
        inline XInt ChineseMultByteToUnicode(XWideChar * paramDest, const XChar * paramSource,XInt paramDestByte)
        {
            setlocale(LC_ALL, "chs"); 
            size_t iCharCount = mbstowcs(paramDest, paramSource, paramDestByte);
            setlocale(LC_ALL,"C");
            return (XInt)iCharCount;
        }
        //-----------------------------------------------------------------------------------------------------
        ///ָ����ʽ�������ַ���
        /**
            �����������������������ַ�����ʱ�򣬻᷵��-1��
            ��������ǻ�д����������

            @param [in] paramBuffer Ҫ�������Ļ�������Ҫ�����㹻�Ŀռ�
            @param [in] paramBufferSize ���������������ַ���
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] paramList ��ʽ���Ĳ����б�
            @return XInt �Żظ�ʽ���ַ����ĳ���,������β0���ַ�����
                - -1 ��ʾ���������ֽ�������
                - >0 ��ʾ��ʽ���ַ����ĳ���,������β0���ַ�����
         */
        inline XInt zdh_vsnprintf(XChar * paramBuffer, XInt paramBufferSize,const XChar* paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramBufferSize > 0);
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
        #if defined(CONFIG_VC)          
            XInt iRet = _vsnprintf(paramBuffer, paramBufferSize, paramFormat, paramList);
            if (iRet == -1) 
            {   //VC������û�м�0��β���п��ܻ����Խ�����
                iRet = paramBufferSize - 1;
                paramBuffer[iRet] = 0;  
            }
            return iRet;
        #else
            XInt iRet = vsnprintf(paramBuffer, paramBufferSize, paramFormat, paramList);
            if (iRet >= paramBufferSize)
            {
                iRet = paramBufferSize - 1;
            }
            return iRet;
        #endif
        }
        //-----------------------------------------------------------------------------------------------------
        ///ָ����ʽ�������ַ���
        /**
            �����������������������ַ�����ʱ�򣬻᷵��-1��
            ��������ǻ�д����������
            @param [in] paramBuffer Ҫ�������Ļ�������Ҫ�����㹻�Ŀռ�
            @param [in] paramBufferSize ���������������ַ���
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] ... ��ʽ���Ĳ����б�
            @return XInt �Żظ�ʽ���ַ����ĳ���,������β0���ַ�����
                - -1 ��ʾ���������ֽ�������
                - >0 ��ʾ��ʽ���ַ����ĳ���,������β0���ַ�����
         */        
        inline XInt zdh_snprintf(XChar * paramBuffer, XInt paramBufferSize,const XChar* paramFormat, ...)
        {
            ZDH_ASSERT(paramBufferSize > 0);
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            va_list argptr;
            va_start(argptr, paramFormat);
            XInt iRet =  zdh_vsnprintf(paramBuffer, paramBufferSize, paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///�����ʽ���ַ�������ַ���
        /**
            �������ֻ�Ǽ����ʽ���ַ�������ַ���
            ����Ľ��������β0
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] paramList ��ʽ���Ĳ����б�
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        inline XInt zdh_vscprintf(const XChar * paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramFormat != NULL);
        #if defined(CONFIG_VC)  
            return _vscprintf(paramFormat, paramList);
        #else
            return vsnprintf(NULL, 0, paramFormat, paramList);
        #endif
        }
        //-----------------------------------------------------------------------------------------------------
        ///�����ʽ���ַ�������ַ���
        /**
            �������ֻ�Ǽ����ʽ���ַ�������ַ���
            ����Ľ��������β0
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] ... ��ʽ���Ĳ����б�
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        inline XInt zdh_scprintf(const XChar * paramFormat, ...)
        {
            ZDH_ASSERT(paramFormat != NULL);
            va_list argptr;
            va_start(argptr, paramFormat);    
            XInt iRet = zdh_vscprintf(paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///ָ����ʽ�������ַ���
        /**
            ע��:�п��ܴ�����������⣬������ʹ�øú������Ƽ�ʹ��zdh_vsnprintf
            @param [in] paramBuffer Ҫ�������Ļ�������Ҫ�����㹻�Ŀռ�
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] paramList ��ʽ���Ĳ����б�
            @return XInt ���ظ�ʽ���ַ����ĳ���,������β0���ַ�����
         */
        inline XInt zdh_vsprintf(XChar * paramBuffer, const XChar* paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            return vsprintf(paramBuffer, paramFormat, paramList);
        }
        //-----------------------------------------------------------------------------------------------------
        ///ָ����ʽ�������ַ���
        /**
            ע��:�п��ܴ�����������⣬������ʹ�øú������Ƽ�ʹ��zdh_snprintf
            @param [in] paramBuffer Ҫ�������Ļ�������Ҫ�����㹻�Ŀռ�
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] ... ��ʽ���Ĳ����б�
            @return XInt ���ظ�ʽ���ַ����ĳ���,������β0���ַ�����
         */
        inline XInt zdh_sprintf(XChar * paramBuffer, const XChar* paramFormat, ...)
        {
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            va_list argptr;
            va_start(argptr, paramFormat);
            XInt iRet = zdh_vsprintf(paramBuffer, paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }
        #if defined(OS_WINDOWS)
        //-----------------------------------------------------------------------------------------------------
        ///ָ����ʽ�������ַ���
        /**
            �����������������������ַ�����ʱ�򣬻᷵��-1��
            ��������ǻ�д����������

            @param [in] paramBuffer Ҫ�������Ļ�������Ҫ�����㹻�Ŀռ�
            @param [in] paramBufferSize ���������������ַ���
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] paramList ��ʽ���Ĳ����б�
            @return XInt �Żظ�ʽ���ַ����ĳ���,������β0���ַ�����
                - -1 ��ʾ���������ֽ�������
                - >0 ��ʾ��ʽ���ַ����ĳ���,������β0���ַ�����
         */
        inline XInt zdh_vsnprintf(XWideChar * paramBuffer, XInt paramBufferSize,const XWideChar* paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramBufferSize > 0);
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            XInt iRet = _vsnwprintf(paramBuffer, paramBufferSize, paramFormat, paramList);
            if (iRet == -1) 
            {   //VC������û�м�0��β���п��ܻ����Խ�����
                paramBuffer[paramBufferSize-1] = 0;  
            }
            return iRet;

        }
        //-----------------------------------------------------------------------------------------------------
        ///ָ����ʽ�������ַ���
        /**
            �����������������������ַ�����ʱ�򣬻᷵��-1��
            ��������ǻ�д����������
            @param [in] paramBuffer Ҫ�������Ļ�������Ҫ�����㹻�Ŀռ�
            @param [in] paramBufferSize ���������������ַ���
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] ... ��ʽ���Ĳ����б�
            @return XInt �Żظ�ʽ���ַ����ĳ���,������β0���ַ�����
                - -1 ��ʾ���������ֽ�������
                - >0 ��ʾ��ʽ���ַ����ĳ���,������β0���ַ�����
         */        
        inline XInt zdh_snprintf(XWideChar * paramBuffer, XInt paramBufferSize,const XWideChar* paramFormat, ...)
        {
            ZDH_ASSERT(paramBufferSize > 0);
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            va_list argptr;
            va_start(argptr, paramFormat);
            XInt iRet =  zdh_vsnprintf(paramBuffer, paramBufferSize, paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///�����ʽ���ַ�������ַ���
        /**
            �������ֻ�Ǽ����ʽ���ַ�������ַ���
            ����Ľ��������β0
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] paramList ��ʽ���Ĳ����б�
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        inline XInt zdh_vscprintf(const XWideChar * paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramFormat != NULL);
            return _vscwprintf(paramFormat, paramList);
        }
        //-----------------------------------------------------------------------------------------------------
        ///�����ʽ���ַ�������ַ���
        /**
            �������ֻ�Ǽ����ʽ���ַ�������ַ���
            ����Ľ��������β0
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] ... ��ʽ���Ĳ����б�
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        inline XInt zdh_scprintf(const XWideChar * paramFormat, ...)
        {
            ZDH_ASSERT(paramFormat != NULL);
            va_list argptr;
            va_start(argptr, paramFormat);    
            XInt iRet = zdh_vscprintf(paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///ָ����ʽ�������ַ���
        /**
            ע��:�п��ܴ�����������⣬������ʹ�øú������Ƽ�ʹ��zdh_vsnprintf
            @param [in] paramBuffer Ҫ�������Ļ�������Ҫ�����㹻�Ŀռ�
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] paramList ��ʽ���Ĳ����б�
            @return XInt ���ظ�ʽ���ַ����ĳ���,������β0���ַ�����
         */
        inline XInt zdh_vsprintf(XWideChar * paramBuffer, const XWideChar* paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            return vswprintf(paramBuffer, paramFormat, paramList);
        }
        //-----------------------------------------------------------------------------------------------------
        ///ָ����ʽ�������ַ���
        /**
            ע��:�п��ܴ�����������⣬������ʹ�øú������Ƽ�ʹ��zdh_snprintf
            @param [in] paramBuffer Ҫ�������Ļ�������Ҫ�����㹻�Ŀռ�
            @param [in] paramFormat ��ʽ����,�ο���׼C�ĸ�ʽ����
            @param [in] ... ��ʽ���Ĳ����б�
            @return XInt ���ظ�ʽ���ַ����ĳ���,������β0���ַ�����
         */
        inline XInt zdh_sprintf(XWideChar * paramBuffer, const XWideChar* paramFormat, ...)
        {
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            va_list argptr;
            va_start(argptr, paramFormat);
            XInt iRet = zdh_vsprintf(paramBuffer, paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }
        #endif
    }; /* namespace string_utils */

}
#endif

