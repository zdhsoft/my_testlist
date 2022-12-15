//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//#include "rapidjson/document.h"     // rapidjson's DOM-style API
//#include "rapidjson/prettywriter.h" // for stringify JSON
#include <cstdio>

// using namespace rapidjson;
#include "form_json.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmJSON *frmJSON;
//---------------------------------------------------------------------------
__fastcall TfrmJSON::TfrmJSON(TComponent* Owner)
	: XFunctionFunForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmJSON::SaveChange()
{
	//
}
//---------------------------------------------------------------------------

void __fastcall TfrmJSON::Init() {
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmJSON::Button2Click(TObject *Sender)
{
	//
//	const wchar_t json[] = L" { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
//	Document document;
//    document.Parse(json);

}
//---------------------------------------------------------------------------
void __fastcall TfrmJSON::Button1Click(TObject *Sender)
{
	if(OpenTextFileDialog1->Execute()) {
		auto * coding = System::Sysutils::TEncoding::UTF8;
		if(OpenTextFileDialog1->EncodingIndex == 0) {
			coding = System::Sysutils::TEncoding::ANSI;
		}
        Memo1->Lines->Clear();
		Memo1->Lines->LoadFromFile(OpenTextFileDialog1->FileName, coding);
	}
}
//---------------------------------------------------------------------------
