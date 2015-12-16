//
// Set.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_SET_HPP
#define COCONUT_FOUNDATION_SET_HPP

namespace coconut
{	
	COCONUT_PUBLIC class COCONUT_EXPORT Set : public Object
	{
	COCONUT_KDCL(coconut.Set, Object.Set)
		
	public:
		Set();
		Set(const Set & set);
		Set & operator = (const Set & set) = default;
		Set(const Set & set, CopyOption option);
		
		Set(Set && set);

		Set(const std::initializer_list<kind_ptr> & args);
		Set(const std::initializer_list<kind_raw_ptr> & args);
		
		template <typename IterT>
		Set(IterT && beg, IterT && end) :
			Set(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone)
		{ /* NOP */ }
		
		template <typename IterT>
		Set(IterT && beg, IterT && end, CopyOption option) :
			Object(SetClass),
			m_impl([] (const_kind_ptr & a, const_kind_ptr & b) -> bool
			{ return (a->compare(*b) != OrderedSame); })
		{
			IterT it = beg;
			while (it != end) {
				if ((*it)) {
					if (option != CopyNone) {
						kind_ptr copy = Object::copyObject((*it), option);
						if (copy) { m_impl.insert(copy); }
					} else {
						m_impl.insert((*it));
					}
				}
				++it;
			}
		}
		
		virtual ~Set();

		COCONUT_KTOR SetPtr with(const Set & set);
		COCONUT_KTOR SetPtr with(const Set & set, CopyOption option);
		COCONUT_KTOR SetPtr with(Set && set);
		COCONUT_KTOR SetPtr with(const std::initializer_list<kind_ptr> & args);
		COCONUT_KTOR SetPtr with(const std::initializer_list<kind_raw_ptr> & args);
		
		template <typename IterT>
		COCONUT_KTOR SetPtr with(IterT && beg, IterT && end)
		{ return ptr_create<Set>(std::forward<IterT>(beg), std::forward<IterT>(end)); }
		
		template <typename IterT>
		COCONUT_KTOR SetPtr with(IterT && beg, IterT && end, CopyOption option)
		{ return ptr_create<Set>(std::forward<IterT>(beg), std::forward<IterT>(end), option); }
		
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
		
		virtual kind_ptr valueForKey(const std::string & utf8_key) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual kind_ptr valueForKeyPath(const std::string & utf8_keypath) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
		
		const Array makeObjectsPerformSelectorKey(const std::string & utf8_selkey, kind_ptr arg = {}) const;
		
		void enumerateObjectsUsingFunction(const std::function<void(const_kind_ptr & obj, bool & stop)> & func) const;
		void enumerateObjectsUsingFunction(const std::function<void(const_kind_ptr & obj, bool & stop)> & func, EnumerationOptions options) const;
		
		bool containsObject(const_kind_ref obj) const;
		bool containsObject(const_kind_ptr & obj) const;
		
		bool intersectsSet(const Set & set) const;
		bool isSubsetOfSet(const Set & set) const;
		
		kind_ptr member(const_kind_ref obj) const;
		kind_ptr member(const_kind_ptr & obj) const;
		
		kind_ptr anyObject() const;
		kind_ptr firstObject() const;
		kind_ptr lastObject() const;
		const Array allObjects(CopyOption option = CopyNone) const;
		
		const Set objectsPassingTest(const std::function<bool(const_kind_ptr & obj, bool & stop)> & func) const;
		const Set objectsPassingTest(const std::function<bool(const_kind_ptr & obj, bool & stop)> & func, EnumerationOptions options) const;
		
		bool everyObjectPassingTest(const std::function<bool(const_kind_ptr & obj, bool & stop)> & func) const;
		bool someObjectPassingTest(const std::function<bool(const_kind_ptr & obj, bool & stop)> & func) const;
		
		const Set filteredSetUsingFunction(const std::function<bool(const_kind_ptr & obj, bool & stop)> & func, CopyOption option = CopyNone) const;
		const Set filteredSetUsingFunction(const std::function<bool(const_kind_ptr & obj, bool & stop)> & func, CopyOption option, EnumerationOptions options) const;
		
		const Set setByAddingObject(kind_ptr ptr, CopyOption option = CopyNone) const;
		const Set setByAddingObjectsFromSet(const Set & set, CopyOption option = CopyNone) const;
		const Set setByAddingObjectsFromOrderedSet(const OrderedSet & set, CopyOption option = CopyNone) const;
		const Set setByAddingObjectsFromArray(const Array & arr, CopyOption option = CopyNone) const;
		
		template <typename IterT>
		const Set setByAddingObjects(IterT && beg, IterT && end) const
		{ return setByAddingObjectsFromSet(Set(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone)); }
		
		template <typename IterT>
		const Set setByAddingObjects(IterT && beg, IterT && end, CopyOption option) const
		{ return setByAddingObjectsFromSet(Set(std::forward<IterT>(beg), std::forward<IterT>(end)), option); }
	
	protected:
		typedef std::set<kind_ptr, std::function<bool(const_kind_ptr & a, const_kind_ptr & b)> > impl_type;
		
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
		friend class Dictionary;
		
	protected:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_SET_HPP */

/* EOF */