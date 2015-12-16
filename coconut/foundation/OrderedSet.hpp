//
// OrderedSet.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_ORDEREDSET_HPP
#define COCONUT_FOUNDATION_ORDEREDSET_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT OrderedSet : public Object
	{
	COCONUT_KDCL(coconut.OrderedSet, Object.OrderedSet)
		
	public:
		OrderedSet();
		OrderedSet(const OrderedSet & set);
		OrderedSet & operator = (const OrderedSet & set) = default;
		OrderedSet(const OrderedSet & set, CopyOption option);
		
		OrderedSet(OrderedSet && set);
		
		OrderedSet(const std::initializer_list<kind_ptr> & args);
		OrderedSet(const std::initializer_list<kind_raw_ptr> & args);
		
		template <typename IterT>
		OrderedSet(IterT && beg, IterT && end) :
			OrderedSet(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone)
		{ /* NOP */ }
		
		template <typename IterT>
		OrderedSet(IterT && beg, IterT && end, CopyOption option) :
			Object(OrderedSetClass),
			m_impl()
		{
			IterT it = beg;
			while (it != end) {
				if ((*it) && doesNotContain(*(*it))) {
					if (option != CopyNone) {
						kind_ptr copy = Object::copyObject((*it), option);
						if (copy) { m_impl.push_back(copy); }
					} else {
						m_impl.push_back((*it));
					}
				}
				++it;
			}
		}
		
		virtual ~OrderedSet();

		COCONUT_KTOR OrderedSetPtr with(const OrderedSet & set);
		COCONUT_KTOR OrderedSetPtr with(const OrderedSet & set, CopyOption option);
		COCONUT_KTOR OrderedSetPtr with(OrderedSet && set);
		COCONUT_KTOR OrderedSetPtr with(const std::initializer_list<kind_ptr> & args);
		COCONUT_KTOR OrderedSetPtr with(const std::initializer_list<kind_raw_ptr> & args);
		
		template <typename IterT>
		COCONUT_KTOR OrderedSetPtr with(IterT && beg, IterT && end)
		{ return ptr_create<OrderedSet>(std::forward<IterT>(beg), std::forward<IterT>(end)); }
		
		template <typename IterT>
		COCONUT_KTOR OrderedSetPtr with(IterT && beg, IterT && end, CopyOption option)
		{ return ptr_create<OrderedSet>(std::forward<IterT>(beg), std::forward<IterT>(end), option); }
		
		COCONUT_KTOR OrderedSetPtr with(const Path & path);
		COCONUT_KTOR OrderedSetPtr with(const URL & url);
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual kind_ptr copy() const
		COCONUT_FINAL_OVERRIDE;
		
		// virtual kind_ptr mutableCopy() const
		// COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const_kind_ref ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual bool doesContain(const_kind_ref ref) const
		COCONUT_FINAL_OVERRIDE;

		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual kind_ptr valueForKey(const std::string & utf8_key) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual kind_ptr valueForKeyPath(const std::string & utf8_keypath) const
		COCONUT_FINAL_OVERRIDE;
		
		void enumerateObjectsUsingFunction(const std::function<void(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const;
		void enumerateObjectsUsingFunction(const std::function<void(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		bool containsObject(const_kind_ref obj) const;
		bool containsObject(const_kind_ptr & obj) const;
		
		bool intersectsOrderedSet(const OrderedSet & set) const;
		bool isSubsetOfOrderedSet(const OrderedSet & set) const;
		
		bool intersectsSet(const Set & set) const;
		bool isSubsetOfSet(const Set & set) const;
		
		kind_ptr firstObject() const;
		kind_ptr lastObject() const;
		kind_ptr objectAtIndex(std::size_t index) const;
		
		std::size_t indexOfObject(const_kind_ref obj) const;
		std::size_t indexOfObject(const_kind_ref obj, Range in_rg) const;
		
		std::size_t indexOfObject(const_kind_ptr & obj) const;
		std::size_t indexOfObject(const_kind_ptr & obj, Range in_rg) const;
		
		std::size_t indexOfObjectIdenticalTo(const_kind_ref obj) const;
		std::size_t indexOfObjectIdenticalTo(const_kind_ptr & obj, Range in_rg) const;
		
		std::size_t indexOfObjectIdenticalTo(const_kind_ptr & obj) const;
		std::size_t indexOfObjectIdenticalTo(const_kind_ref obj, Range in_rg) const;

		std::size_t indexOfObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const;
		std::size_t indexOfObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		bool everyObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const;
		bool someObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const;
		
		const OrderedSet reversedOrderedSet(CopyOption option = CopyNone) const;
		
		const OrderedSet filteredOrderedSetUsingFunction(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, CopyOption option = CopyNone) const;
		const OrderedSet filteredOrderedSetUsingFunction(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, CopyOption option, EnumerationOptions options) const;
		
	public:
		const_kind_ptr operator [] (std::size_t index) const;
		
	protected:
		typedef std::vector<kind_ptr> impl_type;
		
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