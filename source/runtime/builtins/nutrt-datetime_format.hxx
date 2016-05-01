//
// nutrt-datetime_format.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include "unicode/calendar.h"
#include "unicode/dtfmtsym.h"
#include "unicode/smpdtfmt.h"
#include "unicode/fieldpos.h"

namespace coconut {
	namespace runtime {
		namespace builtins {

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string datetime_format_utc(double milliseconds)
{
	UErrorCode status = U_ZERO_ERROR;
	
	icu::SimpleDateFormat dtf = icu::SimpleDateFormat
	(
		icu::UnicodeString::fromUTF8(icu::StringPiece(u8"yyyy-MM-dd'T'HH:mm:ss.SSS'Z'")),
		icu::Locale::getRoot(),
		status
	);
	
	dtf.setTimeZone(*(icu::TimeZone::getGMT()));
	icu::UnicodeString buf;
	dtf.format(milliseconds, buf);
	
	std::string result;
	buf.toUTF8String<std::string>(result);
	return result;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
double datetime_parse_utc(const std::string & utc)
{
	UErrorCode status = U_ZERO_ERROR;
	UDate milliseconds = 0.0;
	
	constexpr auto fmt_short = u8"yyyy-MM-dd'T'HH:mm:ss'Z'";
	constexpr auto fmt_long = u8"yyyy-MM-dd'T'HH:mm:ss.SSS'Z'";
	
	icu::SimpleDateFormat dtf = icu::SimpleDateFormat
	(
		icu::UnicodeString::fromUTF8(
			icu::StringPiece(
				(utc.find(".") != std::string::npos) ? fmt_long : fmt_short
			)
		),
		icu::Locale::getRoot(),
		status
	);
	
	if (U_FAILURE(status)) {
		return 0.0;
	}
	
	UnicodeString buf = UnicodeString::fromUTF8(icu::StringPiece(utc));
	dtf.setTimeZone(*(icu::TimeZone::getGMT()));
	icu::ParsePosition pos(0);
	milliseconds = dtf.parse(
		buf,
		pos
	);
	if (!milliseconds) {
		status = U_ZERO_ERROR;
		dtf.applyLocalizedPattern(
			icu::UnicodeString::fromUTF8(icu::StringPiece(fmt_short)),
			status
		);
		if (U_FAILURE(status)) {
			return 0.0;
		}
		milliseconds = dtf.parse(
			buf,
			pos
		);
	}
	return milliseconds;
}

}}} /* EONS */

/* EOF */