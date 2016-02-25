//
// Queue.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Queue.hpp>

using namespace coconut;

Queue::Queue() :
	Object(QueueClass),
	m_impl()
{ /* NOP */ }

Queue::Queue(const Queue & que) :
	Object(QueueClass),
	m_impl(que.m_impl)
{ /* NOP */ }

Queue::Queue(Queue && que) noexcept :
	Object(QueueClass),
	m_impl(std::move(que.m_impl))
{ /* NOP */ }

Queue::~Queue()
{ /* NOP */ }

#pragma mark -

Owning<Any> Queue::copy() const
{ return ptr_create<Queue>(*this); }

#pragma mark -

std::size_t Queue::size() const
{ return m_impl.size(); }

#pragma mark -

Owning<Any> Queue::dequeue()
{
	Owning<Any> head;
	if (m_impl.size()) {
		head = m_impl.front();
		m_impl.pop();
	}
	return head;
}

void Queue::enqueue(const Owning<Any> & ptr)
{ if (ptr) { m_impl.push(ptr); } }

#pragma mark -

void Queue::clear()
{
	impl_trait none;
	std::swap(m_impl, none);
}

/* EOF */