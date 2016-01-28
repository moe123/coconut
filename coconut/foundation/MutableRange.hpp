//
// MutableRange.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Range.hpp>

#ifndef COCONUT_FOUNDATION_MUTABLERANGE_HPP
#define COCONUT_FOUNDATION_MUTABLERANGE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT MutableRange COCONUT_FINAL : public Range
	{
	COCONUT_KDCL(coconut.MutableRange, Object.Range.MutableRange)
		
	public:
		MutableRange();
		MutableRange(const MutableRange & rg);
		MutableRange(const Range & rg);
		MutableRange(std::size_t location, std::size_t length);
		virtual ~MutableRange();
		
		void setLocation(std::size_t location);
		void setLength(std::size_t length);
	};
}

#endif /* !COCONUT_FOUNDATION_MUTABLERANGE_HPP */

/* EOF */