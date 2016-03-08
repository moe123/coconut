//
// None.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/None.hpp>

using namespace coconut;

None::None() :
	Object(NoneClass)
{ /* NOP */ }

None::None(const None & non) :
	Object(NoneClass)
{ COCONUT_UNUSED(non); }

None::~None()
{ /* NOP */ }

#pragma mark -

Owning<Any> None::copy() const
{ return ptr_create<None>(*this); }

#pragma mark -

ComparisonResult None::compare(const Any & ref) const
{
	if (isMemberOf(ref)) {
		return OrderedSame;
	}
	return OrderedDescending;
}

#pragma mark -

std::string None::stringValue() const
{ return u8"<none>"; }

/* EOF */