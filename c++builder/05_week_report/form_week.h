//---------------------------------------------------------------------------

#ifndef form_weekH
#define form_weekH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <XFunctionFunForm.h>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmWeek : public XFunctionFunForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Button1;
	TFileOpenDialog *FileOpenDialog1;
	TPanel *Panel1;
	TPanel *Panel2;
	TListBox *ListBox1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmWeek(TComponent* Owner);
    void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWeek *frmWeek;
//---------------------------------------------------------------------------
#endif
