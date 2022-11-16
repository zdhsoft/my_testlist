//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <ctime>
#include <Clipbrd.hpp>
#include <regex>
#include "utils.h"
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
	zdh::XLong stValue = 0;
	const auto r = zdh::utils::TryStringToLong(edTimestampMillis->Text.c_str(), stValue);
	if (!r) {
        stValue = -1;
    }
	// std::time_t m = edTimestampMillis->Text.ToDouble();
	if (stValue < 0) {
		edTimestampResultMillis->Text = L"无效的时间戳";
	} else {
        std::time_t millis = stValue % 1000;
		std::time_t t = stValue / 1000;
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

//	regex ss("^([1-2]\\d{3})-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\\d):([0-5]\\d):([0-5]\\d)$");
//	regex ss1("^([1-2]\\d{3})-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\\d):([0-5]\\d):([0-5]\\d).(\\d{1,3})$");
void __fastcall TfrmDateTime::edDateTimeSecondChange(TObject *Sender)
{
	std::wregex stRegDateTime(L"^([1-2]\\d{3})-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\\d):([0-5]\\d):([0-5]\\d)$");
	std::wsmatch m;
	auto r = std::regex_match(edDateTimeSecond->Text.c_str(), stRegDateTime);
	std::wstring ww(edDateTimeSecond->Text.Trim().c_str());
	zdh::utils::log(L"regrex_match:%s =>%d",ww.c_str(), r);
	if(std::regex_search(ww, m, stRegDateTime)) {
		for (size_t i = 0; i < m.size(); ++i)  {
			zdh::utils::log(L"%d:%s", i, m[i].str().c_str());
		}
		zdh::XInt nYear = 0, nMonth = 0, nDay = 0, nHour = 0, nMinute = 0, nSecond = 0;
		zdh::utils::TryStringToInt(m[1].str().c_str(), nYear);
		zdh::utils::TryStringToInt(m[2].str().c_str(), nMonth);
		zdh::utils::TryStringToInt(m[3].str().c_str(), nDay);
		zdh::utils::TryStringToInt(m[4].str().c_str(), nHour);
		zdh::utils::TryStringToInt(m[5].str().c_str(), nMinute);
		zdh::utils::TryStringToInt(m[6].str().c_str(), nSecond);

        zdh::utils::log(L"解析后的日期:%04d-%02d-%02d %02d:%02d:%02d", nYear, nMonth, nDay, nHour, nMinute, nSecond);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDateTime::edDateTimeMillisChange(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------

