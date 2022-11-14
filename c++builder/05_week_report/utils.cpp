//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace zdh {
	namespace utils {
		void log(const wchar_t * format, ...) {
			String s;
			va_list paramList;
			va_start(paramList, format);
			s.vprintf(format, paramList);
			va_end(paramList);
            OutputDebugStringW(s.c_str());
		}
	}
}
