//
// Proxy.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Proxy.hpp>

using namespace coconut;

Proxy::Proxy() :
	Object(ProxyClass)
{ /* NOP */ }

Proxy::Proxy(const Proxy & proxy) :
	Object(ProxyClass)
{ conveyAttributesFrom(proxy); }

Proxy::~Proxy()
{ /* NOP */ }

/* EOF */