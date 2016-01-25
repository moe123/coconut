//
// terminal_utf8.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

namespace coconut
{
	namespace runtime
	{
		namespace builtins
		{
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			void terminal_setfont()
			{
#if defined(__MICROSOFT__)
				HANDLE stdout_h = GetStdHandle(STD_OUTPUT_HANDLE);
				HANDLE stderr_h = GetStdHandle(STD_ERROR_HANDLE);
				OSVERSIONINFOEX osvi;
				osvi.dwOSVersionInfoSize = sizeof(osvi);
				GetVersionEx(reinterpret_cast<LPOSVERSIONINFO>(&osvi));
				bool isafterxp = false;
				if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
					isafterxp = (osvi.dwMajorVersion >= 6);
				}
				if (isafterxp) {
					typedef BOOL (WINAPI * SetCurrentConsoleFontEx__)(HANDLE, BOOL, PCONSOLE_FONT_INFOEX);
					HMODULE mod_h = GetModuleHandle(TEXT("kernel32.dll"));
					SetCurrentConsoleFontEx__ sym = (SetCurrentConsoleFontEx__)GetProcAddress(mod_h, "SetCurrentConsoleFontEx");

					CONSOLE_FONT_INFOEX inf;
					inf.cbSize = sizeof(inf);
					inf.nFont = 12;
					inf.dwFontSize.X = 8;
					inf.dwFontSize.Y = 14;
					inf.FontFamily = FF_DONTCARE;
					inf.FontWeight = 400;
					lstrcpy(inf.FaceName, TEXT("Lucida Console"));

					sym(stdout_h, FALSE, &inf);
					sym(stderr_h, FALSE, &inf);
					
				} else {
					typedef BOOL (WINAPI * SetConsoleFont__)(HANDLE, DWORD);
					HMODULE mod_h = GetModuleHandle(TEXT("kernel32.dll"));
					SetConsoleFont__ sym = (SetConsoleFont__)GetProcAddress(mod_h, "SetConsoleFont");
					sym(stdout_h, 12);
					sym(stderr_h, 12);
				}
#endif
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool terminal_setup()
			{
#if defined(__MICROSOFT__)
				if (IsValidCodePage(CP_UTF8)) {
					if (!SetConsoleCP(CP_UTF8)) {
						return false;
					}
					if (!SetConsoleOutputCP(CP_UTF8)) {
						return false;
					}
					terminal_setfont();
					return true;
				}
				return false;
#else
				return true;
#endif
			}
		}
	}
}

/* EOF */