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
	
		COCONUT_KTOR StackPtr with();
		COCONUT_KTOR StackPtr with(const Stack & stk);
		COCONUT_KTOR StackPtr with(Stack && stk);
		
	public:
		virtual kind_ptr copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
	
	public:
		kind_ptr pop();
		void push(kind_ptr ptr);
		
		void clear();
		
	protected:
		typedef std::stack<kind_ptr> impl_type;
		
	private:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_STACK_HPP */

/* EOF */