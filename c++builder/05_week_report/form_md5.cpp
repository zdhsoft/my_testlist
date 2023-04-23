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
	//
	Memo1->Lines->Clear();
//	Memo1->Lines->Add(Edit1->Text);
//	auto && a = Edit1->Text;
	zdh::XMD5 stMD5;
	stMD5.Init();

	UnicodeString str = L"天下无难事，只怕有心人"; // UnicodeString
	System::UTF8String utf8(str);
	//std::string utf8 = System::Sysutils::TEncoding::UTF8->GetString(str).c_str(); // 转换为UTF-8字符串
	// int byteCount = utf8.Length(); // 计算字节数
	// zdh::XChar buff[4096] = "天下无难事，只怕有心人";
//	std::string str = "天下无难事，只怕有心人";
//	std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;
//	std::u16string utf16 = converter.from_bytes(str);
//	std::string utf8 = converter.to_bytes(utf16);
//	AnsiString mm(kkk);
	zdh::XChar md5sum[33];
	Memo1->Lines->Add(utf8.Length());
	stMD5.Update(utf8.c_str(), utf8.Length());
	stMD5.Finish();
	stMD5.GetMD5String(md5sum, false);
	Memo1->Lines->Add(md5sum);

//    std::string str = "Hello, world!"; // 使用本地字符集创建字符串
//std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;
//std::u16string utf16 = converter.from_bytes(str); // 转换为UTF-16字符串
//std::string utf8 = converter.to_bytes(utf16); // 转换为UTF-8字符串

//	AnsiString st(Edit1->Text);
//	zdh::XMD5 stMD2;
//	stMD2.update(st.c_str(), st.length);
//	stMD2.Finish();
//	stMD2.GetMD5String(md5sum, false);
//    Memo1->Lines->Add(md5sum);
}
//---------------------------------------------------------------------------

