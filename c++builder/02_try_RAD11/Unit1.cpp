//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1* Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject* Sender)
{
    ShowMessage("Hello C++ Builder 11");
    this->Caption = "hello";
    this->Button1->Caption = "hello button";
    this->Button1->Caption = "aaa";
    this->Caption = "aaaaaaaaaaaaaaaaaaa";
    this->Edit1->Enabled = true;
    this->CheckBox1->Checked = true;
    this->Edit1->Text = "aaaaaaaaaaaaaaaaaaaaaaaaaaa";
}
//---------------------------------------------------------------------------

