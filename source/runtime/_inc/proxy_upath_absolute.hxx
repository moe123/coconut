//
// proxy_upath_absolute.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#if defined(_MSC_VER)
	#ifdef _UNICODE
		#undef _UNICODE
	#endif
	#ifdef UNICODE
		#undef UNICODE
	#endif
	#ifndef _WINSOCKAPI_
		#define _WINSOCKAPI_ 1
	#endif
	#ifndef _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS 1
	#endif
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

namespace coconut
{
	namespace runtime
	{
		namespace _inc
		{
			namespace
			{
				std::mutex upath_absolute_mtx;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::string upath_absolute(const std::string & utf8_in)
			{
				std::unique_lock<std::mutex> auto_lock(upath_absolute_mtx);
				std::string p8;
// #if defined(_MSC_VER)
#if defined(WIN32) || defined(_WIN32)
				std::wstring uft16_out;
				unicode::codeset_utf8_utf16(utf8_in, uft16_out);
				WCHAR buf[2048];
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