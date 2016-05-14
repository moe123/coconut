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

#if defined(__MICROSOFT__)
	
#if defined(__MICROSOFT_MINGW__)
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const std::string stream_convpath(const std::u16string & utf16_in)
{
	std::string ansi_out;
	std::string utf8_out = unicode::utf16_to_utf8(
		utf16_in,
		unicode_conv_del_bom
	);
	unicode_utf8_to_ansi(utf8_out, ansi_out);
	
	return ansi_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const std::string & stream_convpath(const std::string & utf8_in)
{
	std::string ansi_out;
	unicode_utf8_to_ansi(utf8_in, ansi_out);
	return ansi_out;
}
	
#else

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const std::wstring stream_convpath(const std::u16string & utf16_in)
{
	std::wstring wide_out;
	std::string utf8_out = unicode::utf16_to_utf8(
		utf16_in,
		unicode_conv_del_bom
	);
	unicode_utf8_to_wide(utf8_out, wide_out);
	
	return wide_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const std::wstring stream_convpath(const std::string & utf8_in)
{
	std::wstring wide_out;
	unicode_utf8_to_wide(utf8_in, wide_out);
	return wide_out;
}

#endif
	
#else

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const std::string stream_convpath(const std::u16string & utf16_in)
{ return unicode::utf16_to_utf8(utf16_in); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const std::string & stream_convpath(const std::string & utf8_in)
{ return utf8_in; }

#endif

}}} /* EONS */

/* EOF */