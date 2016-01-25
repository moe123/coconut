//
// None.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_NONE_HPP
#define COCONUT_FOUNDATION_NONE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT None : public Object
	{
	COCONUT_KDCL(coconut.None, Object.None)
		
	public:
		None();
		None(const None & non);
		None & operator = (const None & non) = default;
		virtual ~None();
		
		COCONUT_KTOR Owning<None> with();
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
	};
}

#endif /* !COCONUT_FOUNDATION_NONE_HPP */

/* EOF */