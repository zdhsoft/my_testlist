///内存相关函数
/**
 * 内存分配接口和一些内存相关函数
 * 
 * zdhsoft 2011 版权所有
 *
 * @file xstring_utils.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-08
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、内存相关函数

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-08  1.0             创建初始文件
***********************************************************************/
#ifndef X_MEMORY_H_
#define X_MEMORY_H_
#include <xtype.h>
namespace zdh
{
#if defined(CPU_32)
    typedef XInt XMemorySize;
#else
    typedef XLong XMemorySize;
#endif

    ///分配内存
    /**
        @param [in] paramSize 要分配内存的字节数
        @return void * 返回分配内存的指针
     */
    inline void * AllocMemory(XMemorySize paramSize)
    {
        return (void *)new XByte[paramSize];
    }
    ///释放内存
    /**
        @param [in] paramMemory 要释放的内存
     */
    inline void FreeMemory(void * paramMemory)
    {
        delete[] (XByte *)paramMemory;
    }
    ///new出一个对象,默认构造函数
    template<class T>
    inline T * NewObject()
    {
        char * pValue = (char *)AllocMemory(sizeof(T));
        return new (pValue) T();
    }
    ///new出一个对象，默认拷贝构造函数
    template<class T>
    inline T * NewObject(const T & a_Obj)
    {
        char * pValue = (char *)AllocMemory(sizeof(T));
        return new (pValue) T(a_Obj);
    }
    ///delete一个对象
    template<class T>
    inline void DeleteObject(T * paramObject)
    {
        ZDH_ASSERT(paramObject != NULL);
        paramObject->~T();
        FreeMemory(paramObject);
    }
    namespace detail
    {
        //请不要直接这里定义的函数
        ///复制内存
        template<class T>
        static T * _MemoryCopy(T * paramMemoryDest, const T* paramMemorySrc, XMemorySize paramCopySize)
        {
            XMemorySize iCopyBytes; 
            PByte pBS; 
            PByte pBD; 
            if( (paramMemoryDest > paramMemorySrc) && ((PByte(paramMemoryDest) - PByte(paramMemorySrc)) < XMemorySize(sizeof(XDDWord))))
            {
                pBS = PByte(paramMemorySrc);
                pBD = PByte(paramMemoryDest);
                iCopyBytes = paramCopySize;
            }
            else
            {
                PDDWord  pS = PDDWord(paramMemorySrc);
                PDDWord pD = PDDWord(paramMemoryDest);
                for(XMemorySize i = paramCopySize / sizeof(XDDWord); i > 0; i--, pS++, pD++)
                {
                    *pD = *pS;
                }
                pBS = PByte(pS);
                pBD = PByte(pD);
                iCopyBytes = paramCopySize % sizeof(XDDWord);
            }
            for(XMemorySize i = iCopyBytes; i > 0; i--, pBS ++, pBD ++)
            {
                *pBD = *pBS;
            }
            return paramMemoryDest;
        }
        ///初始化内存
        template<class T>
        static void * _MemorySet(T * paramMemory, XMemorySize paramMemorySize, XByte paramValue)
        {
            if( paramMemorySize > 16)  //如果大于16字节，就做优化,以8字节的速度复制
            {
                //初始化要复制的数据
                union 
                {
                    XDDWord ddwV;
                    XByte btV[sizeof(XDDWord)];
                }temp;
                {
                    PByte pDest = temp.btV;
                    for(XMemorySize i = (XMemorySize)sizeof(temp.btV); i > 0 ; i-- )
                    {
                        *pDest ++ = paramValue;
                    }
                }

                {
                    //复制
                    XMemorySize iCopyCount = paramMemorySize / sizeof(XDDWord);
                    PDDWord pDest = (PDDWord)paramMemory;
                    while(iCopyCount > 0)
                    {
                        *pDest ++ = temp.ddwV;
                        iCopyCount --;
                    }
                    iCopyCount = paramMemorySize % sizeof(XLong);
                    PByte pByteDest = (PByte)pDest;
                    while(iCopyCount > 0)
                    {
                        *pByteDest ++ = (XByte)paramValue;
                        iCopyCount --;
                    }
                }
            }
            else if( paramMemorySize > 0 )
            {
                PByte pDest = (PByte)paramMemory;
                XByte btValue = (XByte)paramValue;
                for(XMemorySize i = 0; i < paramMemorySize; i++)
                {
                    *pDest ++ = btValue;
                }
            }
            return paramMemory;
        }
        ///移动内存块
        template<class T>
        static T * _MemoryMove(T * paramMemoryDest, const T * paramMemorySrc, XMemorySize paramMoveSize)
        {
            //检查是否有重叠
            XMemorySize iDis = XMemorySize(PByte(paramMemoryDest) - PByte(paramMemorySrc));
            if (iDis > 0 && iDis < paramMoveSize) //如果存在重叠现象
            {
                PByte pBS;
                PByte pBD;
                XMemorySize iCopyCount;
                if (iDis >= XMemorySize(sizeof(XDDWord)))
                {
                    PDDWord pS = PDDWord(PByte(paramMemorySrc) + paramMoveSize);
                    PDDWord pD = PDDWord(PByte(paramMemoryDest) + paramMoveSize);
                    iCopyCount = paramMoveSize / sizeof(XDDWord);
                    while(iCopyCount > 0)
                    {
                        pS--;
                        pD--;
                        *pD = *pS;
                        iCopyCount --;
                    }
                    iCopyCount = paramMoveSize % sizeof(XDDWord);
                    pBS = PByte(pS);
                    pBD = PByte(pD);
                }
                else
                {
                    iCopyCount = paramMoveSize;
                    pBS = PByte(paramMemorySrc) + paramMoveSize;
                    pBD = PByte(paramMemoryDest) + paramMoveSize;
                }

                while(iCopyCount > 0)
                {
                    pBS--;
                    pBD--;
                    *pBD = *pBS;
                    iCopyCount --;
                }
            }
            else
            {
                return _MemoryCopy(paramMemoryDest, paramMemorySrc, paramMoveSize);
            }
            return paramMemoryDest;
        }
    }
    ///将内存初始化为0
    inline void * MemoryZero(void * paramMemory, XMemorySize paramSize)
    {
        ZDH_ASSERT(paramMemory != NULL);
        ZDH_ASSERT(paramSize >= 0);
        return detail::_MemorySet(paramMemory, paramSize, 0);
    }
    ///将指定对象初始化为0
    template<class T>
    inline void MemoryZero(T & paramObject)
    {
        detail::_MemorySet( &paramObject, sizeof(T), 0 );
    }
    ///将指定对象数组初始化为0
    template<class T,int N>
    inline void MemoryZero(T (&paramData)[N] )
    {
        if (N * sizeof(T) > 0)
            detail::_MemorySet( &paramData, N * sizeof(T), 0 );
    }
    ///重置内存
    /**
        @param [out] paramMemory 目标内存指针
        @param [in] paramSize 要设置内存的字节数
        @param [in] paramValue 要设成的值
        @return void * 目标内存的指针
     */
    inline void * MemorySet(void * paramMemory, XMemorySize paramSize, XInt paramValue)
    {
        ZDH_ASSERT(paramMemory != NULL);
        ZDH_ASSERT(paramSize >= 0);
        return detail::_MemorySet(paramMemory, paramSize, (XByte)paramValue);
    }
    ///复制内存
    /**
        这个函数不会检查目标内存和源内存是否有重叠。有重叠的话，有可能得到错误的内存复制。
        @param [out] paramDest 目标内存指针
        @param [in]  paramSrc  源内存的指针
        @param [in]  paramCopySize 要复制内存的字节数
        @return void * 目标内存的指针
     */
    inline void * MemoryCopy(void * paramDest,const void * paramSrc, XMemorySize paramCopySize)
    {
        ZDH_ASSERT(paramDest != NULL);
        ZDH_ASSERT(paramSrc != NULL);
        ZDH_ASSERT(paramCopySize >= 0);
        return detail::_MemoryCopy(paramDest, paramSrc, paramCopySize);
    }

    ///复制内存
    /**
        这个函数不会检查目标内存和源内存是否有重叠。有重叠的话，有可能得到错误的内存复制。
        要求参数是数组的定义 如：int paramDest[100];
        并且原数组和目标数组的大小完全一样
        @param [out] paramDest 目标数组
        @param [in]  paramSrc  源数组
        @return T * 目标数组指针
     */
    template<class T,int N>
    inline T * MemoryCopy(T (&paramDest)[N], const T (&paramSrc)[N])
    {
        MemoryCopy(&paramDest, &paramSrc, (XMemorySize)(sizeof(T) * N));
        return paramDest;
    }

    ///复制数组
    /**
        这个函数不会检查目标内存和源内存是否有重叠。有重叠的话，有可能得到错误的内存复制。
        要求参数是数组的定义 如：int paramDest[100];
        并且原数组和目标数组的大小完全一样
        @param [out] paramDest 目标数组
        @param [in]  paramSrc  源数组
        @return T * 目标数组指针
     */
    template<class T,int N>
    inline T * ArrayCopy(T (&paramDest)[N], const T (&paramSrc)[N])
    {
        for(int i = 0; i < N; i++)
        {
            paramDest[i] = paramSrc[i];
        }
        return paramDest;
    }
    ///移动内存
    /**
        这个函数会检查目标内存和源内存是否有重叠。会保证内存被正确复制
        @param [out] paramDest 目标内存指针
        @param [in]  paramSrc  源内存的指针
        @param [in]  paramCopySize 要复制内存的字节数
        @return void * 目标内存的指针
     */
    inline void * MemoryMove(void * paramDest, const void * paramSrc, XMemorySize paramMoveSize)
    {
        ZDH_ASSERT(paramDest != NULL);
        ZDH_ASSERT(paramSrc != NULL);
        ZDH_ASSERT(paramMoveSize >= 0);
        return detail::_MemoryMove(paramDest, paramSrc, paramMoveSize);
    }
}

#endif /* X_MEMORY_H_ */
