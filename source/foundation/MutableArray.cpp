//
// MutableArray.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/MutableArray.hpp>
#include <coconut/foundation/Range.hpp>

using namespace coconut;

MutableArray::MutableArray() :
	Array()
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const MutableArray & arr) :
	Array(arr.cbegin(), arr.cend())
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const MutableArray & arr, CopyOption option) :
	Array(arr.cbegin(), arr.cend(), option)
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(MutableArray && arr) :
	Array(std::forward<Array>(arr))
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(Array && arr) :
	Array(std::move(arr))
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const Array & arr, CopyOption option) :
	Array(arr.cbegin(), arr.cend(), option)
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const std::initializer_list<kind_ptr> & args) :
	Array(args)
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const std::initializer_list<kind_raw_ptr> & args) :
	Array(args)
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const Path & path) :
	Array(path)
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const URL & url) :
	Array(url)
{ setClassKind(MutableArrayClass, true); }

MutableArray::~MutableArray()
{ /* NOP */ }

#pragma mark -

MutableArrayPtr MutableArray::with()
{ return ptr_create<MutableArray>(); }

MutableArrayPtr MutableArray::with(const MutableArray & arr)
{ return ptr_create<MutableArray>(arr); }

MutableArrayPtr MutableArray::with(const MutableArray & arr, CopyOption option)
{ return ptr_create<MutableArray>(arr, option); }

MutableArrayPtr MutableArray::with(MutableArray && arr)
{ return ptr_create<MutableArray>(std::move(arr)); }

MutableArrayPtr MutableArray::with(const Array & arr, CopyOption option)
{ return ptr_create<MutableArray>(arr, option); }

MutableArrayPtr MutableArray::with(Array && arr)
{ return ptr_create<MutableArray>(std::move(arr)); }

MutableArrayPtr MutableArray::with(const std::initializer_list<kind_ptr> & args)
{ return ptr_create<MutableArray>(args); }

MutableArrayPtr MutableArray::with(const std::initializer_list<kind_raw_ptr> & args)
{ return ptr_create<MutableArray>(args); }

MutableArrayPtr MutableArray::with(const Path & path)
{ return ptr_create<MutableArray>(path); }

MutableArrayPtr MutableArray::with(const URL & url)
{ return ptr_create<MutableArray>(url); }

#pragma mark -

void MutableArray::setValueForKey(kind_ptr ptr, const std::string & utf8_key)
{
	if (runtime::algorithm::is_integer(utf8_key, true)) {
		setObject(ptr, runtime::algorithm::to_numeric<std::size_t>(utf8_key));
	} else {
		Object::setValueForKey(ptr, utf8_key);
	}
}

#pragma mark -

void MutableArray::setArray(MutableArray && arr)
{ m_impl = std::move(arr.m_impl); }

void MutableArray::setArray(Array && arr)
{ m_impl = std::move(arr.m_impl); }

#pragma mark -

void MutableArray::setObjectsFromArray(const Array & arr)
{ setObjectsFromArray(arr, CopyNone); }

void MutableArray::setObjectsFromArray(const Array & arr, CopyOption option)
{
	removeAllObjects();
	addObjectsFromArray(arr, option);
}

#pragma mark -

void MutableArray::setObject(const_kind_ref obj, std::size_t at_idx)
{ setObject(Object::copyObject(obj, CopyKind), at_idx, CopyNone); }

void MutableArray::setObject(const_kind_ref obj, std::size_t at_idx, CopyOption option)
{ setObject(Object::copyObject(obj, option), at_idx, CopyNone); }

#pragma mark -

void MutableArray::setObject(kind_ptr obj, std::size_t at_idx)
{ setObject(obj, at_idx, CopyNone); }

void MutableArray::setObject(kind_ptr obj, std::size_t at_idx, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	if (obj) {
		if (at_idx < size()) {
			if (option == CopyNone) {
				m_impl.at(at_idx) = obj;
			} else {
				kind_ptr copy = Object::copyObject(obj, option);
				if (copy) { m_impl.at(at_idx) = copy; }
			}
		} else {
			if (option == CopyNone) {
				m_impl.push_back(obj);
			} else {
				kind_ptr copy = Object::copyObject(obj, option);
				if (copy) { m_impl.push_back(copy); }
			}
		}
	}
}

#pragma mark -

void MutableArray::addObject(const_kind_ref obj)
{ addObject(Object::copyObject(obj, CopyKind), CopyNone); }

void MutableArray::addObject(const_kind_ref obj, CopyOption option)
{ addObject(Object::copyObject(obj, option), CopyNone); }

#pragma mark -

void MutableArray::addObject(kind_ptr obj)
{ addObject(obj, CopyNone); }

void MutableArray::addObject(kind_ptr obj, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	if (obj) {
		if (option == CopyNone) {
			m_impl.push_back(obj);
		} else {
			kind_ptr copy = Object::copyObject(obj, option);
			if (copy) { m_impl.push_back(copy); }
		}
	}
}

#pragma mark -

void MutableArray::insertObject(const_kind_ref obj, std::size_t at_idx)
{ insertObject(Object::copyObject(obj, CopyKind), at_idx, CopyNone); }

void MutableArray::insertObject(const_kind_ref obj, std::size_t at_idx, CopyOption option)
{ insertObject(Object::copyObject(obj, option), at_idx, CopyNone); }

#pragma mark -

void MutableArray::insertObject(kind_ptr obj, std::size_t at_idx)
{ insertObject(obj, at_idx, CopyNone); }

void MutableArray::insertObject(kind_ptr obj, std::size_t at_idx, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	if (obj) {
		if (at_idx <= size()) {
			if (at_idx == size()) {
				kind_ptr copy = Object::copyObject(obj, option);
				if (copy) { m_impl.push_back(copy); }
			} else {
				const_iterator it = cbegin() + static_cast<difference_type>(at_idx);
				kind_ptr copy = Object::copyObject(obj, option);
				if (copy) { m_impl.reserve(size() + 1); m_impl.insert(it, copy); }
			}
		}
	}
}

#pragma mark -

void MutableArray::exchangeObjectAtIndex(std::size_t idx1, std::size_t idx2)
{
	std::lock_guard<spin_type> lck(spin());
	if (idx1 < size() && idx2 < size()) {
		std::swap(m_impl.at(idx1), m_impl.at(idx2));
	}
}

#pragma mark -

void MutableArray::addObjectsFromArray(const Array & arr)
{ addObjectsFromArray(arr, CopyNone); }

void MutableArray::addObjectsFromArray(const Array & arr, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	for (const_iterator it = arr.cbegin(); it != arr.cend(); ++it) {
		addObject((*it), option);
	}
}

#pragma mark -

void MutableArray::removeObjectAtIndex(std::size_t index)
{
	std::lock_guard<spin_type> lck(spin());
	if (index < size()) { m_impl.erase(m_impl.begin() + static_cast<difference_type>(index)); }
}

#pragma mark -

void MutableArray::removeObject(const_kind_ref obj)
{
	std::lock_guard<spin_type> lck(spin());
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it) && (*it)->isEqual(obj)) { m_impl.erase(it); }
	}
}

void MutableArray::removeObject(const_kind_ref obj, const Range & in_rg)
{
	std::lock_guard<spin_type> lck(spin());
	std::size_t sz = size();
	if (sz && in_rg.maxRange() <= sz) {
		std::size_t loc, max;
		
		Range src(0, sz);
		Range dest = src.intersectionRange(in_rg);
		
		loc = dest.location();
		max = dest.maxRange();
		for (const_iterator it = cbegin() + static_cast<difference_type>(loc); it != cbegin() + static_cast<difference_type>(max); ++it) {
			if ((*it) && (*it)->isEqual(obj)) { m_impl.erase(it); }
		}
	}
}

#pragma mark -

void MutableArray::removeObject(const_kind_ptr & obj)
{ if (obj) { removeObject(*obj); } }

void MutableArray::removeObject(const_kind_ptr & obj, const Range & in_rg)
{ if (obj) { removeObject(*obj, in_rg); } }

#pragma mark -

void MutableArray::removeObjectIdenticalTo(const_kind_ref obj)
{
	std::lock_guard<spin_type> lck(spin());
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it) && (*it)->isIdenticalTo(obj)) { m_impl.erase(it); }
	}
}

void MutableArray::removeObjectIdenticalTo(const_kind_ref obj, const Range & in_rg)
{
	std::lock_guard<spin_type> lck(spin());
	std::size_t sz = size();
	if (sz && in_rg.maxRange() <= sz) {
		std::size_t loc, max;
		
		Range src(0, sz);
		Range dest = src.intersectionRange(in_rg);
		
		loc = dest.location();
		max = dest.maxRange();
		
		for (const_iterator it = cbegin() + static_cast<difference_type>(loc); it != cbegin() + static_cast<difference_type>(max); ++it) {
			if ((*it) && (*it)->isIdenticalTo(obj)) { m_impl.erase(it); }
		}
	}
}

#pragma mark -

void MutableArray::removeObjectIdenticalTo(const_kind_ptr & obj)
{ if (obj) { removeObjectIdenticalTo(*obj); } }

void MutableArray::removeObjectIdenticalTo(const_kind_ptr & obj, const Range & in_rg)
{ if (obj) { removeObjectIdenticalTo(*obj, in_rg); } }

#pragma mark -

void MutableArray::removeObjectsInArray(const Array & arr)
{
	std::lock_guard<spin_type> lck(spin());
	for (const_iterator it = arr.cbegin(); it != arr.cend(); ++it) {
		if ((*it)) { removeObject(*(*it)); }
	}
}

void MutableArray::removeObjectsInRange(const Range & in_rg)
{
	std::lock_guard<spin_type> lck(spin());
	std::size_t sz = size();
	if (sz && in_rg.maxRange() <= sz) {
		std::size_t loc, max;
		
		Range src(0, sz);
		Range dest = src.intersectionRange(in_rg);
		
		loc = dest.location();
		max = dest.maxRange();
		
		for (const_iterator it = cbegin() + static_cast<difference_type>(loc); it != cbegin() + static_cast<difference_type>(max); ++it) {
			m_impl.erase(it);
		}
	}
}

#pragma mark -

void MutableArray::removeLastObject()
{
	std::lock_guard<spin_type> lck(spin());
	m_impl.pop_back();
}

void MutableArray::removeAllObjects()
{
	std::lock_guard<spin_type> lck(spin());
	m_impl.clear();
}

#pragma mark -

void MutableArray::replaceObjectsInRange(const Range & in_rg, const Array & from)
{ replaceObjectsInRange(in_rg, from, Range(0, from.size()), CopyNone); }

void MutableArray::replaceObjectsInRange(const Range & in_rg, const Array & from, CopyOption option)
{ replaceObjectsInRange(in_rg, from, Range(0, from.size()), option); }

void MutableArray::replaceObjectsInRange(const Range & in_rg, const Array & from, const Range & from_rg)
{ replaceObjectsInRange(in_rg, from, from_rg, CopyNone); }

void MutableArray::replaceObjectsInRange(const Range & in_rg, const Array & from, const Range & from_rg, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	std::size_t sz = size();
	if (sz && in_rg.maxRange() <= sz) {
		if(from.size() && from_rg.maxRange() <= from.size()) {
			impl_type buf;
			std::size_t loc = from_rg.location(), max = 0;
			for (std::size_t i = 0; i < from_rg.length(); i++) {
				kind_ptr item = from.objectAtIndex(loc + i);
				if (item) { buf.push_back(item); }
			}

			Range src(0, sz);
			Range dest = src.intersectionRange(in_rg);
			
			loc = dest.location();
			max = dest.maxRange();
			
			for (const_iterator it = cbegin() + static_cast<difference_type>(loc); it != cbegin() + static_cast<difference_type>(max); ++it) {
				m_impl.erase(it);
			}
			
			for (const_reverse_iterator it = buf.crbegin(); it != buf.crend(); ++it) {
				if ((*it)) { insertObject(Object::copyObject((*it), option), dest.location()); }
			}
		}
	}
}

#pragma mark -

void MutableArray::reverse()
{ setObjectsFromArray(reversedArray()); }

void MutableArray::unique()
{ setObjectsFromArray(uniquedArray()); }

#pragma mark -

void MutableArray::filterUsingFunction(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func)
{ filterUsingFunction(func, EnumerationDefault); }

void MutableArray::filterUsingFunction(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options)
{ setObjectsFromArray(filteredArrayUsingFunction(func, CopyNone, options)); }

#pragma mark -

void MutableArray::sortUsingFunction(const std::function<bool(const_kind_ptr & a, const_kind_ptr & b)> & func)
{ sortUsingFunction(func, SortConcurrent); }

void MutableArray::sortUsingFunction(const std::function<bool(const_kind_ptr & a, const_kind_ptr & b)> & func, SortOptions options)
{ setObjectsFromArray(sortedArrayUsingFunction(func, CopyNone, options)); }

void MutableArray::sortAscending()
{ sortAscending(SortConcurrent); }

void MutableArray::sortAscending(SortOptions options)
{ setObjectsFromArray(sortedArrayAscending(CopyNone, options)); }

void MutableArray::sortDescending()
{ sortDescending(SortConcurrent); }

void MutableArray::sortDescending(SortOptions options)
{ setObjectsFromArray(sortedArrayDescending(CopyNone, options)); }

#pragma mark -

void MutableArray::sortUsingSelectorKey(const std::string & utf8_selkey)
{ sortUsingSelectorKey(utf8_selkey, false, SortConcurrent); }

void MutableArray::sortUsingSelectorKey(const std::string & utf8_selkey, bool descending)
{ sortUsingSelectorKey(utf8_selkey, descending, SortConcurrent); }

void MutableArray::sortUsingSelectorKey(const std::string & utf8_selkey, bool descending, SortOptions options)
{ setObjectsFromArray(sortedArrayUsingSelectorKey(utf8_selkey, CopyNone, descending, options)); }

#pragma mark -

void MutableArray::sortUsingDescriptor(const SortDescriptor & descriptor)
{ sortUsingDescriptor(descriptor, SortStable|SortConcurrent); }

void MutableArray::sortUsingDescriptor(const SortDescriptor & descriptor, SortOptions options)
{ setObjectsFromArray(sortedArrayUsingDescriptor(descriptor, CopyNone, options)); }

#pragma mark -

void MutableArray::sortUsingDescriptors(const Array & descriptors)
{ sortUsingDescriptors(descriptors, SortStable|SortConcurrent); }

void MutableArray::sortUsingDescriptors(const Array & descriptors, SortOptions options)
{ setObjectsFromArray(sortedArrayUsingDescriptors(descriptors, CopyNone, options)); }

#pragma mark -

kind_ptr & MutableArray::operator [] (std::size_t index)
{
	std::size_t sz = m_impl.size();
	if (index >= sz) {
		std::lock_guard<spin_type> lck(spin());
		m_impl.resize(sz + 1);
		index = sz;
	}
	return m_impl[index];
}

#pragma mark -

/* EOF */