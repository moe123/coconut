//
// nutrt-unicode_wide.hxx
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
bool unicode_utf8_to_wide(const std::string & utf8_in, std::wstring & wide_out)
{
	bool result = false;

#if defined(__MICROSOFT__) && \
	(defined(COCONUT_SIZEOF_WIDE) && COCONUT_SIZEOF_WIDE == 2)
	
#ifndef CP_UTF8
	#define CP_UTF8 65001
#endif
	
	std::string utf8_out(utf8_in);
	unicode::utf8_del_bom(utf8_out);
	
	UINT codepage = CP_UTF8, len = 0;
	DWORD flags = 0;
	len = MultiByteToWideChar(codepage, flags, utf8_out.c_str(), -1, 0, 0);
	if (len > 0) {
		std::vector<std::wstring::value_type> buf(len + 1);
		if (MultiByteToWideChar(codepage, flags, utf8_out.c_str(), -1, buf.data(), len)) {
			wide_out.assign(buf, 0, len);
			result = true;
		}
		buf.clear();
	}
#else
	
#if defined(COCONUT_SIZEOF_WIDE) && COCONUT_SIZEOF_WIDE == 4
	
#pragma warning WRONG USAGE
	
	using Char8T = std::string::value_type;
	using Char32T = std::wstring::value_type;
	
	unicode::_conv_utf8_to_ucs4<Char8T, Char32T, unicode_conv_default>(utf8_in, wide_out);
	
#else
	
#pragma warning WRONG USAGE
	
	using Char8T = std::string::value_type;
	using Char16T = std::wstring::value_type;
	
	unicode::_conv_utf8_to_utf16<Char8T, Char16T, unicode_conv_default>(utf8_in, wide_out);
	
#endif
	
#endif

	return result;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool unicode_wide_to_utf8(const std::wstring & wide_in, std::string & utf8_out)
{
	bool result = false;
	
#if defined(__MICROSOFT__) && \
	(defined(COCONUT_SIZEOF_WIDE) && COCONUT_SIZEOF_WIDE == 2)
	
#ifndef CP_UTF8
	#define CP_UTF8 65001
#endif

	UINT codepage = CP_UTF8, len = 0;
	DWORD flags = 0;
	len = WideCharToMultiByte(codepage, flags, wide_in.c_str(), -1, 0, 0, NULL, NULL);
	if (len > 0) {
		std::vector<std::string::value_type> buf(len + 1);
		if (WideCharToMultiByte(codepage, flags, wide_in.c_str(), -1, buf.data(), len, NULL, NULL)) {
			utf8_out.assign(buf, 0, len);
			utf8_del_bom(utf8_out);
			result = true;
		}
		buf.clear();
	}
	
#else
	
#if defined(COCONUT_SIZEOF_WIDE) && COCONUT_SIZEOF_WIDE == 4
	
#pragma warning WRONG USAGE
	
	using Char32T = std::wstring::value_type;
	using Char8T = std::string::value_type;
	unicode::_conv_ucs4_to_utf8<Char32T, Char8T>(wide_in, utf8_out);
	
#else
	
#pragma warning WRONG USAGE
	
	using Char16T = std::wstring::value_type;
	using Char8T = std::string::value_type;
	unicode::_conv_utf16_to_utf8<Char16T, Char8T>(wide_in, utf8_out);
	
#endif
	
#endif

	return result;
		
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool unicode_utf8_to_ansi(const std::string & utf8_in, std::string & ansi_out)
{
	bool result = false;
	
#if defined(__MICROSOFT__)

	std::wstring wide_out;
	
	if (unicode_utf8_to_wide(utf8_in, wide_out)) {
		
		UINT codepage = CP_ACP, len = 0;
		DWORD flags = 0;
		len = WideCharToMultiByte(codepage, flags, wide_out.c_str(), -1, 0, 0, NULL, NULL);
		if (len > 0) {
			std::vector<std::string::value_type> buf(len + 1);
			if (WideCharToMultiByte(codepage, flags, wide_out.c_str(), -1, buf.data(), len, NULL, NULL)) {
				ansi_out.assign(buf, 0, len);
				result = true;
			}
			buf.clear();
		}
	}

#endif

	return result;
}

	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool unicode_ansi_to_utf8(const std::string & ansi_in, std::string & utf8_out)
{
	bool result = false;

#if defined(__MICROSOFT__)
	
	std::wstring wide_out;
	
	UINT codepage = CP_ACP, len = 0;
	DWORD flags = 0;
	len = MultiByteToWideChar(codepage, flags, ansi_in.c_str(), -1, 0, 0);
	if (len > 0) {
		std::vector<std::wstring::value_type> buf(len + 1);
		if (MultiByteToWideChar(codepage, flags, ansi_in.c_str(), -1, buf.data(), len)) {
			wide_out.assign(buf, 0, len);
			result = true;
		}
		buf.clear();
	}
	
	if(result) {
		result = unicode_wide_to_utf8(wide_out, utf8_out);
	}

#endif

	return result;
}
	
}}} /* EONS */

/* EOF */