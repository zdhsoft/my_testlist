//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_main.h"
// #include "form_week.h"
#include "form_datetime.h"
#include "form_md5.h"
#include "form_ocr.h"
#include "form_json.h"
#include <System.JSON.hpp>
#include "utils.h"
#include "from_moive.h"
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
	// INITFORM(TfrmWeek, frmWeek);
	INITFORM(TfrmDateTime, frmDateTime);
	INITFORM(TfrmOCR, frmOCR);
	INITFORM(TfrmMD5, frmMD5);
	INITFORM(TfrmJSON, frmJSON);
	INITFORM(TfrmMoive, frmMoive);
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
	//ShowLocalForm(frmWeek, ActionWeek);
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
	ShowMessage("hello week report 1.4!");
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
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::HandleDropFiles(TMessage &msg) {
	wchar_t FileName[_MAX_PATH];
	//   获得拖拉的文件数目，该功能由第二个参数决定
	const int Sum = DragQueryFile(HDROP(msg.WParam), 0xFFFFFFFF, NULL, 0);

    if(Sum > 0)
	{
        TStrings * pList = new TStringList();
		for(int s = 0; s < Sum; s++) {
			// 这里只要第一个文件
			DragQueryFileW(HDROP(msg.WParam), s, FileName, _MAX_PATH);
			pList->Add(FileName);
			// 将文件路径显示于窗体上的Text控件
			// Memo1->Lines->Add(FileName);
		}
		if (m_CurrActiveForm != nullptr && m_CurrActiveForm != NULL) {
			m_CurrActiveForm->DropFileList(pList);
		}
        delete pList;
    }
    //  释放应用程序为传递文件名而开辟的内存空间
	DragFinish( HDROP(msg.WParam) );
}
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	DragAcceptFiles(Handle,true);
    ShowLocalForm(frmDateTime, ActionDateTime);
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::ActionMoiveExecute(TObject *Sender)
{
	//
	ShowLocalForm(frmMoive, ActionMoive);
}
//---------------------------------------------------------------------------

