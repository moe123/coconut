//
// spinlock.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/spinlock.hpp>

using namespace coconut::runtime;

spinlock::spinlock() :
	m_cycle(0),
	m_loop(0),
	m_lock(ATOMIC_FLAG_INIT),
	m_out(false)
{ /* NOP */ }

spinlock::~spinlock()
{
	m_out = true;
	m_cycle = 0;
	m_loop = 0;
}

void spinlock::lock()
{
	if (m_out.load()) { return; }
	m_cycle = 8;
	while (--m_cycle) {
		m_loop = 300;
		while (--m_loop) {
			if (!m_lock.test_and_set(std::memory_order_acquire)) {
				//std::cerr << "spinlock m_loop: " << m_loop << " spinlock m_cycle: " << m_cycle << std::endl;
				return;
			}
		}
		std::this_thread::yield();
	}
}

bool spinlock::try_lock() {
	if (m_out.load()) { return false; }
	return !m_lock.test_and_set(std::memory_order_acquire);
}

void spinlock::unlock()
{
	if (m_out.load()) { return; }
	m_lock.clear(std::memory_order_release);
}

/* EOF */