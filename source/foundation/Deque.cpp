//
// Deque.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Deque.hpp>
#include <coconut/foundation/Range.hpp>

using namespace coconut;

Deque::Deque() :
	Object(DequeClass),
	m_impl()
{ /* NOP */ }

Deque::Deque(const Deque & deq) :
	Object(DequeClass),
	m_impl(deq.m_impl)
{ /* NOP */ }

Deque::Deque(Deque && deq) noexcept :
	Object(DequeClass),
	m_impl(std::move(deq.m_impl))
{ /* NOP */ }

Deque::~Deque()
{ /* NOP */ }

#pragma mark -

Owning<Any> Deque::copy() const
{ return ptr_create<Deque>(*this); }

#pragma mark -

std::size_t Deque::size() const
{ return m_impl.size(); }

#pragma mark -

const Owning<Any> Deque::first() const
{ return m_impl.front(); }

const Owning<Any> Deque::last() const
{ return m_impl.back(); }

#pragma mark -

void Deque::addFirst(const Owning<Any> & obj)
{ if (obj) { m_impl.push_front(obj); } }

void Deque::addLast(const Owning<Any> & obj)
{ if (obj) { m_impl.push_back(obj); } }

#pragma mark -

void Deque::insert(const Owning<Any> & obj, std::size_t at_idx)
{ if (obj) { m_impl.insert(begin() + static_cast<difference_type>(at_idx), obj); } }

#pragma mark -

void Deque::remove(std::size_t index)
{ m_impl.erase(begin() + static_cast<difference_type>(index)); }

void Deque::remove(const Range & in_rg)
{
	std::size_t sz = size();
	if (sz) {
		std::size_t loc, len, max;
		Range src(0, sz);
		Range dest = src.intersectionRange(in_rg);
		
		loc = dest.location();
		len = dest.length();
		max = dest.maxRange();
		
		if (loc && len) {
			m_impl.erase(
				begin() + static_cast<difference_type>(loc),
				begin() + static_cast<difference_type>(max)
			);
		}
	}
}

#pragma mark -

void Deque::removeFirst()
{ m_impl.pop_front(); }

void Deque::removeLast()
{ m_impl.pop_back(); }

void Deque::removeAll()
{ m_impl.clear(); }

#pragma mark -

Deque::iterator Deque::begin() { return m_impl.begin(); }
Deque::iterator Deque::end() { return m_impl.end(); }

Deque::const_iterator Deque::begin() const { return m_impl.begin(); }
Deque::const_iterator Deque::end() const { return m_impl.end(); }

Deque::const_iterator Deque::cbegin() const { return m_impl.cbegin(); }
Deque::const_iterator Deque::cend() const { return m_impl.cend(); }

Deque::reverse_iterator Deque::rbegin() { return m_impl.rbegin(); }
Deque::reverse_iterator Deque::rend() { return m_impl.rend(); }

Deque::const_reverse_iterator Deque::rbegin() const { return m_impl.rbegin(); }
Deque::const_reverse_iterator Deque::rend() const { return m_impl.rend(); }

Deque::const_reverse_iterator Deque::crbegin() const { return m_impl.crbegin(); }
Deque::const_reverse_iterator Deque::crend() const { return m_impl.crend(); }

/* EOF */