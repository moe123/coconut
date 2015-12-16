//
// zombie.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/zombie.hpp>

using namespace coconut::runtime;

zombie::zombie() :
	nucleus(classkind_anon, classkind_zombie)
{ /* NOP */ }

zombie::zombie(ClassKind hunter, bool ismutable) :
	nucleus(classkind_anon, classkind_zombie)
{ setClassKind(hunter, ismutable); }

zombie::~zombie()
{ /* NOP */ }

/* EOF */