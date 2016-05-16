//
// String.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/String.hpp>
#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/Number.hpp>
#include <coconut/foundation/Range.hpp>

using namespace coconut;

String::String() :
	Object(StringClass),
	m_impl()
{ /* NOP */ }

String::String(const String & str) :
	Object(StringClass),
	m_impl(str.m_impl)
{ /* NOP */ }

String::String(String && str) noexcept :
	Object(StringClass),
	m_impl(std::move(str.m_impl))
{ /* NOP */ }

String::String(const std::string & str, StringEncodingOption encoding) :
	Object(StringClass),
	m_impl(str, encoding)
{ /* NOP */ }

String::String(const std::u16string & str, StringEncodingOption encoding) :
	Object(StringClass),
	m_impl(str, encoding)
{ /* NOP */ }

String::String(const std::u32string & str, StringEncodingOption encoding) :
	Object(StringClass),
	m_impl(str, encoding)
{ /* NOP */ }

String::String(const std::int8_t * bytes, std::size_t length, StringEncodingOption encoding) :
	Object(StringClass),
	m_impl(bytes, length, encoding)
{ /* NOP */ }

String::String(const std::int16_t * bytes, std::size_t length, StringEncodingOption encoding) :
	Object(StringClass),
	m_impl(bytes, length, encoding)
{ /* NOP */ }

String::String(const std::int32_t * bytes, std::size_t length, StringEncodingOption encoding) :
	Object(StringClass),
	m_impl(bytes, length, encoding)
{ /* NOP */ }

String::String(const std::uint8_t * bytes, std::size_t length, StringEncodingOption encoding) :
	Object(StringClass),
	m_impl(bytes, length, encoding)
{ /* NOP */ }

String::String(const std::uint16_t * bytes, std::size_t length, StringEncodingOption encoding) :
	Object(StringClass),
	m_impl(bytes, length, encoding)
{ /* NOP */ }

String::String(const std::uint32_t * bytes, std::size_t length, StringEncodingOption encoding) :
	Object(StringClass),
	m_impl(bytes, length, encoding)
{ /* NOP */ }

String::String(const char * utf8_str) :
	Object(StringClass),
	m_impl(utf8_str)
{ /* NOP */ }

String::String(const char16_t * utf16_str) :
	Object(StringClass),
	m_impl(utf16_str)
{ /* NOP */ }

String::String(const char32_t * utf32_str) :
	Object(StringClass),
	m_impl(utf32_str)
{ /* NOP */ }

String::~String()
{ /* NOP */ }

#pragma mark -

std::size_t String::hash() const
{ return m_impl.hash_code(); }

#pragma mark -

Owning<Any> String::copy() const
{ return ptr_create<String>(*this); }

#pragma mark -

Owning<Any> String::valueForSelectorKey(const std::string & utf8_selkey, Owning<Any> arg) const
{
	Owning<Any> val;
	if (isSelectorKey(utf8_selkey)) {
		if (arg && arg->isKindOf(*this)) {
			if (utf8_selkey == u8"@caseInsensitiveCompare:") {
				val = ptr_create<Number>(caseInsensitiveCompare(ref_cast<String>(*arg)));
			} else if (utf8_selkey == u8"@localizedCompare:") {
				val = ptr_create<Number>(localizedCompare(ref_cast<String>(*arg)));
			} else if (utf8_selkey == u8"@localizedStandardCompare:") {
				val = ptr_create<Number>(localizedStandardCompare(ref_cast<String>(*arg)));
			} else if (utf8_selkey == u8"@localizedCaseInsensitiveCompare:") {
				val = ptr_create<Number>(localizedCaseInsensitiveCompare(ref_cast<String>(*arg)));
			}
		}
		if (!val) {
			val = Object::valueForSelectorKey(utf8_selkey, arg);
		}
	}
	return val;
}

#pragma mark -

ComparisonResult String::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return m_impl.compare(ref_cast<String>(ref).m_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string String::stringValue() const
{ return m_impl.to_utf8(); }

std::u16string String::string16Value() const
{ return m_impl.to_utf16(); }

std::u32string String::string32Value() const
{ return m_impl.to_utf32(); }

#pragma mark -

std::size_t String::size() const
{ return m_impl.size(); }

#pragma mark -

float String::floatValue() const
{ return m_impl.to_float(); }

double String::doubleValue() const
{ return m_impl.to_double(); }

long double String::longDoubleValue() const
{ return m_impl.to_long_double(); }

bool String::boolValue() const
{ return m_impl.to_bool(); }

char String::charValue() const
{ return m_impl.to_char(); }

short String::shortValue() const
{ return m_impl.to_short(); }

int String::intValue() const
{ return m_impl.to_int(); }

long String::longValue() const
{ return m_impl.to_long(); }

long long String::longLongValue() const
{ return m_impl.to_long_long(); }

unsigned char String::unsignedCharValue() const
{ return m_impl.to_unsigned_char(); }

unsigned short String::unsignedShortValue() const
{ return m_impl.to_unsigned_short(); }

unsigned int String::unsignedIntValue() const
{ return m_impl.to_unsigned_int(); }

unsigned long String::unsignedLongValue() const
{ return m_impl.to_unsigned_long(); }

unsigned long long String::unsignedLongLongValue() const
{ return m_impl.to_unsigned_long_long(); }

#pragma mark -

ComparisonResult String::caseInsensitiveCompare(const String & str) const
{
	if (isIdenticalTo(str)) {
		return OrderedSame;
	}
	return m_impl.icase_compare(str.m_impl);
}

#pragma mark -

ComparisonResult String::localizedCompare(const String & str) const
{
	if (isIdenticalTo(str)) {
		return OrderedSame;
	}
	return m_impl.compare_localized(str.m_impl);
}

ComparisonResult String::localizedStandardCompare(const String & str) const
{
	if (isIdenticalTo(str)) {
		return OrderedSame;
	}
	return m_impl.compare_localized(str.m_impl);
}

ComparisonResult String::localizedCaseInsensitiveCompare(const String & str) const
{
	if (isIdenticalTo(str)) {
		return OrderedSame;
	}
	return m_impl.icase_compare_localized(str.m_impl);
}

#pragma mark -

bool String::hasPrefix(const String & str) const
{ return m_impl.has_prefix(str.m_impl); }

bool String::hasSuffix(const String & str) const
{ return m_impl.has_suffix(str.m_impl); }

#pragma mark -

bool String::hasCaseInsensitivePrefix(const String & str) const
{ return m_impl.icase_has_prefix(str.m_impl); }

bool String::hasCaseInsensitiveSuffix(const String & str) const
{ return m_impl.icase_has_suffix(str.m_impl); }

#pragma mark -

std::uint16_t String::codeUnitAtIndex(std::size_t index) const
{ return m_impl.code_unit_at(index); }

std::uint32_t String::codePointAtIndex(std::size_t index) const
{ return m_impl.code_point_at(index); }

#pragma mark -

std::uint32_t String::characterAtIndex(std::size_t index) const
{ return m_impl.code_point_at(index); }

#pragma mark -

void String::getCodeUnits(std::vector<std::uint16_t> & bv, const Range & rg)
{
	if (m_impl.size() && rg.maxRange() <= m_impl.size()) {
		std::size_t loc = rg.location();
		for (std::size_t i = 0; i < rg.length(); i++) {
			bv.push_back(m_impl.code_unit_at(loc + i));
		}
	}
}

void String::getCodePoints(std::vector<std::uint32_t> & bv, const Range & rg)
{
	if (m_impl.count() && rg.maxRange() <= m_impl.count()) {
		std::size_t loc = rg.location();
		for (std::size_t i = 0; i < rg.length(); i++) {
			bv.push_back(m_impl.code_point_at(loc + i));
		}
	}
}

#pragma mark -

void String::getCharacters(std::vector<std::uint32_t> & bv, const Range & rg)
{ return getCodePoints(bv, rg); }

#pragma mark -

std::size_t String::numberOfCodeUnits() const
{ return m_impl.size(); }

std::size_t String::numberOfCodePoints() const
{ return m_impl.count(); }

#pragma mark -

std::size_t String::numberOfCharacters() const
{ return m_impl.count(); }

std::size_t String::length() const
{ return m_impl.size(); }

std::size_t String::lengthOfBytesUsingEncoding(StringEncodingOption encoding) const
{ return m_impl.size_for(encoding); }

#pragma mark -

const String String::stringByAppendingString(const String & append) const
{
	String result = String(*this);
	result.m_impl.append(append.m_impl);
	return result;
}

const String String::stringByPaddingToLength(std::size_t newLength, const String & padString, std::size_t padIndex) const
{
	return {};
}

#pragma mark -

const Range String::rangeOfString(const String & str) const
{
	Range rg;
	rg.m_impl = std::move(m_impl.range_of(str.m_impl));
	return rg;
}

const Range String::rangeOfString(const String & str, const Range & in_rg) const
{
	Range rg;
	rg.m_impl = std::move(m_impl.range_of(str.m_impl, in_rg.m_impl));
	return rg;
}

const Range String::rangeOfString(const String & str, StringSearchOptions options) const
{
	Range rg;
	rg.m_impl = std::move(m_impl.range_of(str.m_impl, options));
	return rg;
}

const Range String::rangeOfString(const String & str, const Range & in_rg, StringSearchOptions options) const
{
	Range rg;
	rg.m_impl = std::move(m_impl.range_of(str.m_impl, in_rg.m_impl, options));
	return rg;
}

#pragma mark -

const Array String::componentsSeparatedByString(const String & separator) const
{
	return {};
}

const String String::stringByReplacingOccurrencesOfString(const String & target, const String & replacement) const
{
	return {};
}

const String String::substringFromIndex(std::size_t index) const
{
	return {};
}

const String String::substringWithRange(const Range & rg) const
{
	return {};
}

const String String::substringToIndex(std::size_t index) const
{
	return {};
}

const String String::capitalizedString() const
{
	String result = String(*this);
	result.m_impl.capitalized();
	return result;
}

const String String::lowercaseString() const
{
	String result = String(*this);
	result.m_impl.lowercased();
	return result;
}

const String String::uppercaseString() const
{
	String result = String(*this);
	result.m_impl.uppercased();
	return result;
}

#pragma mark -

const std::uint32_t String::operator [] (std::size_t index) const
{ return characterAtIndex(index); }

#pragma mark -

const String String::operator + (const String & str) const
{ return stringByAppendingString(str); }

const String String::operator + (const Owning<String> & str) const
{ if (str) { return stringByAppendingString(*str); } return String(*this); }

#pragma mark -

bool coconut::operator == (const String & left, const String & right)
{ return (left.compare(right) == OrderedSame); }

bool coconut::operator != (const String & left, const String & right)
{ return (left.compare(right) != OrderedSame); }

bool coconut::operator < (const String & left, const String & right)
{ return (left.compare(right) == OrderedAscending); }

bool coconut::operator <= (const String & left, const String & right)
{
	ComparisonResult cmp = left.compare(right);
	return (cmp == OrderedAscending || cmp == OrderedSame);
}

bool coconut::operator > (const String & left, const String & right)
{ return (left.compare(right) == OrderedDescending); }

bool coconut::operator >= (const String & left, const String & right)
{
	ComparisonResult cmp = left.compare(right);
	return (cmp == OrderedDescending || cmp == OrderedSame);
}

/* EOF */