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
#include <filesystem>

namespace fs = std::filesystem;
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
	// Memo1->Lines->Clear();
	System::UTF8String utf8(Edit1->Text);
	zdh::XMD5 stMD5;
	stMD5.Init();
	stMD5.Update(utf8.c_str(), utf8.Length());
	stMD5.Finish();
	const String stMD5String(stMD5.GetMD5String(cbCaption->Checked));
//	Memo1->Lines->Add(utf8);
//	Memo1->Lines->Add(utf8.Length());
	log(L"MD5:%s", stMD5String.c_str());
	log(L"%s",Edit1->Text.c_str());

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

	fs::path filePath = paramFileName.c_str();
	if(!fs::exists(filePath)) {
		log(L"");
		log(L"Error:", L"文件不存在");
		log(L"%s",paramFileName.c_str());
		return;
	}
	zdh::XLong fileSize = fs::file_size(filePath);
	if (fileSize <= 0) {
		fileSize = 1;
	}
	Label4->Caption = paramFileName + L" => " + zdh::utils::formatMemory(fileSize);

	zdh::XMD5 stMD5;
	stMD5.Init();
	zdh::XChar buff[4096];
	std::ifstream inFile(paramFileName.c_str(), std::ifstream::binary);
	auto v = Now();
	auto t = std::time(0);
	if (!inFile) {
		//std::cout << "error" << std::endl;
		log(L"");
		log(L"Error:", L"打开文件失败!");
		log(L"%s %lld",paramFileName.c_str(), fileSize);
		return;
	}
	zdh::XLong allReadBytes = 0;
	zdh::XLong processPos = 0;
	ProgressBar1->Position = processPos;
    Application->ProcessMessages();
	while (inFile.read(buff, 4096)) { //一直读到文件结束
		auto readedBytes = (int)inFile.gcount(); //看刚才读了多少字节
		stMD5.Update(buff, readedBytes);
        bool pushMsg = false;
		auto k = std::time(0);
		if(k != t) {
			t = k;
			pushMsg = true;
			// Application->ProcessMessages();
		}
		allReadBytes += readedBytes;
		zdh::XLong newP = allReadBytes * 1000 / fileSize;
		if (newP != processPos) {
			pushMsg = true;
			processPos = newP;
            ProgressBar1->Position = processPos;
		}

		if (pushMsg) {
			Application->ProcessMessages();
        }
	}
    ProgressBar1->Position = 1000;
	stMD5.Finish();
	inFile.close();
	String str(stMD5.GetMD5String(cbCaption->Checked));
	log(L"");
	log(L"MD5:%s", str.c_str());
	log(L"%s %s",paramFileName.c_str(), zdh::utils::formatMemory(fileSize).c_str());
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
	Memo1->Lines->Insert(0, s);
    // Memo1->Lines->Add(s);
	// OutputDebugStringW(s.c_str());
}

void __fastcall TfrmMD5::DropFileList(TStrings * paramDropFileList) {
	if (paramDropFileList->Count > 0) {
		// Memo1->Lines->Clear();
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





