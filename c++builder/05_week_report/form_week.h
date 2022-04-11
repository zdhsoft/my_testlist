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
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
	TStrings * m_MemberList;
private:
	void __fastcall Check(TStrings * paramHas, TStrings * paramNotHas);
    bool __fastcall isInList(TStrings * paramSrcList, const String & paramDest);
public:		// User declarations
	__fastcall TfrmWeek(TComponent* Owner);
    void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWeek *frmWeek;
//---------------------------------------------------------------------------
#endif
