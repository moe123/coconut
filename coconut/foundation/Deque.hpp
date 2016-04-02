//
// Deque.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_DATE_HPP
#define COCONUT_FOUNDATION_DATE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Deque : public Object
	{
		COCONUT_CLASSDECLARE(coconut.Deque, Object.Deque)
		
	public:
		Deque();
		Deque(const Deque & deq);
		Deque & operator = (const Deque & deq) = default;
		Deque(Deque && deq) noexcept;
		virtual ~Deque();
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
		
		const Owning<Any> first() const;
		const Owning<Any> last() const;
		
		void addFirst(const Owning<Any> & obj);
		void addLast(const Owning<Any> & obj);
		
		void insert(const Owning<Any> & obj, std::size_t at_idx);
		
		void remove(std::size_t index);
		void remove(const Range & in_rg);
		
		void removeFirst();
		void removeLast();
		void removeAll();
		
	public:
		typedef std::deque< Owning<Any> > impl_trait;

	public:
		typedef impl_trait::iterator iterator;
		typedef impl_trait::const_iterator const_iterator;
		
		typedef impl_trait::reverse_iterator reverse_iterator;
		typedef impl_trait::const_reverse_iterator const_reverse_iterator;
		
		typedef impl_trait::value_type value_type;
		typedef impl_trait::size_type size_type;
		typedef impl_trait::difference_type difference_type;
		
	public:
		iterator begin();
		iterator end();
		
		const_iterator begin() const;
		const_iterator end() const;
		
		const_iterator cbegin() const;
		const_iterator cend() const;
		
		reverse_iterator rbegin();
		reverse_iterator rend();
		
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;
		
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;
		
	protected:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_DATE_HPP */

/* EOF */