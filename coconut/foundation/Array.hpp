//
// Array.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>
#include <coconut/runtime/Serialization.hpp>

#ifndef COCONUT_FOUNDATION_ARRAY_HPP
#define COCONUT_FOUNDATION_ARRAY_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Array : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Array, Object.Array)
		
	public:
		Array();
		Array(const Array & arr);
		Array & operator = (const Array & arr) = default;
		Array(const Array & arr, CopyOption option);
		Array(Array && arr) noexcept;
		Array(const std::initializer_list< Owning<Any> > & args);
		Array(const std::initializer_list<Any *> & args);

		template <typename InputIterT>
		Array(InputIterT && first, InputIterT && last) :
			Array(std::forward<InputIterT>(first), std::forward<InputIterT>(last), CopyNone)
		{ /* NOP */ }
		
		template <typename InputIterT>
		Array(InputIterT && first, InputIterT && last, CopyOption option) :
			Object(ArrayClass),
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
		
		Array(const Path & path);
		Array(const URL & url);
		virtual ~Array();
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> mutableCopy() const
		COCONUT_FINAL_OVERRIDE;
		
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
		
		const Array makeObjectsPerformSelectorKey(const std::string & utf8_selkey, Owning<Any> arg = {}) const;
		
		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		void enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		bool containsObject(const Any & obj) const;
		bool containsObject(const Owning<Any> & obj) const;
		
		const Owning<Any> firstObject() const;
		const Owning<Any> lastObject() const;
		const Owning<Any> objectAtIndex(std::size_t index) const;
		
		const Array objectsInRange(const Range & rg, CopyOption option = CopyNone) const;
		const Array objectsInSlice(const Slice & slc, CopyOption option = CopyNone) const;
		
		std::size_t indexOfObject(const Any & obj) const;
		std::size_t indexOfObject(const Any & obj, const Range & in_rg) const;
		
		std::size_t indexOfObject(const Owning<Any> & obj) const;
		std::size_t indexOfObject(const Owning<Any> & obj, const Range & in_rg) const;
		
		std::size_t indexOfObjectIdenticalTo(const Any & obj) const;
		std::size_t indexOfObjectIdenticalTo(const Any & obj, const Range & in_rg) const;
		
		std::size_t indexOfObjectIdenticalTo(const Owning<Any> & obj) const;
		std::size_t indexOfObjectIdenticalTo(const Owning<Any> & obj, const Range & in_rg) const;
		
		std::size_t lastIndexOfObject(const Any & obj) const;
		std::size_t lastIndexOfObject(const Owning<Any> & obj) const;
		
		std::size_t lastIndexOfObjectIdenticalTo(const Any & obj) const;
		std::size_t lastIndexOfObjectIdenticalTo(const Owning<Any> & obj) const;
		
		const Owning<Any> firstObjectCommonWithArray(const Array & arr) const;
		const Owning<Any> lastObjectCommonWithArray(const Array & arr) const;
		
		std::size_t indexOfObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		std::size_t indexOfObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const;
		
		bool everyObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		bool noneObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
		bool someObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const;
	
		const Array reversedArray(CopyOption option = CopyNone) const;
		const Array uniquedArray(CopyOption option = CopyNone) const;
		const Array shuffledArray(CopyOption option = CopyNone) const;
		
		const Array filteredArrayUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, CopyOption option = CopyNone) const;
		const Array filteredArrayUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, CopyOption option, EnumerationOptions options) const;
		
		const Array sortedArrayUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, CopyOption option = CopyNone) const;
		const Array sortedArrayUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, CopyOption option, SortOptions options) const;
		
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
		
		const Array arrayByPushingObject(const Any & obj) const;
		const Array arrayByPushingObject(const Any & obj, CopyOption option) const;
		
		const Array arrayByPushingObject(Owning<Any> obj) const;
		const Array arrayByPushingObject(Owning<Any> obj, CopyOption option) const;
		
		const Array arrayByPushingObjectsFromArray(const Array & arr) const;
		const Array arrayByPushingObjectsFromArray(const Array & arr, CopyOption option) const;
		
		template <typename InputIterT>
		const Array arrayByPushingObjects(InputIterT && first, InputIterT && last) const
		{ return arrayByPushingObjects(std::forward<InputIterT>(first), std::forward<InputIterT>(last), CopyNone); }
		
		template <typename InputIterT>
		const Array arrayByPushingObjects(InputIterT && first, InputIterT && last, CopyOption option) const
		{ return arrayByPushingObjectsFromArray({std::forward<InputIterT>(first), std::forward<InputIterT>(last)}, option); }
		
		const Array arrayByAddingObject(const Any & obj) const;
		const Array arrayByAddingObject(const Any & obj, CopyOption option) const;
		
		const Array arrayByAddingObject(Owning<Any> obj) const;
		const Array arrayByAddingObject(Owning<Any> obj, CopyOption option) const;
		
		const Array arrayByAddingObjectsFromArray(const Array & arr) const;
		const Array arrayByAddingObjectsFromArray(const Array & arr, CopyOption option) const;
		
		template <typename InputIterT>
		const Array arrayByAddingObjects(InputIterT && first, InputIterT && last) const
		{ return arrayByAddingObjectsFromArray({std::forward<InputIterT>(first), std::forward<InputIterT>(last)}, CopyNone); }
		
		template <typename InputIterT>
		const Array arrayByAddingObjects(InputIterT && first, InputIterT && last, CopyOption option) const
		{ return arrayByAddingObjectsFromArray({std::forward<InputIterT>(first), std::forward<InputIterT>(last)}, option); }
		
		const Array arrayByDifferencingObjectsWithArray(const Array & arr) const;
		const Array arrayByDifferencingObjectsWithArray(const Array & arr, CopyOption option) const;
		
		template <typename InputIterT>
		const Array arrayByDifferencingObjects(InputIterT && first, InputIterT && last) const
		{ return arrayByDifferencingObjectsWithArray({std::forward<InputIterT>(first), std::forward<InputIterT>(last)}, CopyNone); }
		
		template <typename InputIterT>
		const Array arrayByDifferencingObjects(InputIterT && first, InputIterT && last, CopyOption option) const
		{ return arrayByDifferencingObjectsWithArray({std::forward<InputIterT>(first), std::forward<InputIterT>(last)}, option); }

		const Array arrayByIntersectingObjectsWithArray(const Array & arr) const;
		const Array arrayByIntersectingObjectsWithArray(const Array & arr, CopyOption option) const;

		template <typename InputIterT>
		const Array arrayByIntersectingObjects(InputIterT && first, InputIterT && last) const
		{ return arrayByIntersectingObjectsWithArray({std::forward<InputIterT>(first), std::forward<InputIterT>(last)}, CopyNone); }
		
		template <typename InputIterT>
		const Array arrayByIntersectingObjects(InputIterT && first, InputIterT && last, CopyOption option) const
		{ return arrayByIntersectingObjectsWithArray({std::forward<InputIterT>(first), std::forward<InputIterT>(last)}, option); }
		
		const Array subarrayWithRange(const Range & rg, CopyOption option = CopyNone) const;
		const Array subarrayWithSlice(const Slice & slc, CopyOption option = CopyNone) const;
	
		const String componentsJoinedByString(const String & separator);
		
		bool writeToFile(const Path & path, bool atomically = true) const;
		bool writeToURL(const URL & url, bool atomically = true) const;
		
	public:
		const Owning<Any> operator [] (std::size_t index) const;
		const Array operator [] (const Slice & slc) const;
		
		const Array operator + (const Any & obj) const;
		const Array operator + (const Owning<Any> & obj) const;
		
		const Array operator * (std::size_t accumulate) const;
		
		const Array operator << (const Any & obj) const;
		const Array operator << (const Owning<Any> & obj) const;
		
	protected:
		typedef std::vector< Owning<Any> > impl_trait;
		
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
		friend class MutableArray;
		friend class OrderedSet;
		friend class Set;
		
	protected:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_ARRAY_HPP */

/* EOF */