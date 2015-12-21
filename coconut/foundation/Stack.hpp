//
// Stack.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_STACK_HPP
#define COCONUT_FOUNDATION_STACK_HPP

namespace coconut
{
	COCONUT_ABSTRACT class COCONUT_EXPORT Stack : public Object
	{
	COCONUT_KDCL(coconut.Stack, Object.Stack)
		
	public:
		Stack();
		Stack(const Stack & stk);
		Stack(Stack && stk);
		virtual ~Stack();
	
		COCONUT_KTOR Owning<Stack> with();
		COCONUT_KTOR Owning<Stack> with(const Stack & stk);
		COCONUT_KTOR Owning<Stack> with(Stack && stk);
		
	public:
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
	
	public:
		Owning<Any> pop();
		void push(Owning<Any> ptr);
		
		void clear();
		
	protected:
		typedef std::stack<Owning<Any>> impl_type;
		
	private:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_STACK_HPP */

/* EOF */