//
// proxy_ustring_searching.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include "unicode/locid.h"
#include "unicode/stsearch.h"

namespace coconut
{
	namespace runtime
	{
		namespace _inc
		{
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			irange ustring_rangeof(const icu::UnicodeString & haystack, std::size_t start, std::size_t length, const icu::UnicodeString & needle, search_options options, icu::Locale * locale = nullptr)
			{
				std::int32_t idx = -1;
				std::int32_t len = 0;
				
				// TODO collator options and dealing with ``anchored` e.g stars_with / ends_with
				// e.g a mess if search_nowidth and/or different normalizations.
				if (options == search_default) {
					idx = haystack.indexOf(
						needle,
						unsafe_cast<std::int32_t>(start),
						unsafe_cast<std::int32_t>(length)
					);
					if (idx == -1) {
						return irange(NotFound, 0);
					}
					return irange(idx, unsafe_cast<std::size_t>(needle.length()));
				} else {
					bool insensitive = (options == search_insensitive || options & search_insensitive) ? true : false;
					bool diacritic = (options == search_diacritic || options & search_diacritic) ? true : false;
					bool literal = (options == search_literal || options & search_literal) ? true : false;
					bool backwards = (options == search_backwards || options & search_backwards) ? true : false;
					bool anchored = (options == search_anchored || options & search_anchored) ? true : false;
					bool nowidth = (options == search_nowidth || options & search_nowidth) ? true : false;
					bool numeric = (options == search_numeric || options & search_numeric) ? true : false;
					bool forceorder = (options == search_forceorder || options & search_forceorder) ? true : false;
					
					COCONUT_UNUSED(anchored);
					
					if (!literal && (diacritic || nowidth)) {
						UErrorCode status = U_ZERO_ERROR;
						icu::RuleBasedCollator * coll = unsafe_cast<RuleBasedCollator *>(icu::Collator::createInstance(
							((locale == nullptr) ? icu::Locale::getRoot() : *locale),
							status
						));
						if (U_FAILURE(status)) {
							if (insensitive) {
								if (backwards) {
									idx = icu::UnicodeString(haystack).toUpper().lastIndexOf(
										icu::UnicodeString(needle).toUpper(),
										unsafe_cast<std::int32_t>(start),
										unsafe_cast<std::int32_t>(length)
									);
								} else {
									idx = icu::UnicodeString(haystack).toUpper().indexOf(
										icu::UnicodeString(needle).toUpper(),
										unsafe_cast<std::int32_t>(start),
										unsafe_cast<std::int32_t>(length)
									);
								}
							} else {
								if (backwards) {
									idx = haystack.lastIndexOf(
										needle,
										unsafe_cast<std::int32_t>(start),
										unsafe_cast<std::int32_t>(length)
									);
								} else {
									idx = haystack.indexOf(needle,
										unsafe_cast<std::int32_t>(start),
										unsafe_cast<std::int32_t>(length)
									);
								}
							}
							if (idx == -1) {
								return irange(NotFound, 0);
							}
							return irange(idx, unsafe_cast<std::size_t>(needle.length()));
						} else {
							if (diacritic) {
								coll->setStrength(icu::Collator::TERTIARY);
							} else if (insensitive) {
								coll->setStrength(icu::Collator::SECONDARY);
							} else {
								coll->setStrength(icu::Collator::PRIMARY);
								status = U_ZERO_ERROR;
								coll->setAttribute(UCOL_CASE_LEVEL, UCOL_ON, status);
							}
							if (numeric) {
								status = U_ZERO_ERROR;
								coll->setAttribute(UCOL_NUMERIC_COLLATION, UCOL_ON, status);
							}
							if (forceorder && (insensitive || diacritic)) {
								status = U_ZERO_ERROR;
								coll->setAttribute(UCOL_CASE_FIRST, UCOL_LOWER_FIRST, status);
							} /* else {
								status = U_ZERO_ERROR;
								coll->setAttribute(UCOL_CASE_FIRST, UCOL_UPPER_FIRST, status);
							} */
							if (nowidth) {
								status = U_ZERO_ERROR;
								coll->setAttribute(UCOL_NORMALIZATION_MODE, UCOL_ON, status);
							}
							status = U_ZERO_ERROR;
							coll->setAttribute(UCOL_ALTERNATE_HANDLING, UCOL_NON_IGNORABLE, status);
							
							status = U_ZERO_ERROR;
							icu::StringSearch iter(
								needle,
								haystack.tempSubString(
									unsafe_cast<std::int32_t>(start),
									unsafe_cast<std::int32_t>(length)
								),
								coll,
								NULL,
								status
							);
							
							idx = -1;
							len = 0;
							status = U_ZERO_ERROR;
							if (backwards) {
								for (std::int32_t pos = iter.last(status); pos != USEARCH_DONE; pos = iter.previous(status)) {
									idx = pos;
									len = iter.getMatchedLength();
								}
							} else {
								for (std::int32_t pos = iter.first(status); pos != USEARCH_DONE; pos = iter.next(status)) {
									idx = pos;
									len = iter.getMatchedLength();
								}
							}
							if (U_FAILURE(status)) {
								return irange(NotFound, 0);
							}
							return irange(idx, unsafe_cast<std::size_t>(len));
						}
						delete coll;
					} else {
						if (insensitive) {
							if (backwards) {
								idx = icu::UnicodeString(haystack).toUpper().lastIndexOf(
									icu::UnicodeString(needle).toUpper(),
									unsafe_cast<std::int32_t>(start),
									unsafe_cast<std::int32_t>(length)
								);
							} else {
								idx = icu::UnicodeString(haystack).toUpper().indexOf(
									icu::UnicodeString(needle).toUpper(),
									unsafe_cast<std::int32_t>(start),
									unsafe_cast<std::int32_t>(length)
								);
							}
						} else {
							if (backwards) {
								idx = haystack.lastIndexOf(
									needle,
									unsafe_cast<std::int32_t>(start),
									unsafe_cast<std::int32_t>(length)
								);
							} else {
								idx = haystack.indexOf(needle,
									unsafe_cast<std::int32_t>(start),
									unsafe_cast<std::int32_t>(length)
								);
							}
						}
						if (idx == -1) {
							return irange(NotFound, 0);
						}
						return irange(idx, unsafe_cast<std::size_t>(needle.length()));
					}
				}
				return irange(NotFound, 0);
			}
		}
	}
}

/* EOF */