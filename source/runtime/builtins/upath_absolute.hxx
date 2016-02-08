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
			// namespace { std::mutex upath_absolute_mtx; }
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::string upath_absolute(const std::string & utf8_in)
			{
				// std::unique_lock<std::mutex> auto_lock(upath_absolute_mtx);
				std::string p8;
#if defined(__MICROSOFT__)
				std::wstring uft16_out;
				unicode::codeset_utf8_utf16(utf8_in, uft16_out);
				WCHAR buf[512];
				DWORD len;
				if (0 != (len = GetFullPathNameW(uft16_out.c_str(), sizeof(buf), buf, NULL)) {
					if (len <= sizeof(buf)) {
						std::wstring uft16_in(buf, len -1);
						unicode::codeset_utf16_utf8(uft16_in, p8);
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