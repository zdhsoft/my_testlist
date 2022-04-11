//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_week.h"
//#include <Vcl.FileCtrl.hpp>
#include "FileCtrl.hpp"
#include <dirent.h>
#include <IniFiles.hpp>
#include <memory>
#include <filesystem>
#include <Clipbrd.hpp>

namespace fs = std::filesystem;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmWeek *frmWeek;
//---------------------------------------------------------------------------
__fastcall TfrmWeek::TfrmWeek(TComponent* Owner)
	: XFunctionFunForm(Owner)
{
	const auto * iniFile = "./week.ini";
	if(!fs::exists(iniFile)) {
		ShowMessage(String("配置文件:") + iniFile + " 不存在! ");
        return;
    }


	// TMemIniFile * pIni = new TMemIniFile("./week.ini");
	auto pIni = std::auto_ptr<TMemIniFile>(new TMemIniFile(iniFile, TEncoding::UTF8));
	auto && memFileName = pIni->ReadString("week", "member", "./mem.ini");
    auto && memDir = pIni->ReadString("week", "dir", ".");

	m_MemberList = new TStringList();
	m_MemberList->LoadFromFile(memFileName, TEncoding::UTF8);
	Label2->Caption = String("当前成员(") + m_MemberList->Count + "):";
    Edit1->Text = memDir;



}
//---------------------------------------------------------------------------

void __fastcall TfrmWeek::Init() {
	ListBoxCurr->Items->Clear();
	ListBoxCurr->Items->AddStrings(m_MemberList);
}

void __fastcall TfrmWeek::Check(TStrings * paramHas, TStrings * paramNotHas) {
	TStrings * src = ListBox1->Items;
	TStrings * names = ListBoxCurr->Items;
	for(int i = 0; i < names->Count; i++) {
		const String && n = names->Strings[i];
		if (isInList(src, n)) {
			paramHas->Add(n);
		} else {
            paramNotHas->Add(n);
        }
	}
}
bool __fastcall TfrmWeek::isInList(TStrings * paramSrcList, const String & paramDest) {
	bool bRet = false;
	do {
		for(auto i = 0; i < paramSrcList->Count; i++) {
			const String && s = paramSrcList->Strings[i];
			if (s.Pos(paramDest) > 0) {
				bRet = true;
                break;
            }
        }
	}while(false);
    return bRet;
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
			String ExcelExt1(".xls");
            String ExcelExt2(".xlsx");

			while ( (entry=wreaddir(d)) != NULL)
			{
				String s(entry->d_name);
				if (s == p || s == pp) {
                    continue;
				}
				String && ext = ExtractFileExt(s).LowerCase();
				if (!(ext == ExcelExt1 || ext == ExcelExt2)) {
                    continue;
                }
				ListBox1->Items->Add(s);

			}
			ListBoxGood->Items->Clear();
            ListBoxNot->Items->Clear();
			Check(ListBoxGood->Items, ListBoxNot->Items);
			Label3->Caption = String("未填(") + ListBoxNot->Items->Count + "):";
			Label4->Caption = String("已填(") + ListBoxGood->Items->Count + "):";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWeek::FormDestroy(TObject *Sender)
{
	//
	if(m_MemberList!= nullptr) {
		delete m_MemberList;
        m_MemberList = nullptr;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmWeek::Button4Click(TObject *Sender)
{
	//
	Clipboard()->AsText = ListBoxNot->Items->Text;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWeek::Button3Click(TObject *Sender)
{
	Clipboard()->AsText = ListBoxGood->Items->Text;
}
//---------------------------------------------------------------------------

