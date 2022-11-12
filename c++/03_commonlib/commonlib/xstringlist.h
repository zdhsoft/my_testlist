#ifndef _X_STRING_LIST_H_
#define _X_STRING_LIST_H_
#include <xstring.h>
#include <xdynamic_array.h>
#include <xset.h>
namespace zdh
{
    //�ַ����б��࣬�ṩ������ַ����б����
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
        //׷��һ���ַ���
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
        //����һ���ַ���
        XStringList & Insert(XInt paramIndex, const T & paramT)
        {
            T * pT = AllocT();
            *pT = paramT;
            m_StringList.Insert(paramIndex,pT);
            return *this;
        }
        //ɾ��һ���ַ���
        XStringList & Remove(XInt paramIndex)
        {
            FreeT( m_StringList[paramIndex] );
            m_StringList.Remove(paramIndex);
            return *this;
        }
        //����ַ���
        void Clear();
        //ȡ�ַ����ĸ���
        XInt getLength() const
        {
            return m_StringList.getLength();
        }
        //ȡָ���±���ַ���
        T & operator[](XInt paramIndex)
        {
            return *m_StringList[paramIndex];
        }
        //ȡָ���±���ַ���
        const T & operator[](XInt paramIndex) const
        {
            return *m_StringList[paramIndex];
        }
        //ȡָ���±���ַ���
        T & getString(XInt paramIndex)
        {
            return operator[](paramIndex);
        }
        //ȡָ���±���ַ���
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
        //����һ���ַ����б�
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
        //����һ���ַ�������
        T * AllocT()
        {
            return new T();
        }
        //�ͷ�һ���ַ�������
        void FreeT(T * paramT)
        {
            delete paramT;
        }
    private:
        XDynamicArray<T *> m_StringList;    ///<����ַ����б������
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
        ///���������ַ���
        /**
            @return XInt �������
                - 0 ��ʾ�ɹ�
                - 1 ��ʾת�����û�ж���
                - 2 ��ʾ������û�����
                - 3 ��ʾ˫����û�����
                - 4 ��ʾû�п��õ���������
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
            //��ʾ�Ƿ��Ǵ���ת��������� 0��ʾ���ǣ�1��ʾ��
            const XInt CONVERT_STATUS_TRUE = 1;
            const XInt CONVERT_STATUS_FALSE = 0;
            /*
            iStatus��0 ��ʾ���κ�״̬
            iStatus  1 ��ʾ��'��ʼ���ַ�����
            iStatus  2 ��ʾ��"��ʼ���ַ�����
            iStatus  3 ��ʾ��'"��ͷ���ַ���
            */
            const XInt PARSE_STATUS_NONE = 0;
            const XInt PARSE_STATUS_QUATE = 1;
            const XInt PARSE_STATUS_DOUBLE_QUATE = 2;
            const XInt PARSE_STATUS_FOUND_WORD = 3;

            XInt iStatus = PARSE_STATUS_NONE;   //�ַ�������״̬
            XInt iConvert = CONVERT_STATUS_FALSE;   //��ʾ�Ƿ��Ǵ���ת��������� 0��ʾ���ǣ�1��ʾ��

            paramList.Clear();
            T tmpString; //��ʱ�ַ���
            ConstTPointer p = paramCmdLine.c_str();
            XInt iCharLength = paramCmdLine.getLength();
            //����ȡ��ÿ���ַ����д���
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
        ///ָ���ַ����Ϸָ��ַ���
        /**
            @param [in] paramSrc ���ָ���ַ���
            @param [in] paramSplitCharSet �ַ����ָ��ַ�����
            @param [out] paramList �ָ���Ӵ��б�
            @return XInt ���طָ���Ӵ��ĸ���
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
        ///ָ���Ӵ����Ϸָ��ַ���
        /**
            @param [in] paramSrc ���ָ���ַ���
            @param [in] paramSplitStringList �ַ����ָ��ַ�����
            @param [out] paramList �ָ���Ӵ��б�
            @return XInt ���طָ���Ӵ��ĸ���
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
                if( iMinPos > 0 ) //������ҵ�
                {
                    paramSrc.SubString(iStartPos, iMinPos - iStartPos, strTemp);
                    if( strTemp.isNotEmpty() )
                    {
                        paramList.Append( strTemp );
                        strTemp.ToEmptyString();
                    }                   
                    iStartPos = iMinPos + paramSplitStringList[iMinIndex].getLength();
                }
                else //���û���ҵ�
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
    //�ַ��ָ�
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
    //�ַ��ָ�
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
    //�ַ����ָ�
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
