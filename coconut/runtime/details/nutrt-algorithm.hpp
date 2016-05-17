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

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	const std::basic_string<CharT, TraitsT, AllocatorT> & haystack,
	const std::basic_string<CharT, TraitsT, AllocatorT> & needle
) {
	return needle.size() <= haystack.size() &&
		std::equal(needle.cbegin(), needle.cend(), haystack.cbegin());
}
	
template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>,
	std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, TraitsT, AllocatorT> & needle
) {
	return starts_with<CharT, TraitsT, AllocatorT>(
		std::basic_string<CharT, TraitsT, AllocatorT>(haystack),
		needle
	);
}
	
template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>,
	std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool starts_with(
	const std::basic_string<CharT, TraitsT, AllocatorT> & haystack,
	const CharT (&needle)[N]
) {
	return starts_with<CharT, TraitsT, AllocatorT>(
		haystack,
		std::basic_string<CharT, TraitsT, AllocatorT>(needle)
	);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	const std::basic_string<CharT, TraitsT, AllocatorT> & haystack,
	const std::basic_string<CharT, TraitsT, AllocatorT> & needle
) {
	return needle.size() <= haystack.size() &&
		std::equal(needle.crbegin(), needle.crend(), haystack.crbegin());
}
	
template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>,
	std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	const CharT (&haystack)[N],
	const std::basic_string<CharT, TraitsT, AllocatorT> & needle
) {
	return ends_with<CharT, TraitsT, AllocatorT>(
		std::basic_string<CharT, TraitsT, AllocatorT>(haystack),
		needle
	);
}
	
template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>,
	std::size_t N
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ends_with(
	const std::basic_string<CharT, TraitsT, AllocatorT> & haystack,
	const CharT (&needle)[N]
) {
	return ends_with<CharT, TraitsT, AllocatorT>(
		haystack,
		std::basic_string<CharT, TraitsT, AllocatorT>(needle)
	);
}

template <typename CharT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool is_alpha(CharT a)
{
	std::locale loc;
	return std::use_facet< std::ctype<CharT> >(loc).is(std::ctype<CharT>::alpha, a);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool is_ascii(const std::basic_string<CharT, TraitsT, AllocatorT> & in)
{
	using const_iter = typename std::basic_string<CharT, TraitsT, AllocatorT>::const_iterator;
	for (const_iter it = in.cbegin(); it!= in.cend(); ++it) {
		if (!((reinterpret_cast<std::int32_t>(*it) & ~0x7F) == 0)) { return false; }
	}
	return true;
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> & ltrim(
	std::basic_string<CharT, TraitsT, AllocatorT> & s
) {
	s.erase(s.begin(), std::find_if(
		s.begin(), s.end(), std::not1(
			std::ptr_fun<std::int32_t, std::int32_t>(std::isspace)
	)));
	return s;
}
	
template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> ltrim_copy(
	const std::basic_string<CharT, TraitsT, AllocatorT> & s
) {
	std::basic_string<CharT, TraitsT, AllocatorT> s_(s.data(), s.size());
	return ltrim<CharT, TraitsT, AllocatorT>(s_);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> & rtrim(
	std::basic_string<CharT, TraitsT, AllocatorT> & s
) {
	s.erase(std::find_if(
		s.rbegin(), s.rend(), std::not1(
			std::ptr_fun<std::int32_t, std::int32_t>(std::isspace)
	)).base(), s.end());
	return s;
}
	
template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> rtrim_copy(
	const std::basic_string<CharT, TraitsT, AllocatorT> & s
) {
	std::basic_string<CharT, TraitsT, AllocatorT> s_(s.data(), s.size());
	return rtrim<CharT, TraitsT, AllocatorT>(s_);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> & trim(
	std::basic_string<CharT, TraitsT, AllocatorT> & s
) { return ltrim<CharT, TraitsT, AllocatorT>(rtrim<CharT, TraitsT, AllocatorT>(s)); }
	
template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> trim_copy(
	const std::basic_string<CharT, TraitsT, AllocatorT> & s
) {
	std::basic_string<CharT, TraitsT, AllocatorT> s_(s.data(), s.size());
	return trim<CharT, TraitsT, AllocatorT>(s_);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> & to_upper(
	std::basic_string<CharT, TraitsT, AllocatorT> & in
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

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> to_upper_copy(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
) {
	std::basic_string<CharT, TraitsT, AllocatorT> out(in.data(), in.size());
	return to_upper<CharT, TraitsT, AllocatorT>(out);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> & to_lower(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
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

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> to_lower_copy(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
) {
	std::basic_string<CharT, TraitsT, AllocatorT> out(in.data(), in.size());
	return to_lower<CharT, TraitsT, AllocatorT>(out);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool cmp(
	const std::basic_string<CharT, TraitsT, AllocatorT> & left,
	const std::basic_string<CharT, TraitsT, AllocatorT> & right
) { return left.compare(right); }

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool cmp(
	const CharT * left,
	const std::basic_string<CharT, TraitsT, AllocatorT> & right
) {
	return cmp<CharT, TraitsT, AllocatorT>(
		std::basic_string<CharT, TraitsT, AllocatorT>(left),
		right
	);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool cmp(
	const std::basic_string<CharT, TraitsT, AllocatorT> & left,
	const CharT * right
) {
	return cmp<CharT, TraitsT, AllocatorT>(
		left,
		std::basic_string<CharT, TraitsT, AllocatorT>(right)
	);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	const std::basic_string<CharT, TraitsT, AllocatorT> & left,
	const std::basic_string<CharT, TraitsT, AllocatorT> & right
) {
	return cmp(
		to_upper_copy<CharT, TraitsT, AllocatorT>(left),
		to_upper_copy<CharT, TraitsT, AllocatorT>(right)
	);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	const CharT * left,
	const std::basic_string<CharT, TraitsT, AllocatorT> & right
) {
	return icmp<CharT, TraitsT, AllocatorT>(
		std::basic_string<CharT, TraitsT, AllocatorT>(left),
		right
	);
}

template <typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
int icmp(
	const std::basic_string<CharT, TraitsT, AllocatorT> & left,
	const CharT * right
) {
	return icmp<CharT, TraitsT, AllocatorT>(
		left,
		std::basic_string<CharT, TraitsT, AllocatorT>(right)
	);
}

template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char) &&
	(
		std::is_same<CharT, char>::value ||
		std::is_same<CharT, unsigned char>::value
	)
, bool>::type is_integer(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in,
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

template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(wchar_t) &&
	std::is_same<CharT, wchar_t>::value
, bool>::type is_integer(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in,
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
	
template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char16_t) &&
	std::is_same<CharT, char16_t>::value
, bool>::type is_integer(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in,
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
	
template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char32_t) &&
	std::is_same<CharT, char32_t>::value
, bool>::type is_integer(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in,
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

template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char) &&
	(
		std::is_same<CharT, char>::value ||
		std::is_same<CharT, unsigned char>::value
	)
, bool>::type is_number(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
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

template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(wchar_t) &&
	std::is_same<CharT, wchar_t>::value
, bool>::type is_number(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
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

template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char16_t) &&
	std::is_same<CharT, char16_t>::value
, bool>::type is_number(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
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

template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char32_t) &&
	std::is_same<CharT, char32_t>::value
, bool>::type is_number(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
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

template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char) &&
	(
		std::is_same<CharT, char>::value ||
		std::is_same<CharT, unsigned char>::value
	)
, bool>::type is_numeric(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
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

template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(wchar_t) &&
	std::is_same<CharT, wchar_t>::value
, bool>::type is_numeric(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
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

template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char16_t) &&
	std::is_same<CharT, char16_t>::value
, bool>::type is_numeric(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
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
	
template<typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
typename std::enable_if<
	sizeof(CharT) == sizeof(char32_t) &&
	std::is_same<CharT, char32_t>::value
, bool>::type is_numeric(
	const std::basic_string<CharT, TraitsT, AllocatorT> & in
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

template <typename CharT, typename NumT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> to_binary(const NumT & x)
{
	std::bitset<(sizeof(x) * CHAR_BIT)> bits(x);
	return bits. template to_string<CharT, TraitsT, AllocatorT>();
}

template <typename NumT, typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
NumT to_numeric(const std::basic_string<CharT, TraitsT, AllocatorT> & in)
{
	NumT t = 0;

	typedef std::basic_stringstream<CharT, TraitsT, AllocatorT> stringstream_type;
	
	if (in.size() && is_numeric<CharT, TraitsT, AllocatorT>(in)) {
		stringstream_type buf;
		buf << in;
		buf >> t;
	}
	return t;
}

template <typename CharT, typename NumT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> to_string(const NumT & n, std::size_t p = 6)
{
	using ostringstream_type = std::basic_ostringstream<CharT, TraitsT, AllocatorT>;
	
	ostringstream_type ostr;
	ostr.setf(std::ios::fixed, std::ios::floatfield);
	ostr.precision(static_cast<std::streamsize>(p));
	ostr << n;
	return ostr.str();
}

template <typename IterT, typename CharT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void joiner(
	IterT && beg,
	IterT && end,
	const std::basic_string<CharT, TraitsT, AllocatorT> & sep,
	std::basic_string<CharT, TraitsT, AllocatorT> & joined
) {
	using ostringstream_type = std::basic_ostringstream<CharT, TraitsT, AllocatorT>;
	
	ostringstream_type result;

	if (beg != end) {
		result << *beg++;
	}
	while (beg != end) {
		result << sep;
		result << *beg++;
	}
	joined = std::move(result.str());
}

template <typename StrT, typename VecT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void tokenizer(const StrT & in, VecT & tokens, const StrT & delimiter)
{
	using value_type = typename VecT::value_type;
	using size_type = typename VecT::size_type;
	using string_size_type = typename StrT::size_type;
	
	string_size_type pos, last_pos = 0;
	
	while (true) {
		pos = in.find_first_of(delimiter, last_pos);
		if (pos == StrT::npos) {
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

template <typename StrT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::vector<StrT> split(const StrT & in, const StrT & delimiter)
{
	std::vector<StrT> out;
	tokenizer<StrT>(in, out, delimiter);
	return out;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::size_t explode(
	std::vector<std::string> & out,
	const std::string & delimiter,
	const std::string & in,
	int limit = std::numeric_limits<int>::max()
) {
	std::vector<std::string>::size_type begin = 0;
	std::vector<std::string>::size_type end = 0;
	
	if (delimiter.empty()) {
		return 0;
	}
	if (limit == 0) {
		limit = 1;
	}
	if (in.find(delimiter) == std::string::npos) {
		if (limit > 0) {
			out.push_back(in);
		}
		return out.size();
	}
	
	while (end != std::string::npos) {
		if (limit > 0 && static_cast<int>(out.size()) == limit - 1) {
			out.push_back(in.substr(begin));
			break;
		}
		std::vector<std::string>::size_type substr_len = std::string::npos;
		std::vector<std::string>::size_type next_tok = std::string::npos;
		end = in.find_first_of(delimiter, begin);
		if (end != std::string::npos) {
			substr_len = end - begin;
			next_tok = end + delimiter.size();
		}
		out.push_back(in.substr(begin, substr_len));
		begin = next_tok;
	}
	if (limit < 0) {
		limit = std::abs(limit);
		if (limit < static_cast<int>(out.size())) {
			out.resize(out.size() - static_cast<std::size_t>(limit));
		} else {
			out.clear();
		}
	}
	return out.size();
}

template <typename CharT,
	template <
		typename,
		typename = std::allocator<
			std::basic_string<CharT,
				std::char_traits<CharT>,
				std::allocator<CharT>
			>
		>
	> class ContainerT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>,
	typename std::enable_if<
		std::is_same<
			ContainerT< std::basic_string<CharT, TraitsT, AllocatorT> >,
			std::vector< std::basic_string<CharT, TraitsT, AllocatorT> >
		>::value ||
		std::is_same<
			ContainerT< std::basic_string<CharT, TraitsT, AllocatorT> >,
			std::list< std::basic_string<CharT, TraitsT, AllocatorT> >
		>::value ||
		std::is_same<
			ContainerT< std::basic_string<CharT, TraitsT, AllocatorT> >,
			std::set< std::basic_string<CharT, TraitsT, AllocatorT> >
		>::value
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> join(
	const ContainerT< std::basic_string<CharT, TraitsT, AllocatorT> > & parts,
	const std::basic_string<CharT, TraitsT, AllocatorT> & separator
) {
	using IterT = typename std::vector< std::basic_string<CharT, TraitsT, AllocatorT> >::const_iterator;
	std::basic_string<CharT, TraitsT, AllocatorT> joined;
	joiner<IterT, CharT, TraitsT, AllocatorT>(parts.cbegin(), parts.cend(), separator, joined);
	return joined;
}

template <
	typename CharT,
	template <
		typename,
		typename = std::allocator<
			std::basic_string<CharT,
				std::char_traits<CharT>,
				std::allocator<CharT>
			>
		>
	> class ContainerT,
	typename TraitsT = std::char_traits<CharT>,
	typename AllocatorT = std::allocator<CharT>,
	typename std::enable_if<
		std::is_same<
			ContainerT< std::basic_string<CharT, TraitsT, AllocatorT> >,
			std::vector< std::basic_string<CharT, TraitsT, AllocatorT> >
		>::value ||
		std::is_same<
			ContainerT< std::basic_string<CharT, TraitsT, AllocatorT> >,
			std::list< std::basic_string<CharT, TraitsT, AllocatorT> >
		>::value ||
		std::is_same<
			ContainerT< std::basic_string<CharT, TraitsT, AllocatorT> >,
			std::set< std::basic_string<CharT, TraitsT, AllocatorT> >
		>::value
	>::type* = nullptr
>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::basic_string<CharT, TraitsT, AllocatorT> join(
	const ContainerT< std::basic_string<CharT, TraitsT, AllocatorT> > & parts,
	const CharT * separator
) { return join<CharT, ContainerT, TraitsT, AllocatorT>(parts, std::basic_string<CharT, TraitsT, AllocatorT>(separator)); }

template <typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string format(const char * fmt, ArgsT &&... args)
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

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ALGORITHM_HPP */

/* EOF */