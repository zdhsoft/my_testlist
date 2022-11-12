///Base64����ʵ��
/**
 * Copyright (c) 2012 zdhsoft Inc. All rights reserved.
 * Base64����ʵ��
 * �����Base64����������Ҫ���֣�һ��XBuffer���Ƽ�ʹ�á���һ��������C��ʵ�֣���XChar *��ʹ�õ�ʱ��ȷ��
 * ���㹻�Ŀռ��ű����Ľ��
 * zdhsoft 2011 ��Ȩ����
 *
 * @file xbase64.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-17
 * company zdhsoft
 */
/**********************************************************************
    �����б�  //��Ҫ��������
    1��Base64����ʵ��

    ��ʷ:       //��Ҫ�޸ļ�¼
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-17  1.0             ������ʼ�ļ�
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
            ///Base64�����
            template<class T>
            static const T * __EnBase64Tab()
            {
                static const T sEnBase64Tab[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
                return sEnBase64Tab;
            }
            ///Base64�����
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
            ///Base64����
            /**
                Base64���뺯������3���ֽ�ת��Ϊ4���ֽڴ洢������dest[4]�С�
                @param [in] paramSrc Ҫ��������� ��paramUse��֪�����ֽ���
                @param [out] paramDest �����洢
                @param [in] paramUse Ҫ�������ݵ��ֽ��� ��ֵֻ����1,2,3
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
            ///Base64�����뺯��
            /**
                Base64�����뺯��,���������顣
                @param [in] paramSrc �ѱ��������
                @param [out] paramDest ��Ž��������
                @param [in] paramUse �ѱ�������ݵ��ֽ��� ��ֵֻ����1,2,3,4
                @return XInt �����������ֽ���
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
            ///Base64�����뺯��
            /**
                Base64�����뺯��,��������,�����˳���
                @param [in] paramSrc Base64����Ĵ� ����1-4�ַ�
                @param [out] paramDest �������� 
                @return XInt �����������ֽ���
                    - 1 ������ֽ���1
                    - 2 ������ֽ���2
                    - 3 ������ֽ���3
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
                    if( btTmp == 0xFF ) //���������Ч�ַ�,���˳�
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
            ///û�з������͵�Base64���뺯����������������Ϊδ֪���͡�
            /**
                ���������ݽ��ŵ�XBuffer�����С�
                @param [in] paramSrcData Ҫ�����Base64��������
                @param [in] paramDataCount Ҫ��������ݸ���
                @param [out] paramOutBuffer �������Ļ�����
                @param [in] paramBreakByError ���������Ƿ�Ҫ�ж�
                    - true ��ʾ��������Ҫ�ж� Ĭ��ֵ
                    - false ��ʾ��������Ҫ�ж�
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
                    if( int4Free > 0 ) paramOutBuffer.ensureCapacity( (int4Count + 1) * 3 );//��չOutBuffer������Ϊ4����������
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
            ///û�з������͵�Base64���뺯����ԭʼ��������Ϊδ֪���͡�
            /**
                @param [in] paramSrcData Ҫ���������
                @param [in] paramDataCount Ҫ����������ֽ���
                @param [out] paramOutBuffer ����������Ļ�����
             */
            template<class T>
            static void EncodeBase64(const T * paramSrcData,XInt paramDataCount,XBuffer & paramOutBuffer)
            {
                XChar dest[4];
                paramOutBuffer.Clear();//���OutBuffer���Ԫ�ء�
                XInt srcLen = paramDataCount;
                const XByte * __srcData = (const XByte *)paramSrcData;
                if( srcLen > 0 )
                {
                    XInt int3Count = srcLen / 3;
                    XInt int3Free = srcLen % 3;
                    //�������Ҫ�Ŀռ䣬�ռ��ֽ���Ϊ4�ı���
                    if( int3Free > 0 ) paramOutBuffer.ensureCapacity( (int3Count+1) * 4 );
                    else paramOutBuffer.ensureCapacity( int3Count * 4 );

                    for(XInt i = 0;i < int3Count;i++)
                    {
                        __EncodeBase64<XByte,XChar>(__srcData,dest);
                        __srcData+=3;
                        paramOutBuffer.AppendData(dest,4);
                    }
                    if( int3Free > 0 ) //���δ��3����
                    {
                        __EncodeBase64<XByte,XChar>(__srcData,dest,int3Free);
                        paramOutBuffer.AppendData(dest,4);
                    }
                }

            }

            //-----------------------------------------------------------------------------------------------------
            ///Base64���뺯����������������Ϊδ֪���͡�
            /**
                ���������ݽ��ŵ�ָ���Ļ���������ȷ�������㹻������������
                @param [in] paramSrcData Ҫ�����Base64��������
                @param [in] paramDataCount Ҫ��������ݸ���
                @param [out] paramOutBuffer �������Ļ�����
                @param [in] paramBreakByError ���������Ƿ�Ҫ�ж�
                    - true ��ʾ��������Ҫ�ж� Ĭ��ֵ
                    - false ��ʾ��������Ҫ�ж�
                @return XInt ���ؽ����������ֽ���
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
            ///Base64���뺯����ԭʼ��������Ϊδ֪���͡�
            /**
                ��Ҫȷ�����������㹻�Ŀռ䱣�����ݡ����ڱ����Ľ����һ���ַ�������������������0��β��
                @param [in] paramSrcData Ҫ���������
                @param [in] paramDataCount Ҫ����������ֽ���
                @param [out] paramOutBuffer ����������Ļ�����
                @return XInt ���ر������ֽ���
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
                    if( int3Free > 0 ) //���δ��3����
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
        ///û�з������͵�Base64���뺯����������������Ϊδ֪���͡�
        /**
            ���������ݽ��ŵ�XBuffer�����С�
            @param [in] paramSrcData Ҫ�����Base64��������
            @param [in] paramDataCount Ҫ��������ݸ���
            @param [out] paramOutBuffer �������Ļ�����
            @param [in] paramBreakByError ���������Ƿ�Ҫ�ж�
                - true ��ʾ��������Ҫ�ж� Ĭ��ֵ
                - false ��ʾ��������Ҫ�ж�
         */
        inline void DecodeBase64(const void * paramSrcData,XInt paramDataCount,XBuffer & paramOutBuffer,bool paramBreakByError = true)
        {
            detail::DecodeBase64(paramSrcData, paramDataCount, paramOutBuffer, paramBreakByError);
        }

        //-----------------------------------------------------------------------------------------------------
        ///û�з������͵�Base64���뺯����ԭʼ��������Ϊδ֪���͡�
        /**
            @param [in] paramSrcData Ҫ���������
            @param [in] paramDataCount Ҫ����������ֽ���
            @param [out] paramOutBuffer ����������Ļ�����
         */
        inline void EncodeBase64(const void * paramSrcData,XInt paramDataCount,XBuffer & paramOutBuffer)
        {
            detail::EncodeBase64(paramSrcData, paramDataCount, paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///û�з������͵�Base64���뺯����ԭʼ��������Ϊδ֪���͡�
        /**
         * û�з������͵�Base64���뺯����ԭʼ��������ΪXBuffer����
         * @param [in] paramInBuffer ԭʼ�����ݴ洢��buffer��
         * @param [out] paramOutBuffer ��������ݵ����buffer��
         */
        inline void EncodeBase64(XBuffer & paramInBuffer,XBuffer & paramOutBuffer)
        {
            EncodeBase64(paramInBuffer.getData(),paramInBuffer.getLength(),paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///û�з������͵�Base64���뺯����
        /**
         * û�з������͵�Base64���뺯����ԭʼ��������ΪXString����
         * @param paramSrcString ԭʼ��������XString�ķ�ʽ���롣
         * @param paramOutBuffer ��������ݵ����buffer��
         */
        inline void EncodeBase64(const XAnsiString & paramSrcString, XBuffer & paramOutBuffer)
        {
            EncodeBase64(paramSrcString.c_str(),(XInt)paramSrcString.getLength(),paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///û�з������͵�Base64���뺯����
        /**
         * û�з������͵�Base64���뺯����ԭʼ��������Ϊconst XChar * aString�ַ�����
         * @param paramString �ַ�����
         * @param paramOutBuffer ��������ݵ����buffer��
         */
        inline void EncodeBase64(const XChar * paramString,XBuffer & paramOutBuffer)
        {
            EncodeBase64(paramString,string_utils::Length(paramString),paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64����
        /**
         * û�з������͵�Base64���뺯����������������ΪXString��
         * @param [in] paramSrcData ��Ҫ��������ݣ�����ΪXString��
         * @param [out] paramOutBuffer ������ԭʼ���ݴ�ŵ�ַ��
         * @param [in] paramBreakByError ��ͬ���뺯��ѡ���־λ��
         */
        inline void DecodeBase64(const XAnsiString & paramSrcData,XBuffer & paramOutBuffer,bool paramBreakByError = true)
        {
            DecodeBase64((const void *)paramSrcData.c_str(),(XInt)paramSrcData.getLength(),paramOutBuffer,paramBreakByError);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64����
        /**
         * û�з������͵�Base64���뺯����������������ΪXString��
         * @param [in] paramSrcData ��Ҫ��������ݣ�����ΪXString��
         * @param [out] paramOutBuffer ������ԭʼ���ݴ�ŵ�ַ��
         * @param [in] paramBreakByError ��ͬ���뺯��ѡ���־λ��
         */ 
        inline void DecodeBase64(const XChar * paramData,XBuffer & paramOutBuffer,bool paramBreakByError = true)
        {
            DecodeBase64(paramData,string_utils::Length(paramData),paramOutBuffer,paramBreakByError);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64����
        /**
         * û�з������͵�Base64���뺯����������������ΪXBuffer��
         * @param [in] paramSrcData ��Ҫ��������ݣ�����ΪXBuffer��
         * @param [out] paramOutBuffer ������ԭʼ���ݴ�ŵ�ַ��
         * @param [in] paramBreakByError ��ͬ���뺯��ѡ���־λ��
         */
        inline void DecodeBase64(const XBuffer & paramSrcData,XBuffer & paramOutBuffer,bool paramBreakByError = true)
        {
            DecodeBase64(paramSrcData.getData(),paramSrcData.getLength(),paramOutBuffer,paramBreakByError);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64���뺯����ԭʼ��������Ϊδ֪���͡�
        /**
            ��Ҫȷ�����������㹻�Ŀռ䱣�����ݡ����ڱ����Ľ����һ���ַ�������������������0��β��
            @param [in] paramSrcData Ҫ���������
            @param [in] paramDataCount Ҫ����������ֽ���
            @param [out] paramOutBuffer ����������Ļ�����
            @return XInt ���ر������ֽ���
         */       
        inline XInt EncodeBase64(const XChar * paramSrcData, XInt paramDataCount, XChar * paramOutBuffer)
        {
            return detail::EncodeBase64<XChar>(paramSrcData, paramDataCount, paramOutBuffer);
        }

        //-----------------------------------------------------------------------------------------------------
        ///Base64���뺯����������������Ϊδ֪���͡�
        /**
            ���������ݽ��ŵ�ָ���Ļ���������ȷ�������㹻������������
            @param [in] paramSrcData Ҫ�����Base64��������
            @param [in] paramDataCount Ҫ��������ݸ���
            @param [out] paramOutBuffer �������Ļ�����
            @param [in] paramBreakByError ���������Ƿ�Ҫ�ж�
                - true ��ʾ��������Ҫ�ж� Ĭ��ֵ
                - false ��ʾ��������Ҫ�ж�
            @return XInt ���ؽ����������ֽ���
         */ 
        inline XInt DecodeBase64(const XChar * paramSrcData, XInt paramDataCount, XChar * paramOutBuffer, bool paramBreakByError = true)
        {
            return detail::DecodeBase64<XChar>(paramSrcData, paramDataCount, paramOutBuffer, paramBreakByError);
        }
    }
}

#endif
