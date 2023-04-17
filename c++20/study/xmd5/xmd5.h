#pragma once
#ifndef _X_MD5_H_
#define _X_MD5_H_
#include "xtype.h"
namespace zdh
{
    namespace detail
    {
        const XDWord S11 = 7;
        const XDWord S12 = 12;
        const XDWord S13 = 17;
        const XDWord S14 = 22;
        const XDWord S21 = 5;
        const XDWord S22 = 9;
        const XDWord S23 = 14;
        const XDWord S24 = 20;
        const XDWord S31 = 4;
        const XDWord S32 = 11;
        const XDWord S33 = 16;
        const XDWord S34 = 23;
        const XDWord S41 = 6;
        const XDWord S42 = 10;
        const XDWord S43 = 15;
        const XDWord S44 = 21;
        ///一些位操作的宏定义
        inline XDWord F(XDWord X, XDWord Y, XDWord Z) { return (((X) & (Y)) | ((~(X)) & (Z))); }

        inline XDWord G(XDWord X, XDWord Y, XDWord Z) { return (((X) & (Z)) | ((Y) & (~(Z)))); }

        inline XDWord H(XDWord X, XDWord Y, XDWord Z) { return ((X) ^ (Y) ^ (Z)); }

        inline XDWord I(XDWord X, XDWord Y, XDWord Z) { return ((Y) ^ ((X) | (~(Z)))); }

        inline XDWord ROTATE_LEFT(XDWord X, XDWord N) { return (((X) << (N)) | ((X) >> (32 - (N)))); }

        inline XDWord FF(XDWord A, XDWord B, XDWord C, XDWord D, XDWord X, XDWord LL, XDWord AC) { return ROTATE_LEFT(F(B, C, D) + (X)+(AC)+(A), LL) + (B); }

        inline XDWord GG(XDWord A, XDWord B, XDWord C, XDWord D, XDWord X, XDWord LL, XDWord AC) { return ROTATE_LEFT(G(B, C, D) + (X)+(AC)+(A), LL) + (B); }

        inline XDWord HH(XDWord A, XDWord B, XDWord C, XDWord D, XDWord X, XDWord LL, XDWord AC) { return ROTATE_LEFT(H(B, C, D) + (X)+(AC)+(A), LL) + (B); }

        inline XDWord II(XDWord A, XDWord B, XDWord C, XDWord D, XDWord X, XDWord LL, XDWord AC) { return ROTATE_LEFT(I(B, C, D) + (X)+(AC)+(A), LL) + (B); }

        template<class T>
        struct XMD5Context
        {
            T state[4]; ///<用来存放XMD5的4个32位的链接变量。
            T count[2]; ///<用来记录计数的结果
            XByte  buff[64]; ///<用来暂时存储数据。
        };

		template<class T>
		static XInt Length(const T* paramValue)
		{
			XInt iRet = 0;
			while (*paramValue != 0)
			{
				paramValue++;
				iRet++;
			}
			return iRet;
		}

        template<class T = XDWord>
        class XMD5Impl
        {
        public:
            void Init()
            {
                m_Context.count[0] = 0;
                m_Context.count[1] = 0;
                m_Context.state[0] = 0x67452301L;
                m_Context.state[1] = 0xefcdab89L;
                m_Context.state[2] = 0x98badcfeL;
                m_Context.state[3] = 0x10325476L;
            }
            void Update(void* lpInput, T dwLength)
            {
                XByte* pSrc = (XByte*)lpInput;
                T i, index, partLen;
                index = (m_Context.count[0] >> 3) & 0x3F;

                T tmp1, tmp2;

                tmp1 = dwLength << 3;
                tmp2 = tmp1 + m_Context.count[0];
                m_Context.count[0] = tmp2;
                if (tmp2 < tmp1) m_Context.count[1] ++;

                m_Context.count[1] += dwLength >> 29;
                partLen = 64 - index;

                if (dwLength >= partLen)
                {
                    MD5MemCpy(&m_Context.buff[index], (XByte*)pSrc, partLen);
                    MD5Transform(m_Context.buff);
                    for (i = partLen; (i + 63) < dwLength; i += 64) MD5Transform(&pSrc[i]);
                    index = 0;
                }
                else i = 0;
                MD5MemCpy(&m_Context.buff[index], &pSrc[i], dwLength - i);

            }
            void Finish()
            {
                XByte PADDING[64] = {
                    0x80, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0
                };
                XByte bits[8];
                XDWord index, padLen;
                Encode(bits, m_Context.count, 8);
                index = (m_Context.count[0] >> 3) & 0x3f;
                padLen = (index < 56) ? (56 - index) : (120 - index);
                Update(PADDING, padLen);
                Update(bits, 8);
            }
            //取生成的MD5
            XByte* GetMD5Binary(XByte paramMD5[16])
            {
                Encode(paramMD5, m_Context.state, 16);
                return paramMD5;
            }
            //取生成的MD5字符串
            XChar* GetMD5String(XChar paramMD5[33], XBool paramCaption = true)
            {
                XByte btMD5[16];
                GetMD5Binary(btMD5);
                XChar* p = paramMD5;
                for (XInt i = 0; i < 16; i++)
                {
                    XByte btTmp = btMD5[i];
                    *p++ = GetChar((XByte)((btTmp >> 4) & 0xf), paramCaption);
                    *p++ = GetChar((XByte)(btTmp & 0xf), paramCaption);
                }
                *p = 0;
                return paramMD5;
            }
        private:
            void MD5MemSet(XByte* lpOutput, XByte btValue, T dwLength)
            {
                for (T i = 0; i < dwLength; i++)
                {
                    *lpOutput = btValue;
                    lpOutput++;
                }
            }

            void MD5MemCpy(XByte* lpOutput, XByte* lpInput, T dwLength)
            {
                for (T i = 0; i < dwLength; i++)
                {
                    *lpOutput = *lpInput;
                    lpOutput++;
                    lpInput++;
                }
            }

            void MD5Transform(XByte* lpInput)
            {
                XDWord a, b, c, d, x[16];
                a = m_Context.state[0];
                b = m_Context.state[1];
                c = m_Context.state[2];
                d = m_Context.state[3];
                Decode(x, lpInput, 64);

                /* Round 1 */
                a = FF(a, b, c, d, x[0], S11, 0xd76aa478); /* 1 */
                d = FF(d, a, b, c, x[1], S12, 0xe8c7b756); /* 2 */
                c = FF(c, d, a, b, x[2], S13, 0x242070db); /* 3 */
                b = FF(b, c, d, a, x[3], S14, 0xc1bdceee); /* 4 */
                a = FF(a, b, c, d, x[4], S11, 0xf57c0faf); /* 5 */
                d = FF(d, a, b, c, x[5], S12, 0x4787c62a); /* 6 */
                c = FF(c, d, a, b, x[6], S13, 0xa8304613); /* 7 */
                b = FF(b, c, d, a, x[7], S14, 0xfd469501); /* 8 */
                a = FF(a, b, c, d, x[8], S11, 0x698098d8); /* 9 */
                d = FF(d, a, b, c, x[9], S12, 0x8b44f7af); /* 10 */
                c = FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
                b = FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
                a = FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
                d = FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
                c = FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
                b = FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

                /* Round 2 */
                a = GG(a, b, c, d, x[1], S21, 0xf61e2562); /* 17 */
                d = GG(d, a, b, c, x[6], S22, 0xc040b340); /* 18 */
                c = GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
                b = GG(b, c, d, a, x[0], S24, 0xe9b6c7aa); /* 20 */
                a = GG(a, b, c, d, x[5], S21, 0xd62f105d); /* 21 */
                d = GG(d, a, b, c, x[10], S22, 0x2441453); /* 22 */
                c = GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
                b = GG(b, c, d, a, x[4], S24, 0xe7d3fbc8); /* 24 */
                a = GG(a, b, c, d, x[9], S21, 0x21e1cde6); /* 25 */
                d = GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
                c = GG(c, d, a, b, x[3], S23, 0xf4d50d87); /* 27 */
                b = GG(b, c, d, a, x[8], S24, 0x455a14ed); /* 28 */
                a = GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
                d = GG(d, a, b, c, x[2], S22, 0xfcefa3f8); /* 30 */
                c = GG(c, d, a, b, x[7], S23, 0x676f02d9); /* 31 */
                b = GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

                /* Round 3 */
                a = HH(a, b, c, d, x[5], S31, 0xfffa3942); /* 33 */
                d = HH(d, a, b, c, x[8], S32, 0x8771f681); /* 34 */
                c = HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
                b = HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
                a = HH(a, b, c, d, x[1], S31, 0xa4beea44); /* 37 */
                d = HH(d, a, b, c, x[4], S32, 0x4bdecfa9); /* 38 */
                c = HH(c, d, a, b, x[7], S33, 0xf6bb4b60); /* 39 */
                b = HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
                a = HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
                d = HH(d, a, b, c, x[0], S32, 0xeaa127fa); /* 42 */
                c = HH(c, d, a, b, x[3], S33, 0xd4ef3085); /* 43 */
                b = HH(b, c, d, a, x[6], S34, 0x4881d05); /* 44 */
                a = HH(a, b, c, d, x[9], S31, 0xd9d4d039); /* 45 */
                d = HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
                c = HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
                b = HH(b, c, d, a, x[2], S34, 0xc4ac5665); /* 48 */

                /* Round 4 */
                a = II(a, b, c, d, x[0], S41, 0xf4292244); /* 49 */
                d = II(d, a, b, c, x[7], S42, 0x432aff97); /* 50 */
                c = II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
                b = II(b, c, d, a, x[5], S44, 0xfc93a039); /* 52 */

                a = II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
                d = II(d, a, b, c, x[3], S42, 0x8f0ccc92); /* 54 */
                c = II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
                b = II(b, c, d, a, x[1], S44, 0x85845dd1); /* 56 */

                a = II(a, b, c, d, x[8], S41, 0x6fa87e4f); /* 57 */
                d = II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
                c = II(c, d, a, b, x[6], S43, 0xa3014314); /* 59 */
                b = II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */

                a = II(a, b, c, d, x[4], S41, 0xf7537e82); /* 61 */
                d = II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
                c = II(c, d, a, b, x[2], S43, 0x2ad7d2bb); /* 63 */
                b = II(b, c, d, a, x[9], S44, 0xeb86d391); /* 64 */

                m_Context.state[0] += a;
                m_Context.state[1] += b;
                m_Context.state[2] += c;
                m_Context.state[3] += d;
            }

            void Encode(XByte* lpOutput, T* lpInput, T dwLength)
            {
                for (T j = 0; j < dwLength; j += 4)
                {
                    T tmp = *lpInput++;
                    *lpOutput++ = (XByte)(tmp & 0xff);
                    tmp >>= 8;
                    *lpOutput++ = (XByte)(tmp & 0xff);
                    tmp >>= 8;
                    *lpOutput++ = (XByte)(tmp & 0xff);
                    tmp >>= 8;
                    *lpOutput++ = (XByte)(tmp & 0xff);
                }
            }

            void Decode(T* lpOutput, XByte* lpInput, T dwLength)
            {
                for (T j = 0; j < dwLength; j += 4)
                {
                    *lpOutput = (T)(*lpInput++);
                    *lpOutput |= (((T)(*lpInput++)) << 8);
                    *lpOutput |= (((T)(*lpInput++)) << 16);
                    *lpOutput |= (((T)(*lpInput++)) << 24);
                    lpOutput++;
                }
            }
            XChar GetChar(XByte paramValue, XBool paramCaption = true)
            {
                if (paramValue < 10)
                {
                    return (XChar)('0' + paramValue);
                }
                else
                {
                    return (XChar)( paramCaption? 'A':'a' + paramValue - 10);
                }
            }
        private:
            XMD5Context<T> m_Context;
        };
        template<class T>
        XByte* CreateMD5Binary(const T* paramData, XInt paramLength, XByte paramMD5[16])
        {
            XMD5Impl<> md5;
            md5.Init();
            md5.Update((void*)paramData, paramLength);
            md5.Finish();
            md5.GetMD5Binary(paramMD5);
            return paramMD5;
        }
        template<class T>
        XChar* CreateMD5String(const T* paramData, XInt paramLength, XChar paramMD5[33], XBool paramCaption = true)
        {
            XMD5Impl<> md5;
            md5.Init();
            md5.Update((void*)paramData, paramLength);
            md5.Finish();
            md5.GetMD5String(paramMD5);
            return paramMD5;
        }
    }
    typedef detail::XMD5Impl<> XMD5;
    ///生成MD5串
    /**
     * 生成MD5串
     *
     * @author zdhsoft (2011/12/4)
     *
     * @param [in] paramString 要生成MD5的字符串
     * @param [out] paramMD5 包成MD5的缓冲区
     *
     * @return XChar* 返回paramMD5
     */
    inline XChar* CreateMD5(const XChar* paramString, XChar paramMD5[33])
    {
        return detail::CreateMD5String(paramString, detail::Length(paramString), paramMD5);
    }
    /**
     * 生成MD5串
     *
     * @author zdhsoft (2011/12/4)
     *
     * @param [in] paramData 要生成MD5的数据
     * @param [in] paramLength 要生成MD5的数据字节数
     * @param [out] paramMD5 包成MD5的缓冲区
     *
     * @return XChar* 返回paramMD5
     */
    inline XChar* CreateMD5(const void* paramData, XInt paramLength, XChar paramMD5[33])
    {
        return detail::CreateMD5String(paramData, paramLength, paramMD5);
    }
    /**
     * 生成MD5串
     *
     * @author zdhsoft (2011/12/4)
     *
     * @param [in] paramString 要生成MD5的字符串
     * @param [in] paramLength 要生成MD5的字符串长度
     * @param [out] paramMD5 包成MD5的缓冲区
     *
     * @return XChar* 返回paramMD5
     */
    inline XChar* CreateMD5(const XChar* paramString, XInt paramLength, XChar paramMD5[33])
    {
        return detail::CreateMD5String(paramString, paramLength, paramMD5);
    }
}
#endif