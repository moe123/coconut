//
// Set.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_SET_HPP
#define COCONUT_FOUNDATION_SET_HPP

namespace coconut
{	
	COCONUT_PUBLIC class COCONUT_VISIBLE Set : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Set, Object.Set)
		
	public:
		Set();
		Set(const Set & set);
		Set & operator = (const Set & set) = default;
		Set(const Set & set, CopyOption option);
		Set(Set && set) noexcept;
		Set(const std::initializer_list< Owning<Any> > & args);
		Set(const std::initializer_list<Any *> & args);
		
		template <typename InputIterT>
		Set(InputIterT && first, InputIterT && last) :
			Set(std::forward<InputIterT>(first), std::forward<InputIterT>(last), CopyNone)
		{ /* NOP */ }
		
		template <typename InputIterT>
		Set(InputIterT && first, InputIterT && last, CopyOption option) :
			Object(SetClass),
			m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
			{ return (a->compare(*b) != OrderedSame); })
		{
			for (; first != last; ++first) {
				if ((*first)) {
					if (option != CopyNone) {
						Owning<Any> copy = Object::copyObject((*first), option);
						if (copy) { m_impl.insert(copy); }
					} else {
						m_impl.insert((*first));
					}
				}
			}
		}
		
		virtual ~Set();

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
		
		virtual Owning<Any> valueForKey(const std::string & utf8_key) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> valueForKeyPath(const std::string & utf8_keypath) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
		
		const Array makeObjectsPerformSelectorKey(const std::string & utf8_selkey, Owning<Any> arg = {}) const;

		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj)> & func) const;
		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj)> & func, EnumerationOptions options) const;
		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, bool & stop)> & func) const;
		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, bool & stop)> & func, EnumerationOptions options) const;
		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		bool containsObject(const Any & obj) const;
		bool containsObject(const Owning<Any> & obj) const;
		
		bool intersectsSet(const Set & set) const;
		bool isSubsetOfSet(const Set & set) const;
		bool isSupersetOfSet(const Set & set) const;
		
		const Owning<Any> member(const Any & obj) const;
		const Owning<Any> member(const Owning<Any> & obj) const;
		
		const Owning<Any> anyObject() const;
		const Owning<Any> firstObject() const;
		const Owning<Any> lastObject() const;
		const Array allObjects(CopyOption option = CopyNone) const;
		
		const Set objectsPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func) const;
		const Set objectsPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func, EnumerationOptions options) const;
		
		bool everyObjectPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func) const;
		bool noneObjectPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func) const;
		bool someObjectPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func) const;
		
		const Set filteredSetUsingFunction(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func, CopyOption option = CopyNone) const;
		const Set filteredSetUsingFunction(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func, CopyOption option, EnumerationOptions options) const;
		
		const Set setByAddingObject(Owning<Any> ptr, CopyOption option = CopyNone) const;
		const Set setByAddingObjectsFromSet(const Set & set, CopyOption option = CopyNone) const;
		const Set setByAddingObjectsFromOrderedSet(const OrderedSet & set, CopyOption option = CopyNone) const;
		const Set setByAddingObjectsFromArray(const Array & arr, CopyOption option = CopyNone) const;
		
		template <typename InputIterT>
		const Set setByAddingObjects(InputIterT && first, InputIterT && last) const
		{ return setByAddingObjectsFromSet(Set(std::forward<InputIterT>(first), std::forward<InputIterT>(last), CopyNone)); }
		
		template <typename InputIterT>
		const Set setByAddingObjects(InputIterT && first, InputIterT && last, CopyOption option) const
		{ return setByAddingObjectsFromSet(Set(std::forward<InputIterT>(first), std::forward<InputIterT>(last)), option); }
	
	protected:
		typedef std::set< Owning<Any>, bool (*) (const Owning<Any> & a, const Owning<Any> & b)> impl_trait;
		
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
	
	protected:
		friend class Object;
		friend class Dictionary;
		
	protected:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_SET_HPP */

/* EOF */