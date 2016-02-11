//
// upath_absolute.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#if defined(__MICROSOFT__)
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <rpcdce.h>
	#include <wincrypt.h>
	#include <windows.h>
#endif

namespace coconut
{
	namespace runtime
	{
		namespace builtins
		{
#if defined(__MICROSOFT__)
			namespace { std::mutex upath_absolute_mtx; }
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool upath_wisdir(wchar_t * filepath)
			{
				DWORD attrs = GetFileAttributesW(filepath);
				return (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY));
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool upath_wisfile(wchar_t * filepath)
			{
				DWORD attrs = GetFileAttributesW(filepath);
				return (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY));
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			bool upath_wexists(wchar_t * filepath)
			{
				DWORD attrs = GetFileAttributesW(filepath);
				return (attrs != INVALID_FILE_ATTRIBUTES);
			}
#endif
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::string upath_absolute(const std::string & utf8_in)
			{
				std::string p8;
#if defined(__MICROSOFT__)
				std::unique_lock<std::mutex> auto_lock(upath_absolute_mtx);
				std::wstring win;
				unicode::codeset_utf8_utf16(utf8_in, win);
				WCHAR buf[1024 + 1];
				DWORD len;
				if (0 != (len = GetFullPathNameW(win.c_str(), sizeof(buf), buf, NULL)) {
					if (len < sizeof(buf)) {
						std::wstring wout(buf, len);
						if (upath_wexists(wout.c_str()) {
							unicode::codeset_utf16_utf8(wout, p8);
						}
					}
				}
#else
				char buffer[PATH_MAX + 1];
				std::memset(buffer, 0, PATH_MAX + 1);
				char * pathname;
				if (NULL != (pathname = realpath(utf8_in.c_str(), buffer))) {
					p8.assign(pathname);
				}
#endif
				return p8;
			}
		}
	}
}

/* EOF */