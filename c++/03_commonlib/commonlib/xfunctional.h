///�º���ģ��
/**
 * �º���ģ��
 * �����ṩ��һ��º���ģ�塣
 * zdhsoft 2011 ��Ȩ����
 *
 * @file xfunctional.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-13
 * company zdhsoft
 */
/**********************************************************************
    �����б�  //��Ҫ��������
    1��һ��º���ģ��

    ��ʷ:       //��Ҫ�޸ļ�¼
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-13  1.0             ������ʼ�ļ�
***********************************************************************/
#ifndef _X_FUNCTIONAL_H_
#define _X_FUNCTIONAL_H_
namespace zdh
{
    //---------------------------------------------------------------------------
    ///һԪ�º����Ļ���ģ����
    /**
     * һԪ�º����Ļ���ģ����
     */
    template<class Arg,class Result>
    class XFunctions_One
    {
    public:
        ///һԪ�������Ͷ���
        typedef Arg ArgType;
        ///���ؽ�����Ͷ���
        typedef Result ResultType;
    };

    //---------------------------------------------------------------------------
    ///��Ԫ�º����Ļ���ģ����
    template<class Arg1,class Arg2,class Result>
    class XFunctions_Binary
    {
    public:
        ///����һ���Ͷ���
        typedef Arg1 Arg1Type;
        ///���������Ͷ���
        typedef Arg2 Arg2Type;
        ///���ؽ�����Ͷ���
        typedef Result ResultType;
    };

    //����һ���ϵ������ķº���
    //---------------------------------------------------------------------------
    ///���ڷº���ģ����
    template<class T>
    class XFunctions_Equal : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚ����������Ƿ����
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���x==y�򷵻�true�����򷵻�false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x == y;
        }
    };

    //---------------------------------------------------------------------------
    ///�����ڷº���ģ����
    template<class T>
    class XFunctions_NotEqual : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚ����������Ƿ����
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���x!=y�򷵻�true�����򷵻�false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x != y;
        }
    };

    //---------------------------------------------------------------------------
    ///���ڷº���ģ����
    template<class T>
    class XFunctions_Greater : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚϵ�һ�������Ƿ���ڵڶ�������
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���x>y�򷵻�true�����򷵻�false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x > y;
        }
    };

    //---------------------------------------------------------------------------
    ///���ڵ��ڷº���ģ����
    template<class T>
    class XFunctions_GreaterEqual : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚϵ�һ�������Ƿ���ڵ��ڵڶ�������
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���x>=y�򷵻�true�����򷵻�false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x >= y;
        }
    };

    //---------------------------------------------------------------------------
    ///С�ڷº���ģ����
    template<class T>
    class XFunctions_Less : public XFunctions_Binary<T,T,bool> 
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚϵ�һ�������Ƿ�С�ڵڶ�������
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���x<y�򷵻�true�����򷵻�false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x < y;   
        }
    };

    //---------------------------------------------------------------------------
    ///С�ڵ��ڷº���ģ����
    template<class T>
    class XFunctions_LessEqual : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚϵ�һ�������Ƿ�С�ڵ��ڵڶ�������
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���x<=y�򷵻�true�����򷵻�false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x <= y;
        }
    };

    //---------------------------------------------------------------------------
    ///�ȽϷº���ģ����
    template<class T>
    class XFunctions_Compare : public XFunctions_Binary<T,T,XInt>
    {
    public:
        typedef XFunctions_Binary<T,T,XInt> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚ���������
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���رȽϽ��
         *    - 1 ��ʾx > y
         *    - 0 ��ʾx == y
         *    - -1 ��ʾ x < y
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            ResultType rRet;
            if( x > y ) rRet = 1;
            else if( x < y ) rRet = -1;
            else rRet = 0;
            return rRet;
        }
    };

    //����һ���ϵ������ķº���
    //---------------------------------------------------------------------------
    ///���ڷº���ģ����
    template<class T>
    class XFunctions_PointerEqual : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚ����������Ƿ����
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���x==y�򷵻�true�����򷵻�false
         */
        ResultType operator()(const Arg1Type * x,const Arg2Type * y) const
        {
            return *x == *y;
        }
    };

    //---------------------------------------------------------------------------
    ///�ȽϷº���ģ����
    template<class T>
    class XFunctions_PointerCompare : public XFunctions_Binary<T,T,XInt>
    {
    public:
        typedef XFunctions_Binary<T,T,XInt> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚ���������
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���رȽϽ��
         *    - 1 ��ʾx > y
         *    - 0 ��ʾx == y
         *    - -1 ��ʾ x < y
         */
        ResultType operator()(const Arg1Type * x,const Arg2Type * y) const
        {
            ResultType rRet;
            if( *x > *y ) rRet = 1;
            else if( *x < *y ) rRet = -1;
            else rRet = 0;
            return rRet;
        }
    };

    //---------------------------------------------------------------------------
    ///С�ڷº���ģ����
    template<class T>
    class XFunctions_PointerLess : public XFunctions_Binary<T,T,bool> 
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚϵ�һ�������Ƿ�С�ڵڶ�������
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���x<y�򷵻�true�����򷵻�false
         */
        ResultType operator()(const Arg1Type * x,const Arg2Type * y) const
        {
            return *x < *y; 
        }
    };

    //---------------------------------------------------------------------------
    ///���ڷº���ģ����
    template<class T>
    class XFunctions_PointerGreater : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///����()��������Ƚϵ�һ�������Ƿ���ڵڶ�������
        /**
         * @param x ��һ������
         * @param y �ڶ�������
         * @return ���x>y�򷵻�true�����򷵻�false
         */
        ResultType operator()(const Arg1Type * x,const Arg2Type * y) const
        {
            return *x > *y;
        }
    };
}
#endif
