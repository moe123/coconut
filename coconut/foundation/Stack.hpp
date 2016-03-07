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
	COCONUT_ABSTRACT class COCONUT_VISIBLE Stack : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Stack, Object.Stack)
		
	public:
		Stack();
		Stack(const Stack & stk);
		Stack & operator = (const Stack & stk) = default;
		Stack(Stack && stk) noexcept;
		virtual ~Stack();
		
	public:
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
	
	public:
		void push(const Owning<Any> & ptr);
		const Owning<Any> pop();
		const Owning<Any> peek() const;
		
		void clear();
		
	protected:
		typedef std::stack< Owning<Any> > impl_trait;
		
	private:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_STACK_HPP */

/* EOF */