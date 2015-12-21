//
// MutableArray.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Array.hpp>

#ifndef COCONUT_FOUNDATION_MUTABLEARRAY_HPP
#define COCONUT_FOUNDATION_MUTABLEARRAY_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT MutableArray : public Array
	{
	COCONUT_KDCL(coconut.MutableArray, Object.Array.MutableArray)
		
	public:
		MutableArray();
		MutableArray(const MutableArray & arr);
		MutableArray & operator = (const MutableArray & arr) = default;
		MutableArray(const MutableArray & arr, CopyOption option);
		
		MutableArray(MutableArray && arr);
		
		MutableArray(const Array & arr, CopyOption option);
		MutableArray(Array && arr);
		
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
		
		COCONUT_KTOR Owning<MutableArray> with();
		COCONUT_KTOR Owning<MutableArray> with(const MutableArray & arr);
		COCONUT_KTOR Owning<MutableArray> with(const MutableArray & arr, CopyOption option);
		COCONUT_KTOR Owning<MutableArray> with(MutableArray && arr);
		
		COCONUT_KTOR Owning<MutableArray> with(const Array & arr, CopyOption option);
		COCONUT_KTOR Owning<MutableArray> with(Array && arr);
		
		COCONUT_KTOR Owning<MutableArray> with(const std::initializer_list< Owning<Any> > & args);
		COCONUT_KTOR Owning<MutableArray> with(const std::initializer_list<Any *> & args);
		
		template <typename IterT>
		COCONUT_KTOR Owning<MutableArray> with(IterT && beg, IterT && end)
		{ return ptr_create<MutableArray>(std::forward<IterT>(beg), std::forward<IterT>(end)); }
		
		template <typename IterT>
		COCONUT_KTOR Owning<MutableArray> with(IterT && beg, IterT && end, CopyOption option)
		{ return ptr_create<MutableArray>(std::forward<IterT>(beg), std::forward<IterT>(end), option); }
		
		COCONUT_KTOR Owning<MutableArray> with(const Path & path);
		COCONUT_KTOR Owning<MutableArray> with(const URL & url);
		
		virtual void setValueForKey(Owning<Any> ptr, const std::string & utf8_key)
		COCONUT_FINAL_OVERRIDE;
		
		void setArray(MutableArray && arr);
		void setArray(Array && arr);
		
		void setObjectsFromArray(const Array & arr);
		void setObjectsFromArray(const Array & arr, CopyOption option);
		
		template <typename IterT>
		void setObjects(IterT && beg, IterT && end)
		{ setObjects(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone); }
		
		template <typename IterT>
		void setObjects(IterT && beg, IterT && end, CopyOption option)
		{ setObjectsFromArray(Array(std::forward<IterT>(beg), std::forward<IterT>(end)), option); }
		
		void setObject(const Any & obj, std::size_t at_idx);
		void setObject(const Any & obj, std::size_t at_idx, CopyOption option);
		
		void setObject(Owning<Any> obj, std::size_t at_idx);
		void setObject(Owning<Any> obj, std::size_t at_idx, CopyOption option);
		
		void addObject(const Any & obj);
		void addObject(const Any & obj, CopyOption option);
		
		void addObject(Owning<Any> obj);
		void addObject(Owning<Any> obj, CopyOption option);
		
		void insertObject(const Any & obj, std::size_t at_idx);
		void insertObject(const Any & obj, std::size_t at_idx, CopyOption option);
		
		void insertObject(Owning<Any> obj, std::size_t at_idx);
		void insertObject(Owning<Any> obj, std::size_t at_idx, CopyOption option);
		
		void exchangeObjectAtIndex(std::size_t idx1, std::size_t idx2);
		
		void addObjectsFromArray(const Array & arr);
		void addObjectsFromArray(const Array & arr, CopyOption option);
		
		template <typename IterT>
		void addObjects(IterT && beg, IterT && end) const
		{ addObjects(std::forward<IterT>(beg), std::forward<IterT>(end), CopyNone); }
		
		template <typename IterT>
		void addObjects(IterT && beg, IterT && end, CopyOption option)
		{ addObjectsFromArray(Array(std::forward<IterT>(beg), std::forward<IterT>(end)), option); }
		
		void removeObjectAtIndex(std::size_t index);
		
		void removeObject(const Any & obj);
		void removeObject(const Any & obj, const Range & in_rg);
		
		void removeObject(const Owning<Any> & obj);
		void removeObject(const Owning<Any> & obj, const Range & in_rg);
		
		void removeObjectIdenticalTo(const Any & obj);
		void removeObjectIdenticalTo(const Any & obj, const Range & in_rg);
		
		void removeObjectIdenticalTo(const Owning<Any> & obj);
		void removeObjectIdenticalTo(const Owning<Any> & obj, const Range & in_rg);
		
		void removeObjectsInArray(const Array & arr);
		void removeObjectsInRange(const Range & in_rg);
		
		template <typename IterT>
		void removeObjects(IterT && beg, IterT && end)
		{ removeObjectsInArray(Array(std::forward<IterT>(beg), std::forward<IterT>(end))); }
		
		void removeLastObject();
		void removeAllObjects();
		
		void replaceObjectsInRange(const Range & in_rg, const Array & from);
		void replaceObjectsInRange(const Range & in_rg, const Array & from, CopyOption option);
		void replaceObjectsInRange(const Range & in_rg, const Array & from, const Range & from_rg);
		void replaceObjectsInRange(const Range & in_rg, const Array & from, const Range & from_rg, CopyOption option);
		
		void reverse();
		void unique();
		
		void filterUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func);
		void filterUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options);
		
		void sortUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func);
		void sortUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, SortOptions options);

		void sortAscending();
		void sortAscending(SortOptions options);
		
		void sortDescending();
		void sortDescending(SortOptions options);
		
		void sortUsingSelectorKey(const std::string & utf8_selkey);
		void sortUsingSelectorKey(const std::string & utf8_selkey, bool descending);
		void sortUsingSelectorKey(const std::string & utf8_selkey, bool descending, SortOptions options);
		
		void sortUsingDescriptor(const SortDescriptor & descriptor);
		void sortUsingDescriptor(const SortDescriptor & descriptor, SortOptions options);
		
		void sortUsingDescriptors(const Array & descriptors);
		void sortUsingDescriptors(const Array & descriptors, SortOptions options);

	public:
		Owning<Any> & operator [] (std::size_t index);
	};
}

#endif /* !COCONUT_FOUNDATION_MUTABLEARRAY_HPP */

/* EOF */