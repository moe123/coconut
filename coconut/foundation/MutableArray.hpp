//
// MutableArray.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Array.hpp>

#ifndef COCONUT_FOUNDATION_MUTABLEARRAY_HPP
#define COCONUT_FOUNDATION_MUTABLEARRAY_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE MutableArray COCONUT_FINAL : public Array
	{
	COCONUT_CLASSDECLARE(coconut.MutableArray, Object.Array.MutableArray)
		
	public:
		MutableArray();
		MutableArray(const MutableArray & arr);
		MutableArray & operator = (const MutableArray & arr) = default;
		MutableArray(const MutableArray & arr, CopyOption option);
		MutableArray(MutableArray && arr) noexcept;
		MutableArray(const Array & arr, CopyOption option = CopyNone);
		MutableArray(Array && arr) noexcept;
		MutableArray(const std::initializer_list< Owning<Any> > & args);
		MutableArray(const std::initializer_list<Any *> & args);
		
		template <typename IterT>
		MutableArray(IterT && beg, IterT && end) :
			Array(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone)
		{ setClassKind(MutableArrayClass, true); }
		
		template <typename IterT>
		MutableArray(IterT && beg, IterT && end, CopyOption option) :
			Array(std::forward<IterT>(beg), std::forward<IterT>(end), option)
		{ setClassKind(MutableArrayClass, true); }
		
		MutableArray(const Path & path);
		MutableArray(const URL & url);
		virtual ~MutableArray();
		
		virtual void setValueForKey(Owning<Any> ptr, const std::string & utf8_key)
		COCONUT_FINAL_OVERRIDE;
		
		MutableArray & setArray(MutableArray && arr) noexcept;
		MutableArray & setArray(Array && arr) noexcept;
		
		MutableArray & setObjectsFromArray(const Array & arr);
		MutableArray & setObjectsFromArray(const Array & arr, CopyOption option);
		
		template <typename IterT>
		MutableArray & setObjects(IterT && beg, IterT && end)
		{ return setObjects(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone); }
		
		template <typename IterT>
		MutableArray & setObjects(IterT && beg, IterT && end, CopyOption option)
		{ return setObjectsFromArray({std::forward<IterT>(beg), std::forward<IterT>(end)}, option); }
		
		MutableArray & setObject(const Any & obj, std::size_t at_idx);
		MutableArray & setObject(const Any & obj, std::size_t at_idx, CopyOption option);
		
		MutableArray & setObject(Owning<Any> obj, std::size_t at_idx);
		MutableArray & setObject(Owning<Any> obj, std::size_t at_idx, CopyOption option);
		
		MutableArray & addObject(const Any & obj);
		MutableArray & addObject(const Any & obj, CopyOption option);
		
		MutableArray & addObject(Owning<Any> obj);
		MutableArray & addObject(Owning<Any> obj, CopyOption option);
		
		MutableArray & insertObject(const Any & obj, std::size_t at_idx);
		MutableArray & insertObject(const Any & obj, std::size_t at_idx, CopyOption option);
		
		MutableArray & insertObject(Owning<Any> obj, std::size_t at_idx);
		MutableArray & insertObject(Owning<Any> obj, std::size_t at_idx, CopyOption option);
		
		MutableArray & exchangeObjectAtIndex(std::size_t idx1, std::size_t idx2);
		
		MutableArray & addObjectsFromArray(const Array & arr);
		MutableArray & addObjectsFromArray(const Array & arr, CopyOption option);
		
		template <typename IterT>
		MutableArray & addObjects(IterT && beg, IterT && end) const
		{ return addObjects(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone); }
		
		template <typename IterT>
		MutableArray & addObjects(IterT && beg, IterT && end, CopyOption option)
		{ return addObjectsFromArray({std::forward<IterT>(beg), std::forward<IterT>(end)}, option); }
		
		MutableArray & removeObjectAtIndex(std::size_t index);
		
		MutableArray & removeObject(const Any & obj);
		MutableArray & removeObject(const Any & obj, const Range & in_rg);
		
		MutableArray & removeObject(const Owning<Any> & obj);
		MutableArray & removeObject(const Owning<Any> & obj, const Range & in_rg);
		
		MutableArray & removeObjectIdenticalTo(const Any & obj);
		MutableArray & removeObjectIdenticalTo(const Any & obj, const Range & in_rg);
		
		MutableArray & removeObjectIdenticalTo(const Owning<Any> & obj);
		MutableArray & removeObjectIdenticalTo(const Owning<Any> & obj, const Range & in_rg);
		
		MutableArray & removeObjectsInArray(const Array & arr);
		MutableArray & removeObjectsInRange(const Range & in_rg);
		
		template <typename IterT>
		MutableArray & removeObjects(IterT && beg, IterT && end)
		{ return removeObjectsInArray({std::forward<IterT>(beg), std::forward<IterT>(end)}); }
		
		MutableArray & removeLastObject();
		MutableArray & removeAllObjects();
		
		MutableArray & replaceObjectsInRange(const Range & in_rg, const Array & from);
		MutableArray & replaceObjectsInRange(const Range & in_rg, const Array & from, CopyOption option);
		MutableArray & replaceObjectsInRange(const Range & in_rg, const Array & from, const Range & from_rg);
		MutableArray & replaceObjectsInRange(const Range & in_rg, const Array & from, const Range & from_rg, CopyOption option);
		
		MutableArray & reverse();
		MutableArray & unique();
		
		MutableArray & filterUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func);
		MutableArray & filterUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options);
		
		MutableArray & sortUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func);
		MutableArray & sortUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, SortOptions options);

		MutableArray & sortAscending();
		MutableArray & sortAscending(SortOptions options);
		
		MutableArray & sortDescending();
		MutableArray & sortDescending(SortOptions options);
		
		MutableArray & sortUsingSelectorKey(const std::string & utf8_selkey);
		MutableArray & sortUsingSelectorKey(const std::string & utf8_selkey, bool descending);
		MutableArray & sortUsingSelectorKey(const std::string & utf8_selkey, bool descending, SortOptions options);
		
		MutableArray & sortUsingDescriptor(const SortDescriptor & descriptor);
		MutableArray & sortUsingDescriptor(const SortDescriptor & descriptor, SortOptions options);
		
		MutableArray & sortUsingDescriptors(const Array & descriptors);
		MutableArray & sortUsingDescriptors(const Array & descriptors, SortOptions options);

	public:
		Owning<Any> & operator [] (std::size_t index);
		
		MutableArray & operator + (const Any & obj);
		MutableArray & operator + (const Owning<Any> & obj);
		
		MutableArray & operator += (const Any & obj);
		MutableArray & operator += (const Owning<Any> & obj);
	};
}

#endif /* !COCONUT_FOUNDATION_MUTABLEARRAY_HPP */

/* EOF */