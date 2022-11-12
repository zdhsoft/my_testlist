///通用库动态集合模板类
/**
 * 通用库5.0版<br>
 * 这是一个集合类,这个类的元素存放是一个有序的数组。这个类的元素查找方法为二分查找。
 * 这个类提供了类相关的所有功能.集合的方法有交集*,并集+,差集-,除此之后,还有*=,+=,-=等对应方法.
 * 集合类通过Contains,检查指定元素是否在集合中
 * @author zdhsoft(祝冬华)
 * @version 5.0
 * @date 2010-09-05
 * @file xset.h
 */
#ifndef _X_SET_H_
#define _X_SET_H_
#include <xconfig.h>
#include <xdynamic_array.h>
namespace zdh
{
    ///基于数组的集合模板类
    template<class T,class Array = XDynamicArray<T> >
    class XSet
    {
    public:
        typedef T ElementType;
        typedef ElementType * PElementType;
    public:
        ///缺省构造函数
        XSet()
        {}
        ///缺省拷贝构造函数
        XSet(const XSet<T,Array> & paramSet)
            :m_Data(paramSet.m_Data)
        {}
        ///指定最小值和最大值的构函造函数
        XSet(const T & paramMin,const T & paramMAX,XInt paramRepareLength = 0);
        ///取有效的数组元素个数
        XInt getLength() const
        {
            return  m_Data.getLength();
        }
        ///判断集合是否为空
        /**
            @return 返回检查的结果
              - true 表示集合为空
              - false 表示集合不为空
        */
        bool isEmpty() const 
        {
            return m_Data.isEmpty();
        }
        bool isNotEmpty() const
        {
            return m_Data.isNotEmpty();
        }
        ///是否为第一个下标
        /**
            @param paramIndex 被检查的下标
            @return 返回检查的结果 
              - true 表示是第一个下标
              - false 表示不是第一个下标
        */
        bool isFirstIndex(XInt paramIndex) const
        {
            return m_Data.isFirstIndex(paramIndex);
        }
        ///是否为最后一个下标
        /**
            @param paramIndex 被检查的下标
            @return 返回检查的结果 
              - true 表示是最后一个下标
              - false 表示不是最后一个下标
        */
        bool isLastIndex(XInt paramIndex) const
        {
            return m_Data.isLastIndex(paramIndex);
        }
        ///是否为有效的下标
        /**
            @param paramIndex 被检查的下标
            @return 返回检查的结果 
              - true 表示有效下标
              - false 表示无效下标
        */
        bool isValidIndex(XInt paramIndex) const
        {
            return m_Data.isValidIndex(paramIndex);
        }
        ///取当前集合的容量
        XInt getCapacity() const
        {
            return m_Data.getCapacity();
        }
        ///取指定下标的集合元素
        /**
            @param [in] paramIndex 指定的下标
            @return 返回指定下标的引用
            @exception 如果发生越界，则抛出XEOutOfRange异常
        */
        const T & getElement(XInt paramIndex) const
        {
            return m_Data.getElement(paramIndex);
        }
        ///确认最小容量
        /**
            确认最小容量，如果容量不够，则扩展容量
            @param [in] minimumCapacity 确认的最小容量
        */
        void ensureCapacity(XInt paramMinimunCapacity)
        {
            m_Data.ensureCapacity(paramMinimunCapacity);
        }
        ///取第一个下标
        /**
            @return 返回第一个下标
              - ARRAY_INVALID_INDEX 表示无效下标
              - 0 表示有效第一个下标
        */
        XInt getFirstIndex() const
        {
            return m_Data.getFirstIndex();
        }
        ///取最后一个下标
        /**
            @return 返回最后一个下标
              - ARRAY_INVALID_INDEX 表示无效下标
              - >=0 表示有效最后一个下标
        */
        XInt getLastIndex() const 
        {
            return m_Data.getLastIndex();
        }
        ///取集合的最大容量
        XInt getMaxCapacity() const
        {
            return m_Data.getMaxCapacity();
        }
        ///清除集合
        void Clear()
        {
            m_Data.Clear();
        }
        ///向集合中加入一个元素
        XSet<T,Array> & operator << (const T & paramData) //加入一个元素
        {
            Add(paramData);
            return *this;
        }
        XSet<T,Array> & operator ,( const T & paramData)
        {
            Add(paramData);
            return *this;
        }
        ///向集合中删除一个元素
        XSet<T,Array> & operator >> (const T & paramData) //删除一个元素
        {
            Remove(paramData);
            return *this;
        }
        ///向集合加入一个集合的元素
        XSet<T,Array> & operator << (const XSet<T,Array> & paramRightSet) //加入一个集合中的有元素
        {
            Add(paramRightSet);
            return *this;
        }
        ///向集合中，删除一个集合的元素
        XSet<T,Array> & operator >> (const XSet<T,Array> & paramRightSet) //删除一个集合中的有元素
        {
            Remove(paramRightSet);
            return *this;
        }
        ///向集合中加入一个元素
        /**
            @param paramData 被加入的元素
        */
        void Add(const T & paramData)     //加入一个元素
        {
            _Insert(paramData);
        }
        ///向集合中，加入一个集合的元素
        void Add(const XSet<T,Array> & paramRightSet); //加入一个集合中的有元素
        ///删除一个指定的元素
        void Remove(const T & paramData)  //删除一个元素
        {
            XInt iIndex = _Contains(paramData);
            if( iIndex != ARRAY_INVALID_INDEX ) m_Data.Remove(iIndex);
        }
        ///删除另一个集合中有的元素
        void Remove(const XSet<T,Array> & paramRightSet);//删除一个集合中的有元素
        ///检查元素是否在这个集合中
        bool Contains(const T & paramData) const
        {
            return _Contains(paramData) != ARRAY_INVALID_INDEX;
        }
        ///检查指定集合的元素是否在这个集合中
        bool Contains(const XSet<T,Array> & paramRightSet) const;
        ///重载[]运算符
        /**
            重载[]运算符，取指定下标的集合元素
            @param paramIndex 下标值
            @return 返回指定下标的元素的常量引用
        */
        const T & operator[](XInt paramIndex) const
        {
            return m_Data[paramIndex];
        };
        ///缺省拷贝复制函数
        XSet<T,Array> & operator = (const XSet<T,Array> & paramRightSet)
        {
            if( this != & paramRightSet )   
            {
                m_Data = paramRightSet.m_Data;
            }
            return *this;
        }
        XSet<T,Array> & operator = (const T & paramData)
        {
            Clear();
            Add(paramData);
            return *this;
        }
        ///两个集合差集的运算
        XSet<T,Array> operator-(const XSet<T,Array> & paramRightSet) const; //差集
        ///两个集合并集的运算
        /**
            @param paramRightSet 并集集合
            @return 返回并集运算结果
        */
        XSet<T,Array> operator+(const XSet<T,Array> & paramRightSet) const //并集
        {
            XSet<T,Array> aSet(*this);
            aSet.Add(paramRightSet);
            return aSet;
        }
        ///两个集合交集的运算
        XSet<T,Array> operator*(const XSet<T,Array> & paramRightSet) const; //交集
        ///集合的子集运算
        XSet<T,Array> SubSet(const T & paramMinData,const T & paramMaxData) const;
        ///集合差集运算
        XSet<T,Array> & operator-=(const XSet<T,Array> & paramRightSet); //差集
        ///集合并集运算
        XSet<T,Array> & operator+=(const XSet<T,Array> & paramRightSet) //并集
        {
            Add(paramRightSet);
            return *this;
        }
        ///集合交集运算
        XSet<T,Array> & operator*=(const XSet<T,Array> & paramRightSet); //交集
        ///取指定元素的下标
        /**
            @param paramData 指定的元素
            @return 返回指定元素的下标
              - ARRAY_INVALID_INDEX 表示未找到这个元素
              - 其它值，表示该元素的下标
        */
        XInt getIndex(const T & paramData) 
        { 
            return _Contains(paramData); 
        }
        ///比较两个集合是否相同
        bool operator == (const XSet<T,Array> & paramRightSet) const;
        ///比较两个集合是否不相同
        bool operator != (const XSet<T,Array> & paramRightSet) const;
    private:
        ///检查这个集合是否包含指定元素
        XInt _Contains(const T & paramData) const;//采用二分查找
        ///向集合中插入一个元素
        void _Insert(const T & paramData); //插入一个元素
    private:
        Array m_Data;//存放集合数据的数组
    };
    //----------------------------------------------------------------------------
    /**
        向集合中加入另一个集合的元素
        @param paramRightSet 加入的元素集合
    */
    template<class T,class Array>
    void XSet<T,Array>::Add(const XSet<T,Array> & paramRightSet)
    {
        if( this != &paramRightSet )
        {
            for( XInt i = paramRightSet.getLastIndex(); i >= 0; i-- ) Add( paramRightSet[i] );
        }
    }
    //----------------------------------------------------------------------------
    /**
        @param paramRightSet 要删除元素的集合
    */
    template<class T,class Array>
    void XSet<T,Array>::Remove(const XSet<T,Array> & paramRightSet)
    {
        if( this != &paramRightSet )
        {
            for(XInt i = paramRightSet.getLastIndex() ; i>=0; i--) Remove(paramRightSet[i]);
        }
        else Clear();
    }
    //----------------------------------------------------------------------------
    /**
        检查这个集合是否包含指定元素。使用的查找的方法是二分查找
        @param paramData 被检查的元素
        @return 被检查到的元素的下标
          - ARRAY_INVALID_INDEX 表示没有找到这个元素
          - 其它>=0的值，表示找到了
    */
    template<class T,class Array>
    XInt XSet<T,Array>::_Contains(const T & paramData) const
    {
        XInt Low = 0,High = m_Data.getLength() - 1 ,Mid;
        while( Low <= High )
        {
            Mid = (Low + High) /2;
            const T & Tmp = m_Data[Mid];
            if( Tmp == paramData ) return Mid;
            else if ( Tmp > paramData ) High = Mid -1;
            else Low = Mid + 1;
        }
        return ARRAY_INVALID_INDEX;
    }
    //----------------------------------------------------------------------------
    /**
        检查当前集合，是否包括指定的集合
        @param paramRightSet 要检查的集合
        @return 检查的结果
          - true 表示包含指定的集合
          - false 表示不包含指定的集合
    */
    template<class T,class Array>
    bool XSet<T,Array>::Contains(const XSet<T,Array> & paramRightSet) const
    {
        if( this == &paramRightSet ) return true;
        if( paramRightSet.isEmpty() ) return true;
        if( paramRightSet.getLength() > getLength() ) return false;
        for(XInt i = paramRightSet.getLength()-1; i >=0 ; i--)
        {
            if( !Contains(paramRightSet[i]) ) return false;
        }
        return true;
    }
    //----------------------------------------------------------------------------
    /**
        向集合中插入一个元素。这方法是私有方法，仅供XSet内部调用
        @param paramData 要插入的元素
    */
    template<class T,class Array>
    void XSet<T,Array>::_Insert(const T & paramData)
    {
        XInt iLength = m_Data.getLength();
        if( iLength <= 0 ) m_Data.Append( paramData );
        else
        {
            //查找插入的位置
            XInt Low = 0,High = iLength-1,Mid;
            while( Low <= High )
            {
                Mid = (Low + High) /2;
                const T & Tmp = m_Data[Mid];
                if( Tmp == paramData ) return; //如果已有该元素，则返回
                else if ( Tmp > paramData ) High = Mid -1;
                else Low = Mid + 1;
            }
            if( m_Data[Mid] > paramData ) m_Data.Insert(Mid,paramData);
            else m_Data.Insert(Mid+1,paramData);
        }
    }
    //----------------------------------------------------------------------------
    /**
        指定最小值和最大值的构造函数
        @param paramMin 最小值
        @param paramMax 最大小
        @param paramRepareLength 准备的数组大小
    */
    template<class T,class Array>
    XSet<T,Array>::XSet(const T & paramMin,const T & paramMax,XInt paramRepareLength)
    {
        ensureCapacity(paramRepareLength); //确定容量
        if( paramMin > paramMax )
        {
            for( T i = paramMax; i<=paramMin; ++i ) m_Data.Append(i);
        }
        else
        {
            for( T i = paramMin; i<=paramMax; ++i ) m_Data.Append(i);
        }
    }
    //----------------------------------------------------------------------------
    /**
        集合的差集操作，这个操作，会返回一个新的集合，这个集合中的元素，分是属于两个集合
        的元素，但又不是两个集合的共有元素
        @param paramRightSet 另一个差集集合
        @return 返回两个集合差集的结果
    */
    template<class T,class Array>
    XSet<T,Array> XSet<T,Array>::operator - (const XSet<T,Array> & paramRightSet) const
    {
        XSet<T,Array> ret;
        if( this != &paramRightSet )
        {
            for(XInt i = m_Data.getLength() - 1; i>=0; i--)
            {
                const T & data = m_Data[i];
                if( !paramRightSet.Contains( data ) ) ret.Add( data );
            }
            for(XInt i = paramRightSet.getLength() - 1; i>=0 ; i--)
            {
                const T & data = m_Data[i];
                if( !Contains( data ) ) ret.Add( data );
            }
        }
        return ret;
    }
    //----------------------------------------------------------------------------
    /**
        集合的交集操作，这个操作，会返回一个新的集合，这个集合中的元素，是两个集合的共有
        的元素
        @param paramRightSet 交集集合
        @return 返回交集运算的结果
    */
    template<class T,class Array>
    XSet<T,Array> XSet<T,Array>::operator*(const XSet<T,Array> & paramRightSet) const
    {
        XSet<T,Array> ret;
        if( this != & paramRightSet )
        {

            for(XInt i = m_Data.getLength() - 1; i >= 0; i-- )
            {
                const T & data = m_Data[i];
                if( paramRightSet.Contains( data ) ) ret.Add ( data );
            }
        }
        else ret = paramRightSet;
        return ret;
    }
    //----------------------------------------------------------------------------
    /**
        比较两个集合是否相同
        @param paramRightSet 比较的集合
        @return 返回比较的结果
          - true 表示两个集合相同
          - false 表示两个集合不相同
    */
    template<class T,class Array>
    bool XSet<T,Array>::operator == (const XSet<T,Array> & paramRightSet) const
    {
        if( this == &paramRightSet ) return true;
        if( paramRightSet.getLength() != m_Data.getLength() ) return false;

        for(XInt i = m_Data.getLength() -1 ;i >= 0;i--)
        {
            if( m_Data[i] != paramRightSet[i] ) return false;
        }
        return true;
    }
    //----------------------------------------------------------------------------
    /**
    如果两个集合是否不相同
        @param paramRightSet 比较的集合
        @return 返回比较的结果
          - true 表示两个集合不相同
          - false 表示两个集合相同
    */
    template<class T,class Array>
    inline bool XSet<T,Array>::operator != (const XSet<T,Array> & paramRightSet) const
    {
        return !operator == (paramRightSet);
    }
    //----------------------------------------------------------------------------
    /**
        两个集合做差集远算后，并将结果放到当前集合中
        @param paramRightSet 差集集合
        @return 返回当前集合的引用
    */
    template<class T,class Array>
    XSet<T,Array> & XSet<T,Array>::operator-=(const XSet<T,Array> & paramRightSet)
    {
        if( this == &paramRightSet ) Clear();
        else
        {
            if( !paramRightSet.isEmpty() )
            {
                if( isEmpty() ) operator = (paramRightSet);
                else
                {
                    XSet<T,Array> tmp = *this;
                    tmp *= paramRightSet;      //取得两个集合的交集
                    *this += paramRightSet;    //取得两个集合的并集
                    Remove(tmp);     //删除两个集合的交集
                }
            }
        }  
        return *this;
    }
    //----------------------------------------------------------------------------
    /**
        两个集合做交集远算后，并将结果放到当前集合中
        @param paramRightSet 交集集合
        @return 返回当前集合的引用
    */
    template<class T,class Array>
    XSet<T,Array> & XSet<T,Array>::operator*=(const XSet<T,Array> & paramRightSet)
    {
        if( this != &paramRightSet )
        {
            if( paramRightSet.isEmpty() ) Clear(); //如果paramRightSet集合为空,则交集为空
            else //如果当前集合不为空
            {
                if( !isEmpty() ) //如果两个集合都不为空
                {
                    
                    for(XInt i = m_Data.getLength() - 1; i>=0; i--)
                    {
                        if( !paramRightSet.Contains(m_Data[i])) m_Data.Remove(i); //如果指定的元素不存在,则删除
                    }
                }
            }
        }
        return *this;
    }
    //----------------------------------------------------------------------------
    /**
        从当前集合中，取出指定范围的子集中的元素，并做为一个新的集合返回，返回的子集是[paramMinData,paramMaxData]

        @param paramMinData 最小的元素
        @param paramMaxData 最大的元素
        @return 返回子集结果
    */
    template<class T,class Array>
    XSet<T,Array> XSet<T,Array>::SubSet(const T & paramMinData,const T & paramMaxData) const
    {
        const T *max=&paramMaxData;
        const T *min=&paramMinData;
        if( paramMinData > paramMaxData )
        {
            max = &paramMinData;
            min = &paramMaxData;
        }
        XSet<T,Array> retSet;
        XInt iLength = m_Data.getLength();
        for(XInt i = 0; i<iLength;i++)
        {
            const T & data = m_Data[i];
            if( (data >= *min) && (data <= *max) ) retSet.m_Data.Append(data);
        }
        return retSet;
    }
}
#endif
