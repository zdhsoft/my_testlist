///字符串相关的函数
/**
 * 字符串相关的函数
 * 由于GCC对Unicode支持不是很好，加上服务器一般不需要Unicode处理，所以关闭了这里linux下对unicode字符串的函数。windows下不受影响。
 * 注：GCC中的vswprintf和vsprintf的函数处理方式是不一样的，具体可以查帮助。
 * zdhsoft 2011 版权所有
 *
 * @file xstring_utils.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-08
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、字符串相关的函数

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-08  1.0             创建初始文件
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
        ///检查是否为字母字符
        template<class T>
        inline bool isLetter( T paramCh )
        {
            return (paramCh >= 'a' && paramCh <='z') || (paramCh >='A' && paramCh <= 'Z');
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为数字字符
        template<class T>
        inline bool isDigit( T paramCh)
        {
            return paramCh >= '0' && paramCh <='9';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为回车符
        template<class T>
        inline bool isEnter(T paramCh) 
        {
            return paramCh == 13;
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为换行符
        template<class T>
        inline bool isNewLine(T paramCh)
        {
            return paramCh == 10;
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否是空格符
        template<class T>
        inline bool isSpace(T paramCh)
        {
            return paramCh == ' ';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否是tab制表符
        template<class T>
        inline bool isTab(T paramCh)
        {
            return paramCh == 9;
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否则0字符
        template<class T>
        inline bool isZero(T paramCh) 
        {
            return paramCh == 0;
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否则双引号
        template<class T>
        inline bool isQuote(T paramCh)
        {
            return paramCh == '\"';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否则单引号
        template<class T>
        inline bool isApos(T paramCh)
        {
            return paramCh == '\'';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否转定义符
        template<class T>
        inline bool isTransport(T paramCh)
        {
            return paramCh == '\\';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为左中括号
        template<class T>
        inline bool isBracketLeft(T paramCh)
        {
            return paramCh == '[';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为右中括号
        template<class T>
        inline bool isBracketRight(T paramCh) 
        {
            return paramCh == ']';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为#号
        template<class T>
        inline bool isNumbersign(T paramCh)
        {
            return paramCh == '#';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为分号
        template<class T>
        inline bool isSemicolon(T paramCh)
        {
            return paramCh == ';';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为=号
        template<class C>
        bool isEqual(C paramCh)
        {
            return paramCh == '=';
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为ini的空格
        template<class C>
        bool isIniSpaceChar(C paramCh)
        {
            return paramCh == ' ' || paramCh == 9;
        }
        //-----------------------------------------------------------------------------------------------------
        ///检查是否为ini的注释字符
        template<class C>
        bool isIniComment(C paramCh)
        {
            return paramCh =='#' || paramCh == ';';
        }
        //-----------------------------------------------------------------------------------------------------
        ///取字符串的长度
        /**
            @param [in] paramValue 要取得长度的字符串指针
            @return 返回取得长度
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
        ///比较两个字符串
        /**
            @param [in] paramValue1 字符串1
            @param [in] paramValue2 字符串2
            @return 返回字符串比较结果
                - >0 表示paramValue1 > paramValue2
                - 0 表示paramValue1等于paramValue2
                - <0 表示paramValue1 < paramValue2
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
        ///不分大小写比较两个字符串
        /**
            @param [in] paramValue1 字符串1
            @param [in] paramValue2 字符串2
            @return 返回字符串比较结果
                - >0 表示paramValue1 > paramValue2
                - 0 表示paramValue1等于paramValue2
                - <0 表示paramValue1 < paramValue2
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
        ///指定比较的字符数的字符串比较
        /**
            @param [in] paramValue1 字符串1
            @param [in] paramValue2 字符串2
            @param [in] paramN      要比较的字符数，要求该值大于等于0
            @return 返回字符串比较结果
                - >0 表示paramValue1 > paramValue2
                - 0 表示paramValue1等于paramValue2
                - <0 表示paramValue1 < paramValue2
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
        ///指定比较的字符数的字符串不分大小比较
        /**
            @param [in] paramValue1 字符串1
            @param [in] paramValue2 字符串2
            @param [in] paramN      要比较的字符数，要求该值大于等于0
            @return 返回字符串比较结果
                - >0 表示paramValue1 > paramValue2
                - 0 表示paramValue1等于paramValue2
                - <0 表示paramValue1 < paramValue2
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
        ///将32位无符号整数转换为16进制字符串
        /**
            将32位无符号整数转换为16进制字符串
            @param [in] paramValue 被转换的整数
            @param [out] paramBuffer 保存结果的整数,要求大小至少要12字节
            @param [in] paramHexWidth 16进制的宽度，有效宽度1～8
            @param [in] paramHexStyle 十六进制的样式，A表示用大写，a表示用小写
            @param [in] paramHexPrefix 表示是否要加0x前缀,true表示加该前缀，false表示不加该前缀 
            @return 返回转换后的串指针
        */
        template<class T>
        static T * DWordToHex(XDWord paramValue, T * paramBuffer, XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            ZDH_ASSERT( paramBuffer != NULL );
            T * p = paramBuffer;
            //确定十六进制数据的长度
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
            //确定值
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

            //将不足宽度的地方补0
            for(XInt i = iRealWidth; i < iWidth; i++)   
            {
                *d++ = 0;
            }
            //如果有前缀
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
        ///将32位有符号整数转换为16进制字符串
        /**
            将32位有符号整数转换为16进制字符串
            @param [in] paramValue 被转换的整数
            @param [out] paramBuffer 保存结果的整数,要求大小至少要12字节
            @param [in] paramHexWidth 16进制的宽度，有效宽度1～8
            @param [in] paramHexStyle 十六进制的样式，A表示用大写，a表示用小写
            @param [in] paramHexPrefix 表示是否要加0x前缀,true表示加该前缀，false表示不加该前缀 
            @return 返回转换后的串指针
        */      
        template<class T>
        inline T * IntToHex(XInt paramValue, T * paramBuffer, XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            return DWordToHex((XDWord)paramValue, paramBuffer, paramHexWidth, paramHexStyle, paramHexPrefix);
        }
        //-----------------------------------------------------------------------------------------------------
        ///将64位无符号整数转换为16进制字符串
        /**
            将64位无符号整数转换为16进制字符串
            @param [in] paramValue 被转换的整数
            @param [out] paramBuffer 保存结果的整数,要求大小至少要12字节
            @param [in] paramHexWidth 16进制的宽度，有效宽度1～16
            @param [in] paramHexStyle 十六进制的样式，A表示用大写，a表示用小写
            @param [in] paramHexPrefix 表示是否要加0x前缀,true表示加该前缀，false表示不加该前缀 
            @return 返回转换后的串指针
        */
        template<class T>
        static T * DDWordToHex(XDDWord paramValue, T * paramBuffer, XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            ZDH_ASSERT( paramBuffer != NULL );
            T * p = paramBuffer;
            //确定十六进制数据的长度
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
            //确定值
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

            //将不足宽度的地方补0
            for(XInt i = iRealWidth; i < iWidth; i++)   
            {
                *d++ = 0;
            }
            //如果有前缀
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
        ///将64位有符号整数转换为16进制字符串
        /**
            将64位有符号整数转换为16进制字符串
            @param [in] paramValue 被转换的整数
            @param [out] paramBuffer 保存结果的整数,要求大小至少要12字节
            @param [in] paramHexWidth 16进制的宽度，有效宽度1～16
            @param [in] paramHexStyle 十六进制的样式，A表示用大写，a表示用小写
            @param [in] paramHexPrefix 表示是否要加0x前缀,true表示加该前缀，false表示不加该前缀 
            @return 返回转换后的串指针
        */      
        template<class T>
        inline T * LongToHex(XLong paramValue, T * paramBuffer, XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            return DDWordToHex((XDDWord)paramValue, paramBuffer, paramHexWidth, paramHexStyle, paramHexPrefix);
        }
        //-----------------------------------------------------------------------------------------------------
        ///将32位无符号整数，转换为字符串
        /**
            @param [in] paramValue 将要被转换的无符号整数
            @param [out] paramBuffer 用于保存结果的缓冲区，要求缓冲区至少33字节。
            @param [in] paramRadix 表示转换的进制，默认为10进制,有效进制范围在2到36之间。
            @param [in] paramHexStyle 表示大于9的数字表示方式。默认为'A'
                - a 表示大于10的位数，都是小写字符
                - A 表示大于10的位数，都是大写字符
            @return T * 返回转换后的字符串，实际为paramBuffer的指针。
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
        ///将32位有符号整数，转换为字符串
        /**
            @param [in] paramValue 将要被转换的整数
            @param [out] paramBuffer 用于保存结果的缓冲区，要求缓冲区至少33字节。
            @param [in] paramRadix 表示转换的进制，默认为10进制,有效进制范围在2到36之间。
            @param [in] paramHexStyle 表示大于9的数字表示方式。默认为'A'
                - a 表示大于10的位数，都是小写字符
                - A 表示大于10的位数，都是大写字符
            @return T * 返回转换后的字符串，实际为paramBuffer的指针。
        */
        template<class T>
        static T * IntToStr(XInt paramValue, T * paramBuffer, XInt paramRadix = 10, T paramHexStyle = 'A')
        {
            ZDH_ASSERT(paramBuffer != NULL);
            T * p = paramBuffer;
            XDWord dwV;

            if( paramRadix >= 2 && paramRadix <= 36 )
            {
                //如果整数
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
        ///将64位有符号整数转换为字符串
        /**
            @param [in] paramValue 被转换的64位整数
            @param [out] paramBuffer 存放转换后的字符串,要求至少要传入65个字符，否则有可能溢出。
            @param [in] paramRadix 转换后的进制，2表示二进制，16表示十六进制，10表示十进制，该值范围是2到36。
            @param [in] paramHexStyle 
                - a 表示大于10的位数，都是小写字符
                - A 表示大于10的位数，都是大写字符
            @return 返回转换的结果。实际上返回的是参数aBuff的值
        */
        template<class T>
        static T * LongToStr(XLong paramValue,T * paramBuffer,XInt paramRadix = 10,T paramHexStyle = 'A')
        {
            ZDH_ASSERT(paramBuffer!=NULL);
            T * p = paramBuffer;
            XDDWord ddwV;
            //如果是有效的进制
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
        ///将64位有符号整数转换为字符串
        /**
            @param [in] paramValue 被转换的64位整数
            @param [out] paramBuffer 存放转换后的字符串,要求至少要传入65个字符，否则有可能溢出。
            @param [in] paramRadix 转换后的进制，2表示二进制，16表示十六进制，10表示十进制，该值范围是2到36。
            @param [in] paramHexStyle 
                - a 表示大于10的位数，都是小写字符
                - A 表示大于10的位数，都是大写字符
            @return 返回转换的结果。实际上返回的是参数aBuff的值
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
            if( isNULL(paramNumberString) ) 
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
        //----------------------------------------------------------------------------
        /**
              尝试将字符串转换为32位无符号整数，能够自动识别十进制和十六进制数。
              @param [in] paramNumberString 被转换的数值字符串
              @param [out] paramValue 用于保存转换后的数值
              @return 返回尝试转换的状态
                - true 表示转换成功
                - false 表示转换失败，这个时候aValue的值为0
         */
        template<class T>
        static bool TryStringToDWord(const T * paramNumberString, XDWord & paramValue)
        {
            paramValue = 0; //设置初始值
            if( isNULL(paramNumberString) )
            {
                return true;
            }
            bool HexFlag = false;
            const T *p = paramNumberString;
            //跳过导前空格
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
                // DWord的十六进制字符串最多有8个字节
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
                //  最大值是 4294967295 (0xFFFFFFFF)
                const XDWord ABS_MAX_DWORD_DIV10 = 429496729u;
                const XDWord ABS_MAX_DWORD_MOD10 = 5u;

                while (*p != 0)
                {
                    T chNumber = *p;
                    //如果是无效数字
                    if (chNumber < '0' || chNumber > '9')
                    {
                        return false;
                    }
                    //如果将会超过最大除10整数
                    if( dwValue > ABS_MAX_DWORD_DIV10 )
                    {
                        return false;
                    }

                    XDWord v = chNumber - '0';
                    //如果将会超过最大整数
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

            if( isNULL(paramNumberString) ) 
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
        //----------------------------------------------------------------------------
        /**
              尝试将字符串转换为64位无符号整数，能够自动识别十进制和十六进制数。
              @param [in] paramNumberString 被转换的数值字符串
              @param [out] paramValue 用于保存转换后的数值
              @return 返回尝试转换的状态
                - true 表示转换成功
                - false 表示转换失败，这个时候aValue的值为0
         */
        template<class T>
        static bool TryStringToDDWord(const T * paramNumberString, XDDWord & paramValue)
        {
            paramValue = 0; //设置初始值为0

            if( isNULL(paramNumberString) ) 
            {
                return true;
            }
            bool HexFlag = false; //定义十六进制标志符，默认为false。
            
            const T *p = paramNumberString;
            //跳过空格
            while(*p == ' ') 
            {
                p++;
            }
            //判断字符串为十进制的还是十六进制，并对hex赋值。
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
                
            if (HexFlag)// 对十六进制数的字符串进行转换。
            {
                // XDDWord的十六进制字符串最多有16个字节
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
            else//对十进制的数的字符串进行转换。
            {
                // 最大值是 18446744073709551615LL (0xFFFFFFFFFFFFFFFF)

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
                        return false;//转化后的整数值越界，则转化失败。
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
              尝试将字符串转换为32位有符号整数，能够自动识别十进制和十六进制数。
              @param [in] paramNumberString 被转换的数值字符串
              @param [in] paramDefault 缺少数值
              @return XInt 返回转换后的整数
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
              尝试将字符串转换为32位无符号整数，能够自动识别十进制和十六进制数。
              @param [in] paramNumberString 被转换的数值字符串
              @param [in] paramDefault 缺少数值
              @return XDWord 返回转换后的整数
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
              尝试将字符串转换为64位有符号整数，能够自动识别十进制和十六进制数。
              @param [in] paramNumberString 被转换的数值字符串
              @param [in] paramDefault 缺少数值
              @return XLong 返回转换后的整数
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
              尝试将字符串转换为64位无符号整数，能够自动识别十进制和十六进制数。
              @param [in] paramNumberString 被转换的数值字符串
              @param [in] paramDefault 缺少数值
              @return XDDWord 返回转换后的整数
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
        ///将字符串中的小写字符转换为大写字符
        /**
            @param [in,out] 被转换的字符串
            @return T * 转换后的字符串
                这里转换后的字符串与参数中的字符串相同
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
        ///将字符串中的大写字符转换为小写字符
        /**
        @param [in,out] 被转换的字符串
        @return T * 转换后的字符串
        这里转换后的字符串与参数中的字符串相同
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
        ///去除字符串的左边空格
        /**
            请注意,请正确传入字符串的长度
            @param [in,out] paramString 被去除空格的字符串
            @param [in] paramLength 传入字符串的长度
            @return XInt 返回去除空格后，字符串的长度
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
                //找到第一个非空格字符串            
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pStart) ) break;
                    pStart ++;
                }
                //复制数据,并计算新字符串的长度
                T * pDest = paramString;
                iRet = (XInt)(pEnd + 1 - pStart);
                while( pStart <= pEnd )
                {
                    *pDest ++ = *pStart ++;
                }
                //设置字符串结尾符
                *pDest = 0;
            }
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///去除字符串的右边空格
        /**
            请注意,请正确传入字符串的长度
            @param [in,out] paramString 被去除空格的字符串
            @param [in] paramLength 传入字符串的长度
            @return XInt 返回去除空格后，字符串的长度
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
                //反向查找一个非空格字符
                while( pStart <= pEnd )
                {
                    if( !isSpaceTab(*pEnd) ) break;
                    pEnd --;
                }
                *(pEnd + 1) = 0;
                iRet = (XInt)(pEnd + 1 - pStart);
            }
            //返回字符数
            return iRet;
        }
        //-----------------------------------------------------------------------------------------------------
        ///清除左右两边的字符串
        /**
            请注意,请正确传入字符串的长度
            @param [in,out] paramString 被去除空格的字符串
            @param [in] paramLength 传入字符串的长度
            @return XInt 返回去除空格后，字符串的长度
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
        ///去除字符串的左边空格
        /**
            @param [in,out] paramString 被去除空格的字符串
            @return T * 返回去除空格后的字符串
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
        ///去除字符串的右边空格
        /**
            @param [in,out] paramString 被去除空格的字符串
            @return T * 返回去除空格后的字符串
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
        ///去除字符串的左右两边空格
        /**
            @param [in,out] paramString 被去除空格的字符串
            @return T * 返回去除空格后的字符串
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
        ///字符串复制
        /**
            @param [out] paramDest 存放要复制字符串的指针
            @param [in] paramSrc 源字符串的指针
            @reutrn T * 返回存放复制字符串后指针
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
        ///字符串复制(指定最大复制字符数
        /**
            @param [out] paramDest 存放要复制字符串的指针
            @param [in] paramSrc 源字符串的指针
            @param [in] paramN 最大复制的字符数
            @reutrn T * 返回存放复制字符串后指针
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
        ///将中文Unicode转换为Ansi多字节字符串
        /**
            @param [out] paramDest 保存转换后的字符串
            @param [in] paramSource 原始的Unicode字符串
            @param [in] paramDestBytes 用于保存转换后字符串的内存字节数
            @return XInt 返回被转换后的字符个数(不含结尾0)
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
        ///将中文Ansi多字节转换为Unicode字符串
        /**
            @param [out] paramDest 保存转换后的字符串
            @param [in] paramSource 原始的Unicode字符串
            @param [in] paramDestBytes 用于保存转换后字符串的内存字节数
            @return XInt 返回被转换后的字符个数(不含结尾0)
         */
        inline XInt ChineseMultByteToUnicode(XWideChar * paramDest, const XChar * paramSource,XInt paramDestByte)
        {
            setlocale(LC_ALL, "chs"); 
            size_t iCharCount = mbstowcs(paramDest, paramSource, paramDestByte);
            setlocale(LC_ALL,"C");
            return (XInt)iCharCount;
        }
        //-----------------------------------------------------------------------------------------------------
        ///指定格式化生成字符串
        /**
            这个函数当缓冲区不够存放字符串的时候，会返回-1。
            但结果还是会写到缓冲区。

            @param [in] paramBuffer 要保存结果的缓冲区，要求有足够的空间
            @param [in] paramBufferSize 保存结果缓冲区的字符数
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] paramList 格式化的参数列表
            @return XInt 放回格式化字符串的长度,不含结尾0的字符个数
                - -1 表示缓冲区的字节数不够
                - >0 表示格式化字符串的长度,不含结尾0的字符个数
         */
        inline XInt zdh_vsnprintf(XChar * paramBuffer, XInt paramBufferSize,const XChar* paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramBufferSize > 0);
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
        #if defined(CONFIG_VC)          
            XInt iRet = _vsnprintf(paramBuffer, paramBufferSize, paramFormat, paramList);
            if (iRet == -1) 
            {   //VC在这里没有加0结尾，有可能会造成越界访问
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
        ///指定格式化生成字符串
        /**
            这个函数当缓冲区不够存放字符串的时候，会返回-1。
            但结果还是会写到缓冲区。
            @param [in] paramBuffer 要保存结果的缓冲区，要求有足够的空间
            @param [in] paramBufferSize 保存结果缓冲区的字符数
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] ... 格式化的参数列表
            @return XInt 放回格式化字符串的长度,不含结尾0的字符个数
                - -1 表示缓冲区的字节数不够
                - >0 表示格式化字符串的长度,不含结尾0的字符个数
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
        ///计算格式化字符串后的字符数
        /**
            这个函数只是计算格式化字符串后的字符数
            计算的结果不含结尾0
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] paramList 格式化的参数列表
            @return XInt 返回格式化字符串的长度
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
        ///计算格式化字符串后的字符数
        /**
            这个函数只是计算格式化字符串后的字符数
            计算的结果不含结尾0
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] ... 格式化的参数列表
            @return XInt 返回格式化字符串的长度
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
        ///指定格式化生成字符串
        /**
            注意:有可能存在溢出的问题，不建议使用该函数。推荐使用zdh_vsnprintf
            @param [in] paramBuffer 要保存结果的缓冲区，要求有足够的空间
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] paramList 格式化的参数列表
            @return XInt 返回格式化字符串的长度,不含结尾0的字符个数
         */
        inline XInt zdh_vsprintf(XChar * paramBuffer, const XChar* paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            return vsprintf(paramBuffer, paramFormat, paramList);
        }
        //-----------------------------------------------------------------------------------------------------
        ///指定格式化生成字符串
        /**
            注意:有可能存在溢出的问题，不建议使用该函数。推荐使用zdh_snprintf
            @param [in] paramBuffer 要保存结果的缓冲区，要求有足够的空间
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] ... 格式化的参数列表
            @return XInt 返回格式化字符串的长度,不含结尾0的字符个数
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
        ///指定格式化生成字符串
        /**
            这个函数当缓冲区不够存放字符串的时候，会返回-1。
            但结果还是会写到缓冲区。

            @param [in] paramBuffer 要保存结果的缓冲区，要求有足够的空间
            @param [in] paramBufferSize 保存结果缓冲区的字符数
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] paramList 格式化的参数列表
            @return XInt 放回格式化字符串的长度,不含结尾0的字符个数
                - -1 表示缓冲区的字节数不够
                - >0 表示格式化字符串的长度,不含结尾0的字符个数
         */
        inline XInt zdh_vsnprintf(XWideChar * paramBuffer, XInt paramBufferSize,const XWideChar* paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramBufferSize > 0);
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            XInt iRet = _vsnwprintf(paramBuffer, paramBufferSize, paramFormat, paramList);
            if (iRet == -1) 
            {   //VC在这里没有加0结尾，有可能会造成越界访问
                paramBuffer[paramBufferSize-1] = 0;  
            }
            return iRet;

        }
        //-----------------------------------------------------------------------------------------------------
        ///指定格式化生成字符串
        /**
            这个函数当缓冲区不够存放字符串的时候，会返回-1。
            但结果还是会写到缓冲区。
            @param [in] paramBuffer 要保存结果的缓冲区，要求有足够的空间
            @param [in] paramBufferSize 保存结果缓冲区的字符数
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] ... 格式化的参数列表
            @return XInt 放回格式化字符串的长度,不含结尾0的字符个数
                - -1 表示缓冲区的字节数不够
                - >0 表示格式化字符串的长度,不含结尾0的字符个数
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
        ///计算格式化字符串后的字符数
        /**
            这个函数只是计算格式化字符串后的字符数
            计算的结果不含结尾0
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] paramList 格式化的参数列表
            @return XInt 返回格式化字符串的长度
         */
        inline XInt zdh_vscprintf(const XWideChar * paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramFormat != NULL);
            return _vscwprintf(paramFormat, paramList);
        }
        //-----------------------------------------------------------------------------------------------------
        ///计算格式化字符串后的字符数
        /**
            这个函数只是计算格式化字符串后的字符数
            计算的结果不含结尾0
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] ... 格式化的参数列表
            @return XInt 返回格式化字符串的长度
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
        ///指定格式化生成字符串
        /**
            注意:有可能存在溢出的问题，不建议使用该函数。推荐使用zdh_vsnprintf
            @param [in] paramBuffer 要保存结果的缓冲区，要求有足够的空间
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] paramList 格式化的参数列表
            @return XInt 返回格式化字符串的长度,不含结尾0的字符个数
         */
        inline XInt zdh_vsprintf(XWideChar * paramBuffer, const XWideChar* paramFormat, va_list paramList)
        {
            ZDH_ASSERT(paramBuffer != NULL);
            ZDH_ASSERT(paramFormat != NULL);
            return vswprintf(paramBuffer, paramFormat, paramList);
        }
        //-----------------------------------------------------------------------------------------------------
        ///指定格式化生成字符串
        /**
            注意:有可能存在溢出的问题，不建议使用该函数。推荐使用zdh_snprintf
            @param [in] paramBuffer 要保存结果的缓冲区，要求有足够的空间
            @param [in] paramFormat 格式化串,参考标准C的格式化串
            @param [in] ... 格式化的参数列表
            @return XInt 返回格式化字符串的长度,不含结尾0的字符个数
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

