//
// OrderedSet.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/OrderedSet.hpp>
#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/None.hpp>
#include <coconut/foundation/Number.hpp>
#include <coconut/foundation/Range.hpp>
#include <coconut/foundation/Set.hpp>

using namespace coconut;

OrderedSet::OrderedSet() :
	Object(OrderedSetClass),
	m_impl()
{ /* NOP */ }

OrderedSet::OrderedSet(const OrderedSet & set) :
	OrderedSet(set.cbegin(), set.cend(), CopyNone)
{ /* NOP */ }

OrderedSet::OrderedSet(const OrderedSet & set, CopyOption option) :
	OrderedSet(set.cbegin(), set.cend(), option)
{ /* NOP */ }

OrderedSet::OrderedSet(OrderedSet && set) :
	Object(OrderedSetClass),
	m_impl(std::move(set.m_impl))
{ /* NOP */ }

OrderedSet::OrderedSet(const std::initializer_list< Owning<Any> > & args) :
	OrderedSet(args.begin(), args.end(), CopyNone)
{ /* NOP */ }

OrderedSet::OrderedSet(const std::initializer_list<Any *> & args) :
	Object(OrderedSetClass),
	m_impl()
{
	for (Any * item : args) {
		if (dynamic_cast<Any *>(item) != nullptr && doesNotContain(*item)) { m_impl.push_back(item->kindCopy()); }
	}
}

OrderedSet::~OrderedSet()
{ /* NOP */ }

#pragma mark -

Owning<OrderedSet> OrderedSet::with(const OrderedSet & set)
{ return ptr_create<OrderedSet>(set); }

Owning<OrderedSet> OrderedSet::with(const OrderedSet & set, CopyOption option)
{ return ptr_create<OrderedSet>(set, option); }

Owning<OrderedSet> OrderedSet::with(OrderedSet && set)
{ return ptr_create<OrderedSet>(std::move(set)); }

Owning<OrderedSet> OrderedSet::with(const std::initializer_list< Owning<Any> > & args)
{ return ptr_create<OrderedSet>(args); }

Owning<OrderedSet> OrderedSet::with(const std::initializer_list<Any *> & args)
{ return ptr_create<OrderedSet>(args); }

#pragma mark -

std::size_t OrderedSet::hash() const
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

Owning<Any> OrderedSet::copy() const
{ return ptr_create<OrderedSet>(cbegin(), cend(), CopyKind); }

/*
Owning<Any> OrderedSet::mutableCopy() const
{
	return ptr_create<OrderedSet>(cbegin(), cend(), CopyKind);
}
*/

#pragma mark -

ComparisonResult OrderedSet::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (size() < ref_cast<OrderedSet>(ref).size()) {
			return OrderedAscending;
		} else if (size() > ref_cast<OrderedSet>(ref).size()) {
			return OrderedDescending;
		} else if (
			std::equal(cbegin(), cend(), ref_cast<OrderedSet>(ref).cbegin(), [] (const Owning<Any> & a, const Owning<Any> & b) -> bool
			{
				if (a && b) {
					return (a->compare(*b) == OrderedSame);
				}
				return false;
			})
		) {
			return OrderedSame;
		}
	}
	return OrderedDescending;
}

#pragma mark -

bool OrderedSet::doesContain(const Any & ref) const
{ return containsObject(ref); }

#pragma mark -

std::string OrderedSet::stringValue() const
{ return description(); }

#pragma mark -

std::size_t OrderedSet::size() const
{ return m_impl.size(); }

#pragma mark -

Owning<Any> OrderedSet::valueForKey(const std::string & utf8_key) const
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
	Array::impl_type buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		Owning<Any> item = (*it);
		Owning<Any> v;
		if (item) { v = item->valueForKey(utf8_key); }
		if (!v) { v = None::with(); }
		buf.push_back(v);
	}
	return Array::with(buf.cbegin(), buf.cend());
}

Owning<Any> OrderedSet::valueForKeyPath(const std::string & utf8_keypath) const
{
	if (isSelectorKey(utf8_keypath)) {
		return valueForSelectorKey(utf8_keypath);
	}
	Array::impl_type buf;
	std::vector<std::string> parts;
	parts = runtime::algorithm::split<std::string>(utf8_keypath, u8".");
	if (parts.size() == 1) {
		return valueForKey(utf8_keypath);
	} else if (parts.size() >= 2) {
		
		if (runtime::algorithm::is_integer(parts[0], true)) {
			Owning<Any> item = valueForKey(parts[0]);
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
			Owning<Any> item = (*it);
			Owning<Any> v;
			if (item) { v = item->valueForKeyPath(utf8_keypath); }
			if (!v) { v = None::with(); }
			buf.push_back(v);
		}
	}
	return Array::with(buf.cbegin(), buf.cend());
}

#pragma mark -

void OrderedSet::enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const
{ enumerateObjectsUsingFunction(func, EnumerationDefault); }

void OrderedSet::enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const
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

void OrderedSet::enumerateUsingFunction(const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const
{ enumerateObjectsUsingFunction(func, options); }

#pragma mark -

bool OrderedSet::containsObject(const Any & obj) const
{ return (indexOfObject(obj) != NotFound); }

bool OrderedSet::containsObject(const Owning<Any> & obj) const
{ if (obj) { return indexOfObject(*obj); } return false; }

#pragma mark -

bool OrderedSet::intersectsOrderedSet(const OrderedSet & set) const
{
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if((*it) && set.indexOfObject(*(*it)) != NotFound) {
			return true;
		}
	}
	return false;
}

bool OrderedSet::isSubsetOfOrderedSet(const OrderedSet & set) const
{
	bool result = false;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it)) {
			result = true;
			if((*it) && set.indexOfObject(*(*it)) == NotFound) {
				return false;
			}
		}
	}
	return result;
}

#pragma mark -

bool OrderedSet::intersectsSet(const Set & set) const
{
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if((*it) && set.member(*(*it))) {
			return true;
		}
	}
	return false;
}

bool OrderedSet::isSubsetOfSet(const Set & set) const
{
	bool result = false;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it)) {
			result = true;
			if((*it) && !set.member(*(*it))) {
				return false;
			}
		}
	}
	return result;
}

#pragma mark -

const Owning<Any> OrderedSet::firstObject() const
{
	if (size()) {
		return m_impl.front();
	}
	// Fault();
	return {};
}

const Owning<Any> OrderedSet::lastObject() const
{
	if (size()) {
		return m_impl.back();
	}
	// Fault();
	return {};
}

const Owning<Any> OrderedSet::objectAtIndex(std::size_t index) const
{
	if (index < size()) {
		return m_impl.at(index);
	}
	// Fault();
	return {};
}

#pragma mark -

std::size_t OrderedSet::indexOfObject(const Any & obj) const
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

std::size_t OrderedSet::indexOfObject(const Any & obj, Range in_rg) const
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

std::size_t OrderedSet::indexOfObject(const Owning<Any> & obj) const
{ if (obj) { return indexOfObject(*obj); } return false; }

std::size_t OrderedSet::indexOfObject(const Owning<Any> & obj, Range in_rg) const
{ if (obj) { return indexOfObject(*obj, in_rg); } return false; }

#pragma mark -

std::size_t OrderedSet::indexOfObjectIdenticalTo(const Any & obj) const
{
	std::size_t idx = 0;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
		if ((*it) && (*it)->isIdenticalTo(obj)) { return idx; }
	}
	return NotFound;
}

std::size_t OrderedSet::indexOfObjectIdenticalTo(const Owning<Any> & obj) const
{ if (obj) { return indexOfObjectIdenticalTo(*obj); } return false; }

#pragma mark -

std::size_t OrderedSet::indexOfObjectIdenticalTo(const Any & obj, Range in_rg) const
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

std::size_t OrderedSet::indexOfObjectIdenticalTo(const Owning<Any> & obj, Range in_rg) const
{ if (obj) { return indexOfObjectIdenticalTo(*obj, in_rg); } return false; }

#pragma mark -

std::size_t OrderedSet::indexOfObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const
{ return indexOfObjectPassingTest(func, EnumerationDefault); }

std::size_t OrderedSet::indexOfObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options) const
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

bool OrderedSet::everyObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const
{
	bool stop = false, ret = false;
	if (size()) {
		std::size_t idx = 0;
		auto op = runtime::async::exec(runtime::launch_any, [this, &idx, &stop, &ret, &func]
		{
			for (const_iterator it = cbegin(); it != cend(); ++it) {
				idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
				if ((*it)) {
					ret = func((*it), idx, stop);
					if (!ret) { break; }
					if (stop) { break; }
				}
			}
		});
		op.get();
	}
	return ret;
}

bool OrderedSet::noneObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const
{
	bool stop = false, ret = false;
	if (size()) {
		std::size_t idx = 0;
		auto op = runtime::async::exec(runtime::launch_any, [this, &idx, &stop, &ret, &func]
		{
			for (const_iterator it = cbegin(); it != cend(); ++it) {
				idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
				if ((*it)) {
					ret = func((*it), idx, stop);
					if (ret) { break; }
					if (stop) { break; }
				}
			}
		});
		op.get();
	}
	return !ret;
}

bool OrderedSet::someObjectPassingTest(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func) const
{
	bool stop = false, ret = false;
	if (size()) {
		std::size_t idx = 0;
		auto op = runtime::async::exec(runtime::launch_any, [this, &idx, &stop, &ret, &func]
		{
			for (const_iterator it = cbegin(); it != cend(); ++it) {
				idx = static_cast<std::size_t>(std::distance<const_iterator>(cbegin(), it));
				if ((*it)) {
					ret = func((*it), idx, stop);
					if (ret) { break; }
					if (stop) { break; }
				}
			}
		});
		op.get();
	}
	return ret;
}

#pragma mark -

const OrderedSet OrderedSet::reversedOrderedSet(CopyOption option) const
{
	impl_type buf(cbegin(), cend());
	if (buf.size() > 1) {
		std::reverse(buf.begin(), buf.end());
	}
	return OrderedSet(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

const OrderedSet OrderedSet::filteredOrderedSetUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, CopyOption option) const
{ return filteredOrderedSetUsingFunction(func, option, EnumerationDefault); }

const OrderedSet OrderedSet::filteredOrderedSetUsingFunction(const std::function<bool(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, CopyOption option, EnumerationOptions options) const
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
			return OrderedSet(buf.cbegin(), buf.cend(), option);
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
			return OrderedSet(buf.cbegin(), buf.cend(), option);
			
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
			return OrderedSet(buf.cbegin(), buf.cend(), option);
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
			return OrderedSet(buf.cbegin(), buf.cend(), option);
		}
		break;
		default:
			break;
	}
	return {};
}

#pragma mark -

const Owning<Any> OrderedSet::operator [] (std::size_t index) const
{ return objectAtIndex(index); }

#pragma mark -

OrderedSet::iterator OrderedSet::begin() { return m_impl.begin(); }
OrderedSet::iterator OrderedSet::end() { return m_impl.end(); }

OrderedSet::const_iterator OrderedSet::begin() const { return m_impl.begin(); }
OrderedSet::const_iterator OrderedSet::end() const { return m_impl.end(); }

OrderedSet::const_iterator OrderedSet::cbegin() const { return m_impl.cbegin(); }
OrderedSet::const_iterator OrderedSet::cend() const { return m_impl.cend(); }

OrderedSet::reverse_iterator OrderedSet::rbegin() { return m_impl.rbegin(); }
OrderedSet::reverse_iterator OrderedSet::rend() { return m_impl.rend(); }

OrderedSet::const_reverse_iterator OrderedSet::rbegin() const { return m_impl.rbegin(); }
OrderedSet::const_reverse_iterator OrderedSet::rend() const { return m_impl.rend(); }

OrderedSet::const_reverse_iterator OrderedSet::crbegin() const { return m_impl.crbegin(); }
OrderedSet::const_reverse_iterator OrderedSet::crend() const { return m_impl.crend(); }

/* EOF */