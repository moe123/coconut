//
// Array.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_ARRAY_HPP
#define COCONUT_FOUNDATION_ARRAY_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT Array : public Object
	{
	COCONUT_KDCL(coconut.Array, Object.Array)
		
	public:
		Array();
		Array(const Array & arr);
		Array & operator = (const Array & arr) = default;
		Array(const Array & arr, CopyOption option);
		
		Array(Array && arr);

		Array(const std::initializer_list<kind_ptr> & args);
		Array(const std::initializer_list<kind_raw_ptr> & args);
		
		template <typename IterT>
		Array(IterT && beg, IterT && end) :
			Array(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone)
		{ /* NOP */ }
		
		template <typename IterT>
		Array(IterT && beg, IterT && end, CopyOption option) :
			Object(ArrayClass),
			m_impl()
		{
			IterT it = beg;
			while (it != end) {
				if ((*it)) {
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
		
		Array(const Path & path);
		Array(const URL & url);
		virtual ~Array();
		
		COCONUT_KTOR ArrayPtr with();
		COCONUT_KTOR ArrayPtr with(const Array & arr);
		COCONUT_KTOR ArrayPtr with(const Array & arr, CopyOption option);
		
		COCONUT_KTOR ArrayPtr with(Array && arr);
		
		COCONUT_KTOR ArrayPtr with(const std::initializer_list<kind_ptr> & args);
		COCONUT_KTOR ArrayPtr with(const std::initializer_list<kind_raw_ptr> & args);
		
		template <typename IterT>
		COCONUT_KTOR ArrayPtr with(IterT && beg, IterT && end)
		{ return ptr_create<Array>(std::forward<IterT>(beg), std::forward<IterT>(end)); }
		
		template <typename IterT>
		COCONUT_KTOR ArrayPtr with(IterT && beg, IterT && end, CopyOption option)
		{ return ptr_create<Array>(std::forward<IterT>(beg), std::forward<IterT>(end), option); }
		
		COCONUT_KTOR ArrayPtr with(const Path & path);
		COCONUT_KTOR ArrayPtr with(const URL & url);
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual kind_ptr copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual kind_ptr mutableCopy() const
		COCONUT_FINAL_OVERRIDE;
		
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
		
		const Array makeObjectsPerformSelectorKey(const std::string & utf8_selkey, kind_ptr arg = {}) const;
		
		void enumerateObjectsUsingFunction(const std::function<void(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const;
		void enumerateObjectsUsingFunction(const std::function<void(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		bool containsObject(const_kind_ref obj) const;
		bool containsObject(const_kind_ptr & obj) const;
		
		bool containsObject(bool & obj) const;
		
		kind_ptr firstObject() const;
		kind_ptr lastObject() const;
		kind_ptr objectAtIndex(std::size_t index) const;
		
		std::size_t indexOfObject(const_kind_ref obj) const;
		std::size_t indexOfObject(const_kind_ref obj, Range in_rg) const;
		
		std::size_t indexOfObject(const_kind_ptr & obj) const;
		std::size_t indexOfObject(const_kind_ptr & obj, Range in_rg) const;
		
		std::size_t indexOfObjectIdenticalTo(const_kind_ref obj) const;
		std::size_t indexOfObjectIdenticalTo(const_kind_ref obj, Range in_rg) const;
		
		std::size_t indexOfObjectIdenticalTo(const_kind_ptr & obj) const;
		std::size_t indexOfObjectIdenticalTo(const_kind_ptr & obj, Range in_rg) const;

		std::size_t indexOfObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const;
		std::size_t indexOfObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		bool everyObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const;
		bool someObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const;
		
		kind_ptr firstObjectCommonWithArray(const Array & arr) const;
	
		const Array reversedArray(CopyOption option = CopyNone) const;
		const Array uniquedArray(CopyOption option = CopyNone) const;
		const Array shuffledArray(CopyOption option = CopyNone) const;
		
		const Array filteredArrayUsingFunction(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, CopyOption option = CopyNone) const;
		const Array filteredArrayUsingFunction(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, CopyOption option, EnumerationOptions options) const;
		
		const Array sortedArrayUsingFunction(const std::function<bool(const_kind_ptr & a, const_kind_ptr & b)> & func, CopyOption option = CopyNone) const;
		const Array sortedArrayUsingFunction(const std::function<bool(const_kind_ptr & a, const_kind_ptr & b)> & func, CopyOption option, SortOptions options) const;
		
		const Array sortedArrayAscending(CopyOption option = CopyNone) const;
		const Array sortedArrayAscending(CopyOption option, SortOptions options) const;
		
		const Array sortedArrayDescending(CopyOption option = CopyNone) const;
		const Array sortedArrayDescending(CopyOption option, SortOptions options) const;
		
		const Array sortedArrayUsingSelectorKey(const std::string & utf8_selkey, CopyOption option = CopyNone) const;
		const Array sortedArrayUsingSelectorKey(const std::string & utf8_selkey, CopyOption option, bool descending) const;
		const Array sortedArrayUsingSelectorKey(const std::string & utf8_selkey, CopyOption option, bool descending, SortOptions options) const;
		
		const Array sortedArrayUsingDescriptor(const SortDescriptor & descriptor, CopyOption option = CopyNone) const;
		const Array sortedArrayUsingDescriptor(const SortDescriptor & descriptor, CopyOption option, SortOptions options) const;

		const Array sortedArrayUsingDescriptors(const Array & descriptors, CopyOption option = CopyNone) const;
		const Array sortedArrayUsingDescriptors(const Array & descriptors, CopyOption option, SortOptions options) const;
		
		const Array arrayByPushingObject(const_kind_ref obj) const;
		const Array arrayByPushingObject(const_kind_ref obj, CopyOption option) const;
		
		const Array arrayByPushingObject(kind_ptr obj) const;
		const Array arrayByPushingObject(kind_ptr obj, CopyOption option) const;
		
		const Array arrayByPushingObjectsFromArray(const Array & arr) const;
		const Array arrayByPushingObjectsFromArray(const Array & arr, CopyOption option) const;
		
		template <typename IterT>
		const Array arrayByPushingObjects(IterT && beg, IterT && end) const
		{ return arrayByPushingObjects(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone); }
		
		template <typename IterT>
		const Array arrayByPushingObjects(IterT && beg, IterT && end, CopyOption option) const
		{ return arrayByPushingObjectsFromArray(Array(std::forward<IterT>(beg), std::forward<IterT>(end)), option); }
		
		const Array arrayByAddingObject(const_kind_ref obj) const;
		const Array arrayByAddingObject(const_kind_ref obj, CopyOption option) const;
		
		const Array arrayByAddingObject(kind_ptr obj) const;
		const Array arrayByAddingObject(kind_ptr obj, CopyOption option) const;
		
		const Array arrayByAddingObjectsFromArray(const Array & arr) const;
		const Array arrayByAddingObjectsFromArray(const Array & arr, CopyOption option) const;
		
		template <typename IterT>
		const Array arrayByAddingObjects(IterT && beg, IterT && end) const
		{ return arrayByAddingObjects(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone); }
		
		template <typename IterT>
		const Array arrayByAddingObjects(IterT && beg, IterT && end, CopyOption option) const
		{ return arrayByAddingObjectsFromArray(Array(std::forward<IterT>(beg), std::forward<IterT>(end)), option); }
		
		const Array subarrayWithRange(const Range & rg, CopyOption option = CopyNone) const;
		const Array subarrayWithRange(std::size_t location, std::size_t length, CopyOption option = CopyNone) const;
		
		const String componentsJoinedByString(const String & separator);
		
		bool writeToFile(const Path & path, bool atomically = true) const;
		bool writeToURL(const URL & url, bool atomically = true) const;

	public:
		const_kind_ptr operator [] (std::size_t index) const;
		const Array operator [] (const Range & rg) const;
		
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
		friend class Dictionary;
		friend class MutableArray;
		friend class OrderedSet;
		friend class Set;
		
	protected:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_ARRAY_HPP */

/* EOF */