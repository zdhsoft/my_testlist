//---------------------------------------------------------------------------

#ifndef form_jsonH
#define form_jsonH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.StdActns.hpp>
#include <XFunctionFunForm.h>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TfrmJSON : public XFunctionFunForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TMemo *Memo1;
	TMemo *Memo2;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TOpenTextFileDialog *OpenTextFileDialog1;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmJSON(TComponent* Owner);
	void __fastcall SaveChange();
	void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmJSON *frmJSON;
//---------------------------------------------------------------------------
#endif
