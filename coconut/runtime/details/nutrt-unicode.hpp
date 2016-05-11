//
// nutrt-unicode.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_UNICODE_HPP
#define COCONUT_RUNTIME_UNICODE_HPP

namespace coconut
{ namespace runtime
{ namespace unicode
{
	
template<typename CharT1, typename CharT2, typename CodecvtT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void __conv_from_bytes(
	const std::basic_string<CharT1, std::char_traits<CharT1>, std::allocator<CharT1> > & src,
	std::basic_string<CharT2, std::char_traits<CharT2>, std::allocator<CharT2> > & dest
) {
	std::wstring_convert<CodecvtT, CharT2> conv;
	dest = conv.from_bytes(src);
}

template<typename CharT1, typename CharT2, typename CodecvtT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void __conv_to_bytes(
	const std::basic_string<CharT1, std::char_traits<CharT1>, std::allocator<CharT1> > & src,
	std::basic_string<CharT2, std::char_traits<CharT2>, std::allocator<CharT2> > & dest
) {
	std::wstring_convert<CodecvtT, CharT1> conv;
	dest = conv.to_bytes(src);
}
	
template<typename Char16T, typename Char8T,
	typename std::enable_if<
		sizeof(Char16T) == sizeof(char16_t) &&
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_utf16_to_utf8(
	const std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & src,
	std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & dest
) {
	using CodecvtT = std::codecvt_utf8_utf16<Char16T>;
	__conv_to_bytes<Char16T, Char8T, CodecvtT>(src, dest);
}
	
template<typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_default, void
>::type _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8_utf16<Char16T>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
template<typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_del_gen_bom, void
>::type _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8_utf16<
		Char16T, 0x10FFFF, std::codecvt_mode(std::consume_header|std::generate_header)
	>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
template<typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_del_bom, void
>::type _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8_utf16<
		Char16T, 0x10FFFF, std::codecvt_mode(std::consume_header)
	>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
template<typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_gen_bom, void
>::type _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8_utf16<
		Char16T, 0x10FFFF, std::codecvt_mode(std::generate_header)
	>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}

template<typename Char8T, typename Char16T,
	typename std::enable_if<
		sizeof(Char8T) == sizeof(char) &&
		sizeof(Char16T) == sizeof(char16_t), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest,
	unicode_option option = unicode_conv_default
) {
	switch (option)
	{
		case unicode_conv_del_gen_bom:
			_conv_utf8_to_utf16<Char8T, Char16T, unicode_conv_del_gen_bom>(src, dest);
		break;
		case unicode_conv_del_bom:
			_conv_utf8_to_utf16<Char8T, Char16T, unicode_conv_del_bom>(src, dest);
		break;
		case unicode_conv_gen_bom:
			_conv_utf8_to_utf16<Char8T, Char16T, unicode_conv_gen_bom>(src, dest);
		break;
		default:
			_conv_utf8_to_utf16<Char8T, Char16T, unicode_conv_default>(src, dest);
		break;
	}
}
	
template<typename Char16T, typename Char8T,
	typename std::enable_if<
		sizeof(Char16T) == sizeof(char16_t) &&
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_ucs2_to_utf8(
	const std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & src,
	std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<Char16T>;
	__conv_to_bytes<Char16T, Char8T, CodecvtT>(src, dest);
}
	
template<typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_default, void
>::type _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<Char16T>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
template<typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_del_gen_bom, void
>::type _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<
		Char16T, 0x10FFFF, std::codecvt_mode(std::consume_header|std::generate_header)
	>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
template<typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_del_bom, void
>::type _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<
		Char16T, 0x10FFFF, std::codecvt_mode(std::consume_header)
	>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
template<typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_gen_bom, void
>::type _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<
		Char16T, 0x10FFFF, std::codecvt_mode(std::generate_header)
	>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}

template<typename Char8T, typename Char16T,
	typename std::enable_if<
		sizeof(Char8T) == sizeof(char) &&
		sizeof(Char16T) == sizeof(char16_t), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, std::allocator<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, std::allocator<Char16T> > & dest,
	unicode_option option = unicode_conv_default
) {
	switch (option)
	{
		case unicode_conv_del_gen_bom:
			_conv_utf8_to_ucs2<Char8T, Char16T, unicode_conv_del_gen_bom>(src, dest);
		break;
		case unicode_conv_del_bom:
			_conv_utf8_to_ucs2<Char8T, Char16T, unicode_conv_del_bom>(src, dest);
		break;
		case unicode_conv_gen_bom:
			_conv_utf8_to_ucs2<Char8T, Char16T, unicode_conv_gen_bom>(src, dest);
		break;
		default:
			_conv_utf8_to_ucs2<Char8T, Char16T, unicode_conv_default>(src, dest);
		break;
	}
}
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_utf16(
	const std::string & utf8_in,
	unicode_option option
) {
	std::u16string utf16_out;
	
	using Char8T = std::string::value_type;
	using Char16T = std::u16string::value_type;
	
	_conv_utf8_to_utf16<Char8T, Char16T>(utf8_in, utf16_out, option);
	return utf16_out;
}
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_utf16(const std::string & utf8_in)
{
	std::u16string utf16_out;
	
	using Char8T = std::string::value_type;
	using Char16T = std::u16string::value_type;
	
	_conv_utf8_to_utf16<Char8T, Char16T, unicode_conv_default>(utf8_in, utf16_out);
	return utf16_out;
}


COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_ucs2(
	const std::string & utf8_in,
	unicode_option option
) {
	std::u16string ucs2_out;
	
	using Char8T = std::string::value_type;
	using Char16T = std::u16string::value_type;
	
	_conv_utf8_to_ucs2<Char8T, Char16T>(utf8_in, ucs2_out, option);
	return ucs2_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_ucs2(const std::string & utf8_in) {
	std::u16string ucs2_out;
	
	using Char8T = std::string::value_type;
	using Char16T = std::u16string::value_type;
	
	_conv_utf8_to_ucs2<Char8T, Char16T, unicode_conv_default>(utf8_in, ucs2_out);
	return ucs2_out;
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
	std::string utf8_in = ucs2_to_utf8(in_ucs2);
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