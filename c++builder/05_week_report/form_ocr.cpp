﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_ocr.h"
#include "PrScrn.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmOCR *frmOCR;
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
    PrScrn();
}
//---------------------------------------------------------------------------
