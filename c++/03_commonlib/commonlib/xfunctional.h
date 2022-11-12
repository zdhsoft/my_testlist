///仿函数模板
/**
 * 仿函数模板
 * 这里提供了一组仿函数模板。
 * zdhsoft 2011 版权所有
 *
 * @file xfunctional.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-13
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、一组仿函数模板

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-13  1.0             创建初始文件
***********************************************************************/
#ifndef _X_FUNCTIONAL_H_
#define _X_FUNCTIONAL_H_
namespace zdh
{
    //---------------------------------------------------------------------------
    ///一元仿函数的基类模板类
    /**
     * 一元仿函数的基类模板类
     */
    template<class Arg,class Result>
    class XFunctions_One
    {
    public:
        ///一元参数类型定义
        typedef Arg ArgType;
        ///返回结果类型定义
        typedef Result ResultType;
    };

    //---------------------------------------------------------------------------
    ///二元仿函数的基类模板类
    template<class Arg1,class Arg2,class Result>
    class XFunctions_Binary
    {
    public:
        ///参数一类型定义
        typedef Arg1 Arg1Type;
        ///参数二类型定义
        typedef Arg2 Arg2Type;
        ///返回结果类型定义
        typedef Result ResultType;
    };

    //下面一组关系运算类的仿函数
    //---------------------------------------------------------------------------
    ///等于仿函数模板类
    template<class T>
    class XFunctions_Equal : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较两个参数是否相等
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 如果x==y则返回true，否则返回false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x == y;
        }
    };

    //---------------------------------------------------------------------------
    ///不等于仿函数模板类
    template<class T>
    class XFunctions_NotEqual : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较两个参数是否不相等
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 如果x!=y则返回true，否则返回false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x != y;
        }
    };

    //---------------------------------------------------------------------------
    ///大于仿函数模板类
    template<class T>
    class XFunctions_Greater : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较第一个参数是否大于第二个参数
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 如果x>y则返回true，否则返回false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x > y;
        }
    };

    //---------------------------------------------------------------------------
    ///大于等于仿函数模板类
    template<class T>
    class XFunctions_GreaterEqual : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较第一个参数是否大于等于第二个参数
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 如果x>=y则返回true，否则返回false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x >= y;
        }
    };

    //---------------------------------------------------------------------------
    ///小于仿函数模板类
    template<class T>
    class XFunctions_Less : public XFunctions_Binary<T,T,bool> 
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较第一个参数是否小于第二个参数
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 如果x<y则返回true，否则返回false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x < y;   
        }
    };

    //---------------------------------------------------------------------------
    ///小于等于仿函数模板类
    template<class T>
    class XFunctions_LessEqual : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较第一个参数是否小于等于第二个参数
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 如果x<=y则返回true，否则返回false
         */
        ResultType operator()(const Arg1Type & x,const Arg2Type & y) const
        {
            return x <= y;
        }
    };

    //---------------------------------------------------------------------------
    ///比较仿函数模板类
    template<class T>
    class XFunctions_Compare : public XFunctions_Binary<T,T,XInt>
    {
    public:
        typedef XFunctions_Binary<T,T,XInt> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较两个参数
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 返回比较结果
         *    - 1 表示x > y
         *    - 0 表示x == y
         *    - -1 表示 x < y
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

    //下面一组关系运算类的仿函数
    //---------------------------------------------------------------------------
    ///等于仿函数模板类
    template<class T>
    class XFunctions_PointerEqual : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较两个参数是否相等
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 如果x==y则返回true，否则返回false
         */
        ResultType operator()(const Arg1Type * x,const Arg2Type * y) const
        {
            return *x == *y;
        }
    };

    //---------------------------------------------------------------------------
    ///比较仿函数模板类
    template<class T>
    class XFunctions_PointerCompare : public XFunctions_Binary<T,T,XInt>
    {
    public:
        typedef XFunctions_Binary<T,T,XInt> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较两个参数
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 返回比较结果
         *    - 1 表示x > y
         *    - 0 表示x == y
         *    - -1 表示 x < y
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
    ///小于仿函数模板类
    template<class T>
    class XFunctions_PointerLess : public XFunctions_Binary<T,T,bool> 
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较第一个参数是否小于第二个参数
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 如果x<y则返回true，否则返回false
         */
        ResultType operator()(const Arg1Type * x,const Arg2Type * y) const
        {
            return *x < *y; 
        }
    };

    //---------------------------------------------------------------------------
    ///大于仿函数模板类
    template<class T>
    class XFunctions_PointerGreater : public XFunctions_Binary<T,T,bool>
    {
    public:
        typedef XFunctions_Binary<T,T,bool> Inherited;
        typedef typename Inherited::ResultType ResultType;
        typedef typename Inherited::Arg1Type Arg1Type;
        typedef typename Inherited::Arg2Type Arg2Type;
        ///重载()运算符，比较第一个参数是否大于第二个参数
        /**
         * @param x 第一个参数
         * @param y 第二个参数
         * @return 如果x>y则返回true，否则返回false
         */
        ResultType operator()(const Arg1Type * x,const Arg2Type * y) const
        {
            return *x > *y;
        }
    };
}
#endif
