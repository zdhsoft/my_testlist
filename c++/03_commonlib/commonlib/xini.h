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
    ����ļ����˻���text��xml�������ļ���д������ʵ�ֵĹ���һ����
    ������Ծ����ʽ��˵��ʾ��
    xml��ʽ��ʾ��:
    <?xml version="1.0" encoding="GB2312" standalone="yes" ?>
    <ini version="1.0">
        <section name="bbbbb" />
        <section name="test">
            <text value="����һ������" />
            <entry name="test3" value="ttttttttttttttt" />
            <entry name="aaaaa" value="���к���" />
            <entry name="test1" value="" comment="����һ������" />
            <text value="����һ������" />
            <text value="����һ������" />
            <text value="����һ������" />
            <text value="����һ������" />
            <text value="����һ������" />
            <text value="����һ������" />
        </section>
        <section name="aaaaaa" />
    </ini>
    �������ı���ʽʾ��:
    #����һ��ʾ���ļ�
    #�����ȡд��ȫ�¿���

    [system] #�����ϵͳ����
    listen_port = 3366      #�����˿�
    listen_ip = 192.168.1.1 #������IP��ַ
    [db]    #�������ݿ������Ϣ
    ConnectionString = .....
    username=sa
    password=12345
    
    ����xml��text�Ĳ���������ȫһ��
    
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
    enum EIniEntryType ///<�����ļ���Ŀ������
    {
        EIET_TEXT_LINE = 1,     ///<����Ŀ�ı���
        EIET_COMMON_ENTRY = 2,  ///<��ͨ��Ŀ
        EIET_SECTION = 3,       ///<������
        EIET_HEAD_LIST = 4,     
        EIET_FOCRE_DWORD = 0x7fffffff
    };
    enum EIniFileType   ///<�����ļ�����
    {
        EIFT_XML,       ///<����XML��
        EIFT_TEXT,      ///<�����ı���
        EIFT_FOCRE_DWORD = 0x7fffffff
    };

    
    //----------------------------------------------------------------------------------------
    //����XML�������ļ���дʵ��
    namespace xmlini
    {
        ///XML��Ŀ����
        class XMLIniEntry
        {
        public:
            XMLIniEntry(){}
            virtual ~XMLIniEntry(){}
            ///ȡ����Ŀ������
            /**
                @see EIniEntryType
             */
            virtual EIniEntryType getEntryType() const = 0;
        };
        ///XMLͨ����Ŀ
        template<class T>
        class XMLIniEntryCommon : public XMLIniEntry
        {
        public:
            XMLIniEntryCommon() 
            {}
            ///ȡ����Ŀ������
            /**
            @return XIET_COMMON_ENTRY
            @see EIniEntryType
            */
            EIniEntryType getEntryType() const 
            { 
                return EIET_COMMON_ENTRY; 
            }
            ///ȡ��Ŀ������Key
            /**
                @return ������Ŀ������Key
            */
            const T & getKey() const { return m_Key; }
            ///ȡ��Ŀ��ֵ
            /**
            @return ������Ŀ��ֵ
            */
            const T & getValue() const { return m_Value; }
            ///������Ŀ������Key
            /**
                @param [in] paramKey ��Ŀ������Key
            */
            bool setKey(const T & paramKey) 
            { 
                T strKey;
                paramKey.Trim(strKey);

                if( strKey.isEmpty() ) 
                {
                    return false; //���KeyΪ��,�򷵻�
                }
                else
                {
                    m_Key = strKey;
                    return true;
                }
            }
            ///������Ŀ��ֵ
            /**
                @param [in] paramValue ��Ŀ��ֵ
            */
            bool setValue(const T & paramValue) 
            { 
                paramValue.Trim(m_Value);
                return true;
            }
            ///������Ŀ��ֵ
            /**
                @param [in] paramKey ��Ŀ������Key
                @param [in] paramValue ��Ŀ��ֵ
            */
            bool setValue(const T & paramKey,const T & paramValue) 
            {
                return setKey(paramKey) && setValue(paramValue);
            }
            ///ȡ��ǰ��Ŀ��ע��
            const T & getComment() const
            {
                return m_Comment;
            }
            ///ȡ��ǰ��Ŀ��ע��
            void setComment(const T & paramComment)
            {
                m_Comment = paramComment;
            }

        private:
            T m_Key;            ///<��Ŀ������Key
            T m_Value;          ///<��Ŀ��ֵ
            T m_Comment;        ///<ע��
        };

        ///�����ļ���ʼǰ���ı����б�
        template<class T>
        class XMLIniHeadList
        {
        public:
            XMLIniHeadList(){}
            ~XMLIniHeadList() { Clear(); }
            ///��������ı���
            void Clear()
            {
                for(XInt i = 0; i < m_List.getLength(); i++)
                {
                    delete m_List[i];
                }
                m_List.Clear();
            }
            ///׷��һ���ı�
            void AppendText(const T & paramText)
            {
                T * pText = new T(paramText);
                m_List.Append(pText);
            }
            ///����һ���ı�
            void InsertText(XInt paramIndex, const T & paramText)
            {
                T * pText = new T(paramText);
                m_List.Insert(paramIndex, pText);
            }
            ///ɾ��һ���ı�
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
            ///ȡ�ı��е�����
            XInt getTextCount() const
            {
                return m_List.getLength();
            }
            ///ȡָ���±���ı�
            T & getText(XInt paramIndex) 
            {
                return *m_List[paramIndex];
            }
            const T & getText(XInt paramIndex)const
            {
                return *m_List[paramIndex];
            }

        private:
            XDynamicArray<T *> m_List;  ///�ı��б�����
        };
        //----------------------------------------------------------------------------------------
        ///�����ļ�����Ŀ
        /**
            ��¼һЩ�ı�˵��
         */
        template<class T>
        class XMLIniEntryTextLine : public XMLIniEntry
        {
        public:
            XMLIniEntryTextLine() {}
            ~XMLIniEntryTextLine() {}
            ///ȡ����Ŀ������
            /**
                @return EIET_TEXT_LINE
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const { return EIET_TEXT_LINE; }
            ///ȡ�ı��е�����
            const T & getText() const
            {
                return m_Text;
            }
            ///�����ı��е�����
            void setText(const T & paramText)
            {
                m_Text = paramText;
            }
        private:
            T m_Text;   ///<�ı��е�����
        };

        //----------------------------------------------------------------------------------------
        ///�����ļ��Ķ���
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
            ///ȡ����Ŀ������
            /**
                @return EIET_SECTION
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const { return EIET_SECTION; }
            ///ȡ����
            /**
                @return ���ض���
             */
            const T & getSectionName() const 
            { 
                return m_SectionName; 
            }
            ///���ö���
            /**
                @param [in] paramSectionName ���õĶ���
            */
            void setSectionName(const T & paramSectionName) 
            { 
                m_SectionName = paramSectionName; 
            }
            ///ȡ��Ŀ�ĸ���
            /**
                @return ������Ŀ�ĸ���
            */
            XInt getLength() const 
            { 
                return m_ArrayEntry.getLength(); 
            }
            ///ȡָ���±����Ŀ
            /**
                @param [in] paramIndex ָ�����±�
                @return ����ָ���±����Ŀָ��
             */
            XMLIniEntry * getEntry(XInt paramIndex) 
            { 
                return m_ArrayEntry[paramIndex]; 
            }
            ///ȡָ�����Ƶ���Ŀ
            /**
                @param [in] paramIdent ָ������Ŀ����
                @return �������Ŀ���ڣ��򷵻���Ŀ��ָ�룬���򷵻�NULL
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
            ///����������Ŀ
            /**
                @param [in] paramEntry ���������Ŀ
             */
            void AppendEntry(XMLIniEntry * paramEntry) 
            { 
                m_ArrayEntry.Append(paramEntry); 
            }
            ///ָ��λ�ò�����Ŀ
            /**
                @param [in] paramIndex ָ����λ��
                @param [in] paramEntry ���������Ŀ
             */
            void InsertEntry(XInt paramIndex,XMLIniEntry * paramEntry) 
            { 
                m_ArrayEntry.Insert(paramIndex,paramEntry); 
            }
            ///ɾ��ָ������Ŀ
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
            ///������е���Ŀ
            void Clear()
            {
                for(XInt i=m_ArrayEntry.getLastIndex(); i >= 0; i--)
                {
                    delete m_ArrayEntry[i];
                }
                m_ArrayEntry.Clear();
            }   
            ///����comment
            void setComment(const T & paramComment)
            {
                m_Comment = paramComment;
            }
            const T & getComment() const
            {
                return m_Comment;
            }
        private:
            T m_SectionName;                    ///<������
            T m_Comment;                        ///<ע��
            XDynamicArray<XMLIniEntry *>m_ArrayEntry; ///<��Ŀ����
        };
        ///XML ��дʵ��
        template<class T>
        class XMLIni
        {
        public:
            XMLIni() {}
            ///�������ļ����Ĺ��캯��
            /**
                @param [in] aFileName ��ʼ�������ļ���
            */
            XMLIni(const T & paramFileName)
                :m_FileName(paramFileName)
            {}
            ///�幹����
            ~XMLIni() 
            { 
                Clear(); 
            }
            ///ȡ����section�ĸ���
            XInt getSectionCount() const
            {
                return m_ArraySection.getLength();
            }       
            ///ȡָ���±��section
            /**
                @param [in] paramIndex ָ�����±�
                @return XMLIniSection * ����ָ����section
                    - NULL ��ʾ�±�Խ�磬δȡ��ָ���±��section
                    - != NULL ��ʾȡ����ָ���±��section
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

            ///ȡָ�����Ƶ�section
            /**
                ȡָ��section���Ƶ�section
                @param [in] paramSectionName
                @return XMLIniSection * ����section
                    - NULL ��ʾδ�Ҹ����Ƶ�section
                    - != NULL ��ʾ�ҵ���section
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

        ///ɾ��ָ���±��section
            /**
                ɾ��ָ���±��section
                @param [in] paramIndex ָ�����±꣬��Чֵ��[0,getSectionCount)֮��
                @return bool ɾ�����
                    - true ��ʾɾ���ɹ�
                    - false ��ʾɾ��ʧ��
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
            ///ɾ��ָ�����Ƶ�section
            /**
                ɾ��ָ��section���Ƶ�section
                @param [in] paramSectionName ָ��section������
                @return bool ɾ���Ľ��
                    - true ��ʾɾ���ɹ�
                    - false ��ʾɾ��ʧ��
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
            ///׷��һ��section 
            /**
                ��section���������һ��section�������section�Ѿ����ڣ��򲻲���
                @param [in] paramSectionName ����section������
                @return XMLIniSection * ���ز����section����ָ��
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
            ///����һ��section
            /**
                ��ָ�����±��λ�ã�����һ��section,�����section�Ѿ����ڣ��򲻲��롣
                ���ָ�����±겻��[0,getSectionCount)֮�䣬�������׷��һ��section
                @param [in] paramSectionName ����section������
                @param [in] paramSectionIndex �����λ��
                @return XMLIniSection * ���ز����section����ָ��
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
            //�����ļ��Ļ����ӿ�
            ///��ȡXInt���͵�����
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramDefault ȱʡֵ
                @return ���û���ҵ�ָ������Ŀ���򷵻�ȱʡֵ
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
            ///��ȡBool���͵�����
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramDefault ȱʡֵ
                @return ���û���ҵ�ָ������Ŀ���򷵻�ȱʡֵ
            */
            bool ReadBool(const T & paramSectionName,const T & paramIdent,bool paramDefault) 
            {
                return ReadInt(paramSectionName, paramIdent, paramDefault?1:0) != 0;
            }
            ///��ȡstring���͵�����
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramDefault ȱʡֵ
                @return ���û���ҵ�ָ������Ŀ���򷵻�ȱʡֵ
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
            ///��ȡָ����Ŀ��ע��
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @return ���û��,�򷵻ؿմ�
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
            ///д��ָ����Ŀ��ע��
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramComment ע��
            */
            void WriteComment(const T & paramSectionName, const T & paramIdent, const T & paramComment)
            {
                XMLIniEntryCommon <T>* pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->setComment(paramComment);
            }
            ///׷��һ���ı���
            /**
                @param [in] paramSectionName ������
                @param [in] paramText �ı�����
             */
            void AppendText(const T & paramSectionName, const T & paramText = "")
            {
                XMLIniSection<T> * pSection = getSection(paramSectionName,true);
                XMLIniEntryTextLine<T> *pEntry = new XMLIniEntryTextLine<T>();
                pEntry->setText(paramText);
                pSection->AppendEntry(pEntry);
            }
            ///д��һ��ָ����XInt������Ŀ
            /**
                ���ָ������Ŀ���棬��ᴴ������Ŀ
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramValue ��Ŀֵ
             */
            void WriteInt(const T & paramSectionName,const T & paramIdent,XInt paramValue)
            {
                XMLIniEntryCommon<T> * pEntry = getEntry(paramSectionName, paramIdent, true);
                //T strValue = paramValue;
                pEntry->setValue(paramValue);
            }
            ///д��һ��ָ����Bool������Ŀ
            /**
                ���ָ������Ŀ���棬��ᴴ������Ŀ
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramValue ��Ŀֵ
            */
            void WriteBool(const T & paramSectionName,const T &paramIdent,bool paramValue)
            {
                XMLIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->setValue(paramValue?1:0);
            }
            ///д��һ��ָ����String������Ŀ
            /**
                ���ָ������Ŀ���棬��ᴴ������Ŀ
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramValue ��Ŀֵ
            */
            void WriteString(const T & paramSectionName,const T &paramIdent,const T & paramValue)
            {
                XMLIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->setValue(paramValue);
            }
            ///ɾ��ָ������Ŀ
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
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
            ///������е���Ŀ�Ͷ�
            void Clear()
            {
                for(XInt i=m_ArraySection.getLength()-1; i>= 0; i--)
                {
                    delete m_ArraySection[i];
                }
                m_ArraySection.Clear();
                m_HeadList.Clear();
            }       
            ///�ж�ָ����Ŀ�Ƿ����
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @return ������Ŀ�������
                    - true ��ʾ��Ŀ����
                    - false ��ʾ��Ŀ������
            */
            bool isExists(const T & paramSectionName,const T & paramIdent) const
            {
                return getEntry(paramSectionName,paramIdent) != NULL;
            }
            ///װ������
            bool Load();
            bool Load(const T & paramFileName)
            {
                setFileName(paramFileName);
                return Load();
            }
            ///��������
            bool Save();
            bool Save(const T & paramFileName)
            {
                setFileName(paramFileName);
                return Save();
            }
            ///���������ļ���
            /**
                @param [in] paramFileName ָ���������ļ�����
            */
            void setFileName(const T & paramFileName) 
            { 
                m_FileName = paramFileName; 
            }
            ///ȡ�����ļ���
            /**
                @return ���������ļ���
             */
            const T  & getFileName() const 
            { 
                return m_FileName; 
            }
            ///ȡһ��ָ�����������Ƶ���Ŀ
            /**
                @param [in] paramSectionName ָ���Ķ���
                @param [in] paramIdent ָ������Ŀ����
                @return ����ȡ�õĽ��
                    - !=NULL ���ض�Ӧ��Ŀ��ָ��
                    - NULL ��ʾδ�ҵ���Ӧ������
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
            ///ȡһ����ͨ����Ŀ
            /**
                ȡһ��ָ�����������Ƶ���Ŀ�������Ŀ�����ڵĻ����Ƿ�Ҫ�Լ�����һ��
                @param [in] paramSectionName ָ���Ķ���
                @param [in] paramIdent ָ������Ŀ����
                @param [in] paramAutoInsert �Ƿ��Զ�����
                    - true ��ʾ��Ŀ�����ڵĻ������Զ�����һ����Ŀ
                    - false ��ʾ��Ŀ�����ڵĻ������Զ�����
                @return ����ȡ�õĽ��
                    - !=NULL ���ض�Ӧ��Ŀ��ָ��
                    - NULL ��ʾδ�ҵ���Ӧ������
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
            ///ȡһ��ָ��������section
            /**
                ȡһ��ָ��������section�����section�����ڵĻ����Ƿ�Ҫ�Լ�����һ��
                @param [in] paramSectionName ָ���Ķ���
                @param [in] paramAutoInsert �Ƿ��Զ�����
                    - true ��ʾsection�����ڵĻ������Զ�����һ��section
                    - false ��ʾsection�����ڵĻ������Զ�����
                @return ����ȡ�õĽ��
                    - !=NULL ���ض�Ӧ��Ŀ��ָ��
                    - NULL ��ʾδ�ҵ���Ӧ������
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
            ///ȡ�����ļ���ʼǰ���ı����б�
            XMLIniHeadList<T> * getHeadList() 
            {
                return &m_HeadList;
            }
        private:
            XDynamicArray<XMLIniSection<T> *>m_ArraySection; ///��Ŀ������
            T m_FileName;                           ///<�����ļ���
            XMLIniHeadList<T> m_HeadList;
        };
        ///װ������
        template<class T>
        bool XMLIni<T>::Load()
        {
            Clear();

            TiXmlDocument doc;
            if(!doc.LoadFile(getFileName()))
            {
                //װ��ʧ��
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
        ///��������
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
            for(XInt i=0; i < getSectionCount(); i++) //�������еĶ�
            {
                XMLIniSection<T> * pSection = getSection(i);
                TiXmlElement * elemSection = elemRoot->AppendChildElement("section");
                elemSection->setStringAttrib("name",pSection->getSectionName());
                for(XInt j=0; j<pSection->getLength(); j++) //�������е���Ŀ
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
        ///�����ı���iniʵ��
        const XInt INI_INVALID_POS = -1;    ///<��Ч��POS

        ///�ı���Ŀ�Ļ���
        template<class T>
        class TXTIniEntry
        {
        public:
            TXTIniEntry()
                :m_HasOriginal(false)
            {}
            virtual ~TXTIniEntry(){}
            ///ȡ����Ŀ������
            /**
                @see EIniEntryType
             */
            virtual EIniEntryType getEntryType() const = 0;
            ///ȡԭʼ�ı�
            const T & getOriginalText() const 
            {
                return m_OriginalText;
            }
            T & getOriginalText() 
            {
                return m_OriginalText;
            }
            ///����ԭʼ�ı�
            void setOriginalText(const T & paramOriginalText)
            {
                m_OriginalText = paramOriginalText;
            }
            ///Original��־����
            bool isHasOriginal() const
            {
                return m_HasOriginal;
            }
            void setHasOriginal(bool paramFlag)
            {
                m_HasOriginal = paramFlag;
            }
            ///������Ŀ��
            virtual T & BuildLine(T & paramResult)
            {
                paramResult = m_OriginalText;
                return paramResult;
            }
        private:
            T m_OriginalText;       ///ԭʼ���ı���
            bool m_HasOriginal;     ///<�Ƿ����ԭʼ�ı���
        };
        ///�����ļ���ʼǰ���ı����б�
        template<class T>
        class TXTIniHeadList
        {
        public:
            TXTIniHeadList(){}
            ~TXTIniHeadList() 
            { 
                Clear(); 
            }
            ///��������ı���
            void Clear()
            {
                for(XInt i = 0; i < m_List.getLength(); i++)
                {
                    delete m_List[i];
                }
                m_List.Clear();
            }
            ///׷��һ���ı�
            void AppendText(const T & paramText)
            {
                T * pText = new T(paramText);
                m_List.Append(pText);
            }
            ///����һ���ı�
            void InsertText(XInt paramIndex, const T & paramText)
            {
                T * pText = new T(paramText);
                m_List.Insert(paramIndex, pText);
            }
            ///ɾ��һ���ı�
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
            ///ȡ�ı��е�����
            XInt getTextCount() const
            {
                return m_List.getLength();
            }
            ///ȡָ���±���ı�
            T & getText(XInt paramIndex) 
            {
                return *m_List[paramIndex];
            }
            const T & getText(XInt paramIndex)const
            {
                return *m_List[paramIndex];
            }

        private:
            XDynamicArray<T *> m_List;  ///<�ı����б�
        };
        ///��Ŀ�е��ֶ���
        /**
            ��Ҫ�����������ݣ�һ������Ŀ���ֶ����ݣ�һ�����ֶ��������е�λ��
         */
        template<class T>
        class TXTField
        {
        public:
            TXTField()
                :m_Pos(INI_INVALID_POS)
            {}
            ///����Field
            const T & getField() const
            {
                return m_Field;
            }
            void setField(const T & paramField)
            {
                m_Field = paramField;
            }
            ///����pos
            XInt getPos() const
            {
                return m_Pos;
            }
            void setPos(XInt paramPos)
            {
                m_Pos = paramPos;
            }
        private:
            XInt m_Pos;     ///<λ��
            T m_Field;      ///<�ֶ�����
        };
        ///�ı�ͨ����Ŀ
        template<class T>
        class TXTIniEntryCommon : public TXTIniEntry<T>
        {
        public:
                typedef TXTIniEntry<T> Inherited;
        public:
            TXTIniEntryCommon() 
            {}
            ///ȡ����Ŀ������
            /**
                @return XIET_COMMON_ENTRY
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const 
            { 
                return EIET_COMMON_ENTRY; 
            }
            ///ȡ��Ŀ������Key
            /**
                @return ������Ŀ������Key
            */
            TXTField<T> & getKey() 
            { 
                return m_Key; 
            }
            ///ȡ��Ŀ��ֵ
            /**
                @return ������Ŀ��ֵ
            */
            TXTField<T> & getValue() 
            { 
                return m_Value; 
            }
            ///ȡ��ǰ��Ŀ��ע��
            TXTField<T> & getComment() 
            {
                return m_Comment;
            }
            ///�ı�ֵ
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
            ///��Ϊע��
            void ChangeComment(const T & paramComment)
            {
                T strTemp;
                if( paramComment.isNotEmpty()) //�������Ϊ��
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
                    if( strTemp.isEmpty() ) //����ǿմ�����ɾ��ע��
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
                        if( m_Comment.getPos() == INI_INVALID_POS ) //�����û��ע��
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
            ///�����ı���Ŀ��
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
            TXTField<T> m_Key;          ///<��Ŀ������Key
            TXTField<T> m_Value;        ///<��Ŀ��ֵ
            TXTField<T> m_Comment;      ///<ע��
        };

                //----------------------------------------------------------------------------------------
        ///�����ļ�����Ŀ
        /**
            ע���У��հ��л�δ��ʶ�����Ŀ�У�Ϊ����Ŀ��
        */
        template<class T>
        class TXTIniEntryTextLine : public TXTIniEntry<T>
        {
        public:
            typedef TXTIniEntry<T> Inherited;
        public:
            TXTIniEntryTextLine() {}
            ~TXTIniEntryTextLine() {}
            ///ȡ����Ŀ������
            /**
                @return EIET_TEXT_LINE
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const { return EIET_TEXT_LINE; }
            ///ȡ�ı��е�����
            const T & getText() const
            {
                return Inherited::getOriginalText();
            }
            ///�����ı��е�����
            void setText(const T & paramText)
            {
                setOriginalText(paramText);
            }
        };

        //----------------------------------------------------------------------------------------
        ///�����ļ��Ķ���
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
            ///ȡ����Ŀ������
            /**
                @return EIET_SECTION
                @see EIniEntryType
            */
            EIniEntryType getEntryType() const { return EIET_SECTION; }
            ///ȡ����
            /**
                @return ���ض���
             */
            const T & getSectionName() const 
            { 
                return m_SectionName; 
            }
            ///���ö���
            /**
                @param [in] paramSectionName ���õĶ���
            */
            void setSectionName(const T & paramSectionName) 
            { 
                m_SectionName = paramSectionName; 
            }
            ///ȡ��Ŀ�ĸ���
            /**
                @return ������Ŀ�ĸ���
            */
            XInt getLength() const 
            { 
                return m_ArrayEntry.getLength(); 
            }
            ///ȡָ���±����Ŀ
            /**
                @param [in] paramIndex ָ�����±�
                @return ����ָ���±����Ŀָ��
             */
            TXTIniEntry<T> * getEntry(XInt paramIndex) 
            { 
                return m_ArrayEntry[paramIndex]; 
            }
            ///ȡָ�����Ƶ���Ŀ
            /**
                @param [in] paramIdent ָ������Ŀ����
                @return �������Ŀ���ڣ��򷵻���Ŀ��ָ�룬���򷵻�NULL
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
            ///����������Ŀ
            /**
                @param [in] paramEntry ���������Ŀ
             */
            void AppendEntry(TXTIniEntry<T> * paramEntry) 
            { 
                m_ArrayEntry.Append(paramEntry); 
            }
            ///ָ��λ�ò�����Ŀ
            /**
                @param [in] paramIndex ָ����λ��
                @param [in] paramEntry ���������Ŀ
             */
            void InsertEntry(XInt paramIndex,TXTIniEntry<T> * paramEntry) 
            { 
                m_ArrayEntry.Insert(paramIndex,paramEntry); 
            }
            ///ɾ��ָ������Ŀ
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
            ///������е���Ŀ
            void Clear()
            {
                for(XInt i=m_ArrayEntry.getLastIndex(); i >= 0; i--)
                {
                    delete m_ArrayEntry[i];
                }
                m_ArrayEntry.Clear();
            }   
            ///����comment
            void setComment(const T & paramComment)
            {
                m_Comment = paramComment;
            }
            const T & getComment() const
            {
                return m_Comment;
            }
            ///����commentPos
            void setCommentPos(XInt paramPos)
            {
                m_CommentPos = paramPos;
            }
            XInt getCommentPos() const
            {
                return m_CommentPos;
            }
            ///����section��
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
            ///ע�ͱ仯
            void ChangeComment(const T & paramComment)
            {
                T strTemp;
                if( paramComment.isNotEmpty()) //�������Ϊ��
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
                    if( strTemp.isEmpty() ) //����ǿմ�����ɾ��ע��
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
                        if( m_CommentPos == INI_INVALID_POS ) //�����û��ע��
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
            T m_SectionName;                    ///<������
            T m_Comment;                        ///<ע��
            XInt m_CommentPos;
            XDynamicArray<TXTIniEntry<T> *>m_ArrayEntry; ///<��Ŀ����
        };
        ///�ı��еĶ�дʵ��
        template<class T>
        class TXTIni
        {
        public:
            ///�����󣬵�ǰ�е�����
            enum EnumParseTextType
            {
                EPTT_TEXT = 1,                  ///<�ı���
                EPTT_SECTION = 2,               ///<section
                EPTT_ENTRY = 3,                 ///<��Ŀ
                EPTT_COMMENT = 4,               ///<ע����
                EPTT_UNKNOW = 5,                ///<δ֪��
                EPTT_SPACE = 6,                 ///<����
                EPTT_FOCRE_DWORD = 0x7fffffff   
            };
            enum EnumLineStatus
            {
                ELS_ENTER = 1,                  ///<���س�
                ELS_NEW_LINE = 2,               ///<������
                ELS_NORMAL = 3,                 ///<��ͨ״̬
                ELS_FOCRE_DWORD = 0x7fffffff
            };
			enum EnumUTF_BOM_Lead
			{
				UTF_LEAD_0 = 0,		//BOM��һ���ֽ�
				UTF_LEAD_1 = 1,		//BOM�ڶ����ֽ�
				UTF_LEAD_2 = 2,		//BOM�������ֽ�
				UTF_LEAD_END = 3,	//BOM������λ��
				UTF_BOM_SIZE = 3,	//BOM���ֽ���
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
            ///�������ļ����Ĺ��캯��
            /**
                @param [in] aFileName ��ʼ�������ļ���
            */
            TXTIni(const T & paramFileName)
                :m_FileName(paramFileName)
            {
				setUTFBom(4);
			}
            ///�幹����
            ~TXTIni() 
            { 
                Clear(); 
            }
            ///ȡ����section�ĸ���
            XInt getSectionCount() const
            {
                return m_ArraySection.getLength();
            }       
            ///ȡָ���±��section
            /**
                @param [in] paramIndex ָ�����±�
                @return XMLIniSection * ����ָ����section
                    - NULL ��ʾ�±�Խ�磬δȡ��ָ���±��section
                    - != NULL ��ʾȡ����ָ���±��section
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

            ///ȡָ�����Ƶ�section
            /**
                ȡָ��section���Ƶ�section
                @param [in] paramSectionName
                @return XMLIniSection * ����section
                    - NULL ��ʾδ�Ҹ����Ƶ�section
                    - != NULL ��ʾ�ҵ���section
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

            ///ɾ��ָ���±��section
            /**
                ɾ��ָ���±��section
                @param [in] paramIndex ָ�����±꣬��Чֵ��[0,getSectionCount)֮��
                @return bool ɾ�����
                    - true ��ʾɾ���ɹ�
                    - false ��ʾɾ��ʧ��
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
            ///ɾ��ָ�����Ƶ�section
            /**
                ɾ��ָ��section���Ƶ�section
                @param [in] paramSectionName ָ��section������
                @return bool ɾ���Ľ��
                    - true ��ʾɾ���ɹ�
                    - false ��ʾɾ��ʧ��
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
            ///׷��һ��section 
            /**
                ��section���������һ��section�������section�Ѿ����ڣ��򲻲���
                @param [in] paramSectionName ����section������
                @return XMLIniSection * ���ز����section����ָ��
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
            ///����һ��section
            /**
                ��ָ�����±��λ�ã�����һ��section,�����section�Ѿ����ڣ��򲻲��롣
                ���ָ�����±겻��[0,getSectionCount)֮�䣬�������׷��һ��section
                @param [in] paramSectionName ����section������
                @param [in] paramSectionIndex �����λ��
                @return XMLIniSection * ���ز����section����ָ��
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
            //�����ļ��Ļ����ӿ�
            ///��ȡXInt���͵�����
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramDefault ȱʡֵ
                @return ���û���ҵ�ָ������Ŀ���򷵻�ȱʡֵ
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
            ///��ȡBool���͵�����
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramDefault ȱʡֵ
                @return ���û���ҵ�ָ������Ŀ���򷵻�ȱʡֵ
            */
            bool ReadBool(const T & paramSectionName,const T & paramIdent,bool paramDefault) 
            {
                return ReadInt(paramSectionName, paramIdent, paramDefault?1:0) != 0;
            }
            ///��ȡstring���͵�����
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramDefault ȱʡֵ
                @return ���û���ҵ�ָ������Ŀ���򷵻�ȱʡֵ
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
            ///��ȡָ����Ŀ��ע��
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @return ���û��,�򷵻ؿմ�
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
            ///д��ָ����Ŀ��ע��
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramComment ע��
            */
            void WriteComment(const T & paramSectionName, const T & paramIdent, const T & paramComment)
            {
                TXTIniEntryCommon <T>* pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->ChangeComment(paramComment);
            }
            ///׷��һ���ı���
            /**
                @param [in] paramSectionName ������
                @param [in] paramText �ı�����
             */
            void AppendText(const T & paramSectionName, const T & paramText = "")
            {
                TXTIniSection<T> * pSection = getSection(paramSectionName,true);
                TXTIniEntryTextLine<T> *pEntry = new TXTIniEntryTextLine<T>();
                pEntry->setText(paramText);
                pSection->AppendEntry(pEntry);
            }
            ///д��һ��ָ����XInt������Ŀ
            /**
                ���ָ������Ŀ���棬��ᴴ������Ŀ
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramValue ��Ŀֵ
             */
            void WriteInt(const T & paramSectionName,const T & paramIdent,XInt paramValue)
            {
                TXTIniEntryCommon<T> * pEntry = getEntry(paramSectionName, paramIdent, true);
                //T strValue = paramValue;
                pEntry->ChangeValue(paramValue);
            }
            ///д��һ��ָ����Bool������Ŀ
            /**
                ���ָ������Ŀ���棬��ᴴ������Ŀ
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramValue ��Ŀֵ
            */
            void WriteBool(const T & paramSectionName,const T &paramIdent,bool paramValue)
            {
                WriteInt(paramSectionName, paramIdent, paramValue?1:0 );
            }
            ///д��һ��ָ����String������Ŀ
            /**
                ���ָ������Ŀ���棬��ᴴ������Ŀ
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @param [in] paramValue ��Ŀֵ
            */
            void WriteString(const T & paramSectionName,const T &paramIdent,const T & paramValue)
            {
                TXTIniEntryCommon<T> * pEntry = getEntry(paramSectionName,paramIdent,true);
                pEntry->ChangeValue(paramValue);
            }
            ///ɾ��ָ������Ŀ
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
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
            ///������е���Ŀ�Ͷ�
            void Clear()
            {
                for(XInt i=m_ArraySection.getLength()-1; i>= 0; i--)
                {
                    delete m_ArraySection[i];
                }
                m_ArraySection.Clear();
                m_HeadList.Clear();
            }       
            ///�ж�ָ����Ŀ�Ƿ����
            /**
                @param [in] paramSectionName ������
                @param [in] paramIdent ��Ŀ����
                @return ������Ŀ�������
                    - true ��ʾ��Ŀ����
                    - false ��ʾ��Ŀ������
            */
            bool isExists(const T & paramSectionName,const T & paramIdent) const
            {
                return getEntry(paramSectionName,paramIdent) != NULL;
            }
            ///װ������
            bool Load(std::istream & paramStream);
            bool Load(const T & paramFileName)
            {
                setFileName(paramFileName);
				std::ifstream i(getFileName().c_str(),std::ios::binary);
				if( !i.is_open()) //���û�д�
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
            ///���������ļ���
            /**
                @param [in] paramFileName ָ���������ļ�����
            */
            void setFileName(const T & paramFileName) 
            { 
                m_FileName = paramFileName; 
            }
            ///ȡ�����ļ���
            /**
                @return ���������ļ���
             */
            const T  & getFileName() const 
            { 
                return m_FileName; 
            }
            ///ȡһ��ָ�����������Ƶ���Ŀ
            /**
                @param [in] paramSectionName ָ���Ķ���
                @param [in] paramIdent ָ������Ŀ����
                @return ����ȡ�õĽ��
                    - !=NULL ���ض�Ӧ��Ŀ��ָ��
                    - NULL ��ʾδ�ҵ���Ӧ������
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
            ///ȡһ����ͨ����Ŀ
            /**
                ȡһ��ָ�����������Ƶ���Ŀ�������Ŀ�����ڵĻ����Ƿ�Ҫ�Լ�����һ��
                @param [in] paramSectionName ָ���Ķ���
                @param [in] paramIdent ָ������Ŀ����
                @param [in] paramAutoInsert �Ƿ��Զ�����
                    - true ��ʾ��Ŀ�����ڵĻ������Զ�����һ����Ŀ
                    - false ��ʾ��Ŀ�����ڵĻ������Զ�����
                @return ����ȡ�õĽ��
                    - !=NULL ���ض�Ӧ��Ŀ��ָ��
                    - NULL ��ʾδ�ҵ���Ӧ������
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
            ///ȡһ��ָ��������section
            /**
                ȡһ��ָ��������section�����section�����ڵĻ����Ƿ�Ҫ�Լ�����һ��
                @param [in] paramSectionName ָ���Ķ���
                @param [in] paramAutoInsert �Ƿ��Զ�����
                    - true ��ʾsection�����ڵĻ������Զ�����һ��section
                    - false ��ʾsection�����ڵĻ������Զ�����
                @return ����ȡ�õĽ��
                    - !=NULL ���ض�Ӧ��Ŀ��ָ��
                    - NULL ��ʾδ�ҵ���Ӧ������
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
            ///ȡ�����ļ���ʼǰ���ı����б�
            TXTIniHeadList<T> * getHeadList() 
            {
                return &m_HeadList;
            }
        private:


            ///��ȡһ��
            bool ReadLine(std::istream & paramInput, T & paramLine);
            ///д��һ��
            void WriteLine(std::ostream & paramOutput,const T & paramLine);
            ///����һ��
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
				����Bomģʽ
				@param [in] paramBomMode BOMģʽ
					- 1: 0xefU 0xbbU 0xbfU
					- 2: 0xefU 0xbfU 0xbeU
					- 3: 0xefU 0xbfU 0xbfU
					- 4: 0x00U 0x00U 0x00U
				@return int �������ý��
					- ERR_OK ������Ч
					- ERR_FAIL ����ʧ��

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
            ///�����õ���ʱ����
            
            T m_ParseKey;       ///<������Key
            XInt m_ParseKeyPos;

            T m_ParseValue;     ///<������Value
            XInt m_ParseValuePos;

            T m_ParseSection;   ///<������section
            XInt m_ParseSectionPos;

            T m_ParseComment;   ///<������ע��
            XInt m_ParseCommentPos;
                    
            T m_Temp;           ///<�����ı����õ���ʱ����
            XChar m_Buffer[128];
            XInt m_BufferStart;
            XInt m_BufferCount;
        private:
			/*
				UTF-8��BOM��Ϣ�������UTF-8��ʽ���ļ�������BOM��Ϣ����ôm_UTF8HasBom��ֵ����Ϊtrue������¼��Ӧ��bomֵ
				Ҳ���Լ�����BOM��Ϣ�������ʱ����õ�
			*/
			bool m_UTF8HasBom;
			XByte m_UTF_LEAD[4];

		private:
            XDynamicArray<TXTIniSection<T> *>m_ArraySection; ///��Ŀ������
            T m_FileName;                           ///<�����ļ���
            TXTIniHeadList<T> m_HeadList;
        };

        ///д��һ��
        template<class T>
        void TXTIni<T>::WriteLine(std::ostream & paramOutput,const T & paramLine)
        {
            const typename T::StringChar chEnter = 0x0d;
            const typename T::StringChar chLine =  0x0a;
            paramOutput << paramLine.c_str() << chEnter << chLine;
        }
        ///��ȡһ��
        template<class T>
        bool TXTIni<T>::ReadLine(std::istream & paramInput, T & paramLine)
        {
            paramLine.ToEmptyString();
            EnumLineStatus elsStatus = ELS_NORMAL;
            while(paramLine.getLength() < 4096) //���û�г�����󳤶�
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
                //���ҽ�β��
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
        ///����һ��
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
                if( bSkipSpace ) //�����ո�
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
                case 3: //section ���
                    {
                        if( string_utils::isIniComment(ch))
                        {
                            m_ParseCommentPos = iPos;
                            paramLine.SubString(iPos,iLength - iPos, m_ParseComment); //��ȡע��
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
                        if( ch ==  '#' || ch == ';' )  //���ֱ�Ӷ�ȡע��
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
                            else //���ǰ���Ƿǿո��ַ�
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
        ///װ���ı��ļ���ini
        template<class T>
		bool TXTIni<T>::Load(std::istream & paramStream)
        {
            TXTIniSection<T> * pNowSection = NULL;
			
			//std::ifstream i(getFileName().c_str(),std::ios::binary);
			std::istream & i = paramStream;
            T strLine;
            //if( !i.is_open()) //���û�д�
            //{
            //    return false; 
            //}
            Clear();
            strLine.ensureCapacity(4096);
            
            m_Temp = 0;         ///<�����ı����õ���ʱ����
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
    //�򻯶�������
    typedef xmlini::XMLIni<XAnsiString> XIniXML;
    typedef txtini::TXTIni<XAnsiString> XIniText;
}
#endif
