//
// nutrt-ustring_parsing.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include "unicode/locid.h"
#include "unicode/schriter.h"
#include "unicode/dcfmtsym.h"
#include "unicode/numfmt.h"

namespace coconut {
	namespace runtime {
		namespace builtins {

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ustring_parse_numeric(const icu::UnicodeString & in, std::string & out, bool & isfp, icu::Locale * locale = nullptr)
{
	bool result = false;
	UErrorCode status = U_ZERO_ERROR;
	icu::NumberFormat * fmt = icu::NumberFormat::createInstance(((locale == nullptr) ? icu::Locale::getRoot() : *locale), status);
	isfp = false;
	if (U_SUCCESS(status)) {
		icu::Formattable buf;
		status = U_ZERO_ERROR;
		icu::UnicodeString tmp(in);
		fmt->parse(tmp.trim(), buf, status);
		if (U_SUCCESS(status)) {
			status = U_ZERO_ERROR;
			icu::StringPiece str = buf.getDecimalNumber(status);
			if (U_SUCCESS(status)) {
				if (buf.getType() == icu::Formattable::kDouble) {
					isfp = true;
				}
				out = str.data();
				result = true;
			}
		}
	}
	if (!result) { out = "0"; }
	delete fmt;
	return result;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ustring_parse_numeric_v1(const icu::UnicodeString & in, std::string & out, bool & isfp, icu::Locale * locale = nullptr)
{
	//TODO Scanner, CharacterSet
	
	bool result = false;
	bool have_digit = false;
	bool have_sep = false;
	
	UChar32 PLUS_SIGN = 43; // 0x002B \u002B
	UChar32 MINUS_SIGN = 45; // 0x002D \u002D
	UChar32 FULL_STOP = 46; // 0x002E \u002E
	
	UChar32 EXPONENT_LC = 101; // 0x0065 \u0065
	UChar32 EXPONENT_UC = 69; // 0x0045 \u0045
	
	UChar32 PLUS_SIGN_LOC = PLUS_SIGN;
	UChar32 MINUS_SIGN_LOC = MINUS_SIGN;
	UChar32 FULL_STOP_LOC = FULL_STOP;
	UChar32 EXPONENT_LOC = EXPONENT_UC;
	
	icu::UnicodeString buf;
	
	UErrorCode status = U_ZERO_ERROR;
	
	isfp = false;
	
	icu::DecimalFormatSymbols dcms = icu::DecimalFormatSymbols(((locale == nullptr) ? icu::Locale::getRoot() : *locale), status);
	if (U_SUCCESS(status)) {
		icu::UnicodeString sym = dcms.getSymbol(icu::DecimalFormatSymbols::kPlusSignSymbol);
		if (sym.countChar32()) {
			PLUS_SIGN_LOC = sym.char32At(0);
		}
		sym = dcms.getSymbol(icu::DecimalFormatSymbols::kMinusSignSymbol);
		if (sym.countChar32()) {
			MINUS_SIGN_LOC = sym.char32At(0);
		}
		sym = dcms.getSymbol(icu::DecimalFormatSymbols::kDecimalSeparatorSymbol);
		if (sym.countChar32()) {
			FULL_STOP_LOC = sym.char32At(0);
		}
		
		sym = dcms.getSymbol(icu::DecimalFormatSymbols::kExponentialSymbol);
		if (sym.countChar32()) {
			EXPONENT_LOC = sym.char32At(0);
		}
	}
	
	COCONUT_UNUSED(EXPONENT_LOC);
	COCONUT_UNUSED(EXPONENT_LC);
	COCONUT_UNUSED(EXPONENT_UC);
	
	icu::StringCharacterIterator iter(in);
	
	while(iter.hasNext()) {
		UChar32 c32 = iter.current32();
		if (u_isspace(c32)|| u_isblank(c32)) { iter.next32(); } else { break; }
	}
	
	while(iter.hasNext()) {
		UChar32 c32 = iter.current32();
		if (c32 == PLUS_SIGN_LOC || c32 == PLUS_SIGN) {
			buf.append(PLUS_SIGN); iter.next32();
		} else if (c32 == MINUS_SIGN_LOC || c32 == MINUS_SIGN) {
			buf.append(MINUS_SIGN); iter.next32();
		}
		break;
	}
	
	while(iter.hasNext()) {
		UChar32 c32 = iter.current32();
		if (c32 == FULL_STOP_LOC || c32 == FULL_STOP) {
			buf.append(FULL_STOP);
			iter.next32();
			isfp = true;
			have_sep = true;
		} break;
	}
	
	while(iter.hasNext()) {
		UChar32 c32 = iter.current32();
		if (u_isdigit(c32)) {
			buf.append(c32);
			have_digit = true;
			iter.next32();
		} else if (!have_sep && (c32 == FULL_STOP_LOC || c32 == FULL_STOP)) {
			buf.append(FULL_STOP);
			isfp = true;
			have_sep = true;
			iter.next32();
		} else { break; }
	}
	
	// TODO parse exponent
	// rule: if have next and first next not blank or exponent then reject
	// if exponent
	//   is followed by sign add and continue
	//   add exponent digits
	// then if digit and have next and first next not blank then reject
	
	if (have_digit) {
		result = true;
		buf.toUTF8String<std::string>(out);
	} else {
		buf.remove();
		out = "0";
	}
	return result;
}

}}} /* EONS */

/* EOF */