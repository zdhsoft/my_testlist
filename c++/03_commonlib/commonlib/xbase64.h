///Base64编码实现
/**
 * Copyright (c) 2012 zdhsoft Inc. All rights reserved.
 * Base64编码实现
 * 这里的Base64编码的输出主要两种，一个XBuffer，推荐使用。另一这类视于C的实现，即XChar *，使用的时候确保
 * 有足够的空间存放编解码的结果
 * zdhsoft 2011 版权所有
 *
 * @file xbase64.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-17
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、Base64编码实现

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-17  1.0             创建初始文件
***********************************************************************/
#ifndef _X_BASE_64_H_
#define _X_BASE_64_H_
#include <xconfig.h>
#include <xtype.h>
#include <xbuffer.h>
#include <xstring.h>
namespace zdh
{
    const XChar BASE64_FILL_CHAR = '=';
    
    namespace base64
    {

        namespace detail
        {
            ///Base64编码表。
            template<class T>
            static const T * __EnBase64Tab()
            {
                static const T sEnBase64Tab[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
                return sEnBase64Tab;
            }
            ///Base64解码表。
            template<class T>
            static const T * __DeBase64Tab()
            {
                static const T sDeBase64Tab[256] =
                {
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3E,0xFF,0xFF,0xFF,0x3F,
                    0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
                    0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
                    0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
                };
                return sDeBase64Tab;
            }

            //-----------------------------------------------------------------------------------------------------
            ///Base64编码
            /**
                Base64编码函数，将3个字节转化为4个字节存储在数组dest[4]中。
                @param [in] paramSrc 要编码的内容 有paramUse告知内容字节数
                @param [out] paramDest 编码后存储
                @param [in] paramUse 要编码内容的字节数 该值只能是1,2,3
             */
            template<class S, class D>
            static void __EncodeBase64(const S * paramSrc,D paramDest[4],XInt paramUse = 3)
            {
                const D * pTab = __EnBase64Tab<D>();
                if( paramUse == 3 )
                {
                    paramDest[0] = pTab[(paramSrc[0] >>2) & 0x3f];
                    paramDest[1] = pTab[((paramSrc[0] & 0x03) << 4 ) | ((paramSrc[1]>>4) & 0x0f)];
                    paramDest[2] = pTab[((paramSrc[1] & 0x0f) << 2 ) | ((paramSrc[2]>>6) & 0x03)];
                    paramDest[3] = pTab[paramSrc[2] & 0x3f];
                } else if( paramUse == 2 )
                {
                    paramDest[0] = pTab[(paramSrc[0] >>2) & 0x3f];
                    paramDest[1] = pTab[((paramSrc[0] & 0x03) << 4 ) | ((paramSrc[1]>>4) & 0x0f)];
                    paramDest[2] = pTab[((paramSrc[1] & 0x0f) << 2 )];
                    paramDest[3] = BASE64_FILL_CHAR;
                }else if( paramUse == 1 )
                {
                    paramDest[0] = pTab[(paramSrc[0] >>2) & 0x3f];
                    paramDest[1] = pTab[((paramSrc[0] & 0x03) << 4 )];
                    paramDest[2] = BASE64_FILL_CHAR;
                    paramDest[3] = BASE64_FILL_CHAR;
                }
            }

            //-----------------------------------------------------------------------------------------------------
            ///Base64解码码函数
            /**
                Base64解码码函数,不作错误检查。
                @param [in] paramSrc 已编码的内容
                @param [out] paramDest 存放解码的数据
                @param [in] paramUse 已编码的内容的字节数 该值只能是1,2,3,4
                @return XInt 解码后的内容字节数
             */
            template<class T>
            static XInt  __DecodeBase64(const T * paramSrc,T * paramDest,XInt paramUse)
            {
                if( paramUse>4 || paramUse <0 ) return 0;
                XDWord dwTmp = 0;
                XInt iRet = 0;
                const T * pTab = __DeBase64Tab<T>();
                for(XInt iCount = 0; iCount<paramUse; iCount++)
                {
                    if( iCount>0 ) dwTmp <<= 6;
                    dwTmp |= pTab[ *paramSrc++ ];
                }
                if( paramUse == 4 )
                {
                    paramDest[2] = (T)dwTmp & 0xFF;
                    dwTmp >>= 8;
                    paramDest[1] = (T)dwTmp & 0xFF;
                    dwTmp >>= 8;
                    paramDest[0] = (T)dwTmp & 0xFF;
                    iRet = 3;
                }
                else if( paramUse == 3 )
                {
                    dwTmp>>=2;
                    paramDest[1] = (T)dwTmp & 0xFF;
                    dwTmp >>= 8;
                    paramDest[0] = (T)dwTmp & 0xFF;
                    iRet = 2;
                }
                else if( paramUse == 2 )
                {
                    dwTmp>>=4;
                    paramDest[0] = (T)dwTmp & 0xFF;
                    iRet = 1;
                }
                else if( paramUse == 1)
                {
                    paramDest[0] = (T)dwTmp & 0xFF;
                    iRet = 1;
                }
                return iRet;
            }

            //-----------------------------------------------------------------------------------------------------
            ///Base64解码码函数
            /**
                Base64解码码函数,作错误检查,出错退出。
                @param [in] paramSrc Base64编码的串 长度1-4字符
                @param [out] paramDest 保存解码的 
                @return XInt 解码后的数据字节数
                    - 1 解码的字节数1
                    - 2 解码的字节数2
                    - 3 解码的字节数3
             */
            template<class T>
            static XInt  __DecodeBase64Break(const T * paramSrc,T * paramDest)
            {
                XInt iUse = 4;
                XDWord dwTmp = 0;

                XInt iRet = 0;
                const T * pTab = __DeBase64Tab<T>();
                for(XInt iCount = 0; iCount<4; iCount++)
                {
                    T btTmp = pTab[ *paramSrc++ ];
                    if( btTmp == 0xFF ) //如果发现无效字符,则退出
                    {
                        iUse = iCount;
                        break;
                    }
                    if( iCount>0 ) dwTmp <<= 6;
                    dwTmp |= btTmp;
                }
                if( iUse == 4 )
                {
                    paramDest[2] = (T)dwTmp & 0xFF;
                    dwTmp >>= 8;
                    paramDest[1] = (T)dwTmp & 0xFF;
                    dwTmp >>= 8;
                    paramDest[0] = (T)dwTmp & 0xFF;
                    iRet = 3;
                }
                else if( iUse == 3 )
                {
                    dwTmp>>=2;
                    paramDest[1] = (T)dwTmp & 0xFF;
                    dwTmp >>= 8;
                    paramDest[0] = (T)dwTmp & 0xFF;
                    iRet = 2;
                }
                else if( iUse == 2 )
                {
                    dwTmp>>=4;
                    paramDest[0] = (T)dwTmp & 0xFF;
                    iRet = 1;
                }
                else if( iUse == 1)
                {
                    paramDest[0] = (T)dwTmp & 0xFF;
                    iRet = 1;
                }
                return iRet;
            }

            //-----------------------------------------------------------------------------------------------------
            ///没有返回类型的Base64解码函数，解码数据类型为未知类型。
            /**
                解码后的数据将放到XBuffer对象中。
                @param [in] paramSrcData 要解码的Base64编码数据
                @param [in] paramDataCount 要解码的数据个数
                @param [out] paramOutBuffer 保存结果的缓冲区
                @param [in] paramBreakByError 遇到错误是否要中断
                    - true 表示遇到错误要中断 默认值
                    - false 表示遇到错误不要中断
             */
            template<class T>
            static void DecodeBase64(const T * paramSrcData, XInt paramDataCount, XBuffer & paramOutBuffer, bool paramBreakByError = true)
            {
                XByte dest[3] = { 0,0,0 };
                paramOutBuffer.Clear();
                XInt srcLen = paramDataCount;
                const XByte * __srcData = (const XByte *)paramSrcData;
                if( srcLen > 0 )
                {
                    XInt int4Count = srcLen / 4;
                    XInt int4Free = srcLen % 4;
                    if( int4Free > 0 ) paramOutBuffer.ensureCapacity( (int4Count + 1) * 3 );//扩展OutBuffer的容量为4的整数倍。
                    else paramOutBuffer.ensureCapacity( int4Count * 3 );
                    if(paramBreakByError)
                    {
                        bool bExit = false;
                        for(XInt i=0;i<int4Count;i++)
                        {
                            XInt iCount = __DecodeBase64Break<XByte>(__srcData,dest);
                            if( iCount == 3 )
                            {
                                __srcData+=4;
                                paramOutBuffer.AppendData(dest, 3);
                            }
                            else
                            {
                                paramOutBuffer.AppendData(dest, iCount);
                                bExit = true;
                                break;
                            }
                        }
                        if( int4Free > 0 && !bExit )
                        {
                            XInt iCount = __DecodeBase64Break<XByte>(__srcData, dest);
                            paramOutBuffer.AppendData(dest,iCount);
                        }
                    }
                    else
                    {
                        for(XInt i=0; i<int4Count; i++)
                        {
                            XInt iCount = __DecodeBase64<XByte>(__srcData, dest, 4);
                            __srcData+=4;
                            paramOutBuffer.AppendData(dest,iCount);
                        }
                        if( int4Free > 0 )
                        {
                            XInt iCount = __DecodeBase64<XByte>(__srcData, dest, int4Free);
                            paramOutBuffer.AppendData(dest,iCount);
                        }
                    }
                }
            }

            //-----------------------------------------------------------------------------------------------------
            ///没有返回类型的Base64编码函数，原始数据类型为未知类型。
            /**
                @param [in] paramSrcData 要编码的数据
                @param [in] paramDataCount 要编码的数据字节数
                @param [out] paramOutBuffer 保存编码结果的缓冲区
             */
            template<class T>
            static void EncodeBase64(const T * paramSrcData,XInt paramDataCount,XBuffer & paramOutBuffer)
            {
                XChar dest[4];
                paramOutBuffer.Clear();//清除OutBuffer里的元素。
                XInt srcLen = paramDataCount;
                const XByte * __srcData = (const XByte *)paramSrcData;
                if( srcLen > 0 )
                {
                    XInt int3Count = srcLen / 3;
                    XInt int3Free = srcLen % 3;
                    //求出所需要的空间，空间字节数为4的倍数
                    if( int3Free > 0 ) paramOutBuffer.ensureCapacity( (int3Count+1) * 4 );
                    else paramOutBuffer.ensureCapacity( int3Count * 4 );

                    for(XInt i = 0;i < int3Count;i++)
                    {
                        __EncodeBase64<XByte,XChar>(__srcData,dest);
                        __srcData+=3;
                        paramOutBuffer.AppendData(dest,4);
                    }
                    if( int3Free > 0 ) //如果未被3整除
                    {
                        __EncodeBase64<XByte,XChar>(__srcData,dest,int3Free);
                        paramOutBuffer.AppendData(dest,4);
                    }
                }

            }

            //-----------------------------------------------------------------------------------------------------
            ///Base64解码函数，解码数据类型为未知类型。
            /**
                解码后的数据将放到指定的缓冲区，请确保缓冲足够保存解码的数据
                @param [in] paramSrcData 要解码的Base64编码数据
                @param [in] paramDataCount 要解码的数据个数
                @param [out] paramOutBuffer 保存结果的缓冲区
                @param [in] paramBreakByError 遇到错误是否要中断
                    - true 表示遇到错误要中断 默认值
                    - false 表示遇到错误不要中断
                @return XInt 返回解码后的数据字节数
             */
            template<class T>
            static XInt DecodeBase64(const T * paramSrcData, XInt paramDataCount, XChar * paramOutBuffer, bool paramBreakByError = true)
            {
                XByte dest[3] = { 0,0,0 };
                XChar * pDest = paramOutBuffer;
                XInt srcLen = paramDataCount;
                const XByte * __srcData = (const XByte *)paramSrcData;
                if( srcLen > 0 )
                {
                    XInt int4Count = srcLen / 4;
                    XInt int4Free = srcLen % 4;
                    if(paramBreakByError)
                    {
                        bool bExit = false;
                        for(XInt i=0; i<int4Count; i++)
                        {
                            XInt iCount = detail::__DecodeBase64Break<XByte>(__srcData, dest);
                            if( iCount == 3 )
                            {
                                __srcData += 4;
                                *pDest ++ = dest[0];
                                *pDest ++ = dest[1];
                                *pDest ++ = dest[2];
                            }
                            else
                            {
                                if (iCount > 0)
                                {
                                    *pDest ++ = dest[0];
                                }
                                if (iCount > 1)
                                {
                                    *pDest ++ = dest[1];
                                }
                                bExit = true;
                                break;
                            }
                        }
                        if( int4Free > 0 && !bExit )
                        {
                            XInt iCount = detail::__DecodeBase64Break<XByte>(__srcData, dest);
                            if (iCount > 0)
                            {
                                *pDest ++ = dest[0];
                            }
                            if (iCount > 1)
                            {
                                *pDest ++ = dest[1];
                            }
                            if (iCount > 3)
                            {
                                *pDest ++ = dest[2];
                            }
                        }
                    }
                    else
                    {
                        for(XInt i = 0; i < int4Count; i++)
                        {
                            XInt iCount = detail::__DecodeBase64(__srcData, dest, 4);
                            __srcData+=4;
                            if (iCount > 0)
                            {
                                *pDest ++ = dest[0];
                            }
                            if (iCount > 1)
                            {
                                *pDest ++ = dest[1];
                            }
                            if (iCount > 3)
                            {
                                *pDest ++ = dest[2];
                            }
                        }
                        if( int4Free > 0 )
                        {
                            XInt iCount = detail::__DecodeBase64<XByte>(__srcData, dest, int4Free);
                            if (iCount > 0)
                            {
                                *pDest ++ = dest[0];
                            }
                            if (iCount > 1)
                            {
                                *pDest ++ = dest[1];
                            }
                            if (iCount > 3)
                            {
                                *pDest ++ = dest[2];
                            }
                        }
                    }
                }
                return (XInt)(pDest - paramOutBuffer);
            }

            //-----------------------------------------------------------------------------------------------------
            ///Base64编码函数，原始数据类型为未知类型。
            /**
                需要确保缓冲区有足够的空间保存数据。由于编码后的结果是一个字符串，所以在最后会设置0结尾。
                @param [in] paramSrcData 要编码的数据
                @param [in] paramDataCount 要编码的数据字节数
                @param [out] paramOutBuffer 保存编码结果的缓冲区
                @return XInt 返回编码后的字节数
             */
            template<class T>
            static XInt EncodeBase64(const T * paramSrcData, XInt paramDataCount, XChar * paramOutBuffer)
            {
                XChar dest[4];
                XChar * pDest = paramOutBuffer;
                XInt srcLen = paramDataCount;
                const XByte * __srcData = (const XByte *)paramSrcData;
                if( srcLen > 0 )
                {
                    XInt int3Count = srcLen / 3;
                    XInt int3Free = srcLen % 3;

                    for(XInt i = 0; i < int3Count; i++)
                    {
                        detail::__EncodeBase64<XByte, XChar>(__srcData,dest);
                        __srcData+=3;
                        *pDest ++ = dest[0];
                        *pDest ++ = dest[1];
                        *pDest ++ = dest[2];
                        *pDest ++ = dest[3];
                    }
                    if( int3Free > 0 ) //如果未被3整除
                    {
                        detail::__EncodeBase64<XByte, XChar>(__srcData,dest,int3Free);
                        *pDest ++ = dest[0];
                        *pDest ++ = dest[1];
                        *pDest ++ = dest[2];
                        *pDest ++ = dest[3];                        
                    }
                }
                *pDest = 0;
                return (XInt)(pDest - paramOutBuffer);
            }
        }
                
        //-----------------------------------------------------------------------------------------------------
        ///没有返回类型的Base64解码函数，解码数据类型为未知类型。
        /**
            解码后的数据将放到XBuffer对象中。
            @param [in] paramSrcData 要解码的Base64编码数据
            @param [in] paramDataCount 要解码的数据个数
            @param [out] paramOutBuffer 保存结果的缓冲区
            @param [in] paramBreakByError 遇到错误是否要中断
                - true 表示遇到错误要中断 默认值
                - false 表示遇到错误不要中断
         */
        inline void DecodeBase64(const void * paramSrcData,XInt paramDataCount,XBuffer & paramOutBuffer,bool paramBreakByError = true)
        {
            detail::DecodeBase64(paramSrcData, paramDataCount, paramOutBuffer, paramBreakByError);
        }

        //-----------------------------------------------------------------------------------------------------
        ///没有返回类型的Base64编码函数，原始数据类型为未知类型。
        /**
            @param [in] paramSrcData 要编码的数据
            @param [in] paramDataCount 要编码的数据字节数
            @param [out] paramOutBuffer 保存编码结果的缓冲区
         */
        inline void EncodeBase64(const void * paramSrcData,XInt paramDataCount,XBuffer & paramOutBuffer)
        {
            detail::EncodeBase64(paramSrcData, paramDataCount, paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///没有返回类型的Base64编码函数，原始数据类型为未知类型。
        /**
         * 没有返回类型的Base64编码函数，原始数据类型为XBuffer对象。
         * @param [in] paramInBuffer 原始的数据存储的buffer。
         * @param [out] paramOutBuffer 编码后数据的输出buffer。
         */
        inline void EncodeBase64(XBuffer & paramInBuffer,XBuffer & paramOutBuffer)
        {
            EncodeBase64(paramInBuffer.getData(),paramInBuffer.getLength(),paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///没有返回类型的Base64编码函数，
        /**
         * 没有返回类型的Base64编码函数，原始数据类型为XString对象。
         * @param paramSrcString 原始的数据以XString的方式输入。
         * @param paramOutBuffer 编码后数据的输出buffer。
         */
        inline void EncodeBase64(const XAnsiString & paramSrcString, XBuffer & paramOutBuffer)
        {
            EncodeBase64(paramSrcString.c_str(),(XInt)paramSrcString.getLength(),paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///没有返回类型的Base64编码函数，
        /**
         * 没有返回类型的Base64编码函数，原始数据类型为const XChar * aString字符串。
         * @param paramString 字符串。
         * @param paramOutBuffer 编码后数据的输出buffer。
         */
        inline void EncodeBase64(const XChar * paramString,XBuffer & paramOutBuffer)
        {
            EncodeBase64(paramString,string_utils::Length(paramString),paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64解码
        /**
         * 没有返回类型的Base64解码函数，解码数据类型为XString。
         * @param [in] paramSrcData 需要解码的数据，类型为XString。
         * @param [out] paramOutBuffer 解码后的原始数据存放地址。
         * @param [in] paramBreakByError 不同解码函数选择标志位。
         */
        inline void DecodeBase64(const XAnsiString & paramSrcData,XBuffer & paramOutBuffer,bool paramBreakByError = true)
        {
            DecodeBase64((const void *)paramSrcData.c_str(),(XInt)paramSrcData.getLength(),paramOutBuffer,paramBreakByError);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64解码
        /**
         * 没有返回类型的Base64解码函数，解码数据类型为XString。
         * @param [in] paramSrcData 需要解码的数据，类型为XString。
         * @param [out] paramOutBuffer 解码后的原始数据存放地址。
         * @param [in] paramBreakByError 不同解码函数选择标志位。
         */ 
        inline void DecodeBase64(const XChar * paramData,XBuffer & paramOutBuffer,bool paramBreakByError = true)
        {
            DecodeBase64(paramData,string_utils::Length(paramData),paramOutBuffer,paramBreakByError);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64解码
        /**
         * 没有返回类型的Base64解码函数，解码数据类型为XBuffer。
         * @param [in] paramSrcData 需要解码的数据，类型为XBuffer。
         * @param [out] paramOutBuffer 解码后的原始数据存放地址。
         * @param [in] paramBreakByError 不同解码函数选择标志位。
         */
        inline void DecodeBase64(const XBuffer & paramSrcData,XBuffer & paramOutBuffer,bool paramBreakByError = true)
        {
            DecodeBase64(paramSrcData.getData(),paramSrcData.getLength(),paramOutBuffer,paramBreakByError);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64编码函数，原始数据类型为未知类型。
        /**
            需要确保缓冲区有足够的空间保存数据。由于编码后的结果是一个字符串，所以在最后会设置0结尾。
            @param [in] paramSrcData 要编码的数据
            @param [in] paramDataCount 要编码的数据字节数
            @param [out] paramOutBuffer 保存编码结果的缓冲区
            @return XInt 返回编码后的字节数
         */       
        inline XInt EncodeBase64(const XChar * paramSrcData, XInt paramDataCount, XChar * paramOutBuffer)
        {
            return detail::EncodeBase64<XChar>(paramSrcData, paramDataCount, paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64解码函数，解码数据类型为未知类型。
        /**
            解码后的数据将放到指定的缓冲区，请确保缓冲足够保存解码的数据
            @param [in] paramSrcData 要解码的Base64编码数据
            @param [in] paramDataCount 要解码的数据个数
            @param [out] paramOutBuffer 保存结果的缓冲区
            @param [in] paramBreakByError 遇到错误是否要中断
                - true 表示遇到错误要中断 默认值
                - false 表示遇到错误不要中断
            @return XInt 返回解码后的数据字节数
         */ 
        inline XInt DecodeBase64(const XChar * paramSrcData, XInt paramDataCount, XChar * paramOutBuffer, bool paramBreakByError = true)
        {
            return detail::DecodeBase64<XChar>(paramSrcData, paramDataCount, paramOutBuffer, paramBreakByError);
        }
    }
}

#endif
