//---------------------------------------------------------------------------

#ifndef mainFormH
#define mainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtActns.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.ToolWin.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TMainMenu *MainMenu1;
	TActionList *ActionList1;
	TAction *Action1;
	TAction *Action2;
	TAction *Action3;
	TMenuItem *Action11;
	TMenuItem *Action21;
	TMenuItem *Action31;
	TRichEditBold *FormatRichEditBold1;
	TMenuItem *Bold1;
	TPanel *Panel1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TImageList *ImageList1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Action1Execute(TObject *Sender);
	void __fastcall Action2Execute(TObject *Sender);
	void __fastcall Action3Execute(TObject *Sender);
private:	// User declarations
	void __fastcall HandleDropFiles(TMessage &msg);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_DROPFILES,TMessage,HandleDropFiles)
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
