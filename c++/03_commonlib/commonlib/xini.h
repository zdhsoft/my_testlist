#ifndef _X_INI_H_
#define _X_INI_H_
#include <xconfig.h>
#include <xdynamic_array.h>
#include <xstring.h>
#include <xstringlist.h>
#include <xtinyxml.h>
#include <fstream>
#include <iostream>
#include <string>

/*
    这个文件供了基于text和xml的配置文件读写。两者实现的功能一样。
    下面针对具体格式的说明示例
    xml格式的示例:
    <?xml version="1.0" encoding="GB2312" standalone="yes" ?>
    <ini version="1.0">
        <section name="bbbbb" />
        <section name="test">
            <text value="这是一个空行" />
            <entry name="test3" value="ttttttttttttttt" />
            <entry name="aaaaa" value="空行后面" />
            <entry name="test1" value="" comment="这是一个测试" />
            <text value="这是一个空行" />
            <text value="这是一个空行" />
            <text value="这是一个空行" />
            <text value="这是一个空行" />
            <text value="这是一个空行" />
            <text value="这是一个空行" />
        </section>
        <section name="aaaaaa" />
    </ini>
    下面是文本格式示例:
    #这是一个示例文件
    #这个读取写是全新开发

    [system] #这个是系统配置
    listen_port = 3366      #侦听端口
    listen_ip = 192.168.1.1 #侦听的IP地址
    [db]    #这是数据库相关信息
    ConnectionString = .....
    username=sa
    password=12345
    
    基于xml与text的操作方法完全一样
    
    XIniXML inia("...");
    inia.Load();
    int iPort = inia.ReadInt("system","listen_port","");
    XAnsiString strIP = inia.ReadString("system","listen_ip","0.0.0.0");

    XIniText inib("...");
    inib.Load();
    int iPort = inib.ReadInt("system","listen_port","");
    XAnsiString strIP = inib.ReadString("system","listen_ip","0.0.0.0");
 */
namespace zdh
{
    //----------------------------------------------------------------------------------------
    enum EIniEntryType ///<配置文件条目的类型
    {
        EIET_TEXT_LINE = 1,     ///<非条目文本行
        EIET_COMMON_ENTRY = 2,  ///<普通条目
        EIET_SECTION = 3,       ///<段名称
        EIET_HEAD_LIST = 4,     
        EIET_FOCRE_DWORD = 0x7fffffff
    };
    enum EIniFileType   ///<配置文件类型
    {
        EIFT_XML,       ///<基于XML的
        EIFT_TEXT,      ///<基于文本的
        EIFT_FOCRE_DWORD = 0x7fffffff
    };

    
    //----------------------------------------------------------------------------------------
    //基本XML的配置文件读写实现
    namespace xmlini
    {
        ///XML条目基类
        class XMLIniEntry
        {
        public:
            XMLIniEntry(){}
            virtual ~XMLIniEntry(){}
            ///取类条目的类型
            /**
                @see EIniEntryType
             */
            virtual EIniEntryType getEntryType() const = 0;
        };
        ///XML通用条目
        template<class T>
        class XMLIniEntryCommon : public XMLIniEntry
        {
        public:
            XMLIniEntryCommon() 
            {}
            ///取类条目的类型
            /**
            @return XIET_COMMON_ENTRY
            @see EIniEntryType
            */
            EIniEntryType getEntryType() const 
            { 
                return EIET_COMMON_ENTRY; 
            }
            ///取条目的名称Key
            /**
                @return 返回条目的名称Key
            */
            const T & getKey() const { return m_Key; }
            ///取条目的值
            /**
            @return 返回条目的值
            */
            const T & getValue() const { return m_Value; }
            ///设置条目的名称Key
            /**
                @param [in] paramKey 条目的名称Key
            */
            bool setKey(const T & paramKey) 
            { 
                T strKey;
                paramKey.Trim(strKey);

                if( strKey.isEmpty() ) 
                {
                    return false; //如果Key为空,则返回
                }
                else
                {
                    m_Key = strKey;
                    return true;
                }
            }
            ///设置条目的值
            /**
                @param [in] paramValue 条目的值
            */
            bool setValue(const T & paramValue) 
            { 
                paramValue.Trim(m_Value);
                return true;
            }
            ///设置条目的值
            /**
                @param [in] paramKey 条目的名称Key
                @param [in] paramValue 条目的值
            */
            bool setValue(const T & paramKey,const T & paramValue) 
            {
                return setKey(paramKey) && setValue(paramValue);
            }
            ///取当前条目的注释
            const T & getComment() const
            {
                return m_Comment;
            }
            ///取当前条目的注释
            void setComment(const T & paramComment)
            {
                m_Comment = paramComment;
            }

        private:
            T m_Key;            ///<条目的名称Key
            T m_Value;          ///<条目的值
            T m_Comment;        ///<注释
        };

        ///配置文件开始前的文本行列表
        template<class T>
        class XMLIniHeadList
        {
        public:
            XMLIniHeadList(){}
            ~XMLIniHeadList() { Clear(); }
            ///清除所有文本行
            void Clear()
            {
                for(XInt i = 0; i < m_List.getLength(); i++)
                {
                    delete m_List[i];
                }
                m_List.Clear();
            }
            ///追加一个文本
            void AppendText(const T & paramText)
            {
                T * pText = new T(paramText);
                m_List.Append(pText);
            }
            ///插入一个文本
            void InsertText(XInt paramIndex, const T & paramText)
            {
                T * pText = new T(paramText);
                m_List.Insert(paramIndex, pText);
            }
            ///删除一个文本
            bool RemoveText(XInt paramIndex)
            {
                if( m_List.isValidIndex(paramIndex) )
                {
                    delete m_List[paramIndex];
                    m_List.Remove(paramIndex);
                    return true;
                }
                return false;
            }
            ///取文本行的行数
            XInt getTextCount() const
            {
                return m_List.getLength();
            }
            ///取指定下标的文本
            T & getText(XInt paramIndex) 
            {
                return *m_List[paramIndex];
            }
            const T & getText(XInt paramIndex)const
            {
                return *m_List[paramIndex];
            }

        private:
            XDynamicArray<T *> m_List;  ///文本列表数组
        };
        //----------------------------------------------------------------------------------------
        ///配置文件行条目
        /**
            记录一些文本说明
         */
        template<class T>
        class XMLIniEntryTextLine : public XMLIniEntry
        {
        public:
            XMLIniEntryTextLine() {}
            ~XMLIniEntryTextLine() {}
            ///取类条目的类型
            /**
                @return EIET_TEXT_LINE
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const { return EIET_TEXT_LINE; }
            ///取文本行的内容
            const T & getText() const
            {
                return m_Text;
            }
            ///设置文本行的内容
            void setText(const T & paramText)
            {
                m_Text = paramText;
            }
        private:
            T m_Text;   ///<文本行的内容
        };

        //----------------------------------------------------------------------------------------
        ///配置文件的段类
        template<class T>
        class XMLIniSection : public XMLIniEntry
        {
        public:
            XMLIniSection()
            {}
            virtual ~XMLIniSection() 
            { 
                Clear();
            }
            ///取类条目的类型
            /**
                @return EIET_SECTION
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const { return EIET_SECTION; }
            ///取段名
            /**
                @return 返回段名
             */
            const T & getSectionName() const 
            { 
                return m_SectionName; 
            }
            ///设置段名
            /**
                @param [in] paramSectionName 设置的段名
            */
            void setSectionName(const T & paramSectionName) 
            { 
                m_SectionName = paramSectionName; 
            }
            ///取条目的个数
            /**
                @return 返回条目的个数
            */
            XInt getLength() const 
            { 
                return m_ArrayEntry.getLength(); 
            }
            ///取指定下标的条目
            /**
                @param [in] paramIndex 指定的下标
                @return 返回指定下标的条目指针
             */
            XMLIniEntry * getEntry(XInt paramIndex) 
            { 
                return m_ArrayEntry[paramIndex]; 
            }
            ///取指定名称的条目
            /**
                @param [in] paramIdent 指定的条目名称
                @return 如果该条目存在，则返回条目的指针，否则返回NULL
            */
            XMLIniEntryCommon<T> * getEntry(const T & paramIdent)
            {
                for(XInt i = m_ArrayEntry.getLength()-1; i>=0; i--)
                {
                    XMLIniEntryCommon<T> * pEntry = dynamic_cast<XMLIniEntryCommon<T> *>(m_ArrayEntry[i]);
                    if( pEntry != NULL && pEntry->getKey() == paramIdent) 
                    {
                        return pEntry;
                    }
                }
                return NULL;
            }
            ///在最后插入条目
            /**
                @param [in] paramEntry 被插入的条目
             */
            void AppendEntry(XMLIniEntry * paramEntry) 
            { 
                m_ArrayEntry.Append(paramEntry); 
            }
            ///指定位置插入条目
            /**
                @param [in] paramIndex 指定的位置
                @param [in] paramEntry 被插入的条目
             */
            void InsertEntry(XInt paramIndex,XMLIniEntry * paramEntry) 
            { 
                m_ArrayEntry.Insert(paramIndex,paramEntry); 
            }
            ///删除指定的条目
            bool Remove(const T & paramIdent)
            {
                for(XInt i = m_ArrayEntry.getLastIndex(); i >= 0; i--)
                {
                    XMLIniEntryCommon<T> * pEntry = dynamic_cast<XMLIniEntryCommon<T> *>(m_ArrayEntry[i]);
                    if( pEntry != NULL && pEntry->getKey() == paramIdent) 
                    {
                        delete pEntry;
                        m_ArrayEntry.Remove(i);
                        return true;
                    }
                }
                return false;
            }
            ///清除所有的条目
            void Clear()
            {
                for(XInt i=m_ArrayEntry.getLastIndex(); i >= 0; i--)
                {
                    delete m_ArrayEntry[i];
                }
                m_ArrayEntry.Clear();
            }   
            ///属性comment
            void setComment(const T & paramComment)
            {
                m_Comment = paramComment;
            }
            const T & getComment() const
            {
                return m_Comment;
            }
        private:
            T m_SectionName;                    ///<段名称
            T m_Comment;                        ///<注释
            XDynamicArray<XMLIniEntry *>m_ArrayEntry; ///<条目数组
        };
        ///XML 读写实现
        template<class T>
        class XMLIni
        {
        public:
            XMLIni() {}
            ///带配置文件名的构造函数
            /**
                @param [in] aFileName 初始的配置文件名
            */
            XMLIni(const T & paramFileName)
                :m_FileName(paramFileName)
            {}
            ///板构函数
            ~XMLIni() 
            { 
                Clear(); 
            }
            ///取所有section的个数
            XInt getSectionCount() const
            {
                return m_ArraySection.getLength();
            }       
            ///取指定下标的section
            /**
                @param [in] paramIndex 指定的下标
                @return XMLIniSection * 返回指定的section
                    - NULL 表示下标越界，未取得指定下标的section
                    - != NULL 表示取到了指定下标的section
             */
            XMLIniSection<T> * getSection( XInt paramIndex )
            {
                if( m_ArraySection.isValidIndex(paramIndex) )
                {
                    return m_ArraySection[paramIndex];
                }
                else
                {
                    return NULL;
                }
            }

            ///取指定名称的section
            /**
                取指定section名称的section
                @param [in] paramSectionName
                @return XMLIniSection * 返回section
                    - NULL 表示未找该名称的section
                    - != NULL 表示找到了section
             */
            XMLIniSection<T> * getSection( const T & paramSectionName )
            {
                for(XInt i=m_ArraySection.getLastIndex(); i>= 0; i--)
                {
                    if( m_ArraySection[i]->getSectionName() == paramSectionName ) 
                    {
                        return m_ArraySection[i];
                    }
                }
                return NULL;
            }

        ///删除指定下标的section
            /**
                删除指定下标的section
                @param [in] paramIndex 指定的下标，有效值在[0,getSectionCount)之间
                @return bool 删除结果
                    - true 表示删除成功
                    - false 表示删除失败
             */
            bool RemoveSection( XInt paramIndex )
            {
                if( m_ArraySection.isValidIndex(paramIndex ) )
                {
                    delete m_ArraySection[paramIndex];
                    m_ArraySection.Remove(paramIndex);
                    return true;
                }
                else return false;
            }
            ///删除指定名称的section
            /**
                删除指定section名称的section
                @param [in] paramSectionName 指定section的名称
                @return bool 删除的结果
                    - true 表示删除成功
                    - false 表示删除失败
             */
            bool RemoveSection( const T & paramSectionName )
            {
                for(XInt i=m_ArraySection.getLastIndex(); i>= 0; i--)
                {
                    if( m_ArraySection[i]->getSectionName() == paramSectionName ) 
                    {
                        return RemoveSection(i);
                    }
                }
                return false;
            }
            ///追加一个section 
            /**
                在section表的最后插入一个section，如果该section已经存在，则不插入
                @param [in] paramSectionName 插入section的名称
                @return XMLIniSection * 返回插入的section对象指针
             */     
            XMLIniSection<T> * AppendSection( const T & paramSectionName )
            {
                XMLIniSection<T> * pSection = getSection(paramSectionName);
                if( pSection == NULL )
                {
                    pSection = new XMLIniSection<T>();
                    pSection->setSectionName(paramSectionName);
                    m_ArraySection.Append( pSection );
                }
                return pSection;
            }
            ///插入一个section
            /**
                在指定的下标的位置，插入一个section,如果该section已经存在，则不插入。
                如果指定的下标不是[0,getSectionCount)之间，则在最后追加一个section
                @param [in] paramSectionName 插入section的名称
                @param [in] paramSectionIndex 插入的位置
                @return XMLIniSection * 返回插入的section对象指针
             */
            XMLIniSection<T> * InsertSection( const T & paramSectionName,XInt paramSectionIndex ) 
            {
                XMLIniSection<T> * pSection = getSection(paramSectionName);
                if( pSection == NULL )
                {
                    pSection = new XMLIniSection<T>();
                    pSection->setSectionName(paramSectionName);

                    if( m_ArraySection.isValidIndex(paramSectionIndex)) 
                    {
                        m_ArraySection.Insert(paramSectionIndex,pSection);
                    }
                    else m_ArraySection.Append(pSection);
                }
                return pSection;
            }
            //配置文件的基本接口
            ///读取XInt类型的配置
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramDefault 缺省值
                @return 如果没有找到指定的条目，则返回缺省值
             */
            XInt ReadInt(const T & paramSectionName,const T & paramIdent,XInt paramDefault) 
            {
                XMLIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent);
                if( pEntry == NULL ) 
                {
                    return paramDefault;
                }
                else  
                {
                    return pEntry->getValue().ToIntDef(paramDefault);
                }
            }
            ///读取Bool类型的配置
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramDefault 缺省值
                @return 如果没有找到指定的条目，则返回缺省值
            */
            bool ReadBool(const T & paramSectionName,const T & paramIdent,bool paramDefault) 
            {
                return ReadInt(paramSectionName, paramIdent, paramDefault?1:0) != 0;
            }
            ///读取string类型的配置
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramDefault 缺省值
                @return 如果没有找到指定的条目，则返回缺省值
            */      
            const T & ReadString(const T & paramSectionName,const T & paramIdent,const T & paramDefault )
            {
                const XMLIniEntryCommon<T> * pEntry = getEntry(paramSectionName, paramIdent);
                if( pEntry == NULL ) 
                {
                    return paramDefault;
                }
                else 
                {
                    return pEntry->getValue();
                }
            }
            ///读取指定条目的注释
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @return 如果没有,则返回空串
            */  
            const T & ReadComment(const T & paramSectionName,const T & paramIdent)
            {
                const XMLIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent);
                if( pEntry == NULL ) 
                {
                    return T::EmptyString();
                }
                else 
                {
                    return pEntry->getComment();
                }
            }
            ///写入指定条目的注释
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramComment 注释
            */
            void WriteComment(const T & paramSectionName, const T & paramIdent, const T & paramComment)
            {
                XMLIniEntryCommon <T>* pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->setComment(paramComment);
            }
            ///追加一个文本行
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramText 文本内容
             */
            void AppendText(const T & paramSectionName, const T & paramText = "")
            {
                XMLIniSection<T> * pSection = getSection(paramSectionName,true);
                XMLIniEntryTextLine<T> *pEntry = new XMLIniEntryTextLine<T>();
                pEntry->setText(paramText);
                pSection->AppendEntry(pEntry);
            }
            ///写入一个指定的XInt类型条目
            /**
                如果指定的条目不存，则会创建该条目
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramValue 条目值
             */
            void WriteInt(const T & paramSectionName,const T & paramIdent,XInt paramValue)
            {
                XMLIniEntryCommon<T> * pEntry = getEntry(paramSectionName, paramIdent, true);
                //T strValue = paramValue;
                pEntry->setValue(paramValue);
            }
            ///写入一个指定的Bool类型条目
            /**
                如果指定的条目不存，则会创建该条目
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramValue 条目值
            */
            void WriteBool(const T & paramSectionName,const T &paramIdent,bool paramValue)
            {
                XMLIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->setValue(paramValue?1:0);
            }
            ///写入一个指定的String类型条目
            /**
                如果指定的条目不存，则会创建该条目
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramValue 条目值
            */
            void WriteString(const T & paramSectionName,const T &paramIdent,const T & paramValue)
            {
                XMLIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->setValue(paramValue);
            }
            ///删除指定的条目
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
            */
            bool Remove(const T & paramSectionName,const T & paramIdent)
            {
                XMLIniSection<T> * pSection = getSection(paramSectionName);
                if( pSection != NULL ) 
                {
                    return pSection->Remove(paramIdent);
                }
                return false;
            }
            ///清除所有的条目和段
            void Clear()
            {
                for(XInt i=m_ArraySection.getLength()-1; i>= 0; i--)
                {
                    delete m_ArraySection[i];
                }
                m_ArraySection.Clear();
                m_HeadList.Clear();
            }       
            ///判断指定条目是否存在
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @return 返回条目存在情况
                    - true 表示条目存在
                    - false 表示条目不存在
            */
            bool isExists(const T & paramSectionName,const T & paramIdent) const
            {
                return getEntry(paramSectionName,paramIdent) != NULL;
            }
            ///装载配置
            bool Load();
            bool Load(const T & paramFileName)
            {
                setFileName(paramFileName);
                return Load();
            }
            ///保存配置
            bool Save();
            bool Save(const T & paramFileName)
            {
                setFileName(paramFileName);
                return Save();
            }
            ///设置配置文件名
            /**
                @param [in] paramFileName 指定的配置文件名称
            */
            void setFileName(const T & paramFileName) 
            { 
                m_FileName = paramFileName; 
            }
            ///取配置文件名
            /**
                @return 返回配置文件名
             */
            const T  & getFileName() const 
            { 
                return m_FileName; 
            }
            ///取一个指定段名和名称的条目
            /**
                @param [in] paramSectionName 指定的段名
                @param [in] paramIdent 指定的条目名称
                @return 返回取得的结果
                    - !=NULL 返回对应条目的指针
                    - NULL 表示未找到相应的条相
             */
            XMLIniEntryCommon<T> * getEntry(const T & paramSectionName,const T & paramIdent) 
            {
                XMLIniSection<T> * pSection = getSection(paramSectionName);
                if( pSection != NULL )
                {
                    return pSection->getEntry(paramIdent);
                }
                return NULL;
            }
            ///取一个普通的条目
            /**
                取一个指定段名和名称的条目，如果条目不存在的话，是否要自己插入一个
                @param [in] paramSectionName 指定的段名
                @param [in] paramIdent 指定的条目名称
                @param [in] paramAutoInsert 是否自动插入
                    - true 表示条目不存在的话，就自动插入一个条目
                    - false 表示条目不存在的话，不自动插入
                @return 返回取得的结果
                    - !=NULL 返回对应条目的指针
                    - NULL 表示未找到相应的条相
             */
            XMLIniEntryCommon<T> * getEntry(const T & paramSectionName,const T & paramIdent,bool paramAutoInsert)
            {
                XMLIniSection<T> * pSection = getSection(paramSectionName, paramAutoInsert);
                if( pSection != NULL )
                {
                    XMLIniEntryCommon<T> * pEntry = pSection->getEntry(paramIdent);
                    if( pEntry == NULL && paramAutoInsert)
                    {
                        pEntry = new XMLIniEntryCommon<T>();
                        pEntry->setKey(paramIdent);
                        pSection->AppendEntry(pEntry);
                    }
                    return pEntry;
                }
                return NULL;
            }
            ///取一个指定段名的section
            /**
                取一个指定段名的section，如果section不存在的话，是否要自己插入一个
                @param [in] paramSectionName 指定的段名
                @param [in] paramAutoInsert 是否自动插入
                    - true 表示section不存在的话，就自动插入一个section
                    - false 表示section不存在的话，不自动插入
                @return 返回取得的结果
                    - !=NULL 返回对应条目的指针
                    - NULL 表示未找到相应的条相
             */
            XMLIniSection<T> * getSection(const T & paramSectionName,bool paramAutoInsert)
            {
                for(XInt i = m_ArraySection.getLength()-1; i>= 0; i--)
                {
                    if( m_ArraySection[i]->getSectionName() == paramSectionName ) 
                    {
                        return m_ArraySection[i];
                    }
                }
                if( paramAutoInsert )
                {
                    XMLIniSection<T> * pSection = new XMLIniSection<T>();
                    pSection->setSectionName(paramSectionName);
                    m_ArraySection << pSection;
                    return pSection;
                }
                else return NULL;
            }
            ///取配置文件开始前的文本行列表
            XMLIniHeadList<T> * getHeadList() 
            {
                return &m_HeadList;
            }
        private:
            XDynamicArray<XMLIniSection<T> *>m_ArraySection; ///条目段数组
            T m_FileName;                           ///<配置文件名
            XMLIniHeadList<T> m_HeadList;
        };
        ///装载内容
        template<class T>
        bool XMLIni<T>::Load()
        {
            Clear();

            TiXmlDocument doc;
            if(!doc.LoadFile(getFileName()))
            {
                //装载失败
                return false;
            }
            else
            {
                TiXmlElement * elemRoot = doc.FirstChildElement("ini");
                if( elemRoot != NULL )
                {
                    TiXmlElement * elemHeadList = elemRoot->FirstChildElement("headlist");
                    if( elemHeadList != NULL )
                    {
                        TiXmlElement * elemText = elemHeadList->FirstChildElement("text");
                        while(elemText != NULL)
                        {
                            const XChar * pText = elemText->Attribute("value");
                            if( pText != NULL )
                            {
                                getHeadList()->AppendText(pText);
                            }
                            else
                            {
                                getHeadList()->AppendText("");
                            }
                            elemText = elemText->NextSiblingElement("text");
                        }
                    }
                    TiXmlElement * elemSection = elemRoot->FirstChildElement("section");
                    while(elemSection != NULL)
                    {
                        const char * pName = elemSection->Attribute("name");
                        if( pName != NULL )
                        {

                            XMLIniSection<T> * pSection = getSection(pName,true);
                            TiXmlElement * elemEntry = elemSection->FirstChildElement();
                            while( elemEntry != NULL )
                            {
                                if( elemEntry->ValueStr() == "entry" )
                                {
                                    pName = elemEntry->Attribute("name");
                                    if( pName != NULL )
                                    {
                                        XMLIniEntryCommon<T> * pEntry = new XMLIniEntryCommon<T>();
                                        pEntry->setValue(pName,elemEntry->Attribute("value"));
                                        const XChar * pComment = elemEntry->Attribute("comment");
                                        if( pComment != NULL ) 
                                        {
                                            pEntry->setComment(pComment);
                                        }
                                        pSection->AppendEntry(pEntry);
                                    }
                                }
                                else if( elemEntry->ValueStr() == "text" )
                                {
                                    XMLIniEntryTextLine<T> * pEntry = new XMLIniEntryTextLine<T>();
                                    const XChar * pText = elemEntry->Attribute("value");
                                    if( pText != NULL )
                                    {
                                        pEntry->setText( pText );
                                    }
                                    pSection->AppendEntry( pEntry );
                                }
                                elemEntry = elemEntry->NextSiblingElement();
                            }
                        }
                        elemSection = elemSection->NextSiblingElement("section");
                    }
                }
            }
            return true;
        }
        ///保存内容
        template<class T>
        bool XMLIni<T>::Save()
        {
            TiXmlDocument doc;
            TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "GB2312", "yes" );
            doc.LinkEndChild( decl );
            TiXmlElement * elemRoot = new TiXmlElement("ini");
            doc.LinkEndChild( elemRoot );
            elemRoot->setStringAttrib("version","1.0");
            if( getHeadList()->getTextCount() > 0)
            {
                TiXmlElement * elemHeadList = elemRoot->AppendChildElement("headlist");
                for(int i = 0; i < getHeadList()->getTextCount(); i++)
                {
                    TiXmlElement * elemText = elemHeadList->AppendChildElement("text");
                    elemText->setStringAttrib("value", getHeadList()->getText(i));
                }
            }
            for(XInt i=0; i < getSectionCount(); i++) //遍历所有的段
            {
                XMLIniSection<T> * pSection = getSection(i);
                TiXmlElement * elemSection = elemRoot->AppendChildElement("section");
                elemSection->setStringAttrib("name",pSection->getSectionName());
                for(XInt j=0; j<pSection->getLength(); j++) //遍历所有的条目
                {
                    XMLIniEntry * pE = pSection->getEntry(j);
                    switch(pE->getEntryType())
                    {
                    case EIET_COMMON_ENTRY:
                        {
                            XMLIniEntryCommon<T> * pEntry = (XMLIniEntryCommon<T> *)pE;

                            TiXmlElement * elemEntry = elemSection->AppendChildElement("entry"); // XXMLTools::AppendChildElement(elemSection,"entry");
                            elemEntry->setStringAttrib("name",pEntry->getKey());
                            elemEntry->setStringAttrib("value",pEntry->getValue());
                            if( pEntry->getComment().isNotEmpty() )
                            {
                                elemEntry->setStringAttrib("comment",pEntry->getComment());
                            }
                        }
                        break;
                    case EIET_TEXT_LINE:
                        {
                            XMLIniEntryTextLine<T> * pEntry = (XMLIniEntryTextLine<T> *)pE;

                            TiXmlElement * elemEntry = elemSection->AppendChildElement("text"); // XXMLTools::AppendChildElement(elemSection,"entry");
                            if( pEntry->getText().isNotEmpty() )
                            {
                                elemEntry->setStringAttrib("value",pEntry->getText());
                            }
                        }
                        break;
                    }
                }
            }
            return doc.SaveFile(getFileName());
        }
    } //end of namespace xmlini
    namespace txtini
    {
        ///基本文本的ini实现
        const XInt INI_INVALID_POS = -1;    ///<无效的POS

        ///文本条目的基类
        template<class T>
        class TXTIniEntry
        {
        public:
            TXTIniEntry()
                :m_HasOriginal(false)
            {}
            virtual ~TXTIniEntry(){}
            ///取类条目的类型
            /**
                @see EIniEntryType
             */
            virtual EIniEntryType getEntryType() const = 0;
            ///取原始文本
            const T & getOriginalText() const 
            {
                return m_OriginalText;
            }
            T & getOriginalText() 
            {
                return m_OriginalText;
            }
            ///设置原始文本
            void setOriginalText(const T & paramOriginalText)
            {
                m_OriginalText = paramOriginalText;
            }
            ///Original标志属性
            bool isHasOriginal() const
            {
                return m_HasOriginal;
            }
            void setHasOriginal(bool paramFlag)
            {
                m_HasOriginal = paramFlag;
            }
            ///生成条目行
            virtual T & BuildLine(T & paramResult)
            {
                paramResult = m_OriginalText;
                return paramResult;
            }
        private:
            T m_OriginalText;       ///原始的文本行
            bool m_HasOriginal;     ///<是否存在原始文本行
        };
        ///配置文件开始前的文本行列表
        template<class T>
        class TXTIniHeadList
        {
        public:
            TXTIniHeadList(){}
            ~TXTIniHeadList() 
            { 
                Clear(); 
            }
            ///清除所有文本行
            void Clear()
            {
                for(XInt i = 0; i < m_List.getLength(); i++)
                {
                    delete m_List[i];
                }
                m_List.Clear();
            }
            ///追加一个文本
            void AppendText(const T & paramText)
            {
                T * pText = new T(paramText);
                m_List.Append(pText);
            }
            ///插入一个文本
            void InsertText(XInt paramIndex, const T & paramText)
            {
                T * pText = new T(paramText);
                m_List.Insert(paramIndex, pText);
            }
            ///删除一个文本
            bool RemoveText(XInt paramIndex)
            {
                if( m_List.isValidIndex(paramIndex) )
                {
                    delete m_List[paramIndex];
                    m_List.Remove(paramIndex);
                    return true;
                }
                return false;
            }
            ///取文本行的行数
            XInt getTextCount() const
            {
                return m_List.getLength();
            }
            ///取指定下标的文本
            T & getText(XInt paramIndex) 
            {
                return *m_List[paramIndex];
            }
            const T & getText(XInt paramIndex)const
            {
                return *m_List[paramIndex];
            }

        private:
            XDynamicArray<T *> m_List;  ///<文本行列表
        };
        ///条目中的字段类
        /**
            主要包括两个内容，一个是条目的字段内容，一个是字段内容所有的位置
         */
        template<class T>
        class TXTField
        {
        public:
            TXTField()
                :m_Pos(INI_INVALID_POS)
            {}
            ///属性Field
            const T & getField() const
            {
                return m_Field;
            }
            void setField(const T & paramField)
            {
                m_Field = paramField;
            }
            ///属性pos
            XInt getPos() const
            {
                return m_Pos;
            }
            void setPos(XInt paramPos)
            {
                m_Pos = paramPos;
            }
        private:
            XInt m_Pos;     ///<位置
            T m_Field;      ///<字段内容
        };
        ///文本通用条目
        template<class T>
        class TXTIniEntryCommon : public TXTIniEntry<T>
        {
        public:
                typedef TXTIniEntry<T> Inherited;
        public:
            TXTIniEntryCommon() 
            {}
            ///取类条目的类型
            /**
                @return XIET_COMMON_ENTRY
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const 
            { 
                return EIET_COMMON_ENTRY; 
            }
            ///取条目的名称Key
            /**
                @return 返回条目的名称Key
            */
            TXTField<T> & getKey() 
            { 
                return m_Key; 
            }
            ///取条目的值
            /**
                @return 返回条目的值
            */
            TXTField<T> & getValue() 
            { 
                return m_Value; 
            }
            ///取当前条目的注释
            TXTField<T> & getComment() 
            {
                return m_Comment;
            }
            ///改变值
            void ChangeValue(const T & paramValue)
            {
                if( Inherited::isHasOriginal() )
                {
                    ZDH_ASSERT(m_Value.getPos() >= 0);
                    T & strOri = Inherited::getOriginalText();
                    if( m_Comment.getPos() != INI_INVALID_POS )
                    {
                        m_Comment.setPos( m_Comment.getPos() + paramValue.getLength() - m_Value.getField().getLength() );
                    }
                    if( m_Value.getField().isNotEmpty() )
                    {
                        strOri.ReplaceString(m_Value.getPos(), m_Value.getField(), paramValue, 1);
                    }
                    else
                    {
                        strOri.InsertString(m_Value.getPos(), paramValue);
                    }
                    
                    m_Value.setField( paramValue );
                }
                m_Value.setField(paramValue);
            }
            ///改为注释
            void ChangeComment(const T & paramComment)
            {
                T strTemp;
                if( paramComment.isNotEmpty()) //如果不是为空
                {
                    if( !(paramComment[0] == ';' || paramComment[0]== '#') )
                    {
                        strTemp << '#' << paramComment;
                    }
                    else
                    {
                        strTemp = paramComment;
                    }
                }

                if( Inherited::isHasOriginal() )
                {
                    T & strOri = Inherited::getOriginalText();
                    if( strTemp.isEmpty() ) //如果是空串，则删除注释
                    {
                        if( m_Comment.getPos() != INI_INVALID_POS )
                        {
                            strOri.RemoveString(m_Comment.getPos(),m_Comment.getField());
                        }
                        m_Comment.setField(strTemp);
                        m_Comment.setPos(INI_INVALID_POS);
                    }
                    else
                    {
                        if( m_Comment.getPos() == INI_INVALID_POS ) //如果就没有注释
                        {
                            if( strOri.isNotEmpty() )
                            {
                                typename T::StringChar ch = strOri[strOri.getLength()-1];
                                if( ch == ' ' || ch == '\t' )
                                {
                                    m_Comment.setPos( strOri.getLength());
                                    strOri << strTemp;
                                }
                                else
                                {
                                    m_Comment.setPos( strOri.getLength() + 1);
                                    strOri << ' ' << strTemp;
                                }
                            }
                            else
                            {
                                m_Comment.setPos( strOri.getLength() + 1);
                                strOri << ' ' << strTemp;
                            }
                        }
                        else
                        {
                            strOri.ReplaceString(m_Comment.getPos(), m_Comment.getField(), strTemp, 1);
                        }
                        m_Comment.setField( strTemp );
                    }
                }
                else
                {
                    m_Comment.setField(strTemp);
                }
            }
            ///生成文本条目行
            virtual T & BuildLine( T & paramResult )
            {
                if( Inherited::isHasOriginal() ) 
                {
                    return TXTIniEntry<T>::BuildLine(paramResult);
                }
                else
                {
                    paramResult.ToEmptyString();
                    paramResult << m_Key.getField() << " = " << m_Value.getField();
                    if( m_Comment.getField().isNotEmpty() )
                    {
                        if( !(m_Comment.getField()[0] ==';' || m_Comment.getField()[0] == '#') )
                        {
                            paramResult << ' ' << '#';
                        }
                        paramResult << m_Comment.getField();
                    }
                    return paramResult;
                }
            }
        private:
            TXTField<T> m_Key;          ///<条目的名称Key
            TXTField<T> m_Value;        ///<条目的值
            TXTField<T> m_Comment;      ///<注释
        };

                //----------------------------------------------------------------------------------------
        ///配置文件行条目
        /**
            注释行，空白行或未能识别的条目行，为行条目。
        */
        template<class T>
        class TXTIniEntryTextLine : public TXTIniEntry<T>
        {
        public:
            typedef TXTIniEntry<T> Inherited;
        public:
            TXTIniEntryTextLine() {}
            ~TXTIniEntryTextLine() {}
            ///取类条目的类型
            /**
                @return EIET_TEXT_LINE
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const { return EIET_TEXT_LINE; }
            ///取文本行的内容
            const T & getText() const
            {
                return Inherited::getOriginalText();
            }
            ///设置文本行的内容
            void setText(const T & paramText)
            {
                setOriginalText(paramText);
            }
        };

        //----------------------------------------------------------------------------------------
        ///配置文件的段类
        template<class T>
        class TXTIniSection : public TXTIniEntry<T>
        {
        public:
            typedef TXTIniEntry<T> Inherited;
        public:
            TXTIniSection()
                :m_CommentPos(INI_INVALID_POS)
            {}
            virtual ~TXTIniSection() 
            { 
                Clear();
            }
            ///取类条目的类型
            /**
                @return EIET_SECTION
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const { return EIET_SECTION; }
            ///取段名
            /**
                @return 返回段名
             */
            const T & getSectionName() const 
            { 
                return m_SectionName; 
            }
            ///设置段名
            /**
                @param [in] paramSectionName 设置的段名
            */
            void setSectionName(const T & paramSectionName) 
            { 
                m_SectionName = paramSectionName; 
            }
            ///取条目的个数
            /**
                @return 返回条目的个数
            */
            XInt getLength() const 
            { 
                return m_ArrayEntry.getLength(); 
            }
            ///取指定下标的条目
            /**
                @param [in] paramIndex 指定的下标
                @return 返回指定下标的条目指针
             */
            TXTIniEntry<T> * getEntry(XInt paramIndex) 
            { 
                return m_ArrayEntry[paramIndex]; 
            }
            ///取指定名称的条目
            /**
                @param [in] paramIdent 指定的条目名称
                @return 如果该条目存在，则返回条目的指针，否则返回NULL
            */
            TXTIniEntryCommon<T> * getEntry(const T & paramIdent)
            {
                for(XInt i = m_ArrayEntry.getLength()-1; i>=0; i--)
                {
                    TXTIniEntryCommon<T> * pEntry = dynamic_cast<TXTIniEntryCommon<T> *>(m_ArrayEntry[i]);
                    if( pEntry != NULL && pEntry->getKey().getField() == paramIdent) 
                    {
                        return pEntry;
                    }
                }
                return NULL;
            }
            ///在最后插入条目
            /**
                @param [in] paramEntry 被插入的条目
             */
            void AppendEntry(TXTIniEntry<T> * paramEntry) 
            { 
                m_ArrayEntry.Append(paramEntry); 
            }
            ///指定位置插入条目
            /**
                @param [in] paramIndex 指定的位置
                @param [in] paramEntry 被插入的条目
             */
            void InsertEntry(XInt paramIndex,TXTIniEntry<T> * paramEntry) 
            { 
                m_ArrayEntry.Insert(paramIndex,paramEntry); 
            }
            ///删除指定的条目
            bool Remove(const T & paramIdent)
            {
                for(XInt i = m_ArrayEntry.getLastIndex(); i >= 0; i--)
                {
                    TXTIniEntryCommon<T> * pEntry = dynamic_cast<TXTIniEntryCommon<T> *>(m_ArrayEntry[i]);
                    if( pEntry != NULL && pEntry->getKey() == paramIdent) 
                    {
                        delete pEntry;
                        m_ArrayEntry.Remove(i);
                        return true;
                    }
                }
                return false;
            }
            ///清除所有的条目
            void Clear()
            {
                for(XInt i=m_ArrayEntry.getLastIndex(); i >= 0; i--)
                {
                    delete m_ArrayEntry[i];
                }
                m_ArrayEntry.Clear();
            }   
            ///属性comment
            void setComment(const T & paramComment)
            {
                m_Comment = paramComment;
            }
            const T & getComment() const
            {
                return m_Comment;
            }
            ///属性commentPos
            void setCommentPos(XInt paramPos)
            {
                m_CommentPos = paramPos;
            }
            XInt getCommentPos() const
            {
                return m_CommentPos;
            }
            ///生成section行
            virtual T & BuildLine( T & paramResult )
            {
                if( Inherited::isHasOriginal() ) 
                {
                    return TXTIniEntry<T>::BuildLine(paramResult);
                }
                else
                {
                    paramResult.ToEmptyString();
                    paramResult <<'[' << m_SectionName <<']';
                    if( m_Comment.isNotEmpty() )
                    {
                        if( !(m_Comment[0] ==';' || m_Comment[0] == '#') )
                        {
                            paramResult << ' ' << '#';
                        }
                        paramResult << m_Comment;
                    }
                    return paramResult;
                }
            }
            ///注释变化
            void ChangeComment(const T & paramComment)
            {
                T strTemp;
                if( paramComment.isNotEmpty()) //如果不是为空
                {
                    if( !(paramComment[0] == ';' || paramComment[0]== '#') )
                    {
                        strTemp << '#' << paramComment;
                    }
                    else
                    {
                        strTemp = paramComment;
                    }
                }

                if( Inherited::isHasOriginal() )
                {
                    T & strOri = Inherited::getOriginalText();
                    if( strTemp.isEmpty() ) //如果是空串，则删除注释
                    {
                        if( m_CommentPos != INI_INVALID_POS )
                        {
                            strOri.RemoveString(m_CommentPos,m_Comment);
                        }
                        m_Comment = strTemp;
                        m_CommentPos = INI_INVALID_POS;
                    }
                    else
                    {
                        if( m_CommentPos == INI_INVALID_POS ) //如果就没有注释
                        {
                            if( strOri.isNotEmpty() )
                            {
                                typename T::StringChar ch = strOri[strOri.getLength()-1];
                                if( ch == ' ' || ch == '\t' )
                                {
                                    m_CommentPos = strOri.getLength();
                                    strOri << strTemp;
                                }
                                else
                                {
                                    m_CommentPos= strOri.getLength() + 1;
                                    strOri << ' ' << strTemp;
                                }
                            }
                            else
                            {
                                m_CommentPos = strOri.getLength() + 1;
                                strOri << ' ' << strTemp;
                            }
                        }
                        else
                        {
                            strOri.ReplaceString(m_CommentPos, m_Comment, strTemp, 1);
                        }
                        m_Comment = strTemp ;
                    }
                }
                else
                {
                    m_Comment = strTemp ;
                }
            }
        private:
            T m_SectionName;                    ///<段名称
            T m_Comment;                        ///<注释
            XInt m_CommentPos;
            XDynamicArray<TXTIniEntry<T> *>m_ArrayEntry; ///<条目数组
        };
        ///文本行的读写实现
        template<class T>
        class TXTIni
        {
        public:
            ///解析后，当前行的类型
            enum EnumParseTextType
            {
                EPTT_TEXT = 1,                  ///<文本行
                EPTT_SECTION = 2,               ///<section
                EPTT_ENTRY = 3,                 ///<条目
                EPTT_COMMENT = 4,               ///<注释行
                EPTT_UNKNOW = 5,                ///<未知行
                EPTT_SPACE = 6,                 ///<空行
                EPTT_FOCRE_DWORD = 0x7fffffff   
            };
            enum EnumLineStatus
            {
                ELS_ENTER = 1,                  ///<仅回车
                ELS_NEW_LINE = 2,               ///<仅换行
                ELS_NORMAL = 3,                 ///<普通状态
                ELS_FOCRE_DWORD = 0x7fffffff
            };
			enum EnumUTF_BOM_Lead
			{
				UTF_LEAD_0 = 0,		//BOM第一个字节
				UTF_LEAD_1 = 1,		//BOM第二个字节
				UTF_LEAD_2 = 2,		//BOM第三个字节
				UTF_LEAD_END = 3,	//BOM串结束位置
				UTF_BOM_SIZE = 3,	//BOM的字节数
				UTF_BOM_FIRST = 0xef,
			};
			typedef TXTIniSection<T> TSection;
			typedef TXTIniEntry<T>	 TEntry;
			typedef T				 TString;
			typedef TXTIniEntryCommon<T> TEntryCommon;
        public:
            TXTIni() 
			{
				setUTFBom(4);
			}
            ///带配置文件名的构造函数
            /**
                @param [in] aFileName 初始的配置文件名
            */
            TXTIni(const T & paramFileName)
                :m_FileName(paramFileName)
            {
				setUTFBom(4);
			}
            ///板构函数
            ~TXTIni() 
            { 
                Clear(); 
            }
            ///取所有section的个数
            XInt getSectionCount() const
            {
                return m_ArraySection.getLength();
            }       
            ///取指定下标的section
            /**
                @param [in] paramIndex 指定的下标
                @return XMLIniSection * 返回指定的section
                    - NULL 表示下标越界，未取得指定下标的section
                    - != NULL 表示取到了指定下标的section
             */
            TXTIniSection<T> * getSection( XInt paramIndex )
            {
                if( m_ArraySection.isValidIndex(paramIndex) )
                {
                    return m_ArraySection[paramIndex];
                }
                else
                {
                    return NULL;
                }
            }

            ///取指定名称的section
            /**
                取指定section名称的section
                @param [in] paramSectionName
                @return XMLIniSection * 返回section
                    - NULL 表示未找该名称的section
                    - != NULL 表示找到了section
             */
            TXTIniSection<T> * getSection( const T & paramSectionName )
            {
                for(XInt i=m_ArraySection.getLastIndex(); i>= 0; i--)
                {
                    if( m_ArraySection[i]->getSectionName() == paramSectionName ) 
                    {
                        return m_ArraySection[i];
                    }
                }
                return NULL;
            }

            ///删除指定下标的section
            /**
                删除指定下标的section
                @param [in] paramIndex 指定的下标，有效值在[0,getSectionCount)之间
                @return bool 删除结果
                    - true 表示删除成功
                    - false 表示删除失败
             */
            bool RemoveSection( XInt paramIndex )
            {
                if( m_ArraySection.isValidIndex(paramIndex ) )
                {
                    delete m_ArraySection[paramIndex];
                    m_ArraySection.Remove(paramIndex);
                    return true;
                }
                else return false;
            }
            ///删除指定名称的section
            /**
                删除指定section名称的section
                @param [in] paramSectionName 指定section的名称
                @return bool 删除的结果
                    - true 表示删除成功
                    - false 表示删除失败
             */
            bool RemoveSection( const T & paramSectionName )
            {
                for(XInt i=m_ArraySection.getLastIndex(); i>= 0; i--)
                {
                    if( m_ArraySection[i]->getSectionName() == paramSectionName ) 
                    {
                        return RemoveSection(i);
                    }
                }
                return false;
            }
            ///追加一个section 
            /**
                在section表的最后插入一个section，如果该section已经存在，则不插入
                @param [in] paramSectionName 插入section的名称
                @return XMLIniSection * 返回插入的section对象指针
             */     
            TXTIniSection<T> * AppendSection( const T & paramSectionName )
            {
                TXTIniSection<T> * pSection = getSection(paramSectionName);
                if( pSection == NULL )
                {
                    pSection = new TXTIniSection<T>();
                    pSection->setSectionName(paramSectionName);
                    m_ArraySection.Append( pSection );
                }
                return pSection;
            }
            ///插入一个section
            /**
                在指定的下标的位置，插入一个section,如果该section已经存在，则不插入。
                如果指定的下标不是[0,getSectionCount)之间，则在最后追加一个section
                @param [in] paramSectionName 插入section的名称
                @param [in] paramSectionIndex 插入的位置
                @return XMLIniSection * 返回插入的section对象指针
             */
            TXTIniSection<T> * InsertSection( const T & paramSectionName,XInt paramSectionIndex ) 
            {
                TXTIniSection<T> * pSection = getSection(paramSectionName);
                if( pSection == NULL )
                {
                    pSection = new TXTIniSection<T>();
                    pSection->setSectionName(paramSectionName);

                    if( m_ArraySection.isValidIndex(paramSectionIndex)) 
                    {
                        m_ArraySection.Insert(paramSectionIndex,pSection);
                    }
                    else m_ArraySection.Append(pSection);
                }
                return pSection;
            }
            //配置文件的基本接口
            ///读取XInt类型的配置
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramDefault 缺省值
                @return 如果没有找到指定的条目，则返回缺省值
             */
            XInt ReadInt(const T & paramSectionName,const T & paramIdent,XInt paramDefault) 
            {
                TXTIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent);
                if( pEntry == NULL ) 
                {
                    return paramDefault;
                }
                else  
                {
                    return pEntry->getValue().getField().ToIntDef(paramDefault);
                }
            }
            ///读取Bool类型的配置
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramDefault 缺省值
                @return 如果没有找到指定的条目，则返回缺省值
            */
            bool ReadBool(const T & paramSectionName,const T & paramIdent,bool paramDefault) 
            {
                return ReadInt(paramSectionName, paramIdent, paramDefault?1:0) != 0;
            }
            ///读取string类型的配置
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramDefault 缺省值
                @return 如果没有找到指定的条目，则返回缺省值
            */      
            const T & ReadString(const T & paramSectionName,const T & paramIdent,const T & paramDefault )
            {
                TXTIniEntryCommon<T> * pEntry = getEntry(paramSectionName, paramIdent);
                if( pEntry == NULL ) 
                {
                    return paramDefault;
                }
                else 
                {
                    return pEntry->getValue().getField();
                }
            }
            ///读取指定条目的注释
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @return 如果没有,则返回空串
            */  
            const T & ReadComment(const T & paramSectionName,const T & paramIdent)
            {
                const TXTIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent);
                if( pEntry == NULL ) 
                {
                    return T::EmptyString();
                }
                else 
                {
                    return pEntry->getComment();
                }
            }
            ///写入指定条目的注释
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramComment 注释
            */
            void WriteComment(const T & paramSectionName, const T & paramIdent, const T & paramComment)
            {
                TXTIniEntryCommon <T>* pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->ChangeComment(paramComment);
            }
            ///追加一个文本行
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramText 文本内容
             */
            void AppendText(const T & paramSectionName, const T & paramText = "")
            {
                TXTIniSection<T> * pSection = getSection(paramSectionName,true);
                TXTIniEntryTextLine<T> *pEntry = new TXTIniEntryTextLine<T>();
                pEntry->setText(paramText);
                pSection->AppendEntry(pEntry);
            }
            ///写入一个指定的XInt类型条目
            /**
                如果指定的条目不存，则会创建该条目
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramValue 条目值
             */
            void WriteInt(const T & paramSectionName,const T & paramIdent,XInt paramValue)
            {
                TXTIniEntryCommon<T> * pEntry = getEntry(paramSectionName, paramIdent, true);
                //T strValue = paramValue;
                pEntry->ChangeValue(paramValue);
            }
            ///写入一个指定的Bool类型条目
            /**
                如果指定的条目不存，则会创建该条目
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramValue 条目值
            */
            void WriteBool(const T & paramSectionName,const T &paramIdent,bool paramValue)
            {
                WriteInt(paramSectionName, paramIdent, paramValue?1:0 );
            }
            ///写入一个指定的String类型条目
            /**
                如果指定的条目不存，则会创建该条目
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @param [in] paramValue 条目值
            */
            void WriteString(const T & paramSectionName,const T &paramIdent,const T & paramValue)
            {
                TXTIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->ChangeValue(paramValue);
            }
            ///删除指定的条目
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
            */
            bool Remove(const T & paramSectionName,const T & paramIdent)
            {
                TXTIniSection<T> * pSection = getSection(paramSectionName);
                if( pSection != NULL ) 
                {
                    return pSection->Remove(paramIdent);
                }
                return false;
            }
            ///清除所有的条目和段
            void Clear()
            {
                for(XInt i=m_ArraySection.getLength()-1; i>= 0; i--)
                {
                    delete m_ArraySection[i];
                }
                m_ArraySection.Clear();
                m_HeadList.Clear();
            }       
            ///判断指定条目是否存在
            /**
                @param [in] paramSectionName 段名称
                @param [in] paramIdent 条目名称
                @return 返回条目存在情况
                    - true 表示条目存在
                    - false 表示条目不存在
            */
            bool isExists(const T & paramSectionName,const T & paramIdent) const
            {
                return getEntry(paramSectionName,paramIdent) != NULL;
            }
            ///装载配置
            bool Load(std::istream & paramStream);
            bool Load(const T & paramFileName)
            {
                setFileName(paramFileName);
				std::ifstream i(getFileName().c_str(),std::ios::binary);
				if( !i.is_open()) //如果没有打开
				{
				    return false; 
				}
                bool bRet = Load(i);
				i.close();
				return bRet;
            }

			bool Save(std::ostream & paramStream)
			{
				std::ostream & o = paramStream;
				if (hasUTFBom())
				{
					o << m_UTF_LEAD;
				}
				T strOut;
				for (XInt i = 0; i < getHeadList()->getTextCount(); i++)
				{
					WriteLine(o, getHeadList()->getText(i));
				}
				for (XInt i = 0; i < getSectionCount(); i++)
				{
					TXTIniSection<T> * paramSection = getSection(i);
					paramSection->BuildLine(strOut);
					WriteLine(o, strOut);

					for (XInt j = 0; j < paramSection->getLength(); j++)
					{
						paramSection->getEntry(j)->BuildLine(strOut);
						WriteLine(o, strOut);
					}
				}
				return true;
			}
            bool Save(const T & paramFileName)
            {
                setFileName(paramFileName);
				std::ofstream o(getFileName().c_str(), std::ios::binary);
				if (!o) return false;
				bool bRet = Save(o);
				o.close();
				return bRet;
            }
            ///设置配置文件名
            /**
                @param [in] paramFileName 指定的配置文件名称
            */
            void setFileName(const T & paramFileName) 
            { 
                m_FileName = paramFileName; 
            }
            ///取配置文件名
            /**
                @return 返回配置文件名
             */
            const T  & getFileName() const 
            { 
                return m_FileName; 
            }
            ///取一个指定段名和名称的条目
            /**
                @param [in] paramSectionName 指定的段名
                @param [in] paramIdent 指定的条目名称
                @return 返回取得的结果
                    - !=NULL 返回对应条目的指针
                    - NULL 表示未找到相应的条相
             */
            TXTIniEntryCommon<T> * getEntry(const T & paramSectionName,const T & paramIdent) 
            {
                TXTIniSection<T> * pSection = getSection(paramSectionName);
                if( pSection != NULL )
                {
                    return pSection->getEntry(paramIdent);
                }
                return NULL;
            }
            ///取一个普通的条目
            /**
                取一个指定段名和名称的条目，如果条目不存在的话，是否要自己插入一个
                @param [in] paramSectionName 指定的段名
                @param [in] paramIdent 指定的条目名称
                @param [in] paramAutoInsert 是否自动插入
                    - true 表示条目不存在的话，就自动插入一个条目
                    - false 表示条目不存在的话，不自动插入
                @return 返回取得的结果
                    - !=NULL 返回对应条目的指针
                    - NULL 表示未找到相应的条相
             */
            TXTIniEntryCommon<T> * getEntry(const T & paramSectionName,const T & paramIdent,bool paramAutoInsert)
            {
                TXTIniSection<T> * pSection = getSection(paramSectionName, paramAutoInsert);
                if( pSection != NULL )
                {
                    TXTIniEntryCommon<T> * pEntry = pSection->getEntry(paramIdent);
                    if( pEntry == NULL && paramAutoInsert)
                    {
                        pEntry = new TXTIniEntryCommon<T>();
                        pEntry->getKey().setField(paramIdent);
                        pSection->AppendEntry(pEntry);
                    }
                    return pEntry;
                }
                return NULL;
            }
            ///取一个指定段名的section
            /**
                取一个指定段名的section，如果section不存在的话，是否要自己插入一个
                @param [in] paramSectionName 指定的段名
                @param [in] paramAutoInsert 是否自动插入
                    - true 表示section不存在的话，就自动插入一个section
                    - false 表示section不存在的话，不自动插入
                @return 返回取得的结果
                    - !=NULL 返回对应条目的指针
                    - NULL 表示未找到相应的条相
             */
            TXTIniSection<T> * getSection(const T & paramSectionName,bool paramAutoInsert)
            {
                for(XInt i = m_ArraySection.getLength()-1; i>= 0; i--)
                {
                    if( m_ArraySection[i]->getSectionName() == paramSectionName ) 
                    {
                        return m_ArraySection[i];
                    }
                }
                if( paramAutoInsert )
                {
                    TXTIniSection<T> * pSection = new TXTIniSection<T>();
                    pSection->setSectionName(paramSectionName);
                    m_ArraySection << pSection;
                    return pSection;
                }
                else return NULL;
            }
            ///取配置文件开始前的文本行列表
            TXTIniHeadList<T> * getHeadList() 
            {
                return &m_HeadList;
            }
        private:


            ///读取一行
            bool ReadLine(std::istream & paramInput, T & paramLine);
            ///写入一行
            void WriteLine(std::ostream & paramOutput,const T & paramLine);
            ///解析一行
            XInt ParseLine(const T & paramLine);
			
			bool hasUTFBom() const
			{
				return m_UTF8HasBom;
			}
			//m_UTF_LEAD_0
			XByte getUTF_LEAD_0() const
			{
				return m_UTF_LEAD[UTF_LEAD_0];
			}
			XByte getUTF_LEAD_1() const
			{
				return m_UTF_LEAD[UTF_LEAD_1];
			}
			XByte getUTF_LEAD_2() const
			{
				return m_UTF_LEAD[UTF_LEAD_2];
			}
			void ClearUTFBom()
			{
				m_UTF8HasBom = false;
			}
			/**
				设置Bom模式
				@param [in] paramBomMode BOM模式
					- 1: 0xefU 0xbbU 0xbfU
					- 2: 0xefU 0xbfU 0xbeU
					- 3: 0xefU 0xbfU 0xbfU
					- 4: 0x00U 0x00U 0x00U
				@return int 返回设置结果
					- ERR_OK 设置有效
					- ERR_FAIL 设置失败

			 */
			int setUTFBom(int paramBomMode = 1)
			{
				switch(paramBomMode)
				{
				case 1:
					m_UTF_LEAD[UTF_LEAD_0] = 0xefu;
					m_UTF_LEAD[UTF_LEAD_1] = 0xbbu;
					m_UTF_LEAD[UTF_LEAD_2] = 0xbfu;
					m_UTF8HasBom = true;
					break;
				case 2:
					m_UTF_LEAD[UTF_LEAD_0] = 0xefu;
					m_UTF_LEAD[UTF_LEAD_1] = 0xbfu;
					m_UTF_LEAD[UTF_LEAD_2] = 0xbeu;
					m_UTF8HasBom = true;
					break;
				case 3:
					m_UTF_LEAD[UTF_LEAD_0] = 0xefu;
					m_UTF_LEAD[UTF_LEAD_1] = 0xbfu;
					m_UTF_LEAD[UTF_LEAD_2] = 0xbfu;
					m_UTF8HasBom = true;
					break;
				default:
					m_UTF_LEAD[UTF_LEAD_0] = 0;
					m_UTF_LEAD[UTF_LEAD_1] = 0;
					m_UTF_LEAD[UTF_LEAD_2] = 0;
					m_UTF8HasBom = false;
					break;
				}
				m_UTF_LEAD[UTF_LEAD_END] = 0;
				return ERR_OK;
			}
        private:
            ///解析用的临时对象
            
            T m_ParseKey;       ///<解析的Key
            XInt m_ParseKeyPos;

            T m_ParseValue;     ///<解析的Value
            XInt m_ParseValuePos;

            T m_ParseSection;   ///<解析的section
            XInt m_ParseSectionPos;

            T m_ParseComment;   ///<解析的注释
            XInt m_ParseCommentPos;
                    
            T m_Temp;           ///<解析文本行用的临时变量
            XChar m_Buffer[128];
            XInt m_BufferStart;
            XInt m_BufferCount;
        private:
			/*
				UTF-8的BOM信息，如果是UTF-8格式的文件，并有BOM信息，那么m_UTF8HasBom的值会设为true，并记录相应的bom值
				也可自己设置BOM信息，保存的时候会用到
			*/
			bool m_UTF8HasBom;
			XByte m_UTF_LEAD[4];

		private:
            XDynamicArray<TXTIniSection<T> *>m_ArraySection; ///条目段数组
            T m_FileName;                           ///<配置文件名
            TXTIniHeadList<T> m_HeadList;
        };

        ///写入一行
        template<class T>
        void TXTIni<T>::WriteLine(std::ostream & paramOutput,const T & paramLine)
        {
            const typename T::StringChar chEnter = 0x0d;
            const typename T::StringChar chLine =  0x0a;
            paramOutput << paramLine.c_str() << chEnter << chLine;
        }
        ///读取一行
        template<class T>
        bool TXTIni<T>::ReadLine(std::istream & paramInput, T & paramLine)
        {
            paramLine.ToEmptyString();
            EnumLineStatus elsStatus = ELS_NORMAL;
            while(paramLine.getLength() < 4096) //如果没有超过最大长度
            {
                if( m_BufferStart >= m_BufferCount )    
                {
                    paramInput.read(m_Buffer, sizeof(m_Buffer));
                    m_BufferStart = 0;
                    m_BufferCount = (XInt)paramInput.gcount();
                    if( m_BufferCount == 0 ) 
                    {
                        if( paramLine.isEmpty() ) return false;
                        break;
                    }
                }
                //查找结尾符
                while(m_BufferStart < m_BufferCount)
                {
                    XChar ch = m_Buffer[m_BufferStart];
                    switch(elsStatus)
                    {
                    case ELS_ENTER:
                        {
                            if( string_utils::isNewLine(ch) )
                            {
                                elsStatus = ELS_NORMAL;
                                m_BufferStart ++;
                            }
                            return true;
                        }
                        break;
                    case ELS_NEW_LINE:
                        {
                            if( string_utils::isEnter(ch))
                            {
                                elsStatus = ELS_NORMAL;
                                m_BufferStart++;
                            }
                            return true;
                        }
                        break;
                    case ELS_NORMAL:
                        {
                            if( string_utils::isEnter(ch) )
                            {
                                elsStatus = ELS_ENTER;
                            }
                            else if( string_utils::isNewLine(ch) )
                            {
                                elsStatus = ELS_NEW_LINE;
                            }
                            else 
                            {
                                paramLine += ch;
                            }
                            m_BufferStart ++;
                        }
                        break;
                    default:
                        break;
                    }
                }//while(m_BufferStart < m_BufferCount)
            }//while(paramLine.getLength() < 4096)
            return true;
        }
        ///解析一行
        template<class T>
        XInt TXTIni<T>::ParseLine(const T & paramLine)
        {
            XInt iLength = paramLine.getLength();
            XInt iPos = 0;
            bool bSkipSpace = true;
            T & strText = m_Temp;
            strText.ToEmptyString();

            m_ParseKey = m_ParseValue = m_ParseSection = m_ParseComment = strText;
            m_ParseCommentPos = m_ParseKeyPos = m_ParseSectionPos = m_ParseValuePos = INI_INVALID_POS;

            XInt iStatus = 0;
            //XInt iOldStatus = 0;

            //const typename T::StringChar * p = paramLine.c_str();

            while( iPos < iLength )
            {
                typename T::StringChar ch = paramLine[iPos];
                if( bSkipSpace ) //跳过空格
                {
                    if( string_utils::isIniSpaceChar(ch) )
                    {
                        iPos ++;
                        continue;
                    }
                    bSkipSpace = false;
                }
                switch(iStatus)
                {
                case 0:
                    {
                        if( string_utils::isIniComment( ch ))
                        {
                            m_ParseComment = paramLine;
                            return EPTT_COMMENT;
                        }
                        else if( string_utils::isBracketLeft(ch) )
                        {
                            iStatus = 1;
                            bSkipSpace = true;
                        }
                        else if( string_utils::isEqual(ch) )
                        {
                            return EPTT_UNKNOW;
                        }
                        else 
                        {
                            if( m_ParseKeyPos == INI_INVALID_POS) m_ParseKeyPos = iPos;
                            strText = ch;
                            iStatus = 2;
                        }
                    }
                    break;
                case 1: //section
                    {
                        if( m_ParseSectionPos == INI_INVALID_POS ) m_ParseSectionPos = iPos;
                        if( string_utils::isBracketRight(ch) )  
                        {
                            if( strText.isEmpty() ) 
                            {
                                return EPTT_UNKNOW;
                            }
                            else
                            {
                                strText.TrimRight(m_ParseSection);
                                strText.ToEmptyString();
                                bSkipSpace = true;
                                iStatus = 3;
                            }
                        }
                        strText += ch;
                    }
                    break;
                case 2: //entry
                    {
                        if( string_utils::isEqual(ch) )
                        {
                            if( strText.isEmpty() ) 
                            {
                                return EPTT_UNKNOW;
                            }
                            else
                            {
                                strText.TrimRight(m_ParseKey);
                                strText.ToEmptyString();
                                iStatus = 4;
                                bSkipSpace = true;
                            }
                        }
                        else 
                        {
                            //const char * k = strText.c_str();
                            strText += ch;
                        }
                    }
                    break;
                case 3: //section 后段
                    {
                        if( string_utils::isIniComment(ch))
                        {
                            m_ParseCommentPos = iPos;
                            paramLine.SubString(iPos,iLength - iPos, m_ParseComment); //读取注释
                            return EPTT_SECTION;
                        }
                        else 
                        {
                            return EPTT_UNKNOW;
                        }
                    }
                    break;
                case 4: //entry value
                    {
                        if( m_ParseValuePos == INI_INVALID_POS ) m_ParseValuePos = iPos;
                        if( ch ==  '#' || ch == ';' )  //如果直接读取注释
                        {
                            m_ParseCommentPos = iPos;
                            typename T::StringChar chPre = paramLine[iPos-1]; 
                            if( string_utils::isIniSpaceChar(chPre) )
                            {
                                strText.TrimRight(m_ParseValue);
                                strText.ToEmptyString();
                                paramLine.SubString(iPos,iLength-iPos,m_ParseComment);
                                return EPTT_ENTRY;
                            }
                            else if( strText.isEmpty())
                            {
                                paramLine.SubString(iPos,iLength-iPos,m_ParseComment);
                                return EPTT_ENTRY;                          
                            }
                            else //如果前面是非空格字符
                            {
                                strText += ch;
                            }
                        }
                        else 
                        {
                            strText += ch;                      
                        }
                    }
                    break;
                }
                iPos ++;
            }
            switch(iStatus)
            {
            case 0:
                return EPTT_SPACE;
            case 1:
                return EPTT_UNKNOW;
            case 2:
                return EPTT_UNKNOW;
            case 3:
                return EPTT_SECTION;
            case 4:
                strText.TrimRight(m_ParseValue);
                return EPTT_ENTRY;
            }
            return EPTT_UNKNOW;
        }
        ///装载文本文件的ini
        template<class T>
		bool TXTIni<T>::Load(std::istream & paramStream)
        {
            TXTIniSection<T> * pNowSection = NULL;
			
			//std::ifstream i(getFileName().c_str(),std::ios::binary);
			std::istream & i = paramStream;
            T strLine;
            //if( !i.is_open()) //如果没有打开
            //{
            //    return false; 
            //}
            Clear();
            strLine.ensureCapacity(4096);
            
            m_Temp = 0;         ///<解析文本行用的临时变量
            m_BufferStart = 0;
            m_BufferCount = 0;
			int iReadLineCount = 0;

            while( ReadLine(i,strLine))
            {
				if (iReadLineCount == 0)
				{
					do 
					{
						
						if (strLine.getLength() < 3) break;
						XByte bt1 = (XByte)strLine[0];
						XByte bt2 = (XByte)strLine[1];
						XByte bt3 = (XByte)strLine[2];
						int iMode = 0;
						if (bt1 != 0xef) break;
						if (bt2 == 0xbb)
						{ 
							if (bt3 == 0xbf) iMode = 1;
						}
						else if (bt2 == 0xbf)
						{
							if (bt3 == 0xbe) iMode = 2;
							else if (bt3 == 0xbf) iMode = 3;
						}
						if (iMode >= 1 && iMode <= 3)
						{
							strLine.RemoveRangeChar(0, 3);
							this->setUTFBom(iMode);
						}

					} while (false);
				}
				iReadLineCount++;
                switch(ParseLine(strLine))
                {
                case EPTT_TEXT:
                    {
                        if( pNowSection == NULL )
                        {
                            getHeadList()->AppendText(strLine); 
                        }
                        else
                        {
                            TXTIniEntryTextLine<T> * pLine = new TXTIniEntryTextLine<T>();
                            pLine->setText( strLine );
                            pNowSection->AppendEntry( pLine );
                        }
                    }
                    break;
                case EPTT_SECTION:
                    {
                        pNowSection = AppendSection(m_ParseSection);
                        pNowSection->setOriginalText( strLine );
                        if( m_ParseComment.isNotEmpty() )
                        {
                            pNowSection->setComment(m_ParseComment);
                            pNowSection->setCommentPos(m_ParseCommentPos);
                        }
                        pNowSection->setHasOriginal(true);
                    }
                    break;
                case EPTT_ENTRY:
                    {
                        if( pNowSection != NULL )
                        {
                            TXTIniEntryCommon<T> * pEntry = new TXTIniEntryCommon<T>();
                            pEntry->getKey().setField( m_ParseKey );
                            pEntry->getKey().setPos( m_ParseKeyPos );
                            pEntry->getValue().setField( m_ParseValue );
                            pEntry->getValue().setPos( m_ParseValuePos );
                            if( m_ParseComment.isNotEmpty())
                            {
                                pEntry->getComment().setField( m_ParseComment );
                                pEntry->getComment().setPos( m_ParseCommentPos );
                            }
                            pEntry->setOriginalText( strLine );
                            pEntry->setHasOriginal( true );
                            pNowSection->AppendEntry( pEntry );
                        }
                        else
                        {
                            getHeadList()->AppendText(strLine);
                        }
                    }
                    break;
                case EPTT_SPACE:
                    if( pNowSection == NULL )
                    {
                        getHeadList()->AppendText(strLine); 
                    }
                    else
                    {
                        TXTIniEntryTextLine<T> * pLine = new TXTIniEntryTextLine<T>();
                        pLine->setText( strLine );
                        pNowSection->AppendEntry( pLine );
                    }
                    break;
                case EPTT_UNKNOW:
                    if( pNowSection == NULL )
                    {
                        getHeadList()->AppendText(strLine); 
                    }
                    else
                    {
                        TXTIniEntryTextLine<T> * pLine = new TXTIniEntryTextLine<T>();
                        pLine->setText( strLine );
                        pNowSection->AppendEntry( pLine );
                    }
                    break;
                case EPTT_COMMENT:
                    if( pNowSection == NULL )
                    {
                        getHeadList()->AppendText(strLine); 
                    }
                    else
                    {
                        TXTIniEntryTextLine<T> * pLine = new TXTIniEntryTextLine<T>();
                        pLine->setText( strLine );
                        pNowSection->AppendEntry( pLine );
                    }
                    break;
                }
            }
            return true;
        }

    }
    //简化定义类型
    typedef xmlini::XMLIni<XAnsiString> XIniXML;
    typedef txtini::TXTIni<XAnsiString> XIniText;
}
#endif
