//
// spinlock.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/defines.hpp>

#ifndef COCONUT_RUNTIME_SPINLOCK_HPP
#define COCONUT_RUNTIME_SPINLOCK_HPP

namespace coconut
{
	namespace runtime
	{
		COCONUT_PRIVATE class COCONUT_VISIBLE spinlock COCONUT_FINAL
		{
		COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.spinlock, spinlock)
		
		public:
			spinlock();
			spinlock(spinlock &) = default;
			virtual ~spinlock();
			
		public:
			void lock();
			bool try_lock();
			void unlock();
 
		private:
			std::int32_t m_cycle;
			std::int32_t m_loop;
			std::atomic_flag m_lock;
			std::atomic<bool> m_out;
		};
	}
}

#endif /* !COCONUT_RUNTIME_SPINLOCK_HPP */

/* EOF */