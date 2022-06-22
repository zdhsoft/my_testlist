//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	TStringList * s = new TStringList();
	NetHTTPRequest1->Post("http://127.0.0.1:30001", s)->ContentAsString;
	delete s;
}
//---------------------------------------------------------------------------
