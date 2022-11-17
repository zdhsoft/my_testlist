//---------------------------------------------------------------------------

#ifndef typedefH
#define typedefH
//---------------------------------------------------------------------------
namespace zdh {
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

}
#endif
