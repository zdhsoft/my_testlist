//---------------------------------------------------------------------------

#ifndef typedefH
#define typedefH
//---------------------------------------------------------------------------
namespace zdh {
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

}
#endif
