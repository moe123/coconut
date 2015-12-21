//
// Queue.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_QUEUE_HPP
#define COCONUT_FOUNDATION_QUEUE_HPP

namespace coconut
{
	COCONUT_ABSTRACT class COCONUT_EXPORT Queue : public Object
	{
	COCONUT_KDCL(coconut.Queue, Object.Queue)
		
	public:
		Queue();
		Queue(const Queue & que);
		Queue(Queue && que);
		virtual ~Queue();
	
		COCONUT_KTOR QueuePtr with();
		COCONUT_KTOR QueuePtr with(const Queue & que);
		COCONUT_KTOR QueuePtr with(Queue && que);
		
	public:
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
	
	public:
		Owning<Any> dequeue();
		void enqueue(Owning<Any> ptr);
		
		void clear();
		
	protected:
		typedef std::queue<Owning<Any>> impl_type;
		
	private:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_QUEUE_HPP */

/* EOF */