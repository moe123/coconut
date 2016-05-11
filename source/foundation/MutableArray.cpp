//
// MutableArray.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/MutableArray.hpp>
#include <coconut/foundation/Range.hpp>
#include <coconut/foundation/Slice.hpp>

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

MutableArray::MutableArray(MutableArray && arr) noexcept :
	Array(std::forward<Array>(arr))
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(Array && arr) noexcept :
	Array(std::move(arr))
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const Array & arr, CopyOption option) :
	Array(arr.cbegin(), arr.cend(), option)
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const std::initializer_list< Owning<Any> > & args) :
	Array(args)
{ setClassKind(MutableArrayClass, true); }

MutableArray::MutableArray(const std::initializer_list<Any *> & args) :
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

void MutableArray::setValueForKey(Owning<Any> ptr, const std::string & utf8_key)
{
	if (runtime::algorithm::is_integer(utf8_key, true)) {
		setObject(ptr, runtime::algorithm::to_numeric<std::size_t>(utf8_key));
	} else {
		Object::setValueForKey(ptr, utf8_key);
	}
}

#pragma mark -

MutableArray & MutableArray::setArray(MutableArray && arr) noexcept
{ m_impl = std::move(arr.m_impl); return *this; }

MutableArray & MutableArray::setArray(Array && arr) noexcept
{ m_impl = std::move(arr.m_impl); return *this; }

#pragma mark -

MutableArray & MutableArray::setObjectsFromArray(const Array & arr)
{ setObjectsFromArray(arr, CopyNone); return *this; }

MutableArray & MutableArray::setObjectsFromArray(const Array & arr, CopyOption option)
{
	removeAllObjects();
	addObjectsFromArray(arr, option);
	return *this;
}

#pragma mark -

MutableArray & MutableArray::setObject(const Any & obj, std::size_t at_idx)
{ setObject(Object::copyObject(obj, CopyKind), at_idx, CopyNone); return *this; }

MutableArray & MutableArray::setObject(const Any & obj, std::size_t at_idx, CopyOption option)
{ setObject(Object::copyObject(obj, option), at_idx, CopyNone); return *this; }

#pragma mark -

MutableArray & MutableArray::setObject(Owning<Any> obj, std::size_t at_idx)
{ setObject(obj, at_idx, CopyNone); return *this; }

MutableArray & MutableArray::setObject(Owning<Any> obj, std::size_t at_idx, CopyOption option)
{
	if (obj) {
		std::size_t sz = m_impl.size();
		if (at_idx < sz) {
			if (option == CopyNone) {
				m_impl.at(at_idx) = obj;
			} else {
				Owning<Any> copy = Object::copyObject(obj, option);
				if (copy) { m_impl.at(at_idx) = copy; }
			}
		} else {
			if (option == CopyNone) {
				m_impl.push_back(obj);
			} else {
				Owning<Any> copy = Object::copyObject(obj, option);
				if (copy) { m_impl.push_back(copy); }
			}
		}
	}
	return *this;
}

#pragma mark -

MutableArray & MutableArray::addObject(const Any & obj)
{ addObject(Object::copyObject(obj, CopyKind), CopyNone); return *this; }

MutableArray & MutableArray::addObject(const Any & obj, CopyOption option)
{ addObject(Object::copyObject(obj, option), CopyNone); return *this; }

#pragma mark -

MutableArray & MutableArray::addObject(Owning<Any> obj)
{ addObject(obj, CopyNone); return *this; }

MutableArray & MutableArray::addObject(Owning<Any> obj, CopyOption option)
{
	if (obj) {
		if (option == CopyNone) {
			m_impl.push_back(obj);
		} else {
			Owning<Any> copy = Object::copyObject(obj, option);
			if (copy) { m_impl.push_back(copy); }
		}
	}
	return *this;
}

#pragma mark -

MutableArray & MutableArray::insertObject(const Any & obj, std::size_t at_idx)
{ insertObject(Object::copyObject(obj, CopyKind), at_idx, CopyNone); return *this; }

MutableArray & MutableArray::insertObject(const Any & obj, std::size_t at_idx, CopyOption option)
{ insertObject(Object::copyObject(obj, option), at_idx, CopyNone); return *this; }

#pragma mark -

MutableArray & MutableArray::insertObject(Owning<Any> obj, std::size_t at_idx)
{ insertObject(obj, at_idx, CopyNone); return *this; }

MutableArray & MutableArray::insertObject(Owning<Any> obj, std::size_t at_idx, CopyOption option)
{
	if (obj) {
		std::size_t sz = m_impl.size();
		if (at_idx <= sz) {
			if (at_idx == sz) {
				Owning<Any> copy = Object::copyObject(obj, option);
				if (copy) { m_impl.push_back(copy); }
			} else {
				const_iterator it = cbegin() + static_cast<difference_type>(at_idx);
				Owning<Any> copy = Object::copyObject(obj, option);
				if (copy) { m_impl.reserve(sz + 1); m_impl.insert(it, copy); }
			}
		}
	}
	return *this;
}

#pragma mark -

MutableArray & MutableArray::exchangeObjectAtIndex(std::size_t idx1, std::size_t idx2)
{
	if (idx1 < size() && idx2 < m_impl.size()) {
		std::swap(m_impl.at(idx1), m_impl.at(idx2));
	}
	return *this;
}

#pragma mark -

MutableArray & MutableArray::addObjectsFromArray(const Array & arr)
{ addObjectsFromArray(arr, CopyNone); return *this; }

MutableArray & MutableArray::addObjectsFromArray(const Array & arr, CopyOption option)
{
	for (const_iterator it = arr.cbegin(); it != arr.cend(); ++it) {
		addObject((*it), option);
	}
	return *this;
}

#pragma mark -

MutableArray & MutableArray::removeObjectAtIndex(std::size_t index)
{
	if (index < m_impl.size()) {
		m_impl.erase(m_impl.begin() + static_cast<difference_type>(index));
	}
	return *this;
}

#pragma mark -

MutableArray & MutableArray::removeObject(const Any & obj)
{
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it) && (*it)->isEqual(obj)) { m_impl.erase(it); }
	}
	return *this;
}

MutableArray & MutableArray::removeObject(const Any & obj, const Range & in_rg)
{
	std::size_t sz = m_impl.size();
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
	return *this;
}

#pragma mark -

MutableArray & MutableArray::removeObject(const Owning<Any> & obj)
{ if (obj) { removeObject(*obj); } return *this; }

MutableArray & MutableArray::removeObject(const Owning<Any> & obj, const Range & in_rg)
{ if (obj) { removeObject(*obj, in_rg); } return *this; }

#pragma mark -

MutableArray & MutableArray::removeObjectIdenticalTo(const Any & obj)
{
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it) && (*it)->isIdenticalTo(obj)) { m_impl.erase(it); }
	}
	return *this;
}

MutableArray & MutableArray::removeObjectIdenticalTo(const Any & obj, const Range & in_rg)
{
	std::size_t sz = m_impl.size();
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
	return *this;
}

#pragma mark -

MutableArray & MutableArray::removeObjectIdenticalTo(const Owning<Any> & obj)
{ if (obj) { removeObjectIdenticalTo(*obj); } return *this; }

MutableArray & MutableArray::removeObjectIdenticalTo(const Owning<Any> & obj, const Range & in_rg)
{ if (obj) { removeObjectIdenticalTo(*obj, in_rg); } return *this; }

#pragma mark -

MutableArray & MutableArray::removeObjectsInArray(const Array & arr)
{
	for (const_iterator it = arr.cbegin(); it != arr.cend(); ++it) {
		if ((*it)) { removeObject(*(*it)); }
	}
	return *this;
}

MutableArray & MutableArray::removeObjectsInRange(const Range & in_rg)
{
	std::size_t sz = m_impl.size();
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
	return *this;
}

#pragma mark -

MutableArray & MutableArray::removeLastObject()
{ m_impl.pop_back(); return *this; }

MutableArray & MutableArray::removeAllObjects()
{ m_impl.clear(); return *this; }

#pragma mark -

MutableArray & MutableArray::replaceObjectsInRange(const Range & in_rg, const Array & from)
{ replaceObjectsInRange(in_rg, from, Range(0, from.size()), CopyNone); return *this; }

MutableArray & MutableArray::replaceObjectsInRange(const Range & in_rg, const Array & from, CopyOption option)
{ replaceObjectsInRange(in_rg, from, Range(0, from.size()), option); return *this; }

MutableArray & MutableArray::replaceObjectsInRange(const Range & in_rg, const Array & from, const Range & from_rg)
{ replaceObjectsInRange(in_rg, from, from_rg, CopyNone); return *this; }

MutableArray & MutableArray::replaceObjectsInRange(const Range & in_rg, const Array & from, const Range & from_rg, CopyOption option)
{
	std::size_t sz = m_impl.size();
	if (sz && in_rg.maxRange() <= sz) {
		if (from.size() && from_rg.maxRange() <= from.size()) {
			impl_trait buf;
			std::size_t loc = from_rg.location(), max = 0;
			for (std::size_t i = 0; i < from_rg.length(); i++) {
				Owning<Any> item = from.objectAtIndex(loc + i);
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
	return *this;
}

#pragma mark -

MutableArray & MutableArray::reverse()
{ setObjectsFromArray(reversedArray()); return *this; }

MutableArray & MutableArray::unique()
{ setObjectsFromArray(uniquedArray()); return *this; }

#pragma mark -

MutableArray & MutableArray::filterUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func)
{ filterUsingFunction(func, EnumerationDefault); return *this; }

MutableArray & MutableArray::filterUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options)
{ setObjectsFromArray(filteredArrayUsingFunction(func, CopyNone, options)); return *this; }

#pragma mark -

MutableArray & MutableArray::sortUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func)
{ sortUsingFunction(func, SortConcurrent); return *this; }

MutableArray & MutableArray::sortUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, SortOptions options)
{ setObjectsFromArray(sortedArrayUsingFunction(func, CopyNone, options)); return *this; }

MutableArray & MutableArray::sortAscending()
{ sortAscending(SortConcurrent); return *this; }

MutableArray & MutableArray::sortAscending(SortOptions options)
{ setObjectsFromArray(sortedArrayAscending(CopyNone, options)); return *this; }

MutableArray & MutableArray::sortDescending()
{ sortDescending(SortConcurrent); return *this; }

MutableArray & MutableArray::sortDescending(SortOptions options)
{ setObjectsFromArray(sortedArrayDescending(CopyNone, options)); return *this; }

#pragma mark -

MutableArray & MutableArray::sortUsingSelectorKey(const std::string & utf8_selkey)
{ sortUsingSelectorKey(utf8_selkey, false, SortConcurrent); return *this; }

MutableArray & MutableArray::sortUsingSelectorKey(const std::string & utf8_selkey, bool descending)
{ sortUsingSelectorKey(utf8_selkey, descending, SortConcurrent); return *this; }

MutableArray & MutableArray::sortUsingSelectorKey(const std::string & utf8_selkey, bool descending, SortOptions options)
{ setObjectsFromArray(sortedArrayUsingSelectorKey(utf8_selkey, CopyNone, descending, options)); return *this; }

#pragma mark -

MutableArray & MutableArray::sortUsingDescriptor(const SortDescriptor & descriptor)
{ sortUsingDescriptor(descriptor, SortStable|SortConcurrent); return *this; }

MutableArray & MutableArray::sortUsingDescriptor(const SortDescriptor & descriptor, SortOptions options)
{ setObjectsFromArray(sortedArrayUsingDescriptor(descriptor, CopyNone, options)); return *this;}

#pragma mark -

MutableArray & MutableArray::sortUsingDescriptors(const Array & descriptors)
{ sortUsingDescriptors(descriptors, SortStable|SortConcurrent); return *this; }

MutableArray & MutableArray::sortUsingDescriptors(const Array & descriptors, SortOptions options)
{ setObjectsFromArray(sortedArrayUsingDescriptors(descriptors, CopyNone, options)); return *this; }

#pragma mark -

Owning<Any> & MutableArray::operator [] (std::size_t index)
{
	std::size_t sz = m_impl.size();
	if (index == MaxFound || index >= sz) {
		m_impl.resize(sz + 1);
		index = sz;
	}
	return m_impl[index];
}

#pragma mark -

MutableArray & MutableArray::operator + (const Any & obj)
{ addObject(obj); return *this; }

MutableArray & MutableArray::operator + (const Owning<Any> & obj)
{ addObject(obj); return *this; }

#pragma mark -

MutableArray & MutableArray::operator += (const Any & obj)
{ addObject(obj); return *this; }

MutableArray & MutableArray::operator += (const Owning<Any> & obj)
{ addObject(obj); return *this; }

#pragma mark -

/* EOF */