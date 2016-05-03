//
// nutrt-ustring.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>
#include <coconut/runtime/details/nutrt-algorithm.hpp>

#include "unicode/ustdio.h"
#include "unicode/unistr.h"

#ifndef COCONUT_RUNTIME_USTRING_HPP
#define COCONUT_RUNTIME_USTRING_HPP

namespace coconut {
	namespace runtime {
		namespace traits {

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
	COCONUT_CLASSMETHOD std::string format(const std::string & fmt, ArgsT &&... args)
	{ return algorithm::format(fmt.c_str(), std::forward<ArgsT>(args)...); }
	
	template <typename... ArgsT>
	COCONUT_CLASSMETHOD std::u16string uformat(const char * utf8_fmt, ArgsT &&... args)
	{
		std::u16string result;
		if (utf8_fmt) {
			UChar ubuf[1024];
			std::int32_t written = 0;
			if ((written = u_snprintf(ubuf, 1024, utf8_fmt, args...)) > 0) {
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
			UChar ubuf[1024];
			std::int32_t written = 0;
			if ((written = u_snprintf_u(ubuf, 1024, weak_cast<UChar *>(utf16_fmt), args...)) > 0) {
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
	
	void append(const ustring & ustr);
	void capitalized();
	void lowercase();
	void uppercase();
	
	ustring by_appending(const ustring & ustr) const;
	
private:
	icu::UnicodeString m_ustr;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_USTRING_HPP */

/* EOF */