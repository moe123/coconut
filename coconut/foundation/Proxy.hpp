//
// Proxy.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_PROXY_HPP
#define COCONUT_FOUNDATION_PROXY_HPP

namespace coconut
{
	COCONUT_ABSTRACT class COCONUT_EXPORT Proxy : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Proxy, Object.Proxy)
		
	public:
		Proxy();
		Proxy(const Proxy & proxy);
		Proxy & operator = (const Proxy & proxy) = default;
		virtual ~Proxy();
	};
}

#endif /* !COCONUT_FOUNDATION_PROXY_HPP */

/* EOF */