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

void Queue::enqueue(const Owning<Any> & obj)
{ if (obj) { m_impl.push(obj); } }

const Owning<Any> Queue::dequeue()
{
	Owning<Any> head;
	if (m_impl.size()) {
		head = m_impl.front();
		m_impl.pop();
	}
	return head;
}

#pragma mark -

const Owning<Any> Queue::peek() const
{
	Owning<Any> first;
	if (m_impl.size()) {
		first = m_impl.front();
	}
	return first;
}

#pragma mark -

void Queue::clear()
{
	impl_trait none;
	std::swap(m_impl, none);
}

/* EOF */