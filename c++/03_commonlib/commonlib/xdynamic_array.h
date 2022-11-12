///��̬����ģ��
/**
 * ��̬����ģ��
 * �����ṩ��һ����̬�������һ����̬���������ࡣ
 * ��̬����һ�����ڻ����������ͣ��ڲ����ɾ����ʱ�򣬻��ƶ������Ԫ�أ������Ͳ��ʺ϶�������顣
 * ��̬���������������ڶ����ڲ����ɾ������ʱ�򣬲����ƶ�����Ԫ�أ��ƶ����Ƕ����ָ�롣
 * �����ṩ�Ķ�̬����������std::vector<>,�����ﲻ�ṩitertor
 * zdhsoft 2011 ��Ȩ����
 *
 * @file xdynamic_array.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-13
 * company zdhsoft
 */
/**********************************************************************
    �����б�  //��Ҫ��������
    1��һ����̬�������һ����̬����������

    ��ʷ:       //��Ҫ�޸ļ�¼
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-13  1.0             ������ʼ�ļ�
***********************************************************************/
#ifndef _X_DYNAMIC_ARRAY_H_
#define _X_DYNAMIC_ARRAY_H_
#include <xstring.h>
#include <xfunctional.h>
#include <initializer_list>
namespace zdh
{
    const XInt ARRAY_INVALID_INDEX = -1;
    //-----------------------------------------------------------------------------------------------
    ///����ѡ������
    /**
        @param [in] paramArray Ҫ���������
        @param [in] paramCompare Ԫ�رȽϵĶ���
     */
    template<class Array,class Compare>
    void Array_SelectSort(Array & paramArray, const Compare & paramCompare)
    {
        XInt iMaxIndex = paramArray.getLastIndex();

        for(XInt i = paramArray.getFirstIndex(); i < iMaxIndex; i++ )
        {
            XInt iMinValueIndex = i;
            for(XInt j = i + 1; j <= iMaxIndex; j++)
            {
                if( paramCompare(paramArray[j], paramArray[iMinValueIndex])) iMinValueIndex = j;
            }

            if( iMinValueIndex != i ) 
            {
                paramArray.Swap(i, iMinValueIndex);
            }
        }
    }
    //-----------------------------------------------------------------------------------------------
    ///����ѡ������
    /**
        ����Ĭ��ʹ��XFunctions_Less<>����Ƚ϶����ʵ��
        @param [in] paramArray Ҫ���������
     */
    template<class Array>
    inline void Array_SelectSort(Array & paramArray)
    {
        Array_SelectSort(paramArray,XFunctions_Less<typename Array::ElementType>());
    }
    //-----------------------------------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///�����������һ��
    /**
        @param [in] paramArray Ҫ���������
        @param [in] paramLowIndex Ҫ�����������С�±�
        @param [in] paramHighIndex Ҫ��������������±�
        @param [in] paramCompare Ԫ�رȽϵĶ���
        @return XInt ��������Ƚ�Ԫ������λ��
     */
    template<class Array,class Compare>
    XInt Partition( Array & paramArray, XInt paramLowIndex, XInt paramHighIndex, const Compare & paramCompare)
    {
        typedef typename Array::ElementType ElementType;
        ElementType paramElement = paramArray[paramLowIndex];  // ѡȡ����������ıȽϲο�Ԫ��

        while(paramLowIndex < paramHighIndex)
        {    
            while(paramLowIndex < paramHighIndex && paramCompare(paramElement, paramArray[paramHighIndex]))
            {
                -- paramHighIndex;
            }
            if(paramLowIndex < paramHighIndex)
            {
                paramArray[paramLowIndex++] = paramArray[paramHighIndex]; 
            }    
            while (paramLowIndex < paramHighIndex && paramCompare(paramArray[paramLowIndex], paramElement))
            {
                ++ paramLowIndex;
            }
            if(paramLowIndex < paramHighIndex)
            {
                paramArray[paramHighIndex--] = paramArray[paramLowIndex];   
            }    
        } 
        paramArray[paramLowIndex] = paramElement;    // �����������Ƚϲο�Ԫ�ز��뵽������ʵ�λ��
        return paramLowIndex; // ��������Ƚ�Ԫ������λ��
    }

    //-----------------------------------------------------------------------------------------------
    ///�����������
    /**
        @param [in] paramArray Ҫ���������
        @param [in] paramLowIndex Ҫ�����������С�±�
        @param [in] paramHighIndex Ҫ��������������±�
        @param [in] paramCompare Ԫ�رȽϵĶ���
     */
    template<class Array, class Compare>
    void Array_QuickSort(Array & paramArray, XInt paramLowIndex, XInt paramHighIndex, const Compare & paramCompare)
    {
        XInt paramIndex;   // ���ڼ�¼ÿ�λ��ֺ�����Ƚϲο�Ԫ������λ��
        if (paramLowIndex < paramHighIndex)
        {
            paramIndex = Partition(paramArray, paramLowIndex, paramHighIndex, paramCompare);    // ���������һ�ο������򣬻������飬����������Ƚϲο�Ԫ������λ��
            Array_QuickSort(paramArray, paramLowIndex, paramIndex - 1, paramCompare);      // �Ե������еݹ��������
            Array_QuickSort(paramArray, paramIndex + 1, paramHighIndex, paramCompare);     // �Ը������еݹ��������
        }
    }

    //-----------------------------------------------------------------------------------------------
    ///�����������
    /**
        @param [in] paramArray Ҫ���������
        @param [in] paramCompare Ԫ�رȽϵĶ���
     */
    template<class Array,class Compare>
    void Array_QuickSort(Array & paramArray, const Compare & paramCompare)
    {
        XInt iLowIndex, iHighIndex;
        iLowIndex = paramArray.getFirstIndex();
        iHighIndex = paramArray.getLastIndex();
        if (iLowIndex < iHighIndex)
        {
            Array_QuickSort(paramArray, iLowIndex, iHighIndex, paramCompare);
        }
    }

    //-----------------------------------------------------------------------------------------------
    ///�����������
    /**
        ����Ĭ��ʹ��XFunctions_Less<>����Ƚ϶����ʵ��
        @param [in] paramArray Ҫ���������
     */
    template<class Array>
    inline void Array_QuickSort(Array & paramArray)
    {
        Array_QuickSort(paramArray, XFunctions_Less<typename Array::ElementType>());
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    //-----------------------------------------------------------------------------------------------
    ///����ð������
    /**
        @param [in] paramArray Ҫ���������
        @param [in] paramCompare Ԫ�رȽϵĶ���
     */
    template<class Array,class Compare>
    void Array_BubbleSort(Array & paramArray, const Compare & paramCompare)
    {
        for(XInt i = paramArray.getLastIndex(); i>0; i--)
        {
            bool bNotChange = true;
            for(XInt j = 0; j<i; j++)
            {
                if( paramCompare(paramArray[j+1], paramArray[j]) ) 
                {
                    paramArray.Swap(j, j+1);
                    bNotChange = false;
                }
            }
            if( bNotChange ) 
            {
                break; //���û�з�������,��ʾ��������������,��ֱ���˳�
            }
        }
    }

    //-----------------------------------------------------------------------------------------------
    ///����ð������
    /**
        ����Ĭ��ʹ��XFunctions_Less<>����Ƚ϶����ʵ��
        @param [in] paramArray Ҫ���������
     */
    template<class Array>
    inline void Array_BubbleSort(Array & paramArray)
    {
        Array_BubbleSort(paramArray, XFunctions_Less<typename Array::ElementType>());
    }

    //-----------------------------------------------------------------------------------------------
    ///��������ָ��Ԫ�ص��±�
    /**
        @param [in] paramArray Ҫ���ҵ�����
        @param [in] paramElement Ҫ���ҵ�Ԫ��
        @param [in] paramEqual �Ƚ�����Ԫ���Ƿ���ȵĶ���
        @return ���ز��ҽ��
            - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
            - ����ֵ ��ʾ�����������е��±�
     */
    template<class Array,class E,class Compare>
    XInt Array_Find_Normal(const Array & paramArray, const E & paramElement, const Compare & paramEqual)
    {
        XInt iMaxIndex = paramArray.getLastIndex(); 
        for(XInt i = 0; i<=iMaxIndex;  i++ )
        {
            if( paramEqual(paramArray[i], paramElement) ) 
            {
                return i;
            }
        }
        return ARRAY_INVALID_INDEX;
    }

    //-----------------------------------------------------------------------------------------------
    ///��������ָ��Ԫ�ص��±�
    /**
        @param [in] paramArray Ҫ���ҵ�����
        @param [in] paramElement Ҫ���ҵ�Ԫ��
        @return ���ز��ҽ��
            - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
            - ����ֵ ��ʾ�����������е��±�
     */
    template<class Array,class E>
    inline XInt Array_Find_Normal(const Array & paramArray, const E & paramElement)
    {
        return Array_Find_Normal(paramArray, paramElement, XFunctions_Equal<typename Array::ElementType>());
    }

    //-----------------------------------------------------------------------------------------------
    ///���ֲ�������ָ��Ԫ�ص��±�
    /**
        Ҫ��������һ�����������,����Compare��Ӧ�õ���
        @param [in] paramArray Ҫ���ҵ�����
        @param [in] paramElement Ҫ���ҵ�Ԫ��
        @param [in] paramEqual �Ƚ�����Ԫ���Ƿ���ȵĶ���
        @return ���ز��ҽ��
            - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
            - ����ֵ ��ʾ�����������е��±�
     */
    template<class Array,class E,class Compare>
    XInt Array_Find_Binary(const Array & paramArray, const E & paramElement, const Compare & paramCompare)
    {
        XInt Low = paramArray.getFirstIndex(); 
        XInt High = paramArray.getLastIndex();
        XInt Mid;
        XInt iRet = ARRAY_INVALID_INDEX;
        while( Low <= High )
        {
            Mid = (Low + High) /2;
            const typename Array::ElementType & Tmp = paramArray[Mid];
            XInt CompareResult = paramCompare(Tmp, paramElement);
            if( CompareResult == 0 ) 
            {
                iRet = Mid;
                break;
            }
            else if( CompareResult > 0 ) High = Mid -1;
            else Low = Mid + 1;
        }
        return iRet;
    }

    //-----------------------------------------------------------------------------------------------
    ///���ֲ�������ָ��Ԫ�ص��±�
    /**
        Ҫ��������һ�����������,������Ĭ��ʹ�õ���XFunctions_Compare�Ƚ϶���
        @param [in] paramArray Ҫ���ҵ�����
        @param [in] paramElement Ҫ���ҵ�Ԫ��
        @return ���ز��ҽ��
            - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
            - ����ֵ ��ʾ�����������е��±�
     */
    template<class Array,class E>
    inline XInt Array_Find_Binary(const Array & paramArray, const E & paramElement) 
    {
        return Array_Find_Binary(paramArray, paramElement, XFunctions_Compare<const typename Array::ElementType>());
	}
	//һ�������Array��Iterator��
	/*
		�����ṩXArrayIterator����࣬Ŀ����ʹ������֧��C++11��forѭ��
	*/
	template<class Array>
	class XArrayIterator
	{
	public:
		typedef typename Array::ElementType & reference;
		typedef typename Array::ElementType * pointer;


		XArrayIterator()
			:m_Index(ARRAY_INVALID_INDEX), m_Array(nullptr)
		{}

		XArrayIterator(Array * paramArray, XInt paramIndex)
			:m_Index(paramIndex), m_Array(paramArray)
		{}

		XArrayIterator(Array & paramArray, XInt paramIndex)
			:m_Index(paramIndex), m_Array(&paramArray)
		{}

		XArrayIterator(const XArrayIterator<Array> & paramR)
			:m_Index(paramR.m_Index), m_Array(paramR.m_Array)
		{}

		XArrayIterator & operator = (const XArrayIterator<Array> & paramR)
		{
			if (this != &paramR)
			{
				m_Index = paramR.m_Index;
				m_Array = paramR.m_Array;
			}
			return *this;
		}

		XArrayIterator & operator = (Array * paramArray)
		{
			m_Array = paramArray;
			if (isNotNULL(m_Array))
			{
				m_Array = m_Array->getFirstIndex();
			}
			else
			{
				m_Index = ARRAY_INVALID_INDEX;
			}
			return *this;
		}

		bool operator == (const XArrayIterator<Array> & paramR)
		{
			return m_Index == paramR.m_Index && m_Array == paramR.m_Array;
		}

		bool operator != (const XArrayIterator<Array> & paramR)
		{
			return m_Index != paramR.m_Index || m_Array != paramR.m_Array;
		}
		
		reference operator*()
		{	
			return (*m_Array)[m_Index];
		}
		
		const reference operator*() const 
		{	
			return (*m_Array)[m_Index];
		}

		pointer operator->()
		{	
			return &(*m_Array[m_Index]);
		}

		const pointer operator->() const
		{	
			return &(*m_Array[m_Index]);
		}

		XArrayIterator & operator ++()
		{
			if (m_Index != ARRAY_INVALID_INDEX && isNotNULL(m_Array))
			{
				m_Index++;
				if (m_Index >= m_Array->getLength()) m_Index = ARRAY_INVALID_INDEX;
			}
			return *this;
		}


		XArrayIterator operator ++(int)
		{
			XArrayIterator stRet = *this;
			if (m_Index != ARRAY_INVALID_INDEX && isNotNULL(m_Array))
			{
				m_Index++;
				if (m_Index >= m_Array->getLength()) m_Index = ARRAY_INVALID_INDEX;
			}
			return stRet;
		}

		XArrayIterator & operator --()
		{
			if (m_Index != ARRAY_INVALID_INDEX && isNotNULL(m_Array))
			{
				m_Index--;
				if (m_Index < 0) m_Index = ARRAY_INVALID_INDEX;
			}
			return *this;
		}


		XArrayIterator operator --(int)
		{
			XArrayIterator stRet = *this;
			if (m_Index != ARRAY_INVALID_INDEX && isNotNULL(m_Array))
			{
				m_Index--;
				if (m_Index < 0) m_Index = ARRAY_INVALID_INDEX;
			}
			return stRet;
		}

		XArrayIterator & operator +=(XInt paramOffset)
		{
			if (m_Index != ARRAY_INVALID_INDEX && isNotNULL(m_Array))
			{
				m_Index += paramOffset;
				if (!(m_Index >= 0 && m_Index < m_Array->getLength()))
				{
					m_Index = ARRAY_INVALID_INDEX;
				}
			}
			return *this;
		}

		XArrayIterator operator + (XInt paramOffset) const
		{
			XArrayIterator stRet = *this;
			stRet += paramOffset;
			return stRet;
		}

		XArrayIterator & operator -=(XInt paramOffset)
		{
			return operator += (-paramOffset);
		}

		XArrayIterator operator - (XInt paramOffset) const
		{
			XArrayIterator stRet = *this;
			stRet -= paramOffset;
			return stRet;
		}
	private:
		XInt m_Index;
		Array * m_Array;
	};

    //-----------------------------------------------------------------------------------------------
    ///����ģ����
    template<class T>
    class XDynamicArray
    {
    public:
        typedef T ElementType;
        typedef ElementType * PElementType;
		typedef XArrayIterator<XDynamicArray<T> > iterator;

        ///ȱʡ���캯��
        XDynamicArray()
            :m_Length(0),
             m_Capacity(0),
             m_Data(NULL)
        {}
        
        ///ָ����ʼԪ�ظ����Ĺ��캯��
        /**
            @param [in] paramInitLength ��ʼ������Ĵ�С
        */
        XDynamicArray(XInt paramInitLength)
            :m_Length(0),
            m_Capacity(0),
            m_Data(NULL)
        {
            if( paramInitLength > 0)
            {
                InitLength(paramInitLength);
            }
        }
		//������캯���Ķ��壬��Ϊ��ʵ�ֶ����ݵĳ�ʼ���Ĺ���
		/*
			XInt v[] = {1,1,2,3,4};
			XDyanmicArray<int> st = v;
			�����C++11�ĳ�ʼ���б�������ͬ��������Ҫһ����ȷ���������
		*/
		template<int N>
		XDynamicArray(const T (&param)[N])
			: m_Length(0),
			  m_Capacity(0),
			  m_Data(NULL)
		{
			Append(param);
		}

		//������캯���Ķ��壬��Ϊ��ʵ��C++11�ĳ�ʼ���б���������
		/*
			XDynamicArray<int> st {1,2,3,4,5};
			�� XDynamicArray<int> st = {1,2,3,4,5};
		*/
		XDynamicArray(std::initializer_list<T> paramList)
			: m_Length(0),
			 m_Capacity(0),
			 m_Data(NULL)
		{
			this->ensureCapacity((XInt)paramList.size());
			for (auto e : paramList)
			{
				Append(e);
			}
		}
		
		/*���ﶨ��begin��end��Ҫ������Ŀ��
			Ŀ��1��ʹ���������׼STD������������
			Ŀ��2��ʹ������֧��C++11��forѭ��
			���ӣ�
			XDynamicArray<int> st;
			for(auto x:st)
			{
				cout<<x<<endl;
			}
		*/
		iterator begin() 
		{
			iterator stRet(this, this->getFirstIndex());
			return stRet;
		}

		iterator end() 
		{
			iterator stRet(this, ARRAY_INVALID_INDEX);
			return stRet;
		}

        ///ָ����ʼԪ�ظ����Լ�ȱʡԪ��ֵ�Ĺ��캯��
        /**
            @param [in] paramInitLength ��ʼ������Ĵ�С
            @param [in] paramDefault ��ʼ������Ԫ�ص�Ĭ��ֵ
        */
        XDynamicArray(XInt paramInitLength,const T & paramDefault)
            :m_Length(0),
             m_Capacity(0),
             m_Data(NULL)
        {
            if( paramInitLength > 0)
            {
                InitLength(paramInitLength, paramDefault);
            }
        }
        ///ȱʡ�������캯��
        XDynamicArray(const XDynamicArray<T> & paramArray);
        ///ָ����С�Լ���ʼԪ��ָ��Ĺ��캯��
        XDynamicArray(const T * paramData, XInt paramSize, XInt paramStartIndex = 0);

        ///ָ�������ʼ��
        template<int N> XDynamicArray(T (&paramDataArray)[N])
            :m_Data(NULL),
             m_Length(0),
             m_Capacity(0)
        {
            ZDH_ASSERT(N>0);
            ensureCapacity(N);
            T * pT = m_Data;
            for( XInt i = 0; i < N; i++, pT++)
            {
                new ((char *)pT) T(paramDataArray[i]);
            }
            m_Length += N;
        }

        ///ָ����С�Լ���ʼԪ������Ĺ��캯��
        XDynamicArray(const XDynamicArray<T> & paramArray, XInt paramSize, XInt paramStartIndex = 0);
        
        ///���캯��
        ~XDynamicArray()
        {
            Clear(true);
        }
        
        ///ȡ������������
        XInt getMaxCapacity() const
        {
            return 0x7ffffff0 / sizeof(T);
        }
        
        ///ȡ��Ч������Ԫ�ظ���
        XInt getLength() const 
        {
            return m_Length;
        }
        
        ///ȡ��ǰ���������
        XInt getCapacity() const
        {
            return m_Capacity;
        }
        
        ///�ж������Ƿ�Ϊ��
        /**
            @return ���ؼ��Ľ��
                - true ��ʾ����Ϊ��
                - false ��ʾ���鲻Ϊ��
        */
        bool isEmpty() const
        {
            return m_Length <= 0;
        }
        
        ///�ж������Ƿ�Ϊ��
        /**
            @return ���ؼ��Ľ��
                - true ��ʾ���鲻Ϊ��
                - false ��ʾ����Ϊ��
        */
        bool isNotEmpty() const
        {
            return m_Length > 0;
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
            return paramIndex >= 0 && paramIndex < m_Length;
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
            bool bRet = false;
            if( m_Length > 0)  
            {
                bRet = (paramIndex == m_Length - 1);
            }
            return bRet;
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
            bool bRet = false;
            if( m_Length > 0 )
            {
                bRet = (paramIndex == 0);
            }
            return bRet;
        }
        
        ///ȡ��һ���±�
        /**
             @return ���ص�һ���±�
                - ARRAY_INVALID_INDEX ��ʾ��Ч�±�
                - 0 ��ʾ��Ч��һ���±�
        */
        XInt getFirstIndex() const
        {
            XInt iRet = ARRAY_INVALID_INDEX;
            if( m_Length > 0) 
            {
                iRet = 0;
            }
            return iRet;
        }
        
        ///ȡ���һ���±�
        /**
             @return �������һ���±�
                - ARRAY_INVALID_INDEX ��ʾ��Ч�±�
                - >=0 ��ʾ��Ч���һ���±�
        */
        XInt getLastIndex() const 
        {
            XInt iRet = ARRAY_INVALID_INDEX;
            if( m_Length > 0) 
            {
                iRet = m_Length - 1;
            }
            return iRet;
        }
        
        ///ȡ�����д��������Ԫ�ص�ָ��
        /**
            ������Ҫ��,�벻Ҫʹ���������
            @return ����������Ԫ�ص�ָ��
        */
        const T * getData() const
        {
            return m_Data;
        }
        
        ///ȡ�����д��������Ԫ�ص�ָ��
        /**
            ������Ҫ��,�벻Ҫʹ���������
            @return ����������Ԫ�ص�ָ��
        */
        T * getData() 
        {
            return m_Data;
        }
        
        ///ȡָ���±������Ԫ��
        /**
             @param [in] paramIndex ָ�����±�
             @return ����ָ���±������
             @exception �������Խ�磬���׳�XEOutOfRange�쳣
             @see zdh::XEOutOfRange
        */
        T & operator[] (XInt paramIndex) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(isValidIndex(paramIndex));
            if( paramIndex < 0 || paramIndex >= m_Length ) 
            {
                throw XEOutOfRange(paramIndex, m_Length);
            }
            return m_Data[paramIndex];
        }
        
        ///ȡָ���±������Ԫ��
        /**
             @param [in] paramIndex ָ�����±�
             @return ����ָ���±������
             @exception �������Խ�磬���׳�XEOutOfRange�쳣
             @see zdh::XEOutOfRange
        */
        const T & operator[] (XInt paramIndex) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(isValidIndex(paramIndex));
            if( paramIndex < 0 || paramIndex >= m_Length ) 
            {
                throw XEOutOfRange(paramIndex,m_Length);
            }
            return m_Data[paramIndex];
        }
        
        ///ȡָ���±������Ԫ��
        /**
             @param [in] paramIndex ָ�����±�
             @return ����ָ���±������
             @exception �������Խ�磬���׳�XEOutOfRange�쳣
        */
        T & getElement (XInt paramIndex) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(isValidIndex(paramIndex));
            if( paramIndex < 0 || paramIndex >= m_Length ) 
            {
                throw XEOutOfRange(paramIndex,m_Length);
            }
            return m_Data[paramIndex];
        }
        
        ///ȡָ���±������Ԫ��
        /**
             @param [in] paramIndex ָ�����±�
             @return ����ָ���±������
             @exception �������Խ�磬���׳�XEOutOfRange�쳣
        */
        const T & getElement (XInt paramIndex) const ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(isValidIndex(paramIndex));
            if( paramIndex < 0 || paramIndex >= m_Length ) 
            {
                throw XEOutOfRange(paramIndex,m_Length);
            }
            return m_Data[paramIndex];
        }
        
        ///ȷ����С����
        /**
             ȷ����С�����������������������չ����
             @param [in] paramMinimumCapacity ȷ�ϵ���С����
        */
        void ensureCapacity(XInt paramMinimumCapacity)
        {
            expandCapacity(paramMinimumCapacity);
        }
        
        ///׷��һ��Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�Ԫ��
             @return ���ص�ǰ���������
        */
        XDynamicArray<T> & operator <<(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///׷��һ�������Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�����
             @return ���ص�ǰ���������
        */
        XDynamicArray<T> & operator <<(const XDynamicArray<T> & paramElement)
        {
            Append(paramElement);
            return *this;
        }

		template<int N>
		XDynamicArray<T> & operator << (const T(&param)[N])
		{
			Append(param);
			return *this;
		}

		XDynamicArray<T> & operator << (std::initializer_list<T> param)
		{
			Append(param);
			return *this;
		}

        ///׷��һ��Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�Ԫ��
             @return ���ص�ǰ���������
        */
        XDynamicArray<T> & operator +=(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///׷��һ�������Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�����
             @return ���ص�ǰ���������
        */
        XDynamicArray<T> & operator +=(const XDynamicArray<T> & paramElementArray)
        {
            Append(paramElementArray);
            return *this;
        }
        
		template<int N>
		XDynamicArray<T> & operator += (const T(&param)[N])
		{
			Append(param);
			return *this;
		}

		XDynamicArray<T> & operator += (std::initializer_list<T> param)
		{
			Append(param);
			return *this;
		}

        ///׷��һ��Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�Ԫ��
             @return ���ص�ǰ���������
        */
        XDynamicArray<T> & operator ,(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///׷��һ�������Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�����
             @return ���ص�ǰ���������
        */
        XDynamicArray<T> & operator ,(const XDynamicArray<T> & paramElementArray)
        {
            Append(paramElementArray);
            return *this;
        }

		template<int N>
		XDynamicArray<T> & operator , (const T(&param)[N])
		{
			Append(param);
			return *this;
		}

		XDynamicArray<T> & operator , (std::initializer_list<T> param)
		{
			Append(param);
			return *this;
		}
        
        ///���������׷��һ��Ԫ��
        /**
            @param [in] paramElement ׷�ӵ�Ԫ��
        */
        XInt Append(const T & paramElement)
        {
            ensureCapacity(m_Length+1);
            new ((char *)(m_Data + m_Length)) T(paramElement);
            ++m_Length;
            return m_Length - 1;
        }

        XInt Append()
        {
            ensureCapacity(m_Length+1);
            new ((char *)(m_Data + m_Length)) T();
            ++m_Length;
            return m_Length - 1;
        };

		template<int N>
		void Append(const T (&param)[N])
		{
			this->ensureCapacity(N + this->getLength());
			for (auto x : param)
			{
				Append(x);
			}
		}

		void Append(std::initializer_list<T> param)
		{
			this->ensureCapacity((int)(param->size() + this->getLength()));
			for (auto e : param)
			{
				Append(e);
			}
			return *this;
		}

        ///���������׷��һ������
        void Append(const XDynamicArray<T> & paramElementArray)
        {
            if( paramElementArray.m_Length > 0 )  //���Ԫ�ش���
            {
                Append( paramElementArray, paramElementArray.m_Length, 0);
            }
        }
        
        ///���������׷��һ��������ָ����һ��Ԫ��
        void Append(const XDynamicArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0);
        
        ///���������׷��һ��Ԫ��ָ��ָ����һ��Ԫ��
        void Append(const T * paramValues, XInt paramSize, XInt paramStartIndex = 0);
        
        ///��ָ����λ�ò���һ������
        /**
             ��ָ����λ�ò���һ������
             @param paramIndex �����λ��
             @param paramElementArray ���������
        */
        void Insert(XInt paramIndex, const XDynamicArray<T> & paramElementArray)
        {
            if( paramElementArray.m_Length > 0) 
            {
                Insert(paramIndex, paramElementArray.m_Data, paramElementArray.m_Length);
            }
        }
        
        ///��ָ����λ�ò���һ��������ָ����һ��Ԫ��
        /**
             @param [in] paramIndex �����λ��
             @param [in] paramElementArray ����Ԫ�ص�����
             @param [in] paramSize ��������Ԫ�صĸ���
             @param [in] paramStartIndex default = 0 ָ������Ԫ���ڲ��������е�λ��(�±�)
        */
        void Insert(XInt paramIndex, const XDynamicArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0)
        {
            if( paramElementArray.m_Length > 0 ) 
            {
                Insert(paramIndex,paramElementArray.m_Data, paramSize, paramStartIndex);
            }
        }
        
        ///��ָ����λ�ò���Ԫ��ָ��ָ���һ��Ԫ��
        void Insert(XInt paramIndex, const T * paramElements, XInt paramSize, XInt paramStartIndex = 0);
        
        ///���������ǰ�����һ������
        /**
            @param [in] paramElementArray ���������
        */
        void Insert(const XDynamicArray<T> & paramElementArray)
        {
            Insert(0, paramElementArray);
        }
        
        ///���������ǰ�����������ָ����һ��Ԫ��
        /**
             @param [in] paramElementArray ����Ԫ�����ڵ�����
             @param [in] paramSize ����Ԫ�صĸ���
             @param [in] paramStartIndex ����Ԫ���������еĿ�ʼλ��
        */
        void Insert(const XDynamicArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0)
        {
            Insert(0, paramElementArray, paramSize, paramStartIndex);
        }
        
        ///���������ǰ�����Ԫ��ָ��ָ���һ��Ԫ��
        /**
             @param [in] paramElements ����Ԫ�����ڵ�Ԫ��ָ��
             @param [in] paramSize ����Ԫ�صĸ���
             @param [in] paramStartIndex default = 0 ָ������Ԫ�����ָ��Ŀ�ʼλ��
        */
        void Insert(const T * paramElements, XInt paramSize, XInt paramStartIndex = 0)
        {
            Insert(0, paramElements, paramSize, paramStartIndex);
        }
        
        ///��ָ���±�λ�ò���һ��Ԫ��
        void Insert(XInt paramIndex, const T & paramValue);
        
        ///���������ǰ�����һ��Ԫ��
        void Insert(const T & paramValue)
        {
            Insert(0, paramValue);
        }
        
        ///ɾ�����һ��Ԫ��
        /**
            @return bool ����ɾ���Ľ��
                - true ɾ���ɹ�
                - false ɾ��ʧ��
         */
        bool RemoveLast()
        {
            bool bRet = false;
            if( m_Length > 0)
            {
                T * pT = m_Data + m_Length - 1;
                pT->~T(); //������������,���������ݳ�ʼ��Ϊ0
                MemorySet(pT, 0, sizeof(T));
                -- m_Length;
                bRet = true;
            }
            return bRet;
        }
        
        ///�����ѹ��һ��Ԫ��
        /**
            @param [in] paramElement ��ѹ���Ԫ��
            @return bool ѹ��Ľ��
                - true ѹ��Ԫ�سɹ�
                - false ѹ��Ԫ��ʧ��
         */
        bool Push(const T & paramElement)
        {
            Append(paramElement);
            return true;
        }
        
        ///����󵯳�һ��Ԫ��
        /**
            @param [out] paramElement ������Ԫ��
            @return bool �������
                - true �����ɹ�
                - false ����ʧ��
         */
        bool Pop(T & paramElement)
        {
            bool bRet = false;
            if( m_Length > 0)
            {
                T * pT = m_Data + m_Length - 1;
                paramElement = *pT;
                MemorySet(pT,0,sizeof(T));
                -- m_Length;
                bRet = true;
            }           
            return bRet;
        }
        
        ///ɾ��ָ���±�λ�õ�Ԫ��
        void Remove(XInt paramIndex  = 0);
        
        ///ɾ��ָ��ɾ�������Ԫ��
        void RemoveArea(XInt paramStartIndex, XInt paramRemoveCount);
        
        ///�������Ԫ��
        void Clear(bool paramFree = false);
        
        ///��ֵ����
        /**
             ������������ͷ����е�����Ԫ��
             @param paramArray ����ֵ��Դ����
             @return ���ص�ǰ���������
        */
        XDynamicArray<T> & operator = (const XDynamicArray<T> & paramElementArray)
        {
            if( this != & paramElementArray)
            {
                Clear();
                ensureCapacity(paramElementArray.getLength());
                Append(paramElementArray);
            }
            return *this;
        };
        
        XDynamicArray<T> & operator = (const T & paramElement)
        {
            Clear();
            ensureCapacity(1);
            Append(paramElement);
            return *this;
        }
        
        ///����ָ���±������Ԫ��
        /**
         * @param [in] paramIndex1 ָ�����±�1
         * @param [in] paramIndex2 ָ�����±�2
         */
        void Swap(XInt paramIndex1, XInt paramIndex2) ZDH_THROW(XEOutOfRange)
        {
            ZDH_ASSERT(paramIndex1 >= 0 && paramIndex1 < m_Length);
            ZDH_ASSERT(paramIndex2 >= 0 && paramIndex2 < m_Length);
            if( paramIndex1 != paramIndex2 ) 
            {
                if( paramIndex1 < 0 || paramIndex1 >= m_Length ) 
                {
                    throw XEOutOfRange(paramIndex1, m_Length);
                }
                if( paramIndex2 < 0 || paramIndex2 >= m_Length ) 
                {
                    throw XEOutOfRange(paramIndex2, m_Length);
                }
                T tmp = m_Data[paramIndex1];
                m_Data[paramIndex1] = m_Data[paramIndex2];
                m_Data[paramIndex2] = tmp;
            }
        }
        
        ///Ĭ������(����ð������)
        void Sort()
        {
            Array_BubbleSort(*this, XFunctions_Less<T>());
        }
        
        ///ʹ�ÿ�������ģ��
        /**
            @param [in] paramCompare �Ƚ��õĶ���
         */
        template<class Compare>
        void Sort_QuickSort(const Compare & paramCompare)
        {
            Array_QuickSort(*this, paramCompare);
        }
        
        ///ʹ�ÿ�������
        /**
            @param [in] paramAscending �����־
                - true ��ʾ����
                - false ��ʾ����
         */
        void Sort_QuickSort(bool paramAscending = true)
        {
            if( paramAscending ) 
            {
                Array_QuickSort(*this, XFunctions_Less<T>());
            }
            else 
            {
                Array_QuickSort(*this, XFunctions_Greater<T>());
            }
        }
        
        ///ʹ��ð������ģ��
        /**
            @param [in] paramCompare �Ƚ��õĶ���
         */
        template<class Compare>
        void Sort_BubbleSort(const Compare & paramCompare)
        {
            Array_BubbleSort(*this, paramCompare);
        }

        ///ʹ��ð������
        /**
            @param [in] paramAscending �����־
                - true ��ʾ����
                - false ��ʾ����
         */
        void Sort_BubbleSort(bool paramAscending = true) 
        {
            if( paramAscending ) 
            {
                Array_BubbleSort(*this, XFunctions_Less<T>());
            }
            else 
            {
                Array_BubbleSort(*this, XFunctions_Greater<T>());
            }
        }

        ///ʹ�����β��ҵİ취������ָ��Ԫ��
        /**
         * �����Ҫָ���Ƚ�����Ԫ����ȵĶ���
         * @param [in] paramElement �����ҵ�Ԫ��
         * @param [in] paramEqual �Ƚϵ��ڵ���Ķ���
         * @return ���ز��ҽ��
         *      - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
         *      - ����ֵ ��ʾ�����������е��±�
         */
        template<class CompareEQU>
        XInt Find_Normal(const T & paramElement,const CompareEQU & paramEqual)
        {
            return Array_Find_Normal(*this, paramElement, paramEqual);
        }

        ///ʹ�����β��ҵİ취������ָ��Ԫ��
        /**
         * �������Ĭ��ʹ��XFunctions_Equal<T>�Ƚϵ��ڵĶ���
         * @param [in] paramElement �����ҵ�Ԫ��
         * @return ���ز��ҽ��
         *      - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
         *      - ����ֵ ��ʾ�����������е��±�
         */
        XInt Find_Normal(const T & paramElement)
        {
            return Array_Find_Normal(*this, paramElement, XFunctions_Equal<T>());
        }

        ///ʹ�ö��ֲ��ҵİ취������ָ��Ԫ��
        /**
         * �����Ҫָ���Ƚϴ�С�Ķ�����XFunctions_Compare
         * @param [in] paramElement �����ҵ�Ԫ��
         * @param [in] paramEqual �Ƚϵ��ڵ���Ķ���
         * @return ���ز��ҽ��
         *      - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
         *      - ����ֵ ��ʾ�����������е��±�
         */
        template<class Compare>
        XInt Find_Binary(const T & paramElement, const Compare & paramCompare)
        {
            return Array_Find_Binary(*this, paramElement, paramCompare);
        }

        ///ʹ�ö��ֲ��ҵİ취������ָ��Ԫ��
        /**
         * Ҫ��������һ�����������,����Compare��Ӧ�õ���,Ĭ������������
         * �������Ĭ��ʹ��XFunctions_Comapre<T>�Ƚϵ��ڵĶ���
         * @param [in] paramElement �����ҵ�Ԫ��
         * @return ���ز��ҽ��
         *      - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
         *      - ����ֵ ��ʾ�����������е��±�
         */
        XInt Find_Binary(const T & paramElement)
        {
            return Array_Find_Binary(*this, paramElement, XFunctions_Compare<T>());
        }
    private:
        ///��չָ����������������
        /**
            @param [in] paramMinimumCapacity ָ������С����
        */
        void expandCapacity(XInt paramMinimumCapacity);

        ///��ʼ��ָ�����ȵ�����
        void InitLength(XInt paramInitLength);

        ///��ʼ��ָ�����Ⱥ�Ԫ�س�ֵ������
        void InitLength(XInt paramInitLength, const T & paramValue);
    private:
        //���ݳ�Ա
        XInt m_Length;  ///<����Ԫ�ظ���
        XInt m_Capacity; ///<������������
        T * m_Data;     ///<���鿪ʼָ��
    };  

    //
    /**
        ���������׷��һ��Ԫ��ָ��ָ����һ��Ԫ��
         @param [in] paramElements ׷��һ��Ԫ�ص�Ԫ��ָ��
         @param [in] paramSize ׷��Ԫ�صĸ���
         @param [in] paramStartIndex default = 0 ����ĵ�һ��Ԫ����ָ��paramElements�е�ƫ��λ��
         @exception zdh::XELessThanZero
    */
    template<class T>
    void XDynamicArray<T>::Append( const T * paramElements, XInt paramSize, XInt paramStartIndex /*= 0*/ ) ZDH_THROW(XELessThanZero)
    {
        ZDH_ASSERT(paramElements != NULL);
        ZDH_ASSERT(paramSize >= 0);
        ZDH_ASSERT(paramStartIndex >= 0);
        if( paramSize == 0 ) return;
        if( paramSize < 0) 
        {
            throw XELessThanZero(); //����Ǵ����size,���׳��쳣
        }
        XInt iLength = m_Length;
        ensureCapacity( paramSize + iLength );
        paramElements += paramStartIndex;
        T * pT = m_Data + iLength;
        for(XInt i=0; i<paramSize; i++, pT++, paramElements++) 
        {
            new ((char *)pT) T(*paramElements);
        }
        m_Length += paramSize;
    }

    //----------------------------------------------------------------------------
    /**
        ���������׷��һ��������ָ����һ��Ԫ��
         @param [in] paramElementArray ׷�ӵ�Ԫ������
         @param [in] paramSize ׷��Ԫ�صĸ���
         @param [in] paramStartIndex default = 0 ָ������Ԫ�����ָ��Ŀ�ʼλ��
    */
    template<class T>
    void XDynamicArray<T>::Append(const XDynamicArray<T> &paramElementArray, XInt paramSize, XInt paramStartIndex /*= 0*/) 
        ZDH_THROW(XELessThanZero)
        ZDH_THROW(XEOutOfRange)
    {
        ZDH_ASSERT(paramSize > 0);
        ZDH_ASSERT( paramStartIndex >= 0 && paramStartIndex < paramElementArray.getLength() );
        if( paramSize == 0 ) return;

        if( paramSize < 0 ) 
        {
            throw XELessThanZero();
        }
        if( paramStartIndex <0 || paramStartIndex >= paramElementArray.m_Length ) 
        {
            throw XEOutOfRange(paramStartIndex,paramElementArray.m_Length);
        }
        if( (paramStartIndex + paramSize) < 0 || (paramSize + paramStartIndex) > paramElementArray.m_Length ) 
        {
            throw XEOutOfRange(paramSize + paramStartIndex,paramElementArray.m_Length);
        }
        ensureCapacity(m_Length+paramSize);
        T * pT = m_Data + m_Length;
        T * pV = paramElementArray.m_Data + paramStartIndex;
        for(XInt i=0; i<paramSize; i++, pT++, pV++)
        {
            new ((char *)pT) T(*pV);
        }
        m_Length += paramSize;
    }
    
    //----------------------------------------------------------------------------
    /**
        ����ָ��Ԫ��������һ��Ԫ�أ���������
         @param [in] paramElementArray ���ڹ����Ԫ������
         @param [in] paramSize �����Ԫ�ظ���
         @param [in] paramStartIndex default = 0 ָ����ʼ����Ԫ���������е�λ��
    */
    template<class T>
    XDynamicArray<T>::XDynamicArray(const XDynamicArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex/* = 0*/)
        ZDH_THROW(XEOutOfRange)
        ZDH_THROW(XELessThanZero)
        :m_Data(NULL),m_Length(0),m_Capacity(0)
    {
        ZDH_ASSERT(paramSize >= 0);
        ZDH_ASSERT(paramStartIndex >= 0 && paramStartIndex < paramElementArray.m_Length);
        if( paramSize == 0 ) return;
        if( paramSize < 0 ) 
        {
            throw XELessThanZero();
        }

        if( paramStartIndex <0 || paramStartIndex > paramElementArray.m_Length ) 
        {
            throw XEOutOfRange(paramStartIndex,paramElementArray.m_Length);
        }
        if( (paramStartIndex + paramSize) < 0 || (paramSize + paramStartIndex) > paramElementArray.m_Length )
        {
            throw XEOutOfRange(paramSize + paramStartIndex,paramElementArray.m_Length);
        }
        if( paramSize > 0)
        {
            ensureCapacity(paramSize);
            T * pT = m_Data;
            const T * pV = paramElementArray.m_Data + paramStartIndex;
            for(XInt i=0; i<paramSize; i++, pT++, pV++)
            {
                new ((char *)pT) T(*pV);
            }
            m_Length = paramSize;
        }
    }
    
    //----------------------------------------------------------------------------
    /**
         ����ָ��Ԫ��������һ��Ԫ�أ���������
         @param [in] paramElements ���ڹ����һ��Ԫ�ؿ�ʼָ��
         @param [in] paramSize �����Ԫ�ظ���
         @param [in] paramStartIndex ָ����ʼ����Ԫ�����Ԫ��ָ��Ŀ�ʼλ��
    */
    template<class T>
    XDynamicArray<T>::XDynamicArray(const T * paramElements, XInt paramSize, XInt paramStartIndex)
        :m_Data(NULL),
         m_Length(0),
         m_Capacity(0)
    {
        ZDH_ASSERT(paramElements != NULL);
        ZDH_ASSERT(paramSize > 0);
        ZDH_ASSERT(paramStartIndex >= 0);
        if( paramSize == 0 ) return;
        if( paramSize > 0)
        {
            ensureCapacity(paramSize);
            paramElements += paramStartIndex;
            T * pT = m_Data;
            for(XInt i=0; i<paramSize; i++, pT++, paramElements++)
            {
                new ((char *)pT) T(*paramElements);
            }
            m_Length = paramSize;
        }
    }

    //----------------------------------------------------------------------------
    /**
         ȱʡ�������캯��
         @param [in] paramArray ���ڹ��������
    */
    template<class T>
    XDynamicArray<T>::XDynamicArray(const XDynamicArray<T> & paramArray)
        :m_Data(NULL),
         m_Length(0),
         m_Capacity(0)
    {
        if( paramArray.m_Length > 0)
        {
            ensureCapacity(paramArray.getLength());
            T * pT = m_Data;
            T * pV = paramArray.m_Data;
            m_Length = paramArray.m_Length;
            for(XInt i=0; i<m_Length; i++, pT++, pV++)
            {
                new ((char *)pT) T(*pV);
            }
        }
    }
    
    //----------------------------------------------------------------------------
    /**
         ��������е�Ԫ�أ������Ԫ�ؽ���ִ����������
         @param [in] paramFree default = false �ڴ����·����־
            - true ��ʾ�����Ԫ�أ���Ҫ�ͷŵ�ǰ�Ѿ�������ڴ棬����������һ���ڴ档Ȼ�󽫳�����Ϊ0
            - false ��ʾ�����Ԫ�أ�Ȼ�󽫳�����Ϊ0
    */
    template<class T>
    void XDynamicArray<T>::Clear( bool paramFree /*= false*/ )
    {
        //ִ����������
        T * pT = m_Data;
        for(XInt i=0; i<m_Length; i++)
        {
            pT->~T();
            ++pT;
        }
        if( paramFree && m_Capacity > 0) //���·���
        {
            delete[] (XByte *)m_Data;
            m_Data = NULL;
            m_Length = 0;
            m_Capacity = 0;
        }
        else
        {
            //��0��ɾ������ռ�õ�����
            if( m_Length > 0)
            {
                MemorySet(m_Data,0,m_Length * sizeof(T));
                m_Length = 0;
            }
        }
    }
    
    //----------------------------------------------------------------------------
    /**
         ɾ��һ��ָ���±��Ԫ�أ���ɾ����Ԫ�ؽ���ִ����������
         @param [in] paramIndex default = 0 ��ɾ��Ԫ�ص��±�
    */
    template<class T>
    void XDynamicArray<T>::Remove(XInt paramIndex /*= 0*/)
        ZDH_THROW(XEOutOfRange)
    {
        ZDH_ASSERT(paramIndex >=0 && paramIndex < m_Length);
        if( paramIndex >= m_Length || paramIndex < 0 ) 
        {
            throw XEOutOfRange(paramIndex,m_Length);
        }
        //ִ����������
        T * pT = m_Data + paramIndex;
        pT->~T();

        //���ɾ���������һ��Ԫ�أ����ƶ�����
        if( !isLastIndex(paramIndex) ) 
        {
            MemoryMove(pT,((XByte *)pT)+sizeof(T),(m_Length - paramIndex - 1) * sizeof(T));
        }
        -- m_Length; //���鳤�ȼ�1
        MemorySet(((XByte *)m_Data)+ m_Length * sizeof(T), 0, sizeof(T)); //������������0
    }
    
    //----------------------------------------------------------------------------
    /**
         ɾ��һ��ָ���±������Ԫ�أ���ɾ����Ԫ�ؽ���ִ����������
         @param [in] paramStartIndex ��ʼɾ�����±�
         @param [in] paramRemoveCount ɾ��Ԫ�صĸ���
         @exception zdh::XEOutOfRange 
    */
    template<class T>
    void XDynamicArray<T>::RemoveArea(XInt paramStartIndex,XInt paramRemoveCount)
        ZDH_THROW(XEOutOfRange)
    {
        ZDH_ASSERT(paramStartIndex >= 0 && paramStartIndex < m_Length);
        //�ж��Ƿ�Խ��
        if( paramStartIndex >= m_Length || paramStartIndex < 0 ) 
        {
            throw XEOutOfRange(paramStartIndex,m_Length);
        }
        ZDH_ASSERT(paramRemoveCount>0 && ((paramStartIndex + paramRemoveCount) <= m_Length));
        T * pT = m_Data + paramStartIndex;
        for(XInt i=0; i<paramRemoveCount; i++, pT++) pT->~T(); //�ֱ�ִ����������

        //�����Ԫ����ǰ��
        XInt iMoveCount = m_Length - paramStartIndex - paramRemoveCount; //����Ҫ�Ƶĸ���
        if( iMoveCount >= 0 ) 
        {
            MemoryMove(m_Data + paramStartIndex, pT, iMoveCount * sizeof(T));
        }
        //���ƶ��Ĳ�������
        MemorySet(m_Data + m_Length - paramRemoveCount, 0, paramRemoveCount * sizeof(T));
        m_Length -= paramRemoveCount;
    }
    
    //----------------------------------------------------------------------------
    /**
         ��ָ����λ�ò���Ԫ��ָ��ָ���һ��Ԫ��
         @param [in] paramIndex �����λ��
         @param [in] paremElements ����Ԫ�����ڵ�Ԫ��ָ��
         @param [in] paramSize ����Ԫ�صĸ���
         @param [in] paramStartIndex default = 0 ָ������Ԫ�����ָ��Ŀ�ʼλ��
    */
    template<class T>
    void XDynamicArray<T>::Insert(XInt paramIndex, const T * paremElements, XInt paramSize, XInt paramStartIndex)
        ZDH_THROW(XEOutOfRange)
        ZDH_THROW(XELessThanZero)
    {
        ZDH_ASSERT(paramIndex>=0 && paramIndex <= m_Length);
        ZDH_ASSERT(paramSize >= 0);
        ZDH_ASSERT(paramStartIndex >= 0);
        XInt iLength = m_Length;
        if( paramIndex > iLength || paramIndex < 0 ) 
        {
            throw XEOutOfRange(paramIndex, iLength);
        }
        if( paramSize <= 0 || paramStartIndex < 0 ) 
        {
            throw XELessThanZero();
        }
        if( paramIndex == iLength ) //��������λ�������,��׷�� 
        {
            Append(paremElements, paramSize, paramStartIndex);
        }
        else
        {
            ensureCapacity( iLength + paramSize );

            T * pDest = m_Data + paramIndex;
            paremElements += paramStartIndex;
            MemoryMove(pDest + paramSize,pDest,(iLength - paramIndex) * sizeof(T)); //�ƶ�ԭ�е�����
            for(XInt i=0; i<paramSize; i++, pDest++, paremElements++) 
            {
                new ((char *)(pDest)) T(*paremElements); //ִ�й��캯��
            }

            m_Length += paramSize;
        }
    }
    
    //----------------------------------------------------------------------------
    /**
         ��ָ��λ�ò���һ��Ԫ��
         @param paramIndex Ԫ�ز����λ��
         @param paramElement �����Ԫ��
         @exception XEOutOfRange
    */
    template<class T>
    void XDynamicArray<T>::Insert(XInt paramIndex, const T & paramElement)
        ZDH_THROW(XEOutOfRange)
    {
        ZDH_ASSERT(paramIndex >= 0 && paramIndex <= m_Length);
        XInt iLength = m_Length;
        if( paramIndex > iLength || paramIndex < 0 ) 
        {
            throw XEOutOfRange(paramIndex, iLength);
        }
        //ȷ������
        ensureCapacity(iLength + 1);
        //���ݺ���
        if( iLength > paramIndex ) 
        {
            MemoryMove(m_Data + paramIndex + 1,m_Data + paramIndex,(iLength - paramIndex)* sizeof(T));
        }

        new ((char *)(m_Data + paramIndex)) T(paramElement);//����copy���캯��
        ++m_Length;
    }
    
    //----------------------------------------------------------------------------
    /**
         ��ʼ��ָ�����ȵ����飬����������Ԫ�ؽ�������Ĭ�Ϲ��캯��
         @param paramInitLength ��ʼ������ĳ���
    */
    template<class T>
    void XDynamicArray<T>::InitLength( XInt paramInitLength )
    {
        expandCapacity(paramInitLength);
        m_Length = paramInitLength;
        T * pData = m_Data;
        while(paramInitLength > 0)
        {
            new ((char *)pData) T(); //����ȱʡ���캯��
            --paramInitLength;
            ++pData;
        }
    }
    
    //----------------------------------------------------------------------------
    /**
         ��ʼ��ָ�����Ⱥ�Ԫ�س�ֵ������
         @param paramInitLength  ��ʼ������ĳ���
         @param paramElement ����Ԫ�س�ʼ��ֵ
    */
    template<class T>
    void XDynamicArray<T>::InitLength( XInt paramInitLength, const T & paramElement )
    {
        expandCapacity(paramInitLength);
        m_Length = paramInitLength;
        T * pData = m_Data;
        while(paramInitLength > 0)
        {
            new ((char *)pData) T(paramElement); //����ȱʡ������
            --paramInitLength;
            ++pData;
        }
    }

    //----------------------------------------------------------------------------
    /**
         ��չָ����������������
         @param [in] paramMinimumCapacity ָ������С����
    */
    template<class T>
    void XDynamicArray<T>::expandCapacity( XInt paramMinimumCapacity )
        ZDH_THROW(XEOutOfMemory)
    {
        ZDH_ASSERT(paramMinimumCapacity >= 0);
        if( paramMinimumCapacity > m_Capacity ) //���ʵ�������Ҫ��Ҫ������
        {
            //��������
            XInt newCapacity = 0;//paramMinimumCapacity;

            if( m_Capacity > 0 ) 
            {
                newCapacity = m_Capacity * 2;
            }
            if( newCapacity < paramMinimumCapacity )
            {
                newCapacity = paramMinimumCapacity; 
            }
            if( newCapacity > getMaxCapacity() || newCapacity < 0) 
            {
                newCapacity = getMaxCapacity();
            }
            if( newCapacity <= m_Capacity ) 
            {
                throw XEOutOfMemory();
            }
            //����ʵ���ֽڵ�
            XInt iBytes = newCapacity * sizeof(T);

            //��16�ı�������
            if( iBytes % 16 > 0)
            {
                iBytes = iBytes + (16 - (iBytes % 16));
            }
            //
            char * pData = new char[iBytes]; //����ռ�
            if( pData == NULL ) 
            {
                throw XEOutOfMemory();
            }
            //��������
            if( m_Length > 0) 
            {
                MemoryCopy(pData, m_Data, m_Length * sizeof(T));
            }

            //��ʣ�µ�����
            MemorySet(pData + m_Length * sizeof(T), 0, iBytes - m_Length * sizeof(T));
            //�ͷ�ԭ����Դ
            if( m_Capacity > 0) 
            {
                delete[] (char *)m_Data;
            }
            //��������������
            m_Capacity = iBytes / sizeof(T);
            m_Data = (T *)pData;
        }
    }
    //----------------------------------------------------------------------------
    ///��̬��������
    /**
        Ϊ�˱��������ƶ���������ʵ����һ���������顣��������ͨ��������ʹ�á��������е�Ԫ�ص�λ�ñ仯��ʱ��
        ����ı����ĵ�ַ���������ɶ��󡣴Ӷ���֤�˶�����ȶ��ԡ�
        ԭ������ԭ��̬�����ϣ���Ŷ����ָ�룬����Щָ��ָ����Щ���󡣵��������������ƶ���ʱ���ƶ��Ľ��Ƕ���
        ��ָ�룬�����Ƕ���
     */
    template<class T>
    class XObjectArray
    {
    public:
        typedef T ElementType;
        typedef ElementType * PElementType;

        ///Ĭ�Ϲ��캯��
        XObjectArray()
        {}

        ///ָ����ʼԪ�ظ����Ĺ��캯��
        /**
         @param [in] paramInitLength ��ʼ������Ĵ�С
        */
        XObjectArray(XInt paramInitLength)
        {
            if( paramInitLength > 0)
            {
                InitLength(paramInitLength);
            }
        }

        ///ָ����ʼԪ�ظ����Լ�ȱʡԪ��ֵ�Ĺ��캯��
        /**
             @param [in] paramInitLength ��ʼ������Ĵ�С
             @param [in] paramDefault ��ʼ������Ԫ�ص�Ĭ��ֵ
        */
        XObjectArray(XInt paramInitLength, const T & paramDefault)
        {
            if( paramInitLength > 0)
            {
                InitLength(paramInitLength,paramDefault);
            }
        }

        ///ȱʡ�������캯��
        XObjectArray(const XObjectArray<T> & paramElementArray);

        ///ָ����С�Լ���ʼԪ��ָ��Ĺ��캯��
        XObjectArray(const T * paramData, XInt paramSize, XInt paramStartIndex = 0);

        ///ָ����С�Լ���ʼԪ������Ĺ��캯��
        XObjectArray(const XObjectArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0);

        ///Ĭ����������
        ~XObjectArray()
        {
            Clear();
        }

        ///�������
        void Clear();

        ///ȡ������������
        XInt getMaxCapacity() const
        {
            return 0x7ffffff0 / sizeof(T);
        }

        ///ȡ��Ч������Ԫ�ظ���
        XInt getLength() const 
        {
            return m_Array.getLength();
        }

        ///ȡ��ǰ���������
        XInt getCapacity() const
        {
            return m_Array.getCapacity();
        }

        ///�ж������Ƿ�Ϊ��
        /**
             @return ���ؼ��Ľ��
                - true ��ʾ����Ϊ��
                - false ��ʾ���鲻Ϊ��
        */
        bool isEmpty() const
        {
            return m_Array.isEmpty();
        }

        bool isNotEmpty() const
        {
            return m_Array.isNotEmpty();
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
            return m_Array.isValidIndex(paramIndex);
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
            return m_Array.isLastIndex(paramIndex);
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
            return m_Array.isFirstIndex(paramIndex);
        }

        ///ȡ��һ���±�
        /**
             @return ���ص�һ���±�
                - ARRAY_INVALID_INDEX ��ʾ��Ч�±�
                - 0 ��ʾ��Ч��һ���±�
        */
        XInt getFirstIndex() const
        {
            return m_Array.getFirstIndex();
        }

        ///ȡ���һ���±�
        /**
             @return �������һ���±�
                - ARRAY_INVALID_INDEX ��ʾ��Ч�±�
                - >=0 ��ʾ��Ч���һ���±�
        */
        XInt getLastIndex() const 
        {
            return m_Array.getLastIndex();
        }

        ///ȡָ���±������Ԫ��
        /**
             @param [in] paramIndex ָ�����±�
             @return ����ָ���±������
             @exception �������Խ�磬���׳�XEOutOfRange�쳣
             @see zdh::XEOutOfRange
        */
        T & operator[] (XInt paramIndex) 
        {
            return *m_Array[paramIndex];
        }

        const T & operator[] (XInt paramIndex) const 
        {
            return *m_Array[paramIndex];
        }

        ///ȡָ���±������Ԫ��
        /**
             @param [in] paramIndex ָ�����±�
             @return ����ָ���±������
             @exception �������Խ�磬���׳�XEOutOfRange�쳣
        */
        T & getElement (XInt paramIndex) 
        {
            return *m_Array[paramIndex];
        }

        const T & getElement (XInt paramIndex) const 
        {
            return *m_Array[paramIndex];
        }
        
        ///ȷ����С����
        /**
             ȷ����С�����������������������չ����
             @param [in] paramMinimumCapacity ȷ�ϵ���С����
        */
        void ensureCapacity(XInt paramMinimumCapacity)
        {
            expandCapacity(paramMinimumCapacity);
        }
        
        ///׷��һ��Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�Ԫ��
             @return ���ص�ǰ���������
        */
        XObjectArray<T> & operator <<(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///׷��һ�������Ԫ��
        /**
             @param [in] paramElementArray ׷�ӵ�����
             @return ���ص�ǰ���������
        */
        XObjectArray<T> & operator <<(const XObjectArray<T> & paramElementArray)
        {
                Append(paramElementArray);
                return *this;
        }
        
        ///׷��һ��Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�Ԫ��
             @return ���ص�ǰ���������
        */
        XObjectArray<T> & operator +=(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///׷��һ�������Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�����
             @return ���ص�ǰ���������
        */
        XObjectArray<T> & operator +=(const XObjectArray<T> & paramElementArray)
        {
            Append(paramElementArray);
            return *this;
        }
        
        ///׷��һ��Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�Ԫ��
             @return ���ص�ǰ���������
        */
        XObjectArray<T> & operator ,(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///׷��һ�������Ԫ��
        /**
             @param [in] paramElement ׷�ӵ�����
             @return ���ص�ǰ���������
        */
        XObjectArray<T> & operator ,(const XObjectArray<T> & paramElementArray)
        {
            Append(paramElementArray);
            return *this;
        }
        
        ///���������׷��һ��Ԫ��
        /**
         @param [in] paramElement ׷�ӵ�Ԫ��
        */
        T * Append(const T & paramElement)
        {
            T * pRet = new T(paramElement);
            m_Array.Append( pRet );
            return pRet;
        }

        T * Append()
        {
            T * pRet = new T();
            m_Array.Append(pRet);
            return pRet;
        }

        ///���������׷��һ������
        void Append(const XObjectArray<T> & paramElementArray)
        {
            if( paramElementArray.getLength() > 0 )
            {
                Append( paramElementArray, paramElementArray.getLength(), 0);
            }
        }
        
        ///���������׷��һ��������ָ����һ��Ԫ��
        void Append(const XObjectArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0);
        
        ///���������׷��һ��Ԫ��ָ��ָ����һ��Ԫ��
        void Append(const T * paramElements, XInt paramSize, XInt paramStartIndex = 0);
        
        ///��ָ����λ�ò���һ������
        /**
             ��ָ����λ�ò���һ������
             @param paramIndex �����λ��
             @param paramElementArray ���������
        */
        void Insert(XInt paramIndex,const XObjectArray<T> & paramElementArray)
        {
            Insert(paramIndex, paramElementArray, paramElementArray.getLength(), 0);
        }
        
        ///��ָ����λ�ò���һ��������ָ����һ��Ԫ��
        /**
             @param [in] paramIndex �����λ��
             @param [in] paramElementArray ����Ԫ�ص�����
             @param [in] paramSize ��������Ԫ�صĸ���
             @param [in] paramStartIndex default = 0 ָ������Ԫ���������е�λ��
        */
        void Insert(XInt paramIndex,const XObjectArray<T> & paramElementArray,XInt paramSize,XInt paramStartIndex = 0);

        ///��ָ����λ�ò���Ԫ��ָ��ָ���һ��Ԫ��
        void Insert(XInt paramIndex,const T * paramElements,XInt paramSize,XInt paramStartIndex = 0);
        
        ///���������ǰ�����һ������
        /**
            @param [in] paramElementArray ���������
        */
        void Insert(const XObjectArray<T> & paramElementArray)
        {
            Insert(0, paramElementArray, paramElementArray.getLength(), 0);
        }
        
        ///���������ǰ�����������ָ����һ��Ԫ��
        /**
             @param [in] paramElementArray ����Ԫ�����ڵ�����
             @param [in] paramSize ����Ԫ�صĸ���
             @param [in] paramStartIndex ����Ԫ���������еĿ�ʼλ��
        */
        void Insert(const XObjectArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0)
        {
            Insert(0, paramElementArray, paramSize, paramStartIndex);
        }
        
        ///���������ǰ�����Ԫ��ָ��ָ���һ��Ԫ��
        /**
             @param [in] paramElements ����Ԫ�����ڵ�Ԫ��ָ��
             @param [in] paramSize ����Ԫ�صĸ���
             @param [in] paramStartIndex default = 0 ָ������Ԫ�����ָ��Ŀ�ʼλ��
        */
        void Insert(const T * paramElements, XInt paramSize, XInt paramStartIndex = 0)
        {
            Insert(0,paramElements, paramSize, paramStartIndex);
        }
        
        ///��ָ��λ�ò���һ��Ԫ��
        /**
             ��ָ��λ�ò���һ��Ԫ��
             @param paramIndex Ԫ�ز����λ��
             @param paramElement �����Ԫ��
             @exception XEOutOfRange
        */
        void Insert(XInt paramIndex, const T & paramElement)
        {
            
            XInt iLength = getLength();
            if( paramIndex > iLength || paramIndex < 0 ) 
            {
                throw XEOutOfRange(paramIndex,iLength);
            }
            m_Array.Insert(paramIndex,new T(paramElement));
        }

        ///���������ǰ�����һ��Ԫ��
        void Insert(const T & paramElement)
        {
            Insert(0, paramElement);
        }
        
        ///�����ѹ��һ��Ԫ��
        /**
            @param [in] paramElement ��ѹ���Ԫ��
            @return bool ѹ��Ľ��
                - true ѹ��Ԫ�سɹ�
                - false ѹ��Ԫ��ʧ��
         */
        bool Push(const T & paramElement)
        {
            Append(paramElement);
            return true;
        }
        
        ///����󵯳�һ��Ԫ��
        /**
            @param [out] paramElement ������Ԫ��
            @return bool �������
                - true �����ɹ�
                - false ����ʧ��
         */
        bool Pop(T & paramElement)
        {
            bool bRet = false;
            if( getLength() > 0)
            {
                paramElement = m_Array[m_Array.getLastIndex()];
                delete m_Array[m_Array.getLastIndex()];
                m_Array.RemoveLast();
                bRet = true;
            }           
            return bRet;
        }
        
        ///ɾ�����һ��Ԫ��
        void RemoveLast();
        
        ///ɾ��ָ��λ�õ�Ԫ��
        void Remove(XInt paramIndex  = 0);
        
        ///ɾ��ָ��ɾ�������Ԫ��
        void RemoveArea(XInt paramStartIndex, XInt paramRemoveCount);
        
        ///��ֵ����
        /**
             ������������ͷ����е�����Ԫ��
             @param paramArray ����ֵ��Դ����
             @return ���ص�ǰ���������
        */
        XObjectArray<T> & operator = (const XObjectArray<T> & paramElementArray)
        {
            if( this != & paramElementArray)
            {
                Clear();
                ensureCapacity(paramElementArray.getLength());
                Append(paramElementArray);
            }
            return *this;
        };

        XObjectArray<T> & operator = (const T & paramElement)
        {
            Clear();
            ensureCapacity(1);
            Append(paramElement);
            return *this;
        }
        
        ///��������Ԫ��
        void Swap(XInt paramAIndex,XInt paramBIndex)
        {
            m_Array.Swap(paramAIndex,paramBIndex);
        }
        
        ///Ĭ������
        void Sort()
        {
            Array_QuickSort(*this,XFunctions_Less<T>());
        }
        
        ///ʹ�ÿ�������ģ��
        /**
            @param [in] paramCompare �Ƚ��õĶ���
         */
        template<class Compare>
        void Sort_QuickSort(const Compare & paramCompare)
        {
            Array_QuickSort(*this,paramCompare);
        }
        
        ///ʹ�ÿ�������
        /**
            @param [in] paramAscending �����־
                - true ��ʾ����
                - false ��ʾ����
         */
        void Sort_QuickSort(bool paramAscending = true)
        {
            if( paramAscending ) Array_QuickSort(*this,XFunctions_Less<T>());
            else Array_QuickSort(*this,XFunctions_Greater<T>());
        }
        
        ///ʹ��ð������ģ��
        /**
            @param [in] paramCompare �Ƚ��õĶ���
         */
        template<class Compare>
        void Sort_BubbleSort(const Compare & paramCompare)
        {
            Array_BubbleSort(*this,paramCompare);
        }
        
        ///ʹ��ð������
        /**
            @param [in] paramAscending �����־
                - true ��ʾ����
                - false ��ʾ����
         */
        void Sort_BubbleSort(bool paramAscending = true) 
        {
            if( paramAscending ) 
            {
                Array_BubbleSort(*this,XFunctions_Less<T>());
            }
            else 
            {
                Array_BubbleSort(*this,XFunctions_Greater<T>());
            }
        }
        
        ///ʹ�����β��ҵİ취������ָ��Ԫ��
        /**
         * �����Ҫָ���Ƚ�����Ԫ����ȵĶ���
         * @param [in] paramElement �����ҵ�Ԫ��
         * @param [in] paramEqual �Ƚϵ��ڵ���Ķ���
         * @return ���ز��ҽ��
         *      - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
         *      - ����ֵ ��ʾ�����������е��±�
         */
        template<class CompareEQU>
        XInt Find_Normal(const T & paramElement, const CompareEQU & paramEqual)
        {
            return Array_Find_Normal(*this, paramElement,paramEqual);
        }
        
        ///ʹ�����β��ҵİ취������ָ��Ԫ��
        /**
         * �������Ĭ��ʹ��XFunctions_Equal<T>�Ƚϵ��ڵĶ���
         * @param [in] paramElement �����ҵ�Ԫ��
         * @return ���ز��ҽ��
         *      - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
         *      - ����ֵ ��ʾ�����������е��±�
         */
        XInt Find_Normal(const T & paramElement)
        {
            return Array_Find_Normal(*this,paramElement,XFunctions_Equal<T>());
        }
        
        ///ʹ�ö��ֲ��ҵİ취������ָ��Ԫ��
        /**
         * �����Ҫָ���Ƚϴ�С�Ķ�����XFunctions_Compare
         * @param [in] paramElement �����ҵ�Ԫ��
         * @param [in] paramEqual �Ƚϵ��ڵ���Ķ���
         * @return ���ز��ҽ��
         *      - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
         *      - ����ֵ ��ʾ�����������е��±�
         */
        template<class Compare>
        XInt Find_Binary(const T & paramElement,const Compare & paramCompare)
        {
            return Array_Find_Binary(*this,paramElement,paramCompare);
        }
        
        ///ʹ�ö��ֲ��ҵİ취������ָ��Ԫ��
        /**
         * �������Ĭ��ʹ��XFunctions_Comapre<T>�Ƚϵ��ڵĶ���
         * @param [in] paramElement �����ҵ�Ԫ��
         * @return ���ز��ҽ��
         *      - ARRAY_INVALID_INDEX ��ʾ����δ�ҵ�
         *      - ����ֵ ��ʾ�����������е��±�
         */
        XInt Find_Binary(const T & paramElement)
        {
            return Array_Find_Binary(*this,paramElement,XFunctions_Compare<T>());
        }
    private:
        
        ///��չָ����������������
        /**
            @param [in] minimumCapacity ָ������С����
        */
        void expandCapacity(XInt minimumCapacity)
        {
            m_Array.ensureCapacity(minimumCapacity);
        }
        
        ///��ʼ��ָ�����ȵ�����
        void InitLength(XInt paramInitLength);
        
        ///��ʼ��ָ�����Ⱥ�Ԫ�س�ֵ������
        void InitLength(XInt paramInitLength,const T & paramValue);
    private:
        XDynamicArray<T *> m_Array;       ///<��ǰ��ʹ�õĶ���ָ������
    };

    //---------------------------------------------------------------------------
    //ģ�����Ա������ʵ��
    template<class T>
    void XObjectArray<T>::Clear()
    {
        //ִ�����Ĭ����������
        for(XInt i = m_Array.getLength() - 1; i>=0; i--) 
        {
            delete m_Array[i];
        }
        //
        m_Array.Clear();
    }

    //----------------------------------------------------------------------------
    /**
         ����ָ��Ԫ��������һ��Ԫ�أ���������
         @param [in] paramElementArray ���ڹ����Ԫ������
         @param [in] paramSize �����Ԫ�ظ���
         @param [in] paramStartIndex default = 0 ָ����ʼ����Ԫ���������е�λ��
    */
    template<class T>
    XObjectArray<T>::XObjectArray(const XObjectArray<T> & paramElementArray,XInt paramSize,XInt paramStartIndex/* = 0*/)
    {
        if( paramStartIndex <0 || paramStartIndex >= paramElementArray.getLength() ) 
        {
            throw XEOutOfRange(paramStartIndex,paramElementArray.getLength());
        }
        if( paramSize < 0 ) paramSize = 0;
        if( (paramStartIndex + paramSize) < 0 || (paramSize + paramStartIndex) >= paramElementArray.getLength() ) 
        {
            throw XEOutOfRange(paramSize + paramStartIndex,paramElementArray.getLength());
        }
        if( paramSize > 0)
        {
            ensureCapacity(paramSize);
            for(XInt i=0; i<paramSize; i++) 
            {
                m_Array.Append( new T(paramElementArray[i + paramStartIndex]) );
            }
        }
    }

    //----------------------------------------------------------------------------
    /**
         ����ָ��Ԫ��������һ��Ԫ�أ���������
         @param [in] paramData ���ڹ����һ��Ԫ�ؿ�ʼָ��
         @param [in] paramSize �����Ԫ�ظ���
         @param [in] paramStartIndex ָ����ʼ����Ԫ�����Ԫ��ָ��Ŀ�ʼλ��
    */
    template<class T>
    XObjectArray<T>::XObjectArray(const T * paramData,XInt paramSize,XInt paramStartIndex)
    {
        if( paramSize > 0)
        {
            ensureCapacity(paramSize);

            paramData += paramStartIndex;

            for(XInt i=0; i<paramSize; i++,paramData++)
            {
                m_Array.Append( new T(*paramData) );
            }
        }
    }

    //----------------------------------------------------------------------------
    /**
         ȱʡ�������캯��
         @param [in] paramElementArray ���ڹ��������
    */
    template<class T>
    XObjectArray<T>::XObjectArray(const XObjectArray<T> & paramElementArray)
    {
        XInt iLength = paramElementArray.getLength();
        if( iLength > 0)
        {
            ensureCapacity(iLength);
            for(XInt i=0; i<iLength; i++) 
            {
                m_Array.Append( new T(paramElementArray[i]));
            }
        }
    }

    //----------------------------------------------------------------------------
    /**
         ��ʼ��ָ�����Ⱥ�Ԫ�س�ֵ������
         @param paramInitLength ��ʼ������ĳ���
         @param paramValue ����Ԫ�س�ʼ��ֵ
    */
    template<class T>
    void XObjectArray<T>::InitLength( XInt paramInitLength, const T & paramValue )
    {
        ensureCapacity(paramInitLength);
        while(paramInitLength > 0)
        {
            m_Array.Append( new T(paramValue) );
            --paramInitLength;
        }
    }

    //----------------------------------------------------------------------------
    /**
        ��ʼ��ָ�����ȵ�����
        @param paramInitLength ��ʼ������ĳ���
     */
    template<class T>
    void XObjectArray<T>::InitLength(XInt paramInitLength)
    {
        ensureCapacity(paramInitLength);
        while( paramInitLength > 0)
        {
            m_Array.Append( new T() );
            -- paramInitLength;
        }
    }

    //----------------------------------------------------------------------------
    //
    /**
        ���������׷��һ��Ԫ��ָ��ָ����һ��Ԫ��
         @param [in] paramElements ׷��һ��Ԫ�ص�Ԫ��ָ��
         @param [in] paramSize ׷��Ԫ�صĸ���
         @param [in] paramStartIndex default = 0 ����ĵ�һ��Ԫ����ָ��paramElements�е�ƫ��λ��
    */
    template<class T>
    void XObjectArray<T>::Append( const T * paramElements,XInt paramSize,XInt paramStartIndex /*= 0*/ )
        ZDH_THROW(XELessThanZero)
    {
        ZDH_ASSERT(paramSize >= 0);
        ZDH_ASSERT(paramStartIndex >= 0);
        if( paramSize < 0 ) 
        {
            throw XELessThanZero();
        }
        if( paramStartIndex < 0 )
        {
            throw XELessThanZero();
        }
        if( paramSize > 0)
        {
            ensureCapacity(paramSize);
            paramElements += paramStartIndex;

            for(XInt i=0; i<paramSize; i++,paramElements++) 
            {
                m_Array.Append( new T(*paramElements) );
            }
        }
    }

    //----------------------------------------------------------------------------
    /**
         ���������׷��һ��������ָ����һ��Ԫ��
         @param [in] paramElementArray ׷�ӵ�Ԫ������
         @param [in] paramSize ׷��Ԫ�صĸ���
         @param [in] paramStartIndex default = 0 ָ������Ԫ�����ָ��Ŀ�ʼλ��
    */
    template<class T>
    void XObjectArray<T>::Append(const zdh::XObjectArray<T> &paramElementArray, XInt paramSize, XInt paramStartIndex /*= 0*/)
        ZDH_THROW(XEOutOfRange) ZDH_THROW(XELessThanZero)
    {
        ZDH_ASSERT(paramStartIndex >= 0 && paramStartIndex < paramElementArray.getLength());
        ZDH_ASSERT(paramSize >= 0);
        ZDH_ASSERT(paramSize + paramStartIndex <= paramElementArray.getLength());
        XInt vLength = paramElementArray.getLength();
        if( paramStartIndex < 0 || paramStartIndex >= vLength ) 
        {
            throw XEOutOfRange(paramStartIndex,vLength);
        }
        if( paramSize < 0 )
        {
            throw XELessThanZero();
        }
        if( paramSize + paramStartIndex > vLength ) 
        {
            throw XEOutOfRange(paramSize + paramStartIndex,vLength);
        }
        if( paramSize > 0)
        {
            ensureCapacity( getLength() + paramSize );
            for( XInt i=0; i<paramSize; i++) 
            {
                m_Array.Append( new T(paramElementArray[paramStartIndex+i]));
            }
        }
    }

    //----------------------------------------------------------------------------
    /**
         ��ָ����λ�ò���Ԫ��ָ��ָ���һ��Ԫ��
         @param [in] paramIndex �����λ��
         @param [in] paramElements ����Ԫ�����ڵ�Ԫ��ָ��
         @param [in] paramSize ����Ԫ�صĸ���
         @param [in] paramStartIndex default = 0 ָ������Ԫ�����ָ��Ŀ�ʼλ��
    */
    template<class T>
    void XObjectArray<T>::Insert(XInt paramIndex,const T * paramElements,XInt paramSize,XInt paramStartIndex)
        ZDH_THROW(XEOutOfRange) ZDH_THROW(XELessThanZero)

    {
        ZDH_ASSERT(paramIndex >= 0 && paramIndex <= getLength());
        ZDH_ASSERT(paramSize >= 0);
        ZDH_ASSERT(paramStartIndex >= 0);

        XInt iLength = getLength();
        if( paramIndex > iLength || paramIndex < 0) 
        {
            throw XEOutOfRange(paramIndex,iLength);
        }
        if( paramSize <= 0 ) 
        {
            throw XELessThanZero();
        }
        if( paramStartIndex < 0) 
        {
            throw XELessThanZero();
        }

        if( iLength == paramIndex )  
        {
            Append(paramElements,paramSize,paramStartIndex);//�����ǰ����û�����ݣ���ֱ��׷��
        }
        else
        {
            paramElements += paramStartIndex;
            for(XInt i=0; i<paramSize; i++,paramElements++) 
            {
                m_Array.Insert( paramIndex + i,new T( *paramElements ) );
            }
        }
    }
    //---------------------------------------------------------------------------
    /**
         @param [in] paramIndex �����λ��
         @param [in] paramElementArray ����Ԫ�ص�����
         @param [in] paramSize ��������Ԫ�صĸ���
         @param [in] paramStartIndex default = 0 ָ������Ԫ���������е�λ��
    */
    template<class T>
    void XObjectArray<T>::Insert(XInt paramIndex,const XObjectArray<T> & paramElementArray,XInt paramSize,XInt paramStartIndex)
        ZDH_THROW(XEOutOfRange) ZDH_THROW(XELessThanZero)
    {
        ZDH_ASSERT(paramStartIndex >= 0 && paramStartIndex < paramElementArray.getLength());
        ZDH_ASSERT(paramSize > 0);
        ZDH_ASSERT(paramSize + paramStartIndex < paramElementArray.getLength());
        //ȷ������Դ���±��Ƿ�Ϸ�
        XInt vLength = paramElementArray.getLength();
        if( paramStartIndex < 0 || paramStartIndex >= vLength ) 
        {
            throw XEOutOfRange(paramStartIndex,vLength);
        }
        if( paramSize <= 0)
        {
            throw XELessThanZero(); //ȷ��Copy������
        }
        if( paramSize + paramStartIndex >= vLength ) 
        {
            throw XEOutOfRange( paramSize + paramStartIndex, vLength );
        }
        //ȷ������Ŀ����±��Ƿ�Ϸ�
        XInt iLength = getLength();
        if( paramIndex > iLength || paramIndex < 0 ) 
        {
            throw XEOutOfRange( paramIndex, iLength);
        }

        if( iLength == paramIndex ) 
        {
            Append(paramElementArray,paramSize,paramStartIndex);//���û�����ݣ���׷������
        }
        else
        { 
            //������ڲ����λ��
            ensureCapacity(iLength + paramSize);
            for( XInt i = 0; i<paramSize; i++) 
            {
                m_Array.Insert( i + paramIndex, new T(paramElementArray[paramStartIndex + i]));
            }
        }
    }

    //----------------------------------------------------------------------------
    /**
         ɾ��һ��ָ���±��Ԫ�أ���ɾ����Ԫ�ؽ���ִ����������
         @param [in] paramIndex default = 0 ��ɾ��Ԫ�ص��±�
    */
    template<class T>
    void XObjectArray<T>::Remove(XInt paramIndex /*= 0*/)
        ZDH_THROW(XEOutOfRange)
    {
        ZDH_ASSERT(isValidIndex(paramIndex));
        XInt iLength = getLength();
        if( paramIndex >= iLength || paramIndex < 0 ) 
        {
            throw XEOutOfRange(paramIndex,iLength);
        }
        //ִ����������
        delete m_Array[paramIndex];
        m_Array.Remove(paramIndex);
    }

    //----------------------------------------------------------------------------
    /**
         ɾ��һ��ָ���±������Ԫ�أ���ɾ����Ԫ�ؽ���ִ����������
         @param [in] paramStartIndex ��ʼɾ�����±�
         @param [in] paramRemoveCount ɾ��Ԫ�صĸ���
         @exception zdh::XEOutOfRange 
    */
    template<class T>
    void XObjectArray<T>::RemoveArea(XInt paramStartIndex,XInt paramRemoveCount)
        ZDH_THROW(XEOutOfRange) ZDH_THROW(XELessThanZero)
    {
        ZDH_ASSERT(isValidIndex(paramStartIndex));
        ZDH_ASSERT(paramRemoveCount >= 0);
        ZDH_ASSERT(paramRemoveCount + paramStartIndex <= getLength());
        //�ж��Ƿ�Խ��
        XInt iLength = getLength();
        if( paramStartIndex >= iLength || paramStartIndex < 0 ) 
        {
            throw XEOutOfRange(paramStartIndex,iLength);
        }
        if( paramRemoveCount < 0 )
        {
            throw XELessThanZero();
        }
        if( paramRemoveCount + paramStartIndex > iLength ) 
        {
            throw XEOutOfRange( paramRemoveCount + paramStartIndex, iLength);
        }
        for( XInt i=0; i<paramRemoveCount; i++,paramStartIndex++) 
        {
            delete m_Array[paramStartIndex];
        }
        m_Array.RemoveArea(paramStartIndex,paramRemoveCount);
    }

    //----------------------------------------------------------------------------
    /**
        ɾ����������һ��Ԫ�أ���ɾ����Ԫ�ؽ���ִ����������
    */
    template<class T>
    void XObjectArray<T>::RemoveLast()
    {
        XInt iLength = getLength();
        if( iLength > 0)
        {
            delete m_Array[iLength - 1];
            m_Array.RemoveLast();
        }
    }
    //----------------------------------------------------------------------------
}
#endif
