//
// Deque.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_DEQUE_HPP
#define COCONUT_FOUNDATION_DEQUE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Deque COCONUT_FINAL : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Deque, Object.Deque)
		
	public:
		Deque();
		Deque(const Deque & deq);
		Deque & operator = (const Deque & deq) = default;
		Deque(Deque && deq) noexcept;
		Deque(const std::initializer_list< Owning<Any> > & args);
		Deque(const std::initializer_list<Any *> & args);
		
		template <typename InputIterT>
		Deque(InputIterT && first, InputIterT && last) :
			Deque(std::forward<InputIterT>(first), std::forward<InputIterT>(last), CopyNone)
		{ /* NOP */ }
		
		template <typename InputIterT>
		Deque(InputIterT && first, InputIterT && last, CopyOption option) :
			Object(DequeClass),
			m_impl()
		{
			for (; first != last; ++first) {
				if ((*first)) {
					if (option != CopyNone) {
						Owning<Any> copy = Object::copyObject((*first), option);
						if (copy) { m_impl.push_back(copy); }
					} else {
						m_impl.push_back((*first));
					}
				}
			}
		}
		
		virtual ~Deque();
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
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
		
	private:
		typedef std::deque< Owning<Any> > impl_trait;

	public:
		typedef impl_trait::iterator iterator;
		typedef impl_trait::const_iterator const_iterator;
		
		typedef impl_trait::reverse_iterator reverse_iterator;
		typedef impl_trait::const_reverse_iterator const_reverse_iterator;
		
		typedef impl_trait::value_type value_type;
		typedef impl_trait::size_type size_type;
		typedef impl_trait::difference_type difference_type;

		typedef impl_trait::reference reference;
		typedef impl_trait::const_reference const_reference;
		typedef impl_trait::pointer pointer;
		typedef impl_trait::const_pointer const_pointer;
		
		typedef impl_trait::allocator_type allocator_type;
		
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
		
	private:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_DEQUE_HPP */

/* EOF */