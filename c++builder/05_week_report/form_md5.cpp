//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_md5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "md5.h"
#include "utils.h"
#include <iostream>
#include <fstream>

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
	const String stMD5String(stMD5.GetMD5String(cbCaption->Checked));
//	Memo1->Lines->Add(utf8);
//	Memo1->Lines->Add(utf8.Length());
	log(L"%s",Edit1->Text.c_str());
	log(L"MD5:%s", stMD5String.c_str());
	// Memo1->Lines->Add(stMD5.GetMD5String(cbCaption->Checked));
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

void TfrmMD5::CalcFileMD5(const int paramIndex, const int paramFileCount, const String & paramFileName) {
    log(L"%s",paramFileName.c_str());
	zdh::XMD5 stMD5;
	stMD5.Init();
	zdh::XChar buff[4096];
	std::ifstream inFile(paramFileName.c_str(), std::ifstream::binary);
	if (!inFile) {
		std::cout << "error" << std::endl;
		log(L"Error:", L"打开文件失败!");
        log(L"");
		return;
	}
	while (inFile.read(buff, 4096)) { //一直读到文件结束
		auto readedBytes = (int)inFile.gcount(); //看刚才读了多少字节
		stMD5.Update(buff, readedBytes);
	}
	stMD5.Finish();
	inFile.close();
	String str(stMD5.GetMD5String(cbCaption->Checked));

	log(L"MD5:%s", str.c_str());
    log(L"");
}
void TfrmMD5::clearLog() {
    Memo1->Lines->Clear();
}
void TfrmMD5::log(const wchar_t * format, ...) {
	String s;
	va_list paramList;
	va_start(paramList, format);
	s.vprintf(format, paramList);
	va_end(paramList);
    Memo1->Lines->Add(s);
	// OutputDebugStringW(s.c_str());
}

void __fastcall TfrmMD5::DropFileList(TStrings * paramDropFileList) {
	if (paramDropFileList->Count > 0) {
		Memo1->Lines->Clear();
		for(int i = 0; i < paramDropFileList->Count; i++) {
			auto fileName = paramDropFileList->Strings[i];
			if(FileExists(fileName)) {
				CalcFileMD5(i, paramDropFileList->Count, fileName);
			} else if(DirectoryExists(fileName)) {
				log(L"%s 是一个目录!", fileName.c_str());
			} else {
                log(L"%s 不是一个文件", fileName.c_str());
			}
		}
    }
}





