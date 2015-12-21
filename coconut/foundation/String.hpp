//
// String.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_STRING_HPP
#define COCONUT_FOUNDATION_STRING_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT String : public Object
	{
	COCONUT_KDCL(coconut.String, Object.String)
		
	public:
		String();
		String(const String & str);
		String & operator = (const String & str) = default;
		
		String(const std::string & str, StringEncodingOption encoding = StringEncodingUTF8);
		String(const std::u16string & str, StringEncodingOption encoding= StringEncodingUTF16);
		String(const std::u32string & str, StringEncodingOption encoding= StringEncodingUTF32);
		
		String(const std::uint8_t * bytes, std::size_t length, StringEncodingOption encoding);
		String(const std::uint16_t * bytes, std::size_t length, StringEncodingOption encoding);
		String(const std::uint32_t * bytes, std::size_t length, StringEncodingOption encoding);
		
		String(const char * utf8_str);
		String(const char16_t * utf16_str);
		String(const char32_t * utf32_str);
		
		virtual ~String();
		
		// COCONUT_KTOD String normalize(const String & str, NormalizationForm option);
		
		template <typename... ArgsT>
		COCONUT_KTOD String format(const char * utf8_fmt, ArgsT &&... args)
		{ return String(impl_type::uformat(utf8_fmt, std::forward<ArgsT>(args)...)); }
		
		template <typename... ArgsT>
		COCONUT_KTOD String format(const char16_t * utf16_fmt, ArgsT &&... args)
		{ return String(impl_type::uformat(utf16_fmt, std::forward<ArgsT>(args)...)); }
		
		COCONUT_KTOR StringPtr with();
		COCONUT_KTOR StringPtr with(const String & str);
		
		COCONUT_KTOR StringPtr with(const std::string & str, StringEncodingOption encoding = StringEncodingUTF8);
		COCONUT_KTOR StringPtr with(const std::u16string & str, StringEncodingOption encoding= StringEncodingUTF16);
		COCONUT_KTOR StringPtr with(const std::u32string & str, StringEncodingOption encoding= StringEncodingUTF32);
		
		COCONUT_KTOR StringPtr with(const std::uint8_t * bytes, std::size_t length, StringEncodingOption encoding);
		COCONUT_KTOR StringPtr with(const std::uint16_t * bytes, std::size_t length, StringEncodingOption encoding);
		COCONUT_KTOR StringPtr with(const std::uint32_t * bytes, std::size_t length, StringEncodingOption encoding);
		
		COCONUT_KTOR StringPtr with(const char * utf8_str);
		COCONUT_KTOR StringPtr with(const char16_t * utf16_str);
		COCONUT_KTOR StringPtr with(const char32_t * utf32_str);
	
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> valueForSelectorKey(const std::string & utf8_selkey, Owning<Any> arg = {}) const
		COCONUT_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::u16string string16Value() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::u32string string32Value() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual float floatValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual double doubleValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual long double longDoubleValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual bool boolValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual char charValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual short shortValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual int intValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual long longValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual long long longLongValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned char unsignedCharValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned short unsignedShortValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned int unsignedIntValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned long unsignedLongValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned long long unsignedLongLongValue() const
		COCONUT_FINAL_OVERRIDE;
		
		ComparisonResult caseInsensitiveCompare(const String & str) const;
		ComparisonResult localizedCompare(const String & str) const;
		ComparisonResult localizedStandardCompare(const String & str) const;
		ComparisonResult localizedCaseInsensitiveCompare(const String & str) const;
		
		bool hasPrefix(const String & str) const;
		bool hasSuffix(const String & str) const;
		
		bool hasCaseInsensitivePrefix(const String & str) const;
		bool hasCaseInsensitiveSuffix(const String & str) const;
		
		std::uint16_t codeUnitAtIndex(std::size_t index) const;
		std::uint32_t codePointAtIndex(std::size_t index) const;
		std::uint32_t characterAtIndex(std::size_t index) const;
		
		void getCodeUnits(std::vector<std::uint16_t> & bv, const Range & rg);
		void getCodePoints(std::vector<std::uint32_t> & bv, const Range & rg);
		void getCharacters(std::vector<std::uint32_t> & bv, const Range & rg);
		
		std::size_t numberOfCodeUnits() const;
		std::size_t numberOfCodePoints() const;
		std::size_t numberOfCharacters() const;
		
		std::size_t length() const;
		std::size_t lengthOfBytesUsingEncoding(StringEncodingOption encoding) const;
		
		template <typename... ArgsT>
		const String stringByAppendingFormat(const char * utf8_fmt, ArgsT &&... args) const
		{ return stringByAppendingString(String::format(utf8_fmt, args...)); }
		
		template <typename... ArgsT>
		const String stringByAppendingFormat(const char16_t * utf16_fmt, ArgsT &&... args) const
		{ return stringByAppendingString(String::format(utf16_fmt, args...)); }
								 
		const String stringByAppendingString(const String & append) const;
		const String stringByPaddingToLength(std::size_t new_len, const String & pad_str, std::size_t pad_idx) const;
		
		const Range rangeOfString(const String & str) const;
		const Range rangeOfString(const String & str, const Range & in_rg)const;
		const Range rangeOfString(const String & str, StringSearchOptions options) const;
		const Range rangeOfString(const String & str, const Range & in_rg, StringSearchOptions options) const;
		
		ArrayPtr componentsSeparatedByString(const String & separator) const;
		
		const String stringByReplacingOccurrencesOfString(const String & target, const String & replacement) const;
		
		const String substringFromIndex(std::size_t index) const;
		const String substringWithRange(const Range & rg) const;
		const String substringToIndex(std::size_t index) const;
		
		const String capitalizedString() const;
		const String lowercaseString() const;
		const String uppercaseString() const;
		
	public:
		const std::uint32_t operator [] (std::size_t index) const;
	
	public:
		bool operator == (const String & other_str) const;
		bool operator != (const String & other_str) const;
		bool operator <  (const String & other_str) const;
		bool operator <= (const String & other_str) const;
		bool operator >  (const String & other_str) const;
		bool operator >= (const String & other_str) const;
	
	public:
		friend inline std::ostream & operator << (std::ostream & os, const StringPtr ptr)
		{ if (ptr) { os << ptr->stringValue(); } return os; }
		
	protected:
		friend class Path;
		
	protected:
		typedef runtime::ustring impl_type;

	protected:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_STRING_HPP */

/* EOF */