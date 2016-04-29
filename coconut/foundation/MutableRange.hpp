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
	COCONUT_PUBLIC class COCONUT_VISIBLE MutableRange COCONUT_FINAL : public Range
	{
	COCONUT_CLASSDECLARE(coconut.MutableRange, Object.Range.MutableRange)
		
	public:
		MutableRange();
		MutableRange(const MutableRange & rg);
		MutableRange(const Range & rg);
		MutableRange(std::size_t location, std::size_t length);
		virtual ~MutableRange();
		
		MutableRange & setLocation(std::size_t location);
		MutableRange & setLength(std::size_t length);
	};
}

#endif /* !COCONUT_FOUNDATION_MUTABLERANGE_HPP */

/* EOF */