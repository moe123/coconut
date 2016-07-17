//
// nutrt-algorithms.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-unicode.hpp>

#ifndef COCONUT_RUNTIME_ALGORITHMS_HPP
#define COCONUT_RUNTIME_ALGORITHMS_HPP

namespace coconut
{ namespace runtime
{ namespace algorithms
{

#pragma mark -
	
template <typename CharT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
CharT toupper(const CharT & ch, std::locale loc = std::locale())
{
	return std::use_facet< std::ctype<CharT> >(loc).toupper(ch);
}
	
template <typename CharT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
CharT tolower(const CharT & ch, std::locale loc = std::locale())
{
	return std::use_facet< std::ctype<CharT> >(loc).tolower(ch);
}

#pragma mark -
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool istarts_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const std::basic_string<CharT, Traits, Allocator> & needle,
	std::locale loc = std::locale()
) {
	return needle.size() <= haystack.size() && std::equal(
		haystack.cbegin(),
		needle.cbegin(),
		needle.cend(),
		[&loc] (CharT ch1, CharT ch2) {
			return (toupper(ch1, loc) == toupper(ch2, loc));
		}
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool istarts_with(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, Traits, Allocator> & needle,
	std::locale loc = std::locale()
) {
	return istarts_with<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		needle,
		loc
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool istarts_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const CharT (&needle)[N],
	std::locale loc = std::locale()
) {
	return istarts_with<CharT, Traits, Allocator>(
		haystack,
		std::basic_string<CharT, Traits, Allocator>(needle),
		loc
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool istarts_with(
	const CharT (&haystack)[N1],
	const CharT (&needle)[N2],
	std::locale loc = std::locale()
) {
	return istarts_with<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		std::basic_string<CharT, Traits, Allocator>(needle),
		loc
	);
}
	
#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const std::basic_string<CharT, Traits, Allocator> & needle
) {
	return needle.size() <= haystack.size() && std::equal(
		haystack.cbegin(),
		needle.cbegin(),
		needle.cend()
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool iends_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const std::basic_string<CharT, Traits, Allocator> & needle,
	std::locale loc = std::locale()
) {
	return needle.size() <= haystack.size() && std::equal(
		haystack.crbegin(),
		needle.crbegin(),
		needle.crend(),
		[&loc] (CharT ch1, CharT ch2) {
			return (toupper(ch1, loc) == toupper(ch2, loc));
		}
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool iends_with(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, Traits, Allocator> & needle,
	std::locale loc = std::locale()
) {
	return iends_with<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		needle,
		loc
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool iends_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const CharT (&needle)[N],
	std::locale loc = std::locale()
) {
	return iends_with<CharT, Traits, Allocator>(
		haystack,
		std::basic_string<CharT, Traits, Allocator>(needle),
		loc
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool iends_with(
	const CharT (&haystack)[N1],
	const CharT (&needle)[N2],
	std::locale loc = std::locale()
) {
	return iends_with<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		std::basic_string<CharT, Traits, Allocator>(needle),
		loc
	);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const std::basic_string<CharT, Traits, Allocator> & needle
) {
	return needle.size() <= haystack.size() && std::equal(
		haystack.cbegin(),
		needle.cbegin(),
		needle.cend()
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -

template <typename CharT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool is_alpha(CharT a)
{
	std::locale loc;
	return std::use_facet< std::ctype<CharT> >(loc).is(std::ctype<CharT>::alpha, a);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> ltrim_copy(
	const std::basic_string<CharT, Traits, Allocator> & s
) {
	std::basic_string<CharT, Traits, Allocator> s_(s.data(), s.size());
	return ltrim<CharT, Traits, Allocator>(s_);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> rtrim_copy(
	const std::basic_string<CharT, Traits, Allocator> & s
) {
	std::basic_string<CharT, Traits, Allocator> s_(s.data(), s.size());
	return rtrim<CharT, Traits, Allocator>(s_);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> & trim(
	std::basic_string<CharT, Traits, Allocator> & s
) { return ltrim<CharT, Traits, Allocator>(rtrim<CharT, Traits, Allocator>(s)); }
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> trim_copy(
	const std::basic_string<CharT, Traits, Allocator> & s
) {
	std::basic_string<CharT, Traits, Allocator> s_(s.data(), s.size());
	return trim<CharT, Traits, Allocator>(s_);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> & to_upper(
	std::basic_string<CharT, Traits, Allocator> & in
) {
	std::locale loc;
	std::transform(
		in.begin(),
		in.end(),
		in.begin(),
		std::bind1st(
			std::mem_fun(&std::ctype<CharT>::toupper),
			&std::use_facet< std::ctype<CharT> >(loc)
		)
	);
	return in;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> to_upper_copy(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	std::basic_string<CharT, Traits, Allocator> out(in.data(), in.size());
	return to_upper<CharT, Traits, Allocator>(out);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> & to_lower(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	std::locale loc;
	std::transform(
		in.begin(),
		in.end(),
		in.begin(),
		std::bind1st(
			std::mem_fun(&std::ctype<CharT>::tolower),
			&std::use_facet< std::ctype<CharT> >(loc)
		)
	);
	return in;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> to_lower_copy(
	const std::basic_string<CharT, Traits, Allocator> & in
) {
	std::basic_string<CharT, Traits, Allocator> out(in.data(), in.size());
	return to_lower<CharT, Traits, Allocator>(out);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t ifind(
	const std::basic_string<CharT, Traits, Allocator> & haystack,
	const std::basic_string<CharT, Traits, Allocator> & needle
) {
	std::locale loc;
	
	using size_type = typename std::basic_string<CharT, Traits, Allocator>::size_type;
	using const_iter = typename std::basic_string<CharT, Traits, Allocator>::const_iterator;
	size_type npos = std::basic_string<CharT, Traits, Allocator>::npos;
	
	if (!haystack.size() || !needle.size() || (needle.size() > haystack.size())) {
		return npos;
	}
	
	const_iter it = std::search(
		haystack.cbegin(),
		haystack.cend(),
		needle.cbegin(),
		needle.cend(),
		[&loc] (CharT ch1, CharT ch2) {
			return (toupper(ch1, loc) == toupper(ch2, loc));
		}
	);
	
	return ((
		it == haystack.cend()
	) ? npos : weak_cast<std::ptrdiff_t>(std::distance<const_iter>(haystack.cbegin(), it)));
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = allocators::standard<CharT>
	, typename Allocator2 = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t first_index_of(
		const std::basic_string<CharT, Traits, Allocator1> haystack,
		const std::basic_string<CharT, Traits, Allocator2> needle
) {
	using size_type = typename std::basic_string<CharT, Traits, Allocator1>::size_type;
	
	if (!haystack.size() || !needle.size() || (needle.size() > haystack.size())) {
		return -1;
	}
	
	size_type idx = haystack.find(needle);
	return ((
		idx != std::basic_string<CharT, Traits, Allocator1>::npos
	) ? weak_cast<std::ptrdiff_t>(idx) : -1);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = allocators::standard<CharT>
	, typename Allocator2 = allocators::placement<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t first_index_of(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, Traits, Allocator1> needle
) {
	return first_index_of<CharT, Traits, Allocator2, Allocator1>(
		std::basic_string<CharT, Traits, Allocator2>(haystack),
		needle
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = allocators::standard<CharT>
	, typename Allocator2 = allocators::placement<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t first_index_of(
	const std::basic_string<CharT, Traits, Allocator1> haystack,
	const CharT (&needle)[N]
) {
	return first_index_of<CharT, Traits, Allocator1, Allocator2>(
		haystack,
		std::basic_string<CharT, Traits, Allocator2>(needle)
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::placement<CharT>,
	std::size_t N1,
	std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t first_index_of(
	const CharT (&haystack)[N1],
	const CharT (&needle)[N2]
) {
	return first_index_of<CharT, Traits, Allocator, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		std::basic_string<CharT, Traits, Allocator>(needle)
	);
}

#pragma mark -
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = allocators::standard<CharT>
	, typename Allocator2 = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t last_index_of(
	const std::basic_string<CharT, Traits, Allocator1> haystack,
	const std::basic_string<CharT, Traits, Allocator2> needle
) {
	using const_iter = typename std::basic_string<CharT, Traits, Allocator1>::const_iterator;
	
	if (!haystack.size() || !needle.size() || (needle.size() > haystack.size())) {
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
	) ? weak_cast<std::ptrdiff_t>(std::distance<const_iter>(haystack.cbegin(), it)) : -1);
	// weak_cast<std::ptrdiff_t>(it - haystack.cbegin()) : -1);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = allocators::standard<CharT>
	, typename Allocator2 = allocators::placement<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t last_index_of(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, Traits, Allocator1> needle
) {
	return last_index_of<CharT, Traits, Allocator2, Allocator1>(
		std::basic_string<CharT, Traits, Allocator2>(haystack),
		needle
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = allocators::standard<CharT>
	, typename Allocator2 = allocators::placement<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t last_index_of(
	const std::basic_string<CharT, Traits, Allocator1> haystack,
	const CharT (&needle)[N]
) {
	return last_index_of<CharT, Traits, Allocator1, Allocator2>(
		haystack,
		std::basic_string<CharT, Traits, Allocator2>(needle)
	);
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::placement<CharT>,
	std::size_t N1,
	std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::ptrdiff_t last_index_of(
	const CharT (&haystack)[N1],
	const CharT (&needle)[N2]
) {
	return last_index_of<CharT, Traits, Allocator, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(haystack),
		std::basic_string<CharT, Traits, Allocator>(needle)
	);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int cmp(
	const std::basic_string<CharT, Traits, Allocator> & left,
	const std::basic_string<CharT, Traits, Allocator> & right
) { return left.compare(right); }

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int cmp(
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
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int cmp(
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
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int cmp(
	const CharT (&left)[N1],
	const CharT (&right)[N2]
) {
	return cmp<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(left),
		std::basic_string<CharT, Traits, Allocator>(right)
	);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -

template <typename InputIterT, typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void tokenizer(
	std::vector< std::basic_string<CharT, Traits, Allocator> > & out,
	const std::basic_string<CharT, Traits, Allocator> & in,
	const std::basic_string<CharT, Traits, Allocator> & delimiter
) {
	using value_type = typename std::vector<
		std::basic_string<CharT, Traits, Allocator>
	>::value_type;
	
	using size_type = typename std::vector<
		std::basic_string<CharT, Traits, Allocator>
	>::size_type;

	size_type pos, last_pos = 0;
	size_type npos = std::basic_string<CharT, Traits, Allocator>::npos;
	
	while (true) {
		pos = in.find_first_of(delimiter, last_pos);
		if (pos == npos) {
			pos = in.length();
			if (pos != last_pos) {
				out.push_back(value_type(in.data() + last_pos,
					static_cast<size_type>(pos) - last_pos ));
			}
			break;
		} else {
			if (pos != last_pos) {
				out.push_back(value_type(in.data() + last_pos,
					static_cast<size_type>(pos) - last_pos ));
			}
		}
		last_pos = pos + 1;
	}
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::vector<
	std::basic_string<CharT, Traits, Allocator>
> split(
	const std::basic_string<CharT, Traits, Allocator> & in,
	const std::basic_string<CharT, Traits, Allocator> & delimiter
) {
	std::vector< std::basic_string<CharT, Traits, Allocator> > out;
	tokenizer<CharT, Traits, Allocator>(out, in, delimiter);
	return out;
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
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
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::vector<
	std::basic_string<CharT, Traits, Allocator>
> split(
	const CharT (&in)[N1],
	const CharT (&delimiter)[N2]
) {
	return split<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(in),
		std::basic_string<CharT, Traits, Allocator>(delimiter)
	);
}

#pragma mark -
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = allocators::standard<CharT>
	, typename Allocator2 = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::vector<
	std::basic_string<CharT, Traits, Allocator1>
> chunk_split(
	const std::basic_string<CharT, Traits, Allocator2> & in,
	std::size_t chunk_sz
) {
	std::vector< std::basic_string<CharT, Traits, Allocator1> > out;
	for (size_t i = 0; i < in.size(); i += chunk_sz) {
		out.push_back(in.substr(i, chunk_sz));
	}
	return out;
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator1 = allocators::standard<CharT>
	, typename Allocator2 = allocators::placement<CharT>
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::vector<
	std::basic_string<CharT, Traits, Allocator1>
> chunk_split(
	const CharT (&in)[N],
	std::size_t chunk_sz
) {
	return chunk_split<CharT, Traits, Allocator1, Allocator2>
	(
		std::basic_string<CharT, Traits, Allocator2>(in),
	 	chunk_sz
	);
}

#pragma mark -
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> chunk_join(
	const std::basic_string<CharT, Traits, Allocator> & in,
	const std::basic_string<CharT, Traits, Allocator> & token,
	std::size_t chunk_sz
) {
	std::basic_ostringstream<CharT, Traits, Allocator> os;
	std::size_t j = chunk_sz == 0 ? 1 : chunk_sz, i = 1;
	for (; i < in.size(); i++) { if (i % j == 0) { os << token; } os << in[i]; }
	return os.str();
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> chunk_join(
	const CharT (&in)[N],
	const std::basic_string<CharT, Traits, Allocator> & token,
	std::size_t chunk_sz
) {
	return chunk_join<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(in),
		token,
		chunk_sz
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> chunk_join(
	const std::basic_string<CharT, Traits, Allocator> & in,
	const CharT (&token)[N],
	std::size_t chunk_sz
) {
	return chunk_join<CharT, Traits, Allocator>(
		in,
		std::basic_string<CharT, Traits, Allocator>(token),
		chunk_sz
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, size_t N1
	, size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> chunk_join(
	const CharT (&in)[N1],
	const CharT (&token)[N2],
	std::size_t chunk_sz
) {
	return chunk_join<CharT, Traits, Allocator>(
		std::basic_string<CharT, Traits, Allocator>(in),
		std::basic_string<CharT, Traits, Allocator>(token),
		chunk_sz
	);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::vector<
		std::basic_string<CharT, Traits, Allocator>
		, typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	>::size_type
	, typename ssize_type = std::ptrdiff_t
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type explode(
	std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & out,
	const std::basic_string<CharT, Traits, Allocator> & delimiter,
	const std::basic_string<CharT, Traits, Allocator> & in,
	ssize_type limit = std::numeric_limits<ssize_type>::max()
) {
	usize_type begin = 0, end = 0;
	usize_type npos = std::basic_string<CharT, Traits, Allocator>::npos;
	
	if (delimiter.empty()) {
		return 0;
	}
	if (limit == 0) {
		limit = 1;
	}
	if (in.find(delimiter) == npos) {
		if (limit > 0) {
			out.push_back(in);
		}
		return out.size();
	}
	
	while (end != npos) {
		if (limit > 0 && weak_cast<ssize_type>(out.size()) == limit - 1) {
			out.push_back(in.substr(begin));
			break;
		}
		usize_type substr_len = npos;
		usize_type next_tok = npos;
		end = in.find_first_of(delimiter, begin);
		if (end != npos) {
			substr_len = end - begin;
			next_tok = end + delimiter.size();
		}
		out.push_back(in.substr(begin, substr_len));
		begin = next_tok;
	}
	if (limit < 0) {
		limit = std::abs(limit);
		if (limit < weak_cast<ssize_type>(out.size())) {
			out.resize(out.size() - weak_cast<usize_type>(limit));
		} else {
			out.clear();
		}
	}
	return out.size();
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::vector<
		std::basic_string<CharT, Traits, Allocator>
		, typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	>::size_type
	, typename ssize_type = std::ptrdiff_t
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type explode(
	std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & out,
	const CharT (&delimiter)[N],
	const std::basic_string<CharT, Traits, Allocator> & in,
	ssize_type limit = std::numeric_limits<ssize_type>::max()
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
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::vector<
		std::basic_string<CharT, Traits, Allocator>
		, typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	>::size_type
	, typename ssize_type = std::ptrdiff_t
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type explode(
	std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & out,
	const std::basic_string<CharT, Traits, Allocator> & delimiter,
	const CharT (&in)[N],
	ssize_type limit = std::numeric_limits<ssize_type>::max()
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
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::vector<
		std::basic_string<CharT, Traits, Allocator>
		, typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	>::size_type
	, typename ssize_type = std::ptrdiff_t
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type explode(
	std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & out,
	const CharT (&delimiter)[N1],
	const CharT (&in)[N2],
	ssize_type limit = std::numeric_limits<ssize_type>::max()
) {
	return explode<CharT, Traits, Allocator>(
		out,
		std::basic_string<CharT, Traits, Allocator>(delimiter),
		std::basic_string<CharT, Traits, Allocator>(in),
		limit
	);
}

#pragma mark -
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, template <
		typename
		, typename = allocators::standard<
			std::basic_string<CharT, Traits, Allocator>
		>
	> class Container
	, typename std::enable_if<
		container_is_vector<
			Container<
				std::basic_string<CharT, Traits, Allocator>
			>
		>::value ||
		container_is_list<
			Container<
				std::basic_string<CharT, Traits, Allocator>
			>
		>::value ||
		container_is_set<
			Container<
				std::basic_string<CharT, Traits, Allocator>
			>
		>::value ||
		container_is_deque<
			Container<
				std::basic_string<CharT, Traits, Allocator>
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
	, typename Allocator = allocators::standard<CharT>
	, template <
		typename
		, typename = allocators::standard<
			std::basic_string<CharT, Traits, Allocator>
		>
	> class Container
	, std::size_t N
	, typename std::enable_if<
		container_is_vector<
			Container<
				std::basic_string<CharT, Traits, Allocator>
			>
		>::value ||
		container_is_list<
			Container<
				std::basic_string<CharT, Traits, Allocator>
			>
		>::value ||
		container_is_set<
			Container<
				std::basic_string<CharT, Traits, Allocator>
			>
		>::value ||
		container_is_deque<
			Container<
				std::basic_string<CharT, Traits, Allocator>
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

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::basic_string<CharT, Traits, Allocator>::size_type
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type replace(
	std::basic_string<CharT, Traits, Allocator> & out,
	const std::basic_string<CharT, Traits, Allocator> & search,
	const std::basic_string<CharT, Traits, Allocator> & substitute,
	const std::basic_string<CharT, Traits, Allocator> & subject
) {
	usize_type j = 0;
	usize_type npos = std::basic_string<CharT, Traits, Allocator>::npos;
	out.assign(subject);
	
	for (usize_type pos = 0; ; pos += substitute.size()) {
		pos = out.find(search, pos);
		if (pos != npos) {
			out.erase(pos, search.size());
			out.insert(pos, substitute);
			j++;
		} else {
			break;
		}
	}
	return j;
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::basic_string<CharT, Traits, Allocator>::size_type
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type replace(
	std::basic_string<CharT, Traits, Allocator> & out,
	const CharT (&search)[N],
	const std::basic_string<CharT, Traits, Allocator> & substitute,
	const std::basic_string<CharT, Traits, Allocator> & subject
) {
	return replace<CharT, Traits, Allocator, usize_type>(
		out,
		std::basic_string<CharT, Traits, Allocator>(search),
		substitute,
		subject
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::basic_string<CharT, Traits, Allocator>::size_type
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type replace(
	std::basic_string<CharT, Traits, Allocator> & out,
	const std::basic_string<CharT, Traits, Allocator> & search,
	const CharT (&substitute)[N],
	const std::basic_string<CharT, Traits, Allocator> & subject
) {
	return replace<CharT, Traits, Allocator, usize_type>(
		out,
		search,
		std::basic_string<CharT, Traits, Allocator>(substitute),
		subject
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::basic_string<CharT, Traits, Allocator>::size_type
	, std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type replace(
	std::basic_string<CharT, Traits, Allocator> & out,
	const std::basic_string<CharT, Traits, Allocator> & search,
	const std::basic_string<CharT, Traits, Allocator> & substitute,
	const CharT (&subject)[N]
) {
	return replace<CharT, Traits, Allocator, usize_type>(
		out,
		search,
		substitute,
		std::basic_string<CharT, Traits, Allocator>(subject)
	);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::basic_string<CharT, Traits, Allocator>::size_type
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type replace(
	std::basic_string<CharT, Traits, Allocator> & out,
	const CharT (&search)[N1],
	const CharT (&substitute)[N2],
	const std::basic_string<CharT, Traits, Allocator> & subject
) {
	return replace<CharT, Traits, Allocator, usize_type>(
		out,
		std::basic_string<CharT, Traits, Allocator>(search),
		std::basic_string<CharT, Traits, Allocator>(substitute),
		subject
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::basic_string<CharT, Traits, Allocator>::size_type
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type replace(
	std::basic_string<CharT, Traits, Allocator> & out,
	const CharT (&search)[N1],
	const std::basic_string<CharT, Traits, Allocator> & substitute,
	const CharT (&subject)[N2]
) {
	return replace<CharT, Traits, Allocator, usize_type>(
		out,
		std::basic_string<CharT, Traits, Allocator>(search),
		substitute,
		std::basic_string<CharT, Traits, Allocator>(subject)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::basic_string<CharT, Traits, Allocator>::size_type
	, std::size_t N1
	, std::size_t N2
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type replace(
	std::basic_string<CharT, Traits, Allocator> & out,
	const std::basic_string<CharT, Traits, Allocator> & search,
	const CharT (&substitute)[N1],
	const CharT (&subject)[N2]
) {
	return replace<CharT, Traits, Allocator, usize_type>(
		out,
		search,
		std::basic_string<CharT, Traits, Allocator>(substitute),
		std::basic_string<CharT, Traits, Allocator>(subject)
	);
}

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::basic_string<CharT, Traits, Allocator>::size_type
	, std::size_t N1
	, std::size_t N2
	, std::size_t N3
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type replace(
	std::basic_string<CharT, Traits, Allocator> & out,
	const CharT (&search)[N1],
	const CharT (&substitute)[N2],
	const CharT (&subject)[N3]
) {
	return replace<CharT, Traits, Allocator, usize_type>(
		out,
		std::basic_string<CharT, Traits, Allocator>(search),
		std::basic_string<CharT, Traits, Allocator>(substitute),
		std::basic_string<CharT, Traits, Allocator>(subject)
	);
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename usize_type = typename std::basic_string<CharT, Traits, Allocator>::size_type
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
usize_type replace(
	std::basic_string<CharT, Traits, Allocator> & out,
	const std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & search,
	const std::vector<
		std::basic_string<CharT, Traits, Allocator>,
		typename std::vector<
			std::basic_string<CharT, Traits, Allocator>
		>::allocator_type
	> & substitute,
	const std::basic_string<CharT, Traits, Allocator> & subject
) {
	usize_type j = 0;
	usize_type max = std::min(search.size(), substitute.size());
	
	for (usize_type i = 0; i < max; i++) {
		j += replace<CharT, Traits, Allocator, usize_type>(
			out,
			search[i],
			substitute[i],
			subject
		);
	}
	return j;
}

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N
	, typename... ArgsT
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char), std::basic_string<CharT, Traits, Allocator>
>::type format(const CharT (&fmt)[N], ArgsT &&... args)
{
	int sz = std::snprintf(nullptr, 0, fmt, std::forward<ArgsT>(args)...);
	if (sz) {
		std::vector<CharT> buf(static_cast<std::size_t>(sz));
		std::snprintf(buf.data(), buf.size(), fmt, std::forward<ArgsT>(args)...);
		if (buf.back() == '\0') { buf.pop_back(); }
		return {buf.begin(), buf.end()};
	}
	return {};
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, std::size_t N
	, typename... ArgsT
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(wchar_t), std::basic_string<CharT, Traits, Allocator>
>::type format(const CharT (&fmt)[N], ArgsT &&... args)
{
	int sz = std::snprintf(nullptr, 0, fmt, std::forward<ArgsT>(args)...);
	if (sz) {
		std::vector<CharT> buf(static_cast<std::size_t>(sz));
		std::swprintf(buf.data(), buf.size(), fmt, std::forward<ArgsT>(args)...);
		if (buf.back() == '\0') { buf.pop_back(); }
		return {buf.begin(), buf.end()};
	}
	return {};
}
	
template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename Allocator = allocators::standard<CharT>
	, typename... ArgsT
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, Traits, Allocator> format(
	const std::basic_string<CharT, Traits, Allocator> & fmt,
	ArgsT &&... args
) { return format(fmt.c_str(), std::forward<ArgsT>(args)...); }

#pragma mark -

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, std::size_t N
	, typename... ArgsT
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_ostream<CharT, Traits> & format_to(
	std::basic_ostream<CharT, Traits> & os,
	const CharT (&fmt)[N], ArgsT &&... args
) { os << format(fmt, std::forward<ArgsT>(args)...);  return os; }

template <typename CharT
	, typename Traits = std::char_traits<CharT>
	, typename... ArgsT
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_ostream<CharT, Traits> & format_to(
	std::basic_ostream<CharT, Traits> & os,
	const std::string & fmt,
	ArgsT &&... args
) { os << format(fmt.c_str(), std::forward<ArgsT>(args)...); return os; }

#pragma mark -

template <std::size_t N, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void format_stderr(const char (&fmt)[N], ArgsT &&... args)
{
#if defined(__MICROSOFT__)
	const char _endl[3] = "\r\n";
#else
	const char _endl = '\n';
#endif
	std::ios saved_fmt(nullptr);
	std::ios default_fmt(nullptr);
	saved_fmt.copyfmt(std::cerr);
	std::cerr.copyfmt(default_fmt);
	std::cerr << std::nounitbuf;
	std::cerr << format(fmt, std::forward<ArgsT>(args)...) << _endl;
	std::cerr.copyfmt(saved_fmt);
}
	
template <typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void format_stderr(const std::string & fmt, ArgsT &&... args)
{ format_stderr(fmt.c_str(), std::forward<ArgsT>(args)...); }

#pragma mark -

template <std::size_t N, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void format_stdout(const char (&fmt)[N], ArgsT &&... args)
{
#if defined(__MICROSOFT__)
	const char _endl[3] = "\r\n";
#else
	const char _endl = '\n';
#endif
	std::ios saved_fmt(nullptr);
	std::ios default_fmt(nullptr);
	saved_fmt.copyfmt(std::cout);
	std::cout.copyfmt(default_fmt);
	std::cout << std::nounitbuf;
	std::cout << format(fmt, std::forward<ArgsT>(args)...) << _endl;
	std::cout.copyfmt(saved_fmt);
}
	
template <typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void format_stdout(const std::string & fmt, ArgsT &&... args)
{ format_stdout(fmt.c_str(), std::forward<ArgsT>(args)...); }
	
}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ALGORITHMS_HPP */

/* EOF */