//
// Array.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/MutableArray.hpp>
#include <coconut/foundation/None.hpp>
#include <coconut/foundation/Number.hpp>
#include <coconut/foundation/Path.hpp>
#include <coconut/foundation/Range.hpp>
#include <coconut/foundation/Set.hpp>
#include <coconut/foundation/SortDescriptor.hpp>
#include <coconut/foundation/String.hpp>
#include <coconut/foundation/URL.hpp>

using namespace coconut;

Array::Array() :
	Object(ArrayClass),
	m_impl()
{ /* NOP */ }

Array::Array(const Array & arr) :
	Array(arr.cbegin(), arr.cend(), CopyNone)
{ /* NOP */ }

Array::Array(const Array & arr, CopyOption option) :
	Array(arr.cbegin(), arr.cend(), option)
{ /* NOP */ }

Array::Array(Array && arr) :
	Object(ArrayClass),
	m_impl(std::move(arr.m_impl))
{ /* NOP */ }

Array::Array(const std::initializer_list<kind_ptr> & args) :
	Array(args.begin(), args.end(), CopyNone)
{ /* NOP */ }

Array::Array(const std::initializer_list<kind_raw_ptr> & args) :
	Object(ArrayClass),
	m_impl()
{
	for (kind_raw_ptr item : args) {
		if (dynamic_cast<kind_raw_ptr>(item) != nullptr) { m_impl.push_back(item->kindCopy()); }
	}
}

Array::Array(const Path & path) :
	Object(ArrayClass),
	m_impl()
{ /* NOP SERIALIZATION */ }

Array::Array(const URL & url) :
	Object(ArrayClass),
	m_impl()
{ /* NOP SERIALIZATION */ }

Array::~Array()
{ /* NOP */ }

#pragma mark -

ArrayPtr Array::with()
{ return ptr_create<Array>(); }

ArrayPtr Array::with(const Array & arr)
{ return ptr_create<Array>(arr); }

ArrayPtr Array::with(const Array & arr, CopyOption option)
{ return ptr_create<Array>(arr, option); }

ArrayPtr Array::with(Array && arr)
{ return ptr_create<Array>(std::move(arr)); }

ArrayPtr Array::with(const std::initializer_list<kind_ptr> & args)
{ return ptr_create<Array>(args); }

ArrayPtr Array::with(const std::initializer_list<kind_raw_ptr> & args)
{ return ptr_create<Array>(args); }

ArrayPtr Array::with(const Path & path)
{ return ptr_create<Array>(path); }

ArrayPtr Array::with(const URL & url)
{ return ptr_create<Array>(url); }

#pragma mark -

std::size_t Array::hash() const
{
	std::size_t seed = 0;
	std::size_t tau = sizeof(std::size_t) >= 8 ? 0x278DDE6E5FD29E00ULL : 0x9E3779B9UL;
	const_iterator it = cbegin();
	while (it != cend()) {
		if ((*it)) { seed ^= (*it)->hash() + tau + (seed << 6) + (seed >> 2); }
		++it;
	}
	return seed;
}

#pragma mark -

kind_ptr Array::copy() const
{ return ptr_create<Array>(cbegin(), cend(), CopyKind); }

kind_ptr Array::mutableCopy() const
{ return ptr_create<MutableArray>(cbegin(), cend(), CopyKind); }

#pragma mark -

ComparisonResult Array::compare(const_kind_ref ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (size() < ref_cast<Array>(ref).size()) {
			return OrderedAscending;
		} else if (size() > ref_cast<Array>(ref).size()) {
			return OrderedDescending;
		} else if (
			std::equal(cbegin(), cend(), ref_cast<Array>(ref).cbegin(), [] (const_kind_ptr & a, const_kind_ptr & b) -> bool
			{
				if (a && b) { return (a->compare(*b) == OrderedSame); } return false;
			})
		) {
			return OrderedSame;
		}
	}
	return OrderedDescending;
}

#pragma mark -

bool Array::doesContain(const_kind_ref ref) const
{ return containsObject(ref); }

#pragma mark -

std::string Array::stringValue() const
{ return description(); }

#pragma mark -

std::size_t Array::size() const
{ return m_impl.size(); }

#pragma mark -

kind_ptr Array::valueForKey(const std::string & utf8_key) const
{
	if (isSelectorKey(utf8_key)) {
		return Object::valueForSelectorKey(utf8_key);
	} else if(isAttributeKey(utf8_key)) {
		return Object::valueForKey(utf8_key);
	} else if (runtime::algorithm::is_integer(utf8_key, true)) {
		return objectAtIndex(
			runtime::algorithm::to_numeric<std::size_t>(utf8_key)
		);
	}
	impl_type buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		kind_ptr item = (*it);
		kind_ptr v;
		if (item) { v = item->valueForKey(utf8_key); }
		if (!v) { v = None::with(); }
		buf.push_back(v);
	}
	return Array::with(buf.cbegin(), buf.cend());
}

kind_ptr Array::valueForKeyPath(const std::string & utf8_keypath) const
{
	if (isSelectorKey(utf8_keypath)) {
		return valueForSelectorKey(utf8_keypath);
	}
	impl_type buf;
	std::vector<std::string> parts;
	parts = runtime::algorithm::split<std::string>(utf8_keypath, u8".");
	if (parts.size() == 1) {
		return valueForKey(utf8_keypath);
	} else if (parts.size() >= 2) {
		
		if (runtime::algorithm::is_integer(parts[0], true)) {
			kind_ptr item = valueForKey(parts[0]);
			if (item) {
				parts.erase(parts.begin());
				if (parts.size() >= 2) {
					return item->valueForKeyPath(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts.size() == 1) {
					return item->valueForKey(parts[0]);
				}
			}
			return item;
		}
		
		for (const_iterator it = cbegin(); it != cend(); ++it) {
			kind_ptr item = (*it);
			kind_ptr v;
			if (item) { v = item->valueForKeyPath(utf8_keypath); }
			if (!v) { v = None::with(); }
			buf.push_back(v);
		}
	}
	return Array::with(buf.cbegin(), buf.cend());
}

#pragma mark -

const Array Array::makeObjectsPerformSelectorKey(const std::string & utf8_selkey, kind_ptr arg) const
{
	impl_type buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		kind_ptr item = (*it);
		kind_ptr v;
		if (item) {
			//v = item->valueForSelectorKey(utf8_selkey, arg);
			v = item->performSelectorKey(utf8_selkey, arg);
		}
		if (!v) { v = None::with(); }
		buf.push_back(v);
	}
	return Array(buf.begin(), buf.end());
}

#pragma mark -

void Array::enumerateObjectsUsingFunction(const std::function<void(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const
{ enumerateObjectsUsingFunction(func, EnumerationDefault); }

void Array::enumerateObjectsUsingFunction(const std::function<void(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const
{
	if (size()) {
		IterationOption iter_option = IterationAscending;
		if (options != EnumerationDefault) {
			if (options & EnumerationConcurrent || options == EnumerationConcurrent) {
				if (options & EnumerationReverse) {
					iter_option = IterationAsyncDescending;
				} else {
					iter_option = IterationAsyncAscending;
				}
			} else {
				if (options & EnumerationReverse || options == EnumerationReverse) {
					iter_option = IterationDescending;
				}
			}
		}
		
		std::size_t idx = 0;
		bool stop = false;
		
		switch (iter_option)
		{
			case IterationAscending:
			{
				for (const_iterator it = cbegin(); it != cend(); ++it) {
					idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
					if ((*it)) {
						func((*it), idx, stop);
						if (stop) { break; }
					}
				}
			}
			break;
			case IterationAsyncAscending:
			{
				auto op = runtime::async::exec(runtime::launch_async, [this, &idx, &stop, &func]
				{
					for (const_iterator it = cbegin(); it != cend(); ++it) {
						idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
						if ((*it)) {
							func((*it), idx, stop);
							if (stop) { break; }
						}
					}
				});
				op.get();
			}
			break;
			case IterationAsyncDescending:
			{
				auto op = runtime::async::exec(runtime::launch_async, [this, &idx, &stop, &func]
				{
					for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
						idx = static_cast<std::size_t>(std::distance<const_reverse_iterator>(it, crend() -1));
						if ((*it)) {
							func((*it), idx, stop);
							if (stop) { break; }
						}
					}
				});
				op.get();
			}
			break;
			case IterationDescending:
			{
				for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
					idx = static_cast<std::size_t>(std::distance<const_reverse_iterator>(it, crend() -1));
					if ((*it)) {
						func((*it), idx, stop);
						if (stop) { break; }
					}
				}
			}
			break;
			default:
				break;
		}
	}
}

#pragma mark -

bool Array::containsObject(const_kind_ref obj) const
{ return (indexOfObject(obj) != NotFound); }

bool Array::containsObject(const_kind_ptr & obj) const
{ if (obj) { return indexOfObject(*obj); } return false; }

#pragma mark -

kind_ptr Array::firstObject() const
{
	if (size()) {
		return m_impl.front();
	}
	// Fault();
	return {};
}

kind_ptr Array::lastObject() const
{
	if (size()) {
		return m_impl.back();
	}
	// Fault();
	return {};
}

kind_ptr Array::objectAtIndex(std::size_t index) const
{
	if (index < size()) {
		return m_impl.at(index);
	}
	// Fault();
	return {};
}

#pragma mark -

std::size_t Array::indexOfObject(const_kind_ref obj) const
{
	std::size_t idx = 0;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
		if ((*it) && (*it)->isIdenticalTo(obj)) {
			return idx;
		} else if ((*it) && (*it)->isEqual(obj)) {
			return idx;
		}
	}
	return NotFound;
}

std::size_t Array::indexOfObject(const_kind_ref obj, Range in_rg) const
{
	std::size_t idx = 0, sz = size();
	if (sz && in_rg.maxRange() <= sz) {
		std::size_t loc, len, max;
		
		Range src(0, sz);
		Range dest = src.intersectionRange(in_rg);
		
		loc = dest.location();
		len = dest.length();
		max = dest.maxRange();
		
		if (loc && len) {
			for (const_iterator it = cbegin() + static_cast<difference_type>(loc); it != cbegin() + static_cast<difference_type>(max); ++it) {
				idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
				if ((*it) && (*it)->isEqual(obj)) { return idx; }
			}
		}
	}
	return NotFound;
}

#pragma mark -

std::size_t Array::indexOfObject(const_kind_ptr & obj) const
{ if (obj) { return indexOfObject(*obj); } return NotFound; }

std::size_t Array::indexOfObject(const_kind_ptr & obj, Range in_rg) const
{ if (obj) { return indexOfObject(*obj, in_rg); } return NotFound; }

#pragma mark -

std::size_t Array::indexOfObjectIdenticalTo(const_kind_ref obj) const
{
	std::size_t idx = 0;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
		if ((*it) && (*it)->isIdenticalTo(obj)) { return idx; }
	}
	return NotFound;
}

std::size_t Array::indexOfObjectIdenticalTo(const_kind_ref obj, Range in_rg) const
{
	std::size_t idx = 0, sz = size();
	if (sz) {
		std::size_t loc, len, max;
		
		Range src(0, sz);
		Range dest = src.intersectionRange(in_rg);
		
		loc = dest.location();
		len = dest.length();
		max = dest.maxRange();
		
		if (loc && len) {
			for (const_iterator it = cbegin() + static_cast<difference_type>(loc); it != cbegin() + static_cast<difference_type>(max); ++it) {
				idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
				if ((*it) && (*it)->isIdenticalTo(obj)) { return idx; }
			}
		}
	}
	return NotFound;
}

#pragma mark -

std::size_t Array::indexOfObjectIdenticalTo(const_kind_ptr & obj) const
{ if (obj) { return indexOfObjectIdenticalTo(*obj); } return NotFound; }

std::size_t Array::indexOfObjectIdenticalTo(const_kind_ptr & obj, Range in_rg) const
{ if (obj) { return indexOfObjectIdenticalTo(*obj, in_rg); } return NotFound; }

#pragma mark -

kind_ptr Array::firstObjectCommonWithArray(const Array & arr) const
{
	kind_ptr item;
	if (size()) {
		std::size_t idx = 0;
		for (const_iterator it = cbegin(); it != cend(); ++it) {
			idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
			if ((item = arr.objectAtIndex(idx))) {
				if ((*it) && (*it)->isEqual(item)) { return (*it); }
			} else { break; }
		}
	}
	return item;
}

#pragma mark -

std::size_t Array::indexOfObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const
{ return indexOfObjectPassingTest(func, EnumerationDefault); }

std::size_t Array::indexOfObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const
{
	if (size()) {
		IterationOption iter_option = IterationAscending;
		if (options != EnumerationDefault) {
			if (options & EnumerationConcurrent || options == EnumerationConcurrent) {
				if (options & EnumerationReverse) {
					iter_option = IterationAsyncDescending;
				} else {
					iter_option = IterationAsyncAscending;
				}
			} else {
				if (options & EnumerationReverse || options == EnumerationReverse) {
					iter_option = IterationDescending;
				}
			}
		}
		
		std::size_t idx = 0;
		bool stop = false, ret = false;
		
		switch (iter_option)
		{
			case IterationAscending:
			{
				for (const_iterator it = cbegin(); it != cend(); ++it) {
					idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
					if ((*it)) {
						ret = func((*it), idx, stop);
						if (ret) { return idx; }
						if (stop) { break; }
					}
				}
			}
			break;
			case IterationAsyncAscending:
			{
				auto op = runtime::async::exec(runtime::launch_async, [this, &idx, &stop, &ret, &func]
				{
					for (const_iterator it = cbegin(); it != cend(); ++it) {
						idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
						if ((*it)) {
							ret = func((*it), idx, stop);
							if (ret) { return idx; }
							if (stop) { break; }
						}
					}
					return NotFound;
				});
				return op.get();
			}
			break;
			case IterationAsyncDescending:
			{
				auto op = runtime::async::exec(runtime::launch_async, [this, &idx, &stop, &ret, &func]
				{
					for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
						idx = static_cast<std::size_t>(std::distance<const_reverse_iterator>(it, crend() -1));
						if ((*it)) {
							ret = func((*it), idx, stop);
							if (ret) { return idx; }
							if (stop) { break; }
						}
					}
					return NotFound;
				});
				return op.get();
			}
			break;
			case IterationDescending:
			{
				for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
					idx = static_cast<std::size_t>(std::distance<const_reverse_iterator>(it, crend() -1));
					if ((*it)) {
						ret = func((*it), idx, stop);
						if (ret) { return idx; }
						if (stop) { break; }
					}
				}
			}
			break;
			default:
				break;
		}
	}
	return NotFound;
}

#pragma mark -

bool Array::everyObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const
{
	bool stop = false, ret = false;
	if (size()) {
		std::size_t idx = 0;
		for (const_iterator it = cbegin(); it != cend(); ++it) {
			idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
			if ((*it)) {
				ret = func((*it), idx, stop);
				if (!ret) { break; }
				if (stop) { break; }
			}
		}
	}
	return ret;
}

bool Array::someObjectPassingTest(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func) const
{
	bool stop = false, ret = false;
	if (size()) {
		std::size_t idx = 0;
		for (const_iterator it = cbegin(); it != cend(); ++it) {
			idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
			if ((*it)) {
				ret = func((*it), idx, stop);
				if (ret) { break; }
				if (stop) { break; }
			}
		}
	}
	return ret;
}

#pragma mark -

const Array Array::reversedArray(CopyOption option) const
{
	impl_type buf(cbegin(), cend());
	if (size() > 1) { std::reverse(buf.begin(), buf.end()); }
	return Array(buf.cbegin(), buf.cend(), option);
}

const Array Array::uniquedArray(CopyOption option) const
{
	impl_type buf;
	for (const_iterator it0 = cbegin(); it0 != cend(); ++it0) {
		const_iterator it1 = std::find_if(buf.cbegin(), buf.cend(),
			[&it0] (const_kind_ptr & item) -> bool {
				return (item->compare(*(*it0)) == OrderedSame);
			});
		if (it1 == buf.cend()) { buf.push_back(*it0); }
	}
	return Array(buf.cbegin(), buf.cend(), option);
}

const Array Array::shuffledArray(CopyOption option) const
{
	impl_type buf(cbegin(), cend());
	if (size() > 1) {
		std::mt19937 mt{ std::random_device{}() };
		std::size_t maxidx = buf.size() -1;
		std::size_t idx1 = 0, idx2;
		
		for (const_iterator it = buf.cbegin(); it != buf.cend(); ++it) {
			idx1 = static_cast<std::size_t>(std::distance<const_iterator>(buf.cbegin(), it));
			{
				std::uniform_int_distribution<std::uint32_t> dist
				{ 0U, static_cast<std::uint32_t>(maxidx - idx1) };
				idx2 = idx1 + static_cast<std::size_t>(dist(mt));
			}
			std::swap(buf.at(idx1), buf.at(idx2));
		}
	}
	return Array(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

const Array Array::filteredArrayUsingFunction(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, CopyOption option) const
{ return filteredArrayUsingFunction(func, option, EnumerationDefault); }

const Array Array::filteredArrayUsingFunction(const std::function<bool(const_kind_ptr & obj, std::size_t index, bool & stop)> & func, CopyOption option, EnumerationOptions options) const
{
	IterationOption iter_option = IterationAscending;
	if (options != EnumerationDefault) {
		if (options & EnumerationConcurrent || options == EnumerationConcurrent) {
			if (options & EnumerationReverse) {
				iter_option = IterationAsyncDescending;
			} else {
				iter_option = IterationAsyncAscending;
			}
		} else {
			if (options & EnumerationReverse || options == EnumerationReverse) {
				iter_option = IterationDescending;
			}
		}
	}
	
	impl_type buf;
	std::size_t idx = 0;
	bool stop = false, ret = false;
	
	switch (iter_option)
	{
		case IterationAscending:
		{
			for (const_iterator it = cbegin(); it != cend(); ++it) {
				idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
				if ((*it)) {
					ret = func((*it), idx, stop);
					if (ret) { buf.push_back((*it)); }
					if (stop) { break; }
				}
			}
		}
		break;
		case IterationAsyncAscending:
		{
			auto op = runtime::async::exec(runtime::launch_async, [this, &buf, &idx, &stop, &ret, &func]
			{
				for (const_iterator it = cbegin(); it != cend(); ++it) {
					idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
					if ((*it)) {
						ret = func((*it), idx, stop);
						if (ret) { buf.push_back((*it)); }
						if (stop) { break; }
					}
				}
			});
			op.get();
		}
		break;
		case IterationAsyncDescending:
		{
			auto op = runtime::async::exec(runtime::launch_async, [this, &buf, &idx, &stop, &ret, &func]
			{
				for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
					idx = static_cast<std::size_t>(std::distance<const_reverse_iterator>(it, crend() -1));
					if ((*it)) {
						ret = func((*it), idx, stop);
						if (ret) { buf.push_back((*it)); }
						if (stop) { break; }
					}
				}
			});
			op.get();
		}
		break;
		case IterationDescending:
		{
			for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
				idx = static_cast<std::size_t>(std::distance<const_reverse_iterator>(it, crend() -1));
				if ((*it)) {
					ret = func((*it), idx, stop);
					if (ret) { buf.push_back((*it)); }
					if (stop) { break; }
				}
			}
		}
		break;
		default:
			break;
	}
	return Array(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

const Array Array::sortedArrayUsingFunction(const std::function<bool(const_kind_ptr & a, const_kind_ptr & b)> & func, CopyOption option) const
{ return sortedArrayUsingFunction(func, option, SortDefault); }

const Array Array::sortedArrayUsingFunction(const std::function<bool(const_kind_ptr & a, const_kind_ptr & b)> & func, CopyOption option, SortOptions options) const
{
	impl_type buf;
	if (options == SortConcurrent || options & SortConcurrent) {
		auto op = runtime::async::exec(runtime::launch_async, [this, &options, &buf, &func]
		{
			buf.assign(cbegin(), cend());
			if (buf.size() > 1) {
				if (options & SortStable) {
					std::stable_sort(buf.begin(), buf.end(), func);
				} else {
					std::sort(buf.begin(), buf.end(), func);
				}
			}
			return;
		});
		op.get();
	} else {
		buf.assign(cbegin(), cend());
		if (buf.size() > 1) {
			if (options == SortStable || options & SortStable) {
				std::stable_sort(buf.begin(), buf.end(), func);
			} else {
				std::sort(buf.begin(), buf.end(), func);
			}
		}
	}
	return Array(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

const Array Array::sortedArrayAscending(CopyOption option) const
{ return sortedArrayAscending(option, SortDefault); }

const Array Array::sortedArrayAscending(CopyOption option, SortOptions options) const
{
	return sortedArrayUsingFunction([] (const_kind_ptr & a, const_kind_ptr & b) -> bool
	{
		if (a && b) { return (a->compare(*b) == OrderedAscending); } return false;
	}, option, options);
}

#pragma mark -

const Array Array::sortedArrayDescending(CopyOption option) const
{ return sortedArrayDescending(option, SortDefault); }

const Array Array::sortedArrayDescending(CopyOption option, SortOptions options) const
{
	return sortedArrayUsingFunction([] (const_kind_ptr & a, const_kind_ptr & b) -> bool
	{
		if (a && b) { return (a->compare(*b) == OrderedDescending); } return false;
	}, option, options);
}

#pragma mark -

const Array Array::sortedArrayUsingSelectorKey(const std::string & utf8_selkey, CopyOption option) const
{ return sortedArrayUsingSelectorKey(utf8_selkey, option, false, SortDefault); }

const Array Array::sortedArrayUsingSelectorKey(const std::string & utf8_selkey, CopyOption option, bool descending) const
{ return sortedArrayUsingSelectorKey(utf8_selkey, option, descending, SortDefault); }

const Array Array::sortedArrayUsingSelectorKey(const std::string & utf8_selkey, CopyOption option, bool descending, SortOptions options) const
{
	ComparisonResult cmp_result = descending ? OrderedDescending : OrderedAscending;
	return sortedArrayUsingFunction([&utf8_selkey, cmp_result](const_kind_ptr & a, const_kind_ptr & b) -> bool
	{
		if (a && b) {
			kind_ptr sel_cmp = a->valueForSelectorKey(utf8_selkey, b);
			if (sel_cmp) {
				return (static_cast<ComparisonResult>(sel_cmp->intValue()) == cmp_result);
			} else {
				return (a->compare(*b) == cmp_result);
			}
		}
		return false;
	}, option, options);
}
#pragma mark -

const Array Array::sortedArrayUsingDescriptor(const SortDescriptor & descriptor, CopyOption option) const
{ return sortedArrayUsingDescriptors({ descriptor.kindCopy() }, option, SortStable|SortConcurrent); }

const Array Array::sortedArrayUsingDescriptor(const SortDescriptor & descriptor, CopyOption option, SortOptions options) const
{ return sortedArrayUsingDescriptors({ descriptor.kindCopy() }, option, options); }

#pragma mark -

const Array Array::sortedArrayUsingDescriptors(const Array & descriptors, CopyOption option) const
{ return sortedArrayUsingDescriptors(descriptors, option, SortStable|SortConcurrent); }

const Array Array::sortedArrayUsingDescriptors(const Array & descriptors, CopyOption option, SortOptions options) const
{
	if (descriptors.size()) {
		ComparisonResult cmp_result = OrderedAscending;
		return sortedArrayUsingFunction([&descriptors, cmp_result](const_kind_ptr & a, const_kind_ptr & b) -> bool
		{
			if (a && b) {
				ComparisonResult result = OrderedSame;
				for (const_iterator it = descriptors.cbegin(); it != descriptors.cend(); ++it) {
					if ((*it) && (*it)->isKindOf(SortDescriptorClass)) {
						result = ptr_cast<SortDescriptor>((*it))->compareObject(a, b);
						if (OrderedSame != result) { break; };
					}
				}
				return (result == cmp_result);
			}
			return false;
		}, option, options);
	}
	// Fault();
	return {};
}

#pragma mark -

const Array Array::arrayByPushingObject(const_kind_ref obj) const
{ return arrayByPushingObject(Object::copyObject(obj, CopyKind), CopyNone); }

const Array Array::arrayByPushingObject(const_kind_ref obj, CopyOption option) const
{ return arrayByPushingObject(Object::copyObject(obj, option), CopyNone); }

#pragma mark -

const Array Array::arrayByPushingObject(kind_ptr obj) const
{ return arrayByPushingObject(obj, CopyNone); }

const Array Array::arrayByPushingObject(kind_ptr obj, CopyOption option) const
{
	if (obj) {
		impl_type buf;
		buf.push_back(obj);
		buf.insert(buf.cend(), cbegin(), cend());
		return Array(buf.cbegin(), buf.cend(), option);
	}
	// Fault();
	return {};
}

#pragma mark -

const Array Array::arrayByPushingObjectsFromArray(const Array & arr) const
{ return arrayByPushingObjectsFromArray(arr, CopyNone); }

const Array Array::arrayByPushingObjectsFromArray(const Array & arr, CopyOption option) const
{
	impl_type buf(arr.cbegin(), arr.cend());
	buf.insert(buf.cend(), cbegin(), cend());
	return Array(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

const Array Array::arrayByAddingObject(const_kind_ref obj) const
{ return arrayByAddingObject(Object::copyObject(obj, CopyKind), CopyNone); }

const Array Array::arrayByAddingObject(const_kind_ref obj, CopyOption option) const
{ return arrayByAddingObject(Object::copyObject(obj, option), CopyNone); }

#pragma mark -

const Array Array::arrayByAddingObject(kind_ptr obj) const
{ return arrayByAddingObject(obj, CopyNone); }

const Array Array::arrayByAddingObject(kind_ptr obj, CopyOption option) const
{
	if (obj) {
		impl_type buf(cbegin(), cend());
		buf.push_back(obj);
		return Array(buf.cbegin(), buf.cend(), option);
	}
	// Fault();
	return {};
}

#pragma mark -

const Array Array::arrayByAddingObjectsFromArray(const Array & arr) const
{ return arrayByAddingObjectsFromArray(arr, CopyNone); }

const Array Array::arrayByAddingObjectsFromArray(const Array & arr, CopyOption option) const
{
	impl_type buf(cbegin(), cend());
	buf.insert(buf.cend(), arr.cbegin(), arr.cend());
	return Array(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

const Array Array::subarrayWithRange(const Range & rg, CopyOption option) const
{
	impl_type buf;
	if(size() && rg.maxRange() <= size()) {
		std::size_t loc = rg.location();
		for (std::size_t i = 0; i < rg.length(); i++) {
			kind_ptr item = objectAtIndex(loc + i);
			if (item) { buf.push_back(item); }
		}
	} else {
		// Fault();
	}
	return Array(buf.cbegin(), buf.cend(), option);
}

const Array Array::subarrayWithRange(std::size_t location, std::size_t length, CopyOption option) const
{ return Array::subarrayWithRange(Range(location, length), option); }

#pragma mark -

const String Array::componentsJoinedByString(const String & separator)
{
	// TODO MutableString e.g avoiding conv utf16 to utf8 then utf16
	std::vector<std::string> buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it)) {
			buf.push_back((*it)->stringValue());
		}
	}
	return String(runtime::algorithm::join<std::string>(buf, separator.stringValue()));
}

#pragma mark -

bool Array::writeToFile(const Path & path, bool atomically) const
{
	return false;
}

bool Array::writeToURL(const URL & url, bool atomically) const
{
	return false;
}

#pragma mark -

const_kind_ptr Array::operator [] (std::size_t index) const
{ return objectAtIndex(index); }

const Array Array::operator [] (const Range & rg) const
{ return subarrayWithRange(rg); }

#pragma mark -

Array::iterator Array::begin() { return m_impl.begin(); }
Array::iterator Array::end() { return m_impl.end(); }

Array::const_iterator Array::begin() const { return m_impl.begin(); }
Array::const_iterator Array::end() const { return m_impl.end(); }

Array::const_iterator Array::cbegin() const { return m_impl.cbegin(); }
Array::const_iterator Array::cend() const { return m_impl.cend(); }

Array::reverse_iterator Array::rbegin() { return m_impl.rbegin(); }
Array::reverse_iterator Array::rend() { return m_impl.rend(); }

Array::const_reverse_iterator Array::rbegin() const { return m_impl.rbegin(); }
Array::const_reverse_iterator Array::rend() const { return m_impl.rend(); }

Array::const_reverse_iterator Array::crbegin() const { return m_impl.crbegin(); }
Array::const_reverse_iterator Array::crend() const { return m_impl.crend(); }

/* EOF */