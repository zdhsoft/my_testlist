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

//void calcMD5(const char * paramFileName) {
//	zdh::XMD5 stMD5;
//	stMD5.Init();
//	zdh::XChar buff[4096];
//	zdh::XChar md5sum[33];
//	std::ifstream inFile(paramFileName, std::ifstream::binary);
//	if (!inFile) {
//		std::cout << "error" << std::endl;
//		return;
//	}
//	while (inFile.read(buff, 4096)) { //一直读到文件结束
//		auto readedBytes = (int)inFile.gcount(); //看刚才读了多少字节
//		stMD5.Update(buff, readedBytes);
//	}
//	stMD5.Finish();
//	inFile.close();
//	std::cout << stMD5.GetMD5String(md5sum, false) << std::endl;
//}

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

