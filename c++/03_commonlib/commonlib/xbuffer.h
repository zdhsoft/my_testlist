///XBuffer������
/**
 * ����һ����̬���������࣬��С��λ��1K������Ԥ��׼�����㹻���ڴ档
 *
 * zdhsoft 2011 ��Ȩ����
 *
 * @file xbuffer.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-20
 * company zdhsoft
 */
/**********************************************************************
    �����б�  //��Ҫ��������
    1��XBuffer������

    ��ʷ:       //��Ҫ�޸ļ�¼
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-20  1.0             ������ʼ�ļ�
***********************************************************************/
#ifndef _X_BUFFER_H_
#define _X_BUFFER_H_
#include <xstring.h>
namespace zdh
{
    ///����XBufferȱʡ���С
    const XInt XBYTE_BUFFER_MIN_BLOCK = 1024;

    class XBuffer
    {
    public:
        ///Ĭ�Ϲ��캯��
        XBuffer()
            :m_Capacity(0),m_Length(0),m_Data(NULL)
        {}
        ///����ָ������Ĺ��캯��
        template<class ElementType, int N>
        XBuffer( ElementType (&paramData)[N] )
            :m_Capacity(0),m_Length(0),m_Data(NULL)
        {
            AppendData( (void *)&paramData,  N * sizeof(ElementType));
        }       
        ///ָ��Ĭ�����ݹ��캯��
        /**
         * @param [in] paramData Ĭ�ϵ�����ָ��
         * @param [in] paramSize Ĭ�ϵ����ݴ�С
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
        ///Ĭ�Ͽ������캯��
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
        ///Ĭ����������
        ~XBuffer()
        {
            if( m_Capacity > 0 ) FreeMemory(m_Data);
            m_Capacity = 0;
            m_Length = 0;
            m_Data = NULL;
        }
        ///���������
        /**
         * @param [in] paramFree ��ʾ�Ƿ��ͷŻ�����
         *      - true ��ʾҪ�ͷŻ�����
         *      - false ��ʾ��Ҫ�ͷŻ�����
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
        ///ȡ����
        XInt getCapacity() const 
        { 
            return m_Capacity; 
        }
        ///ȡ��ǰ��Ч���ֽ���
        XInt getLength() const 
        { 
            return m_Length; 
        }
        ///ȡ����ָ��
        const XByte * getData() const 
        { 
            return m_Data; 
        }
        ///ȷ�������Ƿ�ﵽָ������С����
        /**
         * ȷ�������Ƿ�ﵽָ������С����,���δ��ָ������,����չ����
         * @param [in] paramMinimumCapacity ��С����
         */
        void ensureCapacity(XInt paramMinimumCapacity)
        {
            if( paramMinimumCapacity > m_Capacity ) 
            {
                expandCapacity(paramMinimumCapacity);
            }
        }
        ///����[]�����
        /**
         * @param [in] paramIndex ָ�����±�
         * @return ����ָ���ֽڵ�����
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
        ///����[]�����
        /**
         * @param [in] paramIndex ָ�����±�
         * @return ����ָ���ֽڵ�ֵ
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
        ///���ظ�ֵ�����
        /**
         * @param [in] paramBuffer Ҫ��ֵ�Ļ�����
         * @return ���ص�ǰ������������
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
        ///׷��һ������������
        /**
         * @param [in] paramBuffer ��׷�ӵĻ���������
         */
        void AppendBuffer(const XBuffer & paramBuffer)
        {
            AppendData( paramBuffer.m_Data, paramBuffer.m_Length );
        }
        ///׷��һ���ַ���
        void AppendString(const XAnsiString & paramString)
        {
            AppendData( paramString.c_str(), paramString.getLength() );
        }
        ///׷��һ���ַ���
        void AppendString(const XChar * paramString)
        {
            ZDH_ASSERT(paramString != NULL);
            AppendData( paramString, string_utils::Length(paramString) );
        }
        ///׷��һ�������Ԫ��
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
        ///׷��ָ��������
        /**
         * @param [in] paramData ָ��������
         * @param [in] paramSize ָ��׷�����ݵ��ֽ���
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
        ///׷��һ���ֽڵ�ֵ
        void AppendByte(XByte paramByte)
        {
            ensureCapacity(m_Length + 1);
            m_Data[ m_Length ++ ] = paramByte;
        }
        ///׷��һ���ַ���ֵ
        void AppendChar(XChar paramChar)
        {
            ensureCapacity( m_Length + 1 );
            m_Data[ m_Length ++ ] = (XByte)paramChar;
        }
        ///׷��һ������ֵ
        /// @param [in] paramBool ׷�Ӳ���ֵ
        ///     - true ׷��һ���ֽ�ֵ 1
        ///     - false ׷��һ���ֽ�ֵ 0 
        void AppendBool(XBool  paramBool)
        {
            ensureCapacity( m_Length + 1 );
            m_Data[m_Length ++] = paramBool?1:0;
        }
        ///׷��һ��16λ�޷�������
        void AppendWord(XWord paramWord)
        {
            ensureCapacity(m_Length + sizeof(XWord));
            *((XWord *)(m_Data + m_Length)) = paramWord;
            m_Length += sizeof(XWord);
        }
        ///׷��һ��16λ�з�������
        void AppendShort(XShort paramShort)
        {
            ensureCapacity(m_Length + sizeof(XShort));
            *((XShort *)(m_Data + m_Length)) = paramShort;
            m_Length += sizeof(XShort);
        }
        ///׷��һ������16λ�޷�������
        void AppendNetworkWord(XWord paramWord)
        {
            ensureCapacity(m_Length + 2);
            m_Data[m_Length++] = *(((XByte *)(&paramWord))+1);
            m_Data[m_Length++] = *((XByte *)(&paramWord));
        }
        ///׷��һ������16λ�з�������
        void AppendNetworkShort(XShort paramShort)
        {
            ensureCapacity(m_Length + 2);
            m_Data[m_Length++] = *(((XByte *)(&paramShort))+1);
            m_Data[m_Length++] = *((XByte *)(&paramShort));
        }
        ///׷��һ��32λ�з�������
        void AppendInt(XInt paramInt)
        {
            ensureCapacity(m_Length + sizeof(XInt));
            *((XInt *)(m_Data + m_Length)) = paramInt;
            m_Length += sizeof(XInt);
        }
        ///׷��һ��32λ�޷�������
        void AppendDWord(XDWord paramDWord)
        {
            ensureCapacity(m_Length + sizeof(XDWord));
            *((XDWord *)(m_Data + m_Length)) = paramDWord;
            m_Length += sizeof(XDWord);
        }
        ///׷��һ������32λ�з�������
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
        ///׷��һ������32λ�޷�������
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
        ///׷��һ��64λ�з�������
        void AppendLong(XLong paramLong)
        {
            ensureCapacity(m_Length + sizeof(XLong));
            *((XLong *)(m_Data + m_Length)) = paramLong;
            m_Length += sizeof(XLong);
        }
        ///׷��һ��64λ�޷�������
        void AppendDDWord(XDDWord paramDDWord)
        {
            ensureCapacity(m_Length + sizeof(XDDWord));
            *((XDDWord *)(m_Data + m_Length)) = paramDDWord;
            m_Length += sizeof(XDDWord);
        }
        ///׷��һ��64λ�з�������
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
        ///׷��һ��64λ�޷�������
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
        ///׷�ӵ����ȸ�����
        void AppendFloat(XFloat paramFloat)
        {
            ensureCapacity(m_Length + sizeof(XFloat));
            *((XFloat *)(m_Data + m_Length)) = paramFloat;
            m_Length += sizeof(XFloat);
        }
        ///׷��˫���ȸ�����
        void AppendDouble(XDouble paramDouble)
        {
            ensureCapacity(m_Length + sizeof(XDouble));
            *((XDouble *)(m_Data + m_Length)) = paramDouble;
            m_Length += sizeof(XDouble);
        }
        ///��ָ��λ�ö�ȡһ���ֽ�
        XByte ReadByte(XInt paramPos) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            return m_Data[paramPos];
        }
        ///��ָ��λ�ö�ȡһ���ַ�
        XChar ReadChar(XInt paramPos) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            return (XChar)m_Data[paramPos];
        }
        ///��ָ��λ�ö�ȡһ������ֵ
        XBool ReadBool(XInt paramPos) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            return m_Data[paramPos] != 0;
        }
        ///��ָ��λ�ö�ȡһ��16λ�޷�������
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
        ///��ָ��λ�ö�ȡһ��16λ�з�������
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
        ///��ָ��λ�ö�ȡһ������˳���16λ�޷�������
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
        ///��ָ��λ�ö�ȡһ������˳��16λ�з�������
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
    
        ///��ָ��λ�ö�ȡһ��32λ�޷�������
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
        ///��ָ��λ�ö�ȡһ��32λ�з�������
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
        ///��ָ��λ�ö�ȡһ������˳���32λ�޷�������
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
        ///��ָ��λ�ö�ȡһ������˳���32λ�з�������
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
        ///��ָ��λ�ö�ȡһ��64λ�޷�������
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
        ///��ָ��λ�ö�ȡһ��64λ�з�������
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
        ///��ָ��λ�ö�ȡһ������˳���64λ�޷�������
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
        ///��ָ��λ�ö�ȡһ������˳���64λ�з�������
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
        ///��ָ��λ�ö�ȡһ�������ȸ�����
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
        ///��ָ��λ�ö�ȡһ��64λ˫���ȸ�����
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
        ///��ָ��λ�ö�ȡָ���ֽ���������
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
        ///��ָ��λ�ö�ȡָ���ֽ��������ݵ��µĻ�����
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
        //������һ������<<������ķ���,���ڷ�����ڻ�������׷������
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
        ///��ָ����λ����д��һ���ֽ�
        void WriteByte(XInt paramPos,XByte paramByte) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            m_Data[paramPos] = paramByte;
        }
        ///��ָ����λ����д��һ���ַ�
        void WriteChar(XInt paramPos,XChar paramChar) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            m_Data[paramPos] = (XByte)paramChar;
        }
        ///��ָ����λ����д��һ������ֵ,����falseֵд��0,����true��д��1
        void WriteBool(XInt paramPos,XBool paramBool) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramPos >= 0 && paramPos < m_Length);
            if( paramPos < 0 || paramPos >= m_Length ) 
            {
                throw XEOutOfRange(paramPos, m_Length);
            }
            m_Data[paramPos] = (paramBool)?1:0;
        }
        ///��ָ����λ����д��һ��16�޷�������
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
        ///��ָ����λ����д��һ��16�з�������
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
        ///��ָ����λ����д��һ������˳���16�޷�������
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
        ///��ָ����λ����д��һ������˳���16�з�������
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

        ///��ָ����λ����д��һ��32�޷�������
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
        ///��ָ����λ����д��һ��32�з�������
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
        ///��ָ����λ����д��һ������˳���32�޷�������
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
        ///��ָ����λ����д��һ������˳���32�з�������
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
        ///��ָ����λ����д��һ��64�޷�������
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
        ///��ָ����λ����д��һ��64�з�������
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
        ///��ָ����λ����д��һ������˳���64�޷�������
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
        ///��ָ����λ����д��һ������˳���64�޷�������
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
        ///��ָ����λ����д��һ�������ȸ�����
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
        ///��ָ����λ����д��һ��˫���ȸ�����
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
        ///��ָ����λ����д��ָ���ֽ���������
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
        ///��ָ����λ����д��һ��������������
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
        ///ɾ�����������ָ���ֽ���������
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
        ///ɾ��������ָ��λ�ú��ֽ���������
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
        ///����->�����,�ṩ����ָ��ı��ʽ
        XBuffer * operator ->() 
        { 
            return this; 
        }
        ///����->�����,�ṩ����ָ��ı��ʽ
        const XBuffer * operator->() const 
        { 
            return this; 
        }
    private:
        ///����Ҫ׼�����ֽ���
        /**
         * @param paramPrepareLength ����Ҫ׼�����ֽ���
         * @return ���ؼ�����׼���ֽ���
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
        ///��չ����������
        /**
         * @param paramMinimumCapacity ��������
         * @param paramCopyData ��ʾ�Ƿ�ҪCopyԭ�������ݣ�Ĭ����ҪCopyԭ����
         * @return ������չ���
         *     - true ��ʾ��չ�ɹ�
         *     - false ��ʾ��չʧ��
         */
        bool expandCapacity(XInt paramMinimumCapacity,bool paramCopyData = true)
        {
            XInt newCapacity = m_Capacity * 2;
            
            if ( newCapacity < 0 )  return false; //������,�򷵻�false
            else if ( paramMinimumCapacity > newCapacity ) newCapacity = paramMinimumCapacity;
            
            XInt iPrepareLength = PrepareLength(newCapacity);
            if( iPrepareLength < paramMinimumCapacity ) return false; //��������������,С��ʵ������Ҫ������,�򷵻�false 

            PByte tmp = (PByte)AllocMemory(iPrepareLength); //�����µ��ڴ�
            
            if( tmp == NULL ) throw XEOutOfMemory(); //��������ڴ�ʧ��
            
            if( paramCopyData ) //�����Ҫcopyԭʼ���� 
            {
                if( m_Length > 0 ) MemoryCopy(tmp, m_Data, m_Length);  
            }
            else m_Length = 0;  //�������Ҫ,�򽫳�����Ϊ0

            if( m_Data != NULL ) FreeMemory(m_Data);    //�������ԭʼ����,���ͷ�ԭʼ����
            m_Capacity = iPrepareLength;            //�����µ�����
            m_Data = tmp;                           //�����µ�����
            return true;
        }
    private:
        XInt m_Capacity;    ///<����
        XInt m_Length;      ///<����
        XByte * m_Data;     ///<��ʼָ��
    };

    ///buffer����
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
        ///׷��һ��ָ��������
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
        ///���ָ����С������
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

        ///���α������ָ�����ֽ���
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

        ///�Ƴ���������ǰ��ָ�������ֽ�
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
        bool    m_BindFlag; ///<����ǰ󶨵Ļ�����ִ������������ʱ������·����ʱ�򣬻��ͷ�ָ�����ڴ�����
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
        ///��ָ��λ�ö�ȡһ���ֽ�
        bool ReadByte(XByte & paramValue) 
        {
            return ReadDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ���ַ�
        bool ReadChar(XChar & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������ֵ
        bool ReadBool(bool & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ��16λ�޷�������
        bool ReadWord(XWord & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ��16λ�з�������
        bool ReadShort(XShort & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������˳���16λ�޷�������
        bool ReadDWord(XDWord & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������˳��16λ�з�������
        bool ReadInt(XInt & paramVaue) 
        {
            return ReadDataTemplate(paramVaue);
        }
        ///��ָ��λ�ö�ȡһ��64λ�޷�������
        bool ReadDDWord(XDDWord & paramVaue) 
        {
            return ReadDataTemplate(paramVaue);
        }
        ///��ָ��λ�ö�ȡһ��64λ�з�������
        bool ReadLong(XLong & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }   
        ///��ָ��λ�ö�ȡһ�������ȸ�����
        bool ReadFloat(XFloat & paramValue)
        {
            return ReadDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ��64λ˫���ȸ�����
        bool ReadDouble(XDouble & paramValue) 
        {
            return ReadDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡָ���ֽ���������
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
        ///��ָ��λ�ö�ȡһ��16λ�޷�������
        bool ReadNetworkWord(XWord & paramValue)
        {
            return ReadDataNetworkTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ��16λ�з�������
        bool ReadNetworkShort(XShort & paramValue)
        {
            return ReadDataNetworkTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������˳���16λ�޷�������
        bool ReadNetworkDWord(XDWord & paramValue)
        {
            return ReadDataNetworkTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������˳��16λ�з�������
        bool ReadNetworkInt(XInt & paramVaue) 
        {
            return ReadDataNetworkTemplate(paramVaue);
        }
        ///��ָ��λ�ö�ȡһ��64λ�޷�������
        bool ReadNetworkDDWord(XDDWord & paramVaue) 
        {
            return ReadDataNetworkTemplate(paramVaue);
        }
        ///��ָ��λ�ö�ȡһ��64λ�з�������
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
        ///����ָ�����ֽ���
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
        ///��ָ��λ�ö�ȡһ���ֽ�
        bool WriteByte(XByte & paramValue) 
        {
            return WriteDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ���ַ�
        bool WriteChar(XChar & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������ֵ
        bool WriteBool(bool & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ��16λ�޷�������
        bool WriteWord(XWord & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ��16λ�з�������
        bool WriteShort(XShort & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������˳���16λ�޷�������
        bool WriteDWord(XDWord & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������˳��16λ�з�������
        bool WriteInt(XInt & paramVaue) 
        {
            return WriteDataTemplate(paramVaue);
        }
        ///��ָ��λ�ö�ȡһ��64λ�޷�������
        bool WriteDDWord(XDDWord & paramVaue) 
        {
            return WriteDataTemplate(paramVaue);
        }
        ///��ָ��λ�ö�ȡһ��64λ�з�������
        bool WriteLong(XLong & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }   
        ///��ָ��λ�ö�ȡһ�������ȸ�����
        bool WriteFloat(XFloat & paramValue)
        {
            return WriteDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ��64λ˫���ȸ�����
        bool WriteDouble(XDouble & paramValue) 
        {
            return WriteDataTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡָ���ֽ���������
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
        ///��ָ��λ�ö�ȡһ��16λ�޷�������
        bool WriteNetworkWord(XWord & paramValue)
        {
            return WriteDataNetworkTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ��16λ�з�������
        bool WriteNetworkShort(XShort & paramValue)
        {
            return WriteDataNetworkTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������˳���16λ�޷�������
        bool WriteNetworkDWord(XDWord & paramValue)
        {
            return WriteDataNetworkTemplate(paramValue);
        }
        ///��ָ��λ�ö�ȡһ������˳��16λ�з�������
        bool WriteNetworkInt(XInt & paramVaue) 
        {
            return WriteDataNetworkTemplate(paramVaue);
        }
        ///��ָ��λ�ö�ȡһ��64λ�޷�������
        bool WriteNetworkDDWord(XDDWord & paramVaue) 
        {
            return WriteDataNetworkTemplate(paramVaue);
        }
        ///��ָ��λ�ö�ȡһ��64λ�з�������
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
