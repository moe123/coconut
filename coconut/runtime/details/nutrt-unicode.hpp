//
// nutrt-unicode.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-allocators.hpp>

#ifndef COCONUT_RUNTIME_UNICODE_HPP
#define COCONUT_RUNTIME_UNICODE_HPP

namespace coconut
{ namespace runtime
{ namespace unicode
{
	
#pragma mark -
	
template <typename CharInT, typename CharOutT, typename CodecvtT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void __conv_from_bytes(
	const std::basic_string<CharInT, std::char_traits<CharInT>, allocators::standard<CharInT> > & src,
	std::basic_string<CharOutT, std::char_traits<CharOutT>, allocators::standard<CharOutT> > & dest
) {
	std::wstring_convert<CodecvtT, CharOutT> conv;
	dest = std::move(conv.from_bytes(src));
}

template <typename CharInT, typename CharOutT, typename CodecvtT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void __conv_to_bytes(
	const std::basic_string<CharInT, std::char_traits<CharInT>, allocators::standard<CharInT> > & src,
	std::basic_string<CharOutT, std::char_traits<CharOutT>, allocators::standard<CharOutT> > & dest
) {
	std::wstring_convert<CodecvtT, CharInT> conv;
	dest = std::move(conv.to_bytes(src));
}

#pragma mark -
#pragma mark -

namespace
{
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
static std::size_t __utf8_glyph_length(const unsigned char & c) noexcept(false)
{
	std::int32_t cp = c;
	if (cp < 0x80) { return 1; }
	else if ((cp & 0xE0) == 0xC0) { return 2; }
	else if ((cp & 0xF0) == 0xE0) { return 3; }
	else if ((cp & 0xF8) == 0xF0) { return 4; }
	else if ((cp & 0xFC) == 0xF8) { return 5; }
	else if ((cp & 0xFE) == 0xFC) { return 6; }
	throw std::runtime_error("invalid UTF-8 codepoint");
	return 0;
}
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
static std::size_t __utf8_glyph_offset(const unsigned char & c) noexcept(false)
{ return __utf8_glyph_length(c) -1; }

} /* EONS */
	
#pragma mark -

template <typename Char8T
	, typename Traits = std::char_traits<Char8T>
	, typename Allocator = allocators::standard<Char8T>
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr,
	std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool __utf8_valid(const Char8T (&in)[N]) {
	for (std::size_t i = 0 ; i < N ; i++) {
		if (__utf8_glyph_length(
			weak_cast<const unsigned char &>(in[i])) == 0
		) {
			return false;
		}
	}
	return true;
}

	
template <typename Char8T
	, typename Traits = std::char_traits<Char8T>
	, typename Allocator = allocators::standard<Char8T>
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::size_t __utf8_glyph_count(
	const std::basic_string<Char8T, Traits, Allocator> & in_utf8
) {
	std::size_t i = 0, j = 0;
	for (; i < in_utf8.size() ; j++) { i += __utf8_glyph_length(in_utf8[i]); }
	return j;
}
	
template <typename Char8T
	, typename Traits = std::char_traits<Char8T>
	, typename Allocator = allocators::standard<Char8T>
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char), void
>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::size_t __utf8_glyph_split(
	std::vector<
		std::basic_string<Char8T, Traits, Allocator>,
		typename std::vector<
			std::basic_string<Char8T, Traits, Allocator>
		>::allocator_type
	> & out,
	const std::basic_string<Char8T, Traits, Allocator> & in_utf8
) {
	std::size_t i = 0, first = 0, last = 0;
	for (; i < in_utf8.size() ; ) {
		first = i;
		last = __utf8_glyph_length(in_utf8[i]);
		i += last;
		out.push_back(in_utf8.substr(first, last));
	}
	return out.size();
}
	
template <typename Char8T
	, typename Traits = std::char_traits<Char8T>
	, typename Allocator = allocators::standard<Char8T>
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<Char8T, Traits, Allocator> __utf8_substr(
	const std::basic_string<Char8T, Traits, Allocator> & in_utf8,
	std::size_t pos,
	std::size_t len = std::basic_string<Char8T, Traits, Allocator>::npos
) {
	std::size_t i, j, k;
	std::size_t ln = len, sz = in_utf8.size();
	std::size_t first, last;
	std::size_t npos = std::basic_string<Char8T, Traits, Allocator>::npos;
	
	first = npos;
	last = npos;
	
	if (ln == 0 || !sz || pos >= sz) { return {}; }
	if (ln == npos) { ln = sz - pos; }
	
	for (k = 0, i = 0, j = sz; i < j; i++, k++) {
		if (k == pos) { first = i; }
		if (k <= pos + ln || ln == npos) { last = i; }
		i += __utf8_glyph_offset(in_utf8[i]);
	}
	
	if (k <= pos + ln || ln == npos) { last = i; }
	if (first == npos || last == npos) { return {}; }
	
	return in_utf8.substr(first, last - first);
}

#pragma mark -
#pragma mark -
	
template <typename Char8T
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool __utf8_have_bom(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & in_utf8
) {
	bool have_bom = false;
	if (in_utf8.size() >= 3) {
		if (in_utf8[0] == 0xEF && in_utf8[1] == 0xBB &&  in_utf8[2] == 0xBF) {
			have_bom = true;
		}
	}
	return have_bom;
}
	
template <typename Char8T
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void __utf8_add_bom(
	std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & in_utf8
) { if (!__utf8_have_bom(in_utf8)) { in_utf8.insert(0, u8"\xEF\xBB\xBF"); } }
	
template <typename Char8T
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void __utf8_del_bom(
	std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & in_utf8
) { if (__utf8_have_bom(in_utf8)) { in_utf8.erase(0, 3); } }
	
template <typename Char8T
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void __utf8_bom(
	std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & in_utf8,
	unicode_option option
) {
	switch (option)
	{
		case unicode_conv_del_gen_bom:
		case unicode_conv_gen_bom:
			__utf8_add_bom(in_utf8);
		break;
		default:
			__utf8_del_bom(in_utf8);
		break;
	}
}

#pragma mark -
#pragma mark -
	
namespace
{
	
template <typename Char8T = char
	, typename Char16T = char16_t
	, typename CodecvtT = std::codecvt_utf8_utf16<Char16T>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const byteorder_type __utf16_storage_endianess(
	Char8T * no_param1 = nullptr,
	Char16T * no_param2 = nullptr
) {
	COCONUT_UNUSED(no_param1);
	COCONUT_UNUSED(no_param2);
	
	std::basic_string<
		Char8T,
		std::char_traits<Char8T>,
		allocators::standard<Char8T>
	> src(u8"\xEF\xBB\xBF");
	
	std::basic_string<
		Char16T,
		std::char_traits<Char16T>,
		allocators::standard<Char16T>
	> dest;
	
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
	
	if (dest.size()) {
		if (dest[0] == 0xFEFF) {
			return byteorder_bigendian;
		} else if (dest[0] == 0xFFFE) {
			return byteorder_littleendian;
		}
	}
	
	return byteorder_unknown;
}
	
template <typename Char8T = char
	, typename Char32T = char16_t
	, typename CodecvtT = std::codecvt_utf8<Char32T>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
const byteorder_type __utf32_storage_endianess(
	Char8T * no_param1 = nullptr,
	Char32T * no_param2 = nullptr
) {
	COCONUT_UNUSED(no_param1);
	COCONUT_UNUSED(no_param2);
	
	std::basic_string<
		Char8T,
		std::char_traits<Char8T>,
		allocators::standard<Char8T>
	> src(u8"\xEF\xBB\xBF");
	
	std::basic_string<
		Char32T,
		std::char_traits<Char32T>,
		allocators::standard<Char32T>
	> dest;
	
	__conv_from_bytes<Char8T, Char32T, CodecvtT>(src, dest);
	
	if (dest.size()) {
		if (dest[0] == 0x0000FEFF) {
			return byteorder_bigendian;
		} else if (dest[0] == 0xFFFE0000) {
			return byteorder_littleendian;
		}
	}
	
	return byteorder_unknown;
}

/* toll-free bridge between local STL priv-impl + ICU backend + win32-wide */
static byteorder_type const _utf16_storage = __utf16_storage_endianess();
static byteorder_type const _utf32_storage = __utf32_storage_endianess();
	
} /* EONS */

#pragma mark -
#pragma mark -

template <typename Char16T
	, typename std::enable_if<
		sizeof(Char16T) == sizeof(char16_t), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
byteorder_type __utf16_have_bom(
	const std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & in_utf16
) {
	if (in_utf16.size()) {
		if (in_utf16[0] == 0xFEFF) {
			return byteorder_bigendian;
		} else if (in_utf16[0] == 0xFFFE) {
			return byteorder_littleendian;
		}
	}
	return byteorder_platform;
}
	
template <typename Char16T
	, typename std::enable_if<
		sizeof(Char16T) == sizeof(char16_t), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
byteorder_type __utf16_add_bom(
	const std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & in_utf16,
	byteorder_type byteorder
) {
	byteorder_type ret = __utf16_have_bom(in_utf16);
	if (ret != byteorder_platform) {
		if (ret != byteorder) {
			throw;
		}
	} else {
		if (byteorder == byteorder_bigendian) {
			in_utf16.insert(0, Char16T(0xFEFF), 1);
			ret = byteorder_bigendian;
		} else if (byteorder == byteorder_littleendian) {
			in_utf16.insert(0, Char16T(0xFFFE), 1);
			ret = byteorder_littleendian;
		} else {
#if defined(__MICROSOFT__)
			ret = byteorder_littleendian;
#else
			ret = byteorder_bigendian;
#endif
			byteorder_type storage = _utf16_storage;
			
			COCONUT_UNUSED(storage);
			
			if (byteorder == byteorder_bigendian) {
				in_utf16.insert(0, Char16T(0xFEFF), 1);
				ret = byteorder_bigendian;
			} else if (byteorder == byteorder_littleendian) {
				in_utf16.insert(0, Char16T(0xFFFE), 1);
				ret = byteorder_littleendian;
			}
			
			throw;
		}
	}
	return ret;
}
	
template <typename Char16T
	, typename std::enable_if<
		sizeof(Char16T) == sizeof(char16_t), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void __utf16_del_bom(
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & in_utf16
) {
	byteorder_type ret = __utf16_have_bom(in_utf16);
	if (ret == byteorder_bigendian || ret == byteorder_littleendian) {
		in_utf16.erase(0, 1);
	}
}
	
template <typename Char16T
	, typename std::enable_if<
		sizeof(Char16T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void __utf16_bom(
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & in_utf16,
	unicode_option option
) {
	switch (option)
	{
		case unicode_conv_del_gen_bom:
		case unicode_conv_gen_bom:
			__utf16_add_bom(in_utf16);
		break;
		default:
			__utf16_del_bom(in_utf16);
		break;
	}
}

#pragma mark -
#pragma mark -

template <typename Char16T, typename Char8T
	, typename std::enable_if<
		sizeof(Char16T) == sizeof(char16_t) &&
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_utf16_to_utf8(
	const std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & src,
	std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & dest,
	unicode_option option
) {
	using CodecvtT = std::codecvt_utf8_utf16<Char16T>;
	__conv_to_bytes<Char16T, Char8T, CodecvtT>(src, dest);
	__utf8_bom<Char8T>(dest, option);
}

template <typename Char16T, typename Char8T
	, typename std::enable_if<
		sizeof(Char16T) == sizeof(char16_t) &&
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_utf16_to_utf8(
	const std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & src,
	std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & dest
) {
	using CodecvtT = std::codecvt_utf8_utf16<Char16T>;
	__conv_to_bytes<Char16T, Char8T, CodecvtT>(src, dest);
}

#pragma mark -
	
template <typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_default,
void>::type _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8_utf16<Char16T>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
template <typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_del_gen_bom,
void>::type _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest
) {
	/*using CodecvtT = std::codecvt_utf8_utf16<
		Char16T, 0x10FFFF, std::codecvt_mode(std::consume_header|std::generate_header)
	>;*/
	using CodecvtT = std::codecvt_utf8_utf16<Char16T>;
	if (__utf8_have_bom(src)) {
		__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
	} else {
		std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > _src(src);
		__utf8_add_bom(_src);
		__conv_from_bytes<Char8T, Char16T, CodecvtT>(_src, dest);
	}
}
	
template <typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_del_bom,
void>::type _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest
) {
	/*
	using CodecvtT = std::codecvt_utf8_utf16<
		Char16T, 0x10FFFF, std::codecvt_mode(std::consume_header)
	>;
	*/
	using CodecvtT = std::codecvt_utf8_utf16<Char16T>;
	if (__utf8_have_bom(src)) {
		std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > _src(src);
		__utf8_del_bom(_src);
		__conv_from_bytes<Char8T, Char16T, CodecvtT>(_src, dest);
	} else {
		__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
	}
}
	
template <typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_gen_bom,
void>::type _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest
) {
	/*
	using CodecvtT = std::codecvt_utf8_utf16<
		Char16T, 0x10FFFF, std::codecvt_mode(std::generate_header)
	>;
	*/
	using CodecvtT = std::codecvt_utf8_utf16<Char16T>;
	if (__utf8_have_bom(src)) {
		__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
	} else {
		std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > _src(src);
		__utf8_add_bom(_src);
		__conv_from_bytes<Char8T, Char16T, CodecvtT>(_src, dest);
	}
}
	
#pragma mark -

template <typename Char8T, typename Char16T
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char) &&
		sizeof(Char16T) == sizeof(char16_t), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_utf8_to_utf16(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest,
	unicode_option option
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

#pragma mark -
#pragma mark -

template <typename Char16T, typename Char8T
	, typename std::enable_if<
		sizeof(Char16T) == sizeof(char16_t) &&
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_ucs2_to_utf8(
	const std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & src,
	std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & dest,
	unicode_option option
) {
	using CodecvtT = std::codecvt_utf8<Char16T>;
	__conv_to_bytes<Char16T, Char8T, CodecvtT>(src, dest);
	__utf8_bom<Char8T>(dest, option);
}

template <typename Char16T, typename Char8T
	, typename std::enable_if<
		sizeof(Char16T) == sizeof(char16_t) &&
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_ucs2_to_utf8(
	const std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & src,
	std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<Char16T>;
	__conv_to_bytes<Char16T, Char8T, CodecvtT>(src, dest);
}
	
#pragma mark -
	
template <typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_default,
void>::type _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<Char16T>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
	
template <typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_del_gen_bom,
void>::type _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<
		Char16T, 0x10FFFF, std::codecvt_mode(std::consume_header|std::generate_header)
	>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
template <typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_del_bom,
void>::type _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<
		Char16T, 0x10FFFF, std::codecvt_mode(std::consume_header)
	>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}
	
template <typename Char8T, typename Char16T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char16T) == sizeof(char16_t) &&
	O == unicode_conv_gen_bom,
void>::type _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<
		Char16T, 0x10FFFF, std::codecvt_mode(std::generate_header)
	>;
	__conv_from_bytes<Char8T, Char16T, CodecvtT>(src, dest);
}

template <typename Char8T, typename Char16T
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char) &&
		sizeof(Char16T) == sizeof(char16_t), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_utf8_to_ucs2(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char16T, std::char_traits<Char16T>, allocators::standard<Char16T> > & dest,
	unicode_option option
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

#pragma mark -
#pragma mark -

template <typename Char32T, typename Char8T
	, typename std::enable_if<
		sizeof(Char32T) == sizeof(char32_t) &&
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_ucs4_to_utf8(
	const std::basic_string<Char32T, std::char_traits<Char32T>, allocators::standard<Char32T> > & src,
	std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & dest,
	unicode_option option
) {
	using CodecvtT = std::codecvt_utf8<Char32T>;
	__conv_to_bytes<Char32T, Char8T, CodecvtT>(src, dest);
	__utf8_bom<Char8T>(dest, option);
}

template <typename Char32T, typename Char8T
	, typename std::enable_if<
		sizeof(Char32T) == sizeof(char32_t) &&
		sizeof(Char8T) == sizeof(char), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_ucs4_to_utf8(
	const std::basic_string<Char32T, std::char_traits<Char32T>, allocators::standard<Char32T> > & src,
	std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<Char32T>;
	__conv_to_bytes<Char32T, Char8T, CodecvtT>(src, dest);
}
	
#pragma mark -
	
template <typename Char8T, typename Char32T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char32T) == sizeof(char32_t) &&
	O == unicode_conv_default,
void>::type _conv_utf8_to_ucs4(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char32T, std::char_traits<Char32T>, allocators::standard<Char32T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<Char32T>;
	__conv_from_bytes<Char8T, Char32T, CodecvtT>(src, dest);
}
	
template <typename Char8T, typename Char32T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char32T) == sizeof(char32_t) &&
	O == unicode_conv_del_gen_bom,
void>::type _conv_utf8_to_ucs4(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char32T, std::char_traits<Char32T>, allocators::standard<Char32T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<
		Char32T, 0x10FFFF, std::codecvt_mode(std::consume_header|std::generate_header)
	>;
	__conv_from_bytes<Char8T, Char32T, CodecvtT>(src, dest);
}
	
template <typename Char8T, typename Char32T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char32T) == sizeof(char32_t) &&
	O == unicode_conv_del_bom,
void>::type _conv_utf8_to_ucs4(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char32T, std::char_traits<Char32T>, allocators::standard<Char32T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<
		Char32T, 0x10FFFF, std::codecvt_mode(std::consume_header)
	>;
	__conv_from_bytes<Char8T, Char32T, CodecvtT>(src, dest);
}
	
template <typename Char8T, typename Char32T, unicode_option O>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(Char8T) == sizeof(char) &&
	sizeof(Char32T) == sizeof(char32_t) &&
	O == unicode_conv_gen_bom,
void>::type _conv_utf8_to_ucs4(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char32T, std::char_traits<Char32T>, allocators::standard<Char32T> > & dest
) {
	using CodecvtT = std::codecvt_utf8<
		Char32T, 0x10FFFF, std::codecvt_mode(std::generate_header)
	>;
	__conv_from_bytes<Char8T, Char32T, CodecvtT>(src, dest);
}

template <typename Char8T, typename Char32T
	, typename std::enable_if<
		sizeof(Char8T) == sizeof(char) &&
		sizeof(Char32T) == sizeof(char32_t), void
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void _conv_utf8_to_ucs4(
	const std::basic_string<Char8T, std::char_traits<Char8T>, allocators::standard<Char8T> > & src,
	std::basic_string<Char32T, std::char_traits<Char32T>, allocators::standard<Char32T> > & dest,
	unicode_option option
) {
	switch (option)
	{
		case unicode_conv_del_gen_bom:
			_conv_utf8_to_ucs4<Char8T, Char32T, unicode_conv_del_gen_bom>(src, dest);
		break;
		case unicode_conv_del_bom:
			_conv_utf8_to_ucs4<Char8T, Char32T, unicode_conv_del_bom>(src, dest);
		break;
		case unicode_conv_gen_bom:
			_conv_utf8_to_ucs4<Char8T, Char32T, unicode_conv_gen_bom>(src, dest);
		break;
		default:
			_conv_utf8_to_ucs4<Char8T, Char32T, unicode_conv_default>(src, dest);
		break;
	}
}
	
#pragma mark -
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_utf16(
	const std::string & in_utf8,
	unicode_option option
) {
	std::u16string utf16_out;
	
	using Char8T = std::string::value_type;
	using Char16T = std::u16string::value_type;
	
	_conv_utf8_to_utf16<Char8T, Char16T>(in_utf8, utf16_out, option);
	return utf16_out;
}
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_utf16(const std::string & in_utf8)
{
	std::u16string utf16_out;
	
	using Char8T = std::string::value_type;
	using Char16T = std::u16string::value_type;
	
	_conv_utf8_to_utf16<Char8T, Char16T, unicode_conv_default>(in_utf8, utf16_out);
	return utf16_out;
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_ucs2(
	const std::string & in_utf8,
	unicode_option option
) {
	std::u16string ucs2_out;
	
	using Char8T = std::string::value_type;
	using Char16T = std::u16string::value_type;
	
	_conv_utf8_to_ucs2<Char8T, Char16T>(in_utf8, ucs2_out, option);
	return ucs2_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string utf8_to_ucs2(const std::string & in_utf8) {
	std::u16string ucs2_out;
	
	using Char8T = std::string::value_type;
	using Char16T = std::u16string::value_type;
	
	_conv_utf8_to_ucs2<Char8T, Char16T, unicode_conv_default>(in_utf8, ucs2_out);
	return ucs2_out;
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u32string utf8_to_ucs4(
	const std::string & in_utf8,
	unicode_option option
) {
	std::u32string ucs4_out;
	
	using Char8T = std::string::value_type;
	using Char32T = std::u32string::value_type;
	
	_conv_utf8_to_ucs4<Char8T, Char32T>(in_utf8, ucs4_out, option);
	return ucs4_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u32string utf8_to_ucs4(const std::string & in_utf8)
{
	std::u32string ucs4_out;
	
	using Char8T = std::string::value_type;
	using Char32T = std::u32string::value_type;
	
	_conv_utf8_to_ucs4<Char8T, Char32T, unicode_conv_default>(in_utf8, ucs4_out);
	return ucs4_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u32string utf8_to_utf32(
	const std::string & in_utf8,
	unicode_option option
) { return utf8_to_ucs4(in_utf8, option); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u32string utf8_to_utf32(const std::string & in_utf8)
{ return utf8_to_ucs4(in_utf8); }
	
#pragma mark -
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string utf16_to_utf8(
	const std::u16string & utf16_in,
	unicode_option option
) {
	std::string utf8_out;
	
	using Char16T = std::u16string::value_type;
	using Char8T = std::string::value_type;
	
	_conv_utf16_to_utf8<Char16T, Char8T>(utf16_in, utf8_out, option);
	return utf8_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string utf16_to_utf8(const std::u16string & utf16_in)
{
	std::string utf8_out;
	
	using Char16T = std::u16string::value_type;
	using Char8T = std::string::value_type;
	
	_conv_utf16_to_utf8<Char16T, Char8T>(utf16_in, utf8_out);
	return utf8_out;
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string ucs2_to_utf8(
	const std::u16string & in_ucs2,
	unicode_option option
) {
	std::string utf8_out;
	
	using Char16T = std::u16string::value_type;
	using Char8T = std::string::value_type;
	
	_conv_ucs2_to_utf8<Char16T, Char8T>(in_ucs2, utf8_out, option);
	return utf8_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string ucs2_to_utf8(const std::u16string & in_ucs2)
{
	std::string utf8_out;
	
	using Char16T = std::u16string::value_type;
	using Char8T = std::string::value_type;
	
	_conv_ucs2_to_utf8<Char16T, Char8T>(in_ucs2, utf8_out);
	return utf8_out;
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string ucs2_to_utf16(
	const std::u16string & in_ucs2,
	unicode_option option
)
{ return utf8_to_utf16(ucs2_to_utf8(in_ucs2, unicode_conv_del_bom), option); }
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::u16string ucs2_to_utf16(const std::u16string & in_ucs2)
{ return utf8_to_utf16(ucs2_to_utf8(in_ucs2, unicode_conv_del_bom)); }

#pragma mark -
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string ucs4_to_utf8(
	const std::u32string & in_ucs4,
	unicode_option option
) {
	std::string utf8_out;
	
	using Char32T = std::u32string::value_type;
	using Char8T = std::string::value_type;
	
	_conv_ucs4_to_utf8<Char32T, Char8T>(in_ucs4, utf8_out, option);
	return utf8_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string ucs4_to_utf8(const std::u32string & in_ucs4)
{
	std::string utf8_out;
	
	using Char32T = std::u32string::value_type;
	using Char8T = std::string::value_type;
	
	_conv_ucs4_to_utf8<Char32T, Char8T>(in_ucs4, utf8_out);
	return utf8_out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string utf32_to_utf8(
	const std::u32string & in_utf32,
	unicode_option option
) { return ucs4_to_utf8(in_utf32, option); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string utf32_to_utf8(const std::u32string & in_utf32)
{ return ucs4_to_utf8(in_utf32); }

#pragma mark -
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string & utf8_add_bom(std::string & in_utf8)
{ __utf8_add_bom(in_utf8); return in_utf8; }
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string & utf8_del_bom(std::string & in_utf8)
{ __utf8_del_bom(in_utf8); return in_utf8; }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string & utf8_hav_bom(std::string & in_utf8)
{ __utf8_have_bom(in_utf8); return in_utf8; }
	
}}} /* EONS */

#endif /* !COCONUT_RUNTIME_UNICODE_HPP */

/* EOF */