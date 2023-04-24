//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	DragAcceptFiles(Handle,true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HandleDropFiles(TMessage &msg) {
    wchar_t FileName[_MAX_PATH];
    int i, Sum;
    //   获得拖拉的文件数目，该功能由第二个参数决定
	Sum = DragQueryFile(HDROP(msg.WParam), 0xFFFFFFFF, NULL, 0);

    if(Sum > 0)
	{
		for(int s = 0; s < Sum; s++) {
			// 这里只要第一个文件
			DragQueryFileW(HDROP(msg.WParam), s, FileName, _MAX_PATH);
			// 将文件路径显示于窗体上的Text控件
			Memo1->Lines->Add(FileName);
		}
    }
    //  释放应用程序为传递文件名而开辟的内存空间
    DragFinish( HDROP(msg.WParam) );
}
