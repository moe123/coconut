//
// Stack.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Stack.hpp>

using namespace coconut;

Stack::Stack() :
	Object(StackClass),
	m_impl()
{ /* NOP */ }

Stack::Stack(const Stack & stk) :
	Object(StackClass),
	m_impl(stk.m_impl)
{ /* NOP */ }

Stack::Stack(Stack && stk) :
	Object(StackClass),
	m_impl(std::move(stk.m_impl))
{ /* NOP */ }

Stack::~Stack()
{ /* NOP */ }

#pragma mark -

StackPtr Stack::with()
{ return ptr_create<Stack>(); }

StackPtr Stack::with(const Stack & stk)
{ return ptr_create<Stack>(stk); }

StackPtr Stack::with(Stack && stk)
{ return ptr_create<Stack>(std::move(stk)); }

#pragma mark -

Owning<Any> Stack::copy() const
{ return ptr_create<Stack>(*this); }

#pragma mark -

std::size_t Stack::size() const
{ return m_impl.size(); }

#pragma mark -

Owning<Any> Stack::pop()
{
	Owning<Any> head;
	if (m_impl.size()) {
		head = m_impl.top();
		m_impl.pop();
	}
	return head;
}

void Stack::push(Owning<Any> ptr)
{ if (ptr) { m_impl.push(ptr); } }

#pragma mark -

void Stack::clear()
{
	impl_type none;
	std::swap(m_impl, none);
}

/* EOF */