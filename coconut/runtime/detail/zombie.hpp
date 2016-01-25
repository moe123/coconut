//
// zombie.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/nucleus.hpp>

#ifndef COCONUT_RUNTIME_ZOMBIE_HPP
#define COCONUT_RUNTIME_ZOMBIE_HPP

namespace coconut
{
	namespace runtime
	{
		COCONUT_PRIVATE class COCONUT_EXPORT zombie : public nucleus
		{
		COCONUT_KDCL(coconut.runtime.zombie, nucleus.zombie)
		
		public:
			zombie();
			zombie(const zombie & undead) = delete;
			zombie(ClassKind hunter, bool ismutable = false);
			virtual ~zombie();
		};
	}
}

#endif /* !COCONUT_RUNTIME_ZOMBIE_HPP */

/* EOF */