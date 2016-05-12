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
	return unicode::utf8_to_ansi(
		unicode::utf16_to_utf8(utf16_in, unicode_conv_del_bom)
	);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const std::string & stream_convpath(const std::string & utf8_in)
{ return unicode::utf8_to_ansi(utf8_in); }
	
#else

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const std::wstring stream_convpath(const std::u16string & utf16_in)
{
	std::wstring wout(utf16_in.cbegin(), utf16_in.cend());
	return wout;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const std::wstring stream_convpath(const std::string & utf8_in)
{ return unicode::utf8_to_wide(utf8_in); }

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