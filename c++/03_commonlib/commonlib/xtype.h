///基本数据类型定义
/**
 * 基本数据类型定义，定义了在64位环境和32位环境一致的数据类型
 *
 * zdhsoft 2011 版权所有
 *
 * @file xtype.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-07
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、基本数据类型定义

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-07  1.0             创建初始文件
***********************************************************************/

#ifndef _X_TYPE_H_
#define _X_TYPE_H_
#include <xconfig.h>
#include <cstdio>

#ifdef CONFIG_BCB
	using std::printf;
#endif

//定义NULL，如果未定义，则在这里定义
#ifndef NULL
    #ifdef  __cplusplus
        #define NULL    0
    #else
        #define NULL    ((void *)0)
    #endif
#endif
namespace zdh
{
    //基本数据类型定义
    typedef unsigned char           XByte;          ///<字节类型
    typedef char                    XChar;          ///<字符类型
    typedef unsigned short          XWord;          ///<字类型
    typedef signed short            XShort;         ///<短整数
    typedef wchar_t                 XWideChar;      ///<宽字符类型

    typedef unsigned int            XDWord;         ///<32位无符号整数
    typedef          int            XInt;           ///<32位有符号整数
    typedef unsigned long long      XDDWord;        ///<64位无符号整数
    typedef signed   long long      XLong;          ///<64位有符号整数
    typedef bool                    XBool;          ///<布尔类型
    typedef float                   XFloat;         ///<单精度浮点数
    typedef double                  XDouble;        ///<双精度浮点数

	typedef XByte					XUInt8;          ///<字节类型
	typedef XChar                   XInt8;           ///<字符类型
	typedef XWord                   XUInt16;         ///<字类型
	typedef XShort                  XInt16;          ///<短整数

	typedef XDWord					XUInt32;         ///<32位无符号整数
	typedef XInt					XInt32;          ///<32位有符号整数
	typedef XDDWord					XUInt64;         ///<64位无符号整数
	typedef XLong					XInt64;          ///<64位有符号整数	
	//指针类型定义
    typedef void *      Pointer;
    typedef XByte *     PByte;
    typedef XChar *     PChar;
    typedef XWord *     PWord;
    typedef XShort *    PShort;
    typedef XInt *      PInt;
    typedef XDWord *    PDWord;
    typedef XLong *     PLong;
    typedef XDDWord *   PDDWord;
    typedef XWideChar * PWideChar;
    typedef XBool *     PBool;
    typedef XFloat *    PFloat;
    typedef XDouble *   PDouble;

    enum
    {
        ERR_OK		=  0,		///<错误码表示成功
        ERR_FAIL	= -1,		///<错误码表示失败
		XTRUE		=  1,		///<用于整数做为bool类型的时候
		XFALSE		=  0,       ///<用于整数做为bool类型的时候
    };

    //-----------------------------------------------------------------------------------------------------
    ///判断错误码是不是OK
    inline bool isOK(XInt param_error_code)
    {
        return param_error_code == ERR_OK;
    }

    //-----------------------------------------------------------------------------------------------------
    ///判断错误码是不是失败
	inline bool isNotOK(XInt param_error_code)
    {
		return param_error_code != ERR_OK;
    }
    
    //-----------------------------------------------------------------------------------------------------
    ///判断指针值是否为空
    template<class T>
    inline bool isNULL(const T * param_pointer)
    {
        return param_pointer == NULL;
    }
    
    //-----------------------------------------------------------------------------------------------------
    ///判断指针值是否不为空
    template<class T>
	inline bool isNotNULL(const T * param_pointer)
    {
		return param_pointer != NULL;
    }
    
    //-----------------------------------------------------------------------------------------------------
    ///释放一个对象
    template<class T>
	inline void FreeObject(T * & param_pointer)
    {
		if (isNotNULL(param_pointer))
        {
			delete param_pointer;
			param_pointer = NULL;
        }
    }

    //-----------------------------------------------------------------------------------------------------
    ///用Release方法释放对象
    template<class T>
	inline void ReleaseObject(T * & param_pointer)
    {
		if (isNotNULL(param_pointer))
        {
			param_pointer->Release();
			param_pointer = NULL;
        }
    }
    //定义未使用的参数

#ifdef _DEBUG
    template<class T>
    inline void PrintTypeSize(const char * paramTypeName)
    {
        printf("  %s size is %d\n", paramTypeName, static_cast<XInt>(sizeof(T)));
    }
    inline void PrintSizeOf()
    {
        printf("print type size:\n");
        PrintTypeSize<XByte>("XByte");
        PrintTypeSize<XChar>("XChar");
        PrintTypeSize<XWord>("XWord");
        PrintTypeSize<XShort>("XShort");
        PrintTypeSize<XWideChar>("XWideChar");
        PrintTypeSize<XDWord>("XDWord");
        PrintTypeSize<XInt>("XInt");
        PrintTypeSize<XDDWord>("XDDWord");
        PrintTypeSize<XLong>("XLong");
        PrintTypeSize<XBool>("XBool");
        PrintTypeSize<XFloat>("XFloat");
        PrintTypeSize<XDouble>("XDouble");

        PrintTypeSize<Pointer>("Pointer");
        PrintTypeSize<PByte>("PByte");
        PrintTypeSize<PChar>("PChar");
        PrintTypeSize<PWord>("PWord");
        PrintTypeSize<PShort>("PShort");
        PrintTypeSize<PInt>("PInt");
        PrintTypeSize<PDWord>("PDWord");
        PrintTypeSize<PLong>("PLong");
        PrintTypeSize<PDDWord>("PDDWord");
        PrintTypeSize<PWideChar>("PWideChar");
        PrintTypeSize<PBool>("PBool");
        PrintTypeSize<PFloat>("PFloat");
        PrintTypeSize<PDouble>("PDouble");
    }
#endif
}

#endif
