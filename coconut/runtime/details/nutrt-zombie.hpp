//
// nutrt-zombie.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-nucleus.hpp>

#ifndef COCONUT_RUNTIME_ZOMBIE_HPP
#define COCONUT_RUNTIME_ZOMBIE_HPP

namespace coconut {
	namespace runtime {

COCONUT_PRIVATE class COCONUT_VISIBLE zombie : public nucleus
{
COCONUT_CLASSDECLARE(coconut.runtime.zombie, nucleus.zombie)

public:
	zombie();
	zombie(const zombie & undead) = delete;
	zombie(ClassKind hunter, bool ismutable = false);
	virtual ~zombie();
};

}} /* EONS */

#endif /* !COCONUT_RUNTIME_ZOMBIE_HPP */

/* EOF */