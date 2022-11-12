/** 
    Copyright (c) 2012 zdhsoft Inc. All rights reserved.
 */

#ifndef _X_COMMONLIB_ALLOCATOR_H_
#define _X_COMMONLIB_ALLOCATOR_H_

#include <xtype.h>

namespace zdh 
{
    namespace detail
    {
        //调用构造函数
        template<class T1, class T2> 
        inline void __Construct(T1 *paramPtr, const T2 & paramValue)
        {	
            ::new (Pointer(paramPtr)) T1(paramValue);
        }
        //调用构造函数
        template<class T> 
        inline void __Construct(T *paramPtr)
        {	
            ::new (Pointer(paramPtr)) T();
        }

        template<class T>
        inline void ___Destroy(T * paramPtr)
        {
            (paramPtr)->~T();
        }

        template<> 
        inline void ___Destroy(char *)
        {	// destroy a char (do nothing)
        }

        template<> 
        inline void ___Destroy(wchar_t *)
        {	// destroy a wchar_t (do nothing)
        }


    }

    class XAllocator 
    {
    public:
        Pointer Alloc(size_t paramSize) 
        {
            if (paramSize < 0) paramSize = 0;
            return ::operator new(paramSize);
        }
        void Free(Pointer paramMemory) 
        {
            ::operator delete(paramMemory);
        }
    };
}
#endif
