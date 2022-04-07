//---------------------------------------------------------------------------

#ifndef form_weekH
#define form_weekH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <XFunctionFunForm.h>
//---------------------------------------------------------------------------
class TfrmWeek : public XFunctionFunForm
{
__published:	// IDE-managed Components
	TButton *Button1;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmWeek(TComponent* Owner);
    void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWeek *frmWeek;
//---------------------------------------------------------------------------
#endif
