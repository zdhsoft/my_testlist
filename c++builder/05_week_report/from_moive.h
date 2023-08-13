//---------------------------------------------------------------------------

#ifndef from_moiveH
#define from_moiveH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <XFunctionFunForm.h>
//---------------------------------------------------------------------------
class TfrmMoive : public XFunctionFunForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TfrmMoive(TComponent* Owner);
	void __fastcall SaveChange();
	void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMoive *frmMoive;
//---------------------------------------------------------------------------
#endif
