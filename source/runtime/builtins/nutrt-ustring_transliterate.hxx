//
// nutrt-ustring_transliterate.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <unicode/translit.h>

namespace coconut
{ namespace runtime
{ namespace builtins
{

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ustring_transliterate(
	const std::string & utf8_in
	, std::string & translit_out
) {
	bool result = false;
	icu::UnicodeString str = icu::UnicodeString::fromUTF8(icu::StringPiece(utf8_in));

	UErrorCode status = U_ZERO_ERROR;
	icu::Transliterator * trsl = icu::Transliterator::createInstance(
		u8"NFD; [:M:] Remove; NFC", UTRANS_FORWARD, status
	);
	
	if (U_FAILURE(status)) {
		delete trsl;
		status = U_ZERO_ERROR;
		trsl = icu::Transliterator::createInstance(
			u8"NFD; [:M:] Remove; NFC", UTRANS_REVERSE, status
		);
	}
	
	if (U_FAILURE(status)) {
		delete trsl;
		return result;
	} else {
		result = true;
		trsl->transliterate(str);
		translit_out.clear();
		str.toUTF8String(translit_out);
		delete trsl;
	}
	return result;
}

}}} /* EONS */

/* EOF */