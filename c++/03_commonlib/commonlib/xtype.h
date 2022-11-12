///�����������Ͷ���
/**
 * �����������Ͷ��壬��������64λ������32λ����һ�µ���������
 *
 * zdhsoft 2011 ��Ȩ����
 *
 * @file xtype.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-07
 * company zdhsoft
 */
/**********************************************************************
    �����б�  //��Ҫ��������
    1�������������Ͷ���

    ��ʷ:       //��Ҫ�޸ļ�¼
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-07  1.0             ������ʼ�ļ�
***********************************************************************/

#ifndef _X_TYPE_H_
#define _X_TYPE_H_
#include <xconfig.h>
#include <cstdio>

#ifdef CONFIG_BCB
	using std::printf;
#endif

//����NULL�����δ���壬�������ﶨ��
#ifndef NULL
    #ifdef  __cplusplus
        #define NULL    0
    #else
        #define NULL    ((void *)0)
    #endif
#endif
namespace zdh
{
    //�����������Ͷ���
    typedef unsigned char           XByte;          ///<�ֽ�����
    typedef char                    XChar;          ///<�ַ�����
    typedef unsigned short          XWord;          ///<������
    typedef signed short            XShort;         ///<������
    typedef wchar_t                 XWideChar;      ///<���ַ�����

    typedef unsigned int            XDWord;         ///<32λ�޷�������
    typedef          int            XInt;           ///<32λ�з�������
    typedef unsigned long long      XDDWord;        ///<64λ�޷�������
    typedef signed   long long      XLong;          ///<64λ�з�������
    typedef bool                    XBool;          ///<��������
    typedef float                   XFloat;         ///<�����ȸ�����
    typedef double                  XDouble;        ///<˫���ȸ�����

	typedef XByte					XUInt8;          ///<�ֽ�����
	typedef XChar                   XInt8;           ///<�ַ�����
	typedef XWord                   XUInt16;         ///<������
	typedef XShort                  XInt16;          ///<������

	typedef XDWord					XUInt32;         ///<32λ�޷�������
	typedef XInt					XInt32;          ///<32λ�з�������
	typedef XDDWord					XUInt64;         ///<64λ�޷�������
	typedef XLong					XInt64;          ///<64λ�з�������	
	//ָ�����Ͷ���
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
        ERR_OK		=  0,		///<�������ʾ�ɹ�
        ERR_FAIL	= -1,		///<�������ʾʧ��
		XTRUE		=  1,		///<����������Ϊbool���͵�ʱ��
		XFALSE		=  0,       ///<����������Ϊbool���͵�ʱ��
    };

    //-----------------------------------------------------------------------------------------------------
    ///�жϴ������ǲ���OK
    inline bool isOK(XInt param_error_code)
    {
        return param_error_code == ERR_OK;
    }

    //-----------------------------------------------------------------------------------------------------
    ///�жϴ������ǲ���ʧ��
	inline bool isNotOK(XInt param_error_code)
    {
		return param_error_code != ERR_OK;
    }
    
    //-----------------------------------------------------------------------------------------------------
    ///�ж�ָ��ֵ�Ƿ�Ϊ��
    template<class T>
    inline bool isNULL(const T * param_pointer)
    {
        return param_pointer == NULL;
    }
    
    //-----------------------------------------------------------------------------------------------------
    ///�ж�ָ��ֵ�Ƿ�Ϊ��
    template<class T>
	inline bool isNotNULL(const T * param_pointer)
    {
		return param_pointer != NULL;
    }
    
    //-----------------------------------------------------------------------------------------------------
    ///�ͷ�һ������
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
    ///��Release�����ͷŶ���
    template<class T>
	inline void ReleaseObject(T * & param_pointer)
    {
		if (isNotNULL(param_pointer))
        {
			param_pointer->Release();
			param_pointer = NULL;
        }
    }
    //����δʹ�õĲ���

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
