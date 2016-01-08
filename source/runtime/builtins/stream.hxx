//
// stream.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

namespace coconut
{
	namespace runtime
	{
		namespace builtins
		{
#if defined(__MICROSOFT__)
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
				unicode::codeset_utf8_utf16(utf8_in, wout);
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