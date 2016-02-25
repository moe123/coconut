//
// Queue.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_QUEUE_HPP
#define COCONUT_FOUNDATION_QUEUE_HPP

namespace coconut
{
	COCONUT_ABSTRACT class COCONUT_VISIBLE Queue : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Queue, Object.Queue)
		
	public:
		Queue();
		Queue(const Queue & que);
		Queue & operator = (const Queue & que) = default;
		Queue(Queue && que) noexcept;
		virtual ~Queue();

	public:
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
	
	public:
		Owning<Any> dequeue();
		void enqueue(const Owning<Any> & ptr);
		
		void clear();
		
	protected:
		typedef std::queue< Owning<Any> > impl_trait;
		
	private:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_QUEUE_HPP */

/* EOF */