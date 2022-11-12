///字符串类模板
/**
 * 字符串类模板
 * 这个提供相对比较集成的字符串类，用于比较方便的操作。
 *
 * zdhsoft 2011 版权所有
 *
 * @file xstring.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-11
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、字符串类模板

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-01  1.0             创建初始文件
***********************************************************************/
#ifndef _X_STRING_H_
#define _X_STRING_H_
#include <xstring_utils.h>
#include <xmemory.h>
#include <string>
namespace zdh
{
    ///字符串基础模板
    template<class T = XChar>
    class XStringBase
    {
    public:
        enum
        {
            npos = -1,
            force_dword = 0x7fffffff //强制该枚举类型为32位整数
        };
    public:
        typedef T StringChar;
        typedef T * TPointer;
        typedef const T * ConstTPointer;
    private:
        ///字符串结构结构体
        struct SStringStruct
        {
            XInt Length;        ///<尺寸
            XInt Capacity;      ///<当前字符串的容量
            //Data              ///<当前数据指针所在的位置
        };
        //字符串内的常量定义,不给外部使用的
        enum 
        { 
            STRING_BLOCK_SIZE = 64,             //单位块大小
            CHAR_SIZE = sizeof(T),              //每个字符串的大小
            HEAD_SIZE = sizeof(SStringStruct),  //字符串头的字节数
            XSTRING_BASE_ENUM_FORCE_DWORD = 0x7FFFFFFF //强制该Enum为32位
        };  //字符串最小内存块大小
    public:
        ///默认构造函数
        XStringBase() 
            :m_Data(NULL) 
        {}
        ///构造函数
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
        ///默认拷贝构造函数
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
        ///构造函数
        XStringBase(const T & paramChar)
            :m_Data(NULL)
        {
            ensureCapacity(1);
            *((T *)m_Data) = paramChar;
            *(((T *)m_Data) + 1) = 0;
            getOriData()->Length = 1;

        }
        ///析构函数
        ~XStringBase()
        {
            if( isNotNULL(m_Data) )
            {
                FreeMemory(getOriData());
                m_Data = NULL;
            }
        }
        ///取字符串最小块的字节数
        XInt getBlockBytes() const { return STRING_BLOCK_SIZE; }
        ///取字符的字节数
        XInt getCharBytes() const { return CHAR_SIZE; }
        ///取当前容量
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
        ///取当前字符串的长度
        XInt getLength() const
        {
            XInt iRet = 0;
            if( isNotNULL(m_Data) )
            {
                iRet = getOriData()->Length;
            }
            return iRet;
        }
        //兼容STL的string 方法
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
        ///取数组的最大容量
        XInt getMaxCapacity() const { return (0x7ffffff0 - HEAD_SIZE) / CHAR_SIZE;  }
        ///确定装载字符容量(会自动增加0结尾)
        void ensureCapacity(XInt paramCharCapacity)
        {
            if( paramCharCapacity > 0)
            {
                expandCapacity(paramCharCapacity + 1); //增加一个字符0的位置
            }
        }
        ///取字符串的内容
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
        ///判断当前字符串是否为空
        bool isEmpty() const { return getLength() == 0; }
        bool empty() const
        {
            return isEmpty();
        }
        bool isNotEmpty() const { return getLength() != 0; }
        ///取字符串指针函数
        const void * Data() const { return m_Data; }
        ///赋值函数
        /**
            将当前串设为指定的串
         */
        void Assign(const XStringBase<T> & paramR)
        {
            if( &paramR != this )
            {
                Assign(paramR.c_str(), paramR.getLength());
            }
        }
        ///赋值函数
        /**
            将当前串设为指定的串    
         */
        void Assign(const T * paramR)
        {
            ZDH_ASSERT(paramR != NULL);
            XInt iLength = string_utils::Length(paramR);
            Assign(paramR, iLength);
        }
        ///赋值函数
        /**
            将当前串设为指定的串    
            @param [in] paramR 指定的串
            @param [in] paramLength 指定串的长度
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
        ///赋值函数
        /**
            将当前串设为只有指定字符的串    
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
        ///追加指定的字符串
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
        ///追加指定的字符串
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
        ///追加指定的字符串
        void AppendString(const T * paramR)
        {
            AppendString(paramR, string_utils::Length(paramR));
        }
        ///追加指定长度的字符串
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
        ///追加一个字符
        void AppendChar(const T paramR)
        {
            AppendChar(paramR,1);
        }
        ///追加指定个数的字符
        /**
            字符'\0'不能被加入
            @param [in] paramR 要追加的字符
            @param [in] paramCount 要追加的个数
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
        ///取指定下标的字符
        /**
            @param [in] paramIndex 指定的下标，有效范围是[0,getLength()-1];
         */
        T at(XInt paramIndex) const;
        ///取指定下标的字符引用
        /**
            @param [in] paramIndex 指定的下标，有效范围是[0,getLength()-1];
         */
        T & at(XInt paramIndex);
        ///检查指定的下标是否有效
        bool CheckIndex(XInt iIndex) const
        {
            return iIndex >= 0 && iIndex < getLength();
        }
        ///查找子串的位置
        /**
            如果子串存在，则返回子串的下标，有效下标在[0,getLength()-1]之间;
            如果子串为空，则返回npos;
            @param [in] paramSubString 子串
            @return XInt 返回子串的下标
                - npos 表示未找到子串
                - >=0 表示返回对应子串的下标

         */
        XInt Pos(const XStringBase<T> & paramSubString) const
        {
            return Pos(0,paramSubString);
        }
        ///查找子串的位置
        /**
            如果子串存在，则返回子串的下标，有效下标在[0,getLength()-1]之间;
            如果子串为空，则返回npos;
            @param [in] paramSubString 子串
            @return XInt 返回子串的下标
                - npos 表示未找到子串
                - >=0 表示返回对应子串的下标

         */
        XInt Pos(const T * paramSubString) const
        {
            return Pos(0, paramSubString, string_utils::Length(paramSubString));
        }
        ///查找子串的位置
        /**
            如果子串存在，则返回子串的下标，有效下标在[0,getLength()-1]之间;
            如果子串为空，则返回npos;
            @param [in] paramSubString 子串
            @param [in] paramSubStringLength 子串的长度 
            @return XInt 返回子串的下标
                - npos 表示未找到子串
                - >=0 表示返回对应子串的下标

         */
        XInt Pos(const T * paramSubString, XInt paramSubStringLength) const
        {
            return Pos(0, paramSubString, paramSubStringLength);
        }
        ///查找子串的位置
        /**
            如果子串存在，则返回子串的下标，有效下标在[0,getLength()-1]之间;
            如果子串为空，则返回npos;
            @param [in] paramStartPos 开始的下标
            @param [in] paramSubString 子串
            @param [in] paramSubStringLength 子串的长度 
            @return XInt 返回子串的下标
                - npos 表示未找到子串
                - >=0 表示返回对应子串的下标

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
        ///从指定开始的位置，查找子串的位置
        /**
            如果子串存在，则返回子串的下标，有效下标在[0,getLength()-1]之间;
            如果子串为空，则返回npos;
            @param [in] paramStartPos 开始的位置
            @param [in] paramSubString 子串
            @return XInt 返回子串的下标
                - npos 表示未找到子串
                - >=0 表示返回对应子串的下标

         */
        XInt Pos(const XInt paramStartPos, const XStringBase<T> & paramSubString) const
        {
            return Pos(paramStartPos, paramSubString.c_str(), paramSubString.getLength());
        }
        ///确定字符的位置
        /**
            如果字符为0,则返回npos
            如果字符存在，则返回字符的下标，有效下标在[0,getLength()-1]之间;
            @param [in] paramChar 要查找的字符
            @return XInt 返回字符的下标
                - npos 表示未找到字符
                - >=0 表示返回对应字符的下标
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
        ///从指定开始的位置，查找字符
        /**
            @param [in] paramStartPos 指定开始的位置，从0开始
            @param [in] paramChar 查找的字符
            @return XInt 返回字符的下标
                - npos 表示未找到字符
                - >=0 表示返回对应字符的下标
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
        //为兼容stl的string函数
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


        ///替换字符
        /**
            @param [in] paramFindChar 查找的字符
            @param [in] paramDestChar 要被替换成的字符
            @return XInt 被替换的字符个数
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
        ///指定位置字符串
        /**
            @param [in] paramPos 插入的位置
            @param [in] paramInsertString 插入的字符串
         */
        void InsertString(XInt paramPos, const XStringBase<T> & paramInsertString, XInt paramInsertCount = 1)
        {
            InsertString(paramPos, paramInsertString.c_str(), paramInsertString.getLength(),paramInsertCount);
        }
        ///指定位置字符串
        /**
            @param [in] paramPos 插入的位置
            @param [in] paramInsertString 插入的字符串
         */
        void InsertString(XInt paramPos, const T * paramInsertString, XInt paramInsertCount = 1)
        {
            InsertString(paramPos, paramInsertString, string_utils::Length(paramInsertString),paramInsertCount);
        }
        ///指定位置字符串
        /**
            @param [in] paramPos 插入的位置
            @param [in] paramInsertString 插入的字符串
            @param [in] paramInsertLength 要插入的字符串的长度
            @param [in] paramInsertCount 反复插入串的次数，默认为1
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
            if( iInsertLength > 0) //如果有要插入的数据
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
                    //移动
                    T * pDest = p + iLength + iAllInsertLength; //最后的地址
                    T * pSrc = p + iLength;
                    T * pMove = p + paramPos;
                    while( pSrc >= pMove )
                    {
                        *pDest-- = *pSrc --;
                    }
                    //插入
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

        ///查询替换子串
        /**
            @param [in] paramSubString 要被替换的子串
            @param [in] paramDestString 要被换成的字符串
            @param [in] paramMaxReplaceCount 最大替换的次数,如果该值小于0,则不限次数
            @return XInt 实际替换的次数
         */
        XInt ReplaceString(const T * paramSubString, const T * paramDestString, XInt paramMaxReplaceCount = -1)
        {
            ZDH_ASSERT(paramSubString != NULL );
            ZDH_ASSERT(paramDestString != NULL );
            return ReplaceString( 0, paramSubString, string_utils::Length(paramSubString), paramDestString, string_utils::Length( paramDestString), paramMaxReplaceCount );
        }
        ///查询替换子串
        /**
            @param [in] paramSubString 要被替换的子串
            @param [in] paramDestString 要被换成的字符串
            @param [in] paramMaxReplaceCount 最大替换的次数,如果该值小于0,则不限次数
            @return XInt 实际替换的次数
         */
        XInt ReplaceString(const XStringBase<T> & paramSubString, const XStringBase<T> & paramDestString, XInt paramMaxReplaceCount = -1)
        {
            return ReplaceString( 0, paramSubString.c_str(), paramSubString.getLength(), paramDestString.c_str(), paramDestString.getLength(), paramMaxReplaceCount);
        }
        ///查询替换子串
        /**
            @param [in] paramStartPos 开始查找替换的位置
            @param [in] paramSubString 要被替换的子串
            @param [in] paramDestString 要被换成的字符串
            @param [in] paramMaxReplaceCount 最大替换的次数,如果该值小于0,则不限次数
            @return XInt 实际替换的次数
         */
        XInt ReplaceString(XInt paramStartPos, const T * paramSubString, const T * paramDestString, XInt paramMaxReplaceCount = -1)
        {
            ZDH_ASSERT(paramSubString != NULL );
            ZDH_ASSERT(paramDestString != NULL );
            return ReplaceString( paramStartPos, paramSubString, string_utils::Length(paramSubString), paramDestString, string_utils::Length( paramDestString), paramMaxReplaceCount );
        }
        ///查询替换子串
        /**
            @param [in] paramStartPos 开始查找替换的位置
            @param [in] paramSubString 要被替换的子串
            @param [in] paramDestString 要被换成的字符串
            @param [in] paramMaxReplaceCount 最大替换的次数,如果该值小于0,则不限次数
            @return XInt 实际替换的次数
         */
        XInt ReplaceString(XInt paramStartPos, const XStringBase<T> & paramSubString, const XStringBase<T> & paramDestString, XInt paramMaxReplaceCount = -1)
        {
            return ReplaceString( paramStartPos, paramSubString.c_str(), paramSubString.getLength(), paramDestString.c_str(), paramDestString.getLength(), paramMaxReplaceCount);
        }
        ///查询替换子串
        /**
            @param [in] paramStartPos 开始查找替换的位置
            @param [in] paramSubString 要被替换的子串
            @param [in] paramSubStringLength 子串的长度
            @param [in] paramDestString 要被换成的字符串
            @param [in] paramDestStringLength 要被换成的字符串的长度
            @param [in] paramMaxReplaceCount 最大替换的次数,如果该值小于0,则不限次数
            @return XInt 实际替换的次数
         */
        XInt ReplaceString(XInt paramStartPos, const T * paramSubString, XInt paramSubStringLength, const T * paramDestString, XInt paramDestStringLength, XInt paramMaxReplaceCount = -1)
        {
            ZDH_ASSERT(paramSubString != NULL);
            ZDH_ASSERT(paramDestString != NULL);
            ZDH_ASSERT(paramSubStringLength == string_utils::Length(paramSubString));
            ZDH_ASSERT(paramDestStringLength == string_utils::Length(paramDestString));
            XInt iRet = 0;  //返回替换的次数
            XInt iStart = paramStartPos;    //开始替换的位置
            XInt iBegin = 0;                //要保留字符串的起始位置
            XStringBase<T> strTemp;         //临时用的字符串
            XInt iLocalLength = getLength();    //当前字符串的长度
            strTemp.ensureCapacity( iLocalLength );
            XInt iPos = Pos(iStart, paramSubString, paramSubStringLength ); //第一次查找
            //当找到子串，并且替换次数小于最大替换次数或者无限替换次数
            while(iPos >= 0 && ((paramMaxReplaceCount > 0 && iRet < paramMaxReplaceCount) || paramMaxReplaceCount < 0) )
            {
                iRet ++;
                XInt iCopyLength = iPos - iBegin; //确定要复制的字符串
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
            if( iRet > 0) //如果发生了替换
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
        ///将字符转换成32位有符号整数
        /**
            如果字符串是无效整数，将会抛出异常XEConvert。
            字符串支持8,10,16进制整数
         */
        XInt ToInt() const;
        ///将字符转换成32位有符号整数
        /**
            字符串支持8,10,16进制整数
            @param [out] paramResult 存放转换的结果
            @return bool 转换结果
                - true 表示转换成功
                - false 表示转换失败
         */
        bool ToInt(XInt & paramResult) const
        {
            return string_utils::TryStringToInt(c_str(),paramResult);
        }
        ///将字符转换成32位有符号整数
        /**
            如果字符串是无效整数，将会返回指定的缺省值。
            字符串支持8,10,16进制整数
            @param [in] paramDefault 转换失败的缺省值
         */
        XInt ToIntDef(XInt paramDefault) const
        {
            return string_utils::StringToIntDef(c_str(),paramDefault);
        }
        ///将字符转换成32位无符号整数
        /**
            如果字符串是无效整数，将会抛出异常XEConvert。
            字符串支持8,10,16进制整数
         */
        XDWord ToDWord() const;
        ///将字符转换成32位无符号整数
        /**
            字符串支持8,10,16进制整数
            @param [out] paramResult 存放转换的结果
            @return bool 转换结果
                - true 表示转换成功
                - false 表示转换失败
         */
        bool ToDWord(XDWord & paramResult) const
        {
            return string_utils::TryStringToDWord(c_str(), paramResult);
        }
        ///将字符转换成32位无符号整数
        /**
            如果字符串是无效整数，将会返回指定的缺省值。
            字符串支持8,10,16进制整数
            @param [in] paramDefault 转换失败的缺省值
         */
        XDWord ToDWordDef(XDWord paramDefault) const
        {
            return string_utils::StringToDWordDef(c_str(),paramDefault);
        }
        ///将字符转换成64位有符号整数
        /**
            如果字符串是无效整数，将会抛出异常XEConvert。
            字符串支持8,10,16进制整数
         */
        XLong ToLong() const;
        ///将字符转换成64位有符号整数
        /**
            字符串支持8,10,16进制整数
            @param [out] paramResult 存放转换的结果
            @return bool 转换结果
                - true 表示转换成功
                - false 表示转换失败
         */
        bool ToLong(XLong & paramResult) const
        {
            return string_utils::TryStringToLong(c_str(), paramResult);
        }
        ///将字符转换成64位有符号整数
        /**
            如果字符串是无效整数，将会返回指定的缺省值。
            字符串支持8,10,16进制整数
            @param [in] paramDefault 转换失败的缺省值
         */
        XLong ToLongDef(XLong paramDefault) const
        {
            return string_utils::StringToLongDef(c_str(),paramDefault);
        }
        ///将字符转换成64位无符号整数
        /**
            如果字符串是无效整数，将会抛出异常XEConvert。
            字符串支持8,10,16进制整数
         */
        XDDWord ToDDWord() const;
        ///将字符转换成64位无符号整数
        /**
            字符串支持8,10,16进制整数
            @param [out] paramResult 存放转换的结果
            @return bool 转换结果
                - true 表示转换成功
                - false 表示转换失败
         */
        bool ToDDWord(XDWord & paramResult) const
        {
            return string_utils::TryStringToDDWord(c_str(), paramResult);
        }
        ///将字符转换成64位无符号整数
        /**
            如果字符串是无效整数，将会返回指定的缺省值。
            字符串支持8,10,16进制整数
            @param [in] paramDefault 转换失败的缺省值
         */
        XDDWord ToDDWordDef(XDDWord paramDefault) const
        {
            return string_utils::StringToDDWordDef(c_str(), paramDefault);
        }
        ///比较函数
        /**
            @param [in] paramR 参考比较的函数
            @return XInt 返回比较结果
                - 0 表示this == paramR
                > 0 表示this > paramR
                < 0 表示this < paramR
         */
        XInt Compare(const XStringBase<T>& paramR) const
        {
            return string_utils::Compare(c_str(),paramR.c_str());
        }
        ///忽略大小写比较函数
        /**
            @param [in] paramR 参考比较的函数
            @return XInt 返回比较结果
                - 0 表示this == paramR
                > 0 表示this > paramR
                < 0 表示this < paramR
         */
        XInt CompareIC(const XStringBase<T>& paramR) const //ignorecase
        {
            return string_utils::CompareIC(c_str(),paramR.c_str());
        }
        ///设为空串
        void ToEmptyString()
        {
            if( getCapacity() > 0)
            {
                *((T *)m_Data) = 0;
                getOriData()->Length = 0;
            }
        }
        ///字符串交换
        void Swap(XStringBase<T> & paramR)
        {
            T * pTemp = m_Data;
            m_Data = paramR.m_Data;
            paramR.m_Data = pTemp;
        }
		//删除指区域的字符
		/**
			@param [in] paramStartPos 指定删除的起始位置
			@param [in] paramCharCount 要删除的字符个数
			@return XInt 删除字符的个数
				- > 0 删除字符的个数
				- -1 paramStartPos 越界
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
        ///在当前的字符串中，删除指定的字符
        /**
            @param [in] paramCh 要删除的字符
            @return XInt 删除字符的个数
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
        //一组删除子串的函数
        ///删除子串
        /**
            这个函数指定的要删除的子串和要删除子串的次数
            @param [in] paramRemoveString 要删除的子串
            @param [in] paramMaxRemoveCount 要删除子串的最大删除次数,-1表示不限制次数
            @return XInt 实际删除的次数
         */
        XInt RemoveString(const XStringBase<T> & paramRemoveString, XInt paramMaxRemoveCount)
        {
            return RemoveString(0, paramRemoveString.c_str(), paramRemoveString.getLength(), paramMaxRemoveCount);
        }
        ///删除子串
        /**
            这个函数指定的要删除的子串和要删除子串的次数
            @param [in] paramStartPos 指定开始删除的位置
            @param [in] paramRemoveString 要删除的子串
            @param [in] paramMaxRemoveCount 要删除子串的最大删除次数,-1表示不限制次数
            @return XInt 实际删除的次数
         */
        XInt RemoveString(XInt paramStartPos, const XStringBase<T> & paramRemoveString, XInt paramMaxRemoveCount)
        {
            return RemoveString(paramStartPos, paramRemoveString.c_str(), paramRemoveString.getLength(), paramMaxRemoveCount);
        }
        ///删除子串
        /**
            这个函数指定的要删除的子串和要删除子串的次数
            @param [in] paramRemoveString 要删除的子串
            @param [in] paramMaxRemoveCount 要删除子串的最大删除次数,-1表示不限制次数
            @return XInt 实际删除的次数
         */
        XInt RemoveString(const T * paramRemoveString, XInt paramMaxRemoveCount)
        {
            return RemoveString(0, paramRemoveString, string_utils::Length(paramRemoveString), paramMaxRemoveCount);
        }
        ///删除子串
        /**
            这个函数指定的要删除的子串和要删除子串的次数
            @param [in] paramStartPos 指定开始删除的位置
            @param [in] paramRemoveString 要删除的子串
            @param [in] paramMaxRemoveCount 要删除子串的最大删除次数,-1表示不限制次数
            @return XInt 实际删除的次数
         */
        XInt RemoveString(XInt paramStartPos, T * paramRemoveString, XInt paramMaxRemoveCount)
        {
            return RemoveString(paramStartPos, paramRemoveString, string_utils::Length(paramRemoveString), paramMaxRemoveCount);
        }
        ///删除子串
        /**
            这个函数指定的要删除的子串
            @param [in] paramRemoveString 要删除的子串
            @return XInt 实际删除的次数
         */
        XInt RemoveString(const XStringBase<T> & paramRemoveString)
        {
            return RemoveString(0, paramRemoveString.c_str(), paramRemoveString.getLength(), -1);
        }
        ///删除子串
        /**
            这个函数指定的要删除的子串
            @param [in] paramStartPos 指定开始删除的位置
            @param [in] paramRemoveString 要删除的子串
            @return XInt 实际删除的次数
         */
        XInt RemoveString(XInt paramStartPos, const XStringBase<T> & paramRemoveString)
        {
            return RemoveString(paramStartPos, paramRemoveString.c_str(), paramRemoveString.getLength(), -1);
        }
        ///删除子串
        /**
            这个函数指定的要删除的子串
            @param [in] paramRemoveString 要删除的子串
            @return XInt 实际删除的次数
         */
        XInt RemoveString(const T * paramRemoveString)
        {
            return RemoveString(0, paramRemoveString, string_utils::Length(paramRemoveString), -1);
        }
        ///删除子串
        /**
            这个函数指定的要删除的子串
            @param [in] paramStartPos 指定开始删除的位置
            @param [in] paramRemoveString 要删除的子串
            @return XInt 实际删除的次数
         */
        XInt RemoveString(XInt paramStartPos, T * paramRemoveString)
        {
            return RemoveString(paramStartPos, paramRemoveString, string_utils::Length(paramRemoveString), -1);
        }
        ///删除指定的子串
        /**
            @param [in] paramStartPos 开始删除的下标
            @param [in] paramRemoveString 要删除的子串
            @param [in] paramRemoveStringLength 要删除子串的长度
            @param [in] paramMaxRemoveCount 要删除的次数，-1表示不限次数
            @return XInt 实际删除子串的次数
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
        ///将当前字符串小写转换成大写
        void UpperCase() 
        {
            string_utils::UpperCase((T *)Data());
        }
        ///将字符串大写转换成小写
        void LowerCase()
        {
            string_utils::LowerCase((T *)Data());
        }
        ///将整数转换为16进制串
        /**
            @param [in] paramValue 要转换的值
            @param [in] paramHexWidth 16进制数字的宽度
            @param [in] paramHexStyle 16进制的样式
            @param [in] paramHexPrefix 是否要0x前缀
         */
        void NumberToHex(XInt paramValue,XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            NumberToHex((XDWord)paramValue, paramHexWidth, paramHexStyle, paramHexPrefix);
        }
        ///将整数转换为16进制串
        /**
            @param [in] paramValue 要转换的值
            @param [in] paramHexWidth 16进制数字的宽度
            @param [in] paramHexStyle 16进制的样式
            @param [in] paramHexPrefix 是否要0x前缀
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
        ///将整数转换为16进制串
        /**
            @param [in] paramValue 要转换的值
            @param [in] paramHexWidth 16进制数字的宽度
            @param [in] paramHexStyle 16进制的样式
            @param [in] paramHexPrefix 是否要0x前缀
         */
        void NumberToHex(XLong paramValue,XInt paramHexWidth = 1, T paramHexStyle = 'A', bool paramHexPrefix = true)
        {
            NumberToHex((XDDWord)paramValue, paramHexWidth, paramHexStyle, paramHexPrefix);
        }
        ///将整数转换为16进制串
        /**
            @param [in] paramValue 要转换的值
            @param [in] paramHexWidth 16进制数字的宽度
            @param [in] paramHexStyle 16进制的样式
            @param [in] paramHexPrefix 是否要0x前缀
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
        ///取可以访问的字符串指针
        T * getDataPtr()
        {
            return m_Data;
        }
        ///扩展容量
        /**
            注意:这个函数，并不会做安全检查
            @param [in] paramMinimumCapacity 指定的最小容量，这个容量是字符个数
         */
        void expandCapacity(XInt paramMinimumCapacity);
        ///取实际字符串指针
        /**
            注意:这里不会做越界检查,
         */
        const SStringStruct * getOriData() const  { return ((const SStringStruct *)m_Data) - 1; }
        ///取实际字符串指针
        /**
            注意:这里不会做越界检查
         */
        SStringStruct * getOriData() {  return ((SStringStruct *)m_Data) - 1;}
        ///复制字符串
        /**
            @param [in] paramSrc 源字符串地址
            @param [out] paramDest 目标串地址
            @param [in] paramCopyCharNumber 要复制的字符个数
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

        ///查找子串是否存在
        /**
            @param [in] paramString 查找的字符串
            @param [in] paramSubString 被查找的子串
            @return T * 返回结果
                - NULL 表示未找到该子串
                - not NULL 表示找到了该子串，并返回该子串的地址
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
                if( c == c2 ) //如果找到了第一个字符，那么开始找子串
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
        T * m_Data;         ///<数据指针
    };
	using std::string;
    ///单字符字符串
    class XAnsiString : public XStringBase<XChar>
    {
    public:
        typedef XStringBase<XChar> Inherited;
    public:
        ///默认构造函数
        XAnsiString(){}
        ///指定初始值的构造函数
        XAnsiString(const XChar * paramString)
            :Inherited(paramString)
        {}
        ///默认拷贝构造函数
        XAnsiString(const XAnsiString & paramString)
            :Inherited(paramString)
        {}
        XAnsiString(const XStringBase<XWideChar> & paramWideString)
        {
            SetStringByWideString(paramWideString);
        }
        ///指定初始字符构造函数
        XAnsiString(XChar paramChar)
            :Inherited(paramChar)
        {}
        ///指定8位无符号整数构造函数
        XAnsiString(const XByte & paramByte)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramByte,TempBuffer));
        }
        ///指定16位有符号整数构造函数
        XAnsiString(const XShort & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///指定16位无符号整数构造函数
        XAnsiString(const XWord & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///指定32位有符号整数构造函数
        XAnsiString(const XInt & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///指定32位无符号整数构造函数
        XAnsiString(const XDWord & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::DWordToStr(paramNumber,TempBuffer));
        }
        ///指定64位有符号整数构造函数
        XAnsiString(const XLong & paramNumber)
        {
            XChar TempBuffer[32];
            Assign(string_utils::LongToStr(paramNumber,TempBuffer));
        }
        ///指定64位无符号整数构造函数
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
        ///指定字符赋值函数
        XAnsiString & operator = (const XChar & paramValue)
        {
            Assign(paramValue);
            return *this;
        }

		operator string()
		{
			return string(c_str(), std::size_t(getLength()));
		}
        ///指定8位无符号整数赋值函数
        XAnsiString & operator = (const XByte & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定16位有符号整数赋值函数
        XAnsiString & operator = (const XShort & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定16位无符号整数赋值函数
        XAnsiString & operator = (const XWord & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定32位有符号整数赋值函数
        XAnsiString & operator = (const XInt & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定32位无符号整数赋值函数
        XAnsiString & operator = (const XDWord & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定64位有符号整数赋值函数
        XAnsiString & operator = (const XLong & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定64位无符号整数赋值函数
        XAnsiString & operator = (const XDDWord & paramValue)
        {
            XChar TempBuffer[32];
            Assign(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定字符串赋值函数
        XAnsiString & operator = (const XAnsiString & paramValue)
        {
            if( &paramValue != this)
            {
                Assign(paramValue);
            }
            return *this;
        }
        ///追加一个字符串
        XAnsiString & operator += (const XChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }

        ///追加一个字符
        XAnsiString & operator += (const XChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///追加8位无符号整数
        XAnsiString & operator += (const XByte & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位有符号整数
        XAnsiString & operator += (const XShort & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位无符号整数
        XAnsiString & operator += (const XWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加32位有符号整数
        XAnsiString & operator += (const XInt & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加32位无符号整数
        XAnsiString & operator += (const XDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位有符号整数
        XAnsiString & operator += (const XLong & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位无符号整数
        XAnsiString & operator += (const XDDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加一个字符串
        XAnsiString & operator += (const XAnsiString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///追加一个字符串
        XAnsiString & operator << (const XChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///追加一个字符
        XAnsiString & operator << (const XChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///追加8位无符号整数
        XAnsiString & operator << (const XByte & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位有符号整数
        XAnsiString & operator << (const XShort & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位无符号整数
        XAnsiString & operator << (const XWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加32位有符号整数
        XAnsiString & operator << (const XInt & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加32位无符号整数
        XAnsiString & operator << (const XDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位有符号整数
        XAnsiString & operator << (const XLong & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位无符号整数
        XAnsiString & operator << (const XDDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加一个字符串
        XAnsiString & operator << (const XAnsiString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///追加一个字符串
        XAnsiString & operator , (const XChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///追加一个字符
        XAnsiString & operator , (const XChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///追加8位无符号整数
        XAnsiString & operator , (const XByte & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位有符号整数
        XAnsiString & operator , (const XShort & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位无符号整数
        XAnsiString & operator , (const XWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加32位有符号整数
        XAnsiString & operator , (const XInt & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加32位无符号整数
        XAnsiString & operator , (const XDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位有符号整数
        XAnsiString & operator , (const XLong & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位无符号整数
        XAnsiString & operator , (const XDDWord & paramValue)
        {
            XChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加一个字符串
        XAnsiString & operator , (const XAnsiString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///重载[]运算符
        XChar operator[](XInt paramIndex) const
        {
            return at(paramIndex);
        }
        ///重载[]运算符
        XChar & operator[](XInt paramIndex)
        {
            return at(paramIndex);
        }
        ///连接一个字符
        XAnsiString operator + (const XChar & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接8位无符整数
        XAnsiString operator + (const XByte & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接16位有符整数
        XAnsiString operator + (const XShort & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接16位无符整数
        XAnsiString operator + (const XWord & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接32位有符整数
        XAnsiString operator + (const XInt & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接32位无符整数
        XAnsiString operator + (const XDWord & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接64位有符整数
        XAnsiString operator + (const XLong & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接64位无符整数
        XAnsiString operator + (const XDDWord & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接一个字符串
        XAnsiString operator + (const XAnsiString & paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接一个字符串
        XAnsiString operator + (const XChar * paramValue) const
        {
            XAnsiString strRet(*this);
            strRet += paramValue;
            return strRet;
        }

        //一组比较函数
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

        //一组比较函数
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
        ///指定格式化生成字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XAnsiString & 返回当前字符串
         */
        XAnsiString& sprintf(const XChar* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            vprintf(paramFormat, argptr);
            va_end(argptr);
            return *this;
        }
        ///指定格式化生成字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XAnsiString & 返回当前字符串
         */
        XAnsiString& snprintf(XInt paramSize, const XChar* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            vnprintf(paramSize, paramFormat, argptr);
            va_end(argptr);
            return *this;
        }
        ///指定格式化生成字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XInt 返回格式化字符串的长度
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

        ///指定格式化生成字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XInt 返回格式化字符串的长度
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

        ///指定连接格式化生成的字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XAnsiString & 返回当前字符串
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
        ///指定连接格式化生成的字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XInt 返回格式化字符串的长度
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
        ///指定连接格式化生成的字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XInt 返回格式化字符串的长度
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


        ///指定连接格式化生成的字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XInt 返回格式化字符串的长度
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

        ///清空字符串左右两边空格字符
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
        ///清空字符串左边空格字符串
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
        ///清空字符串右边空格字符串
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
        ///取指定的子串
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
        ///取指定的子串
        /**
            @param [in] paramStartPos 指定的位置
            @param [in] paramSubLength 子串的长度
            @return XAnsiString 取得的子串
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
        ///取空串
        static const XAnsiString & EmptyString() 
        {
            static XAnsiString sEmptyString;
            return sEmptyString;
        }
        ///将宽字符串集字符串，转换为多字节字符串
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
    ///双字符字符串
    class XWideString : public XStringBase<XWideChar>
    {
    public:
        typedef XStringBase<XWideChar> Inherited;
    public:
        ///默认构造函数
        XWideString(){}
        ///指定初始值的构造函数
        XWideString(const XWideChar * paramString)
            :Inherited(paramString)
        {}
        ///默认拷贝构造函数
        XWideString(const XWideString & paramString)
            :Inherited(paramString)
        {}
        XWideString(const XStringBase<XChar> & paramString)
        {
            SetStringByWideString(paramString);
        }
        ///指定初始字符构造函数
        XWideString(XWideChar paramChar)
            :Inherited(paramChar)
        {}
        ///指定8位无符号整数构造函数
        XWideString(const XByte & paramByte)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramByte,TempBuffer));
        }
        ///指定16位有符号整数构造函数
        XWideString(const XShort & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///指定16位无符号整数构造函数
        XWideString(const XWord & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///指定32位有符号整数构造函数
        XWideString(const XInt & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramNumber,TempBuffer));
        }
        ///指定32位无符号整数构造函数
        XWideString(const XDWord & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::DWordToStr(paramNumber,TempBuffer));
        }
        ///指定64位有符号整数构造函数
        XWideString(const XLong & paramNumber)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::LongToStr(paramNumber,TempBuffer));
        }
        ///指定64位无符号整数构造函数
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

        ///指定字符赋值函数
        XWideString & operator = (const XWideChar & paramValue)
        {
            Assign(paramValue);
            return *this;
        }
        ///指定8位无符号整数赋值函数
        XWideString & operator = (const XByte & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定16位有符号整数赋值函数
        XWideString & operator = (const XShort & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定16位无符号整数赋值函数
        //XWideString & operator = (const XWord & paramValue)
        //{
        //    XWideChar TempBuffer[32];
        //    Assign(string_utils::IntToStr(paramValue,TempBuffer));
        //    return *this;
        //}
        ///指定32位有符号整数赋值函数
        XWideString & operator = (const XInt & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定32位无符号整数赋值函数
        XWideString & operator = (const XDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定64位有符号整数赋值函数
        XWideString & operator = (const XLong & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定64位无符号整数赋值函数
        XWideString & operator = (const XDDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            Assign(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///指定字符串赋值函数
        XWideString & operator = (const XWideString & paramValue)
        {
            if( &paramValue != this)
            {
                Assign(paramValue);
            }
            return *this;
        }
        ///追加一个字符串
        XWideString & operator += (const XWideChar * paramValue)
        {
            AppendString(paramValue);//,::strlen(paramValue));
            return *this;
        }
        ///追加一个字符
        XWideString & operator += (const XWideChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///追加8位无符号整数
        XWideString & operator += (const XByte & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位有符号整数
        XWideString & operator += (const XShort & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位无符号整数
        //XWideString & operator += (const XWord & paramValue)
        //{
        //    XWideChar TempBuffer[32];
        //    AppendString(string_utils::IntToStr(paramValue,TempBuffer));
        //    return *this;
        //}
        ///追加32位有符号整数
        XWideString & operator += (const XInt & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加32位无符号整数
        XWideString & operator += (const XDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位有符号整数
        XWideString & operator += (const XLong & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位无符号整数
        XWideString & operator += (const XDDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加一个字符串
        XWideString & operator += (const XWideString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///追加一个字符串
        XWideString & operator << (const XWideChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///追加一个字符
        XWideString & operator << (const XWideChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///追加8位无符号整数
        XWideString & operator << (const XByte & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位有符号整数
        XWideString & operator << (const XShort & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位无符号整数
        //XWideString & operator << (const XWord & paramValue)
        //{
        //    XWideChar TempBuffer[32];
        //    AppendString(string_utils::IntToStr(paramValue,TempBuffer));
        //    return *this;
        //}
        ///追加32位有符号整数
        XWideString & operator << (const XInt & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加32位无符号整数
        XWideString & operator << (const XDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位有符号整数
        XWideString & operator << (const XLong & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位无符号整数
        XWideString & operator << (const XDDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加一个字符串
        XWideString & operator << (const XWideString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///追加一个字符串
        XWideString & operator , (const XWideChar * paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///追加一个字符
        XWideString & operator , (const XWideChar & paramValue)
        {
            AppendChar(paramValue);
            return *this;
        }
        ///追加8位无符号整数
        XWideString & operator , (const XByte & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位有符号整数
        XWideString & operator , (const XShort & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加16位无符号整数
        //XWideString & operator , (const XWord & paramValue)
        //{
        //    XWideChar TempBuffer[32];
        //    AppendString(string_utils::IntToStr(paramValue,TempBuffer));
        //    return *this;
        //}
        ///追加32位有符号整数
        XWideString & operator , (const XInt & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::IntToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加32位无符号整数
        XWideString & operator , (const XDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位有符号整数
        XWideString & operator , (const XLong & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::LongToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加64位无符号整数
        XWideString & operator , (const XDDWord & paramValue)
        {
            XWideChar TempBuffer[32];
            AppendString(string_utils::DDWordToStr(paramValue,TempBuffer));
            return *this;
        }
        ///追加一个字符串
        XWideString & operator , (const XWideString & paramValue)
        {
            AppendString(paramValue);
            return *this;
        }
        ///重载[]运算符
        XWideChar operator[](XInt paramIndex) const
        {
            return at(paramIndex);
        }
        ///重载[]运算符
        XWideChar & operator[](XInt paramIndex)
        {
            return at(paramIndex);
        }
        ///连接一个字符
        XWideString operator + (const XWideChar & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接8位无符整数
        XWideString operator + (const XByte & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接16位有符整数
        XWideString operator + (const XShort & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接16位无符整数
        //XWideString operator + (const XWord & paramValue) const
        //{
        //    XWideString strRet(*this);
        //    strRet += paramValue;
        //    return strRet;
        //}
        ///连接32位有符整数
        XWideString operator + (const XInt & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接32位无符整数
        XWideString operator + (const XDWord & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接64位有符整数
        XWideString operator + (const XLong & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接64位无符整数
        XWideString operator + (const XDDWord & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接一个字符串
        XWideString operator + (const XWideString & paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }
        ///连接一个字符串
        XWideString operator + (const XWideChar * paramValue) const
        {
            XWideString strRet(*this);
            strRet += paramValue;
            return strRet;
        }

        //一组比较函数
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

        //一组比较函数
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
        ///指定格式化生成字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XWideString & 返回当前字符串
         */
        XWideString& sprintf(const XWideChar* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            vprintf(paramFormat,argptr);
            return *this;
        }
        ///指定格式化生成字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XInt 返回格式化字符串的长度
         */
        XInt printf(const XWideChar* paramFormat, ...) // Returns formatted length
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            return vprintf(paramFormat,argptr);
        }
        ///指定格式化生成字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XInt 返回格式化字符串的长度
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
        ///指定连接格式化生成的字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XWideString & 返回当前字符串
         */
        XWideString& cat_sprintf(const XWideChar* paramFormat, ...) // Returns *this
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            cat_vprintf(paramFormat, argptr);
            return *this;
        }
        ///指定连接格式化生成的字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XInt 返回格式化字符串的长度
         */
        XInt cat_printf(const XWideChar* paramFormat, ...) // Returns formatted length
        {
            va_list argptr;
            va_start(argptr, paramFormat);
            return cat_vprintf(paramFormat, argptr);
        }
        ///指定连接格式化生成的字符串
        /**
            @param [in] 格式化串,参考标准C的格式化串
            @return XInt 返回格式化字符串的长度
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


        ///清空字符串左右两边空格字符
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
        ///清空字符串左边空格字符串
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
        ///清空字符串右边空格字符串
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
        ///取指定的子串
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
        ///取指定的子串
        /**
            @param [in] paramStartPos 指定的位置
            @param [in] paramSubLength 子串的长度
            @return XWideString 取得的子串
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
        ///取空串
        static const XWideString & EmptyString() 
        {
            static XWideString sEmptyString;
            return sEmptyString;
        }
        ///将宽字符串集字符串，转换为多字节字符串
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
    ///异常类基类
    class EException
    {
    public:
        ///默认构造函数
        EException()
            :m_HelpContext(0)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        EException(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :m_Message(paramMessage),
             m_HelpContext(paramHelpContext)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        EException(const XChar* paramMessage, XInt paramHelpContext = 0)
            :m_Message(paramMessage),
            m_HelpContext(paramHelpContext)
        {}
        ///析构函数
        virtual ~EException()
        {}
        ///取异常信息
        const XAnsiString getMessage() const
        {
            return m_Message;
        }
        ///设置异常信息
        void setMessage(const XChar * paramMessage)     
        {
            m_Message = paramMessage;
        }
        ///设置异常信息
        void setMessage(const XAnsiString & paramMessage)
        {
            m_Message = paramMessage;
        }
        ///取帮助信息ID
        XInt getHelpContext() const
        {
            return m_HelpContext;
        }
        ///设置帮助信息ID
        void setHelpContext(XInt paramHelpContext)
        {
            m_HelpContext = paramHelpContext;
        }
        ///转换成字符串指针
        operator const XChar *() const
        {
            return m_Message.c_str();
        }
    private:
        XAnsiString m_Message;  ///<异常信息
        XInt m_HelpContext;     ///<帮助信息ID
    };

    #define MESSAGE_OUT_OF_MEMORY "out of memory"
    #define MESSAGE_NOT_EXISTS "not exists object!"
    #define MESSAGE_IS_ZERO "is zero"
    #define MESSAGE_LESS_THAN_ZERO "less than zero"
    #define MESSAGE_CONVERT_FAIL "Type convert fail"
    #define MESSAGE_GREATER_THAN_ZERO "greater than zero"
    #define MESSAGE_OUT_OF_RANGE "out of range:index=%d,length=%d"

    ///内存溢出异常
    class XEOutOfMemory : public EException
    {
    public:
        ///默认构造函数
        XEOutOfMemory()
            :EException(MESSAGE_OUT_OF_MEMORY)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        XEOutOfMemory(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        XEOutOfMemory(const XChar* paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///析构函数
        ~XEOutOfMemory()
        {
        }
    };
    //---------------------------------------------------------------------
    class XEConvert : public EException
    {
    public:
        ///默认构造函数
        XEConvert()
            :EException(MESSAGE_CONVERT_FAIL)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        XEConvert(const XAnsiString & paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///指定异常信息的构造函数
        /**
            @param [in] paramMessage 异常信息
            @param [in] paramHelpContext 帮助信息ID
         */
        XEConvert(const XChar* paramMessage, XInt paramHelpContext = 0)
            :EException(paramMessage,paramHelpContext)
        {}
        ///析构函数
        ~XEConvert()
        {
        }
    };


    ///数组越界异常
    class XEOutOfRange : public EException
    {
    public:
        ///数组越界异常构造函数
        /**
            @param [in] paramIndex 越界的下标值
            @param [in] aLength 被越界的数组的长度
        */
        XEOutOfRange(XInt paramIndex = 0,XInt aLength = 0)
            :m_Index(paramIndex),m_Length(aLength)
        {
            MakeMsg();
        }
        ///析构函数
        ~XEOutOfRange(){}
        ///设置越界信息
        /**
            @param [in] paramIndex 越界的下标值
            @param [in] aLength 被越界的数组的长度
        */
        void setInfo(XInt paramIndex,XInt aLength)
        {
            m_Index = paramIndex;
            m_Length = aLength;
            MakeMsg();
        }
        ///取越界的下标值
        /**
            @return 返回越界的下标值
         */
        XInt getIndex() const { return m_Index; }
        ///取被越界的数组的长度
        /**
            @return 返回被越界的长度
         */
        XInt getLength() const { return m_Length; }
    protected:
        ///生成异常信息
        void MakeMsg()
        {
            XAnsiString strMsg;
            strMsg.printf(MESSAGE_OUT_OF_RANGE,m_Index,m_Length);
            setMessage(strMsg);
        }
    private:
        XInt m_Index;  ///<越界的下标
        XInt m_Length; ///<被越界的数组的下标
    };
    ///值为零异常类
    class XEIsZero : public EException
    {
    public:
        XEIsZero()
            :EException(MESSAGE_IS_ZERO)
        {}
    };
    ///值小于零异常类
    class XELessThanZero : public EException
    {
    public:
        XELessThanZero()
            :EException(MESSAGE_LESS_THAN_ZERO)
        {}
    };
    ///值大于零异常类
    class XEGreatherThanZero : public EException
    {
    public:
        XEGreatherThanZero()
            :EException(MESSAGE_GREATER_THAN_ZERO)
        {}
    };
    ///不存在异常类
    class XENotExists : public EException
    {
    public:
        XENotExists()
            :EException(MESSAGE_NOT_EXISTS)
        {}
    };
    //---------------------------------------------------------------------
    ///取指定下标的字符
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
    ///取指定下标的字符引用
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
    ///扩展容量
    /**
        注意:这个函数，并不会做安全检查
        @param [in] paramMinimumCapacity 指定的最小容量，这个容量是字符个数
    */
    template<class T>
    void XStringBase<T>::expandCapacity(XInt paramMinimumCapacity)
        ZDH_THROW(XEOutOfMemory)
    {
        //ZDH_ASSERT(paramMinimumCapacity>0);
        XInt iNowCapacity = getCapacity();
        if( iNowCapacity < paramMinimumCapacity)    
        {
            XInt iNewCapacity = paramMinimumCapacity * CHAR_SIZE + HEAD_SIZE; //取得实际所需的字节数
            iNowCapacity *= 2;
            if( iNewCapacity < iNowCapacity) iNewCapacity = iNowCapacity;
            XInt iMod = iNewCapacity % STRING_BLOCK_SIZE;
            //确保申请的内存为指定大小的倍数
            if( iMod > 0 )
            {
                iNewCapacity += (STRING_BLOCK_SIZE - iMod);
            }
            SStringStruct * pData = (SStringStruct *)AllocMemory(iNewCapacity);
            //检查内存是否溢出
            if( pData == NULL )
            {
                throw XEOutOfMemory();
            }
            //设置基本属性
            pData->Capacity = (iNewCapacity - HEAD_SIZE) / CHAR_SIZE;
            pData->Length = getLength();
            if( pData->Length > 0 ) //复制数据
            {
                CopyData( (T *)m_Data, (T *)(pData + 1), getLength() );
            }
            else
            {
                *((T *)(pData + 1)) = 0;
            }
            //释放原来的
            if( m_Data != NULL )
            {
                FreeMemory(getOriData());
            }
            //开始替换
            m_Data = (T *)(pData+1);
        }
    }
    //-----------------------------------------------------------------------------
    ///将字符串转换成32位有符号整数
    /**
        转换失败，将抛出XEConvert异常
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
    ///将字符串转换成32位无符号整数
    /**
        转换失败，将抛出XEConvert异常
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
    ///将字符串转换成64位有符号整数
    /**
        转换失败，将抛出XEConvert异常
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
    ///将字符串转换成64位无符号整数
    /**
        转换失败，将抛出XEConvert异常
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
    ///重载ostream的<<运算符
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
    ///其它扩展运算符 为兼容stl的string
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
