///����ѡ��궨��
/**
 * ����ļ��ṩ����ѡ�Ӧ�������еĹ���
 *
 * zdhsoft 2011-2013 ��Ȩ����
 *
 * @file xconfig.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-07
 * company zdhsoft
 */
/**********************************************************************
    �����б�  //��Ҫ��������
    1���ṩ����꿪�غ�Ĭ�ϵ����ƿռ䶨��
	2����ʼ֧��vc2010��gcc 4.3, C++Builder 2010���ϰ汾���ϰ汾����֧�֣���Ҫ��������C++0x11�����ݣ�

    ��ʷ:       //��Ҫ�޸ļ�¼
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-07  1.0             ������ʼ�ļ�
    zdhsoft     2012-03-22  1.1             ���Ӷ�Borland C++ Builder��֧��
	zdhsoft		2013-11-26  1.2				��ʼ����֧��c++0x11����
***********************************************************************/
#ifndef _X_CONFIG_H_
#define _X_CONFIG_H_

#if defined(_MSC_VER) || defined(__MINGW__) || defined(__BORLANDC__)
    #define OS_WINDOWS   ///<windows����ϵͳ
#if defined(__x86_64__) || defined(WIN64) || defined(AMD64) || defined(_WIN64)
    #define CPU_64   ///<64λ���뻷��
#else
    #define CPU_32   ///<32λ���뻷��
#endif


#else
    #define OS_LINUX     ///<linux����ϵͳ
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
    namespace detail ///���ṩ����ʵ�ֵ�ϸ�ڵ����ƿռ�,ʹ�����벻Ҫֱ���Ǹÿռ�ĺ���
    {
    }
}

//���ڵ��Ե�ʱ�����ӵģ�����ʽ������ʱ��Ҫȥ��
#if !defined(_DEBUG)
    #define _DEBUG
#endif

#define ZDH_THROW(x)  //��ʾ���׳����쳣 ��û��ʵ�ʵĴ���
//��VC����ʹ�ñ�׼C��assert����ֳ���
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
