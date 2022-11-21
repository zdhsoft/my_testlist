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
#include <Vcl.AppEvnts.hpp>
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
	TAction *ActionOCR;
	TTimer *Timer1;
	TTrayIcon *TrayIcon1;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TApplicationEvents *ApplicationEvents1;
	TMenuItem *Action31;
	TMenuItem *D1;
	TAction *ActionAbout;
	TMenuItem *N2;
	TAction *ActionMD5;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TAction *ActionExit;
	TMenuItem *X1;
	TMenuItem *N3;
	TMenuItem *X2;
	TAction *ActionJSON;
	TToolButton *ToolButton6;
	void __fastcall ActionWeekExecute(TObject *Sender);
	void __fastcall ActionDateTimeExecute(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ApplicationEvents1Minimize(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall ActionAboutExecute(TObject *Sender);
	void __fastcall ActionOCRExecute(TObject *Sender);
	void __fastcall ActionMD5Execute(TObject *Sender);
	void __fastcall ActionExitExecute(TObject *Sender);
	void __fastcall ActionJSONExecute(TObject *Sender);
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
