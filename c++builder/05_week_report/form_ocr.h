//---------------------------------------------------------------------------

#ifndef form_ocrH
#define form_ocrH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <XFunctionFunForm.h>
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TfrmOCR : public XFunctionFunForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TImage *Image1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	int m_ImageWidth = 0;
	int m_ImageHeight = 0;
private:
	void setImageSize();
public:		// User declarations
	__fastcall TfrmOCR(TComponent* Owner);
	void __fastcall SaveChange();
	void __fastcall Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOCR *frmOCR;
//---------------------------------------------------------------------------
#endif
