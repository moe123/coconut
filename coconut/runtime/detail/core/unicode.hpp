//
// unicode.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/defines.hpp>

#ifndef COCONUT_RUNTIME_UNICODE_HPP
#define COCONUT_RUNTIME_UNICODE_HPP

namespace coconut {
	namespace runtime {
		namespace unicode {

template <typename CharT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void codeset_utf16_utf8(
	const std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT> > & source,
	std::string & result
) {
	typedef std::codecvt_utf8_utf16<CharT> codecvt_utf8_utf16;
	std::wstring_convert<codecvt_utf8_utf16, CharT> conv;
	result.swap(conv.to_bytes(source));
}

template <typename CharT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void codeset_utf8_utf16(
	const std::string & source, std::basic_string<CharT, std::char_traits<CharT>,
	std::allocator<CharT> > & result
) {
	typedef std::codecvt_utf8_utf16<CharT> codecvt_utf8_utf16;
	std::wstring_convert<codecvt_utf8_utf16, CharT> conv;
	result.swap(conv.from_bytes(source));
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_ucs2(const std::string & utf8_in)
{
	typedef std::codecvt_utf8<char16_t> codecvt_utf8_ucs2;
	std::wstring_convert<codecvt_utf8_ucs2, char16_t> conv;
	return conv.from_bytes(utf8_in);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_utf16(const std::string & utf8_in)
{
	typedef std::codecvt_utf8_utf16<char16_t> codecvt_utf8_utf16;
	std::wstring_convert<codecvt_utf8_utf16, char16_t> conv;
	return conv.from_bytes(utf8_in);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u32string utf8_to_ucs4(const std::string & utf8_in)
{
	typedef std::codecvt_utf8<char32_t> codecvt_utf8_ucs4;
	std::wstring_convert<codecvt_utf8_ucs4, char32_t> conv;
	return conv.from_bytes(utf8_in);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u32string utf8_to_utf32(const std::string & utf8_in)
{ return utf8_to_ucs4(utf8_in); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string ucs2_to_utf8(const std::u16string & in_ucs2)
{
	typedef std::codecvt_utf8<char16_t> codecvt_utf8_ucs2;
	std::wstring_convert<codecvt_utf8_ucs2, char16_t> conv;
	return conv.to_bytes(in_ucs2);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string ucs2_to_utf16(const std::u16string & in_ucs2)
{
	std::string utf8_in = unicode::ucs2_to_utf8(in_ucs2);
	return utf8_to_utf16(utf8_in);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string utf16_to_utf8(const std::u16string & utf16_in)
{
	typedef std::codecvt_utf8_utf16<char16_t> codecvt_utf8_utf16;
	std::wstring_convert<codecvt_utf8_utf16, char16_t> conv;
	return conv.to_bytes(utf16_in);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string ucs4_to_utf8(const std::u32string & in_ucs4)
{
	typedef std::codecvt_utf8<char32_t> codecvt_utf8_ucs4;
	std::wstring_convert<codecvt_utf8_ucs4, char32_t> conv;
	return conv.to_bytes(in_ucs4);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string utf32_to_utf8(const std::u32string & in_utf32)
{ return ucs4_to_utf8(in_utf32); }

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_UNICODE_HPP */

/* EOF */