﻿//---------------------------------------------------------------------------

#ifndef form_md5H
#define form_md5H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <XFunctionFunForm.h>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>

//---------------------------------------------------------------------------
class TfrmMD5 : public XFunctionFunForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TLabel *Label3;
	TPanel *Panel1;
	TPanel *Panel2;
	TCheckBox *cbCaption;
	TMemo *Memo1;
	TProgressBar *ProgressBar1;
	TLabel *Label4;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
	void CalcFileMD5(const int paramIndex, const int paramFileCount, const String & paramFileName);
	void log(const wchar_t * format, ...);
    void clearLog();
public:		// User declarations
	__fastcall TfrmMD5(TComponent* Owner);
	void __fastcall SaveChange();
	void __fastcall Init();
	virtual void __fastcall DropFileList(TStrings * paramDropFileList);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMD5 *frmMD5;
//---------------------------------------------------------------------------
#endif
