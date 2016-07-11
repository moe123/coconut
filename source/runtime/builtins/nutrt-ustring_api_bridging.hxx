//
// nutrt-ustring_encoding.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

namespace coconut
{ namespace runtime
{ namespace builtins
{

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
byteorder_type ustring_if_bom(const icu::UnicodeString & in)
{
	const UChar * buff = in.getBuffer();
	if (buff && in.length()) {
		if (buff[0] == 0xFEFF) {
			return byteorder_bigendian;
		} else if (buff[0] == 0xFFFE) {
			return byteorder_littleendian;
		}
	}
	return byteorder_platform;
}
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
byteorder_type ustring_storage_endianess()
{
	std::string src(u8"\xEF\xBB\xBF");
	icu::UnicodeString dest = icu::UnicodeString::fromUTF8(icu::StringPiece(src));
	const UChar * buff = dest.getBuffer();;
	if (buff && dest.length()) {
		if (buff[0] == 0xFEFF) {
			return byteorder_bigendian;
		} else if (buff[0] == 0xFFFE) {
			return byteorder_littleendian;
		}
	}
	return byteorder_unknown;
}
	
namespace
{
	
static byteorder_type const ustring_storage = ustring_storage_endianess();

} /* EONS */
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ustring_to_del_bom(icu::UnicodeString & src)
{
	byteorder_type ret = ustring_if_bom(src);
	if (ret != byteorder_platform && src.length()) {
		src.remove(0, 1);
	}
	return ret;
}
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ustring_to_std_u8string(
	const icu::UnicodeString & src
	, std::string & dest_utf8
	, unicode_option option
) {
	src.toUTF8String<std::string>(dest_utf8);
	switch (option)
	{
		case unicode_conv_gen_bom:
			unicode::utf8_add_bom(dest_utf8);
			break;
		default:
			unicode::utf8_del_bom(dest_utf8);
			break;
	}
	return (dest_utf8.size() > 0);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
byteorder_type ustring_to_std_u16string(
	const icu::UnicodeString & src
	, std::u16string & dest_utf16
	, unicode_option option
) {
	byteorder_type ret = byteorder_unknown;
	
	const UChar * buff = src.getBuffer();
	const std::int32_t size = src.length();
	
	byteorder_type src_storage = ustring_storage;
	byteorder_type dest_storage = unicode::_utf16_storage;

	if (buff && size) {
	
		if (
			src_storage != byteorder_unknown &&
			dest_storage != byteorder_unknown
		) {
			if (ustring_storage == unicode::_utf16_storage) {
				for (std::size_t i = 0 ; i < size ; i++) {
					dest_utf16[i] = weak_cast<char16_t>(buff[i]);
				}
				ret = src_storage;
			} else {
				for (std::size_t i = 0 ; i < size ; i++) {
					dest_utf16[i] = runtime::byteorder::swpc16(
						weak_cast<const volatile std::uint16_t>(buff[i])
					);
				}
				ret = dest_storage;
			}
			switch (option)
			{
				case unicode_conv_gen_bom:
					unicode::utf16_add_bom(dest_utf16, ret);
					break;
				default:
					unicode::utf16_del_bom(dest_utf16);
					break;
			}
			return ret;
		}
	} else {
		ret = byteorder_platform;
	}
	return ret;
}
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
byteorder_type ustring_to_std_u32string(
	const icu::UnicodeString & src
	, std::u32string & dest_utf32
	, unicode_option option
) {
	byteorder_type ret = byteorder_unknown;
	
	std::vector<UChar32> buff;
	UErrorCode err = U_ZERO_ERROR;
	const std::int32_t size = src.toUTF32(0, 0, err);
	if (err == U_ZERO_ERROR) {
		buff.resize(static_cast<std::size_t>(size));
		src.toUTF32(buff.data(), size, err);
	}
	
	if (err == U_ZERO_ERROR) {
	
		byteorder_type src_storage = ustring_storage;
		byteorder_type dest_storage = unicode::_utf32_storage;
		
		if (size) {
			if (
				src_storage != byteorder_unknown &&
				dest_storage != byteorder_unknown
			) {
				if (ustring_storage == unicode::_utf32_storage) {
					for (std::size_t i = 0 ; i < size ; i++) {
						dest_utf32[i] = weak_cast<char32_t>(buff[i]);
					}
					ret = src_storage;
				} else {
					for (std::size_t i = 0 ; i < size ; i++) {
						dest_utf32[i] = runtime::byteorder::swpc32(
								weak_cast<const volatile std::uint32_t>(buff[i])
						);
					}
					ret = dest_storage;
				}
				switch (option)
				{
					case unicode_conv_gen_bom:
						// unicode::utf32_add_bom(dest_utf32, ret);
					break;
					default:
						// unicode::utf32_del_bom(dest_utf32);
					break;
				}
				return ret;
			}
		} else {
			ret = byteorder_platform;
		}
	}
	return ret;
}

}}} /* EONS */

/* EOF */