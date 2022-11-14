//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("form_md5.cpp", frmMD5);
USEFORM("form_main.cpp", frmMain);
USEFORM("form_datetime.cpp", frmDateTime);
USEFORM("form_week.cpp", frmWeek);
USEFORM("form_ocr.cpp", frmOCR);
//---------------------------------------------------------------------------
bool AppIsRuning() {
	auto hmutex = CreateMutex(NULL, false, L"WeekResport1.0");
	auto err = GetLastError();
	if (err == ERROR_ALREADY_EXISTS) {
		return true;
	}
	else {
		return false;
	}
}

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();

//          if AppIsRunning then begin
//    //showMessage('程序已经启动，请勿重复启动！');
//    application.Terminate;
//    exit;
//  end;
		if (AppIsRuning()) {
			ShowMessage("程序已经启动，请勿重复启动！");
			Application->Terminate();
        }

		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
