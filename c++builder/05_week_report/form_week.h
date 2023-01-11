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
#include <Vcl.ComCtrls.hpp>
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
	TSplitter *Splitter1;
	TPanel *Panel3;
	TSplitter *Splitter2;
	TPanel *Panel4;
	TButton *Button2;
	TLabel *Label2;
	TListBox *ListBoxCurr;
	TPanel *Panel5;
	TPanel *Panel6;
	TSplitter *Splitter3;
	TPanel *Panel7;
	TPanel *Panel8;
	TLabel *Label3;
	TLabel *Label4;
	TListBox *ListBoxNot;
	TListBox *ListBoxGood;
	TButton *Button3;
	TButton *Button4;
	TDateTimePicker *DateTimePicker1;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall DateTimePicker1Change(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
private:	// User declarations
	TStrings * m_MemberList;
private:
	void __fastcall Check(TStrings * paramHas, TStrings * paramNotHas);
	bool __fastcall isInList(TStrings * paramSrcList, const String & paramDest);
    void __fastcall updateChange(bool paramPrompt = true);
public:		// User declarations
	__fastcall TfrmWeek(TComponent* Owner);
    void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWeek *frmWeek;
//---------------------------------------------------------------------------
#endif
