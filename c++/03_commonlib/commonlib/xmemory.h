///�ڴ���غ���
/**
 * �ڴ����ӿں�һЩ�ڴ���غ���
 * 
 * zdhsoft 2011 ��Ȩ����
 *
 * @file xstring_utils.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-08
 * company zdhsoft
 */
/**********************************************************************
    �����б�  //��Ҫ��������
    1���ڴ���غ���

    ��ʷ:       //��Ҫ�޸ļ�¼
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-08  1.0             ������ʼ�ļ�
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

    ///�����ڴ�
    /**
        @param [in] paramSize Ҫ�����ڴ���ֽ���
        @return void * ���ط����ڴ��ָ��
     */
    inline void * AllocMemory(XMemorySize paramSize)
    {
        return (void *)new XByte[paramSize];
    }
    ///�ͷ��ڴ�
    /**
        @param [in] paramMemory Ҫ�ͷŵ��ڴ�
     */
    inline void FreeMemory(void * paramMemory)
    {
        delete[] (XByte *)paramMemory;
    }
    ///new��һ������,Ĭ�Ϲ��캯��
    template<class T>
    inline T * NewObject()
    {
        char * pValue = (char *)AllocMemory(sizeof(T));
        return new (pValue) T();
    }
    ///new��һ������Ĭ�Ͽ������캯��
    template<class T>
    inline T * NewObject(const T & a_Obj)
    {
        char * pValue = (char *)AllocMemory(sizeof(T));
        return new (pValue) T(a_Obj);
    }
    ///deleteһ������
    template<class T>
    inline void DeleteObject(T * paramObject)
    {
        ZDH_ASSERT(paramObject != NULL);
        paramObject->~T();
        FreeMemory(paramObject);
    }
    namespace detail
    {
        //�벻Ҫֱ�����ﶨ��ĺ���
        ///�����ڴ�
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
        ///��ʼ���ڴ�
        template<class T>
        static void * _MemorySet(T * paramMemory, XMemorySize paramMemorySize, XByte paramValue)
        {
            if( paramMemorySize > 16)  //�������16�ֽڣ������Ż�,��8�ֽڵ��ٶȸ���
            {
                //��ʼ��Ҫ���Ƶ�����
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
                    //����
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
        ///�ƶ��ڴ��
        template<class T>
        static T * _MemoryMove(T * paramMemoryDest, const T * paramMemorySrc, XMemorySize paramMoveSize)
        {
            //����Ƿ����ص�
            XMemorySize iDis = XMemorySize(PByte(paramMemoryDest) - PByte(paramMemorySrc));
            if (iDis > 0 && iDis < paramMoveSize) //��������ص�����
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
    ///���ڴ��ʼ��Ϊ0
    inline void * MemoryZero(void * paramMemory, XMemorySize paramSize)
    {
        ZDH_ASSERT(paramMemory != NULL);
        ZDH_ASSERT(paramSize >= 0);
        return detail::_MemorySet(paramMemory, paramSize, 0);
    }
    ///��ָ�������ʼ��Ϊ0
    template<class T>
    inline void MemoryZero(T & paramObject)
    {
        detail::_MemorySet( &paramObject, sizeof(T), 0 );
    }
    ///��ָ�����������ʼ��Ϊ0
    template<class T,int N>
    inline void MemoryZero(T (&paramData)[N] )
    {
        if (N * sizeof(T) > 0)
            detail::_MemorySet( &paramData, N * sizeof(T), 0 );
    }
    ///�����ڴ�
    /**
        @param [out] paramMemory Ŀ���ڴ�ָ��
        @param [in] paramSize Ҫ�����ڴ���ֽ���
        @param [in] paramValue Ҫ��ɵ�ֵ
        @return void * Ŀ���ڴ��ָ��
     */
    inline void * MemorySet(void * paramMemory, XMemorySize paramSize, XInt paramValue)
    {
        ZDH_ASSERT(paramMemory != NULL);
        ZDH_ASSERT(paramSize >= 0);
        return detail::_MemorySet(paramMemory, paramSize, (XByte)paramValue);
    }
    ///�����ڴ�
    /**
        �������������Ŀ���ڴ��Դ�ڴ��Ƿ����ص������ص��Ļ����п��ܵõ�������ڴ渴�ơ�
        @param [out] paramDest Ŀ���ڴ�ָ��
        @param [in]  paramSrc  Դ�ڴ��ָ��
        @param [in]  paramCopySize Ҫ�����ڴ���ֽ���
        @return void * Ŀ���ڴ��ָ��
     */
    inline void * MemoryCopy(void * paramDest,const void * paramSrc, XMemorySize paramCopySize)
    {
        ZDH_ASSERT(paramDest != NULL);
        ZDH_ASSERT(paramSrc != NULL);
        ZDH_ASSERT(paramCopySize >= 0);
        return detail::_MemoryCopy(paramDest, paramSrc, paramCopySize);
    }

    ///�����ڴ�
    /**
        �������������Ŀ���ڴ��Դ�ڴ��Ƿ����ص������ص��Ļ����п��ܵõ�������ڴ渴�ơ�
        Ҫ�����������Ķ��� �磺int paramDest[100];
        ����ԭ�����Ŀ������Ĵ�С��ȫһ��
        @param [out] paramDest Ŀ������
        @param [in]  paramSrc  Դ����
        @return T * Ŀ������ָ��
     */
    template<class T,int N>
    inline T * MemoryCopy(T (&paramDest)[N], const T (&paramSrc)[N])
    {
        MemoryCopy(&paramDest, &paramSrc, (XMemorySize)(sizeof(T) * N));
        return paramDest;
    }

    ///��������
    /**
        �������������Ŀ���ڴ��Դ�ڴ��Ƿ����ص������ص��Ļ����п��ܵõ�������ڴ渴�ơ�
        Ҫ�����������Ķ��� �磺int paramDest[100];
        ����ԭ�����Ŀ������Ĵ�С��ȫһ��
        @param [out] paramDest Ŀ������
        @param [in]  paramSrc  Դ����
        @return T * Ŀ������ָ��
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
    ///�ƶ��ڴ�
    /**
        �����������Ŀ���ڴ��Դ�ڴ��Ƿ����ص����ᱣ֤�ڴ汻��ȷ����
        @param [out] paramDest Ŀ���ڴ�ָ��
        @param [in]  paramSrc  Դ�ڴ��ָ��
        @param [in]  paramCopySize Ҫ�����ڴ���ֽ���
        @return void * Ŀ���ڴ��ָ��
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
