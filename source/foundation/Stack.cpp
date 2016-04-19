//
// Stack.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
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

Stack::Stack(Stack && stk) noexcept :
	Object(StackClass),
	m_impl(std::move(stk.m_impl))
{ /* NOP */ }

Stack::~Stack()
{ /* NOP */ }

#pragma mark -

Owning<Any> Stack::copy() const
{ return ptr_create<Stack>(*this); }

#pragma mark -

std::size_t Stack::size() const
{ return m_impl.size(); }

#pragma mark -

void Stack::push(const Owning<Any> & obj)
{ if (obj) { m_impl.push(obj); } }

#pragma mark -

const Owning<Any> Stack::pop()
{
	Owning<Any> head;
	if (m_impl.size()) {
		head = m_impl.top();
		m_impl.pop();
	}
	return head;
}

#pragma mark -

const Owning<Any> Stack::peek() const
{
	Owning<Any> last;
	if (m_impl.size()) {
		last = m_impl.top();
	}
	return last;
}

#pragma mark -

void Stack::clear()
{
	impl_trait none;
	std::swap(m_impl, none);
}

/* EOF */