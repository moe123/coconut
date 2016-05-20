//
// nutrt-algorithm.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_ALGORITHM_HPP
#define COCONUT_RUNTIME_ALGORITHM_HPP

namespace coconut
{ namespace runtime
{ namespace algorithm
{
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const std::basic_string<CharT, Traits, Allocator> & needle
) {
	return needle.size() <= haystack.size() &&
		std::equal(needle.cbegin(), needle.cend(), haystack.cbegin());
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, Traits, Allocator> & needle
) {
	return starts_with<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		needle
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const CharT (&needle)[N]
) {
	return starts_with<CharT, Traits, Allocator>(
		haystack,
		std::basic_string<CharT, Traits, Allocator>(needle)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	const CharT (&haystack)[N1],
	const CharT (&needle)[N2]
) {
	return starts_with<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		std::basic_string<CharT, Traits, Allocator>(needle)
	);
}

template <typename InputIterT1, typename InputIterT2
	, typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, typename std::enable_if<
		std::integral_constant<bool,
			!tag_is_reverse_iterator<InputIterT1>::value &&
			!tag_is_reverse_iterator<InputIterT2>::value
		>::value
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	InputIterT1 && first_haystack,
	InputIterT2 && first_needle,
	InputIterT2 && last_needle
) { return std::equal(first_needle, last_needle, first_haystack); }

template <typename InputIterT
	, typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	InputIterT && first_haystack,
	const std::basic_string<CharT, Traits, Allocator> & needle
) {
	return starts_with<InputIterT, CharT, Traits, Allocator>(
		std::forward<InputIterT>(first_haystack),
		needle.cbegin(),
		needle.cend()
	);
}

template <typename InputIterT
	, typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	InputIterT && first_haystack,
	const CharT (&needle)[N]
) {
	return starts_with<InputIterT, CharT, Traits, Allocator>(
		std::forward<InputIterT>(first_haystack),
		std::basic_string<CharT, Traits, Allocator>(needle)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const std::basic_string<CharT, Traits, Allocator> & needle
) {
	return needle.size() <= haystack.size() &&
		std::equal(needle.crbegin(), needle.crend(), haystack.crbegin());
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, Traits, Allocator> & needle
) {
	return ends_with<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		needle
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const CharT (&needle)[N]
) {
	return ends_with<CharT, Traits, Allocator>(
		haystack,
		std::basic_string<CharT, Traits, Allocator>(needle)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	const CharT (&haystack)[N1],
	const CharT (&needle)[N2]
) {
	return ends_with<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		std::basic_string<CharT, Traits, Allocator>(needle)
	);
}

template <typename InputIterT1, typename InputIterT2
	, typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, typename std::enable_if<
		std::integral_constant<bool,
			!!tag_is_reverse_iterator<InputIterT1>::value &&
			!!tag_is_reverse_iterator<InputIterT2>::value
		>::value
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	InputIterT1 && first_haystack,
	InputIterT2 && first_needle,
	InputIterT2 && last_needle
) { return std::equal(first_needle, last_needle, first_haystack); }

template <typename InputIterT
	, typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	InputIterT && first_haystack,
	const std::basic_string<CharT, Traits, Allocator> & needle
) {
	return starts_with<InputIterT, CharT, Traits, Allocator>(
		std::forward<InputIterT>(first_haystack),
		needle.crbegin(),
		needle.crend()
	);
}

template <typename InputIterT
	, typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	InputIterT && first_haystack,
	const CharT (&needle)[N]
) {
	return starts_with<InputIterT, CharT, Traits, Allocator>(
		std::forward<InputIterT>(first_haystack),
		std::basic_string<CharT, Traits, Allocator>(needle)
	);
}

template <typename CharT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool is_alpha(CharT a)
{
	std::locale loc;
	return std::use_facet< std::ctype<CharT> >(loc).is(std::ctype<CharT>::alpha, a);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool is_ascii(const std::basic_string<CharT, Traits, Allocator> & in)
{
	using const_iter = typename std::basic_string<CharT, Traits, Allocator>::const_iterator;
	for (const_iter it = in.cbegin(); it!= in.cend(); ++it) {
		if (!((reinterpret_cast<std::int32_t>(*it) & ~0x7F) == 0)) { return false; }
	}
	return true;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> & ltrim(
	std::basic_string<CharT, Traits, Allocator> & s
) {
	s.erase(s.begin(), std::find_if(
		s.begin(), s.end(), std::not1(
			std::ptr_fun<std::int32_t, std::int32_t>(std::isspace)
	)));
	return s;
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> ltrim_copy(
	const std::basic_string<CharT, Traits, Allocator> & s
) {
	std::basic_string<CharT, Traits, Allocator> s_(s.data(), s.size());
	return ltrim<CharT, Traits, Allocator>(s_);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> & rtrim(
	std::basic_string<CharT, Traits, Allocator> & s
) {
	s.erase(std::find_if(
		s.rbegin(), s.rend(), std::not1(
			std::ptr_fun<std::int32_t, std::int32_t>(std::isspace)
	)).base(), s.end());
	return s;
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> rtrim_copy(
	const std::basic_string<CharT, Traits, Allocator> & s
) {
	std::basic_string<CharT, Traits, Allocator> s_(s.data(), s.size());
	return rtrim<CharT, Traits, Allocator>(s_);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> & trim(
	std::basic_string<CharT, Traits, Allocator> & s
) { return ltrim<CharT, Traits, Allocator>(rtrim<CharT, Traits, Allocator>(s)); }
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> trim_copy(
	const std::basic_string<CharT, Traits, Allocator> & s
) {
	std::basic_string<CharT, Traits, Allocator> s_(s.data(), s.size());
	return trim<CharT, Traits, Allocator>(s_);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> & to_upper(
	std::basic_string<CharT, Traits, Allocator> & in
) {
	std::locale loc;
	std::transform(
		in.begin(),
		in.end(),
		in.begin(), std::bind1st(
			std::mem_fun(&std::ctype<CharT>::toupper),
			&std::use_facet< std::ctype<CharT> >(loc)
		)
	);
	return in;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> to_upper_copy(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	std::basic_string<CharT, Traits, Allocator> out(in.data(), in.size());
	return to_upper<CharT, Traits, Allocator>(out);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> & to_lower(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	std::locale loc;
	std::transform(
		in.begin(),
		in.end(),
		in.begin(), std::bind1st(
			std::mem_fun(&std::ctype<CharT>::tolower),
			&std::use_facet< std::ctype<CharT> >(loc)
		)
	);
	return in;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> to_lower_copy(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	std::basic_string<CharT, Traits, Allocator> out(in.data(), in.size());
	return to_lower<CharT, Traits, Allocator>(out);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = std::allocator<CharT>
	, typename Allocator2 = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t index_of(
		const std::basic_string<CharT, Traits, Allocator1> haystack,
		const std::basic_string<CharT, Traits, Allocator2> needle
) {
	using size_type = typename std::basic_string<CharT, Traits, Allocator1>::size_type;
	
	if (!haystack.size() || (needle.size() > haystack.size())) {
		return -1;
	}
	size_type idx = haystack.find(needle);
	return ((
		idx != std::basic_string<CharT, Traits, Allocator1>::npos
	) ? weak_cast<std::ptrdiff_t>(idx) : -1);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>,
	std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t index_of(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, Traits, Allocator> needle
) {
	return index_of<CharT, Traits, no_allocator<CharT>, Allocator>(
		std::basic_string<CharT, Traits, no_allocator<CharT> >(haystack),
		needle
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>,
	std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t index_of(
	const std::basic_string<CharT, Traits, Allocator> haystack,
	const CharT (&needle)[N]
) {
	return index_of<CharT, Traits, Allocator, no_allocator<CharT>>(
		haystack,
		std::basic_string<CharT, Traits, no_allocator<CharT> >(needle)
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>,
	std::size_t N1,
	std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t index_of(
	const CharT (&haystack)[N1],
	const CharT (&needle)[N2]
) {
	return index_of<CharT, Traits, no_allocator<CharT>, no_allocator<CharT> >(
		std::basic_string<CharT, Traits, no_allocator<CharT> >(haystack),
		std::basic_string<CharT, Traits, no_allocator<CharT> >(needle)
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = std::allocator<CharT>
	, typename Allocator2 = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t last_index_of(
	const std::basic_string<CharT, Traits, Allocator1> haystack,
	const std::basic_string<CharT, Traits, Allocator2> needle
) {
	using const_iter = typename std::basic_string<CharT, Traits, Allocator1>::const_iterator;
	
	if (!haystack.size() || (needle.size() > haystack.size())) {
		return -1;
	}
	const_iter it = std::find_end(
		haystack.cbegin(),
		haystack.cend(),
		needle.cbegin(),
		needle.cend()
	);
	return ((
		it != haystack.cend()
	) ? weak_cast<std::ptrdiff_t>(it - haystack.cbegin()) : -1);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>,
	std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t last_index_of(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, Traits, Allocator> needle
) {
	return last_index_of<CharT, Traits, no_allocator<CharT>, Allocator>(
		std::basic_string<CharT, Traits, no_allocator<CharT> >(haystack),
		needle
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>,
	std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t last_index_of(
	const std::basic_string<CharT, Traits, Allocator> haystack,
	const CharT (&needle)[N]
) {
	return last_index_of<CharT, Traits, Allocator, no_allocator<CharT> >(
		haystack,
		std::basic_string<CharT, Traits, no_allocator<CharT> >(needle)
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>,
	std::size_t N1,
	std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t last_index_of(
	const CharT (&haystack)[N1],
	const CharT (&needle)[N2]
) {
	return last_index_of<CharT, Traits, no_allocator<CharT>, no_allocator<CharT> >(
		std::basic_string<CharT, Traits, no_allocator<CharT> >(haystack),
		std::basic_string<CharT, Traits, no_allocator<CharT> >(needle)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool cmp(
	const std::basic_string<CharT, Traits, Allocator> & left,
	const std::basic_string<CharT, Traits, Allocator> & right
) { return left.compare(right); }

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool cmp(
	const CharT (&left)[N],
	const std::basic_string<CharT, Traits, Allocator> & right
) {
	return cmp<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(left),
		right
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool cmp(
	const std::basic_string<CharT, Traits, Allocator> & left,
	const CharT (&right)[N]
) {
	return cmp<CharT, Traits, Allocator>(
		left,
		std::basic_string<CharT, Traits, Allocator>(right)
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool cmp(
	const CharT (&left)[N1],
	const CharT (&right)[N2]
) {
	return cmp<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(left),
		std::basic_string<CharT, Traits, Allocator>(right)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	std::basic_string<CharT, Traits, Allocator> && left,
	std::basic_string<CharT, Traits, Allocator> && right
) {
	return cmp(
		to_upper<CharT, Traits, Allocator>(left),
		to_upper<CharT, Traits, Allocator>(right)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	std::basic_string<CharT, Traits, Allocator> && left,
	const std::basic_string<CharT, Traits, Allocator> & right
) {
	return cmp(
		to_upper<CharT, Traits, Allocator>(left),
		to_upper_copy<CharT, Traits, Allocator>(right)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	const std::basic_string<CharT, Traits, Allocator> & left,
	std::basic_string<CharT, Traits, Allocator> && right
) {
	return cmp(
		to_upper_copy<CharT, Traits, Allocator>(left),
		to_upper<CharT, Traits, Allocator>(right)
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	const std::basic_string<CharT, Traits, Allocator> & left,
	const std::basic_string<CharT, Traits, Allocator> & right
) {
	return cmp(
		to_upper_copy<CharT, Traits, Allocator>(left),
		to_upper_copy<CharT, Traits, Allocator>(right)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	const CharT (&left)[N],
	const std::basic_string<CharT, Traits, Allocator> & right
) {
	return icmp<CharT, Traits, Allocator>(
		std::move(std::basic_string<CharT, Traits, Allocator>(left)),
		right
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	const std::basic_string<CharT, Traits, Allocator> & left,
	const CharT (&right)[N]
) {
	return icmp<CharT, Traits, Allocator>(
		left,
		std::move(std::basic_string<CharT, Traits, Allocator>(right))
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	const CharT (&left)[N1],
	const CharT (&right)[N2]
) {
	return icmp<CharT, Traits, Allocator>(
		std::move(std::basic_string<CharT, Traits, Allocator>(left)),
		std::move(std::basic_string<CharT, Traits, Allocator>(right))
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char) &&
	(
		std::is_same<CharT, char>::value ||
		std::is_same<CharT, unsigned char>::value
	)
, bool>::type is_integer(
	const std::basic_string<CharT, Traits, Allocator> & in,
	bool is_unsigned = false
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex;
		if (is_unsigned) {
			regex.assign(weak_cast<const CharT *>(u8"[[:digit:]]+"));
		} else {
			regex.assign(weak_cast<const CharT *>(u8"(\\+|-)?[[:digit:]]+"));
		}
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(wchar_t) &&
	std::is_same<CharT, wchar_t>::value
, bool>::type is_integer(
	const std::basic_string<CharT, Traits, Allocator> & in,
	bool is_unsigned = false
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex;
		if (is_unsigned) {
			regex.assign(L"[[:digit:]]+");
		} else {
			regex.assign(L"(\\+|-)?[[:digit:]]+");
		}
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char16_t) &&
	std::is_same<CharT, char16_t>::value
, bool>::type is_integer(
	const std::basic_string<CharT, Traits, Allocator> & in,
	bool is_unsigned = false
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex;
		if (is_unsigned) {
			regex.assign(u"[[:digit:]]+");
		} else {
			regex.assign(u"(\\+|-)?[[:digit:]]+");
		}
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char32_t) &&
	std::is_same<CharT, char32_t>::value
, bool>::type is_integer(
	const std::basic_string<CharT, Traits, Allocator> & in,
	bool is_unsigned = false
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex;
		if (is_unsigned) {
			regex.assign(U"[[:digit:]]+");
		} else {
			regex.assign(U"(\\+|-)?[[:digit:]]+");
		}
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char) &&
	(
		std::is_same<CharT, char>::value ||
		std::is_same<CharT, unsigned char>::value
	)
, bool>::type is_number(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex(
			weak_cast<const CharT *>(u8"((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?")
		);
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(wchar_t) &&
	std::is_same<CharT, wchar_t>::value
, bool>::type is_number(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex(
			L"((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?"
		);
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char16_t) &&
	std::is_same<CharT, char16_t>::value
, bool>::type is_number(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex(
			u"((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?"
		);
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char32_t) &&
	std::is_same<CharT, char32_t>::value
, bool>::type is_number(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex(
			U"((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?"
		);
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char) &&
	(
		std::is_same<CharT, char>::value ||
		std::is_same<CharT, unsigned char>::value
	)
, bool>::type is_numeric(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex(
			weak_cast<const CharT *>(u8"((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?")
		);
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(wchar_t) &&
	std::is_same<CharT, wchar_t>::value
, bool>::type is_numeric(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex(
			L"((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?"
		);
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char16_t) &&
	std::is_same<CharT, char16_t>::value
, bool>::type is_numeric(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex(
			u"((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?"
		);
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char32_t) &&
	std::is_same<CharT, char32_t>::value
, bool>::type is_numeric(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	bool result;
	try {
		std::basic_regex<CharT, std::regex_traits<CharT> > regex(
			U"((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?"
		);
		result = std::regex_match(in, regex);
	}
	catch (std::regex_error e) { result = false; }
	return result;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, typename NumT
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> to_binary(const NumT & x)
{
	std::bitset<(sizeof(x) * CHAR_BIT)> bits(x);
	return bits. template to_string<CharT, Traits, Allocator>();
}

template <typename NumT
	, typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
NumT to_numeric(const std::basic_string<CharT, Traits, Allocator> & in)
{
	NumT t = 0;
	if (in.size() && is_numeric<CharT, Traits, Allocator>(in)) {
		std::basic_stringstream<CharT, Traits, Allocator> buf;
		buf << in;
		buf >> t;
	}
	return t;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, typename NumT
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> to_string(const NumT & n, std::size_t p = 6)
{
	std::basic_ostringstream<CharT, Traits, Allocator> os;
	os.setf(std::ios::fixed, std::ios::floatfield);
	os.precision(static_cast<std::streamsize>(p));
	os << n;
	return os.str();
}

template <typename InputIterT, typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void joiner(
	InputIterT && first,
	InputIterT && last,
	const std::basic_string<CharT, Traits, Allocator> & sep,
	std::basic_string<CharT, Traits, Allocator> & joined
) {
	std::basic_ostringstream<CharT, Traits, Allocator> os;

	if (first != last) {
		os << *first++;
	}
	while (first != last) {
		os << sep;
		os << *first++;
	}
	joined = std::move(os.str());
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void tokenizer(
	const std::basic_string<CharT, Traits, Allocator> & in,
	std::vector< std::basic_string<CharT, Traits, Allocator> > & tokens,
	const std::basic_string<CharT, Traits, Allocator> & delimiter)
{
	using value_type = typename std::vector<
		std::basic_string<CharT, Traits, Allocator>
	>::value_type;
	
	using size_type = typename std::vector<
		std::basic_string<CharT, Traits, Allocator>
	>::size_type;

	size_type pos, last_pos = 0;
	
	while (true) {
		pos = in.find_first_of(delimiter, last_pos);
		if (pos == std::basic_string<CharT, Traits, Allocator>::npos) {
			pos = in.length();
			if (pos != last_pos) {
				tokens.push_back(value_type(in.data() + last_pos,
					static_cast<size_type>(pos) - last_pos ));
			}
			break;
		} else {
			if (pos != last_pos) {
				tokens.push_back(value_type(in.data() + last_pos,
					static_cast<size_type>(pos) - last_pos ));
			}
		}
		last_pos = pos + 1;
	}
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::vector<
	std::basic_string<CharT, Traits, Allocator>
> split(
	const std::basic_string<CharT, Traits, Allocator> & in,
	const std::basic_string<CharT, Traits, Allocator> & delimiter
) {
	std::vector< std::basic_string<CharT, Traits, Allocator> > out;
	tokenizer<CharT, Traits, Allocator>(in, out, delimiter);
	return out;
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::vector<
	std::basic_string<CharT, Traits, Allocator>
> split(
		const CharT (&in)[N],
		const std::basic_string<CharT, Traits, Allocator> & delimiter
) {
	return split<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(in),
		delimiter
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::vector<
	std::basic_string<CharT, Traits, Allocator>
> split(
	const std::basic_string<CharT, Traits, Allocator> & in,
	const CharT (&delimiter)[N]
) {
	return split<CharT, Traits, Allocator>(
		in,
		std::basic_string<CharT, Traits, Allocator>(delimiter)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, typename USizeT = typename std::vector<
		std::basic_string<CharT, Traits, Allocator>
		, typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	>::size_type
	, typename SSizeT = std::ptrdiff_t
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::size_t explode(
	std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & out,
	const std::basic_string<CharT, Traits, Allocator> & delimiter,
	const std::basic_string<CharT, Traits, Allocator> & in,
	SSizeT limit = std::numeric_limits<SSizeT>::max()
) {
	USizeT begin = 0, end = 0;
	
	if (delimiter.empty()) {
		return 0;
	}
	if (limit == 0) {
		limit = 1;
	}
	if (in.find(delimiter) == std::basic_string<CharT, Traits, Allocator>::npos) {
		if (limit > 0) {
			out.push_back(in);
		}
		return out.size();
	}
	
	while (end != std::basic_string<CharT, Traits, Allocator>::npos) {
		if (limit > 0 && weak_cast<SSizeT>(out.size()) == limit - 1) {
			out.push_back(in.substr(begin));
			break;
		}
		USizeT substr_len = std::basic_string<CharT, Traits, Allocator>::npos;
		USizeT next_tok = std::basic_string<CharT, Traits, Allocator>::npos;
		end = in.find_first_of(delimiter, begin);
		if (end != std::basic_string<CharT, Traits, Allocator>::npos) {
			substr_len = end - begin;
			next_tok = end + delimiter.size();
		}
		out.push_back(in.substr(begin, substr_len));
		begin = next_tok;
	}
	if (limit < 0) {
		limit = std::abs(limit);
		if (limit < weak_cast<SSizeT>(out.size())) {
			out.resize(out.size() - weak_cast<USizeT>(limit));
		} else {
			out.clear();
		}
	}
	return out.size();
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::size_t explode(
	std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & out,
	const CharT (&delimiter)[N],
	const std::basic_string<CharT, Traits, Allocator> & in,
	int limit = std::numeric_limits<int>::max()
) {
	return explode<CharT, Traits, Allocator>(
		out,
		std::basic_string<CharT, Traits, Allocator>(delimiter),
		in,
		limit
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::size_t explode(
	std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & out,
	const std::basic_string<CharT, Traits, Allocator> & delimiter,
	const CharT (&in)[N],
	int limit = std::numeric_limits<int>::max()
) {
	return explode<CharT, Traits, Allocator>(
		out,
		delimiter,
		std::basic_string<CharT, Traits, Allocator>(in),
		limit
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::size_t explode(
	std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & out,
	const CharT (&delimiter)[N1],
	const CharT (&in)[N2],
	int limit = std::numeric_limits<int>::max()
) {
	return explode<CharT, Traits, Allocator>(
		out,
		std::basic_string<CharT, Traits, Allocator>(delimiter),
		std::basic_string<CharT, Traits, Allocator>(in),
		limit
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, template <
		typename
		, typename = std::allocator<
			std::basic_string<CharT
				, Traits
				, Allocator
			>
		>
	> class Container
	, typename std::enable_if<
		std::is_same<
			Container< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
			, std::vector< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
		>::value ||
		std::is_same<
			Container< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
			, std::list< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
		>::value ||
		std::is_same<
			Container< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
			, std::set< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
		>::value ||
		std::is_same<
			Container< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
			, std::deque< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
		>::value
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> join(
	const Container< std::basic_string<CharT, Traits, Allocator>,
		typename Container<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & parts,
	const std::basic_string<CharT, Traits, Allocator> & separator
) {
	std::basic_string<CharT, Traits, Allocator> joined;
	joiner<typename Container<
			std::basic_string<CharT, Traits, Allocator>,
			typename Container<
				std::basic_string<CharT, Traits, Allocator>
			>::allocator_type
		>::const_iterator,
		CharT,
		Traits,
		Allocator
	>(parts.cbegin(), parts.cend(), separator, joined);
	return joined;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = std::allocator<CharT>
	, template <
		typename
		, typename = std::allocator<
			std::basic_string<CharT
				, Traits
				, Allocator
			>
		>
	> class Container
	, std::size_t N
	, typename std::enable_if<
		std::is_same<
			Container< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
			, std::vector< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
		>::value ||
		std::is_same<
			Container< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
			, std::list< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
		>::value ||
		std::is_same<
			Container< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
			, std::set< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
		>::value ||
		std::is_same<
			Container< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
			, std::deque< std::basic_string<CharT, Traits, Allocator>
				, typename Container<
					std::basic_string<CharT, Traits, Allocator>
				>::allocator_type
			>
		>::value
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> join(
	const Container< std::basic_string<CharT, Traits, Allocator>,
		typename Container<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & parts,
	const CharT (&separator)[N]
) {
	return join<CharT, Traits, Allocator, Container>(
		parts,
		std::basic_string<CharT, Traits, Allocator>(separator)
	);
}

template <std::size_t N, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string format(const char (&fmt)[N], ArgsT &&... args)
{
	int sz = std::snprintf(nullptr, 0, fmt, std::forward<ArgsT>(args)...);
	if (sz) {
		std::vector<char> buf(static_cast<std::size_t>(sz));
		std::snprintf(buf.data(), buf.size(), fmt, std::forward<ArgsT>(args)...);
		if (buf.back() == '\0') { buf.pop_back(); }
		return {buf.begin(), buf.end()};
	}
	return {};
}
	
template <typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string format(const std::string & fmt, ArgsT &&... args)
{ return format(fmt.c_str(), std::forward<ArgsT>(args)...); }
	
template <std::size_t N, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void print(std::ostream & os, const char (&fmt)[N], ArgsT &&... args)
{ os << format(fmt, std::forward<ArgsT>(args)...); }
	
template <typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void print(std::ostream & os, const std::string & fmt, ArgsT &&... args)
{ os << format(fmt.c_str(), std::forward<ArgsT>(args)...); }
	
template <std::size_t N, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void print_stderr(const char (&fmt)[N], ArgsT &&... args)
{
#if defined(__MICROSOFT__)
	const char _endl[3] = "\r\n";
#else
	const char _endl = '\n';
#endif
	std::cerr << std::nounitbuf;
	std::cerr << format(fmt, std::forward<ArgsT>(args)...) << _endl;
}
	
template <typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void print_stderr(const std::string & fmt, ArgsT &&... args)
{ print_stderr(fmt.c_str(), std::forward<ArgsT>(args)...); }

template <std::size_t N, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void print_stdout(const char (&fmt)[N], ArgsT &&... args)
{
#if defined(__MICROSOFT__)
	const char _endl[3] = "\r\n";
#else
	const char _endl = '\n';
#endif
	std::cout << std::nounitbuf;
	std::cout << format(fmt, std::forward<ArgsT>(args)...) << _endl;
}
	
template <typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void print_stdout(const std::string & fmt, ArgsT &&... args)
{ print_stdout(fmt.c_str(), std::forward<ArgsT>(args)...); }
	
}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ALGORITHM_HPP */

/* EOF */