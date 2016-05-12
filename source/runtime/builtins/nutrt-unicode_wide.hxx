//
// nutrt-stream_convpath.hxx
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
{ namespace runtime
{ namespace builtins
{

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool unicode_wide_utf8_to_wide(const std::string & utf8_in, std::wstring & wide_out)
{
	bool result = false;

#if defined(__MICROSOFT__)
	
#ifndef CP_UTF8
	#define CP_UTF8 65001
#endif
	
	UINT codepage = CP_UTF8, len = 0;
	DWORD flags = 0;
	len = MultiByteToWideChar(codepage, flags, utf8_in.c_str(), -1, 0, 0);
	if (len > 0) {
		std::vector<std::wstring::value_type> buf(len + 1);
		MultiByteToWideChar(codepage, flags, utf8_in.c_str(), -1, buf.data(), len);
		wide_out.assign(buf, 0, len);
		buf.clear();
		result = true;
	}
	
#endif
	return result;
}
	
bool unicode_wide_wide_to_utf8(const std::wstring & wide_in, std::string & utf8_out)
{
	bool result = false;
	
#if defined(__MICROSOFT__)
	
#ifndef CP_UTF8
	#define CP_UTF8 65001
#endif

	UINT codepage = CP_UTF8, len = 0;
	DWORD flags = 0;
	len = WideCharToMultiByte(codepage, flags, wide_in.c_str(), -1, 0, 0, NULL, NULL);
	if (len > 0) {
		std::vector<std::string::value_type> buf(len + 1);
		WideCharToMultiByte(codepage, flags, wide_in.c_str(), -1, buf.data(), len, NULL, NULL);
		utf8_out.assign(buf, 0, len);
		buf.clear();
		result = true;
	}
	
#endif
	return result;
		
}

}}} /* EONS */

/* EOF */