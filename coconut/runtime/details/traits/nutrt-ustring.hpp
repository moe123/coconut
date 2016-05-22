//
// nutrt-ustring.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>
#include <coconut/runtime/details/nutrt-algorithms.hpp>

#include "unicode/ustdio.h"
#include "unicode/unistr.h"

#ifndef COCONUT_RUNTIME_USTRING_HPP
#define COCONUT_RUNTIME_USTRING_HPP

namespace coconut
{ namespace runtime
{ namespace traits
{

COCONUT_CLASSFORWARD_DCL(locale)
COCONUT_CLASSFORWARD_DCL(irange)

COCONUT_PRIVATE class COCONUT_VISIBLE ustring COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.ustring, ustring)
	
public:
	ustring();
	ustring(const ustring & ustr);
	ustring(ustring && ustr) noexcept;
	ustring(const std::int8_t * bytes, std::size_t length, encoding_option encoding);
	ustring(const std::int16_t * bytes, std::size_t length, encoding_option encoding);
	ustring(const std::int32_t * bytes, std::size_t length, encoding_option encoding);
	ustring(const std::uint8_t * bytes, std::size_t length, encoding_option encoding);
	ustring(const std::uint16_t * bytes, std::size_t length, encoding_option encoding);
	ustring(const std::uint32_t * bytes, std::size_t length, encoding_option encoding);
	ustring(const std::string & in, encoding_option encoding);
	ustring(const std::u16string & in, encoding_option encoding);
	ustring(const std::u32string & in, encoding_option encoding);
	ustring(const char * utf8_str);
	ustring(const char16_t * utf16_str);
	ustring(const char32_t * utf32_str);
	~ustring();

public:
	COCONUT_CLASSMETHOD bool get_sys_codepages(std::vector<std::string> & codepages);
	COCONUT_CLASSMETHOD void get_codepages(std::set<std::string> & codepages);
	COCONUT_CLASSMETHOD std::string get_codepage(encoding_option encoding);
	
	COCONUT_CLASSMETHOD bool guess_encoding(const std::string & in8bits, encoding_option & encoding, float & confidence);
	COCONUT_CLASSMETHOD bool transliterate(const std::string & utf8_in, std::string & translit_out);
	
	COCONUT_CLASSMETHOD std::string make_utf8(const std::string & in8bits, float & confidence, encoding_option from = encoding_auto);
	COCONUT_CLASSMETHOD int compare_utf8(const std::string & utf8_a, const std::string & utf8_b, search_options options);
	
	template <typename... ArgsT>
	COCONUT_CLASSMETHOD std::u16string uformat(const char * utf8_fmt, ArgsT &&... args)
	{
		std::u16string result;
		if (utf8_fmt) {
			char16_t ubuf[1024];
			std::int32_t written = 0;
			if ((written = u_snprintf(weak_cast<UChar *>(ubuf), 1024, utf8_fmt, args...)) > 0) {
				result.assign(ubuf, (ubuf + written));
			}
		}
		return result;
	}
	
	template <typename... ArgsT>
	COCONUT_CLASSMETHOD std::u16string uformat(const char16_t * utf16_fmt, ArgsT &&... args)
	{
		std::u16string result;
		if (utf16_fmt) {
			char16_t ubuf[1024];
			std::int32_t written = 0;
			if ((written = u_snprintf_u(weak_cast<UChar *>(ubuf), 1024, weak_cast<UChar *>(utf16_fmt), args...)) > 0) {
				result.assign(ubuf, (ubuf + written));
			}
		}
		return result;
	}
	
	COCONUT_CLASSMETHOD ustring unescaped(const ustring & ustr);

public:
	ustring & operator = (const ustring & ustr);
	
	ustring & assign(const ustring & ustr);
	ustring & assign(ustring && ustr);
	ustring & assign(const ustring & ustr, std::size_t subpos, std::size_t sublen);
	
	template <class InputIterT>
	ustring & assign(InputIterT && first, InputIterT && last)
	{ clear(); for (; first != last; ++first) { append(*first); } return *this; }
	
	void swap(ustring & ustr);
	
	std::uint16_t at(std::size_t index) const;
	std::uint32_t char_at(std::size_t index) const;
	
	int compare(const ustring & other_ustr) const;
	int compare(const ustring & other_ustr, search_options options) const;
	
	int icase_compare(const ustring & other_ustr) const;
	int icase_compare(const ustring & other_ustr, search_options options) const;
	
	int compare_localized(const ustring & other_ustr) const;
	int compare_localized(const ustring & other_ustr, search_options options) const;
	
	int icase_compare_localized(const ustring & other_ustr) const;
	int icase_compare_localized(const ustring & other_ustr, search_options options) const;
	
	bool is_valid() const;
	
	std::size_t capacity() const;
	std::size_t size() const;
	std::size_t length() const;
	std::size_t count() const;
	
	std::size_t size_for(encoding_option encoding) const;
	
	void clear();
	
	float to_float() const;
	double to_double() const;
	long double to_long_double() const;
	
	bool to_bool() const;
	
	char to_char() const;
	short to_short() const;
	int to_int() const;
	long to_long() const;
	long long to_long_long() const;
	
	unsigned char to_unsigned_char() const;
	unsigned short to_unsigned_short() const;
	unsigned int to_unsigned_int() const;
	unsigned long to_unsigned_long() const;
	unsigned long long to_unsigned_long_long() const;
	
	std::string to_string() const;
	std::size_t hash_code() const;
	
	const std::string to_utf8() const;
	
	const std::u16string to_utf16() const;
	const std::u32string to_utf32() const;
	
	const std::u16string to_utf16_le() const;
	const std::u32string to_utf32_le() const;
	
	const std::u16string to_utf16_be() const;
	const std::u32string to_utf32_be() const;
	
	bool has_prefix(const ustring & ustr) const;
	bool has_suffix(const ustring & ustr) const;
	
	bool icase_has_prefix(const ustring & ustr) const;
	bool icase_has_suffix(const ustring & ustr) const;
	
	irange range_of(const ustring & ustr) const;
	irange range_of(const ustring & ustr, const irange & in_rg) const;
	irange range_of(const ustring & ustr, search_options options) const;
	irange range_of(const ustring & ustr, const irange & in_rg, search_options options) const;
	
	std::uint16_t code_unit_at(std::size_t index) const;
	std::uint32_t code_point_at(std::size_t index) const;
	
	ustring & append(const ustring & ustr);
	
	ustring & append(const std::int16_t & code_unit);
	ustring & append(const std::int32_t & code_point);
	
	ustring & append(const std::uint16_t & code_unit);
	ustring & append(const std::uint32_t & code_point);
	
	ustring & append(const char16_t & code_unit);
	ustring & append(const char32_t & code_point);
	
	ustring & append(const wchar_t & code);
	
	template <class InputIterT>
	ustring & append(InputIterT && first, InputIterT &&  last)
	{ for (; first != last; ++first) { append(*first); } return *this; }
	
	ustring & capitalized();
	ustring & lowercased();
	ustring & uppercased();
	ustring & lowercased(const locale & loc);
	ustring & uppercased(const locale & loc);
	
	ustring by_appending(const ustring & ustr) const;
	ustring by_capitalizing(const ustring & ustr) const;
	ustring by_lowercasing(const ustring & ustr) const;
	ustring by_uppercasing(const ustring & ustr) const;
	ustring by_lowercasing(const ustring & ustr, const locale & loc) const;
	ustring by_uppercasing(const ustring & ustr, const locale & loc) const;

private:
	/* private traits */
	
	using item_type = UChar32;
	using this_type = ustring;
	using inner_type = icu::UnicodeString;
	
	typedef std::vector<item_type, allocators::placement<item_type> > container_type;
	
public:
	/* type_traits */
	
	typedef container_type::iterator iterator;
	typedef container_type::const_iterator const_iterator;
	
	typedef container_type::reverse_iterator reverse_iterator;
	typedef container_type::const_reverse_iterator const_reverse_iterator;
	
	typedef container_type::value_type value_type;
	typedef container_type::size_type size_type;
	typedef container_type::difference_type difference_type;
	
	typedef container_type::reference reference;
	typedef container_type::const_reference const_reference;
	typedef container_type::pointer pointer;
	typedef container_type::const_pointer const_pointer;
	
	typedef allocators::builtins<this_type> allocator_type;
	
public:
	/* type_iterator */
	
	iterator begin();
	iterator end();
	
	const_iterator begin() const;
	const_iterator end() const;
	
	const_iterator cbegin() const;
	const_iterator cend() const;
	
	reverse_iterator rbegin();
	reverse_iterator rend();
	
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;
	
private:
	inner_type m_ustr;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_USTRING_HPP */

/* EOF */