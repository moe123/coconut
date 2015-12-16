//
// core_stream.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

/*
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
*/

namespace coconut
{
	namespace runtime
	{
		namespace _inc
		{
// #if defined(_MSC_VER)
#if defined(WIN32) || defined(_WIN32)
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			const std::wstring stream_convpath(const std::u16string & utf16_in)
			{
				std::wstring wout(utf16_in.begin(), utf16_in.end());
				return wout;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			const std::wstring stream_convpath(const std::string & utf8_in)
			{
				std::wstring wout;
				unicode::codeset_utf8_utf16(utf8_in, uft16_out);
				return wout;
				/*
				std::wstring wout;
				UINT codepage = CP_UTF8, len = 0;
				DWORD flags = 0;
				len = MultiByteToWideChar(codepage, flags, utf8_in.c_str(), -1, 0, 0);
				if (len > 0) {
					std::vector<std::wstring::value_type> buf(len);
					MultiByteToWideChar(codepage, flags, utf8_in.c_str(), -1, buf.data(), len);
					wout.assign(buf.begin(), buf.end() -1);
				}
				return wout;
				*/
			}
#else
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			const std::string stream_convpath(const std::u16string & utf16_in)
			{ return unicode::utf16_to_utf8(utf16_in); }
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			const std::string & stream_convpath(const std::string & utf8_in)
			{ return utf8_in; }
#endif
		}
	}
}

/* EOF */