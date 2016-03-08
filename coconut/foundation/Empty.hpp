//
// Empty.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_EMPTY_HPP
#define COCONUT_FOUNDATION_EMPTY_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Empty COCONUT_FINAL : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Empty, Object.Empty)
		
	public:
		Empty();
		Empty(const Empty & emp);
		virtual ~Empty();

		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
	};
}

#endif /* !COCONUT_FOUNDATION_EMPTY_HPP */

/* EOF */