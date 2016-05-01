//
// nutrt-ustring_searching.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include "unicode/locid.h"
#include "unicode/stsearch.h"

namespace coconut {
	namespace runtime {
		namespace builtins {

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
irange ustring_rangeof(const icu::UnicodeString & haystack, std::size_t start, std::size_t length, const icu::UnicodeString & needle, search_options options, icu::Locale * locale = nullptr)
{
	std::int32_t idx = -1;
	std::int32_t len = 0;
	
	// TODO dealing with ``anchored` e.g stars_with / ends_with
	// e.g a mess if search_nowidth and/or different normalizations ; find a rule.
	
	bool literal = (options == search_literal || options & search_literal) ? true : false;
	bool insensitive = (options == search_insensitive || options & search_insensitive) ? true : false;
	bool diacritic = (options == search_diacritic || options & search_diacritic) ? true : false;
	bool backwards = (options == search_backwards || options & search_backwards) ? true : false;
	bool anchored = (options == search_anchored || options & search_anchored) ? true : false;
	
	COCONUT_UNUSED(anchored);
		
	if (!literal) {
		bool nowidth = (options == search_nowidth || options & search_nowidth) ? true : false;
		bool numeric = (options == search_numeric || options & search_numeric) ? true : false;
		bool forceorder = (options == search_forceorder || options & search_forceorder) ? true : false;
		
		// TODO CACHING COLLATORS
		UErrorCode status = U_ZERO_ERROR;
		icu::RuleBasedCollator * coll = weak_cast<RuleBasedCollator *>(icu::Collator::createInstance(
			((locale == nullptr) ? icu::Locale::getRoot() : *locale),
			status
		));
		if (U_FAILURE(status)) {
			if (insensitive) {
				if (backwards) {
					idx = icu::UnicodeString(haystack).toUpper().lastIndexOf(
						icu::UnicodeString(needle).toUpper(),
						weak_cast<std::int32_t>(start),
						weak_cast<std::int32_t>(length)
					);
				} else {
					idx = icu::UnicodeString(haystack).toUpper().indexOf(
						icu::UnicodeString(needle).toUpper(),
						weak_cast<std::int32_t>(start),
						weak_cast<std::int32_t>(length)
					);
				}
			} else {
				if (backwards) {
					idx = haystack.lastIndexOf(
						needle,
						weak_cast<std::int32_t>(start),
						weak_cast<std::int32_t>(length)
					);
				} else {
					idx = haystack.indexOf(needle,
						weak_cast<std::int32_t>(start),
						weak_cast<std::int32_t>(length)
					);
				}
			}
			if (idx == -1) {
				return irange(NotFound, 0);
			}
			return irange(idx, weak_cast<std::size_t>(needle.length()));
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
			if (forceorder) {
				status = U_ZERO_ERROR;
				coll->setAttribute(UCOL_CASE_FIRST, UCOL_LOWER_FIRST, status);
			}
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
					weak_cast<std::int32_t>(start),
					weak_cast<std::int32_t>(length)
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
			return irange(idx, weak_cast<std::size_t>(len));
		}
		delete coll;
	} else {
		if (insensitive || diacritic) {
			if (backwards) {
				idx = icu::UnicodeString(haystack).toUpper().lastIndexOf(
					icu::UnicodeString(needle).toUpper(),
					weak_cast<std::int32_t>(start),
					weak_cast<std::int32_t>(length)
				);
			} else {
				idx = icu::UnicodeString(haystack).toUpper().indexOf(
					icu::UnicodeString(needle).toUpper(),
					weak_cast<std::int32_t>(start),
					weak_cast<std::int32_t>(length)
				);
			}
		} else {
			if (backwards) {
				idx = haystack.lastIndexOf(
					needle,
					weak_cast<std::int32_t>(start),
					weak_cast<std::int32_t>(length)
				);
			} else {
				idx = haystack.indexOf(needle,
					weak_cast<std::int32_t>(start),
					weak_cast<std::int32_t>(length)
				);
			}
		}
		if (idx == -1) {
			return irange(NotFound, 0);
		}
		return irange(idx, weak_cast<std::size_t>(needle.length()));
	}
	return irange(NotFound, 0);
}

}}} /* EONS */

/* EOF */