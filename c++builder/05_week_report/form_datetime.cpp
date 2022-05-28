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


void __fastcall TfrmDateTime::edTimestampSecondChange(TObject *Sender)
{
	std::time_t t = edTimestampSecond->Text.ToIntDef(-1);
	if (t < 0) {
		edTimestampResultSecond->Text = L"无效的时间戳";
	} else {
		auto * tm = localtime(&t);
		String s;
        s.sprintf(L"%04d-%02d-%02d %02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        edTimestampResultSecond->Text = s;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmDateTime::edTimestampMillisChange(TObject *Sender)
{
	std::time_t m = edTimestampMillis->Text.ToDouble();
	if (m < 0) {
		edTimestampResultMillis->Text = L"无效的时间戳";
	} else {
        std::time_t millis = m % 1000;
		std::time_t t = m / 1000;
		auto * tm = localtime(&t);
		String s;
		s.sprintf(L"%04d-%02d-%02d %02d:%02d:%02d.%03d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, millis);
        edTimestampResultMillis->Text = s;
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmDateTime::btTimestampResultCopyClick(TObject *Sender)
{
    	//
	Clipboard()->AsText = edTimestampResultSecond->Text;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDateTime::btTimestampMillisResultCopyClick(TObject *Sender)
{
	Clipboard()->AsText = edTimestampResultMillis->Text;
}
//---------------------------------------------------------------------------


