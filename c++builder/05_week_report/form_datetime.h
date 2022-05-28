//---------------------------------------------------------------------------

#ifndef form_datetimeH
#define form_datetimeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <XFunctionFunForm.h>
#include <Vcl.ExtCtrls.hpp>

enum EnumNowStatus {
	Normal,
    Stop,
};

//---------------------------------------------------------------------------
class TfrmDateTime : public XFunctionFunForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TTimer *Timer1;
	TLabel *Label2;
	TLabel *LabelTimestamp;
	TButton *btnStartTimestamp;
	TButton *btnStopTimestamp;
	TButton *btnCopyTimestamp;
	TLabel *Label3;
	TEdit *edTimestampSecond;
	TButton *btnConvertSecond;
	TEdit *edTimestampResultSecond;
	TLabel *Label4;
	TEdit *edTimestampMillis;
	TButton *btnConvertMillis;
	TEdit *edTimestampResultMillis;
	TButton *btTimestampResultCopy;
	TButton *btTimestampMillisResultCopy;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *edDateTimeSecond;
	TEdit *edDateTimeMillis;
	TButton *Button1;
	TButton *Button2;
	TEdit *edDTResultSecond;
	TEdit *edDTResultMillis;
	TButton *btDTResultSecondCopy;
	TButton *btDTResultMillisCopy;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall btnStartTimestampClick(TObject *Sender);
	void __fastcall btnStopTimestampClick(TObject *Sender);
	void __fastcall btnCopyTimestampClick(TObject *Sender);
	void __fastcall btnConvertSecondClick(TObject *Sender);
	void __fastcall btnConvertMillisClick(TObject *Sender);
	void __fastcall edTimestampSecondChange(TObject *Sender);
	void __fastcall edTimestampMillisChange(TObject *Sender);
	void __fastcall btTimestampResultCopyClick(TObject *Sender);
	void __fastcall btTimestampMillisResultCopyClick(TObject *Sender);
private:	// User declarations
	EnumNowStatus m_NowStatus = EnumNowStatus::Normal;
private:
    void flashTimeStamp(bool paramForce = false);
public:		// User declarations
	__fastcall TfrmDateTime(TComponent* Owner);
	void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDateTime *frmDateTime;
//---------------------------------------------------------------------------
#endif
