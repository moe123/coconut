//
// upath_absolute.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

namespace coconut {
	namespace runtime {
		namespace builtins {

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool upath_absolute(const std::string & utf8_path_in, std::string & utf8_path_out)
{
	bool result = false;
#if defined(__MICROSOFT__)

	std::wstring win;
	std::wstring wout;
	unicode::codeset_utf8_utf16(utf8_path_in, win);
	if ((result = fs_resolve_v0(win, wout))) {
		unicode::codeset_utf16_utf8(wout, utf8_path_out);
	}

#else
	result = fs_resolve(utf8_path_in, utf8_path_out);
#endif
	return result;
}

}}} /* EONS */

/* EOF */