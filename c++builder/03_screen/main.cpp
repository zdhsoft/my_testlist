#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>

#include <stdio.h>
extern "C" int __stdcall PrScrn();

int _tmain(int argc, _TCHAR* argv[])
{
    return PrScrn();
}

