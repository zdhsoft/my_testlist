///XBuffer对象类
/**
 * 这是一个动态缓冲区的类，最小单位是1K，可以预先准备好足够的内存。
 *
 * zdhsoft 2011 版权所有
 *
 * @file xbuffer.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-20
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、XBuffer对象类

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-20  1.0             创建初始文件
***********************************************************************/
#ifndef _X_BUFFER_H_
#define _X_BUFFER_H_
#include <xstring.h>
namespace zdh
{
    ///定义XBuffer缺省块大小
    const XInt XBYTE_BUFFER_MIN_BLOCK = 1024;

    class XBuffer
    {
    public:
        ///默认构造函数
        XBuffer()
            :m_Capacity(0),m_Length(0),m_Data(NULL)
        {}
        ///定义指定数组的构造函数
        template<class ElementType, int N>
        XBuffer( ElementType (&paramData)[N] )
            :m_Capacity(0),m_Length(0),m_Data(NULL)
        {
            AppendData( (void *)&paramData,  N * sizeof(ElementType));
        }       
        ///指定默认数据构造函数
        /**
         * @param [in] paramData 默认的数据指针
         * @param [in] paramSize 默认的数据大小
         */
        XBuffer(const void * paramData,XInt paramSize) ZDH_THROW(XEIsZero) ZDH_THROW(XELessThanZero)
            :m_Capacity(0),m_Length(0),m_Data(NULL)
        {
            ZDH_ASSERT(paramData != NULL);
            ZDH_ASSERT(paramSize >= 0);
            if( paramData == NULL ) 
            {
                throw XEIsZero();
            }
            if( paramSize < 0 ) 
            {
                throw XELessThanZero();
            }
            if( paramSize > 0 )
            {
                ensureCapacity(paramSize);
                MemoryCopy(m_Data, paramData, paramSize);
                m_Length = paramSize;
            }
        }
        ///默认拷贝构造函数
        XBuffer(const XBuffer & paramBuffer)
            :m_Capacity(0),m_Length(0),m_Data(NULL)
        {
            if( paramBuffer.m_Length > 0)
            {
                ensureCapacity(paramBuffer.m_Length);
                MemoryCopy(m_Data, paramBuffer.m_Data, paramBuffer.m_Length);
                m_Length = paramBuffer.m_Length;
            }
        }
        ///默认析构函数
        ~XBuffer()
        {
            if( m_Capacity > 0 ) FreeMemory(m_Data);
            m_Capacity = 0;
            m_Length = 0;
            m_Data = NULL;
        }
        ///清除缓冲区
        /**
         * @param [in] paramFree 表示是否释放缓冲区
         *      - true 表示要释放缓冲区
         *      - false 表示不要释放缓冲区
         */
        void Clear(bool paramFree = false)
        {
            if( paramFree )
            {
                if( m_Data != NULL ) FreeMemory(m_Data);
                m_Data = NULL;
                m_Capacity =0;
            }
            m_Length = 0;
        }
        ///取容量
        XInt getCapacity() const 
        { 
            return m_Capacity; 
        }
        ///取当前有效的字节数
        XInt getLength() const 
        { 
            return m_Length; 
        }
        ///取数据指针
        const XByte * getData() const 
        { 
            return m_Data; 
        }
        ///确认容量是否达到指定的最小容量
        /**
         * 确认容量是否达到指定的最小容量,如果未达指定容量,则扩展容量
         * @param [in] paramMinimumCapacity 最小容量
         */
        void ensureCapacity(XInt paramMinimumCapacity)
        {
            if( paramMinimumCapacity > m_Capacity ) 
            {
                expandCapacity(paramMinimumCapacity);
            }
        }
        ///重载[]运算符
        /**
         * @param [in] paramIndex 指定的下标
         * @return 返回指定字节的引用
         */
        XByte & operator[](XInt paramIndex) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramIndex >= 0 && paramIndex < m_Length);
            if( paramIndex < 0 || paramIndex >= m_Length ) 
            {
                throw XEOutOfRange(paramIndex,m_Length);
            }
            return m_Data[paramIndex];
        }
        ///重载[]运算符
        /**
         * @param [in] paramIndex 指定的下标
         * @return 返回指定字节的值
         */
        XByte operator[](XInt paramIndex) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramIndex >= 0 && paramIndex < m_Length);
            if( paramIndex < 0 || paramIndex >= m_Length ) 
            {
                throw XEOutOfRange(paramIndex,m_Length);
            }
            return m_Data[paramIndex];
        }
        ///重载赋值运算符
        /**
         * @param [in] paramBuffer 要赋值的缓冲区
         * @return 返回当前缓冲区的引用
         */
        XBuffer & operator = (const XBuffer & paramBuffer)
        {
            if( this != &paramBuffer ) 
            {
                Clear();
                if( paramBuffer.m_Length > 0 )
                {
                    if( m_Capacity < paramBuffer.m_Length ) expandCapacity( paramBuffer.m_Length, false );
                    MemoryCopy( m_Data, paramBuffer.m_Data, paramBuffer.m_Length );
                    m_Length = paramBuffer.m_Length;
                }
                else 
                {
                    m_Length = 0;
                }
            }
            return *this;
        }
        ///追加一个缓冲区对象
        /**
         * @param [in] paramBuffer 被追加的缓冲区对象
         */
        void AppendBuffer(const XBuffer & paramBuffer)
        {
            AppendData( paramBuffer.m_Data, paramBuffer.m_Length );
        }
        ///追加一个字符串
        void AppendString(const XAnsiString & paramString)
        {
            AppendData( paramString.c_str(), paramString.getLength() );
        }
        ///追加一个字符串
        void AppendString(const XChar * paramString)
        {
            ZDH_ASSERT(paramString != NULL);
            AppendData( paramString, string_utils::Length(paramString) );
        }
        ///追加一个数组的元素
        /**
            @code
                XBuffer a;
                XInt v[100];
                a.AppendArray(v);
            @endcode
         */
        template<class ElementType, int N>
        void AppendArray( ElementType (&paramData)[N] )
        {
            AppendData( (void *)&paramData,  N * sizeof(ElementType));
        }
        ///追加指定的数据
        /**
         * @param [in] paramData 指定的数据
         * @param [in] paramSize 指定追加数据的字节数
         */
        void AppendData(const void * paramData,XInt paramSize)
        {
            ZDH_ASSERT(paramData != NULL);
            ZDH_ASSERT(paramSize >= 0);
            if( paramSize > 0)
            {
                ensureCapacity(paramSize + m_Length);
                MemoryCopy( m_Data + m_Length, paramData, paramSize );
                m_Length += paramSize;
            }
        }
        ///追加一个字节的值
        void AppendByte(XByte paramByte)
        {
            ensureCapacity(m_Length + 1);
            m_Data[ m_Length ++ ] = paramByte;
        }
        ///追加一个字符的值
        void AppendChar(XChar paramChar)
        {
            ensureCapacity( m_Length + 1 );
            m_Data[ m_Length ++ ] = (XByte)paramChar;
        }
        ///追加一个布尔值
        /// @param [in] paramBool 追加布尔值
        ///     - true 追加一个字节值 1
        ///     - false 追加一个字节值 0 
        void AppendBool(XBool  paramBool)
        {
            ensureCapacity( m_Length + 1 );
            m_Data[m_Length ++] = paramBool?1:0;
        }
        ///追加一个16位无符号整数
        void AppendWord(XWord paramWord)
        {
            ensureCapacity(m_Length + sizeof(XWord));
            *((XWord *)(m_Data + m_Length)) = paramWord;
            m_Length += sizeof(XWord);
        }
        ///追加一个16位有符号整数
        void AppendShort(XShort paramShort)
        {
            ensureCapacity(m_Length + sizeof(XShort));
            *((XShort *)(m_Data + m_Length)) = paramShort;
            m_Length += sizeof(XShort);
        }
        ///追加一个网络16位无符号整数
        void AppendNetworkWord(XWord paramWord)
        {
            ensureCapacity(m_Length + 2);
            m_Data[m_Length++] = *(((XByte *)(&paramWord))+1);
            m_Data[m_Length++] = *((XByte *)(&paramWord));
        }
        ///追加一个网络16位有符号整数
        void AppendNetworkShort(XShort paramShort)
        {
            ensureCapacity(m_Length + 2);
            m_Data[m_Length++] = *(((XByte *)(&paramShort))+1);
            m_Data[m_Length++] = *((XByte *)(&paramShort));
        }
        ///追加一个32位有符号整数
        void AppendInt(XInt paramInt)
        {
            ensureCapacity(m_Length + sizeof(XInt));
            *((XInt *)(m_Data + m_Length)) = paramInt;
            m_Length += sizeof(XInt);
        }
        ///追加一个32位无符号整数
        void AppendDWord(XDWord paramDWord)
        {
            ensureCapacity(m_Length + sizeof(XDWord));
            *((XDWord *)(m_Data + m_Length)) = paramDWord;
            m_Length += sizeof(XDWord);
        }
        ///追加一个网络32位有符号整数
        void AppendNetworkInt(XInt paramInt)
        {
            ensureCapacity(m_Length + 4);
            XByte * d = m_Data + m_Length;
            const XByte * s = ((const XByte *)(&paramInt)) + 3;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d    = * s;
            m_Length += 4;
        }
        ///追加一个网络32位无符号整数
        void AppendNetworkDWord(XDWord paramDWord)
        {
            ensureCapacity(m_Length + 4);
            XByte * d = m_Data + m_Length;
            const XByte * s = ((const XByte *)(&paramDWord)) + 3;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d    = * s;
            m_Length += 4;
        }
        ///追加一个64位有符号整数
        void AppendLong(XLong paramLong)
        {
            ensureCapacity(m_Length + sizeof(XLong));
            *((XLong *)(m_Data + m_Length)) = paramLong;
            m_Length += sizeof(XLong);
        }
        ///追加一个64位无符号整数
        void AppendDDWord(XDDWord paramDDWord)
        {
            ensureCapacity(m_Length + sizeof(XDDWord));
            *((XDDWord *)(m_Data + m_Length)) = paramDDWord;
            m_Length += sizeof(XDDWord);
        }
        ///追加一个64位有符号整数
        void AppendNetworkLong(XLong paramLong)
        {
            ensureCapacity(m_Length + 8);
            XByte * d = m_Data + m_Length;
            const XByte * s = ((const XByte *)(&paramLong)) + 7;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d    = * s;
            m_Length += 8;
        }
        ///追加一个64位无符号整数
        void AppendNetworkDDWord(XDDWord paramDDWord)
        {
            ensureCapacity(m_Length + 8);
            XByte * d = m_Data + m_Length;
            const XByte * s = ((const XByte *)(&paramDDWord)) + 7;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d ++ = * s --;
            * d    = * s;
            m_Length += 8;
        }
        ///追加单精度浮点数
        void AppendFloat(XFloat paramFloat)
        {
            ensureCapacity(m_Length + sizeof(XFloat));
            *((XFloat *)(m_Data + m_Length)) = paramFloat;
            m_Length += sizeof(XFloat);
        }
        ///追加双精度浮点数
        void AppendDouble(XDouble paramDouble)
        {
            ensureCapacity(m_Length + sizeof(XDouble));
            *((XDouble *)(m_Data + m_Length)) = paramDouble;
            m_Length += sizeof(XDouble);
        }
        ///从指定位置读取一个字节
        XByte ReadByte(XInt paramPos) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            return m_Data[paramPos];
        }
        ///从指定位置读取一个字符
        XChar ReadChar(XInt paramPos) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            return (XChar)m_Data[paramPos];
        }
        ///从指定位置读取一个布尔值
        XBool ReadBool(XInt paramPos) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            return m_Data[paramPos] != 0;
        }
        ///从指定位置读取一个16位无符号整数
        XWord ReadWord(XInt paramPos) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 2) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 2) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 2), m_Length);
            }
            return *((XWord *)(m_Data + paramPos));
        }
        ///从指定位置读取一个16位有符号整数
        XShort ReadShort(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 2) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 2) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 2), m_Length);
            }
            return *((XShort *)(m_Data + paramPos));
        }
        ///从指定位置读取一个网络顺序的16位无符号整数
        XWord ReadNetworkWord(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 2) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 2) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 2), m_Length);
            }
            XWord wRet;
            *(((XByte *)(&wRet)) + 1) = m_Data[paramPos ++];
            *((XByte *)(&wRet)) = m_Data[paramPos];
            return wRet;
        }
        ///从指定位置读取一个网络顺序16位有符号整数
        XShort ReadNetworkShort(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 2) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 2) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 2), m_Length);
            }
            XShort sRet;
            *(((XByte *)(&sRet)) + 1) = m_Data[paramPos ++];
            *((XByte *)(&sRet)) = m_Data[paramPos];
            return sRet;
        }
    
        ///从指定位置读取一个32位无符号整数
        XDWord ReadDWord(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 4) > m_Length )
            {
                throw XEOutOfRange((paramPos + 4), m_Length);
            }
            return *((XDWord *)(m_Data + paramPos));
        }
        ///从指定位置读取一个32位有符号整数
        XInt ReadInt(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 4) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 4), m_Length);
            }
            return *((XInt *)(m_Data + paramPos));
        }
        ///从指定位置读取一个网络顺序的32位无符号整数
        XDWord ReadNetworkDWord(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 4) > m_Length ) 
            {
                throw XEOutOfRange( (paramPos + 4), m_Length);
            }
            XDWord dwRet;
            XByte * d = (XByte *)&dwRet;
            XByte * s = m_Data + paramPos + 3;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d = *s;
            return dwRet;
        }
        ///从指定位置读取一个网络顺序的32位有符号整数
        XInt ReadNetworkInt(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 4) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 4), m_Length);
            }
            XInt iRet;
            XByte * d = (XByte *)&iRet;
            XByte * s = m_Data + paramPos + 3;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d = *s;
            return iRet;
        }
        ///从指定位置读取一个64位无符号整数
        XDDWord ReadDDWord(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 8) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 8), m_Length);
            }
            return *((XDDWord *)(m_Data + paramPos));
        }
        ///从指定位置读取一个64位有符号整数
        XLong ReadLong(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length )
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 8) > m_Length ) 
            {
                throw XEOutOfRange( (paramPos + 8), m_Length);
            }
            return *((XLong *)(m_Data + paramPos));
        }   
        ///从指定位置读取一个网络顺序的64位无符号整数
        XDDWord ReadNetworkDDWord(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 8) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 8), m_Length);
            }
            XDDWord ddwRet;
            XByte * d = (XByte *)&ddwRet;
            XByte * s = m_Data + paramPos + 7;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d = *s;
            return ddwRet;
        }
        ///从指定位置读取一个网络顺序的64位有符号整数
        XLong ReadNetworkLong(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 8) > m_Length ) 
            {
                throw XEOutOfRange( (paramPos + 8), m_Length);
            }
            XLong lngRet;
            XByte * d = (XByte *)&lngRet;
            XByte * s = m_Data + paramPos + 7;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d++ = *s--;
            *d = *s;
            return lngRet;
        }   
        ///从指定位置读取一个单精度浮点数
        XFloat ReadFloat(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 4) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 4), m_Length);
            }
            return *((XFloat *)(m_Data + paramPos));
        }
        ///从指定位置读取一个64位双精度浮点数
        XDouble ReadDouble(XInt paramPos) const
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( (paramPos + 8) > m_Length ) 
            {
                throw XEOutOfRange((paramPos + 8), m_Length);
            }
            return *((XDouble *)(m_Data + paramPos));
        }
        ///从指定位置读取指定字节数的数据
        void ReadData(XInt paramPos,void * paramData,XInt paramReadSize) const ZDH_THROW(XELessThanZero) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramData != NULL);
            ZDH_ASSERT(paramReadSize >= 0);
            ZDH_ASSERT(paramPos >= 0 && (paramPos + paramReadSize) <= m_Length);

            if( paramReadSize < 0) 
            {
                throw XELessThanZero();
            }
            if( paramReadSize == 0 ) 
            {
                return;
            }
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + paramReadSize > m_Length ) 
            {
                throw XEOutOfRange(paramPos + paramReadSize,m_Length);
            }
            MemoryCopy( paramData, m_Data + paramPos, paramReadSize );
        }
        ///从指定位置读取指定字节数的数据到新的缓冲区
        void ReadBuffer(XInt paramPos,XBuffer & paramBuffer, XInt paramReadSize) const ZDH_THROW(XELessThanZero) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramReadSize >= 0);
            ZDH_ASSERT(paramPos >= 0 && (paramPos + paramReadSize) <= m_Length);
            if( paramReadSize < 0) 
            {
                throw XELessThanZero();
            }
            paramBuffer.Clear();
            if( paramReadSize == 0 ) 
            {
                return;
            }
            if( paramPos < 0 || paramPos >= m_Length )
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + paramReadSize > m_Length ) 
            {
                throw XEOutOfRange(paramPos + paramReadSize,m_Length);
            }
            paramBuffer.AppendData(m_Data + paramPos,paramReadSize);
        }
        //下面是一组重载<<运算符的方法,用于方便的在缓冲区后追加数据
        XBuffer & operator << (XByte paramByte)
        {
            AppendByte(paramByte);
            return *this;
        }
        XBuffer & operator << (XChar paramChar)
        {
            AppendChar(paramChar);
            return *this;
        }
        XBuffer & operator << (XWord paramWord)
        {
            AppendWord(paramWord);
            return *this;
        }
        XBuffer & operator << (XShort paramShort)
        {
            AppendShort(paramShort);
            return *this;
        }
        XBuffer & operator << (XInt paramInt)
        {
            AppendInt(paramInt);
            return *this;
        }
        XBuffer & operator << (XDWord paramDWord)
        {
            AppendDWord(paramDWord);
            return *this;
        }
        XBuffer & operator << (XLong paramLong)
        {
            AppendLong(paramLong);
            return *this;
        }
        XBuffer & operator << (XDDWord paramDDWord)
        {
            AppendDDWord(paramDDWord);
            return *this;
        }
        XBuffer & operator << (XBool paramBool)
        {
            AppendBool(paramBool);
            return *this;
        }
        XBuffer & operator << (XFloat paramFloat)
        {
            AppendFloat(paramFloat);
            return *this;
        }
        XBuffer & operator << (XDouble paramDouble)
        {
            AppendDouble(paramDouble);
            return *this;
        }
        XBuffer & operator << (const char * paramString)
        {
            AppendString(paramString);
            return *this;
        }
        XBuffer & operator << (const XAnsiString & paramString)
        {
            AppendString(paramString);
            return *this;
        }
        XBuffer & operator << (const XBuffer & paramBuffer)
        {
            AppendBuffer(paramBuffer);
            return *this;
        }
        ///在指定的位置上写入一个字节
        void WriteByte(XInt paramPos,XByte paramByte) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            m_Data[paramPos] = paramByte;
        }
        ///在指定的位置上写入一个字符
        void WriteChar(XInt paramPos,XChar paramChar) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            m_Data[paramPos] = (XByte)paramChar;
        }
        ///在指定的位置上写入一个布尔值,对于false值写入0,对于true会写入1
        void WriteBool(XInt paramPos,XBool paramBool) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            m_Data[paramPos] = (paramBool)?1:0;
        }
        ///在指定的位置上写入一个16无符号整数
        void WriteWord(XInt paramPos,XWord paramWord) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 2) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 2 > m_Length )
            {
                throw XEOutOfRange(paramPos + 2, m_Length);
            }
            *((XWord *)(m_Data + paramPos)) = paramWord;
        }
        ///在指定的位置上写入一个16有符号整数
        void WriteShort(XInt paramPos,XShort paramShort) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 2) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 2 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 2, m_Length);
            }
            *((XShort *)(m_Data + paramPos)) = paramShort;
        }
        ///在指定的位置上写入一个网络顺序的16无符号整数
        void WriteNetworkWord(XInt paramPos,XWord paramWord) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 2) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 2 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 2, m_Length);
            }
            m_Data[paramPos ++] = *(((XByte *)(&paramWord)) + 1) ;
            m_Data[paramPos] = *((XByte *)(&paramWord)) ;
        }
        ///在指定的位置上写入一个网络顺序的16有符号整数
        void WriteNetworkShort(XInt paramPos,XShort paramShort) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 2) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 2 > m_Length )
            {
                throw XEOutOfRange(paramPos + 2, m_Length);
            }
            m_Data[paramPos ++] = *(((XByte *)(&paramShort)) + 1) ;
            m_Data[paramPos] = *((XByte *)(&paramShort)) ;
        }

        ///在指定的位置上写入一个32无符号整数
        void WriteDWord(XInt paramPos,XDWord paramDWord) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 4 > m_Length )
            {
                throw XEOutOfRange(paramPos + 4, m_Length);
            }
            *((XDWord *)(m_Data + paramPos)) = paramDWord;
        }
        ///在指定的位置上写入一个32有符号整数
        void WriteInt(XInt paramPos,XInt paramInt) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 4 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 4, m_Length);
            }
            *((XInt *)(m_Data + paramPos)) = paramInt;
        }
        ///在指定的位置上写入一个网络顺序的32无符号整数
        void WriteNetworkDWord(XInt paramPos,XDWord paramDWord) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 4 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 4, m_Length);
            }
            XByte * s = (XByte *)&paramDWord;
            XByte * d = m_Data + paramPos + 3;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d = *s;
        }
        ///在指定的位置上写入一个网络顺序的32有符号整数
        void WriteNetworkInt(XInt paramPos,XInt paramInt) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 4 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 4, m_Length);
            }
            XByte * s = (XByte *)&paramInt;
            XByte * d = m_Data + paramPos + 3;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d = *s;
        }
        ///在指定的位置上写入一个64无符号整数
        void WriteDDWord(XInt paramPos,XDDWord paramDDWord) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 8 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 8, m_Length);
            }
            *((XDDWord *)(m_Data + paramPos)) = paramDDWord;
        }
        ///在指定的位置上写入一个64有符号整数
        void WriteLong(XInt paramPos,XLong paramLong) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 8 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 8, m_Length);
            }
            *((XLong *)(m_Data + paramPos)) = paramLong;
        }   
        ///在指定的位置上写入一个网络顺序的64无符号整数
        void WriteNetworkDDWord(XInt paramPos,XDDWord paramDDWord) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 8 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 8, m_Length);
            }
            XByte * s = (XByte *)&paramDDWord;
            XByte * d = m_Data + paramPos + 7;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d = *s;
        }
        ///在指定的位置上写入一个网络顺序的64无符号整数
        void WriteNetworkLong(XInt paramPos,XLong paramLong) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length )
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 8 > m_Length )
            {
                throw XEOutOfRange(paramPos + 8, m_Length);
            }
            XByte * s = (XByte *)&paramLong;
            XByte * d = m_Data + paramPos + 7;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d-- = *s++;
            *d = *s;
        }
        ///在指定的位置上写入一个单精度浮点数
        void WriteFloat(XInt paramPos,XFloat paramFloat) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 4) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 4 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 4, m_Length);
            }
            *((XFloat *)(m_Data + paramPos)) = paramFloat;
        }
        ///在指定的位置上写入一个双精度浮点数
        void WriteDouble(XInt paramPos,XDouble paramDouble) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && (paramPos + 8) <= m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + 8 > m_Length ) 
            {
                throw XEOutOfRange(paramPos + 8, m_Length);
            }
            *((XDouble *)(m_Data + paramPos)) = paramDouble;
        }
        ///在指定的位置上写入指定字节数的数据
        void WriteData(XInt paramPos,const void * paramData,XInt paramWriteSize) ZDH_THROW(XELessThanZero) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramWriteSize >= 0);
            ZDH_ASSERT(paramData != NULL);
            ZDH_ASSERT(paramPos >= 0 && (paramPos + paramWriteSize) <= m_Length);
            if( paramWriteSize < 0) 
            {
                throw XELessThanZero();
            }
            if( paramWriteSize == 0 ) 
            {
                return;
            }
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + paramWriteSize > m_Length ) 
            {
                throw XEOutOfRange(paramPos + paramWriteSize,m_Length);
            }
            MemoryCopy( m_Data + paramPos,  paramData, paramWriteSize );
        }
        ///在指定的位置上写入一个缓冲区的数据
        void WriteBuffer(XInt paramPos,const XBuffer & paramBuffer) ZDH_THROW(XELessThanZero) ZDH_THROW(XEOutOfRange)
        {
            XInt iWriteSize = paramBuffer.m_Length;
            ZDH_ASSERT(paramPos >= 0 && (paramPos + iWriteSize) <= m_Length);
            if( iWriteSize < 0) 
            {
                throw XELessThanZero();
            }
            if( iWriteSize == 0 ) 
            {
                return;
            }
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            if( paramPos + iWriteSize > m_Length ) 
            {
                throw XEOutOfRange(paramPos + iWriteSize,m_Length);
            }
            MemoryCopy(m_Data + paramPos, paramBuffer.m_Data, iWriteSize );
        }
        ///删除缓冲区最后指定字节数的数据
        void RemoveLast(XInt paramRemoveBytes) ZDH_THROW(XELessThanZero)
        {
            ZDH_ASSERT(paramRemoveBytes >= 0 && paramRemoveBytes <= m_Length);
            if( paramRemoveBytes < 0 ) 
            {
                throw XELessThanZero();
            }
            if( paramRemoveBytes <= m_Length && paramRemoveBytes > 0 ) 
            {
                m_Length -= paramRemoveBytes;
            }
        }
        ///删除缓冲区指定位置和字节数的数据
        void Remove(XInt paramPos,XInt paramRemoveBytes) ZDH_THROW(XELessThanZero) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramRemoveBytes >= 0 && paramRemoveBytes + paramPos <= m_Length);
            if( paramRemoveBytes < 0 ) 
            {
                throw XELessThanZero();
            }
            if( paramRemoveBytes == 0) 
            {
                return;
            }
            if( paramPos < 0 || paramPos >= m_Length )
            {
                throw XEOutOfRange(paramPos,m_Length);
            }
            if( paramPos + paramRemoveBytes > m_Length ) 
            {
                throw XEOutOfRange(paramPos + paramRemoveBytes - 1, m_Length);
            }
            if( paramPos + paramRemoveBytes < m_Length ) 
            {
                MemoryCopy(m_Data + paramPos, m_Data + paramPos + paramRemoveBytes, m_Length - paramPos - paramRemoveBytes );
            }
            m_Length -= paramRemoveBytes;
        }
        ///重载->运算符,提供类似指针的表达式
        XBuffer * operator ->() 
        { 
            return this; 
        }
        ///重载->运算符,提供类似指针的表达式
        const XBuffer * operator->() const 
        { 
            return this; 
        }
    private:
        ///计算要准备的字节数
        /**
         * @param paramPrepareLength 至少要准备的字节数
         * @return 返回计算后的准备字节数
         */
        XInt PrepareLength(XInt paramPrepareLength) 
        {
            if( paramPrepareLength < XBYTE_BUFFER_MIN_BLOCK )
            {
                paramPrepareLength = XBYTE_BUFFER_MIN_BLOCK;
            }
            else if( (paramPrepareLength % XBYTE_BUFFER_MIN_BLOCK) != 0) 
            {
                paramPrepareLength = (paramPrepareLength / XBYTE_BUFFER_MIN_BLOCK+1) * XBYTE_BUFFER_MIN_BLOCK;
            }
            return paramPrepareLength;
        }
        ///扩展缓冲区容量
        /**
         * @param paramMinimumCapacity 最少容量
         * @param paramCopyData 表示是否要Copy原来的数据，默认是要Copy原数据
         * @return 返回扩展结果
         *     - true 表示扩展成功
         *     - false 表示扩展失败
         */
        bool expandCapacity(XInt paramMinimumCapacity,bool paramCopyData = true)
        {
            XInt newCapacity = m_Capacity * 2;
            
            if ( newCapacity < 0 )  return false; //如果溢出,则返回false
            else if ( paramMinimumCapacity > newCapacity ) newCapacity = paramMinimumCapacity;
            
            XInt iPrepareLength = PrepareLength(newCapacity);
            if( iPrepareLength < paramMinimumCapacity ) return false; //如果计算出来容量,小于实际所需要的容量,则返回false 

            PByte tmp = (PByte)AllocMemory(iPrepareLength); //申请新的内存
            
            if( tmp == NULL ) throw XEOutOfMemory(); //如果申请内存失败
            
            if( paramCopyData ) //如果需要copy原始数据 
            {
                if( m_Length > 0 ) MemoryCopy(tmp, m_Data, m_Length);  
            }
            else m_Length = 0;  //如果不需要,则将长度置为0

            if( m_Data != NULL ) FreeMemory(m_Data);    //如果存在原始数据,则释放原始数据
            m_Capacity = iPrepareLength;            //设置新的容量
            m_Data = tmp;                           //设置新的数据
            return true;
        }
    private:
        XInt m_Capacity;    ///<容量
        XInt m_Length;      ///<长度
        XByte * m_Data;     ///<开始指针
    };

    ///buffer代理
    class XDataProxy
    {
    public:
        XDataProxy()
            :m_Data(NULL) ,m_Size(0), m_Pos(0), m_BindFlag(false)
        {}
        ~XDataProxy()
        {
            Deattach();   
        }

        XInt Attach(void * paramData, XInt paramDataSize, bool paramBindFlag = false)
        {
            Deattach();
            if (isNULL(paramData))
            {
                return ERR_FAIL;
            }
            if (paramDataSize < 1)
            {
                return ERR_FAIL;
            }
            m_Data      = (PByte)paramData;
            m_Size      = paramDataSize;
            m_BindFlag  = paramBindFlag;
            m_Pos       = 0;
            return ERR_OK;
        }

        XInt Attach(XInt paramDataSize)
        {
            Deattach();
            
            if (paramDataSize < 1)
            {
                return ERR_FAIL;
            }

            m_Data = (PByte)AllocMemory(paramDataSize);
            if (isNULL(m_Data))
            {
                return ERR_FAIL;
            }
            
            m_BindFlag  = true;
            m_Pos       = 0;
            return ERR_OK;
        }
        
        void Bind()
        {
            m_BindFlag = true;
        }

        void Unbind()
        {
            m_BindFlag = false;
        }

        void Deattach()
        {
            if (isNotNULL(m_Data) && m_BindFlag)
            {
                FreeMemory(m_Data);
            }
            m_Data      = NULL;
            m_Size      = 0;
            m_BindFlag  = false;
            m_Pos       = 0;
        }
        
        PByte getData()
        {
            return m_Data;
        }
        XInt getSize() const
        {
            return m_Size;
        }
        bool getBindFlag() const
        {
            return m_BindFlag;
        }
        XInt getPos() const
        {
            return m_Pos;
        }
        void Clear()
        {
            m_Pos = 0;
        }
        XInt getUseLength() const
        {
            return m_Pos;
        }
        XInt getFreeLength() const
        {
            return m_Size - m_Pos;
        }
        PByte getUseData()
        {
            return m_Data;
        }
        PByte getFreeData()
        {
            return m_Data + m_Pos;
        }
        bool isAttached() const
        {
            return isNotNULL(m_Data);
        }
        XInt AppendByte(XByte paramByte)
        {
            return AppendData(paramByte);
        }
        ///追加一个指定的数据
        template<class T>
        XInt AppendData(const T & paramData)
        {
            if( (XInt)sizeof(T) > getFreeLength() )
            {
                return ERR_FAIL;
            }
            MemoryCopy(getFreeData(), (const void *)&paramData, (XMemorySize)sizeof(T));
            m_Pos += (XInt)sizeof(T);
            return ERR_OK;
        }
        ///添加指定大小的数据
        XInt Append(const char* paramData, int paramDataSize)
        {
            if (isNULL(paramData) || paramDataSize < 1)
            {
                return ERR_FAIL;
            }
            if (paramDataSize > getFreeLength())  
            {
                return ERR_FAIL;
            }
            MemoryCopy(getFreeData(), (const void *)paramData, (XMemorySize)paramDataSize);
            m_Pos += paramDataSize;
            return ERR_OK;
        }

        ///将游标向后跳指定的字节数
        XInt Skip(XInt paramSkipBytes)
        {
            if (paramSkipBytes < 0)
            {
                return ERR_FAIL;
            }

            if (paramSkipBytes > getFreeLength())
            {
                return ERR_FAIL;
            }

            m_Pos += paramSkipBytes;
            return 0;
        }

        ///移除缓冲区中前面指定长度字节
        XInt Remove(XInt paramRemoveBytes)
        {
            if (paramRemoveBytes > m_Pos)
            {
                return ERR_FAIL;
            }
            else if (paramRemoveBytes < m_Pos) 
            {
                MemoryMove(m_Data, m_Data + paramRemoveBytes, m_Pos - paramRemoveBytes);
            }
            m_Pos -= paramRemoveBytes;
            return ERR_OK;
        }
    private:
        PByte   m_Data;
        XInt    m_Size;
        XInt    m_Pos;
        bool    m_BindFlag; ///<如果是绑定的话，在执行析构函数的时候或重新分配的时候，会释放指定的内存区域
    };

    class XDataReader
    {
    public:
        XDataReader()
            :m_Data(NULL),m_DataSize(0),m_Pos(0)
        {}
        XDataReader(const XByte * paramData, XInt paramDataSize)
            :m_Data(paramData), m_DataSize(paramDataSize), m_Pos(0)
        {}

        void SetData(const XByte * paramData, XInt paramDataSize)
        {
            m_Data     = paramData;
            m_DataSize = paramDataSize;
        }

        const XByte * getData() const
        {
            return m_Data;
        }

        XInt getDataSize() const
        {
            return m_DataSize;
        }

        XInt getPos() const
        {
            return m_Pos;
        }

        void setPos(XInt paramPos)
        {
            m_Pos = paramPos;
        }

        XInt getFreeSize() const
        {
            return m_DataSize - m_Pos;
        }
        ///从指定位置读取一个字节
        bool ReadByte(XByte & paramValue) 
        {
            return ReadDataTemplate(paramValue);
        }
        ///从指定位置读取一个字符
        bool ReadChar(XChar & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///从指定位置读取一个布尔值
        bool ReadBool(bool & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///从指定位置读取一个16位无符号整数
        bool ReadWord(XWord & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///从指定位置读取一个16位有符号整数
        bool ReadShort(XShort & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///从指定位置读取一个网络顺序的16位无符号整数
        bool ReadDWord(XDWord & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///从指定位置读取一个网络顺序16位有符号整数
        bool ReadInt(XInt & paramVaue) 
        {
            return ReadDataTemplate(paramVaue);
        }
        ///从指定位置读取一个64位无符号整数
        bool ReadDDWord(XDDWord & paramVaue) 
        {
            return ReadDataTemplate(paramVaue);
        }
        ///从指定位置读取一个64位有符号整数
        bool ReadLong(XLong & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }   
        ///从指定位置读取一个单精度浮点数
        bool ReadFloat(XFloat & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///从指定位置读取一个64位双精度浮点数
        bool ReadDouble(XDouble & paramValue) 
        {
            return ReadDataTemplate(paramValue);
        }
        ///从指定位置读取指定字节数的数据
        bool ReadData(void * paramData,XInt paramReadSize)
        {
            bool bRet;
            if (((m_DataSize - m_Pos) >= paramReadSize) && (paramReadSize > 0))
            {
                MemoryCopy( (void *)(m_Data + m_Pos), (const void *)paramData,paramReadSize);
                m_Pos += paramReadSize;
                bRet = true;
            }
            else
            {
                bRet = false;
            }
            return bRet;
        }
        ///从指定位置读取一个16位无符号整数
        bool ReadNetworkWord(XWord & paramValue)
        {
            return ReadDataNetworkTemplate(paramValue);
        }
        ///从指定位置读取一个16位有符号整数
        bool ReadNetworkShort(XShort & paramValue)
        {
            return ReadDataNetworkTemplate(paramValue);
        }
        ///从指定位置读取一个网络顺序的16位无符号整数
        bool ReadNetworkDWord(XDWord & paramValue)
        {
            return ReadDataNetworkTemplate(paramValue);
        }
        ///从指定位置读取一个网络顺序16位有符号整数
        bool ReadNetworkInt(XInt & paramVaue) 
        {
            return ReadDataNetworkTemplate(paramVaue);
        }
        ///从指定位置读取一个64位无符号整数
        bool ReadNetworkDDWord(XDDWord & paramVaue) 
        {
            return ReadDataNetworkTemplate(paramVaue);
        }
        ///从指定位置读取一个64位有符号整数
        bool ReadNetworkLong(XLong & paramValue)
        {
            return ReadDataNetworkTemplate(paramValue);
        }   

        template<class T>
        bool ReadDataTemplate(T & paramValue)
        {
            bool bRet;
            if ((m_DataSize - m_Pos) >= (XInt)sizeof(T))
            {
                paramValue = *((const T *)(m_Data + m_Pos));
                m_Pos += (XInt)sizeof(T);
                bRet = true;
            }
            else
            {
                bRet = false;
            }
            return bRet;
        }

        template<class T>
        bool ReadDataNetworkTemplate(T & paramValue)
        {
            bool bRet;
            if ((m_DataSize - m_Pos) >= (XInt)sizeof(T))
            {
                XByte * pData = ((XByte *)&paramValue) + sizeof(T) - 1;
                const XByte * pDataSrc = m_Data + m_Pos;
                for(size_t i = 0; i < sizeof(T); i++, pData --, pDataSrc ++)
                {
                    *pData = *pDataSrc;                  
                }
                bRet = true;
                m_Pos += (XInt)sizeof(T);
            }
            else
            {
                bRet = false;
            }
            return bRet;
        }
        ///跳过指定的字节数
        void Skip(XInt paramSkipByteCount)
        {
            m_Pos += paramSkipByteCount;
        }
    private:
        const XByte * m_Data;
        XInt          m_DataSize;
        XInt          m_Pos;
    };
    class XDataWrite
    {
    public:
        XDataWrite()
            :m_Data(NULL),m_DataSize(0),m_Pos(0)
        {}
        XDataWrite(XByte * paramData, XInt paramDataSize)
            :m_Data(paramData), m_DataSize(paramDataSize), m_Pos(0)
        {}

        void SetData(XByte * paramData, XInt paramDataSize)
        {
            m_Data     = paramData;
            m_DataSize = paramDataSize;
        }

        XByte * getData() 
        {
            return m_Data;
        }

        XInt getDataSize() const
        {
            return m_DataSize;
        }

        XInt getPos() const
        {
            return m_Pos;
        }

        void setPos(XInt paramPos)
        {
            m_Pos = paramPos;
        }

        XInt getFreeSize() const
        {
            return m_DataSize - m_Pos;
        }
        ///从指定位置读取一个字节
        bool WriteByte(XByte & paramValue) 
        {
            return WriteDataTemplate(paramValue);
        }
        ///从指定位置读取一个字符
        bool WriteChar(XChar & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///从指定位置读取一个布尔值
        bool WriteBool(bool & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///从指定位置读取一个16位无符号整数
        bool WriteWord(XWord & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///从指定位置读取一个16位有符号整数
        bool WriteShort(XShort & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///从指定位置读取一个网络顺序的16位无符号整数
        bool WriteDWord(XDWord & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///从指定位置读取一个网络顺序16位有符号整数
        bool WriteInt(XInt & paramVaue) 
        {
            return WriteDataTemplate(paramVaue);
        }
        ///从指定位置读取一个64位无符号整数
        bool WriteDDWord(XDDWord & paramVaue) 
        {
            return WriteDataTemplate(paramVaue);
        }
        ///从指定位置读取一个64位有符号整数
        bool WriteLong(XLong & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }   
        ///从指定位置读取一个单精度浮点数
        bool WriteFloat(XFloat & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///从指定位置读取一个64位双精度浮点数
        bool WriteDouble(XDouble & paramValue) 
        {
            return WriteDataTemplate(paramValue);
        }
        ///从指定位置读取指定字节数的数据
        bool WriteData(void * paramData,XInt paramReadSize)
        {
            bool bRet;
            if (((m_DataSize - m_Pos) >= paramReadSize) && (paramReadSize > 0))
            {
                MemoryCopy(paramData, (const void *)(m_Data + m_Pos), paramReadSize);
                m_Pos += paramReadSize;
                bRet = true;
            }
            else
            {
                bRet = false;
            }
            return bRet;
        }
        ///从指定位置读取一个16位无符号整数
        bool WriteNetworkWord(XWord & paramValue)
        {
            return WriteDataNetworkTemplate(paramValue);
        }
        ///从指定位置读取一个16位有符号整数
        bool WriteNetworkShort(XShort & paramValue)
        {
            return WriteDataNetworkTemplate(paramValue);
        }
        ///从指定位置读取一个网络顺序的16位无符号整数
        bool WriteNetworkDWord(XDWord & paramValue)
        {
            return WriteDataNetworkTemplate(paramValue);
        }
        ///从指定位置读取一个网络顺序16位有符号整数
        bool WriteNetworkInt(XInt & paramVaue) 
        {
            return WriteDataNetworkTemplate(paramVaue);
        }
        ///从指定位置读取一个64位无符号整数
        bool WriteNetworkDDWord(XDDWord & paramVaue) 
        {
            return WriteDataNetworkTemplate(paramVaue);
        }
        ///从指定位置读取一个64位有符号整数
        bool WriteNetworkLong(XLong & paramValue)
        {
            return WriteDataNetworkTemplate(paramValue);
        }   

        template<class T>
        bool WriteDataTemplate(T & paramValue)
        {
            bool bRet;
            if ((m_DataSize - m_Pos) >= (XInt)sizeof(T))
            {
                *((T *)(m_Data + m_Pos)) = paramValue;
                m_Pos += (XInt)sizeof(T);
                bRet = true;
            }
            else
            {
                bRet = false;
            }
            return bRet;
        }

        template<class T>
        bool WriteDataNetworkTemplate(T & paramValue)
        {
            bool bRet;
            if ((m_DataSize - m_Pos) >= (XInt)sizeof(T))
            {
                XByte * pData = ((XByte *)&paramValue) + sizeof(T) - 1;
                XByte * pDataSrc = m_Data + m_Pos;
                for(size_t i = 0; i < sizeof(T); i++, pData --, pDataSrc ++)
                {
                    *pDataSrc = *pData;                  
                }
                bRet = true;
                m_Pos += (XInt)sizeof(T);
            }
            else
            {
                bRet = false;
            }
            return bRet;
        }
    private:
        XByte * m_Data;
        XInt    m_DataSize;
        XInt    m_Pos;
    };
}
#endif
