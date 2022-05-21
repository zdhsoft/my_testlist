//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_ocr.h"
#include "PrScrn.h"
#include <Clipbrd.hpp>
#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmOCR *frmOCR;
using namespace std;
//---------------------------------------------------------------------------
__fastcall TfrmOCR::TfrmOCR(TComponent* Owner)
	: XFunctionFunForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmOCR::SaveChange()
{
	//
}

void __fastcall TfrmOCR::Init() {
}

void __fastcall TfrmOCR::Button1Click(TObject *Sender)
{
	//
	if(PrScrn() != 0) {
		if (Clipboard()->HasFormat(CF_BITMAP)) {
			auto_ptr<TBitmap> p(new TBitmap());
			p->Assign(Clipboard());
			if (p->Width > m_ImageWidth || p->Height > m_ImageHeight) {
				int newWidth;
				int newHeight;
				// 如果需要做缩放
				auto rw = p->Width * 1.0 / m_ImageWidth;
				auto intH = static_cast<int>(p->Height / rw);
				if (intH <= m_ImageHeight) {
					newWidth = m_ImageWidth;
					newHeight = intH;

				} else {
					auto rh = p->Height * 1.0 / m_ImageHeight;
					auto intW = static_cast<int>(p->Width / rh);

					newWidth = intW;
					newHeight = m_ImageHeight;
				}
				TRect stRect;
				stRect.SetWidth(newWidth);
                stRect.SetHeight(newHeight);
				Image1->Canvas->StretchDraw(stRect, p.get());

			} else {
				Image1->Picture->Assign(p.get());
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmOCR::FormResize(TObject *Sender)
{
    //
	setImageSize();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOCR::FormPaint(TObject *Sender)
{
	//
	// setImageSize();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOCR::FormShow(TObject *Sender)
{
	//
	setImageSize();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOCR::FormCreate(TObject *Sender)
{
	//
	setImageSize();
}
//---------------------------------------------------------------------------
void TfrmOCR::setImageSize() {
   m_ImageWidth = Image1->Width;
   m_ImageHeight = Image1->Height;
   if (m_ImageWidth < 1) m_ImageWidth = 1;
   if (m_ImageHeight < 1) m_ImageHeight = 1;
}

