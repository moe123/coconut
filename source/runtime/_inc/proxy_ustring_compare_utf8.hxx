//
// proxy_ustring_compare_utf8.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include "unicode/locid.h"
#include "unicode/coll.h"

namespace coconut
{
	namespace runtime
	{
		namespace _inc
		{
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			int ustring_compare_utf8(const std::string & utf8_a, const std::string & utf8_b, search_options options, icu::Locale * locale = nullptr)
			{
				int cmp = cmp_descending;
				if (options == search_default) {
					return algorithm::cmp(utf8_a, utf8_b);
				} else {
					bool insensitive = (options == search_insensitive || options & search_insensitive) ? true : false;
					bool diacritic = (options == search_diacritic || options & search_diacritic) ? true : false;
					bool literal = (options == search_literal || options & search_literal) ? true : false;
					bool nowidth = (options == search_nowidth || options & search_nowidth) ? true : false;
					if (!literal && (diacritic || nowidth)) {
						// TODO HANDLING OPTIONS LIKE IN THE UTF16 VERSION
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
								status = U_ZERO_ERROR;
								coll->setAttribute(UCOL_CASE_FIRST, UCOL_UPPER_FIRST, status);
							} else if (insensitive) {
								coll->setStrength(icu::Collator::SECONDARY);
							} else {
								coll->setStrength(icu::Collator::PRIMARY);
								status = U_ZERO_ERROR;
								coll->setAttribute(UCOL_CASE_LEVEL, UCOL_ON, status);
								status = U_ZERO_ERROR;
								coll->setAttribute(UCOL_CASE_FIRST, UCOL_UPPER_FIRST, status);
							}
							
							status = U_ZERO_ERROR;
							coll->setAttribute(UCOL_NORMALIZATION_MODE, UCOL_ON, status);
							status = U_ZERO_ERROR;
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
						if (insensitive) {
							cmp = algorithm::icmp(utf8_a, utf8_b);
						} else {
							cmp = algorithm::cmp(utf8_a, utf8_b);
						}
					}
				}
				return cmp;
			}
		}
	}
}

/* EOF */