//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_main.h"
#include "form_week.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	m_CurrActiveForm = nullptr;
	frmWeek = new TfrmWeek(PanelContainer);
	frmWeek->Parent = this->PanelContainer;

	frmWeek->Init();

	m_SubFormList.push_back(frmWeek);
    AnsiString s;
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
    //
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
	//
    ShowMessage("hello week report 1.0");
}
//---------------------------------------------------------------------------

