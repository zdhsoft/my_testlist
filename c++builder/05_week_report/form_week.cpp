//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_week.h"
//#include <Vcl.FileCtrl.hpp>
#include "FileCtrl.hpp"
#include <dirent.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmWeek *frmWeek;
//---------------------------------------------------------------------------
__fastcall TfrmWeek::TfrmWeek(TComponent* Owner)
	: XFunctionFunForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmWeek::Init() {
	//
}
void __fastcall TfrmWeek::Button1Click(TObject *Sender)
{
	FileOpenDialog1->DefaultFolder = Edit1->Text;
	if(FileOpenDialog1->Execute()) {
		Edit1->Text = FileOpenDialog1->FileName;
		wDIR* d = wopendir(Edit1->Text.c_str());
		if(d != nullptr) {
            ListBox1->Items->Clear();
			struct wdirent* entry;
			String p(".");
			String pp("..");
			while ( (entry=wreaddir(d)) != NULL)
			{
				String s(entry->d_name);
				if (s == p || s == pp) {
                    continue;
                }
				ListBox1->Items->Add(s);
			}
		}
	}
}
//---------------------------------------------------------------------------

