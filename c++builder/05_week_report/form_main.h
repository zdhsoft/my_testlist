//---------------------------------------------------------------------------

#ifndef form_mainH
#define form_mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <XFunctionFunForm.h>
#include <vector>
using namespace std;
typedef vector<TForm *> TSubFormList;
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TActionList *ActionList1;
	TMenuItem *F1;
	TMenuItem *H1;
	TStatusBar *StatusBar1;
	TToolBar *ToolBar1;
	TImageList *ImageList1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TPanel *PanelContainer;
	TAction *ActionWeek;
	TAction *ActionDateTime;
	TAction *Action3;
	TTimer *Timer1;
	void __fastcall ActionWeekExecute(TObject *Sender);
	void __fastcall ActionDateTimeExecute(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
    TSubFormList m_SubFormList;
	XFunctionFunForm * m_CurrActiveForm;
private:
	void __fastcall ShowLocalForm(XFunctionFunForm * paramForm,TAction * paramAction);
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
