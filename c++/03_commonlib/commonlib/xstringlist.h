#ifndef _X_STRING_LIST_H_
#define _X_STRING_LIST_H_
#include <xstring.h>
#include <xdynamic_array.h>
#include <xset.h>
namespace zdh
{
    //字符串列表类，提供方便的字符串列表操作
    template<class T = XAnsiString>
    class XStringList
    {
    public:
        typedef T SubStringType;
        typedef typename T::StringChar StringChar;
    public:
        XStringList()
        {
        }

        XStringList(const XStringList<T> & paramList)
        {
            CopyList(paramList);    
        }
        ~XStringList()
        {
            Clear();
        }
        
        XStringList & operator = (const XStringList<T> & paramList)
        {
            CopyList(paramList);
            return *this;
        }
        //追加一个字符串
        XStringList<T> & Append(const T & paramT)
        {
            T * pT = AllocT();
            *pT = paramT;
            m_StringList.Append(pT);
            return *this;
        }
        XStringList<T> & Append(const StringChar * paramT)
        {
            T * pT = AllocT();
            *pT = paramT;
            m_StringList.Append(pT);
            return *this;
        }
        bool isEmpty() const
        {
            return  m_StringList.isEmpty();
        }
        bool isNotEmpty() const
        {
            return m_StringList.isNotEmpty();
        }
        //插入一个字符串
        XStringList & Insert(XInt paramIndex, const T & paramT)
        {
            T * pT = AllocT();
            *pT = paramT;
            m_StringList.Insert(paramIndex,pT);
            return *this;
        }
        //删除一个字符串
        XStringList & Remove(XInt paramIndex)
        {
            FreeT( m_StringList[paramIndex] );
            m_StringList.Remove(paramIndex);
            return *this;
        }
        //请除字符串
        void Clear();
        //取字符串的个数
        XInt getLength() const
        {
            return m_StringList.getLength();
        }
        //取指定下标的字符串
        T & operator[](XInt paramIndex)
        {
            return *m_StringList[paramIndex];
        }
        //取指定下标的字符串
        const T & operator[](XInt paramIndex) const
        {
            return *m_StringList[paramIndex];
        }
        //取指定下标的字符串
        T & getString(XInt paramIndex)
        {
            return operator[](paramIndex);
        }
        //取指定下标的字符串
        const T & getString(XInt paramIndex) const
        {
            return operator[](paramIndex);
        }
        //
        XStringList<T> & operator << (const T & paramString)
        {
            return Append( paramString );
        }
        XStringList<T> & operator << (const StringChar * paramString)
        {
            return Append( paramString );
        }

        XStringList<T> & operator ,(const T & paramString)
        {
            return Append( paramString );
        }
        XStringList<T> & operator ,(const StringChar * paramString)
        {
            return Append( paramString );
        }
    private:
        //复制一个字符串列表
        void CopyList(const XStringList<T> & paramList)
        {
            if( &paramList != this)
            {
                Clear();
                for(XInt i = 0; i <paramList.getLength(); i++)
                {
                    Append(paramList[i]);
                }
            }
        }
        //分配一个字符串对象
        T * AllocT()
        {
            return new T();
        }
        //释放一个字符串对象
        void FreeT(T * paramT)
        {
            delete paramT;
        }
    private:
        XDynamicArray<T *> m_StringList;    ///<存放字符串列表的数组
    };
    //-------------------------------------------------------------------------------------
    template<class T>
    void XStringList<T>::Clear()
    {
        for(XInt i = m_StringList.getLastIndex(); i>= 0; i--)
        {
            FreeT( m_StringList[i] );
        }
        m_StringList.Clear();
    }

    namespace zdh_detail
    {
        //-------------------------------------------------------------------------------------
        ///解析命令字符串
        /**
            @return XInt 分析结果
                - 0 表示成功
                - 1 表示转定义符没有定义
                - 2 表示单引号没有完成
                - 3 表示双引号没有完成
                - 4 表示没有可用的命令或参数
         */
        template<class T>
        static XInt ParseCommandLineTemplate(const T & paramCmdLine, XStringList<T> & paramList)
        {
            typedef typename T::StringChar StringChar;  
            typedef typename T::ConstTPointer ConstTPointer;
            const StringChar KEYWORD_CHAR_SAPCE = ' ';
            const StringChar KEYWORD_CHAR_QUATE = '\'';
            const StringChar KEYWORD_CHAR_DOUBLE_QUATE = '\"';
            const StringChar KEYWORD_CHAR_CONVERT = '\\';
            //表示是否是处理转定义符方面 0表示不是，1表示是
            const XInt CONVERT_STATUS_TRUE = 1;
            const XInt CONVERT_STATUS_FALSE = 0;
            /*
            iStatus　0 表示无任何状态
            iStatus  1 表示在'开始的字符串中
            iStatus  2 表示在"开始的字符串中
            iStatus  3 表示非'"开头的字符串
            */
            const XInt PARSE_STATUS_NONE = 0;
            const XInt PARSE_STATUS_QUATE = 1;
            const XInt PARSE_STATUS_DOUBLE_QUATE = 2;
            const XInt PARSE_STATUS_FOUND_WORD = 3;

            XInt iStatus = PARSE_STATUS_NONE;   //字符串解析状态
            XInt iConvert = CONVERT_STATUS_FALSE;   //表示是否是处理转定义符方面 0表示不是，1表示是

            paramList.Clear();
            T tmpString; //临时字符串
            ConstTPointer p = paramCmdLine.c_str();
            XInt iCharLength = paramCmdLine.getLength();
            //依次取出每个字符进行处理
            for(XInt i = 0; i < iCharLength; i++)
            {
                StringChar ch = *p++;
                switch(ch)
                {
                case KEYWORD_CHAR_SAPCE:
                    {
                        if( iConvert == CONVERT_STATUS_TRUE)
                        {
                            switch(iStatus)
                            {
                            case PARSE_STATUS_NONE:
                                iStatus = PARSE_STATUS_FOUND_WORD;
                                tmpString = ch;
                                break;
                            case PARSE_STATUS_QUATE:
                            case PARSE_STATUS_DOUBLE_QUATE:
                            case PARSE_STATUS_FOUND_WORD:
                                tmpString += ch;
                                break;
                            }
                            iConvert = CONVERT_STATUS_FALSE;
                        }
                        else
                        {
                            switch(iStatus)
                            {
                            case PARSE_STATUS_NONE:
                                if( !tmpString.isEmpty() ) 
                                {
                                    tmpString.ToEmptyString();
                                }
                                break;
                            case PARSE_STATUS_QUATE:
                            case PARSE_STATUS_DOUBLE_QUATE:
                                tmpString += ch;
                                break;
                            case PARSE_STATUS_FOUND_WORD:
                                paramList.Append(tmpString);
                                tmpString.ToEmptyString();
                                iStatus = PARSE_STATUS_NONE;
                                break;
                            }
                        }
                    }
                    break;
                case KEYWORD_CHAR_CONVERT:
                    {
                        if( iConvert == CONVERT_STATUS_TRUE )
                        {
                            switch(iStatus)
                            {
                            case PARSE_STATUS_NONE:
                                iStatus = PARSE_STATUS_FOUND_WORD;
                                tmpString = ch;
                                break;
                            case PARSE_STATUS_QUATE:
                            case PARSE_STATUS_DOUBLE_QUATE:
                            case PARSE_STATUS_FOUND_WORD:
                                tmpString += ch;
                                break;
                            }
                            iConvert = CONVERT_STATUS_FALSE;
                        }
                        else
                        {
                            iConvert = CONVERT_STATUS_TRUE;
                        }
                    }
                    break;
                case KEYWORD_CHAR_DOUBLE_QUATE:
                    {
                        if( iConvert == CONVERT_STATUS_TRUE )
                        {
                            switch(iStatus)
                            {
                            case PARSE_STATUS_NONE:
                                iStatus = PARSE_STATUS_FOUND_WORD;
                                tmpString = ch;
                                break;
                            case PARSE_STATUS_QUATE:
                            case PARSE_STATUS_DOUBLE_QUATE:
                            case PARSE_STATUS_FOUND_WORD:
                                tmpString += ch;
                                break;
                            }
                            iConvert = CONVERT_STATUS_FALSE;
                        }
                        else
                        {
                            switch(iStatus)
                            {
                            case PARSE_STATUS_NONE:
                                iStatus = PARSE_STATUS_DOUBLE_QUATE;
                                break;
                            case PARSE_STATUS_DOUBLE_QUATE:
                                iStatus = PARSE_STATUS_NONE; 
                                paramList.Append(tmpString);
                                tmpString.ToEmptyString();
                                break;
                            case PARSE_STATUS_QUATE:
                            case PARSE_STATUS_FOUND_WORD:
                                tmpString += ch;
                                break;
                            }
                            iConvert = CONVERT_STATUS_FALSE;
                        }
                    }
                    break;
                case KEYWORD_CHAR_QUATE:
                    {
                        if( iConvert == CONVERT_STATUS_TRUE )
                        {
                            switch(iStatus)
                            {
                            case PARSE_STATUS_NONE:
                                iStatus = PARSE_STATUS_FOUND_WORD;
                                tmpString = ch;
                                break;
                            case PARSE_STATUS_QUATE:
                            case PARSE_STATUS_DOUBLE_QUATE:
                            case PARSE_STATUS_FOUND_WORD:
                                tmpString += ch;
                                break;
                            }
                            iConvert = CONVERT_STATUS_FALSE;
                        }
                        else
                        {
                            switch(iStatus)
                            {
                            case PARSE_STATUS_NONE:
                                iStatus = PARSE_STATUS_QUATE;
                                break;
                            case PARSE_STATUS_QUATE:
                                iStatus = PARSE_STATUS_NONE; 
                                paramList.Append(tmpString);
                                tmpString.ToEmptyString();
                                break;
                            case PARSE_STATUS_DOUBLE_QUATE:
                            case PARSE_STATUS_FOUND_WORD:
                                tmpString += ch;
                                break;
                            }
                            iConvert = CONVERT_STATUS_FALSE;
                        }
                    }
                    break;
                default:
                    {
                        if( iConvert == CONVERT_STATUS_TRUE)
                        {
                            switch(iStatus)
                            {
                            case PARSE_STATUS_NONE:
                                iStatus = PARSE_STATUS_FOUND_WORD;
                                tmpString = ch;
                                break;
                            case PARSE_STATUS_QUATE:
                            case PARSE_STATUS_DOUBLE_QUATE:
                            case PARSE_STATUS_FOUND_WORD:
                                tmpString += ch;
                                break;
                            }
                            iConvert = CONVERT_STATUS_FALSE;
                        }
                        else
                        {
                            switch(iStatus)
                            {
                            case PARSE_STATUS_NONE:
                                iStatus = PARSE_STATUS_FOUND_WORD;
                                tmpString = ch;
                                break;
                            case PARSE_STATUS_QUATE:
                            case PARSE_STATUS_DOUBLE_QUATE:
                            case PARSE_STATUS_FOUND_WORD:
                                tmpString += ch;
                                break;
                            }
                        }
                        break;
                    }//switch(ch)
                }//for...
            }
            XInt iRet = 0;
            if( !tmpString.isEmpty() )
            {
                paramList.Append(tmpString);
            }
            do
            {
                if ( iConvert == CONVERT_STATUS_TRUE ) 
                {
                    iRet = 1;
                    break;
                }
                if ( tmpString.isEmpty() ) break;
                if ( iStatus == PARSE_STATUS_QUATE ) 
                {
                    iRet = 2;
                    break;
                }
                else if ( iStatus == PARSE_STATUS_DOUBLE_QUATE )
                {
                    iRet = 3;
                    break;
                }
                if( paramList.getLength() == 0 )
                {
                    iRet = 4;
                    break;
                }
            }while(false);

            return iRet;        
        }
        ///指定字符集合分隔字符串
        /**
            @param [in] paramSrc 被分割的字符串
            @param [in] paramSplitCharSet 字符串分割字符集合
            @param [out] paramList 分割后子串列表
            @return XInt 返回分割后子串的个数
         */
        template<class S,class C>
        static XInt SplitStringTemplateByCharSet(const S & paramSrc, const XSet<C> & paramSplitCharSet, XStringList<S> & paramList)
        {
            paramList.Clear();
            
            if( paramSrc.isEmpty() ) 
            {
                return 0;
            }
            
            if( paramSplitCharSet.isEmpty() )
            {
                paramList.Append(paramSrc);
                return paramList.getLength();
            }

            S strTemp;
            for(XInt i = 0; i < paramSrc.getLength(); i++)
            {
                C ch = paramSrc[i];
                if( paramSplitCharSet.Contains(ch) )
                {
                    if( strTemp.isNotEmpty() )
                    {
                        paramList.Append(strTemp);
                        strTemp.ToEmptyString();
                    }
                }
                else
                {
                    strTemp += ch;
                }
            }
            if(strTemp.isNotEmpty())
            {
                paramList.Append(strTemp);
            }
            return paramList.getLength();
        }
        ///指定子串集合分隔字符串
        /**
            @param [in] paramSrc 被分割的字符串
            @param [in] paramSplitStringList 字符串分割字符集合
            @param [out] paramList 分割后子串列表
            @return XInt 返回分割后子串的个数
         */     
        template<class S>
        static XInt SplitStringTemplateByString(const S & paramSrc, const XStringList<S> & paramSplitStringList, XStringList<S> & paramList)
        {
            paramList.Clear();
            if( paramSrc.isEmpty() ) 
            {
                return 0;
            }
            if( paramSplitStringList.isEmpty() )
            {
                paramList.Append(paramSrc);
                return paramList.getLength();
            }
            S strTemp;
            bool bFinish = false;
            XInt iStartPos = 0;
            do
            {
                XInt iMinIndex = -1;
                XInt iMinPos = -1;
                for(XInt i = 0; i < paramSplitStringList.getLength(); i++)
                {
                    XInt iFoundPos = paramSrc.Pos( iStartPos, paramSplitStringList[i] );
                    if( iFoundPos != -1)
                    {
                        if(iMinPos == -1 || iMinPos > iFoundPos )
                        {
                            iMinIndex = i;
                            iMinPos = iFoundPos;
                        }
                    }
                }
                if( iMinPos > 0 ) //如果有找到
                {
                    paramSrc.SubString(iStartPos, iMinPos - iStartPos, strTemp);
                    if( strTemp.isNotEmpty() )
                    {
                        paramList.Append( strTemp );
                        strTemp.ToEmptyString();
                    }                   
                    iStartPos = iMinPos + paramSplitStringList[iMinIndex].getLength();
                }
                else //如果没有找到
                {
                    paramSrc.SubString(iStartPos, paramSrc.getLength(), strTemp);
                    if( strTemp.isNotEmpty() )
                    {
                        paramList.Append( strTemp );
                        strTemp.ToEmptyString();
                    }
                    bFinish = true;
                }
            }while(!bFinish);

            return paramList.getLength();
        }
    }
    ///Parse command line function
    inline XInt ParseCommandLine(const XAnsiString & paramCmdLine, XStringList<XAnsiString> & paramList)
    {
        return zdh_detail::ParseCommandLineTemplate(paramCmdLine, paramList);
    }
    inline XInt ParseCommandLine(const XChar * paramCmdLine, XStringList<XAnsiString> & paramList)
    {
        return zdh_detail::ParseCommandLineTemplate(XAnsiString(paramCmdLine), paramList);
    }
#if defined(OS_WINDOWS)
    inline XInt ParseCommandLine(const XWideString & paramCmdLine, XStringList<XWideString> & paramList)
    {
        return zdh_detail::ParseCommandLineTemplate(paramCmdLine, paramList);
    }

    inline XInt ParseCommandLine(const XWideChar * paramCmdLine, XStringList<XWideString> & paramList)
    {
        return zdh_detail::ParseCommandLineTemplate( XWideString(paramCmdLine) ,paramList);
    }
#endif
    //字符分割
    inline XInt SplitStringByChar(const XChar * paramSrc, XChar paramSplitChar, XStringList<XAnsiString> & paramList)
    {
        XSet<XChar> splitSet;
        splitSet << paramSplitChar;
        return zdh_detail::SplitStringTemplateByCharSet(XAnsiString(paramSrc), splitSet, paramList);
    }
    inline XInt SplitStringByChar(const XChar * paramSrc, const XChar * paramSplitCharSet, XStringList<XAnsiString> & paramList)
    {
        XSet<XChar> splitSet;
        const XChar * p = paramSplitCharSet;
        while(*p)
        {
            splitSet << *p;
            p++;
        }
        return zdh_detail::SplitStringTemplateByCharSet(XAnsiString(paramSrc), splitSet, paramList);
    }
    inline XInt SplitStringByChar(const XChar * paramSrc, const XSet<XChar> & paramSplitCharSet, XStringList<XAnsiString> & paramList)
    {
        return zdh_detail::SplitStringTemplateByCharSet(XAnsiString(paramSrc), paramSplitCharSet, paramList);
    }

    inline XInt SplitStringByChar(const XAnsiString & paramSrc, XChar paramSplitChar, XStringList<XAnsiString> & paramList)
    {
        XSet<XChar> splitSet;
        splitSet << paramSplitChar;
        return zdh_detail::SplitStringTemplateByCharSet(paramSrc, splitSet, paramList);
    }
    inline XInt SplitStringByChar(const XAnsiString & paramSrc, const XChar * paramSplitCharSet, XStringList<XAnsiString> & paramList)
    {
        XSet<XChar> splitSet;
        const XChar * p = paramSplitCharSet;
        while(*p)
        {
            splitSet << *p;
            p++;
        }
        return zdh_detail::SplitStringTemplateByCharSet(XAnsiString(paramSrc), splitSet, paramList);
    }
    inline XInt SplitStringByChar(const XAnsiString & paramSrc, const XSet<XChar> & paramSplitCharSet, XStringList<XAnsiString> & paramList)
    {
        return zdh_detail::SplitStringTemplateByCharSet(XAnsiString(paramSrc), paramSplitCharSet, paramList);
    }


#if defined(OS_WINDOWS)
    //字符分割
    inline XInt SplitStringByChar(const XWideChar * paramSrc, XWideChar paramSplitChar, XStringList<XWideString> & paramList)
    {
        XSet<XWideChar> splitSet;
        splitSet << paramSplitChar;
        return zdh_detail::SplitStringTemplateByCharSet(XWideString(paramSrc), splitSet, paramList);
    }
    inline XInt SplitStringByChar(const XWideChar * paramSrc, const XWideChar * paramSplitCharSet, XStringList<XWideString> & paramList)
    {
        XSet<XWideChar> splitSet;
        const XWideChar * p = paramSplitCharSet;
        while(*p)
        {
            splitSet << *p;
            p++;
        }
        return zdh_detail::SplitStringTemplateByCharSet(XWideString(paramSrc), splitSet, paramList);
    }

    inline XInt SplitStringByChar(const XWideChar * paramSrc, const XSet<XWideChar> & paramSplitCharSet, XStringList<XWideString> & paramList)
    {
        return zdh_detail::SplitStringTemplateByCharSet(XWideString(paramSrc), paramSplitCharSet, paramList);
    }

    inline XInt SplitStringByChar(const XWideString & paramSrc, XWideChar paramSplitChar, XStringList<XWideString> & paramList)
    {
        XSet<XWideChar> splitSet;
        splitSet << paramSplitChar;
        return zdh_detail::SplitStringTemplateByCharSet(paramSrc, splitSet, paramList);
    }
    inline XInt SplitStringByChar(const XWideString & paramSrc, const XWideChar * paramSplitCharSet, XStringList<XWideString> & paramList)
    {
        XSet<XWideChar> splitSet;
        const XWideChar * p = paramSplitCharSet;
        while(*p)
        {
            splitSet << *p;
            p++;
        }
        return zdh_detail::SplitStringTemplateByCharSet(XWideString(paramSrc), splitSet, paramList);
    }
    inline XInt SplitStringByChar(const XWideString & paramSrc, const XSet<XWideChar> & paramSplitCharSet, XStringList<XWideString> & paramList)
    {
        return zdh_detail::SplitStringTemplateByCharSet(XWideString(paramSrc), paramSplitCharSet, paramList);
    }
#endif
    //字符串分割
    inline XInt SplitStringByString(const XAnsiString & paramSrc, const XAnsiString & paramSplitString,XStringList<XAnsiString> & paramList)
    {
        XStringList<XAnsiString> SplitList;
        SplitList.Append( paramSplitString );
        return zdh_detail::SplitStringTemplateByString(paramSrc, SplitList, paramList );
    }
    inline XInt SplitStringByString(const XChar * paramSrc, const XChar * paramSplitString,XStringList<XAnsiString> & paramList)
    {
        XStringList<XAnsiString> SplitList;
        SplitList.Append( paramSplitString );
        return zdh_detail::SplitStringTemplateByString(XAnsiString(paramSrc), SplitList, paramList );
    }

    inline XInt SplitStringByString(const XAnsiString & paramSrc, const XStringList<XAnsiString> & paramSplitString,XStringList<XAnsiString> & paramList)
    {
        return zdh_detail::SplitStringTemplateByString(paramSrc, paramSplitString, paramList );
    }
    inline XInt SplitStringByString(const XChar * paramSrc,const XStringList<XAnsiString> & paramSplitString, XStringList<XAnsiString> & paramList)
    {
        return zdh_detail::SplitStringTemplateByString(XAnsiString(paramSrc), paramSplitString, paramList );
    }
#if defined(OS_WINDOWS)
    inline XInt SplitStringByString(const XWideString & paramSrc, const XWideString & paramSplitString,XStringList<XWideString> & paramList)
    {
        XStringList<XWideString> SplitList;
        SplitList.Append( paramSplitString );
        return zdh_detail::SplitStringTemplateByString(paramSrc, SplitList, paramList );
    }

    inline XInt SplitStringByString(const XWideChar * paramSrc, const XWideChar * paramSplitString,XStringList<XWideString> & paramList)
    {
        XStringList<XWideString> SplitList;
        SplitList.Append( paramSplitString );
        return zdh_detail::SplitStringTemplateByString(XWideString(paramSrc), SplitList, paramList );
    }

    inline XInt SplitStringByString(const XWideString & paramSrc, const XStringList<XWideString> & paramSplitString,XStringList<XWideString> & paramList)
    {
        return zdh_detail::SplitStringTemplateByString(paramSrc, paramSplitString, paramList );
    }
    inline XInt SplitStringByString(const XWideChar * paramSrc,const XStringList<XWideString> & paramSplitString, XStringList<XWideString> & paramList)
    {
        return zdh_detail::SplitStringTemplateByString(XWideString(paramSrc), paramSplitString, paramList );
    }
#endif
}
#endif
