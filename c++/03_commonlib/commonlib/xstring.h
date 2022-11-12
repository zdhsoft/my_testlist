///�ַ�����ģ��
/**
 * �ַ�����ģ��
 * ����ṩ��ԱȽϼ��ɵ��ַ����࣬���ڱȽϷ���Ĳ�����
 *
 * zdhsoft 2011 ��Ȩ����
 *
 * @file xstring.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-11
 * company zdhsoft
 */
/**********************************************************************
    �����б�  //��Ҫ��������
    1���ַ�����ģ��

    ��ʷ:       //��Ҫ�޸ļ�¼
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-01  1.0             ������ʼ�ļ�
***********************************************************************/
#ifndef _X_STRING_H_
#define _X_STRING_H_
#include <xstring_utils.h>
#include <xmemory.h>
#include <string>
namespace zdh
{
    ///�ַ�������ģ��
    template<class T = XChar>
    class XStringBase
    {
    public:
        enum
        {
            npos = -1,
            force_dword = 0x7fffffff //ǿ�Ƹ�ö������Ϊ32λ����
        };
    public:
        typedef T StringChar;
        typedef T * TPointer;
        typedef const T * ConstTPointer;
    private:
        ///�ַ����ṹ�ṹ��
        struct SStringStruct
        {
            XInt Length;        ///<�ߴ�
            XInt Capacity;      ///<��ǰ�ַ���������
            //Data              ///<��ǰ����ָ�����ڵ�λ��
        };
        //�ַ����ڵĳ�������,�����ⲿʹ�õ�
        enum 
        { 
            STRING_BLOCK_SIZE = 64,             //��λ���С
            CHAR_SIZE = sizeof(T),              //ÿ���ַ����Ĵ�С
            HEAD_SIZE = sizeof(SStringStruct),  //�ַ���ͷ���ֽ���
            XSTRING_BASE_ENUM_FORCE_DWORD = 0x7FFFFFFF //ǿ�Ƹ�EnumΪ32λ
        };  //�ַ�����С�ڴ���С
    public:
        ///Ĭ�Ϲ��캯��
        XStringBase() 
            :m_Data(NULL) 
        {}
        ///���캯��
        XStringBase(const T * paramString)
            :m_Data(NULL)
        {
            XInt iLength = string_utils::Length(paramString);
            if( iLength > 0)
            {
                ensureCapacity(iLength);
                CopyData(paramString, (T *)m_Data, iLength);
                getOriData()->Length = iLength;
            }
        }
        ///Ĭ�Ͽ������캯��
        XStringBase(const XStringBase<T> & paramString)
            :m_Data(NULL)
        {
            XInt iLength = paramString.getLength();
            if( iLength > 0)
            {
                ensureCapacity(iLength);
                CopyData(paramString.c_str(), (T *)m_Data, iLength);
                getOriData()->Length = iLength;
            }
        }
        ///���캯��
        XStringBase(const T & paramChar)
            :m_Data(NULL)
        {
            ensureCapacity(1);
            *((T *)m_Data) = paramChar;
            *(((T *)m_Data) + 1) = 0;
            getOriData()->Length = 1;

        }
        ///��������
        ~XStringBase()
        {
            if( isNotNULL(m_Data) )
            {
                FreeMemory(getOriData());
                m_Data = NULL;
            }
        }
        ///ȡ�ַ�����С����ֽ���
        XInt getBlockBytes() const { return STRING_BLOCK_SIZE; }
        ///ȡ�ַ����ֽ���
        XInt getCharBytes() const { return CHAR_SIZE; }
        ///ȡ��ǰ����
        XInt getCapacity() const
        {
            XInt iRet = 0;
            if( isNotNULL(m_Data) ) 
            {
                iRet = getOriData()->Capacity;
            }
            return iRet;
        }
        XInt capacity() const
        {
            return getCapacity();
        }
        ///ȡ��ǰ�ַ����ĳ���
        XInt getLength() const
        {
            XInt iRet = 0;
            if( isNotNULL(m_Data) )
            {
                iRet = getOriData()->Length;
            }
            return iRet;
        }
        //����STL��string ����
        XInt length() const
        {
            XInt iRet = 0;
            if( isNotNULL(m_Data) )
            {
                iRet = getOriData()->Length;
            }
            return iRet;
        }
        XInt size() const
        {
            return length();
        }
        ///ȡ������������
        XInt getMaxCapacity() const { return (0x7ffffff0 - HEAD_SIZE) / CHAR_SIZE;  }
        ///ȷ��װ���ַ�����(���Զ�����0��β)
        void ensureCapacity(XInt paramCharCapacity)
        {
            if( paramCharCapacity > 0)
            {
                expandCapacity(paramCharCapacity + 1); //����һ���ַ�0��λ��
            }
        }
        ///ȡ�ַ���������
        const T * c_str() const
        {
            static T sNullString[1] = {0};
            if( isNULL(m_Data) ) 
            {
                return sNullString;
            }
            else 
            {
                return (const T *)m_Data;
            }
        }
        const T * data() const
        {
            return c_str();
        }
        ///�жϵ�ǰ�ַ����Ƿ�Ϊ��
        bool isEmpty() const { return getLength() == 0; }
        bool empty() const
        {
            return isEmpty();
        }
        bool isNotEmpty() const { return getLength() != 0; }
        ///ȡ�ַ���ָ�뺯��
        const void * Data() const { return m_Data; }
        ///��ֵ����
        /**
            ����ǰ����Ϊָ���Ĵ�
         */
        void Assign(const XStringBase<T> & paramR)
        {
            if( &paramR != this )
            {
                Assign(paramR.c_str(), paramR.getLength());
            }
        }
        ///��ֵ����
        /**
            ����ǰ����Ϊָ���Ĵ�    
         */
        void Assign(const T * paramR)
        {
            ZDH_ASSERT(paramR != NULL);
            XInt iLength = string_utils::Length(paramR);
            Assign(paramR, iLength);
        }
        ///��ֵ����
        /**
            ����ǰ����Ϊָ���Ĵ�    
            @param [in] paramR ָ���Ĵ�
            @param [in] paramLength ָ�����ĳ���
         */
        void Assign(const T * paramR, XInt paramLength)
        {
            if( c_str() == paramR ) return;
            XInt iLength = paramLength;
            if( iLength > 0)
            {
                ensureCapacity(iLength+1);
                CopyData(paramR, (T *)m_Data, iLength);
                getOriData()->Length = iLength;
            }
            else
            {
                ToEmptyString();
            }
        }
        ///��ֵ����
        /**
            ����ǰ����Ϊֻ��ָ���ַ��Ĵ�    
         */
        void Assign(const T & paramR)
        {
            if( paramR != 0 )
            {
                ensureCapacity(1);
                *((T *)m_Data)  = paramR;
                *(((T *)m_Data) + 1) = 0;
                getOriData()->Length = 1;
            }
            else
            {
                ToEmptyString();
            }
        }
        ///׷��ָ�����ַ���
        void AppendString(const XStringBase<T> & paramR)
        {
            XInt iLength = paramR.getLength();
            if( iLength > 0)
            {
                XInt iThisLength = getLength();
                ensureCapacity(iThisLength + iLength);
                CopyData(paramR.c_str(), ((T *)m_Data) + iThisLength, iLength);
                getOriData()->Length = iLength + iThisLength;
            }
        }
        ///׷��ָ�����ַ���
        void AppendString(const XStringBase<T> & paramR,XInt paramCount)
        {
            XInt iLength = paramR.getLength();
            if( iLength > 0 && paramCount > 0)
            {
                XInt iThisLength = getLength();
                ensureCapacity(iThisLength + (iLength * paramCount));
                T * p = ((T *)m_Data) + iThisLength;
                const T * s = paramR.c_str();
                for(XInt i = 0; i < paramCount; i++)
                {
                    CopyData(s, p, iLength);
                    p += iLength;

                }
                getOriData()->Length = (iLength * paramCount )+ iThisLength ;
            }
        }
        ///׷��ָ�����ַ���
        void AppendString(const T * paramR)
        {
            AppendString(paramR, string_utils::Length(paramR));
        }
        ///׷��ָ�����ȵ��ַ���
        void AppendString(const T * paramR, XInt paramLength)
        {
            XInt iLength = paramLength;//string_utils::Length(paramR);
            if( iLength > 0 && paramR != NULL )
            {
                XInt iThisLength = getLength();
                ensureCapacity(iThisLength + iLength);
                CopyData(paramR, ((T *)m_Data) + iThisLength, iLength);
                getOriData()->Length = iLength + iThisLength;
            }
        }
        void AppendString(const T * paramR, XInt paramLength, XInt paramCount)
        {
            XInt iLength = paramLength;
            if( iLength > 0 && paramR != NULL && paramCount > 0 )
            {
                XInt iThisLength = getLength();
                ensureCapacity(iThisLength + (iLength * paramCount));
                T * p = ((T *)m_Data) + iThisLength;
                for(XInt i = 0; i < paramCount; i++)
                {
                    CopyData(paramR, p, iLength);
                    p += iLength;
                }
                getOriData()->Length = (iLength * paramCount)+ iThisLength;
            }
        }
        ///׷��һ���ַ�
        void AppendChar(const T paramR)
        {
            AppendChar(paramR,1);
        }
        ///׷��ָ���������ַ�
        /**
            �ַ�'\0'���ܱ�����
            @param [in] paramR Ҫ׷�ӵ��ַ�
            @param [in] paramCount Ҫ׷�ӵĸ���
         */
        void AppendChar(const T paramR, XInt paramCount)
        {
            if( paramR != 0 && paramCount > 0 )
            {
                XInt iThisLength = getLength();
                ensureCapacity(iThisLength + paramCount);
                T * p = ((T *)m_Data) + iThisLength;
                for(XInt i = 0; i < paramCount; i++)
                {
                    *p++ = paramR;
                }
                *p = 0;
                getOriData()->Length = iThisLength + paramCount;                
            }
        }
        ///ȡָ���±���ַ�
        /**
            @param [in] paramIndex ָ�����±꣬��Ч��Χ��[0,getLength()-1];
         */
        T at(XInt paramIndex) const;
        ///ȡָ���±���ַ�����
        /**
            @param [in] paramIndex ָ�����±꣬��Ч��Χ��[0,getLength()-1];
         */
        T & at(XInt paramIndex);
        ///���ָ�����±��Ƿ���Ч
        bool CheckIndex(XInt iIndex) const
        {
            return iIndex >= 0 && iIndex < getLength();
        }
        ///�����Ӵ���λ��
        /**
            ����Ӵ����ڣ��򷵻��Ӵ����±꣬��Ч�±���[0,getLength()-1]֮��;
            ����Ӵ�Ϊ�գ��򷵻�npos;
            @param [in] paramSubString �Ӵ�
            @return XInt �����Ӵ����±�
                - npos ��ʾδ�ҵ��Ӵ�
                - >=0 ��ʾ���ض�Ӧ�Ӵ����±�

         */
        XInt Pos(const XStringBase<T> & paramSubString) const
        {
            return Pos(0,paramSubString);
        }
        ///�����Ӵ���λ��
        /**
            ����Ӵ����ڣ��򷵻��Ӵ����±꣬��Ч�±���[0,getLength()-1]֮��;
            ����Ӵ�Ϊ�գ��򷵻�npos;
            @param [in] paramSubString �Ӵ�
            @return XInt �����Ӵ����±�
                - npos ��ʾδ�ҵ��Ӵ�
                - >=0 ��ʾ���ض�Ӧ�Ӵ����±�

         */
        XInt Pos(const T * paramSubString) const
        {
            return Pos(0, paramSubString, string_utils::Length(paramSubString));
        }
        ///�����Ӵ���λ��
        /**
            ����Ӵ����ڣ��򷵻��Ӵ����±꣬��Ч�±���[0,getLength()-1]֮��;
            ����Ӵ�Ϊ�գ��򷵻�npos;
            @param [in] paramSubString �Ӵ�
            @param [in] paramSubStringLength �Ӵ��ĳ��� 
            @return XInt �����Ӵ����±�
                - npos ��ʾδ�ҵ��Ӵ�
                - >=0 ��ʾ���ض�Ӧ�Ӵ����±�

         */
        XInt Pos(const T * paramSubString, XInt paramSubStringLength) const
        {
            return Pos(0, paramSubString, paramSubStringLength);
        }
        ///�����Ӵ���λ��
        /**
            ����Ӵ����ڣ��򷵻��Ӵ����±꣬��Ч�±���[0,getLength()-1]֮��;
            ����Ӵ�Ϊ�գ��򷵻�npos;
            @param [in] paramStartPos ��ʼ���±�
            @param [in] paramSubString �Ӵ�
            @param [in] paramSubStringLength �Ӵ��ĳ��� 
            @return XInt �����Ӵ����±�
                - npos ��ʾδ�ҵ��Ӵ�
                - >=0 ��ʾ���ض�Ӧ�Ӵ����±�

         */
        XInt Pos(XInt paramStartPos, const T * paramSubString, XInt paramSubStringLength) const
        {
            ZDH_ASSERT(paramSubString != NULL);
            ZDH_ASSERT(paramSubStringLength == string_utils::Length(paramSubString));
            if(isEmpty() || paramSubStringLength== 0)
            {
                return npos;
            }
            if( paramStartPos < 0 ) 
            {
                paramStartPos = 0;
            }
            else if( paramStartPos >= getLength() ) 
            {
                return npos;
            }
            const T * s1 = c_str() + paramStartPos;
            const T * s2 = paramSubString;
            const T * pFind = FindString( s1, s2 );
            if( isNULL(pFind) ) 
            {
                return npos;
            }
            return (XInt(pFind - s1) + paramStartPos);
        }
        ///��ָ����ʼ��λ�ã������Ӵ���λ��
        /**
            ����Ӵ����ڣ��򷵻��Ӵ����±꣬��Ч�±���[0,getLength()-1]֮��;
            ����Ӵ�Ϊ�գ��򷵻�npos;
            @param [in] paramStartPos ��ʼ��λ��
            @param [in] paramSubString �Ӵ�
            @return XInt �����Ӵ����±�
                - npos ��ʾδ�ҵ��Ӵ�
                - >=0 ��ʾ���ض�Ӧ�Ӵ����±�

         */
        XInt Pos(const XInt paramStartPos, const XStringBase<T> & paramSubString) const
        {
            return Pos(paramStartPos, paramSubString.c_str(), paramSubString.getLength());
        }
        ///ȷ���ַ���λ��
        /**
            ����ַ�Ϊ0,�򷵻�npos
            ����ַ����ڣ��򷵻��ַ����±꣬��Ч�±���[0,getLength()-1]֮��;
            @param [in] paramChar Ҫ���ҵ��ַ�
            @return XInt �����ַ����±�
                - npos ��ʾδ�ҵ��ַ�
                - >=0 ��ʾ���ض�Ӧ�ַ����±�
         */
        XInt Pos(const T & paramChar) const
        {
            if( isEmpty() ) return npos;
            if( paramChar == 0 ) return npos;
            const T * s1 = c_str();
            T s2[2];
            s2[0] = paramChar;
            s2[1] = 0;
            const T * pFind = FindString( s1, s2 );
            if( isNULL(pFind) ) return npos;
            return XInt(pFind - s1);
        }
        ///��ָ����ʼ��λ�ã������ַ�
        /**
            @param [in] paramStartPos ָ����ʼ��λ�ã���0��ʼ
            @param [in] paramChar ���ҵ��ַ�
            @return XInt �����ַ����±�
                - npos ��ʾδ�ҵ��ַ�
                - >=0 ��ʾ���ض�Ӧ�ַ����±�
         */
        XInt Pos(const XInt paramStartPos, const T & paramChar) const
        {
            if( paramStartPos < 0 ) 
            {
                return Pos(paramChar);
            }
            else if( paramStartPos >= getLength() ) 
            {
                return npos;
            }
            const T * s1 = c_str() + paramStartPos;
            T s2[2];
            s2[0] = paramChar;
            s2[1] = 0;
            const T * pFind = FindString( s1, s2 );
            if( isNULL(pFind) ) return npos;
            return ((XInt)(pFind - s1)) + paramStartPos;
        }
        //Ϊ����stl��string����
        XInt find(T tofind, XInt offset) const
        {
            XInt n = getLength();
            const T * str = c_str();
            if (offset >= n) return npos;
            const T * p = str + offset;
            XInt i = 0;
            
            for (; i < n ; ++p, ++i)
            {
                if (*p == tofind) return XInt( p - str );
            }
            return npos;
        }
        
        XInt find(T tofind)
        {
            return find(tofind,0);
        }

        XInt rfind(T tofind, XInt offset) const
        {
            XInt n = getLength();
            const T * str = c_str();
            if(offset >= n || offset < 0) 
            {
                offset = n - 1;
            }
            const T * p = str + offset;
            XInt i = offset;
            for(; i >= 0; --p, --i)
            {
                if(*p == tofind) return (XInt)(p - str);
            }
            return npos;
        }
        XInt rfind(T tofind) const
        {
            return rfind(tofind, getLength() - 1);
        }
        void clear()
        {
            ToEmptyString();
        }
        void reserve (XInt cap)
        {
            ensureCapacity(cap);
        }


        ///�滻�ַ�
        /**
            @param [in] paramFindChar ���ҵ��ַ�
            @param [in] paramDestChar Ҫ���滻�ɵ��ַ�
            @return XInt ���滻���ַ�����
         */
        XInt ReplaceChar(const T &paramFindChar, const T & paramDestChar)
        {
            ZDH_ASSERT(paramFindChar != paramDestChar);
            XInt iRetReplaceCount = 0;
            XInt iLength = getLength();
            if( paramDestChar != paramFindChar && iLength > 0 )
            {
                T * pData = (T *)m_Data;
                for(XInt i = 0; i < iLength; i++, pData ++)
                {
                    if( * pData == paramFindChar )
                    {
                        iRetReplaceCount ++;
                        *pData = paramDestChar;
                    }
                }
            }
            return iRetReplaceCount;
        }
        ///ָ��λ���ַ���
        /**
            @param [in] paramPos �����λ��
            @param [in] paramInsertString ������ַ���
         */
        void InsertString(XInt paramPos, const XStringBase<T> & paramInsertString, XInt paramInsertCount = 1)
        {
            InsertString(paramPos, paramInsertString.c_str(), paramInsertString.getLength(),paramInsertCount);
        }
        ///ָ��λ���ַ���
        /**
            @param [in] paramPos �����λ��
            @param [in] paramInsertString ������ַ���
         */
        void InsertString(XInt paramPos, const T * paramInsertString, XInt paramInsertCount = 1)
        {
            InsertString(paramPos, paramInsertString, string_utils::Length(paramInsertString),paramInsertCount);
        }
        ///ָ��λ���ַ���
        /**
            @param [in] paramPos �����λ��
            @param [in] paramInsertString ������ַ���
            @param [in] paramInsertLength Ҫ������ַ����ĳ���
            @param [in] paramInsertCount �������봮�Ĵ�����Ĭ��Ϊ1
         */
        void InsertString(XInt paramPos, const T * paramInsertString, XInt paramInsertLength, XInt paramInsertCount)
        {
            ZDH_ASSERT(paramInsertString != NULL);
            ZDH_ASSERT(paramInsertLength >= 0);
            ZDH_ASSERT(paramInsertLength == string_utils::Length(paramInsertString));
            if( paramInsertCount <=0 ) return;
            XInt iLength = getLength();
            XInt iInsertLength = paramInsertLength;
            XInt iAllInsertLength = iInsertLength * paramInsertCount;
            if( iInsertLength > 0) //�����Ҫ���������
            {
                if( paramPos < 0 ) paramPos = 0;
                ensureCapacity(iLength + iAllInsertLength);
                if( paramPos >= iLength ) 
                {
                    for(XInt i = 0; i < paramInsertCount; i++)
                    {
                        AppendString(paramInsertString, iInsertLength);
                    }
                }
                else
                {
                    T * p = (T *)Data();
                    //�ƶ�
                    T * pDest = p + iLength + iAllInsertLength; //���ĵ�ַ
                    T * pSrc = p + iLength;
                    T * pMove = p + paramPos;
                    while( pSrc >= pMove )
                    {
                        *pDest-- = *pSrc --;
                    }
                    //����
                    for(XInt j = 0; j < paramInsertCount; j++)
                    {
                        const T * pInsert = paramInsertString;
                        for(XInt i = 0; i < iInsertLength; i++)
                        {
                            *pMove ++ = *pInsert++;
                        }
                    }
                    getOriData()->Length = iLength + iAllInsertLength;                  
                }
            }
        }

        ///��ѯ�滻�Ӵ�
        /**
            @param [in] paramSubString Ҫ���滻���Ӵ�
            @param [in] paramDestString Ҫ�����ɵ��ַ���
            @param [in] paramMaxReplaceCount ����滻�Ĵ���,�����ֵС��0,���޴���
            @return XInt ʵ���滻�Ĵ���
         */
        XInt ReplaceString(const T * paramSubString, const T * paramDestString, XInt paramMaxReplaceCount = -1)
        {
            ZDH_ASSERT(paramSubString != NULL );
            ZDH_ASSERT(paramDestString != NULL );
            return ReplaceString( 0, paramSubString, string_utils::Length(paramSubString), paramDestString, string_utils::Length( paramDestString), paramMaxReplaceCount );
        }
        ///��ѯ�滻�Ӵ�
        /**
            @param [in] paramSubString Ҫ���滻���Ӵ�
            @param [in] paramDestString Ҫ�����ɵ��ַ���
            @param [in] paramMaxReplaceCount ����滻�Ĵ���,�����ֵС��0,���޴���
            @return XInt ʵ���滻�Ĵ���
         */
        XInt ReplaceString(const XStringBase<T> & paramSubString, const XStringBase<T> & paramDestString, XInt paramMaxReplaceCount = -1)
        {
            return ReplaceString( 0, paramSubString.c_str(), paramSubString.getLength(), paramDestString.c_str(), paramDestString.getLength(), paramMaxReplaceCount);
        }
        ///��ѯ�滻�Ӵ�
        /**
            @param [in] paramStartPos ��ʼ�����滻��λ��
            @param [in] paramSubString Ҫ���滻���Ӵ�
            @param [in] paramDestString Ҫ�����ɵ��ַ���
            @param [in] paramMaxReplaceCount ����滻�Ĵ���,�����ֵС��0,���޴���
            @return XInt ʵ���滻�Ĵ���
         */
        XInt ReplaceString(XInt paramStartPos, const T * paramSubString, const T * paramDestString, XInt paramMaxReplaceCount = -1)
        {
            ZDH_ASSERT(paramSubString != NULL );
            ZDH_ASSERT(paramDestString != NULL );
            return ReplaceString( paramStartPos, paramSubString, string_utils::Length(paramSubString), paramDestString, string_utils::Length( paramDestString), paramMaxReplaceCount );
        }
        ///��ѯ�滻�Ӵ�
        /**
            @param [in] paramStartPos ��ʼ�����滻��λ��
            @param [in] paramSubString Ҫ���滻���Ӵ�
            @param [in] paramDestString Ҫ�����ɵ��ַ���
            @param [in] paramMaxReplaceCount ����滻�Ĵ���,�����ֵС��0,���޴���
            @return XInt ʵ���滻�Ĵ���
         */
        XInt ReplaceString(XInt paramStartPos, const XStringBase<T> & paramSubString, const XStringBase<T> & paramDestString, XInt paramMaxReplaceCount = -1)
        {
            return ReplaceString( paramStartPos, paramSubString.c_str(), paramSubString.getLength(), paramDestString.c_str(), paramDestString.getLength(), paramMaxReplaceCount);
        }
        ///��ѯ�滻�Ӵ�
        /**
            @param [in] paramStartPos ��ʼ�����滻��λ��
            @param [in] paramSubString Ҫ���滻���Ӵ�
            @param [in] paramSubStringLength �Ӵ��ĳ���
            @param [in] paramDestString Ҫ�����ɵ��ַ���
            @param [in] paramDestStringLength Ҫ�����ɵ��ַ����ĳ���
            @param [in] paramMaxReplaceCount ����滻�Ĵ���,�����ֵС��0,���޴���
            @return XInt ʵ���滻�Ĵ���
         */
        XInt ReplaceString(XInt paramStartPos, const T * paramSubString, XInt paramSubStringLength, const T * paramDestString, XInt paramDestStringLength, XInt paramMaxReplaceCount = -1)
        {
            ZDH_ASSERT(paramSubString != NULL);
            ZDH_ASSERT(paramDestString != NULL);
            ZDH_ASSERT(paramSubStringLength == string_utils::Length(paramSubString));
            ZDH_ASSERT(paramDestStringLength == string_utils::Length(paramDestString));
            XInt iRet = 0;  //�����滻�Ĵ���
            XInt iStart = paramStartPos;    //��ʼ�滻��λ��
            XInt iBegin = 0;                //Ҫ�����ַ�������ʼλ��
            XStringBase<T> strTemp;         //��ʱ�õ��ַ���
            XInt iLocalLength = getLength();    //��ǰ�ַ����ĳ���
            strTemp.ensureCapacity( iLocalLength );
            XInt iPos = Pos(iStart, paramSubString, paramSubStringLength ); //��һ�β���
            //���ҵ��Ӵ��������滻����С������滻�������������滻����
            while(iPos >= 0 && ((paramMaxReplaceCount > 0 && iRet < paramMaxReplaceCount) || paramMaxReplaceCount < 0) )
            {
                iRet ++;
                XInt iCopyLength = iPos - iBegin; //ȷ��Ҫ���Ƶ��ַ���
                if( iCopyLength > 0 )
                {
                    strTemp.AppendString( c_str() + iBegin, iCopyLength, 1); 
                }
                if( paramDestStringLength > 0)
                {
                    strTemp.AppendString( paramDestString, paramDestStringLength, 1);
                }
                iStart = iBegin = iPos + paramSubStringLength;
                
                iPos = Pos(iStart, paramSubString, paramSubStringLength);
            }
            if( iRet > 0) //����������滻
            {
                XInt iCopyLength = iLocalLength - iBegin;
                if( iCopyLength > 0 )
                {
                    strTemp.AppendString( c_str() + iBegin, iCopyLength, 1);
                }
                Swap(strTemp);
            }
            return iRet;
        }
        ///���ַ�ת����32λ�з�������
        /**
            ����ַ�������Ч�����������׳��쳣XEConvert��
            �ַ���֧��8,10,16��������
         */
        XInt ToInt() const;
        ///���ַ�ת����32λ�з�������
        /**
            �ַ���֧��8,10,16��������
            @param [out] paramResult ���ת���Ľ��
            @return bool ת�����
                - true ��ʾת���ɹ�
                - false ��ʾת��ʧ��
         */
        bool ToInt(XInt & paramResult) const
        {
            return string_utils::TryStringToInt(c_str(),paramResult);
        }
        ///���ַ�ת����32λ�з�������
        /**
            ����ַ�������Ч���������᷵��ָ����ȱʡֵ��
            �ַ���֧��8,10,16��������
            @param [in] paramDefault ת��ʧ�ܵ�ȱʡֵ
         */
        XInt ToIntDef(XInt paramDefault) const
        {
            return string_utils::StringToIntDef(c_str(),paramDefault);
        }
        ///���ַ�ת����32λ�޷�������
        /**
            ����ַ�������Ч�����������׳��쳣XEConvert��
            �ַ���֧��8,10,16��������
         */
        XDWord ToDWord() const;
        ///���ַ�ת����32λ�޷�������
        /**
            �ַ���֧��8,10,16��������
            @param [out] paramResult ���ת���Ľ��
            @return bool ת�����
                - true ��ʾת���ɹ�
                - false ��ʾת��ʧ��
         */
        bool ToDWord(XDWord & paramResult) const
        {
            return string_utils::TryStringToDWord(c_str(), paramResult);
        }
        ///���ַ�ת����32λ�޷�������
        /**
            ����ַ�������Ч���������᷵��ָ����ȱʡֵ��
            �ַ���֧��8,10,16��������
            @param [in] paramDefault ת��ʧ�ܵ�ȱʡֵ
         */
        XDWord ToDWordDef(XDWord paramDefault) const
        {
            return string_utils::StringToDWordDef(c_str(),paramDefault);
        }
        ///���ַ�ת����64λ�з�������
        /**
            ����ַ�������Ч�����������׳��쳣XEConvert��
            �ַ���֧��8,10,16��������
         */
        XLong ToLong() const;
        ///���ַ�ת����64λ�з�������
        /**
            �ַ���֧��8,10,16��������
            @param [out] paramResult ���ת���Ľ��
            @return bool ת�����
                - true ��ʾת���ɹ�
                - false ��ʾת��ʧ��
         */
        bool ToLong(XLong & paramResult) const
        {
            return string_utils::TryStringToLong(c_str(), paramResult);
        }
        ///���ַ�ת����64λ�з�������
        /**
            ����ַ�������Ч���������᷵��ָ����ȱʡֵ��
            �ַ���֧��8,10,16��������
            @param [in] paramDefault ת��ʧ�ܵ�ȱʡֵ
         */
        XLong ToLongDef(XLong paramDefault) const
        {
            return string_utils::StringToLongDef(c_str(),paramDefault);
        }
        ///���ַ�ת����64λ�޷�������
        /**
            ����ַ�������Ч�����������׳��쳣XEConvert��
            �ַ���֧��8,10,16��������
         */
        XDDWord ToDDWord() const;
        ///���ַ�ת����64λ�޷�������
        /**
            �ַ���֧��8,10,16��������
            @param [out] paramResult ���ת���Ľ��
            @return bool ת�����
                - true ��ʾת���ɹ�
                - false ��ʾת��ʧ��
         */
        bool ToDDWord(XDWord & paramResult) const
        {
            return string_utils::TryStringToDDWord(c_str(), paramResult);
        }
        ///���ַ�ת����64λ�޷�������
        /**
            ����ַ�������Ч���������᷵��ָ����ȱʡֵ��
            �ַ���֧��8,10,16��������
            @param [in] paramDefault ת��ʧ�ܵ�ȱʡֵ
         */
        XDDWord ToDDWordDef(XDDWord paramDefault) const
        {
            return string_utils::StringToDDWordDef(c_str(), paramDefault);
        }
        ///�ȽϺ���
        /**
            @param [in] paramR �ο��Ƚϵĺ���
            @return XInt ���رȽϽ��
                - 0 ��ʾthis == paramR
                > 0 ��ʾthis > paramR
                < 0 ��ʾthis < paramR
         */
        XInt Compare(const XStringBase<T>& paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str());
        }
        ///���Դ�Сд�ȽϺ���
        /**
            @param [in] paramR �ο��Ƚϵĺ���
            @return XInt ���رȽϽ��
                - 0 ��ʾthis == paramR
                > 0 ��ʾthis > paramR
                < 0 ��ʾthis < paramR
         */
        XInt CompareIC(const XStringBase<T>& paramR) const //ignorecase
        {
            return string_utils::CompareIC(c_str(),paramR.c_str());
        }
        ///��Ϊ�մ�
        void ToEmptyString()
        {
            if( getCapacity() > 0)
            {
                *((T *)m_Data) = 0;
                getOriData()->Length = 0;
            }
        }
        ///�ַ�������
        void Swap(XStringBase<T> & paramR)
        {
            T * pTemp = m_Data;
            m_Data = paramR.m_Data;
            paramR.m_Data = pTemp;
        }
		//ɾ��ָ������ַ�
		/**
			@param [in] paramStartPos ָ��ɾ������ʼλ��
			@param [in] paramCharCount Ҫɾ�����ַ�����
			@return XInt ɾ���ַ��ĸ���
				- > 0 ɾ���ַ��ĸ���
				- -1 paramStartPos Խ��
				- -2 paramCharCount <= 0
		 */
		XInt RemoveRangeChar(XInt paramStartPos, XInt paramCharCount)
		{
			XInt iLength = getLength();
			if (paramStartPos < 0 || paramStartPos >= iLength) return -1;
			if (paramCharCount <= 0) return -2;
			XInt iLastPos = paramStartPos + paramCharCount;
			if (iLastPos >= iLength)
			{
				*(((T *)c_str()) + paramStartPos) = 0;
				getOriData()->Length = paramStartPos;
				return iLength - paramStartPos;
			}
			else
			{
				T * pDest = ((T *)c_str()) + paramStartPos;
				T * pSrc = pDest + paramCharCount;
				XInt iMoveCharCount = iLength - (paramStartPos + paramCharCount);
				for (XInt i = 0; i < iMoveCharCount; i++)
				{
					*pDest++ = *pSrc++;
				}
				*pDest = 0;
				getOriData()->Length -= paramCharCount;
				return paramCharCount;
			}
		}
        ///�ڵ�ǰ���ַ����У�ɾ��ָ�����ַ�
        /**
            @param [in] paramCh Ҫɾ�����ַ�
            @return XInt ɾ���ַ��ĸ���
         */
        XInt RemoveChar(T paramCh)
        {
            XInt iFoundCount = 0;
            if( isNotEmpty() ) 
            {
                T * pSrc = (T *)c_str();
                T * pDest = pSrc;
                XInt iLength = getLength(); 

                
                while(iLength > 0)
                {
                    T ch = *pSrc++;
                    if( ch == paramCh )
                    {
                        iFoundCount ++;
                    }
                    else
                    {
                        *pDest++ = ch;
                    }
                    iLength --;
                }
                *pDest = 0;
                getOriData()->Length = getOriData()->Length - iFoundCount;
            }
            return iFoundCount;
        }
        //һ��ɾ���Ӵ��ĺ���
        ///ɾ���Ӵ�
        /**
            �������ָ����Ҫɾ�����Ӵ���Ҫɾ���Ӵ��Ĵ���
            @param [in] paramRemoveString Ҫɾ�����Ӵ�
            @param [in] paramMaxRemoveCount Ҫɾ���Ӵ������ɾ������,-1��ʾ�����ƴ���
            @return XInt ʵ��ɾ���Ĵ���
         */
        XInt RemoveString(const XStringBase<T> & paramRemoveString, XInt paramMaxRemoveCount)
        {
            return RemoveString(0, paramRemoveString.c_str(), paramRemoveString.getLength(), paramMaxRemoveCount);
        }
        ///ɾ���Ӵ�
        /**
            �������ָ����Ҫɾ�����Ӵ���Ҫɾ���Ӵ��Ĵ���
            @param [in] paramStartPos ָ����ʼɾ����λ��
            @param [in] paramRemoveString Ҫɾ�����Ӵ�
            @param [in] paramMaxRemoveCount Ҫɾ���Ӵ������ɾ������,-1��ʾ�����ƴ���
            @return XInt ʵ��ɾ���Ĵ���
         */
        XInt RemoveString(XInt paramStartPos, const XStringBase<T> & paramRemoveString, XInt paramMaxRemoveCount)
        {
            return RemoveString(paramStartPos, paramRemoveString.c_str(), paramRemoveString.getLength(), paramMaxRemoveCount);
        }
        ///ɾ���Ӵ�
        /**
            �������ָ����Ҫɾ�����Ӵ���Ҫɾ���Ӵ��Ĵ���
            @param [in] paramRemoveString Ҫɾ�����Ӵ�
            @param [in] paramMaxRemoveCount Ҫɾ���Ӵ������ɾ������,-1��ʾ�����ƴ���
            @return XInt ʵ��ɾ���Ĵ���
         */
        XInt RemoveString(const T * paramRemoveString, XInt paramMaxRemoveCount)
        {
            return RemoveString(0, paramRemoveString, string_utils::Length(paramRemoveString), paramMaxRemoveCount);
        }
        ///ɾ���Ӵ�
        /**
            �������ָ����Ҫɾ�����Ӵ���Ҫɾ���Ӵ��Ĵ���
            @param [in] paramStartPos ָ����ʼɾ����λ��
            @param [in] paramRemoveString Ҫɾ�����Ӵ�
            @param [in] paramMaxRemoveCount Ҫɾ���Ӵ������ɾ������,-1��ʾ�����ƴ���
            @return XInt ʵ��ɾ���Ĵ���
         */
        XInt RemoveString(XInt paramStartPos, T * paramRemoveString, XInt paramMaxRemoveCount)
        {
            return RemoveString(paramStartPos, paramRemoveString, string_utils::Length(paramRemoveString), paramMaxRemoveCount);
        }
        ///ɾ���Ӵ�
        /**
            �������ָ����Ҫɾ�����Ӵ�
            @param [in] paramRemoveString Ҫɾ�����Ӵ�
            @return XInt ʵ��ɾ���Ĵ���
         */
        XInt RemoveString(const XStringBase<T> & paramRemoveString)
        {
            return RemoveString(0, paramRemoveString.c_str(), paramRemoveString.getLength(), -1);
        }
        ///ɾ���Ӵ�
        /**
            �������ָ����Ҫɾ�����Ӵ�
            @param [in] paramStartPos ָ����ʼɾ����λ��
            @param [in] paramRemoveString Ҫɾ�����Ӵ�
            @return XInt ʵ��ɾ���Ĵ���
         */
        XInt RemoveString(XInt paramStartPos, const XStringBase<T> & paramRemoveString)
        {
            return RemoveString(paramStartPos, paramRemoveString.c_str(), paramRemoveString.getLength(), -1);
        }
        ///ɾ���Ӵ�
        /**
            �������ָ����Ҫɾ�����Ӵ�
            @param [in] paramRemoveString Ҫɾ�����Ӵ�
            @return XInt ʵ��ɾ���Ĵ���
         */
        XInt RemoveString(const T * paramRemoveString)
        {
            return RemoveString(0, paramRemoveString, string_utils::Length(paramRemoveString), -1);
        }
        ///ɾ���Ӵ�
        /**
            �������ָ����Ҫɾ�����Ӵ�
            @param [in] paramStartPos ָ����ʼɾ����λ��
            @param [in] paramRemoveString Ҫɾ�����Ӵ�
            @return XInt ʵ��ɾ���Ĵ���
         */
        XInt RemoveString(XInt paramStartPos, T * paramRemoveString)
        {
            return RemoveString(paramStartPos, paramRemoveString, string_utils::Length(paramRemoveString), -1);
        }
        ///ɾ��ָ�����Ӵ�
        /**
            @param [in] paramStartPos ��ʼɾ�����±�
            @param [in] paramRemoveString Ҫɾ�����Ӵ�
            @param [in] paramRemoveStringLength Ҫɾ���Ӵ��ĳ���
            @param [in] paramMaxRemoveCount Ҫɾ���Ĵ�����-1��ʾ���޴���
            @return XInt ʵ��ɾ���Ӵ��Ĵ���
         */
        XInt RemoveString(XInt paramStartPos, const T * paramRemoveString, XInt paramRemoveStringLength, XInt paramMaxRemoveCount)
        {
            ZDH_ASSERT(paramRemoveString != NULL);
            ZDH_ASSERT(paramRemoveStringLength == string_utils::Length(paramRemoveString));
            XInt iLocalLength = getLength();
            if( paramStartPos < 0)
            {
                paramStartPos = 0;
            }
            else if( paramStartPos >= iLocalLength ) 
            {
                return 0;
            }

            XInt iFoundCount = 0;
            if( paramRemoveStringLength > 0 && iLocalLength >= paramRemoveStringLength )
            {

                XInt iPos = Pos(paramStartPos, paramRemoveString);
                XChar * pDest = (XChar *)c_str();
                const XChar * pSrc = c_str();

                while(iPos >= 0 &&( paramMaxRemoveCount < 0|| (paramMaxRemoveCount > iFoundCount) ))
                {
                    const XChar * pFound = c_str() + iPos;
                    iFoundCount ++;

                    while( pSrc < pFound )
                    {
                        *pDest++ = *pSrc++;
                    }

                    pSrc = pFound + paramRemoveStringLength;
                    iPos = Pos(iPos + paramRemoveStringLength, paramRemoveString);
                }
                if( iFoundCount > 0) 
                {
                    const XChar * pLast = c_str() + iLocalLength;

                    while(pSrc < pLast)
                    {
                        *pDest ++ = *pSrc++;
                    }

                    *pDest = 0;
                    getOriData()->Length = iLocalLength - paramRemoveStringLength * iFoundCount;
                }
            }
            return iFoundCount;
        }
        ///����ǰ�ַ���Сдת���ɴ�д
        void UpperCase() 
        {
            string_utils::UpperCase((T *)Data());
        }
        ///���ַ�����дת����Сд
        void LowerCase()
        {
            string_utils::LowerCase((T *)Data());
        }
        ///������ת��Ϊ16���ƴ�
        /**
            @param [in] paramValue Ҫת����ֵ
            @param [in] paramHexWidth 16�������ֵĿ��
            @param [in] paramHexStyle 16���Ƶ���ʽ
            @param [in] paramHexPrefix �Ƿ�Ҫ0xǰ׺
         */
        void NumberToHex(XInt paramValue,XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            NumberToHex((XDWord)paramValue, paramHexWidth, paramHexStyle, paramHexPrefix);
        }
        ///������ת��Ϊ16���ƴ�
        /**
            @param [in] paramValue Ҫת����ֵ
            @param [in] paramHexWidth 16�������ֵĿ��
            @param [in] paramHexStyle 16���Ƶ���ʽ
            @param [in] paramHexPrefix �Ƿ�Ҫ0xǰ׺
         */
        void NumberToHex(XDWord paramValue,XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            if( paramHexWidth > 8) 
            {
                ensureCapacity(paramHexWidth + 4);
            }
            else 
            {
                ensureCapacity(12);
            }
            string_utils::DWordToHex(paramValue, (T *)Data(), paramHexWidth, paramHexStyle, paramHexPrefix);
        }
        ///������ת��Ϊ16���ƴ�
        /**
            @param [in] paramValue Ҫת����ֵ
            @param [in] paramHexWidth 16�������ֵĿ��
            @param [in] paramHexStyle 16���Ƶ���ʽ
            @param [in] paramHexPrefix �Ƿ�Ҫ0xǰ׺
         */
        void NumberToHex(XLong paramValue,XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            NumberToHex((XDDWord)paramValue, paramHexWidth, paramHexStyle, paramHexPrefix);
        }
        ///������ת��Ϊ16���ƴ�
        /**
            @param [in] paramValue Ҫת����ֵ
            @param [in] paramHexWidth 16�������ֵĿ��
            @param [in] paramHexStyle 16���Ƶ���ʽ
            @param [in] paramHexPrefix �Ƿ�Ҫ0xǰ׺
         */
        void NumberToHex(XDDWord paramValue,XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            if( paramHexWidth > 16) 
            {
                ensureCapacity(paramHexWidth + 4);
            }
            else 
            {
                ensureCapacity(20);
            }
            string_utils::DDWordToHex(paramValue, (T *)Data(), paramHexWidth, paramHexStyle, paramHexPrefix);
        }
    protected:
        ///ȡ���Է��ʵ��ַ���ָ��
        T * getDataPtr()
        {
            return m_Data;
        }
        ///��չ����
        /**
            ע��:�������������������ȫ���
            @param [in] paramMinimumCapacity ָ������С����������������ַ�����
         */
        void expandCapacity(XInt paramMinimumCapacity);
        ///ȡʵ���ַ���ָ��
        /**
            ע��:���ﲻ����Խ����,
         */
        const SStringStruct * getOriData() const  { return ((const SStringStruct *)m_Data) - 1; }
        ///ȡʵ���ַ���ָ��
        /**
            ע��:���ﲻ����Խ����
         */
        SStringStruct * getOriData() {  return ((SStringStruct *)m_Data) - 1;}
        ///�����ַ���
        /**
            @param [in] paramSrc Դ�ַ�����ַ
            @param [out] paramDest Ŀ�괮��ַ
            @param [in] paramCopyCharNumber Ҫ���Ƶ��ַ�����
         */
        static void CopyData(const T * paramSrc, T * paramDest, XInt paramCopyCharNumber)
        {
			const T * pS = paramSrc;
			T * pD = paramDest;
			for (XInt i = paramCopyCharNumber; i > 0; i--)
			{
				*pD++ = *pS++;
			}
			*pD = 0;
        }

        ///�����Ӵ��Ƿ����
        /**
            @param [in] paramString ���ҵ��ַ���
            @param [in] paramSubString �����ҵ��Ӵ�
            @return T * ���ؽ��
                - NULL ��ʾδ�ҵ����Ӵ�
                - not NULL ��ʾ�ҵ��˸��Ӵ��������ظ��Ӵ��ĵ�ַ
         */
        static const T * FindString(const T * paramString, const T * paramSubString)
        {
            if( isNULL(paramSubString) ) return paramString;
            if( isNULL(paramString) ) return NULL;
            const T * s = paramString;
            T c = *s;
            T c2 = *paramSubString;
            while( c )
            {
                if( c == c2 ) //����ҵ��˵�һ���ַ�����ô��ʼ���Ӵ�
                {
                    const T * s1 = s;
                    const T * s2 = paramSubString;
                    T t1 = c;
                    T t2 = c2;
                    while( t1 && t2 && (!(t2 - t1)))
                    {
                        t1 = *++s1;
                        t2 = *++s2;
                    }
                    if( !t2 ) return s;
                }
                c = *++s;
            }
            return NULL;
        }
    private:
        T * m_Data;         ///<����ָ��
    };
	using std::string;
    ///���ַ��ַ���
    class XAnsiString : public XStringBase<XChar>
    {
    public:
        typedef XStringBase<XChar> Inherited;
    public:
        ///Ĭ�Ϲ��캯��
        XAnsiString(){}
        ///ָ����ʼֵ�Ĺ��캯��
        XAnsiString(const XChar * paramString)
            :Inherited(paramString)
        {}
        ///Ĭ�Ͽ������캯��
        XAnsiString(const XAnsiString & paramString)
            :Inherited(paramString)
        {}
        XAnsiString(const XStringBase<XWideChar> & paramWideString)
        {
            SetStringByWideString(paramWideString);
        }
        ///ָ����ʼ�ַ����캯��
        XAnsiString(XChar paramChar)
            :Inherited(paramChar)
        {}
        ///ָ��8λ�޷����������캯��
        XAnsiString(const XByte & paramByte)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramByte,TempBuffer));
        }
        ///ָ��16λ�з����������캯��
        XAnsiString(const XShort & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///ָ��16λ�޷����������캯��
        XAnsiString(const XWord & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///ָ��32λ�з����������캯��
        XAnsiString(const XInt & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///ָ��32λ�޷����������캯��
        XAnsiString(const XDWord & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::DWordToStr(paramNumber,TempBuffer));
        }
        ///ָ��64λ�з����������캯��
        XAnsiString(const XLong & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::LongToStr(paramNumber,TempBuffer));
        }
        ///ָ��64λ�޷����������캯��
        XAnsiString(const XDDWord & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::DDWordToStr(paramNumber,TempBuffer));
        }
        XAnsiString & operator = (const XChar * paramValue)
        {
            Assign(paramValue);
            return *this;
        }
        XAnsiString & operator = (const XStringBase<XWideChar> & paramString)
        {
            SetStringByWideString(paramString);
            return *this;
        }
        ///ָ���ַ���ֵ����
        XAnsiString & operator = (const XChar & paramValue)
        {
            Assign(paramValue);
            return *this;
        }

		operator string()
		{
			return string(c_str(), std::size_t(getLength()));
		}
        ///ָ��8λ�޷���������ֵ����
        XAnsiString & operator = (const XByte & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��16λ�з���������ֵ����
        XAnsiString & operator = (const XShort & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��16λ�޷���������ֵ����
        XAnsiString & operator = (const XWord & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��32λ�з���������ֵ����
        XAnsiString & operator = (const XInt & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��32λ�޷���������ֵ����
        XAnsiString & operator = (const XDWord & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��64λ�з���������ֵ����
        XAnsiString & operator = (const XLong & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��64λ�޷���������ֵ����
        XAnsiString & operator = (const XDDWord & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ���ַ�����ֵ����
        XAnsiString & operator = (const XAnsiString & paramValue)
        {
            if( &paramValue != this)
            {
                Assign(paramValue);
            }
            return *this;
        }
        ///׷��һ���ַ���
        XAnsiString & operator += (const XChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }

        ///׷��һ���ַ�
        XAnsiString & operator += (const XChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///׷��8λ�޷�������
        XAnsiString & operator += (const XByte & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�з�������
        XAnsiString & operator += (const XShort & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�޷�������
        XAnsiString & operator += (const XWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��32λ�з�������
        XAnsiString & operator += (const XInt & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��32λ�޷�������
        XAnsiString & operator += (const XDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�з�������
        XAnsiString & operator += (const XLong & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�޷�������
        XAnsiString & operator += (const XDDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��һ���ַ���
        XAnsiString & operator += (const XAnsiString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///׷��һ���ַ���
        XAnsiString & operator << (const XChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///׷��һ���ַ�
        XAnsiString & operator << (const XChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///׷��8λ�޷�������
        XAnsiString & operator << (const XByte & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�з�������
        XAnsiString & operator << (const XShort & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�޷�������
        XAnsiString & operator << (const XWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��32λ�з�������
        XAnsiString & operator << (const XInt & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��32λ�޷�������
        XAnsiString & operator << (const XDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�з�������
        XAnsiString & operator << (const XLong & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�޷�������
        XAnsiString & operator << (const XDDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��һ���ַ���
        XAnsiString & operator << (const XAnsiString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///׷��һ���ַ���
        XAnsiString & operator , (const XChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///׷��һ���ַ�
        XAnsiString & operator , (const XChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///׷��8λ�޷�������
        XAnsiString & operator , (const XByte & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�з�������
        XAnsiString & operator , (const XShort & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�޷�������
        XAnsiString & operator , (const XWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��32λ�з�������
        XAnsiString & operator , (const XInt & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��32λ�޷�������
        XAnsiString & operator , (const XDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�з�������
        XAnsiString & operator , (const XLong & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�޷�������
        XAnsiString & operator , (const XDDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��һ���ַ���
        XAnsiString & operator , (const XAnsiString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///����[]�����
        XChar operator[](XInt paramIndex) const
        {
            return at(paramIndex);
        }
        ///����[]�����
        XChar & operator[](XInt paramIndex)
        {
            return at(paramIndex);
        }
        ///����һ���ַ�
        XAnsiString operator + (const XChar & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����8λ�޷�����
        XAnsiString operator + (const XByte & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����16λ�з�����
        XAnsiString operator + (const XShort & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����16λ�޷�����
        XAnsiString operator + (const XWord & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����32λ�з�����
        XAnsiString operator + (const XInt & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����32λ�޷�����
        XAnsiString operator + (const XDWord & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����64λ�з�����
        XAnsiString operator + (const XLong & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����64λ�޷�����
        XAnsiString operator + (const XDDWord & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����һ���ַ���
        XAnsiString operator + (const XAnsiString & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����һ���ַ���
        XAnsiString operator + (const XChar * paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }

        //һ��ȽϺ���
        bool operator == (const XAnsiString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) == 0;
        }
        bool operator != (const XAnsiString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) != 0;
        }
        bool operator >= (const XAnsiString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) >= 0;
        }
        bool operator <= (const XAnsiString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) <= 0;
        }
        bool operator > (const XAnsiString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) > 0;
        }
        bool operator < (const XAnsiString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) < 0;
        }

        //һ��ȽϺ���
        bool operator == (const XChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) == 0;
        }
        bool operator != (const XChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) != 0;
        }
        bool operator >= (const XChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) >= 0;
        }
        bool operator <= (const XChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) <= 0;
        }
        bool operator > (const XChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) > 0;
        }
        bool operator < (const XChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) < 0;
        }
        ///ָ����ʽ�������ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XAnsiString & ���ص�ǰ�ַ���
         */
        XAnsiString& sprintf(const XChar* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            vprintf(paramFormat, argptr);
            va_end(argptr);
            return *this;
        }
        ///ָ����ʽ�������ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XAnsiString & ���ص�ǰ�ַ���
         */
        XAnsiString& snprintf(XInt paramSize, const XChar* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            vnprintf(paramSize, paramFormat, argptr);
            va_end(argptr);
            return *this;
        }
        ///ָ����ʽ�������ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        XInt printf(const XChar* paramFormat, ...) // Returns formatted length
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            XInt iRet = vprintf(paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }
        XInt nprintf(XInt paramSize, const XChar* paramFormat, ...) // Returns formatted length
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            XInt iRet = vnprintf(paramSize, paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }

        ///ָ����ʽ�������ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        XInt vprintf(const XChar* paramFormat, va_list paramList) // Returns formatted length
        {
#if defined(OS_LINUX)
            va_list ap;
            va_copy(ap, paramList);
#endif
            XInt iLength = string_utils::zdh_vscprintf(paramFormat, paramList);
            if( iLength > 0)
            {
                ensureCapacity(iLength);
#if defined(OS_LINUX)
                string_utils::zdh_vsprintf((XChar *)Data(), paramFormat, ap);
                va_end(ap);
#else
                string_utils::zdh_vsprintf((XChar *)Data(), paramFormat, paramList);
#endif
                getOriData()->Length = iLength;
            }
            return iLength;
        }

        XInt vnprintf(XInt paramSize, const XChar * paramFormat, va_list paramList)
        {
            if (paramSize <= 1)
            {
                ToEmptyString();
                return 0;
            }
            else
            {
                ensureCapacity(paramSize - 1);
                XInt iLength = string_utils::zdh_vsnprintf((XChar *)Data(), paramSize, paramFormat, paramList);
                if (iLength < 0)
                {
                    ToEmptyString();
                    iLength = 0;
                }
                else 
                {
                    getOriData()->Length = iLength;
                }
                return iLength;
            }
        }

        ///ָ�����Ӹ�ʽ�����ɵ��ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XAnsiString & ���ص�ǰ�ַ���
         */
        XAnsiString& cat_sprintf(const char* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            cat_vprintf(paramFormat, argptr);
            va_end(argptr);
            return *this;
        }
        XAnsiString& cat_snprintf(XInt paramSize, const char* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            cat_vnprintf(paramSize, paramFormat, argptr);
            va_end(argptr);
            return *this;
        }
        ///ָ�����Ӹ�ʽ�����ɵ��ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        XInt cat_printf(const char* paramFormat, ...) // Returns formatted length
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            XInt iRet = cat_vprintf(paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }
        XInt cat_nprintf(XInt paramSize, const char * paramFormat, ...)
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            XInt iRet = cat_vnprintf(paramSize, paramFormat, argptr);
            va_end(argptr);
            return iRet;
        }
        ///ָ�����Ӹ�ʽ�����ɵ��ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        XInt cat_vprintf(const char* paramFormat, va_list paramList) // Returns formatted length
        {
#if defined(OS_LINUX)
            va_list ap;
            va_copy(ap, paramList);
#endif
            XInt iLength = string_utils::zdh_vscprintf(paramFormat, paramList);
            if( iLength > 0)
            {
                XInt iLocalLength = getLength();
                ensureCapacity(iLength + iLocalLength);
#if defined(OS_LINUX)
                string_utils::zdh_vsprintf(((XChar *)Data()) + iLocalLength, paramFormat, ap);
                va_end(ap);
#else
                string_utils::zdh_vsprintf(((XChar *)Data()) + iLocalLength, paramFormat, paramList);
#endif
                getOriData()->Length = iLength + iLocalLength;
            }
            return iLength;
        }


        ///ָ�����Ӹ�ʽ�����ɵ��ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        XInt cat_vnprintf(XInt paramSize, const char* paramFormat, va_list paramList) // Returns formatted length
        {
            if (paramSize <= 1)
            {
                return 0;
            }
            else
            {
                XInt iLocalLength = getLength();
                ensureCapacity(paramSize - 1 + iLocalLength);
                XInt iLength = string_utils::zdh_vsnprintf(((XChar *)Data()) + iLocalLength, paramSize, paramFormat, paramList);
                if (iLength <0)
                {
                    *((XChar *)Data() + iLocalLength) = 0;
                    return 0;
                }
                else
                {
                    getOriData()->Length = iLength + iLocalLength;
                    return iLength;
                }
            }
        }

        ///����ַ����������߿ո��ַ�
        XAnsiString Trim() const
        {
            XAnsiString strRet(*this);
            if( strRet.isNotEmpty() )
            {
                strRet.getOriData()->Length = string_utils::Trim((XChar *)strRet.Data(),strRet.getLength());
            }
            return strRet;
        }
        XAnsiString & Trim(XAnsiString & paramStore) const
        {
            paramStore = *this;
            if( paramStore.isNotEmpty() )
            {
                paramStore.getOriData()->Length = string_utils::Trim((XChar *)paramStore.Data(),paramStore.getLength());
            }
            return paramStore;
        }
        ///����ַ�����߿ո��ַ���
        XAnsiString TrimLeft() const
        {
            XAnsiString strRet(*this);
            if( strRet.isNotEmpty() )
            {
                strRet.getOriData()->Length = string_utils::TrimLeft((XChar *)strRet.Data(),strRet.getLength());
            }
            return strRet;
        }
        XAnsiString & TrimLeft(XAnsiString & paramStore) const
        {
            paramStore = *this;
            if( paramStore.isNotEmpty() )
            {
                paramStore.getOriData()->Length = string_utils::TrimLeft((XChar *)paramStore.Data(),paramStore.getLength());
            }
            return paramStore;
        }
        ///����ַ����ұ߿ո��ַ���
        XAnsiString TrimRight() const
        {
            XAnsiString strRet(*this);
            if( strRet.isNotEmpty() )
            {
                strRet.getOriData()->Length = string_utils::TrimRight((XChar *)strRet.Data(),strRet.getLength());
            }
            return strRet;
        }
        XAnsiString & TrimRight(XAnsiString & paramStore) const
        {
            paramStore = *this;
            if( paramStore.isNotEmpty() )
            {
                paramStore.getOriData()->Length = string_utils::TrimRight((XChar *)paramStore.Data(),paramStore.getLength());
            }
            return paramStore;
        }
        ///ȡָ�����Ӵ�
        XAnsiString & SubString(const XInt paramStartPos, const XInt paramSubLength, XAnsiString & paramStore ) const
        {
            XAnsiString & strRet = paramStore;
            XInt iLength = getLength();
            if( paramStartPos >= 0 && paramSubLength > 0 && paramStartPos < iLength )
            {
                XInt iMaxLength = iLength - paramStartPos;
                if( iMaxLength > paramSubLength) iMaxLength = paramSubLength;
                strRet.ensureCapacity( iMaxLength );
                const XChar * pSrc = c_str() + paramStartPos;
                while( iMaxLength > 0)
                {
                    strRet += *pSrc ++;
                    iMaxLength --;
                }
            }
            return paramStore;
        }
        ///ȡָ�����Ӵ�
        /**
            @param [in] paramStartPos ָ����λ��
            @param [in] paramSubLength �Ӵ��ĳ���
            @return XAnsiString ȡ�õ��Ӵ�
         */
        XAnsiString SubString(const XInt paramStartPos, const XInt paramSubLength) const
        {
            XAnsiString strRet;
            SubString(paramStartPos,paramSubLength,strRet);
            return strRet;
        }
        XAnsiString substr(XInt paramStartPos, XInt paramEndPos)
        {
            return SubString(paramStartPos, paramEndPos - paramStartPos);
        }
        ///ȡ�մ�
        static const XAnsiString & EmptyString() 
        {
            static XAnsiString sEmptyString;
            return sEmptyString;
        }
        ///�����ַ������ַ�����ת��Ϊ���ֽ��ַ���
        void SetStringByWideString(const XStringBase<XWideChar> & paramString)
        {
            XInt iCharCount = string_utils::ChineseUnicodeToMultByte(NULL, paramString.c_str(), 0);
            ensureCapacity(iCharCount);
            XChar * pData = getDataPtr();
            string_utils::ChineseUnicodeToMultByte(pData, paramString.c_str(), getOriData()->Capacity - 1);         
            pData[iCharCount] = 0;
        }
        XAnsiString& assign(const XChar * str, XInt len)
        {
            Assign(str,len);
            return *this;
        }
        XAnsiString& append(const XChar* str, XInt len)
        {
            AppendString(str,len);
            return *this;
        }
        void swap(XAnsiString & other)
        {
            Swap(other);
        }
    };


    //---------------------------------------------------------------------------------------------------
    #if defined(OS_WINDOWS)
    ///˫�ַ��ַ���
    class XWideString : public XStringBase<XWideChar>
    {
    public:
        typedef XStringBase<XWideChar> Inherited;
    public:
        ///Ĭ�Ϲ��캯��
        XWideString(){}
        ///ָ����ʼֵ�Ĺ��캯��
        XWideString(const XWideChar * paramString)
            :Inherited(paramString)
        {}
        ///Ĭ�Ͽ������캯��
        XWideString(const XWideString & paramString)
            :Inherited(paramString)
        {}
        XWideString(const XStringBase<XChar> & paramString)
        {
            SetStringByWideString(paramString);
        }
        ///ָ����ʼ�ַ����캯��
        XWideString(XWideChar paramChar)
            :Inherited(paramChar)
        {}
        ///ָ��8λ�޷����������캯��
        XWideString(const XByte & paramByte)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramByte,TempBuffer));
        }
        ///ָ��16λ�з����������캯��
        XWideString(const XShort & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///ָ��16λ�޷����������캯��
        XWideString(const XWord & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///ָ��32λ�з����������캯��
        XWideString(const XInt & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///ָ��32λ�޷����������캯��
        XWideString(const XDWord & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::DWordToStr(paramNumber,TempBuffer));
        }
        ///ָ��64λ�з����������캯��
        XWideString(const XLong & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::LongToStr(paramNumber,TempBuffer));
        }
        ///ָ��64λ�޷����������캯��
        XWideString(const XDDWord & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::DDWordToStr(paramNumber,TempBuffer));
        }
        XWideString & operator = (const XWideChar * paramValue)
        {
            Assign(paramValue);
            return *this;
        }
        XWideString & operator = (const XStringBase<XChar> & paramString)
        {
            SetStringByWideString( paramString );
            return *this;
        }

        ///ָ���ַ���ֵ����
        XWideString & operator = (const XWideChar & paramValue)
        {
            Assign(paramValue);
            return *this;
        }
        ///ָ��8λ�޷���������ֵ����
        XWideString & operator = (const XByte & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��16λ�з���������ֵ����
        XWideString & operator = (const XShort & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��16λ�޷���������ֵ����
        //XWideString & operator = (const XWord & paramValue)
        //{
        //    XWideChar TempBuffer[32];
        //    Assign(string_utils::IntToStr(paramValue,TempBuffer));
        //    return *this;
        //}
        ///ָ��32λ�з���������ֵ����
        XWideString & operator = (const XInt & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��32λ�޷���������ֵ����
        XWideString & operator = (const XDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��64λ�з���������ֵ����
        XWideString & operator = (const XLong & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ��64λ�޷���������ֵ����
        XWideString & operator = (const XDDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///ָ���ַ�����ֵ����
        XWideString & operator = (const XWideString & paramValue)
        {
            if( &paramValue != this)
            {
                Assign(paramValue);
            }
            return *this;
        }
        ///׷��һ���ַ���
        XWideString & operator += (const XWideChar * paramValue)
        {
            AppendString(paramValue);//,::strlen(paramValue));
            return *this;
        }
        ///׷��һ���ַ�
        XWideString & operator += (const XWideChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///׷��8λ�޷�������
        XWideString & operator += (const XByte & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�з�������
        XWideString & operator += (const XShort & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�޷�������
        //XWideString & operator += (const XWord & paramValue)
        //{
        //    XWideChar TempBuffer[32];
        //    AppendString(string_utils::IntToStr(paramValue,TempBuffer));
        //    return *this;
        //}
        ///׷��32λ�з�������
        XWideString & operator += (const XInt & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��32λ�޷�������
        XWideString & operator += (const XDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�з�������
        XWideString & operator += (const XLong & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�޷�������
        XWideString & operator += (const XDDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��һ���ַ���
        XWideString & operator += (const XWideString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///׷��һ���ַ���
        XWideString & operator << (const XWideChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///׷��һ���ַ�
        XWideString & operator << (const XWideChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///׷��8λ�޷�������
        XWideString & operator << (const XByte & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�з�������
        XWideString & operator << (const XShort & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�޷�������
        //XWideString & operator << (const XWord & paramValue)
        //{
        //    XWideChar TempBuffer[32];
        //    AppendString(string_utils::IntToStr(paramValue,TempBuffer));
        //    return *this;
        //}
        ///׷��32λ�з�������
        XWideString & operator << (const XInt & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��32λ�޷�������
        XWideString & operator << (const XDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�з�������
        XWideString & operator << (const XLong & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�޷�������
        XWideString & operator << (const XDDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��һ���ַ���
        XWideString & operator << (const XWideString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///׷��һ���ַ���
        XWideString & operator , (const XWideChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///׷��һ���ַ�
        XWideString & operator , (const XWideChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///׷��8λ�޷�������
        XWideString & operator , (const XByte & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�з�������
        XWideString & operator , (const XShort & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��16λ�޷�������
        //XWideString & operator , (const XWord & paramValue)
        //{
        //    XWideChar TempBuffer[32];
        //    AppendString(string_utils::IntToStr(paramValue,TempBuffer));
        //    return *this;
        //}
        ///׷��32λ�з�������
        XWideString & operator , (const XInt & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��32λ�޷�������
        XWideString & operator , (const XDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�з�������
        XWideString & operator , (const XLong & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��64λ�޷�������
        XWideString & operator , (const XDDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///׷��һ���ַ���
        XWideString & operator , (const XWideString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///����[]�����
        XWideChar operator[](XInt paramIndex) const
        {
            return at(paramIndex);
        }
        ///����[]�����
        XWideChar & operator[](XInt paramIndex)
        {
            return at(paramIndex);
        }
        ///����һ���ַ�
        XWideString operator + (const XWideChar & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����8λ�޷�����
        XWideString operator + (const XByte & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����16λ�з�����
        XWideString operator + (const XShort & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����16λ�޷�����
        //XWideString operator + (const XWord & paramValue) const
        //{
        //    XWideString strRet(*this);
        //    strRet += paramValue;
        //    return strRet;
        //}
        ///����32λ�з�����
        XWideString operator + (const XInt & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����32λ�޷�����
        XWideString operator + (const XDWord & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����64λ�з�����
        XWideString operator + (const XLong & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����64λ�޷�����
        XWideString operator + (const XDDWord & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����һ���ַ���
        XWideString operator + (const XWideString & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///����һ���ַ���
        XWideString operator + (const XWideChar * paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }

        //һ��ȽϺ���
        bool operator == (const XWideString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) == 0;
        }
        bool operator != (const XWideString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) != 0;
        }
        bool operator >= (const XWideString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) >= 0;
        }
        bool operator <= (const XWideString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) <= 0;
        }
        bool operator > (const XWideString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) > 0;
        }
        bool operator < (const XWideString & paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str()) < 0;
        }

        //һ��ȽϺ���
        bool operator == (const XWideChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) == 0;
        }
        bool operator != (const XWideChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) != 0;
        }
        bool operator >= (const XWideChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) >= 0;
        }
        bool operator <= (const XWideChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) <= 0;
        }
        bool operator > (const XWideChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) > 0;
        }
        bool operator < (const XWideChar * paramR) const
        {
            return string_utils::Compare(c_str(),paramR) < 0;
        }
        ///ָ����ʽ�������ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XWideString & ���ص�ǰ�ַ���
         */
        XWideString& sprintf(const XWideChar* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            vprintf(paramFormat,argptr);
            return *this;
        }
        ///ָ����ʽ�������ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        XInt printf(const XWideChar* paramFormat, ...) // Returns formatted length
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            return vprintf(paramFormat,argptr);
        }
        ///ָ����ʽ�������ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        XInt vprintf(const XWideChar* paramFormat, va_list paramList) // Returns formatted length
        {
            XInt iLength = string_utils::zdh_vscprintf(paramFormat, paramList);
            if( iLength > 0)
            {
                ensureCapacity(iLength);
                string_utils::zdh_vsnprintf((XWideChar *)Data(), iLength + 1, paramFormat, paramList);
                getOriData()->Length = iLength;
            }
            return iLength;
        }
        ///ָ�����Ӹ�ʽ�����ɵ��ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XWideString & ���ص�ǰ�ַ���
         */
        XWideString& cat_sprintf(const XWideChar* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            cat_vprintf(paramFormat, argptr);
            return *this;
        }
        ///ָ�����Ӹ�ʽ�����ɵ��ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        XInt cat_printf(const XWideChar* paramFormat, ...) // Returns formatted length
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            return cat_vprintf(paramFormat, argptr);
        }
        ///ָ�����Ӹ�ʽ�����ɵ��ַ���
        /**
            @param [in] ��ʽ����,�ο���׼C�ĸ�ʽ����
            @return XInt ���ظ�ʽ���ַ����ĳ���
         */
        XInt cat_vprintf(const XWideChar* paramFormat, va_list paramList) // Returns formatted length
        {
            XInt iLength = string_utils::zdh_vscprintf(paramFormat, paramList);
            if( iLength > 0)
            {
                XInt iLocalLength = getLength();
                ensureCapacity(iLength + iLocalLength);
                string_utils::zdh_vsprintf(((XWideChar *)Data()) + iLocalLength, paramFormat, paramList);
                getOriData()->Length = iLength + iLocalLength;
            }
            return iLength;
        }


        ///����ַ����������߿ո��ַ�
        XWideString Trim() const
        {
            XWideString strRet(*this);
            if( strRet.isNotEmpty() )
            {
                strRet.getOriData()->Length = string_utils::Trim((XWideChar *)strRet.Data(),strRet.getLength());
            }
            return strRet;
        }
        XWideString & Trim(XWideString & paramStore) const
        {
            paramStore = *this;
            if( paramStore.isNotEmpty() )
            {
                paramStore.getOriData()->Length = string_utils::Trim((XWideChar *)paramStore.Data(),paramStore.getLength());
            }
            return paramStore;
        }
        ///����ַ�����߿ո��ַ���
        XWideString TrimLeft() const
        {
            XWideString strRet(*this);
            if( strRet.isNotEmpty() )
            {
                strRet.getOriData()->Length = string_utils::TrimLeft((XWideChar *)strRet.Data(),strRet.getLength());
            }
            return strRet;
        }
        XWideString & TrimLeft(XWideString & paramStore) const
        {
            paramStore = *this;
            if( paramStore.isNotEmpty() )
            {
                paramStore.getOriData()->Length = string_utils::TrimLeft((XWideChar *)paramStore.Data(),paramStore.getLength());
            }
            return paramStore;
        }
        ///����ַ����ұ߿ո��ַ���
        XWideString TrimRight() const
        {
            XWideString strRet(*this);
            if( strRet.isNotEmpty() )
            {
                strRet.getOriData()->Length = string_utils::TrimRight((XWideChar *)strRet.Data(),strRet.getLength());
            }
            return strRet;
        }
        XWideString & TrimRight(XWideString & paramStore) const
        {
            paramStore = *this;
            if( paramStore.isNotEmpty() )
            {
                paramStore.getOriData()->Length = string_utils::TrimRight((XWideChar *)paramStore.Data(),paramStore.getLength());
            }
            return paramStore;
        }
        ///ȡָ�����Ӵ�
        XWideString & SubString(const XInt paramStartPos, const XInt paramSubLength, XWideString & paramStore ) const
        {
            XWideString & strRet = paramStore;
            XInt iLength = getLength();
            if( paramStartPos >= 0 && paramSubLength > 0 && paramStartPos < iLength )
            {
                XInt iMaxLength = iLength - paramStartPos;
                if( iMaxLength > paramSubLength) iMaxLength = paramSubLength;
                strRet.ensureCapacity( iMaxLength );
                const XWideChar * pSrc = c_str() + paramStartPos;
                while( iMaxLength > 0)
                {
                    strRet += *pSrc ++;
                    iMaxLength --;
                }
            }
            return paramStore;
        }
        ///ȡָ�����Ӵ�
        /**
            @param [in] paramStartPos ָ����λ��
            @param [in] paramSubLength �Ӵ��ĳ���
            @return XWideString ȡ�õ��Ӵ�
         */
        XWideString SubString(const XInt paramStartPos, const XInt paramSubLength) const
        {
            XWideString strRet;
            SubString(paramStartPos,paramSubLength,strRet);
            return strRet;
        }
        XWideString substr(XInt paramStartPos, XInt paramEndPos)
        {
            return SubString(paramStartPos, paramEndPos - paramStartPos);
        }
        ///ȡ�մ�
        static const XWideString & EmptyString() 
        {
            static XWideString sEmptyString;
            return sEmptyString;
        }
        ///�����ַ������ַ�����ת��Ϊ���ֽ��ַ���
        void SetStringByWideString(const XStringBase<XChar> & paramString)
        {
            XInt iCharCount = string_utils::ChineseMultByteToUnicode(NULL, paramString.c_str(), 0);
            ensureCapacity(iCharCount);
            XWideChar * pData = getDataPtr();
            string_utils::ChineseMultByteToUnicode(pData, paramString.c_str(), getOriData()->Capacity - 1);         
            pData[iCharCount] = 0;
        }
        XWideString& assign(const XWideChar * str, XInt len)
        {
            Assign(str,len);
            return *this;
        }
        XWideString& append(const XWideChar* str, XInt len)
        {
            AppendString(str,len);
            return *this;
        }
        void swap(XWideString & other)
        {
            Swap(other);
        }
    };
#endif
    //---------------------------------------------------------------------------------------------------
    ///�쳣�����
    class EException
    {
    public:
        ///Ĭ�Ϲ��캯��
        EException()
            :m_HelpContext(0)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        EException(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :m_Message(paramMessage),
             m_HelpContext(paramHelpContext)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        EException(const XChar* paramMessage, XInt paramHelpContext = 0)
            :m_Message(paramMessage),
            m_HelpContext(paramHelpContext)
        {}
        ///��������
        virtual ~EException()
        {}
        ///ȡ�쳣��Ϣ
        const XAnsiString getMessage() const
        {
            return m_Message;
        }
        ///�����쳣��Ϣ
        void setMessage(const XChar * paramMessage)     
        {
            m_Message = paramMessage;
        }
        ///�����쳣��Ϣ
        void setMessage(const XAnsiString & paramMessage)
        {
            m_Message = paramMessage;
        }
        ///ȡ������ϢID
        XInt getHelpContext() const
        {
            return m_HelpContext;
        }
        ///���ð�����ϢID
        void setHelpContext(XInt paramHelpContext)
        {
            m_HelpContext = paramHelpContext;
        }
        ///ת�����ַ���ָ��
        operator const XChar *() const
        {
            return m_Message.c_str();
        }
    private:
        XAnsiString m_Message;  ///<�쳣��Ϣ
        XInt m_HelpContext;     ///<������ϢID
    };

    #define MESSAGE_OUT_OF_MEMORY "out of memory"
    #define MESSAGE_NOT_EXISTS "not exists object!"
    #define MESSAGE_IS_ZERO "is zero"
    #define MESSAGE_LESS_THAN_ZERO "less than zero"
    #define MESSAGE_CONVERT_FAIL "Type convert fail"
    #define MESSAGE_GREATER_THAN_ZERO "greater than zero"
    #define MESSAGE_OUT_OF_RANGE "out of range:index=%d,length=%d"

    ///�ڴ�����쳣
    class XEOutOfMemory : public EException
    {
    public:
        ///Ĭ�Ϲ��캯��
        XEOutOfMemory()
            :EException(MESSAGE_OUT_OF_MEMORY)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        XEOutOfMemory(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        XEOutOfMemory(const XChar* paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///��������
        ~XEOutOfMemory()
        {
        }
    };
    //---------------------------------------------------------------------
    class XEConvert : public EException
    {
    public:
        ///Ĭ�Ϲ��캯��
        XEConvert()
            :EException(MESSAGE_CONVERT_FAIL)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        XEConvert(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///ָ���쳣��Ϣ�Ĺ��캯��
        /**
            @param [in] paramMessage �쳣��Ϣ
            @param [in] paramHelpContext ������ϢID
         */
        XEConvert(const XChar* paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///��������
        ~XEConvert()
        {
        }
    };


    ///����Խ���쳣
    class XEOutOfRange : public EException
    {
    public:
        ///����Խ���쳣���캯��
        /**
            @param [in] paramIndex Խ����±�ֵ
            @param [in] aLength ��Խ�������ĳ���
        */
        XEOutOfRange(XInt paramIndex = 0,XInt aLength = 0)
            :m_Index(paramIndex),m_Length(aLength)
        {
            MakeMsg();
        }
        ///��������
        ~XEOutOfRange(){}
        ///����Խ����Ϣ
        /**
            @param [in] paramIndex Խ����±�ֵ
            @param [in] aLength ��Խ�������ĳ���
        */
        void setInfo(XInt paramIndex,XInt aLength)
        {
            m_Index = paramIndex;
            m_Length = aLength;
            MakeMsg();
        }
        ///ȡԽ����±�ֵ
        /**
            @return ����Խ����±�ֵ
         */
        XInt getIndex() const { return m_Index; }
        ///ȡ��Խ�������ĳ���
        /**
            @return ���ر�Խ��ĳ���
         */
        XInt getLength() const { return m_Length; }
    protected:
        ///�����쳣��Ϣ
        void MakeMsg()
        {
            XAnsiString strMsg;
            strMsg.printf(MESSAGE_OUT_OF_RANGE,m_Index,m_Length);
            setMessage(strMsg);
        }
    private:
        XInt m_Index;  ///<Խ����±�
        XInt m_Length; ///<��Խ���������±�
    };
    ///ֵΪ���쳣��
    class XEIsZero : public EException
    {
    public:
        XEIsZero()
            :EException(MESSAGE_IS_ZERO)
        {}
    };
    ///ֵС�����쳣��
    class XELessThanZero : public EException
    {
    public:
        XELessThanZero()
            :EException(MESSAGE_LESS_THAN_ZERO)
        {}
    };
    ///ֵ�������쳣��
    class XEGreatherThanZero : public EException
    {
    public:
        XEGreatherThanZero()
            :EException(MESSAGE_GREATER_THAN_ZERO)
        {}
    };
    ///�������쳣��
    class XENotExists : public EException
    {
    public:
        XENotExists()
            :EException(MESSAGE_NOT_EXISTS)
        {}
    };
    //---------------------------------------------------------------------
    ///ȡָ���±���ַ�
    template<class T>
    T XStringBase<T>::at(XInt paramIndex) const ZDH_THROW(XEOutOfRange)
        ZDH_THROW(XEOutOfRange)
    {
        if( !CheckIndex(paramIndex) ) 
        {
            throw XEOutOfRange(paramIndex,getLength());
        }
        return *(((T *)m_Data) + paramIndex);
    }
    //---------------------------------------------------------------------
    ///ȡָ���±���ַ�����
    template<class T>
    T & XStringBase<T>::at(XInt paramIndex)
        ZDH_THROW(XEOutOfRange)
    {
        if( !CheckIndex(paramIndex) ) 
        {
            throw XEOutOfRange(paramIndex,getLength());
        }
        return *(((T *)m_Data) + paramIndex);
    }
    //---------------------------------------------------------------------
    ///��չ����
    /**
        ע��:�������������������ȫ���
        @param [in] paramMinimumCapacity ָ������С����������������ַ�����
    */
    template<class T>
    void XStringBase<T>::expandCapacity(XInt paramMinimumCapacity)
        ZDH_THROW(XEOutOfMemory)
    {
        //ZDH_ASSERT(paramMinimumCapacity>0);
        XInt iNowCapacity = getCapacity();
        if( iNowCapacity < paramMinimumCapacity)    
        {
            XInt iNewCapacity = paramMinimumCapacity * CHAR_SIZE + HEAD_SIZE; //ȡ��ʵ��������ֽ���
            iNowCapacity *= 2;
            if( iNewCapacity < iNowCapacity) iNewCapacity = iNowCapacity;
            XInt iMod = iNewCapacity % STRING_BLOCK_SIZE;
            //ȷ��������ڴ�Ϊָ����С�ı���
            if( iMod > 0 )
            {
                iNewCapacity += (STRING_BLOCK_SIZE - iMod);
            }
            SStringStruct * pData = (SStringStruct *)AllocMemory(iNewCapacity);
            //����ڴ��Ƿ����
            if( pData == NULL )
            {
                throw XEOutOfMemory();
            }
            //���û�������
            pData->Capacity = (iNewCapacity - HEAD_SIZE) / CHAR_SIZE;
            pData->Length = getLength();
            if( pData->Length > 0 ) //��������
            {
                CopyData( (T *)m_Data, (T *)(pData + 1), getLength() );
            }
            else
            {
                *((T *)(pData + 1)) = 0;
            }
            //�ͷ�ԭ����
            if( m_Data != NULL )
            {
                FreeMemory(getOriData());
            }
            //��ʼ�滻
            m_Data = (T *)(pData+1);
        }
    }
    //-----------------------------------------------------------------------------
    ///���ַ���ת����32λ�з�������
    /**
        ת��ʧ�ܣ����׳�XEConvert�쳣
     */
    template<class T>
    XInt XStringBase<T>::ToInt() const
        ZDH_THROW(XEConvert)
    {
        XInt iRet;
        if( !string_utils::TryStringToInt(c_str(),iRet))
        {
            throw XEConvert();
        }
        return iRet;
    }
    //-----------------------------------------------------------------------------
    ///���ַ���ת����32λ�޷�������
    /**
        ת��ʧ�ܣ����׳�XEConvert�쳣
     */
    template<class T>
    XDWord XStringBase<T>::ToDWord() const
        ZDH_THROW(XEConvert)
    {
        XDWord dwRet;
        if( !string_utils::TryStringToDWord(c_str(),dwRet))
        {
            throw XEConvert();
        }
        return dwRet;
    }
    //-----------------------------------------------------------------------------
    ///���ַ���ת����64λ�з�������
    /**
        ת��ʧ�ܣ����׳�XEConvert�쳣
     */
    template<class T>
    XLong XStringBase<T>::ToLong() const
        ZDH_THROW(XEConvert)
    {
        XLong lngRet;
        if( !string_utils::TryStringToLong(c_str(),lngRet))
        {
            throw XEConvert();
        }
        return lngRet;
    }
    //-----------------------------------------------------------------------------
    ///���ַ���ת����64λ�޷�������
    /**
        ת��ʧ�ܣ����׳�XEConvert�쳣
     */
    template<class T>
    XDDWord XStringBase<T>::ToDDWord() const
        ZDH_THROW(XEConvert)
    {
        XDDWord ddwRet;
        if( !string_utils::TryStringToDDWord(c_str(),ddwRet))
        {
            throw XEConvert();
        }
        return ddwRet;
    }
    //-----------------------------------------------------------------------------
    ///����ostream��<<�����
    inline std::ostream & operator << (std::ostream & paramOutStream, const XAnsiString & paramStr)
    {
        return paramOutStream << paramStr.c_str();
    }
    //-----------------------------------------------------------------------------
#if defined(OS_WINDOWS)
    inline std::wostream & operator << (std::wostream & paramOutStream, const XWideString & paramStr)
    {
        return paramOutStream << paramStr.c_str();
    }
#endif
    //-----------------------------------------------------------------------------
    ///������չ����� Ϊ����stl��string
    inline bool operator == (const XChar* a, const XAnsiString & b) 
    { 
        return b == a; 
    }
    //-----------------------------------------------------------------------------
    inline bool operator != (const XChar* a, const XAnsiString & b) 
    { 
        return b != a; 
    }
    //-----------------------------------------------------------------------------
    inline XAnsiString operator + (const char* a, const XAnsiString & b)
    {
        return XAnsiString(a) << b;
    }
    #if defined(OS_WINDOWS)
        //-----------------------------------------------------------------------------
        inline bool operator == (const XWideChar* a, const XWideString & b) 
        { 
            return b == a; 
        }
        //-----------------------------------------------------------------------------
        inline bool operator != (const XWideChar* a, const XWideString & b) 
        { 
            return b != a; 
        }
        //-----------------------------------------------------------------------------
        inline XWideString operator + (const XWideChar* a, const XWideString & b)
        {
            return XWideString(a) << b;
        }
    #endif

}
#endif
