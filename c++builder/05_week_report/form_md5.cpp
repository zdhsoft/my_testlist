//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_md5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "md5.h"
#include "utils.h"

TfrmMD5 *frmMD5;
//---------------------------------------------------------------------------
__fastcall TfrmMD5::TfrmMD5(TComponent* Owner)
	: XFunctionFunForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMD5::SaveChange()
{
	//
}

//void __fastcall TfrmMD5::WMDropFiles (TWMDropFiles &message)
//{
//    Memo1->Lines->Add("WMDropFiles");
//	 UINT FileCount = DragQueryFile((HDROP) message.Drop, 0xFFFFFFFF, NULL,
//	 0);
//	 AnsiString FileName;
//	 AnsiString FileExtension;
//
//	 int FileLength;
//	 for(UINT ii=0; ii < FileCount; ii++)
//	 {
//		 FileName.SetLength(MAX_PATH);
//		 FileLength = DragQueryFileA((HDROP)message.Drop, ii, FileName.c_str(), FileName.Length());
//		 FileName.SetLength(FileLength);
//         Memo1->Lines->Add(FileName);
//	 //ProcessFile(FileLength) // <------ Whatever you want it to be...
//	 } // end for
//	 DragFinish((HDROP) message.Drop);
//}
void __fastcall TfrmMD5::Init() {
}
void __fastcall TfrmMD5::Edit1Change(TObject *Sender)
{
	Memo1->Lines->Clear();
	System::UTF8String utf8(Edit1->Text);
	zdh::XMD5 stMD5;
	stMD5.Init();
	stMD5.Update(utf8.c_str(), utf8.Length());
	stMD5.Finish();
//	Memo1->Lines->Add(utf8);
//	Memo1->Lines->Add(utf8.Length());
	Memo1->Lines->Add(stMD5.GetMD5String(cbCaption->Checked));
//	UnicodeString str = L"天下无难事，只怕有心人";
//	utf8 = str;
//	stMD5.Init();
//	Memo1->Lines->Add(utf8);
//    Memo1->Lines->Add(utf8.Length());
//	stMD5.Update(utf8.c_str(), utf8.Length());
//	stMD5.Finish();
//	Memo1->Lines->Add(stMD5.GetMD5String(true));
}
//---------------------------------------------------------------------------







