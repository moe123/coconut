//
// OrderedSet.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_ORDEREDSET_HPP
#define COCONUT_FOUNDATION_ORDEREDSET_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT OrderedSet : public Object
	{
	COCONUT_CLASSDECLARE(coconut.OrderedSet, Object.OrderedSet)
		
	public:
		OrderedSet();
		OrderedSet(const OrderedSet & set);
		OrderedSet & operator = (const OrderedSet & set) = default;
		OrderedSet(const OrderedSet & set, CopyOption option);
		OrderedSet(OrderedSet && set);
		OrderedSet(const std::initializer_list< Owning<Any> > & args);
		OrderedSet(const std::initializer_list<Any *> & args);
		
		template <typename IterT>
		OrderedSet(IterT && beg, IterT && end) :
			OrderedSet(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone)
		{ /* NOP */ }
		
		template <typename IterT>
		OrderedSet(IterT && beg, IterT && end, CopyOption option) :
			Object(OrderedSetClass),
			m_impl()
		{
			for (; beg != end; ++beg) {
				if ((*beg) && doesNotContain(*(*beg))) {
					if (option != CopyNone) {
						Owning<Any> copy = Object::copyObject((*beg), option);
						if (copy) { m_impl.push_back(copy); }
					} else {
						m_impl.push_back((*beg));
					}
				}
			}
		}
		
		virtual ~OrderedSet();
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		// virtual Owning<Any> mutableCopy() const
		// COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual bool doesContain(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;

		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> valueForKey(const std::string & utf8_key) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> valueForKeyPath(const std::string & utf8_keypath) const
		COCONUT_FINAL_OVERRIDE;
		
		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		void enumerateUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		bool containsObject(const Any & obj) const;
		bool containsObject(const Owning<Any> & obj) const;
		
		bool intersectsOrderedSet(const OrderedSet & set) const;
		bool isSubsetOfOrderedSet(const OrderedSet & set) const;
		
		bool intersectsSet(const Set & set) const;
		bool isSubsetOfSet(const Set & set) const;
		
		const Owning<Any> firstObject() const;
		const Owning<Any> lastObject() const;
		const Owning<Any> objectAtIndex(std::size_t index) const;
		
		std::size_t indexOfObject(const Any & obj) const;
		std::size_t indexOfObject(const Any & obj, Range in_rg) const;
		
		std::size_t indexOfObject(const Owning<Any> & obj) const;
		std::size_t indexOfObject(const Owning<Any> & obj, Range in_rg) const;
		
		std::size_t indexOfObjectIdenticalTo(const Any & obj) const;
		std::size_t indexOfObjectIdenticalTo(const Owning<Any> & obj) const;
		
		std::size_t indexOfObjectIdenticalTo(const Owning<Any> & obj, Range in_rg) const;
		std::size_t indexOfObjectIdenticalTo(const Any & obj, Range in_rg) const;

		std::size_t indexOfObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		std::size_t indexOfObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		bool everyObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		bool noneObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		bool someObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		
		const OrderedSet reversedOrderedSet(CopyOption option = CopyNone) const;
		
		const OrderedSet filteredOrderedSetUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, CopyOption option = CopyNone) const;
		const OrderedSet filteredOrderedSetUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, CopyOption option, EnumerationOptions options) const;
		
	public:
		const Owning<Any> operator [] (std::size_t index) const;
		
	protected:
		typedef std::vector< Owning<Any> > impl_type;
		
	public:
		typedef impl_type::iterator iterator;
		typedef impl_type::const_iterator const_iterator;
		
		typedef impl_type::reverse_iterator reverse_iterator;
		typedef impl_type::const_reverse_iterator const_reverse_iterator;
		
		typedef impl_type::value_type value_type;
		typedef impl_type::size_type size_type;
		typedef impl_type::difference_type difference_type;
		
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
		friend class Object;
		
	protected:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_ORDEREDSET_HPP */

/* EOF */