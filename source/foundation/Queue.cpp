//
// Queue.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
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

Queue::Queue(Queue && que) :
	Object(QueueClass),
	m_impl(std::move(que.m_impl))
{ /* NOP */ }

Queue::~Queue()
{ /* NOP */ }

#pragma mark -

QueuePtr Queue::with()
{ return ptr_create<Queue>(); }

QueuePtr Queue::with(const Queue & que)
{ return ptr_create<Queue>(que); }

QueuePtr Queue::with(Queue && que)
{ return ptr_create<Queue>(std::move(que)); }

#pragma mark -

kind_ptr Queue::copy() const
{ return ptr_create<Queue>(*this); }

#pragma mark -

std::size_t Queue::size() const
{ return m_impl.size(); }

#pragma mark -

kind_ptr Queue::dequeue()
{
	kind_ptr head;
	if (m_impl.size()) {
		head = m_impl.front();
		m_impl.pop();
	}
	return head;
}

void Queue::enqueue(kind_ptr ptr)
{ if (ptr) { m_impl.push(ptr); } }

#pragma mark -

void Queue::clear()
{
	impl_type none;
	std::swap(m_impl, none);
}

/* EOF */