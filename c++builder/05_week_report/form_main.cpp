//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_main.h"
#include "form_week.h"
#include "form_datetime.h"
#include "form_md5.h"
#include "form_ocr.h"
#include "form_json.h"
#include <System.JSON.hpp>
#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define INITFORM(CLASS, OBJECT) OBJECT = new CLASS(PanelContainer); OBJECT->Parent = this->PanelContainer; OBJECT->Init(); m_SubFormList.push_back(OBJECT);

TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	m_CurrActiveForm = nullptr;
	INITFORM(TfrmWeek, frmWeek);
	INITFORM(TfrmDateTime, frmDateTime);
	INITFORM(TfrmOCR, frmOCR);
	INITFORM(TfrmMD5, frmMD5);
    INITFORM(TfrmJSON, frmJSON);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowLocalForm(XFunctionFunForm * paramForm,TAction * paramAction)
{
	for(TSubFormList::iterator iter = this->m_SubFormList.begin(); iter != m_SubFormList.end(); ++iter)
	{
		if (*iter != paramForm)
		{
			(*iter)->Hide();
		}
		if (paramForm != NULL)
		{
			paramForm->Show();

		}
	}
	m_CurrActiveForm = paramForm;
	for(int i = 0; i < ActionList1->ActionCount; i++)
	{
		TAction * pAction = dynamic_cast<TAction *>(ActionList1->Actions[i]);
		if (pAction == NULL) continue;
		pAction->Checked = false;
	}
	if (paramAction != NULL) paramAction->Checked = true;
}

void __fastcall TfrmMain::ActionWeekExecute(TObject *Sender)
{
	ShowLocalForm(frmWeek, ActionWeek);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ActionDateTimeExecute(TObject *Sender)
{
	ShowLocalForm(frmDateTime, ActionDateTime);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Timer1Timer(TObject *Sender)
{
	//
	const TDateTime &d = Now();
	StatusBar1->Panels->Items[0]->Text = d.DateTimeString();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ApplicationEvents1Minimize(TObject *Sender)
{
	//
	Hide();
	WindowState = TWindowState::wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N1Click(TObject *Sender)
{
	Show();
	WindowState = TWindowState::wsNormal;
    Application->BringToFront();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::ActionAboutExecute(TObject *Sender)
{
	// GetFileVersionInfo()
	//
    ShowMessage("hello week report 1.1");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ActionOCRExecute(TObject *Sender)
{
	ShowLocalForm(frmOCR, ActionOCR);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ActionMD5Execute(TObject *Sender)
{
	ShowLocalForm(frmMD5, ActionMD5);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ActionExitExecute(TObject *Sender)
{
	//
    Application->Terminate();
}
//---------------------------------------------------------------------------

void EnumJsonValues(TJSONValue *lpJsonValue, UnicodeString sKeyName)
{
  TJSONObject *lpJsonObject = dynamic_cast<TJSONObject *>(lpJsonValue);
  if(lpJsonObject) // 结构体
   {
     for(int iPairIdx=0; iPairIdx<lpJsonObject->Count; iPairIdx++)
      {
        TJSONPair *lpPair = lpJsonObject->Pairs[iPairIdx]; // 第 iPairIdx 对键名/键值
        UnicodeString sName = lpPair->JsonString->Value(); // 第 iPairIdx 对键名
        TJSONValue *lpValue = lpPair->JsonValue;           // 第 iPairIdx 对键值

        // 不知道 lpValue 这个值是什么类型的，进一步枚举值，需要递归
        EnumJsonValues(lpValue, sKeyName.IsEmpty()?sName:sKeyName+L"."+sName);
      }
     return;
   }
  TJSONArray *lpJsonArray = dynamic_cast<TJSONArray *>(lpJsonValue);
  if(lpJsonArray) // 数组
   {
     for(int i=0; i<lpJsonArray->Count; i++)               // 枚举数组里面每个元素
      {
        TJSONValue *lpValue = lpJsonArray->Items[i];       // 数组里面第 i 个元素

        // 不知道 lpValue 这个值是什么类型的，进一步枚举值，需要递归
        EnumJsonValues(lpValue, sKeyName+L"["+IntToStr(i)+L"]");
      }
     return;
   }
  // 既不是结构体，也不是数组，而是简单的单一值，可以直接输出
  UnicodeString sKeyValue = lpJsonValue->Value(); // sKeyName 的值就是 lpJsonValue
  //Memo2->Lines->Add(sKeyName + L" = " + sKeyValue);
  zdh::utils::log(L"%s = %s", sKeyName.c_str(), sKeyValue.c_str());
}

void __fastcall TfrmMain::ActionJSONExecute(TObject* Sender)
{
	ShowLocalForm(frmJSON, ActionJSON);
//    //
//    String s = "./package.json";
//
//    std::auto_ptr list(new TStringList());
//    list->LoadFromFile(s);
//    std::auto_ptr lpJson(TJSONObject::ParseJSONValue(list->Text));
//	if (lpJson.get() == nullptr || lpJson.get() == NULL) {
//        zdh::utils::log(L"加载的json:$s的结果为null", s.c_str());
//        return;
//    }
//    if (lpJson->Null) {
//        zdh::utils::log(L"加载的json:$s的属性为NULL", s.c_str());
//        return;
//    }
//    EnumJsonValues(lpJson.get(), L"");
    //	lpJson->GetValueA()
    //	TJSONObject * lpRoot = dynamic_cast<TJSONObject *>(lpJson.get());
}
//---------------------------------------------------------------------------


