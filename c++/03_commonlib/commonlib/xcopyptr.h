#ifndef _X_COPY_PTR_H_
#define _X_COPY_PTR_H_
#include <xtype.h>
#include <xallocator.h>
namespace zdh
{
    //一个用于对象复制的指针模板类
    template<class T, class Allocator = XAllocator>
    class XCopyPtr
    {
    public:
        XCopyPtr()
            :m_Object(NULL)
        {}
        XCopyPtr(T * paramObject)
            :m_Object(paramObject)
        {}
        XCopyPtr(XCopyPtr & paramObject)
            :m_Object(paramObject.m_Object)
        {
            paramObject.m_Object = NULL;
        }

        ~XCopyPtr()
        {
            Release();
        }

        bool NewObject()
        {
            Release();
            Allocator stAlloc;
            Pointer p = stAlloc.Alloc(sizeof(T));
            if (isNotNULL(p))
            {
                m_Object = reinterpret_cast<T *>(p);
                new ((char *)m_Object) T();
                return true;
            }
            else
            {
                return false;
            }
        }

        bool NewObject(const T & paramObject)
        {
            Release();
            Allocator stAlloc;
            Pointer p = stAlloc.Alloc(sizeof(T));
            if (isNotNULL(p))
            {
                m_Object = reinterpret_cast<T *>(p);
                new ((char *)m_Object) T(paramObject);
                return true;
            }
            else
            {
                return false;
            }
        }

        XCopyPtr & operator = (XCopyPtr & paramObject)
        {
            if(this != &paramObject)
            {
                Release();
                m_Object = paramObject.m_Object;
                paramObject.m_Object = NULL;
            }

            return *this;
        }

        XCopyPtr & operator = (T * paramObject)
        {
            if (m_Object != paramObject)
            {
                Release();
                m_Object = paramObject;
            }
            return this;
        }
        
        void Release()
        {
            if (!isEmpty())
            {
                m_Object->~T();
                Allocator stAlloc;
                stAlloc.Free(m_Object);
                m_Object = NULL;
            }
        }

        bool isEmpty() const
        {
            return isNULL(m_Object);
        }

        const T * operator->() const
        {
            return m_Object;
        }

        T * operator->() 
        {
            return m_Object;
        }

        T & operator *()
        {
            return *m_Object;
        }

        const T & operator *() const
        {
            return *m_Object;
        }
        
        //取对象指针
        T * getObject()
        {
            return m_Object;
        }

        const T * getObject() const
        {
            return m_Object;
        }

    private:
        T * m_Object;
    };
}
#endif
