///ͨ�ÿ�Mapģ����
/**
 * ͨ�ÿ�5.0��<br>
 * ����һ��ӳ����,�ṩ������Map����,���ӳ���ǻ��ڶ�̬��������,���ҷ�ʽ�ö��ֲ���.<br>
 * ��Ҫ�ķ�����operator[],getValue(),getKey(),operator=,getLength(),RemoveByKey(),RemoveByIndex(),Clear(),Contains()�ȷ���<br>
 * ����֮��,������һЩ������ķ���.getCapaity(),getFirstIndex(),getLastIndex()�ȷ���.
 * ���Map�������ڲ�Entry�ṹ��:SEntry
 * @author zdhsoft(ף����)
 * @version 5.0
 * @date 2010-09-05
 * @file xmap.h
 */
#ifndef _X_MAP_H_
#define _X_MAP_H_
#include <xdynamic_array.h>
namespace zdh
{
    template<class K,class V>
    class XMap
    {   
        ///Map�е���Ŀ
        struct SEntry
        {
            SEntry(const K & paramKey)
                :Key(paramKey)
            {}
            SEntry(const K & paramKey,const V & paramValue)
                :Key(paramKey),Value(paramValue)
            {}
            SEntry(const SEntry & paramEntry)
                :Key(paramEntry.Key),Value(paramEntry.Value)
            {}
            K Key;
            V Value;
        };
    public:
        ///Ĭ�Ϲ��캯��
        XMap() {}
        ///Ĭ�Ͽ������캯��
        XMap(const XMap<K,V> & paramMap);
        ///Ĭ����������
        ~XMap()
        { 
            Clear(); 
        }
        ///�������Ԫ��
        void Clear(bool paramFree = false);
        ///ȷ��map������
        void ensureCapacity(XInt paramMinimumCapacity) 
        { 
            m_Data.ensureCapacity(paramMinimumCapacity); 
        }
        ///ȡmapԪ�صĸ���
        XInt getLength() const 
        { 
            return m_Data.getLength(); 
        }
        //!ȡmap������
        XInt getCapacity() const 
        { 
            return m_Data.getCapacity(); 
        }
        ///ȡmap���������
        XInt getMaxCapacity() const 
        { 
            return 0x7FFFFFF0 / sizeof(SEntry); 
        }
        ///ȡ��һ���±�
        XInt getFirstIndex() const 
        { 
            return m_Data.getFirstIndex(); 
        }
        ///ȡ���һ���±�
        XInt getLastIndex() const 
        { 
            return m_Data.getLastIndex(); 
        }
        ///�ж��Ƿ��ǵ�һ���±�
        bool isFirstIndex(XInt paramIndex) const 
        { 
            return m_Data.isFirstIndex(paramIndex); 
        }
        ///�ж��Ƿ������һ���±�
        bool isLastIndex(XInt paramIndex) const 
        { 
            return m_Data.isLastIndex(paramIndex); 
        }
        ///�ж��Ƿ�����Ч���±�
        bool isValidIndex(XInt paramIndex) const 
        { 
            return m_Data.isValidIndex(paramIndex); 
        }
        ///�ж�map�Ƿ�Ϊ��
        bool isEmpty() const 
        { 
            return m_Data.isEmpty(); 
        }
        ///ȡ��key��Ӧ��Value,������Value������
        /**
            ȡ��key��Ӧ��Value,������Value������
            �����Ӧ��Keyֵ������,����һ����Ŀ,������Key
            @param [in] paramKey Map��Keyֵ
            @return ����Value������ 
         */
        V & operator[](const K & paramKey)
        {
            XInt iIndex = getIndexBykey(paramKey);
            SEntry * pEntry;
            if( iIndex == ARRAY_INVALID_INDEX) 
            {
                pEntry = new SEntry(paramKey);
                InsertEntry(pEntry);
            }else pEntry = m_Data[iIndex];
            return pEntry->Value;
        }
        ///ȡָ���±�Entry��Value��������
        /**
            @param [in] paramIndex Entry���±�
            @return ����Entry��Value��������
         */
        const V & getValue(XInt paramIndex) const
        {
            return m_Data[paramIndex]->Value;
        }
        ///ȡָ���±��Entry��Value����
        /**
            @param [in] paramIndex Entry���±�
            @return ����Entry��Value����
         */
        V & getValue(XInt paramIndex)
        {
            return m_Data[paramIndex]->Value;
        }
        ///ȡָ���±��Entry��Key��������
        /**
            @param [in] paramIndex Entry���±�
            @return ����Entry��Key����
         */
        const K & getKey(XInt paramIndex) const
        {
            return m_Data[paramIndex]->Key;
        }

        ///ȡKey��Ӧ���±�
        XInt getIndexBykey(const K & paramKey) const;
        ///��鵱ǰMap�Ƿ����ָ��Key����Ŀ
        /**
            @param [in] paramKey ָ����Key
            @return ���ؼ����
                - true ��ʾ��ǰMap�а������Key
                - false ��ʾ��ǰMap�в��������Key
         */
        bool Contains(const K & paramKey) const
        {
            return getIndexBykey(paramKey) != ARRAY_INVALID_INDEX;
        }
        ///ɾ��ָ���±����Ŀ
        /**
            @param [in] paramIndex ָ�����±�
         */
        void RemoveByIndex(XInt paramIndex)
        {
            delete m_Data[paramIndex];
            m_Data.Remove(paramIndex);
        }
        ///ɾ��ָ��Key����Ŀ
        /**
            @param [in] paramKey ָ����key
         */
        void RemoveByKey(const K & paramKey)
        {
            XInt paramIndex = getIndexBykey(paramKey);
            if( paramIndex >= 0) RemoveByIndex(paramIndex);
        }
        ///Ĭ�ϸ�ֵ����
        XMap<K,V> & operator = (const XMap<K,V> & paramMap);
    
    private:
        ///����һ����Ŀ
        void InsertEntry(SEntry * paramEntry);
    
    private:
        XDynamicArray<SEntry *> m_Data; ///<Entry����
    };
    //----------------------------------------------------------------------------
    /**
        Ĭ�Ͽ������캯��
        @param [in] paramMap Ŀ��Map
     */
    template<class K,class V>
    XMap<K,V>::XMap(const XMap<K,V> & paramMap)
    {
        XInt iLength = paramMap.getLength();
        for(XInt i=0; i<iLength; i++) m_Data.Append( new SEntry( *paramMap.m_Data[i] ));
    }
    //----------------------------------------------------------------------------
    /**
        Ĭ�����صĸ�ֵ����
        @param [in] paramMap Ŀ��Map
        @return ���ص�ǰMap������
     */
    template<class K,class V>
    XMap<K,V> & XMap<K,V>::operator = (const XMap<K,V> & paramMap)
    {
        if( this != &paramMap )
        {
            Clear();
            XInt iLength = paramMap.getLength();
            for(XInt i=0; i<iLength; i++) m_Data.Append( new SEntry(*paramMap.m_Data[i]) );
        }
        return *this;
    }

    //----------------------------------------------------------------------------
    /**
        ��Map����һ��ָ������Ŀ,Ҫ�������Key��Map�в����ڵ�.
        @param [in] paramEntry Ҫ�������Ŀ
     */
    template<class K,class V>
    void XMap<K,V>::InsertEntry(SEntry * paramEntry)
    {
        if( isEmpty() ) 
        {
            m_Data.Append(paramEntry);
            return;
        }
        else
        {
            XInt iLow = 0,iHigh = m_Data.getLength() - 1,iMid = 0;
            while( iLow <= iHigh )
            {
                iMid = (iLow + iHigh) / 2;
                const SEntry * pEntry = m_Data[iMid];
                if( pEntry->Key > paramEntry->Key ) iHigh = iMid - 1;
                else iLow = iMid + 1;
            }
            if( m_Data[iMid]->Key > paramEntry->Key ) m_Data.Insert(iMid,paramEntry);
            else m_Data.Insert(iMid+1,paramEntry);
        }
    }
    //----------------------------------------------------------------------------
    /**
        ���Map������Entry,��ִ����Ӧ����������
        @param [in] paramFree ����Entry�����־
            - true ��ʾҪ����Entry����
            - false ��ʾ��Ҫ����Entry����
     */
    template<class K,class V>
    void XMap<K,V>::Clear(bool paramFree)
    {
        for(XInt i = m_Data.getLength() -1; i >=0; i--) delete m_Data[i];
        m_Data.Clear(paramFree);
    }
    //----------------------------------------------------------------------------
    /**
        ȡKey��Ӧ���±�,ʹ�ö��ֲ���
        @param [in] paramKey ��Ӧ��Key
        @return ����Key���±�
            - ARRAY_INVALID_INDEX ��ʾû���ҵ���Key
            - >=0 ��ʾ�ҵ����±�ֵ
     */
    template<class K,class V>
    XInt XMap<K,V>::getIndexBykey(const K & paramKey) const
    {
        XInt iLow = 0;
        XInt iHigh = m_Data.getLength() - 1;
        while( iLow <= iHigh )
        {
            XInt iMid = (iLow + iHigh) / 2;
            SEntry * pEntry = m_Data[iMid];
            if( pEntry->Key == paramKey ) return iMid;
            else if ( pEntry->Key > paramKey ) iHigh = iMid - 1;
            else iLow = iMid + 1;
        }
        return ARRAY_INVALID_INDEX;
    }

}
#endif
