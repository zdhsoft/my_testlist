///编译选项宏定义
/**
 * 这个文件提供编译选项，应用于所有的工程
 *
 * zdhsoft 2011-2013 版权所有
 *
 * @file xconfig.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-07
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、提供编译宏开关和默认的名称空间定义
	2、开始支持vc2010，gcc 4.3, C++Builder 2010以上版本，老版本将不支持（主要是引用了C++0x11的内容）

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-07  1.0             创建初始文件
    zdhsoft     2012-03-22  1.1             增加对Borland C++ Builder的支持
	zdhsoft		2013-11-26  1.2				开始部分支持c++0x11功能
***********************************************************************/
#ifndef _X_CONFIG_H_
#define _X_CONFIG_H_

#if defined(_MSC_VER) || defined(__MINGW__) || defined(__BORLANDC__)
    #define OS_WINDOWS   ///<windows操作系统
#if defined(__x86_64__) || defined(WIN64) || defined(AMD64) || defined(_WIN64)
    #define CPU_64   ///<64位编译环境
#else
    #define CPU_32   ///<32位编译环境
#endif


#else
    #define OS_LINUX     ///<linux操作系统
#endif

#ifdef _MSC_VER 
	#pragma warning (disable: 4996)
	#pragma warning (disable: 4127)
    #define CONFIG_VC
	#if _MSC_VER < 1600
		#error VC2010 previous version is not supported
	#endif
#endif

#ifdef __GNUC__
	//__GNUC__
	//	__GNUC_MINOR__
	//	__GNUC_PATCHLEVEL__
    #define CONFIG_GCC
	#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 3)
		#error GCC 4.3 previous version is not supported
	#endif
#endif

#ifdef __BORLANDC__
    #define CONFIG_BCB
	#if __BORLANDC__ < 0x0610
		#error C++Builder 2009 previous version is not supported
	#endif
#endif

namespace zdh 
{
    namespace detail ///不提供对外实现的细节的名称空间,使用者请不要直接是该空间的函数
    {
    }
}

//用于调试的时候增加的，在正式发布的时候要去掉
#if !defined(_DEBUG)
    #define _DEBUG
#endif

#define ZDH_THROW(x)  //提示会抛出的异常 但没有实际的代码
//在VC下面使用标准C的assert会出现程序
#if defined(_DEBUG)
    #if defined(_MSC_VER) 
        #include <crtdbg.h>
        #define ZDH_ASSERT(x) _ASSERT(x)  
    #else
        #include <cassert>
        #define ZDH_ASSERT(x) assert(x)
    #endif
#else
    #define ZDH_ASSERT(x)
#endif

#if defined(MULT_THREAD)
    #define CONFIG_MULT_THREAD 1
#else
    #define CONFIG_MULT_THREAD 0
#endif
#endif
