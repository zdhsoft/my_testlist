///通用库Map模板类
/**
 * 通用库5.0版<br>
 * 这是一个映射类,提供基本的Map功能,这个映射是基于动态有序数组,查找方式用二分查找.<br>
 * 主要的方法有operator[],getValue(),getKey(),operator=,getLength(),RemoveByKey(),RemoveByIndex(),Clear(),Contains()等方法<br>
 * 除此之外,还提了一些类数组的方法.getCapaity(),getFirstIndex(),getLastIndex()等方法.
 * 这个Map定义了内部Entry结构体:SEntry
 * @author zdhsoft(祝冬华)
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
        ///Map中的条目
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
        ///默认构造函数
        XMap() {}
        ///默认拷贝构造函数
        XMap(const XMap<K,V> & paramMap);
        ///默认析构函数
        ~XMap()
        { 
            Clear(); 
        }
        ///清除所有元素
        void Clear(bool paramFree = false);
        ///确定map的容量
        void ensureCapacity(XInt paramMinimumCapacity) 
        { 
            m_Data.ensureCapacity(paramMinimumCapacity); 
        }
        ///取map元素的个数
        XInt getLength() const 
        { 
            return m_Data.getLength(); 
        }
        //!取map的容量
        XInt getCapacity() const 
        { 
            return m_Data.getCapacity(); 
        }
        ///取map的最大容量
        XInt getMaxCapacity() const 
        { 
            return 0x7FFFFFF0 / sizeof(SEntry); 
        }
        ///取第一个下标
        XInt getFirstIndex() const 
        { 
            return m_Data.getFirstIndex(); 
        }
        ///取最后一个下标
        XInt getLastIndex() const 
        { 
            return m_Data.getLastIndex(); 
        }
        ///判断是否是第一个下标
        bool isFirstIndex(XInt paramIndex) const 
        { 
            return m_Data.isFirstIndex(paramIndex); 
        }
        ///判断是否是最后一个下标
        bool isLastIndex(XInt paramIndex) const 
        { 
            return m_Data.isLastIndex(paramIndex); 
        }
        ///判断是否是有效的下标
        bool isValidIndex(XInt paramIndex) const 
        { 
            return m_Data.isValidIndex(paramIndex); 
        }
        ///判断map是否为空
        bool isEmpty() const 
        { 
            return m_Data.isEmpty(); 
        }
        ///取得key对应的Value,并返回Value的引用
        /**
            取得key对应的Value,并返回Value的引用
            如果对应的Key值不存在,则建立一个条目,存放这个Key
            @param [in] paramKey Map的Key值
            @return 返回Value的引用 
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
        ///取指定下标Entry的Value常量引用
        /**
            @param [in] paramIndex Entry的下标
            @return 返回Entry的Value常量引用
         */
        const V & getValue(XInt paramIndex) const
        {
            return m_Data[paramIndex]->Value;
        }
        ///取指定下标的Entry的Value引用
        /**
            @param [in] paramIndex Entry的下标
            @return 返回Entry的Value引用
         */
        V & getValue(XInt paramIndex)
        {
            return m_Data[paramIndex]->Value;
        }
        ///取指定下标的Entry的Key常量引用
        /**
            @param [in] paramIndex Entry的下标
            @return 返回Entry的Key引用
         */
        const K & getKey(XInt paramIndex) const
        {
            return m_Data[paramIndex]->Key;
        }

        ///取Key对应的下标
        XInt getIndexBykey(const K & paramKey) const;
        ///检查当前Map是否包含指定Key的条目
        /**
            @param [in] paramKey 指定的Key
            @return 返回检查结果
                - true 表示当前Map中包含这个Key
                - false 表示当前Map中不包含这个Key
         */
        bool Contains(const K & paramKey) const
        {
            return getIndexBykey(paramKey) != ARRAY_INVALID_INDEX;
        }
        ///删除指定下标的条目
        /**
            @param [in] paramIndex 指定的下标
         */
        void RemoveByIndex(XInt paramIndex)
        {
            delete m_Data[paramIndex];
            m_Data.Remove(paramIndex);
        }
        ///删除指定Key的条目
        /**
            @param [in] paramKey 指定的key
         */
        void RemoveByKey(const K & paramKey)
        {
            XInt paramIndex = getIndexBykey(paramKey);
            if( paramIndex >= 0) RemoveByIndex(paramIndex);
        }
        ///默认赋值函数
        XMap<K,V> & operator = (const XMap<K,V> & paramMap);
    
    private:
        ///插入一个条目
        void InsertEntry(SEntry * paramEntry);
    
    private:
        XDynamicArray<SEntry *> m_Data; ///<Entry数组
    };
    //----------------------------------------------------------------------------
    /**
        默认拷贝构造函数
        @param [in] paramMap 目标Map
     */
    template<class K,class V>
    XMap<K,V>::XMap(const XMap<K,V> & paramMap)
    {
        XInt iLength = paramMap.getLength();
        for(XInt i=0; i<iLength; i++) m_Data.Append( new SEntry( *paramMap.m_Data[i] ));
    }
    //----------------------------------------------------------------------------
    /**
        默认重载的赋值函数
        @param [in] paramMap 目标Map
        @return 返回当前Map的引用
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
        向Map插入一个指定的条目,要求这个的Key是Map中不存在的.
        @param [in] paramEntry 要插入的条目
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
        清除Map中所有Entry,并执行相应的析构函数
        @param [in] paramFree 重设Entry数组标志
            - true 表示要重设Entry数组
            - false 表示不要重设Entry数组
     */
    template<class K,class V>
    void XMap<K,V>::Clear(bool paramFree)
    {
        for(XInt i = m_Data.getLength() -1; i >=0; i--) delete m_Data[i];
        m_Data.Clear(paramFree);
    }
    //----------------------------------------------------------------------------
    /**
        取Key对应的下标,使用二分查找
        @param [in] paramKey 对应的Key
        @return 返回Key的下标
            - ARRAY_INVALID_INDEX 表示没有找到该Key
            - >=0 表示找到的下标值
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
