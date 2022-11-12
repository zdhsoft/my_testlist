///ͨ�ÿ⶯̬����ģ����
/**
 * ͨ�ÿ�5.0��<br>
 * ����һ��������,������Ԫ�ش����һ����������顣������Ԫ�ز��ҷ���Ϊ���ֲ��ҡ�
 * ������ṩ������ص����й���.���ϵķ����н���*,����+,�-,����֮��,����*=,+=,-=�ȶ�Ӧ����.
 * ������ͨ��Contains,���ָ��Ԫ���Ƿ��ڼ�����
 * @author zdhsoft(ף����)
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
    ///��������ļ���ģ����
    template<class T,class Array = XDynamicArray<T> >
    class XSet
    {
    public:
        typedef T ElementType;
        typedef ElementType * PElementType;
    public:
        ///ȱʡ���캯��
        XSet()
        {}
        ///ȱʡ�������캯��
        XSet(const XSet<T,Array> & paramSet)
            :m_Data(paramSet.m_Data)
        {}
        ///ָ����Сֵ�����ֵ�Ĺ����캯��
        XSet(const T & paramMin,const T & paramMAX,XInt paramRepareLength = 0);
        ///ȡ��Ч������Ԫ�ظ���
        XInt getLength() const
        {
            return  m_Data.getLength();
        }
        ///�жϼ����Ƿ�Ϊ��
        /**
            @return ���ؼ��Ľ��
              - true ��ʾ����Ϊ��
              - false ��ʾ���ϲ�Ϊ��
        */
        bool isEmpty() const 
        {
            return m_Data.isEmpty();
        }
        bool isNotEmpty() const
        {
            return m_Data.isNotEmpty();
        }
        ///�Ƿ�Ϊ��һ���±�
        /**
            @param paramIndex �������±�
            @return ���ؼ��Ľ�� 
              - true ��ʾ�ǵ�һ���±�
              - false ��ʾ���ǵ�һ���±�
        */
        bool isFirstIndex(XInt paramIndex) const
        {
            return m_Data.isFirstIndex(paramIndex);
        }
        ///�Ƿ�Ϊ���һ���±�
        /**
            @param paramIndex �������±�
            @return ���ؼ��Ľ�� 
              - true ��ʾ�����һ���±�
              - false ��ʾ�������һ���±�
        */
        bool isLastIndex(XInt paramIndex) const
        {
            return m_Data.isLastIndex(paramIndex);
        }
        ///�Ƿ�Ϊ��Ч���±�
        /**
            @param paramIndex �������±�
            @return ���ؼ��Ľ�� 
              - true ��ʾ��Ч�±�
              - false ��ʾ��Ч�±�
        */
        bool isValidIndex(XInt paramIndex) const
        {
            return m_Data.isValidIndex(paramIndex);
        }
        ///ȡ��ǰ���ϵ�����
        XInt getCapacity() const
        {
            return m_Data.getCapacity();
        }
        ///ȡָ���±�ļ���Ԫ��
        /**
            @param [in] paramIndex ָ�����±�
            @return ����ָ���±������
            @exception �������Խ�磬���׳�XEOutOfRange�쳣
        */
        const T & getElement(XInt paramIndex) const
        {
            return m_Data.getElement(paramIndex);
        }
        ///ȷ����С����
        /**
            ȷ����С�����������������������չ����
            @param [in] minimumCapacity ȷ�ϵ���С����
        */
        void ensureCapacity(XInt paramMinimunCapacity)
        {
            m_Data.ensureCapacity(paramMinimunCapacity);
        }
        ///ȡ��һ���±�
        /**
            @return ���ص�һ���±�
              - ARRAY_INVALID_INDEX ��ʾ��Ч�±�
              - 0 ��ʾ��Ч��һ���±�
        */
        XInt getFirstIndex() const
        {
            return m_Data.getFirstIndex();
        }
        ///ȡ���һ���±�
        /**
            @return �������һ���±�
              - ARRAY_INVALID_INDEX ��ʾ��Ч�±�
              - >=0 ��ʾ��Ч���һ���±�
        */
        XInt getLastIndex() const 
        {
            return m_Data.getLastIndex();
        }
        ///ȡ���ϵ��������
        XInt getMaxCapacity() const
        {
            return m_Data.getMaxCapacity();
        }
        ///�������
        void Clear()
        {
            m_Data.Clear();
        }
        ///�򼯺��м���һ��Ԫ��
        XSet<T,Array> & operator << (const T & paramData) //����һ��Ԫ��
        {
            Add(paramData);
            return *this;
        }
        XSet<T,Array> & operator ,( const T & paramData)
        {
            Add(paramData);
            return *this;
        }
        ///�򼯺���ɾ��һ��Ԫ��
        XSet<T,Array> & operator >> (const T & paramData) //ɾ��һ��Ԫ��
        {
            Remove(paramData);
            return *this;
        }
        ///�򼯺ϼ���һ�����ϵ�Ԫ��
        XSet<T,Array> & operator << (const XSet<T,Array> & paramRightSet) //����һ�������е���Ԫ��
        {
            Add(paramRightSet);
            return *this;
        }
        ///�򼯺��У�ɾ��һ�����ϵ�Ԫ��
        XSet<T,Array> & operator >> (const XSet<T,Array> & paramRightSet) //ɾ��һ�������е���Ԫ��
        {
            Remove(paramRightSet);
            return *this;
        }
        ///�򼯺��м���һ��Ԫ��
        /**
            @param paramData �������Ԫ��
        */
        void Add(const T & paramData)     //����һ��Ԫ��
        {
            _Insert(paramData);
        }
        ///�򼯺��У�����һ�����ϵ�Ԫ��
        void Add(const XSet<T,Array> & paramRightSet); //����һ�������е���Ԫ��
        ///ɾ��һ��ָ����Ԫ��
        void Remove(const T & paramData)  //ɾ��һ��Ԫ��
        {
            XInt iIndex = _Contains(paramData);
            if( iIndex != ARRAY_INVALID_INDEX ) m_Data.Remove(iIndex);
        }
        ///ɾ����һ���������е�Ԫ��
        void Remove(const XSet<T,Array> & paramRightSet);//ɾ��һ�������е���Ԫ��
        ///���Ԫ���Ƿ������������
        bool Contains(const T & paramData) const
        {
            return _Contains(paramData) != ARRAY_INVALID_INDEX;
        }
        ///���ָ�����ϵ�Ԫ���Ƿ������������
        bool Contains(const XSet<T,Array> & paramRightSet) const;
        ///����[]�����
        /**
            ����[]�������ȡָ���±�ļ���Ԫ��
            @param paramIndex �±�ֵ
            @return ����ָ���±��Ԫ�صĳ�������
        */
        const T & operator[](XInt paramIndex) const
        {
            return m_Data[paramIndex];
        };
        ///ȱʡ�������ƺ���
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
        ///�������ϲ������
        XSet<T,Array> operator-(const XSet<T,Array> & paramRightSet) const; //�
        ///�������ϲ���������
        /**
            @param paramRightSet ��������
            @return ���ز���������
        */
        XSet<T,Array> operator+(const XSet<T,Array> & paramRightSet) const //����
        {
            XSet<T,Array> aSet(*this);
            aSet.Add(paramRightSet);
            return aSet;
        }
        ///�������Ͻ���������
        XSet<T,Array> operator*(const XSet<T,Array> & paramRightSet) const; //����
        ///���ϵ��Ӽ�����
        XSet<T,Array> SubSet(const T & paramMinData,const T & paramMaxData) const;
        ///���ϲ����
        XSet<T,Array> & operator-=(const XSet<T,Array> & paramRightSet); //�
        ///���ϲ�������
        XSet<T,Array> & operator+=(const XSet<T,Array> & paramRightSet) //����
        {
            Add(paramRightSet);
            return *this;
        }
        ///���Ͻ�������
        XSet<T,Array> & operator*=(const XSet<T,Array> & paramRightSet); //����
        ///ȡָ��Ԫ�ص��±�
        /**
            @param paramData ָ����Ԫ��
            @return ����ָ��Ԫ�ص��±�
              - ARRAY_INVALID_INDEX ��ʾδ�ҵ����Ԫ��
              - ����ֵ����ʾ��Ԫ�ص��±�
        */
        XInt getIndex(const T & paramData) 
        { 
            return _Contains(paramData); 
        }
        ///�Ƚ����������Ƿ���ͬ
        bool operator == (const XSet<T,Array> & paramRightSet) const;
        ///�Ƚ����������Ƿ���ͬ
        bool operator != (const XSet<T,Array> & paramRightSet) const;
    private:
        ///�����������Ƿ����ָ��Ԫ��
        XInt _Contains(const T & paramData) const;//���ö��ֲ���
        ///�򼯺��в���һ��Ԫ��
        void _Insert(const T & paramData); //����һ��Ԫ��
    private:
        Array m_Data;//��ż������ݵ�����
    };
    //----------------------------------------------------------------------------
    /**
        �򼯺��м�����һ�����ϵ�Ԫ��
        @param paramRightSet �����Ԫ�ؼ���
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
        @param paramRightSet Ҫɾ��Ԫ�صļ���
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
        �����������Ƿ����ָ��Ԫ�ء�ʹ�õĲ��ҵķ����Ƕ��ֲ���
        @param paramData ������Ԫ��
        @return ����鵽��Ԫ�ص��±�
          - ARRAY_INVALID_INDEX ��ʾû���ҵ����Ԫ��
          - ����>=0��ֵ����ʾ�ҵ���
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
        ��鵱ǰ���ϣ��Ƿ����ָ���ļ���
        @param paramRightSet Ҫ���ļ���
        @return ���Ľ��
          - true ��ʾ����ָ���ļ���
          - false ��ʾ������ָ���ļ���
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
        �򼯺��в���һ��Ԫ�ء��ⷽ����˽�з���������XSet�ڲ�����
        @param paramData Ҫ�����Ԫ��
    */
    template<class T,class Array>
    void XSet<T,Array>::_Insert(const T & paramData)
    {
        XInt iLength = m_Data.getLength();
        if( iLength <= 0 ) m_Data.Append( paramData );
        else
        {
            //���Ҳ����λ��
            XInt Low = 0,High = iLength-1,Mid;
            while( Low <= High )
            {
                Mid = (Low + High) /2;
                const T & Tmp = m_Data[Mid];
                if( Tmp == paramData ) return; //������и�Ԫ�أ��򷵻�
                else if ( Tmp > paramData ) High = Mid -1;
                else Low = Mid + 1;
            }
            if( m_Data[Mid] > paramData ) m_Data.Insert(Mid,paramData);
            else m_Data.Insert(Mid+1,paramData);
        }
    }
    //----------------------------------------------------------------------------
    /**
        ָ����Сֵ�����ֵ�Ĺ��캯��
        @param paramMin ��Сֵ
        @param paramMax ���С
        @param paramRepareLength ׼���������С
    */
    template<class T,class Array>
    XSet<T,Array>::XSet(const T & paramMin,const T & paramMax,XInt paramRepareLength)
    {
        ensureCapacity(paramRepareLength); //ȷ������
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
        ���ϵĲ����������������᷵��һ���µļ��ϣ���������е�Ԫ�أ�����������������
        ��Ԫ�أ����ֲ����������ϵĹ���Ԫ��
        @param paramRightSet ��һ�������
        @return �����������ϲ�Ľ��
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
        ���ϵĽ�������������������᷵��һ���µļ��ϣ���������е�Ԫ�أ����������ϵĹ���
        ��Ԫ��
        @param paramRightSet ��������
        @return ���ؽ�������Ľ��
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
        �Ƚ����������Ƿ���ͬ
        @param paramRightSet �Ƚϵļ���
        @return ���رȽϵĽ��
          - true ��ʾ����������ͬ
          - false ��ʾ�������ϲ���ͬ
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
    ������������Ƿ���ͬ
        @param paramRightSet �Ƚϵļ���
        @return ���رȽϵĽ��
          - true ��ʾ�������ϲ���ͬ
          - false ��ʾ����������ͬ
    */
    template<class T,class Array>
    inline bool XSet<T,Array>::operator != (const XSet<T,Array> & paramRightSet) const
    {
        return !operator == (paramRightSet);
    }
    //----------------------------------------------------------------------------
    /**
        �����������Զ��󣬲�������ŵ���ǰ������
        @param paramRightSet �����
        @return ���ص�ǰ���ϵ�����
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
                    tmp *= paramRightSet;      //ȡ���������ϵĽ���
                    *this += paramRightSet;    //ȡ���������ϵĲ���
                    Remove(tmp);     //ɾ���������ϵĽ���
                }
            }
        }  
        return *this;
    }
    //----------------------------------------------------------------------------
    /**
        ��������������Զ��󣬲�������ŵ���ǰ������
        @param paramRightSet ��������
        @return ���ص�ǰ���ϵ�����
    */
    template<class T,class Array>
    XSet<T,Array> & XSet<T,Array>::operator*=(const XSet<T,Array> & paramRightSet)
    {
        if( this != &paramRightSet )
        {
            if( paramRightSet.isEmpty() ) Clear(); //���paramRightSet����Ϊ��,�򽻼�Ϊ��
            else //�����ǰ���ϲ�Ϊ��
            {
                if( !isEmpty() ) //����������϶���Ϊ��
                {
                    
                    for(XInt i = m_Data.getLength() - 1; i>=0; i--)
                    {
                        if( !paramRightSet.Contains(m_Data[i])) m_Data.Remove(i); //���ָ����Ԫ�ز�����,��ɾ��
                    }
                }
            }
        }
        return *this;
    }
    //----------------------------------------------------------------------------
    /**
        �ӵ�ǰ�����У�ȡ��ָ����Χ���Ӽ��е�Ԫ�أ�����Ϊһ���µļ��Ϸ��أ����ص��Ӽ���[paramMinData,paramMaxData]

        @param paramMinData ��С��Ԫ��
        @param paramMaxData ����Ԫ��
        @return �����Ӽ����
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
