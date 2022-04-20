//---------------------------------------------------------------------------

#ifndef form_datetimeH
#define form_datetimeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <XFunctionFunForm.h>
//---------------------------------------------------------------------------
class TfrmDateTime : public XFunctionFunForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmDateTime(TComponent* Owner);
	void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDateTime *frmDateTime;
//---------------------------------------------------------------------------
#endif
