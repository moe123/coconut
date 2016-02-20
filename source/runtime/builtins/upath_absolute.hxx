//
// upath_absolute.hxx
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
			std::string upath_absolute(const std::string & utf8_in)
			{
				std::string utf8_out;
#if defined(__MICROSOFT__)
				std::wstring win;
				std::wstring wout;
				unicode::codeset_utf8_utf16(utf8_in, win);
				if (fs_resolve_v0(win, wout)) {
					unicode::codeset_utf16_utf8(wout, utf8_out);
				}
#else
				char buffer[PATH_MAX + 1];
				std::memset(buffer, 0, PATH_MAX + 1);
				char * pathname;
				if (NULL != (pathname = realpath(utf8_in.c_str(), buffer))) {
					utf8_out.assign(pathname);
				}
#endif
				return utf8_out;
			}
		}
	}
}

/* EOF */