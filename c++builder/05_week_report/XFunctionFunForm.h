//---------------------------------------------------------------------------

#ifndef XFunctionFunFormH
#define XFunctionFunFormH
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class XFunctionFunForm : public TForm
{
public:
	__fastcall XFunctionFunForm(TComponent* Owner);
	virtual void __fastcall SaveChange();
    virtual void __fastcall DropFileList(TStrings * paramDropFileList);
};
#endif
