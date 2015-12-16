//
// locale.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_LOCALE_HPP
#define COCONUT_RUNTIME_LOCALE_HPP

namespace coconut
{
	namespace runtime
	{
		COCONUT_PRIVATE class COCONUT_EXPORT locale COCONUT_FINAL
		{
		COCONUT_RUNTIME_KDCL(coconut.runtime.locale, locale)
			
		public:
			locale();
			locale(const locale & locl);
			virtual ~locale();
			
			locale & operator = (const locale & locl);
			int compare(const locale & other_locl) const;
		};
	}
}

#endif /* !COCONUT_RUNTIME_LOCALE_HPP */

/* EOF */