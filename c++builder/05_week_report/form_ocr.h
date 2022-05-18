//---------------------------------------------------------------------------

#ifndef form_ocrH
#define form_ocrH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <XFunctionFunForm.h>

//---------------------------------------------------------------------------
class TfrmOCR : public XFunctionFunForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmOCR(TComponent* Owner);
	void __fastcall SaveChange();
   	void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOCR *frmOCR;
//---------------------------------------------------------------------------
#endif
