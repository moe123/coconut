//
// Stack.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_STACK_HPP
#define COCONUT_FOUNDATION_STACK_HPP

namespace coconut
{
	COCONUT_ABSTRACT class COCONUT_EXPORT Stack : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Stack, Object.Stack)
		
	public:
		Stack();
		Stack(const Stack & stk);
		Stack & operator = (const Stack & stk) = default;
		Stack(Stack && stk);
		virtual ~Stack();
		
	public:
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
	
	public:
		Owning<Any> pop();
		void push(const Owning<Any> & ptr);
		
		void clear();
		
	protected:
		typedef std::stack< Owning<Any> > impl_type;
		
	private:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_STACK_HPP */

/* EOF */