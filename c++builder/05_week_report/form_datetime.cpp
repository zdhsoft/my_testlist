//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <ctime>
#include <Clipbrd.hpp>
#include "form_datetime.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDateTime *frmDateTime;
//---------------------------------------------------------------------------
__fastcall TfrmDateTime::TfrmDateTime(TComponent* Owner)
	: XFunctionFunForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmDateTime::Init() {
	//
	// Timer1Timer(this);
    flashTimeStamp(true);
}

void __fastcall TfrmDateTime::Timer1Timer(TObject *Sender)
{
	//
    flashTimeStamp(false);
}
//---------------------------------------------------------------------------
void TfrmDateTime::flashTimeStamp(bool paramForce) {
	if(!paramForce && m_NowStatus == EnumNowStatus::Stop) {
		return;
	}

	auto t = std::time(0);
	LabelTimestamp->Caption = String(t);

	// 	const TDateTime &d = Now();
//	StatusBar1->Panels->Items[0]->Text = d.DateTimeString();
}
void __fastcall TfrmDateTime::btnStartTimestampClick(TObject *Sender)
{
	//
    m_NowStatus = EnumNowStatus::Normal;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDateTime::btnStopTimestampClick(TObject *Sender)
{
	//
    m_NowStatus = EnumNowStatus::Stop;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDateTime::btnCopyTimestampClick(TObject *Sender)
{
	//
    Clipboard()->AsText = LabelTimestamp->Caption;
}
//---------------------------------------------------------------------------



void __fastcall TfrmDateTime::btnConvertSecondClick(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------

void __fastcall TfrmDateTime::btnConvertMillisClick(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------

