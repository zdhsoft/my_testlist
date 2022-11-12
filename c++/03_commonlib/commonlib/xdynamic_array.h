///动态数组模板
/**
 * 动态数组模板
 * 这里提供了一个动态数组类和一个动态对象数组类。
 * 动态数据一般用于基本数据类型，在插入和删除的时候，会移动数组的元素，这样就不适合对象的数组。
 * 动态对象数组则适用于对象。在插入和删除的是时候，不会移动数组元素，移动仅是对象的指针。
 * 这里提供的动态数组类视于std::vector<>,但这里不提供itertor
 * zdhsoft 2011 版权所有
 *
 * @file xdynamic_array.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-13
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、一个动态数组类和一个动态对象数组类

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-13  1.0             创建初始文件
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
    ///数组选择排序
    /**
        @param [in] paramArray 要排序的数组
        @param [in] paramCompare 元素比较的对象
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
    ///数组选择排序
    /**
        这里默认使用XFunctions_Less<>这个比较对象的实例
        @param [in] paramArray 要排序的数组
     */
    template<class Array>
    inline void Array_SelectSort(Array & paramArray)
    {
        Array_SelectSort(paramArray,XFunctions_Less<typename Array::ElementType>());
    }
    //-----------------------------------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///数组快速排序一次
    /**
        @param [in] paramArray 要排序的数组
        @param [in] paramLowIndex 要排序的数组最小下标
        @param [in] paramHighIndex 要排序的数组的最大下标
        @param [in] paramCompare 元素比较的对象
        @return XInt 返回数组比较元素最后的位置
     */
    template<class Array,class Compare>
    XInt Partition( Array & paramArray, XInt paramLowIndex, XInt paramHighIndex, const Compare & paramCompare)
    {
        typedef typename Array::ElementType ElementType;
        ElementType paramElement = paramArray[paramLowIndex];  // 选取并保存数组的比较参考元素

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
        paramArray[paramLowIndex] = paramElement;    // 将保存的数组比较参考元素插入到数组的适当位置
        return paramLowIndex; // 返回数组比较元素最后的位置
    }

    //-----------------------------------------------------------------------------------------------
    ///数组快速排序
    /**
        @param [in] paramArray 要排序的数组
        @param [in] paramLowIndex 要排序的数组最小下标
        @param [in] paramHighIndex 要排序的数组的最大下标
        @param [in] paramCompare 元素比较的对象
     */
    template<class Array, class Compare>
    void Array_QuickSort(Array & paramArray, XInt paramLowIndex, XInt paramHighIndex, const Compare & paramCompare)
    {
        XInt paramIndex;   // 用于记录每次划分后，数组比较参考元素最后的位置
        if (paramLowIndex < paramHighIndex)
        {
            paramIndex = Partition(paramArray, paramLowIndex, paramHighIndex, paramCompare);    // 对数组进行一次快速排序，划分数组，并返回数组比较参考元素最后的位置
            Array_QuickSort(paramArray, paramLowIndex, paramIndex - 1, paramCompare);      // 对低子序列递归进行排序
            Array_QuickSort(paramArray, paramIndex + 1, paramHighIndex, paramCompare);     // 对高子序列递归进行排序
        }
    }

    //-----------------------------------------------------------------------------------------------
    ///数组快速排序
    /**
        @param [in] paramArray 要排序的数组
        @param [in] paramCompare 元素比较的对象
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
    ///数组快速排序
    /**
        这里默认使用XFunctions_Less<>这个比较对象的实例
        @param [in] paramArray 要排序的数组
     */
    template<class Array>
    inline void Array_QuickSort(Array & paramArray)
    {
        Array_QuickSort(paramArray, XFunctions_Less<typename Array::ElementType>());
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    //-----------------------------------------------------------------------------------------------
    ///数组冒泡排序
    /**
        @param [in] paramArray 要排序的数组
        @param [in] paramCompare 元素比较的对象
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
                break; //如果没有发生交换,表示这个数组是有序的,则直接退出
            }
        }
    }

    //-----------------------------------------------------------------------------------------------
    ///数组冒泡排序
    /**
        这里默认使用XFunctions_Less<>这个比较对象的实例
        @param [in] paramArray 要排序的数组
     */
    template<class Array>
    inline void Array_BubbleSort(Array & paramArray)
    {
        Array_BubbleSort(paramArray, XFunctions_Less<typename Array::ElementType>());
    }

    //-----------------------------------------------------------------------------------------------
    ///查找数组指定元素的下标
    /**
        @param [in] paramArray 要查找的数组
        @param [in] paramElement 要查找的元素
        @param [in] paramEqual 比较两个元素是否相等的对象
        @return 返回查找结果
            - ARRAY_INVALID_INDEX 表示数据未找到
            - 其它值 表示数据在数组中的下标
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
    ///查找数组指定元素的下标
    /**
        @param [in] paramArray 要查找的数组
        @param [in] paramElement 要查找的元素
        @return 返回查找结果
            - ARRAY_INVALID_INDEX 表示数据未找到
            - 其它值 表示数据在数组中的下标
     */
    template<class Array,class E>
    inline XInt Array_Find_Normal(const Array & paramArray, const E & paramElement)
    {
        return Array_Find_Normal(paramArray, paramElement, XFunctions_Equal<typename Array::ElementType>());
    }

    //-----------------------------------------------------------------------------------------------
    ///二分查找数组指定元素的下标
    /**
        要求数组是一个有序的数组,并和Compare对应用的上
        @param [in] paramArray 要查找的数组
        @param [in] paramElement 要查找的元素
        @param [in] paramEqual 比较两个元素是否相等的对象
        @return 返回查找结果
            - ARRAY_INVALID_INDEX 表示数据未找到
            - 其它值 表示数据在数组中的下标
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
    ///二分查找数组指定元素的下标
    /**
        要求数组是一个有序的数组,在这里默认使用的是XFunctions_Compare比较对象
        @param [in] paramArray 要查找的数组
        @param [in] paramElement 要查找的元素
        @return 返回查找结果
            - ARRAY_INVALID_INDEX 表示数据未找到
            - 其它值 表示数据在数组中的下标
     */
    template<class Array,class E>
    inline XInt Array_Find_Binary(const Array & paramArray, const E & paramElement) 
    {
        return Array_Find_Binary(paramArray, paramElement, XFunctions_Compare<const typename Array::ElementType>());
	}
	//一个数组的Array的Iterator类
	/*
		这里提供XArrayIterator这个类，目的是使得这里支持C++11的for循环
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
    ///数组模板类
    template<class T>
    class XDynamicArray
    {
    public:
        typedef T ElementType;
        typedef ElementType * PElementType;
		typedef XArrayIterator<XDynamicArray<T> > iterator;

        ///缺省构造函数
        XDynamicArray()
            :m_Length(0),
             m_Capacity(0),
             m_Data(NULL)
        {}
        
        ///指定初始元素个数的构造函数
        /**
            @param [in] paramInitLength 初始化数组的大小
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
		//这个构造函数的定义，是为了实现对数据的初始化的功能
		/*
			XInt v[] = {1,1,2,3,4};
			XDyanmicArray<int> st = v;
			这个和C++11的初始化列表有所不同，这里需要一个明确的数组对象
		*/
		template<int N>
		XDynamicArray(const T (&param)[N])
			: m_Length(0),
			  m_Capacity(0),
			  m_Data(NULL)
		{
			Append(param);
		}

		//这个构造函数的定义，是为了实现C++11的初始化列表，如下例子
		/*
			XDynamicArray<int> st {1,2,3,4,5};
			或 XDynamicArray<int> st = {1,2,3,4,5};
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
		
		/*这里定义begin和end主要有两个目的
			目的1：使它可以像标准STD容器那样遍历
			目的2：使它可以支持C++11的for循环
			例子：
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

        ///指定初始元素个数以及缺省元素值的构造函数
        /**
            @param [in] paramInitLength 初始化数组的大小
            @param [in] paramDefault 初始化数组元素的默认值
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
        ///缺省拷贝构造函数
        XDynamicArray(const XDynamicArray<T> & paramArray);
        ///指定大小以及初始元素指针的构造函数
        XDynamicArray(const T * paramData, XInt paramSize, XInt paramStartIndex = 0);

        ///指定数组初始化
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

        ///指定大小以及初始元素数组的构造函数
        XDynamicArray(const XDynamicArray<T> & paramArray, XInt paramSize, XInt paramStartIndex = 0);
        
        ///析造函数
        ~XDynamicArray()
        {
            Clear(true);
        }
        
        ///取数组的最大容量
        XInt getMaxCapacity() const
        {
            return 0x7ffffff0 / sizeof(T);
        }
        
        ///取有效的数组元素个数
        XInt getLength() const 
        {
            return m_Length;
        }
        
        ///取当前数组的容量
        XInt getCapacity() const
        {
            return m_Capacity;
        }
        
        ///判断数组是否为空
        /**
            @return 返回检查的结果
                - true 表示数组为空
                - false 表示数组不为空
        */
        bool isEmpty() const
        {
            return m_Length <= 0;
        }
        
        ///判断数组是否不为空
        /**
            @return 返回检查的结果
                - true 表示数组不为空
                - false 表示数组为空
        */
        bool isNotEmpty() const
        {
            return m_Length > 0;
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
            return paramIndex >= 0 && paramIndex < m_Length;
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
            bool bRet = false;
            if( m_Length > 0)  
            {
                bRet = (paramIndex == m_Length - 1);
            }
            return bRet;
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
            bool bRet = false;
            if( m_Length > 0 )
            {
                bRet = (paramIndex == 0);
            }
            return bRet;
        }
        
        ///取第一个下标
        /**
             @return 返回第一个下标
                - ARRAY_INVALID_INDEX 表示无效下标
                - 0 表示有效第一个下标
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
        
        ///取最后一个下标
        /**
             @return 返回最后一个下标
                - ARRAY_INVALID_INDEX 表示无效下标
                - >=0 表示有效最后一个下标
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
        
        ///取数据中存放数组首元素的指针
        /**
            无特殊要求,请不要使用这个方法
            @return 返回数组首元素的指针
        */
        const T * getData() const
        {
            return m_Data;
        }
        
        ///取数据中存放数组首元素的指针
        /**
            无特殊要求,请不要使用这个方法
            @return 返回数组首元素的指针
        */
        T * getData() 
        {
            return m_Data;
        }
        
        ///取指定下标的数组元素
        /**
             @param [in] paramIndex 指定的下标
             @return 返回指定下标的引用
             @exception 如果发生越界，则抛出XEOutOfRange异常
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
        
        ///取指定下标的数组元素
        /**
             @param [in] paramIndex 指定的下标
             @return 返回指定下标的引用
             @exception 如果发生越界，则抛出XEOutOfRange异常
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
        
        ///取指定下标的数组元素
        /**
             @param [in] paramIndex 指定的下标
             @return 返回指定下标的引用
             @exception 如果发生越界，则抛出XEOutOfRange异常
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
        
        ///取指定下标的数组元素
        /**
             @param [in] paramIndex 指定的下标
             @return 返回指定下标的引用
             @exception 如果发生越界，则抛出XEOutOfRange异常
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
        
        ///确认最小容量
        /**
             确认最小容量，如果容量不够，则扩展容量
             @param [in] paramMinimumCapacity 确认的最小容量
        */
        void ensureCapacity(XInt paramMinimumCapacity)
        {
            expandCapacity(paramMinimumCapacity);
        }
        
        ///追加一个元素
        /**
             @param [in] paramElement 追加的元素
             @return 返回当前对象的引用
        */
        XDynamicArray<T> & operator <<(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///追加一个数组的元素
        /**
             @param [in] paramElement 追加的数组
             @return 返回当前对象的引用
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

        ///追加一个元素
        /**
             @param [in] paramElement 追加的元素
             @return 返回当前对象的引用
        */
        XDynamicArray<T> & operator +=(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///追加一个数组的元素
        /**
             @param [in] paramElement 追加的数组
             @return 返回当前对象的引用
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

        ///追加一个元素
        /**
             @param [in] paramElement 追加的元素
             @return 返回当前对象的引用
        */
        XDynamicArray<T> & operator ,(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///追加一个数组的元素
        /**
             @param [in] paramElement 追加的数组
             @return 返回当前对象的引用
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
        
        ///在数组最后追加一个元素
        /**
            @param [in] paramElement 追加的元素
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

        ///在数组最后追加一个数组
        void Append(const XDynamicArray<T> & paramElementArray)
        {
            if( paramElementArray.m_Length > 0 )  //如果元素存在
            {
                Append( paramElementArray, paramElementArray.m_Length, 0);
            }
        }
        
        ///在数组最后追加一个数组中指定的一组元素
        void Append(const XDynamicArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0);
        
        ///在数组最后追加一个元素指针指定的一组元素
        void Append(const T * paramValues, XInt paramSize, XInt paramStartIndex = 0);
        
        ///在指定的位置插入一个数组
        /**
             在指定的位置插入一个数组
             @param paramIndex 插入的位置
             @param paramElementArray 插入的数组
        */
        void Insert(XInt paramIndex, const XDynamicArray<T> & paramElementArray)
        {
            if( paramElementArray.m_Length > 0) 
            {
                Insert(paramIndex, paramElementArray.m_Data, paramElementArray.m_Length);
            }
        }
        
        ///在指定的位置插入一个数组中指定的一组元素
        /**
             @param [in] paramIndex 插入的位置
             @param [in] paramElementArray 插入元素的数组
             @param [in] paramSize 插入数组元素的个数
             @param [in] paramStartIndex default = 0 指定插入元素在插入数组中的位置(下标)
        */
        void Insert(XInt paramIndex, const XDynamicArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0)
        {
            if( paramElementArray.m_Length > 0 ) 
            {
                Insert(paramIndex,paramElementArray.m_Data, paramSize, paramStartIndex);
            }
        }
        
        ///在指定的位置插入元素指针指向的一组元素
        void Insert(XInt paramIndex, const T * paramElements, XInt paramSize, XInt paramStartIndex = 0);
        
        ///在数组的最前面插入一个数组
        /**
            @param [in] paramElementArray 插入的数组
        */
        void Insert(const XDynamicArray<T> & paramElementArray)
        {
            Insert(0, paramElementArray);
        }
        
        ///在数组的最前面插入数组中指定的一组元素
        /**
             @param [in] paramElementArray 插入元素所在的数组
             @param [in] paramSize 插入元素的个数
             @param [in] paramStartIndex 插入元素在数组中的开始位置
        */
        void Insert(const XDynamicArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0)
        {
            Insert(0, paramElementArray, paramSize, paramStartIndex);
        }
        
        ///在数组的最前面插入元素指针指向的一组元素
        /**
             @param [in] paramElements 插入元素所在的元素指针
             @param [in] paramSize 插入元素的个数
             @param [in] paramStartIndex default = 0 指定插入元素相对指针的开始位置
        */
        void Insert(const T * paramElements, XInt paramSize, XInt paramStartIndex = 0)
        {
            Insert(0, paramElements, paramSize, paramStartIndex);
        }
        
        ///在指定下标位置插入一个元素
        void Insert(XInt paramIndex, const T & paramValue);
        
        ///在数组的最前面插入一个元素
        void Insert(const T & paramValue)
        {
            Insert(0, paramValue);
        }
        
        ///删除最后一个元素
        /**
            @return bool 返回删除的结果
                - true 删除成功
                - false 删除失败
         */
        bool RemoveLast()
        {
            bool bRet = false;
            if( m_Length > 0)
            {
                T * pT = m_Data + m_Length - 1;
                pT->~T(); //调用析构函数,并将有数据初始化为0
                MemorySet(pT, 0, sizeof(T));
                -- m_Length;
                bRet = true;
            }
            return bRet;
        }
        
        ///在最后压入一个元素
        /**
            @param [in] paramElement 被压入的元素
            @return bool 压入的结果
                - true 压入元素成功
                - false 压入元素失败
         */
        bool Push(const T & paramElement)
        {
            Append(paramElement);
            return true;
        }
        
        ///在最后弹出一个元素
        /**
            @param [out] paramElement 弹出的元素
            @return bool 弹出结果
                - true 弹出成功
                - false 弹出失败
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
        
        ///删除指定下标位置的元素
        void Remove(XInt paramIndex  = 0);
        
        ///删除指定删除区域的元素
        void RemoveArea(XInt paramStartIndex, XInt paramRemoveCount);
        
        ///清除数组元素
        void Clear(bool paramFree = false);
        
        ///赋值方法
        /**
             这个方法，会释放已有的所有元素
             @param paramArray 被赋值的源数组
             @return 返回当前数组的引用
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
        
        ///交换指定下标的两个元素
        /**
         * @param [in] paramIndex1 指定的下标1
         * @param [in] paramIndex2 指定的下标2
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
        
        ///默认排序(数组冒泡排序)
        void Sort()
        {
            Array_BubbleSort(*this, XFunctions_Less<T>());
        }
        
        ///使用快速排序模板
        /**
            @param [in] paramCompare 比较用的对象
         */
        template<class Compare>
        void Sort_QuickSort(const Compare & paramCompare)
        {
            Array_QuickSort(*this, paramCompare);
        }
        
        ///使用快速排序
        /**
            @param [in] paramAscending 升序标志
                - true 表示升序
                - false 表示降序
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
        
        ///使用冒泡排序模板
        /**
            @param [in] paramCompare 比较用的对象
         */
        template<class Compare>
        void Sort_BubbleSort(const Compare & paramCompare)
        {
            Array_BubbleSort(*this, paramCompare);
        }

        ///使用冒泡排序
        /**
            @param [in] paramAscending 升序标志
                - true 表示升序
                - false 表示降序
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

        ///使用依次查找的办法，查找指定元素
        /**
         * 这个需要指定比较两个元素相等的对象
         * @param [in] paramElement 被查找的元素
         * @param [in] paramEqual 比较等于的类的对象
         * @return 返回查找结果
         *      - ARRAY_INVALID_INDEX 表示数据未找到
         *      - 其它值 表示数据在数组中的下标
         */
        template<class CompareEQU>
        XInt Find_Normal(const T & paramElement,const CompareEQU & paramEqual)
        {
            return Array_Find_Normal(*this, paramElement, paramEqual);
        }

        ///使用依次查找的办法，查找指定元素
        /**
         * 这个方法默认使用XFunctions_Equal<T>比较等于的对象
         * @param [in] paramElement 被查找的元素
         * @return 返回查找结果
         *      - ARRAY_INVALID_INDEX 表示数据未找到
         *      - 其它值 表示数据在数组中的下标
         */
        XInt Find_Normal(const T & paramElement)
        {
            return Array_Find_Normal(*this, paramElement, XFunctions_Equal<T>());
        }

        ///使用二分查找的办法，查找指定元素
        /**
         * 这个需要指定比较大小的对象，如XFunctions_Compare
         * @param [in] paramElement 被查找的元素
         * @param [in] paramEqual 比较等于的类的对象
         * @return 返回查找结果
         *      - ARRAY_INVALID_INDEX 表示数据未找到
         *      - 其它值 表示数据在数组中的下标
         */
        template<class Compare>
        XInt Find_Binary(const T & paramElement, const Compare & paramCompare)
        {
            return Array_Find_Binary(*this, paramElement, paramCompare);
        }

        ///使用二分查找的办法，查找指定元素
        /**
         * 要求数组是一个有序的数组,并和Compare对应用的上,默认是升序数组
         * 这个方法默认使用XFunctions_Comapre<T>比较等于的对象
         * @param [in] paramElement 被查找的元素
         * @return 返回查找结果
         *      - ARRAY_INVALID_INDEX 表示数据未找到
         *      - 其它值 表示数据在数组中的下标
         */
        XInt Find_Binary(const T & paramElement)
        {
            return Array_Find_Binary(*this, paramElement, XFunctions_Compare<T>());
        }
    private:
        ///扩展指定数组容量的容量
        /**
            @param [in] paramMinimumCapacity 指定的最小容量
        */
        void expandCapacity(XInt paramMinimumCapacity);

        ///初始化指定长度的数组
        void InitLength(XInt paramInitLength);

        ///初始化指定长度和元素初值的数组
        void InitLength(XInt paramInitLength, const T & paramValue);
    private:
        //数据成员
        XInt m_Length;  ///<数组元素个数
        XInt m_Capacity; ///<数组容量个数
        T * m_Data;     ///<数组开始指针
    };  

    //
    /**
        在数组最后追加一个元素指针指定的一组元素
         @param [in] paramElements 追加一组元素的元素指针
         @param [in] paramSize 追加元素的个数
         @param [in] paramStartIndex default = 0 插入的第一个元素在指针paramElements中的偏移位置
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
            throw XELessThanZero(); //如果是错误的size,则抛出异常
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
        在数组最后追加一个数组中指定的一组元素
         @param [in] paramElementArray 追加的元素数组
         @param [in] paramSize 追加元素的个数
         @param [in] paramStartIndex default = 0 指定插入元素相对指针的开始位置
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
        根据指定元素数组中一组元素，构造数组
         @param [in] paramElementArray 用于构造的元素数组
         @param [in] paramSize 构造的元素个数
         @param [in] paramStartIndex default = 0 指定开始构造元素在数组中的位置
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
         根据指定元素数据中一组元素，构造数组
         @param [in] paramElements 用于构造的一组元素开始指针
         @param [in] paramSize 构造的元素个数
         @param [in] paramStartIndex 指定开始构造元素相对元素指针的开始位置
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
         缺省拷贝构造函数
         @param [in] paramArray 用于构造的数组
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
         清除数组中的元素，被清除元素将被执行析构函数
         @param [in] paramFree default = false 内存重新分配标志
            - true 表示清除完元素，需要释放当前已经申请的内存，并重新申请一块内存。然后将长度置为0
            - false 表示仅清除元素，然后将长度置为0
    */
    template<class T>
    void XDynamicArray<T>::Clear( bool paramFree /*= false*/ )
    {
        //执行析构函数
        T * pT = m_Data;
        for(XInt i=0; i<m_Length; i++)
        {
            pT->~T();
            ++pT;
        }
        if( paramFree && m_Capacity > 0) //重新分配
        {
            delete[] (XByte *)m_Data;
            m_Data = NULL;
            m_Length = 0;
            m_Capacity = 0;
        }
        else
        {
            //清0已删除对象占用的数据
            if( m_Length > 0)
            {
                MemorySet(m_Data,0,m_Length * sizeof(T));
                m_Length = 0;
            }
        }
    }
    
    //----------------------------------------------------------------------------
    /**
         删除一个指定下标的元素，被删除的元素将会执行析构函数
         @param [in] paramIndex default = 0 被删除元素的下标
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
        //执行析构函数
        T * pT = m_Data + paramIndex;
        pT->~T();

        //如果删除不是最后一个元素，则移动数据
        if( !isLastIndex(paramIndex) ) 
        {
            MemoryMove(pT,((XByte *)pT)+sizeof(T),(m_Length - paramIndex - 1) * sizeof(T));
        }
        -- m_Length; //数组长度减1
        MemorySet(((XByte *)m_Data)+ m_Length * sizeof(T), 0, sizeof(T)); //将最后的数据清0
    }
    
    //----------------------------------------------------------------------------
    /**
         删除一个指定下标区域的元素，被删除的元素将会执行析构函数
         @param [in] paramStartIndex 开始删除的下标
         @param [in] paramRemoveCount 删除元素的个数
         @exception zdh::XEOutOfRange 
    */
    template<class T>
    void XDynamicArray<T>::RemoveArea(XInt paramStartIndex,XInt paramRemoveCount)
        ZDH_THROW(XEOutOfRange)
    {
        ZDH_ASSERT(paramStartIndex >= 0 && paramStartIndex < m_Length);
        //判断是否越界
        if( paramStartIndex >= m_Length || paramStartIndex < 0 ) 
        {
            throw XEOutOfRange(paramStartIndex,m_Length);
        }
        ZDH_ASSERT(paramRemoveCount>0 && ((paramStartIndex + paramRemoveCount) <= m_Length));
        T * pT = m_Data + paramStartIndex;
        for(XInt i=0; i<paramRemoveCount; i++, pT++) pT->~T(); //分别执行析构函数

        //后面的元素往前移
        XInt iMoveCount = m_Length - paramStartIndex - paramRemoveCount; //计算要移的个数
        if( iMoveCount >= 0 ) 
        {
            MemoryMove(m_Data + paramStartIndex, pT, iMoveCount * sizeof(T));
        }
        //将移动的部分清零
        MemorySet(m_Data + m_Length - paramRemoveCount, 0, paramRemoveCount * sizeof(T));
        m_Length -= paramRemoveCount;
    }
    
    //----------------------------------------------------------------------------
    /**
         在指定的位置插入元素指针指向的一组元素
         @param [in] paramIndex 插入的位置
         @param [in] paremElements 插入元素所在的元素指针
         @param [in] paramSize 插入元素的个数
         @param [in] paramStartIndex default = 0 指定插入元素相对指针的开始位置
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
        if( paramIndex == iLength ) //如果插入的位置在最后,则追加 
        {
            Append(paremElements, paramSize, paramStartIndex);
        }
        else
        {
            ensureCapacity( iLength + paramSize );

            T * pDest = m_Data + paramIndex;
            paremElements += paramStartIndex;
            MemoryMove(pDest + paramSize,pDest,(iLength - paramIndex) * sizeof(T)); //移动原有的数据
            for(XInt i=0; i<paramSize; i++, pDest++, paremElements++) 
            {
                new ((char *)(pDest)) T(*paremElements); //执行构造函数
            }

            m_Length += paramSize;
        }
    }
    
    //----------------------------------------------------------------------------
    /**
         在指定位置插入一个元素
         @param paramIndex 元素插入的位置
         @param paramElement 插入的元素
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
        //确定容量
        ensureCapacity(iLength + 1);
        //数据后移
        if( iLength > paramIndex ) 
        {
            MemoryMove(m_Data + paramIndex + 1,m_Data + paramIndex,(iLength - paramIndex)* sizeof(T));
        }

        new ((char *)(m_Data + paramIndex)) T(paramElement);//调用copy构造函数
        ++m_Length;
    }
    
    //----------------------------------------------------------------------------
    /**
         初始化指定长度的数组，数组中所有元素将被调用默认构造函数
         @param paramInitLength 初始化数组的长度
    */
    template<class T>
    void XDynamicArray<T>::InitLength( XInt paramInitLength )
    {
        expandCapacity(paramInitLength);
        m_Length = paramInitLength;
        T * pData = m_Data;
        while(paramInitLength > 0)
        {
            new ((char *)pData) T(); //调用缺省构造函数
            --paramInitLength;
            ++pData;
        }
    }
    
    //----------------------------------------------------------------------------
    /**
         初始化指定长度和元素初值的数组
         @param paramInitLength  初始化数组的长度
         @param paramElement 数组元素初始化值
    */
    template<class T>
    void XDynamicArray<T>::InitLength( XInt paramInitLength, const T & paramElement )
    {
        expandCapacity(paramInitLength);
        m_Length = paramInitLength;
        T * pData = m_Data;
        while(paramInitLength > 0)
        {
            new ((char *)pData) T(paramElement); //调用缺省构函数
            --paramInitLength;
            ++pData;
        }
    }

    //----------------------------------------------------------------------------
    /**
         扩展指定数组容量的容量
         @param [in] paramMinimumCapacity 指定的最小容量
    */
    template<class T>
    void XDynamicArray<T>::expandCapacity( XInt paramMinimumCapacity )
        ZDH_THROW(XEOutOfMemory)
    {
        ZDH_ASSERT(paramMinimumCapacity >= 0);
        if( paramMinimumCapacity > m_Capacity ) //如果实际需求大要所要的容量
        {
            //计算容量
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
            //计算实际字节点
            XInt iBytes = newCapacity * sizeof(T);

            //以16的倍数对齐
            if( iBytes % 16 > 0)
            {
                iBytes = iBytes + (16 - (iBytes % 16));
            }
            //
            char * pData = new char[iBytes]; //申请空间
            if( pData == NULL ) 
            {
                throw XEOutOfMemory();
            }
            //复制数据
            if( m_Length > 0) 
            {
                MemoryCopy(pData, m_Data, m_Length * sizeof(T));
            }

            //将剩下的清零
            MemorySet(pData + m_Length * sizeof(T), 0, iBytes - m_Length * sizeof(T));
            //释放原有资源
            if( m_Capacity > 0) 
            {
                delete[] (char *)m_Data;
            }
            //设置数组新内容
            m_Capacity = iBytes / sizeof(T);
            m_Data = (T *)pData;
        }
    }
    //----------------------------------------------------------------------------
    ///动态对象数组
    /**
        为了避免对象的移动，在这里实现了一个对象数组。可以像普通数组那样使用。但数组中的元素的位置变化的时候，
        不会改变对象的地址和重新生成对象。从而保证了对象的稳定性。
        原理是在原动态数组上，存放对象的指针，而这些指针指向这些对象。当对象在数组中移动的时候，移动的仅是对象
        的指针，而不是对象
     */
    template<class T>
    class XObjectArray
    {
    public:
        typedef T ElementType;
        typedef ElementType * PElementType;

        ///默认构造函数
        XObjectArray()
        {}

        ///指定初始元素个数的构造函数
        /**
         @param [in] paramInitLength 初始化数组的大小
        */
        XObjectArray(XInt paramInitLength)
        {
            if( paramInitLength > 0)
            {
                InitLength(paramInitLength);
            }
        }

        ///指定初始元素个数以及缺省元素值的构造函数
        /**
             @param [in] paramInitLength 初始化数组的大小
             @param [in] paramDefault 初始化数组元素的默认值
        */
        XObjectArray(XInt paramInitLength, const T & paramDefault)
        {
            if( paramInitLength > 0)
            {
                InitLength(paramInitLength,paramDefault);
            }
        }

        ///缺省拷贝构造函数
        XObjectArray(const XObjectArray<T> & paramElementArray);

        ///指定大小以及初始元素指针的构造函数
        XObjectArray(const T * paramData, XInt paramSize, XInt paramStartIndex = 0);

        ///指定大小以及初始元素数组的构造函数
        XObjectArray(const XObjectArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0);

        ///默认析构函数
        ~XObjectArray()
        {
            Clear();
        }

        ///清除数组
        void Clear();

        ///取数组的最大容量
        XInt getMaxCapacity() const
        {
            return 0x7ffffff0 / sizeof(T);
        }

        ///取有效的数组元素个数
        XInt getLength() const 
        {
            return m_Array.getLength();
        }

        ///取当前数组的容量
        XInt getCapacity() const
        {
            return m_Array.getCapacity();
        }

        ///判断数组是否为空
        /**
             @return 返回检查的结果
                - true 表示数组为空
                - false 表示数组不为空
        */
        bool isEmpty() const
        {
            return m_Array.isEmpty();
        }

        bool isNotEmpty() const
        {
            return m_Array.isNotEmpty();
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
            return m_Array.isValidIndex(paramIndex);
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
            return m_Array.isLastIndex(paramIndex);
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
            return m_Array.isFirstIndex(paramIndex);
        }

        ///取第一个下标
        /**
             @return 返回第一个下标
                - ARRAY_INVALID_INDEX 表示无效下标
                - 0 表示有效第一个下标
        */
        XInt getFirstIndex() const
        {
            return m_Array.getFirstIndex();
        }

        ///取最后一个下标
        /**
             @return 返回最后一个下标
                - ARRAY_INVALID_INDEX 表示无效下标
                - >=0 表示有效最后一个下标
        */
        XInt getLastIndex() const 
        {
            return m_Array.getLastIndex();
        }

        ///取指定下标的数组元素
        /**
             @param [in] paramIndex 指定的下标
             @return 返回指定下标的引用
             @exception 如果发生越界，则抛出XEOutOfRange异常
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

        ///取指定下标的数组元素
        /**
             @param [in] paramIndex 指定的下标
             @return 返回指定下标的引用
             @exception 如果发生越界，则抛出XEOutOfRange异常
        */
        T & getElement (XInt paramIndex) 
        {
            return *m_Array[paramIndex];
        }

        const T & getElement (XInt paramIndex) const 
        {
            return *m_Array[paramIndex];
        }
        
        ///确认最小容量
        /**
             确认最小容量，如果容量不够，则扩展容量
             @param [in] paramMinimumCapacity 确认的最小容量
        */
        void ensureCapacity(XInt paramMinimumCapacity)
        {
            expandCapacity(paramMinimumCapacity);
        }
        
        ///追加一个元素
        /**
             @param [in] paramElement 追加的元素
             @return 返回当前对象的引用
        */
        XObjectArray<T> & operator <<(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///追加一个数组的元素
        /**
             @param [in] paramElementArray 追加的数组
             @return 返回当前对象的引用
        */
        XObjectArray<T> & operator <<(const XObjectArray<T> & paramElementArray)
        {
                Append(paramElementArray);
                return *this;
        }
        
        ///追加一个元素
        /**
             @param [in] paramElement 追加的元素
             @return 返回当前对象的引用
        */
        XObjectArray<T> & operator +=(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///追加一个数组的元素
        /**
             @param [in] paramElement 追加的数组
             @return 返回当前对象的引用
        */
        XObjectArray<T> & operator +=(const XObjectArray<T> & paramElementArray)
        {
            Append(paramElementArray);
            return *this;
        }
        
        ///追加一个元素
        /**
             @param [in] paramElement 追加的元素
             @return 返回当前对象的引用
        */
        XObjectArray<T> & operator ,(const T & paramElement)
        {
            Append(paramElement);
            return *this;
        }
        
        ///追加一个数组的元素
        /**
             @param [in] paramElement 追加的数组
             @return 返回当前对象的引用
        */
        XObjectArray<T> & operator ,(const XObjectArray<T> & paramElementArray)
        {
            Append(paramElementArray);
            return *this;
        }
        
        ///在数组最后追加一个元素
        /**
         @param [in] paramElement 追加的元素
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

        ///在数组最后追加一个数组
        void Append(const XObjectArray<T> & paramElementArray)
        {
            if( paramElementArray.getLength() > 0 )
            {
                Append( paramElementArray, paramElementArray.getLength(), 0);
            }
        }
        
        ///在数组最后追加一个数组中指定的一组元素
        void Append(const XObjectArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0);
        
        ///在数组最后追加一个元素指针指定的一组元素
        void Append(const T * paramElements, XInt paramSize, XInt paramStartIndex = 0);
        
        ///在指定的位置插入一个数组
        /**
             在指定的位置插入一个数组
             @param paramIndex 插入的位置
             @param paramElementArray 插入的数组
        */
        void Insert(XInt paramIndex,const XObjectArray<T> & paramElementArray)
        {
            Insert(paramIndex, paramElementArray, paramElementArray.getLength(), 0);
        }
        
        ///在指定的位置插入一个数组中指定的一组元素
        /**
             @param [in] paramIndex 插入的位置
             @param [in] paramElementArray 插入元素的数组
             @param [in] paramSize 插入数组元素的个数
             @param [in] paramStartIndex default = 0 指定插入元素在数组中的位置
        */
        void Insert(XInt paramIndex,const XObjectArray<T> & paramElementArray,XInt paramSize,XInt paramStartIndex = 0);

        ///在指定的位置插入元素指针指向的一组元素
        void Insert(XInt paramIndex,const T * paramElements,XInt paramSize,XInt paramStartIndex = 0);
        
        ///在数组的最前面插入一个数组
        /**
            @param [in] paramElementArray 插入的数组
        */
        void Insert(const XObjectArray<T> & paramElementArray)
        {
            Insert(0, paramElementArray, paramElementArray.getLength(), 0);
        }
        
        ///在数组的最前面插入数组中指定的一组元素
        /**
             @param [in] paramElementArray 插入元素所在的数组
             @param [in] paramSize 插入元素的个数
             @param [in] paramStartIndex 插入元素在数组中的开始位置
        */
        void Insert(const XObjectArray<T> & paramElementArray, XInt paramSize, XInt paramStartIndex = 0)
        {
            Insert(0, paramElementArray, paramSize, paramStartIndex);
        }
        
        ///在数组的最前面插入元素指针指向的一组元素
        /**
             @param [in] paramElements 插入元素所在的元素指针
             @param [in] paramSize 插入元素的个数
             @param [in] paramStartIndex default = 0 指定插入元素相对指针的开始位置
        */
        void Insert(const T * paramElements, XInt paramSize, XInt paramStartIndex = 0)
        {
            Insert(0,paramElements, paramSize, paramStartIndex);
        }
        
        ///在指定位置插入一个元素
        /**
             在指定位置插入一个元素
             @param paramIndex 元素插入的位置
             @param paramElement 插入的元素
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

        ///在数组的最前面插入一个元素
        void Insert(const T & paramElement)
        {
            Insert(0, paramElement);
        }
        
        ///在最后压入一个元素
        /**
            @param [in] paramElement 被压入的元素
            @return bool 压入的结果
                - true 压入元素成功
                - false 压入元素失败
         */
        bool Push(const T & paramElement)
        {
            Append(paramElement);
            return true;
        }
        
        ///在最后弹出一个元素
        /**
            @param [out] paramElement 弹出的元素
            @return bool 弹出结果
                - true 弹出成功
                - false 弹出失败
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
        
        ///删除最后一个元素
        void RemoveLast();
        
        ///删除指定位置的元素
        void Remove(XInt paramIndex  = 0);
        
        ///删除指定删除区域的元素
        void RemoveArea(XInt paramStartIndex, XInt paramRemoveCount);
        
        ///赋值方法
        /**
             这个方法，会释放已有的所有元素
             @param paramArray 被赋值的源数组
             @return 返回当前数组的引用
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
        
        ///交换数组元素
        void Swap(XInt paramAIndex,XInt paramBIndex)
        {
            m_Array.Swap(paramAIndex,paramBIndex);
        }
        
        ///默认排序
        void Sort()
        {
            Array_QuickSort(*this,XFunctions_Less<T>());
        }
        
        ///使用快速排序模板
        /**
            @param [in] paramCompare 比较用的对象
         */
        template<class Compare>
        void Sort_QuickSort(const Compare & paramCompare)
        {
            Array_QuickSort(*this,paramCompare);
        }
        
        ///使用快速排序
        /**
            @param [in] paramAscending 升序标志
                - true 表示升序
                - false 表示降序
         */
        void Sort_QuickSort(bool paramAscending = true)
        {
            if( paramAscending ) Array_QuickSort(*this,XFunctions_Less<T>());
            else Array_QuickSort(*this,XFunctions_Greater<T>());
        }
        
        ///使用冒泡排序模板
        /**
            @param [in] paramCompare 比较用的对象
         */
        template<class Compare>
        void Sort_BubbleSort(const Compare & paramCompare)
        {
            Array_BubbleSort(*this,paramCompare);
        }
        
        ///使用冒泡排序
        /**
            @param [in] paramAscending 升序标志
                - true 表示升序
                - false 表示降序
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
        
        ///使用依次查找的办法，查找指定元素
        /**
         * 这个需要指定比较两个元素相等的对象
         * @param [in] paramElement 被查找的元素
         * @param [in] paramEqual 比较等于的类的对象
         * @return 返回查找结果
         *      - ARRAY_INVALID_INDEX 表示数据未找到
         *      - 其它值 表示数据在数组中的下标
         */
        template<class CompareEQU>
        XInt Find_Normal(const T & paramElement, const CompareEQU & paramEqual)
        {
            return Array_Find_Normal(*this, paramElement,paramEqual);
        }
        
        ///使用依次查找的办法，查找指定元素
        /**
         * 这个方法默认使用XFunctions_Equal<T>比较等于的对象
         * @param [in] paramElement 被查找的元素
         * @return 返回查找结果
         *      - ARRAY_INVALID_INDEX 表示数据未找到
         *      - 其它值 表示数据在数组中的下标
         */
        XInt Find_Normal(const T & paramElement)
        {
            return Array_Find_Normal(*this,paramElement,XFunctions_Equal<T>());
        }
        
        ///使用二分查找的办法，查找指定元素
        /**
         * 这个需要指定比较大小的对象，如XFunctions_Compare
         * @param [in] paramElement 被查找的元素
         * @param [in] paramEqual 比较等于的类的对象
         * @return 返回查找结果
         *      - ARRAY_INVALID_INDEX 表示数据未找到
         *      - 其它值 表示数据在数组中的下标
         */
        template<class Compare>
        XInt Find_Binary(const T & paramElement,const Compare & paramCompare)
        {
            return Array_Find_Binary(*this,paramElement,paramCompare);
        }
        
        ///使用二分查找的办法，查找指定元素
        /**
         * 这个方法默认使用XFunctions_Comapre<T>比较等于的对象
         * @param [in] paramElement 被查找的元素
         * @return 返回查找结果
         *      - ARRAY_INVALID_INDEX 表示数据未找到
         *      - 其它值 表示数据在数组中的下标
         */
        XInt Find_Binary(const T & paramElement)
        {
            return Array_Find_Binary(*this,paramElement,XFunctions_Compare<T>());
        }
    private:
        
        ///扩展指定数组容量的容量
        /**
            @param [in] minimumCapacity 指定的最小容量
        */
        void expandCapacity(XInt minimumCapacity)
        {
            m_Array.ensureCapacity(minimumCapacity);
        }
        
        ///初始化指定长度的数组
        void InitLength(XInt paramInitLength);
        
        ///初始化指定长度和元素初值的数组
        void InitLength(XInt paramInitLength,const T & paramValue);
    private:
        XDynamicArray<T *> m_Array;       ///<当前已使用的对象指针数组
    };

    //---------------------------------------------------------------------------
    //模板类成员函数的实现
    template<class T>
    void XObjectArray<T>::Clear()
    {
        //执行相关默认析构函数
        for(XInt i = m_Array.getLength() - 1; i>=0; i--) 
        {
            delete m_Array[i];
        }
        //
        m_Array.Clear();
    }

    //----------------------------------------------------------------------------
    /**
         根据指定元素数组中一组元素，构造数组
         @param [in] paramElementArray 用于构造的元素数组
         @param [in] paramSize 构造的元素个数
         @param [in] paramStartIndex default = 0 指定开始构造元素在数组中的位置
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
         根据指定元素数据中一组元素，构造数组
         @param [in] paramData 用于构造的一组元素开始指针
         @param [in] paramSize 构造的元素个数
         @param [in] paramStartIndex 指定开始构造元素相对元素指针的开始位置
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
         缺省拷贝构造函数
         @param [in] paramElementArray 用于构造的数组
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
         初始化指定长度和元素初值的数组
         @param paramInitLength 初始化数组的长度
         @param paramValue 数组元素初始化值
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
        初始化指定长度的数组
        @param paramInitLength 初始化数组的长度
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
        在数组最后追加一个元素指针指定的一组元素
         @param [in] paramElements 追加一组元素的元素指针
         @param [in] paramSize 追加元素的个数
         @param [in] paramStartIndex default = 0 插入的第一个元素在指针paramElements中的偏移位置
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
         在数组最后追加一个数组中指定的一组元素
         @param [in] paramElementArray 追加的元素数组
         @param [in] paramSize 追加元素的个数
         @param [in] paramStartIndex default = 0 指定插入元素相对指针的开始位置
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
         在指定的位置插入元素指针指向的一组元素
         @param [in] paramIndex 插入的位置
         @param [in] paramElements 插入元素所在的元素指针
         @param [in] paramSize 插入元素的个数
         @param [in] paramStartIndex default = 0 指定插入元素相对指针的开始位置
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
            Append(paramElements,paramSize,paramStartIndex);//如果当前数组没有数据，则直接追加
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
         @param [in] paramIndex 插入的位置
         @param [in] paramElementArray 插入元素的数组
         @param [in] paramSize 插入数组元素的个数
         @param [in] paramStartIndex default = 0 指定插入元素在数组中的位置
    */
    template<class T>
    void XObjectArray<T>::Insert(XInt paramIndex,const XObjectArray<T> & paramElementArray,XInt paramSize,XInt paramStartIndex)
        ZDH_THROW(XEOutOfRange) ZDH_THROW(XELessThanZero)
    {
        ZDH_ASSERT(paramStartIndex >= 0 && paramStartIndex < paramElementArray.getLength());
        ZDH_ASSERT(paramSize > 0);
        ZDH_ASSERT(paramSize + paramStartIndex < paramElementArray.getLength());
        //确定复制源的下标是否合法
        XInt vLength = paramElementArray.getLength();
        if( paramStartIndex < 0 || paramStartIndex >= vLength ) 
        {
            throw XEOutOfRange(paramStartIndex,vLength);
        }
        if( paramSize <= 0)
        {
            throw XELessThanZero(); //确定Copy的数据
        }
        if( paramSize + paramStartIndex >= vLength ) 
        {
            throw XEOutOfRange( paramSize + paramStartIndex, vLength );
        }
        //确定插入目标的下标是否合法
        XInt iLength = getLength();
        if( paramIndex > iLength || paramIndex < 0 ) 
        {
            throw XEOutOfRange( paramIndex, iLength);
        }

        if( iLength == paramIndex ) 
        {
            Append(paramElementArray,paramSize,paramStartIndex);//如果没有数据，则追加数据
        }
        else
        { 
            //如果存在插入的位置
            ensureCapacity(iLength + paramSize);
            for( XInt i = 0; i<paramSize; i++) 
            {
                m_Array.Insert( i + paramIndex, new T(paramElementArray[paramStartIndex + i]));
            }
        }
    }

    //----------------------------------------------------------------------------
    /**
         删除一个指定下标的元素，被删除的元素将会执行析构函数
         @param [in] paramIndex default = 0 被删除元素的下标
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
        //执行析构函数
        delete m_Array[paramIndex];
        m_Array.Remove(paramIndex);
    }

    //----------------------------------------------------------------------------
    /**
         删除一个指定下标区域的元素，被删除的元素将会执行析构函数
         @param [in] paramStartIndex 开始删除的下标
         @param [in] paramRemoveCount 删除元素的个数
         @exception zdh::XEOutOfRange 
    */
    template<class T>
    void XObjectArray<T>::RemoveArea(XInt paramStartIndex,XInt paramRemoveCount)
        ZDH_THROW(XEOutOfRange) ZDH_THROW(XELessThanZero)
    {
        ZDH_ASSERT(isValidIndex(paramStartIndex));
        ZDH_ASSERT(paramRemoveCount >= 0);
        ZDH_ASSERT(paramRemoveCount + paramStartIndex <= getLength());
        //判断是否越界
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
        删除数组的最后一个元素，被删除的元素将会执行析构函数
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
