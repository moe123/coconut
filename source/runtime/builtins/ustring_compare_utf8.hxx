//
// ustring_compare_utf8.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include "unicode/locid.h"
#include "unicode/coll.h"

namespace coconut
{
	namespace runtime
	{
		namespace builtins
		{
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			int ustring_compare_utf8(const std::string & utf8_a, const std::string & utf8_b, search_options options, icu::Locale * locale = nullptr)
			{
				int cmp = cmp_descending;
				bool literal = (options == search_literal || options & search_literal) ? true : false;
				bool insensitive = (options == search_insensitive || options & search_insensitive) ? true : false;
				bool diacritic = (options == search_diacritic || options & search_diacritic) ? true : false;
				
				if (!literal) {
					bool nowidth = (options == search_nowidth || options & search_nowidth) ? true : false;
					bool numeric = (options == search_numeric || options & search_numeric) ? true : false;
					bool forceorder = (options == search_forceorder || options & search_forceorder) ? true : false;
					
					// TODO CACHING COLLATORS
					UErrorCode status = U_ZERO_ERROR;
					icu::Collator * coll = icu::Collator::createInstance(
						((locale == nullptr) ? icu::Locale::getRoot() : *locale),
						status
					);
					if (U_FAILURE(status)) {
						if (insensitive || diacritic) {
							cmp = algorithm::icmp(utf8_a, utf8_b);
						} else {
							cmp = algorithm::cmp(utf8_a, utf8_b);
						}
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
						} /* else {
						   status = U_ZERO_ERROR;
						   coll->setAttribute(UCOL_CASE_FIRST, UCOL_UPPER_FIRST, status);
						   } */
						if (nowidth) {
							status = U_ZERO_ERROR;
							coll->setAttribute(UCOL_NORMALIZATION_MODE, UCOL_ON, status);
						}
						coll->setAttribute(UCOL_ALTERNATE_HANDLING, UCOL_NON_IGNORABLE, status);
						status = U_ZERO_ERROR;
						
						cmp = unsafe_cast<int>(coll->compareUTF8(icu::StringPiece(utf8_a), icu::StringPiece(utf8_b), status));
						if (U_FAILURE(status)) {
							if (insensitive || diacritic) {
								cmp = algorithm::icmp(utf8_a, utf8_b);
							} else {
								cmp = algorithm::cmp(utf8_a, utf8_b);
							}
						}
					}
					delete coll;
					return cmp;
				} else {
					if (insensitive || diacritic) {
						cmp = algorithm::icmp(utf8_a, utf8_b);
					} else {
						cmp = algorithm::cmp(utf8_a, utf8_b);
					}
				}
				return cmp;
			}
		}
	}
}

/* EOF */