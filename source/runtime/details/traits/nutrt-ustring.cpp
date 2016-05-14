//
// nutrt-ustring.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-ustring.hpp>
#include <coconut/runtime/details/traits/nutrt-locale.hpp>
#include <coconut/runtime/details/traits/nutrt-irange.hpp>

#include <coconut/runtime/details/nutrt-base64.hpp>
#include <coconut/runtime/details/nutrt-hash.hpp>
#include <coconut/runtime/details/nutrt-algorithm.hpp>
#include <coconut/runtime/details/nutrt-byteorder.hpp>
#include <coconut/runtime/details/nutrt-unicode.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

#include <source/runtime/builtins/nutrt-ustring_compare_utf8.hxx>
#include <source/runtime/builtins/nutrt-ustring_compare_utf16.hxx>
#include <source/runtime/builtins/nutrt-ustring_encoding.hxx>
#include <source/runtime/builtins/nutrt-ustring_parsing.hxx>
#include <source/runtime/builtins/nutrt-ustring_searching.hxx>
#include <source/runtime/builtins/nutrt-ustring_transliterate.hxx>

ustring::ustring()
: m_ustr()
{ /* NOP */ }

ustring::ustring(const ustring & ustr)
: m_ustr(ustr.m_ustr)
{ /* NOP */ }

ustring::ustring(ustring && ustr) noexcept
: m_ustr(ustr.m_ustr)
{ ustr.m_ustr.remove(); }

ustring::ustring(const std::int8_t * bytes, std::size_t length, encoding_option encoding)
: m_ustr()
{
	if (bytes && length) {
		switch (encoding)
		{
			case encoding_auto:
			{
				float confidence = 0.0f;
				std::string codepage = builtins::ustring_detectcodepage(weak_cast<const char *>(bytes), length, confidence);
				if (confidence >= 0.10f) {
					m_ustr = icu::UnicodeString(
						weak_cast<const char *>(bytes),
						weak_cast<std::int32_t>(length),
						codepage.c_str()
					);
					if (!is_valid() || !size()) {
						clear();
						m_ustr.setToBogus();
					}
				}
			}
			break;
			case encoding_utf8:
			{
				m_ustr = icu::UnicodeString::fromUTF8(
					icu::StringPiece(std::string(bytes, bytes + length))
				);
				if (!is_valid() || !size()) {
					clear();
					m_ustr.setToBogus();
				}
			}
			break;
			case encoding_shiftjis:
			case encoding_iso2022jp:
			case encoding_iso2022cn:
			case encoding_iso2022kr:
			case encoding_gb18030:
			case encoding_big5:
			case encoding_eucjp:
			case encoding_euckr:
			case encoding_iso88591:
			case encoding_iso88592:
			case encoding_iso88595:
			case encoding_iso88596:
			case encoding_iso88597:
			case encoding_iso88598:
			case encoding_iso88598i:
			case encoding_iso88599:
			case encoding_windows1250:
			case encoding_windows1251:
			case encoding_windows1252:
			case encoding_windows1253:
			case encoding_windows1254:
			case encoding_windows1255:
			case encoding_windows1256:
			case encoding_koi8r:
			case encoding_ibm420:
			case encoding_ibm420ltr:
			case encoding_ibm420rtl:
			case encoding_ibm424:
			case encoding_ibm424ltr:
			case encoding_ibm424rtl:
			{
				std::string codepage = builtins::ustring_getcodepage(encoding);
				m_ustr = icu::UnicodeString(
					weak_cast<const char *>(bytes),
					weak_cast<std::int32_t>(length),
					codepage.c_str()
				);
				if (!is_valid() || !size()) {
					clear();
					m_ustr.setToBogus();
				}
			}
			break;
			default:
			{
				m_ustr.setToBogus();
			}
			break;
		}
	}
}

ustring::ustring(const std::int16_t * bytes, std::size_t length, encoding_option encoding)
: m_ustr()
{
	if (bytes && length) {
		switch (encoding)
		{
			case encoding_ucs2:
			case encoding_ucs2le:
			case encoding_ucs2be:
			case encoding_utf16:
			case encoding_utf16le:
			case encoding_utf16be:
			{
				std::string codepage = builtins::ustring_getcodepage(encoding);
				
				std::cerr << " --- codepage -- " << codepage << std::endl;
				
				m_ustr = icu::UnicodeString(
					weak_cast<const char *>(bytes),
					weak_cast<std::int32_t>(length * sizeof(UChar)),
					codepage.c_str()
				);
				/*
				m_ustr = icu::UnicodeString(
					weak_cast<const UChar *>(bytes),
					weak_cast<std::int32_t>(length)
				);*/
				
				if (!is_valid() || !size()) {
					clear();
					m_ustr.setToBogus();
				}
			}
			break;
			default:
			{
				m_ustr.setToBogus();
			}
			break;
		}
	}
}

ustring::ustring(const std::int32_t * bytes, std::size_t length, encoding_option encoding)
: m_ustr()
{
	if (bytes && length) {
		switch (encoding)
		{
			case encoding_utf32:
			case encoding_utf32le:
			case encoding_utf32be:
			case encoding_ucs4:
			case encoding_ucs4le:
			case encoding_ucs4be:
			{
				m_ustr = icu::UnicodeString::fromUTF32(
					weak_cast<const UChar32 *>(bytes),
					weak_cast<std::int32_t>(length)
				);
				if (!is_valid() || !size()) {
					clear();
					m_ustr.setToBogus();
				}
			}
			break;
			default:
			{
				m_ustr.setToBogus();
			}
			break;
		}
	}
}

ustring::ustring(const std::uint8_t * bytes, std::size_t length, encoding_option encoding)
: ustring(weak_cast<const std::int8_t *>(bytes), length, encoding)
{ /* NOP */ }

ustring::ustring(const std::uint16_t * bytes, std::size_t length, encoding_option encoding)
: ustring(weak_cast<const std::int16_t *>(bytes), length, encoding)
{ /* NOP */ }

ustring::ustring(const std::uint32_t * bytes, std::size_t length, encoding_option encoding)
: ustring(weak_cast<const std::int32_t *>(bytes), length, encoding)
{ /* NOP */ }

ustring::ustring(const std::string & in, encoding_option encoding)
: ustring(
	weak_cast<const std::int8_t *>(in.data()),
	in.size(),
	encoding
)
{ /* NOP */ }

ustring::ustring(const std::u16string & in, encoding_option encoding)
: ustring(
	weak_cast<const std::int16_t *>(in.data()),
	in.size(),
	encoding
)
{ /* NOP */ }

ustring::ustring(const std::u32string & in, encoding_option encoding)
: ustring(
	weak_cast<const std::int32_t *>(in.data()),
	in.size(),
	encoding
)
{ /* NOP */ }

ustring::ustring(const char * utf8_str)
: ustring(
	weak_cast<const std::int8_t *>(utf8_str),
	std::char_traits<char>::length(utf8_str),
	encoding_utf8
)
{ /* NOP */ }

ustring::ustring(const char16_t * utf16_str)
: ustring(
	weak_cast<const std::int16_t *>(utf16_str),
	std::char_traits<char16_t>::length(utf16_str),
	encoding_utf16
)
{ /* NOP */ }

ustring::ustring(const char32_t * utf32_str)
: ustring(
	weak_cast<const std::int32_t *>(utf32_str),
	std::char_traits<char32_t>::length(utf32_str),
	encoding_utf32
)
{ /* NOP */ }

ustring::~ustring()
{ /* NOP */ }

#pragma mark -

std::string ustring::get_codepage(encoding_option encoding)
{ return builtins::ustring_getcodepage(encoding); }

bool ustring::get_sys_codepages(std::vector<std::string> & codepages)
{ return builtins::ustring_syscodepages(codepages); }

void ustring::get_codepages(std::set<std::string> & codepages)
{ builtins::ustring_getcodepages(codepages); }

#pragma mark -

bool ustring::transliterate(const std::string & utf8_in, std::string & translit_out)
{ return builtins::ustring_transliterate(utf8_in, translit_out); }

#pragma mark -

bool ustring::guess_encoding(const std::string & in8bits, encoding_option & encoding, float & confidence)
{
	bool result = false;
	std::string codepage = builtins::ustring_detectcodepage(in8bits.data(), in8bits.length(), confidence);
	if (builtins::ustring_getencoding(codepage.c_str(), encoding)) {
		result = true;
	} else {
		encoding = encoding_utf8;
		confidence = 0.0f;
	}
	return result;
}

std::string ustring::make_utf8(const std::string & in8bits, float & confidence, encoding_option from)
{
	std::string result;
	if (from == encoding_auto) {
		encoding_option guess;
		if (ustring::guess_encoding(in8bits, guess, confidence)) {
			if (guess == encoding_utf8 && confidence >= 0.8f) {
				return in8bits;
			}
			confidence = 0.8f;
			ustring ustr(in8bits, guess);
			if (!ustr.is_valid() || !ustr.size()) {
				confidence = 0.0f;
				ustr.clear();
			}
			result = std::move(ustr.to_utf8());
		} else {
			confidence = 0.8f;
			ustring ustr(in8bits, from);
			if (!ustr.is_valid() || !ustr.size()) {
				confidence = 0.0f;
				ustr.clear();
			}
			result = std::move(ustr.to_utf8());
		}
	} else {
		confidence = 0.8f;
		ustring ustr(in8bits, from);
		if (!ustr.is_valid() || !ustr.size()) {
			confidence = 0.0f;
			ustr.clear();
		}
		result = std::move(ustr.to_utf8());
	}
	return result;
}

#pragma mark -

int ustring::compare_utf8(const std::string & utf8_a, const std::string & utf8_b, search_options options)
{
	if (options == search_literal || options & search_literal) {
		options &= ~search_literal;
		options |= search_nowidth;
	}
	//icu::Locale loc = icu::Locale::getDefault();
	icu::Locale loc = icu::Locale::getEnglish();
	return builtins::ustring_compare_utf8(utf8_a, utf8_b, options, &loc);
}

#pragma mark -

ustring ustring::unescaped(const ustring & ustr)
{
	ustring result;
	if (ustr.size() && ustr.is_valid()) {
		result.m_ustr = ustr.m_ustr.unescape();
		if (!result.is_valid()) {
			result.clear();
		}
	}
	return result;
}

#pragma mark -

ustring & ustring::operator = (const ustring & ustr)
{
	if (this == &ustr) {
		return *this;
	}
	m_ustr = ustr.m_ustr;
	return *this;
}

#pragma mark -

ustring & ustring::assign(const ustring & ustr)
{ m_ustr = ustr.m_ustr ; return *this; }

ustring & ustring::assign(ustring && ustr)
{ *this = std::move(ustr); return *this; }

void ustring::swap(ustring & ustr)
{
	icu::UnicodeString tmp(m_ustr);
	m_ustr = ustr.m_ustr;
	ustr.m_ustr = tmp;
}

std::uint16_t ustring::at(std::size_t index) const
{ return code_unit_at(index); }

std::uint32_t ustring::char_at(std::size_t index) const
{ return code_point_at(index); }

#pragma mark -

int ustring::compare(const ustring & other_ustr) const
{ return compare(other_ustr, search_literal|search_nowidth); }

int ustring::compare(const ustring & other_ustr, search_options options) const
{
	if (this == &other_ustr) {
		return cmp_same;
	}
	if ((options & search_literal) && ((options & search_nowidth) || (options & search_numeric))) {
		options &= ~search_literal;
	}
	return builtins::ustring_compare_utf16(m_ustr , other_ustr.m_ustr, options);
}

int ustring::icase_compare(const ustring & other_ustr) const
{ return icase_compare(other_ustr, search_literal|search_insensitive); }

int ustring::icase_compare(const ustring & other_ustr, search_options options) const
{
	if (this == &other_ustr) {
		return cmp_same;
	}
	if (!(options & search_insensitive)) {
		options |= search_insensitive;
	}
	if ((options & search_literal) && ((options & search_nowidth) || (options & search_numeric))) {
		options &= ~search_literal;
	}
	return builtins::ustring_compare_utf16(m_ustr , other_ustr.m_ustr, options);
}

int ustring::compare_localized(const ustring & other_ustr) const
{ return compare_localized(other_ustr, search_nowidth|search_forceorder); }

int ustring::compare_localized(const ustring & other_ustr, search_options options) const
{
	if (this == &other_ustr) {
		return cmp_same;
	}
	if ((options & search_literal) && ((options & search_nowidth) || (options & search_numeric))) {
		options &= ~search_literal;
	}
	//icu::Locale loc = icu::Locale::getDefault();
	icu::Locale loc = icu::Locale::getEnglish();
	return builtins::ustring_compare_utf16(m_ustr , other_ustr.m_ustr, options, &loc);
}

int ustring::icase_compare_localized(const ustring & other_ustr) const
{ return icase_compare_localized(other_ustr, search_insensitive|search_nowidth|search_forceorder); }

int ustring::icase_compare_localized(const ustring & other_ustr, search_options options) const
{
	if (this == &other_ustr) {
		return cmp_same;
	}
	if (!(options & search_insensitive)) {
		options |= search_insensitive;
	}
	if ((options & search_literal) && ((options & search_nowidth) || (options & search_numeric))) {
		options &= ~search_literal;
	}
	//icu::Locale loc = icu::Locale::getDefault();
	icu::Locale loc = icu::Locale::getEnglish();
	return builtins::ustring_compare_utf16(m_ustr , other_ustr.m_ustr, options, &loc);
}

#pragma mark -

bool ustring::is_valid() const
{ return m_ustr.isBogus() ? false : true; }

#pragma mark -

std::size_t ustring::capacity() const
{
	std::int32_t sz = m_ustr.getCapacity();
	if (sz) {
		return weak_cast<std::size_t>(sz);
	}
	return 0;
}

std::size_t ustring::size() const
{
	std::int32_t sz = m_ustr.length();
	if (sz) {
		return weak_cast<std::size_t>(sz);
	}
	return 0;
}

std::size_t ustring::length() const
{ return size(); }

std::size_t ustring::count() const
{
	if (size()) {
		return weak_cast<std::size_t>(m_ustr.countChar32());
	}
	return 0;
}

#pragma mark -

std::size_t ustring::size_for(encoding_option encoding) const
{
	std::int32_t sz = m_ustr.length();
	if (sz && encoding != encoding_auto) {
		std::string codepage = builtins::ustring_getcodepage(encoding);
		if (!codepage.size()) {
			return 0;
		}
		std::int32_t nb = m_ustr.extract(0, sz, NULL, codepage.c_str());
		if (nb) { return weak_cast<std::size_t>(nb); }
	}
	return 0;
}


#pragma mark -

void ustring::clear()
{ m_ustr.remove(); }

#pragma mark -

float ustring::to_float() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<float>(out);
	}
	return 0;
}

double ustring::to_double() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<double>(out);
	}
	return 0;
}

long double ustring::to_long_double() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<long double>(out);
	}
	return 0;
}

bool ustring::to_bool() const
{
	return to_double() > 0 ? true : false;
}

char ustring::to_char() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<char>(out);
	}
	return 0;
}

short ustring::to_short() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<short>(out);
	}
	return 0;
}

int ustring::to_int() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<int>(out);
	}
	return 0;
}

long ustring::to_long() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<long>(out);
	}
	return 0;
}

long long ustring::to_long_long() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<long long>(out);
	}
	return 0;
}

unsigned char ustring::to_unsigned_char() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<unsigned char>(out);
	}
	return 0;
}

unsigned short ustring::to_unsigned_short() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<unsigned short>(out);
	}
	return 0;
}

unsigned int ustring::to_unsigned_int() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<unsigned int>(out);
	}
	return 0;
}

unsigned long ustring::to_unsigned_long() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<unsigned long>(out);
	}
	return 0;
}

unsigned long long ustring::to_unsigned_long_long() const
{
	std::string out;
	bool isfp = false;
	if (builtins::ustring_parse_numeric(m_ustr, out, isfp)) {
		return algorithm::to_numeric<unsigned long long>(out);
	}
	return 0;
}

#pragma mark -

std::string ustring::to_string() const
{
	return to_utf8();
}

#pragma mark -

std::size_t ustring::hash_code() const
{
	std::int32_t hc = m_ustr.hashCode();
	return hc > 0 ? weak_cast<std::size_t>(hc) : 0UL;
}

#pragma mark -

const std::string ustring::to_utf8() const
{
	std::string result;
	m_ustr.toUTF8String<std::string>(result);
	return result;
}

const std::u16string ustring::to_utf16() const
{
	std::u16string result;
	const UChar * buff = m_ustr.getBuffer();
	const std::int32_t size = m_ustr.length();
	if (buff && size) {
		result.assign(buff, (buff + size));
	}
	return result;
}

const std::u32string ustring::to_utf32() const
{
	std::u32string result;
	UErrorCode err = U_ZERO_ERROR;
	const std::int32_t size = m_ustr.toUTF32(0, 0, err);
	if (err == U_ZERO_ERROR) {
		std::vector<UChar32> buff(static_cast<std::size_t>(size));
		m_ustr.toUTF32(buff.data(), size, err);
		if (err == U_ZERO_ERROR ) {
			result.assign(buff.begin(), buff.end());
		}
	}
	return result;
}

const std::u16string ustring::to_utf16_le() const
{
#if COCONUT_ARCH_BIG_ENDIAN
	std::u16string s = to_utf16();
	for (std::size_t i = 0 ; i < s.size() ; i++) {
		char16_t c = s[i];
		s[i] = runtime::byteorder::swpc16(c);
	}
	return s;
#else
	return to_utf16();
#endif
}

const std::u32string ustring::to_utf32_le() const
{
#if COCONUT_ARCH_BIG_ENDIAN
	std::u32string s = to_utf32();
	for (std::size_t i = 0 ; i < s.size() ; i++) {
		char32_t c = s[i];
		s[i] = runtime::byteorder::swpc32(c);
	}
	return s;
#else
	return to_utf32();
#endif
}

const std::u16string ustring::to_utf16_be() const
{
#if COCONUT_ARCH_BIG_ENDIAN
	return to_utf16();
#else
	std::u16string s0 = u"\uFFFE";
	std::u16string s1 = to_utf16();
	for (std::size_t i = 0 ; i < s1.size(); i++) {
		const char16_t c = s1[i];
		s1[i] = runtime::byteorder::swpc16(c);
	}
	return s1;
#endif
}

const std::u32string ustring::to_utf32_be() const
{
#if COCONUT_ARCH_BIG_ENDIAN
	return to_utf32();
#else
	std::u32string s = to_utf32();
	for (std::size_t i = 0 ; i < s.size() ; i++) {
		char32_t c = s[i];
		s[i] = runtime::byteorder::swpc32(c);
	}
	return s;
#endif
}

#pragma mark -

bool ustring::has_prefix(const ustring & ustr) const
{
	// TODO range_of + options search_nowidth|search_anchored
	
	return m_ustr.startsWith(ustr.m_ustr); // bit_cmp norms not wanted
}

bool ustring::has_suffix(const ustring & ustr) const
{
	// TODO range_of + options search_nowidth|search_anchored|search_backwards

	return m_ustr.endsWith(ustr.m_ustr); // bit_cmp norms not wanted
}

#pragma mark -

bool ustring::icase_has_prefix(const ustring & ustr) const
{
	// TODO range_of + options search_insensitive|search_nowidth|search_anchored

	if (size() >= ustr.size()) { // bit_cmp norms not wanted
		return (
			m_ustr.caseCompare(
				0,
				weak_cast<std::int32_t>(ustr.size()),
				ustr.m_ustr,
				U_FOLD_CASE_DEFAULT
			) == 0
		);
	
	}
	return false;
}

bool ustring::icase_has_suffix(const ustring & ustr) const
{
	// TODO range_of + options search_insensitive|search_nowidth|search_anchored|search_backwards

	if (size() >= ustr.size()) { // bit_cmp norms not wanted
		return (
			m_ustr.caseCompare(
				weak_cast<std::int32_t>(size() - ustr.size()),
				weak_cast<std::int32_t>(ustr.size()),
				ustr.m_ustr,
				U_FOLD_CASE_DEFAULT
			) == 0
		);
		
	}
	return false;
}

#pragma mark -

irange ustring::range_of(const ustring & ustr) const
{ return range_of(ustr, irange(0, weak_cast<std::size_t>(m_ustr.length())), search_literal); }

irange ustring::range_of(const ustring & ustr, const irange & in_rg) const
{ return range_of(ustr, in_rg, search_literal); }

irange ustring::range_of(const ustring & ustr, search_options options) const
{ return range_of(ustr, irange(0, weak_cast< std::size_t>(m_ustr.length())), options); }

irange ustring::range_of(const ustring & ustr, const irange & in_rg, search_options options) const
{ return builtins::ustring_rangeof(m_ustr, in_rg.location(), in_rg.length(), ustr.m_ustr, options); }

#pragma mark -

std::uint16_t ustring::code_unit_at(std::size_t index) const
{
	return weak_cast<std::uint16_t>(
		m_ustr.charAt(weak_cast<std::int32_t>(index))
	);
}

std::uint32_t ustring::code_point_at(std::size_t index) const
{
	return weak_cast<std::uint32_t>(
		m_ustr.char32At(weak_cast<std::int32_t>(index))
	);
}

#pragma mark -

ustring & ustring::append(const ustring & ustr)
{ m_ustr.append(ustr.m_ustr); return *this; }

ustring & ustring::append(std::int16_t & code_unit)
{ m_ustr.append(weak_cast<UChar>(code_unit)); return *this; }

ustring & ustring::append(std::int32_t & code_point)
{ m_ustr.append(weak_cast<UChar32>(code_point)); return *this; }

ustring & ustring::append(std::uint16_t & code_unit)
{ m_ustr.append(weak_cast<UChar>(code_unit)); return *this; }

ustring & ustring::append(std::uint32_t & code_point)
{ m_ustr.append(weak_cast<UChar32>(code_point)); return *this; }

#pragma mark -

ustring & ustring::capitalized()
{ m_ustr.toTitle(nullptr); return *this; }

ustring & ustring::lowercased()
{ m_ustr.toLower(); return *this; }

ustring & ustring::uppercased()
{ m_ustr.toUpper(); return *this; }

#pragma mark -

ustring ustring::by_appending(const ustring & ustr) const
{
	ustring result;
	result.m_ustr.append(m_ustr);
	result.m_ustr.append(ustr.m_ustr);
	return result;
}

#pragma mark -

ustring ustring::by_capitalizing(const ustring & ustr) const
{
	ustring result;
	result.m_ustr.append(m_ustr);
	result.m_ustr.toTitle(nullptr);
	return result;
}

ustring ustring::by_lowercasing(const ustring & ustr) const
{
	ustring result;
	result.m_ustr.append(m_ustr);
	result.m_ustr.toLower();
	return result;
}

ustring ustring::by_uppercasing(const ustring & ustr) const
{
	ustring result;
	result.m_ustr.append(m_ustr);
	result.m_ustr.toUpper();
	return result;
}

/* EOF */