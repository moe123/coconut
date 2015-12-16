//
// Empty.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_EMPTY_HPP
#define COCONUT_FOUNDATION_EMPTY_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT Empty COCONUT_FINAL : public Object
	{
	COCONUT_KDCL(coconut.Empty, Object.Empty)
		
	public:
		Empty();
		Empty(const Empty & emp);
		virtual ~Empty();
		
		COCONUT_KTOR EmptyPtr with();
		
		virtual kind_ptr copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const_kind_ref ref) const
		COCONUT_FINAL_OVERRIDE;
	};
}

#endif /* !COCONUT_FOUNDATION_EMPTY_HPP */

/* EOF */