//
// Set.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Set.hpp>
#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/OrderedSet.hpp>
#include <coconut/foundation/None.hpp>

using namespace coconut;

Set::Set() :
	Object(SetClass),
	m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
	{ return (a->compare(*b) != OrderedSame); })
{ /* NOP */ }

Set::Set(const Set & set) :
	Set(set.cbegin(), set.cend(), CopyNone)
{ /* NOP */ }

Set::Set(const Set & set, CopyOption option) :
	Set(set.cbegin(), set.cend(), option)
{ /* NOP */ }

Set::Set(Set && set) noexcept :
	Object(SetClass),
	m_impl(std::move(set.m_impl))
{ /* NOP */ }

Set::Set(const std::initializer_list< Owning<Any> > & args) :
	Set(args.begin(), args.end(), CopyNone)
{ /* NOP */ }

Set::Set(const std::initializer_list<Any *> & args) :
	Object(SetClass),
	m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
	{ return (a->compare(*b) != OrderedSame); })
{
	for (Any * item : args) {
		if (dynamic_cast<Any *>(item) != nullptr) { m_impl.insert(item->kindCopy()); }
	}
}

Set::~Set()
{ /* NOP */ }

#pragma mark -

std::size_t Set::hash() const
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

Owning<Any> Set::copy() const
{
	//std::unique_lock<spinlock>();
	return ptr_create<Set>(cbegin(), cend(), CopyKind);
}

/*
Owning<Any> Set::mutableCopy() const
{
return ptr_create<MutableSet>(cbegin(), cend(), CopyKind);
}
*/

#pragma mark -

ComparisonResult Set::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (size() < ref_cast<Set>(ref).size()) {
			return OrderedAscending;
		} else if (size() > ref_cast<Set>(ref).size()) {
			return OrderedDescending;
		} else if (
			std::equal(cbegin(), cend(), ref_cast<Set>(ref).cbegin(), [] (const Owning<Any> & a, const Owning<Any> & b) -> bool
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

bool Set::doesContain(const Any & ref) const
{ return containsObject(ref); }

#pragma mark -

std::string Set::stringValue() const
{ return description(); }

#pragma mark -

std::size_t Set::size() const
{ return m_impl.size(); }

#pragma mark -

Owning<Any> Set::valueForKey(const std::string & utf8_key) const
{
	if (isSelectorKey(utf8_key)) {
		return Object::valueForSelectorKey(utf8_key);
	} else if(isAttributeKey(utf8_key)) {
		return Object::attributeForKey(utf8_key);
	} else if (runtime::algorithm::is_integer(utf8_key, true)) {
		if (size()) {
			size_t idx = runtime::algorithm::to_numeric<std::size_t>(utf8_key);
			if (idx < size()) {
				const_iterator it = m_impl.cbegin();
				std::advance<const_iterator>(it, static_cast<difference_type>(idx));
				return (*it);
			}
		}
		// Fault();
		return {};
	}
	
	Array::impl_trait buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		Owning<Any> item = (*it);
		Owning<Any> v;
		if (item) { v = item->valueForKey(utf8_key); }
		if (!v) { v = ptr_create<None>(); }
		buf.push_back(v);
	}
	return ptr_create<Array>(buf.cbegin(), buf.cend());
}

Owning<Any> Set::valueForKeyPath(const std::string & utf8_keypath) const
{
	if (isSelectorKey(utf8_keypath)) {
		return valueForSelectorKey(utf8_keypath);
	}
	Array::impl_trait buf;
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
			if (!v) { v = ptr_create<None>(); }
			buf.push_back(v);
		}
	}
	return ptr_create<Array>(buf.cbegin(), buf.cend());
}

#pragma mark -

const Array Set::makeObjectsPerformSelectorKey(const std::string & utf8_selkey, Owning<Any> arg) const
{
	Array::impl_trait buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		Owning<Any> item = (*it);
		Owning<Any> v;
		if (item) {
			v = item->valueForSelectorKey(utf8_selkey, arg);
		}
		if (!v) { v = ptr_create<None>(); }
		buf.push_back(v);
	}
	return Array(buf.cbegin(), buf.cend());
}

#pragma mark -

void Set::enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, bool & stop)> & func) const
{ enumerateObjectsUsingFunction(func, EnumerationDefault); }

void Set::enumerateObjectsUsingFunction(const std::function<void(const Owning<Any> & obj, bool & stop)> & func, EnumerationOptions options) const
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
		
		bool stop = false;
		
		switch (iter_option)
		{
			case IterationAscending:
			{
				for (const_iterator it = cbegin(); it != cend(); ++it) {
					if ((*it)) {
						func((*it), stop);
						if (stop) { break; }
					}
				}
			}
			break;
			case IterationAsyncAscending:
			{
				auto op = runtime::async::exec(runtime::launch_async, [this, &stop, &func]
				{
					for (const_iterator it = cbegin(); it != cend(); ++it) {
						if ((*it)) {
							func((*it), stop);
							if (stop) { break; }
						}
					}
				});
				op.get();
			}
			break;
			case IterationAsyncDescending:
			{
				auto op = runtime::async::exec(runtime::launch_async, [this, &stop, &func]
				{
					for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
						if ((*it)) {
							func((*it), stop);
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
					if ((*it)) {
						func((*it), stop);
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

bool Set::containsObject(const Any & obj) const
{
	if (member(obj)) {
		return true;
	}
	return false;
}

bool Set::containsObject(const Owning<Any> & obj) const
{ if (obj) { return containsObject(*obj); } return false; }

#pragma mark -

bool Set::intersectsSet(const Set & set) const
{
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if((*it) && set.member(*(*it))) {
			return true;
		}
	}
	return false;
}

bool Set::isSubsetOfSet(const Set & set) const
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

const Owning<Any> Set::member(const Any & obj) const
{
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it) && (*it)->isIdenticalTo(obj)) {
			return (*it);
		} else if((*it) && (*it)->isEqual(obj)) {
			return (*it);
		}
	}
	// Fault();
	return {};
}

const Owning<Any> Set::member(const Owning<Any> & obj) const
{ if (obj) { return member(*obj); } return {}; }

#pragma mark -

const Owning<Any> Set::anyObject() const
{
	if (size() == 1) {
		const_iterator it = m_impl.cbegin();
		//std::advance<const_iterator>(it, 0);
		return (*it);
	} else if (size() > 1) { // std::size_t radar: 22086484
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<std::uint32_t> dist{ 0U, static_cast<std::uint32_t>(size() -1) };
		std::uint32_t next = dist(mt);
		const_iterator it = m_impl.cbegin();
		std::advance<const_iterator>(it, next);

		return (*it);
	}
	// Fault();
	return {};
}

const Owning<Any> Set::firstObject() const
{
	if (size()) {
		const_iterator it = m_impl.cbegin();
		//std::advance<const_iterator>(it, 0);
		return (*it);
	}
	// Fault();
	return {};
}

const Owning<Any> Set::lastObject() const
{
	if (size()) {
		const_iterator it = m_impl.cbegin();
		std::advance<const_iterator>(it, static_cast<difference_type>(size() -1));
		return (*it);
	}
	// Fault();
	return {};
}

const Array Set::allObjects(CopyOption option) const
{ return Array(cbegin(), cend(), option); }

#pragma mark -

const Set Set::objectsPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func) const
{ return objectsPassingTest(func, EnumerationDefault); }

const Set Set::objectsPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func, EnumerationOptions options) const
{
	Array::impl_trait buf;
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
		
		bool stop = false, ret = false;
		
		switch (iter_option)
		{
			case IterationAscending:
			{
				for (const_iterator it = cbegin(); it != cend(); ++it) {
					if ((*it)) {
						ret = func((*it), stop);
						if (ret) { buf.push_back((*it)); }
						if (stop) { break; }
					}
				}
			}
			break;
			case IterationAsyncAscending:
			{
				auto op = runtime::async::exec(runtime::launch_async, [this, &buf, &stop, &ret, &func]
				{
					for (const_iterator it = cbegin(); it != cend(); ++it) {
						if ((*it)) {
							ret = func((*it), stop);
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
				auto op = runtime::async::exec(runtime::launch_async, [this, &buf, &stop, &ret, &func]
				{
					for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
						if ((*it)) {
							ret = func((*it), stop);
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
					if ((*it)) {
						ret = func((*it), stop);
						if (ret) { buf.push_back((*it)); }
						if (stop) { break; }
					}
				}
			}
			break;
			default:
				break;
		}
	}
	return Set(buf.cbegin(), buf.cend());
}

#pragma mark -

bool Set::everyObjectPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func) const
{
	bool stop = false, ret = false;
	if (size()) {
		auto op = runtime::async::exec(runtime::launch_any, [this, &stop, &ret, &func]
		{
			for (const_iterator it = cbegin(); it != cend(); ++it) {
				if ((*it)) {
					ret = func((*it), stop);
					if (!ret) { break; }
					if (stop) { break; }
				}
			}
		});
		op.get();
	}
	return ret;
}

bool Set::noneObjectPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func) const
{
	bool stop = false, ret = false;
	if (size()) {
		auto op = runtime::async::exec(runtime::launch_any, [this, &stop, &ret, &func]
		{
			for (const_iterator it = cbegin(); it != cend(); ++it) {
				if ((*it)) {
					ret = func((*it), stop);
					if (ret) { break; }
					if (stop) { break; }
				}
			}
		});
		op.get();
	}
	return !ret;
}

bool Set::someObjectPassingTest(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func) const
{
	bool stop = false, ret = false;
	if (size()) {
		auto op = runtime::async::exec(runtime::launch_any, [this, &stop, &ret, &func]
		{
			for (const_iterator it = cbegin(); it != cend(); ++it) {
				if ((*it)) {
					ret = func((*it), stop);
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

const Set Set::filteredSetUsingFunction(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func, CopyOption option) const
{ return filteredSetUsingFunction(func, option, EnumerationDefault); }

const Set Set::filteredSetUsingFunction(const std::function<bool(const Owning<Any> & obj, bool & stop)> & func, CopyOption option, EnumerationOptions options) const
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
	
	Array::impl_trait buf;
	bool stop = false, ret = false;
	
	switch (iter_option)
	{
		case IterationAscending:
		{
			for (const_iterator it = cbegin(); it != cend(); ++it) {
				if ((*it)) {
					ret = func((*it), stop);
					if (ret) { buf.push_back((*it)); }
					if (stop) { break; }
				}
			}
			return Set(buf.cbegin(), buf.cend(), option);
		}
		break;
		case IterationAsyncAscending:
		{
			auto op = runtime::async::exec(runtime::launch_async, [this, &buf, &stop, &ret, &func]
			{
				for (const_iterator it = cbegin(); it != cend(); ++it) {
					if ((*it)) {
						ret = func((*it), stop);
						if (ret) { buf.push_back((*it)); }
						if (stop) { break; }
					}
				}
			});
			op.get();
			return Set(buf.cbegin(), buf.cend(), option);
			
		}
		break;
		case IterationAsyncDescending:
		{
			auto op = runtime::async::exec(runtime::launch_async, [this, &buf, &stop, &ret, &func]
			{
				for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
					if ((*it)) {
						ret = func((*it), stop);
						if (ret) { buf.push_back((*it)); }
						if (stop) { break; }
					}
				}
			});
			op.get();
			return Set(buf.cbegin(), buf.cend(), option);
		}
		break;
		case IterationDescending:
		{
			for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
				if ((*it)) {
					ret = func((*it), stop);
					if (ret) { buf.push_back((*it)); }
					if (stop) { break; }
				}
			}
			return Set(buf.cbegin(), buf.cend(), option);
		}
		break;
		default:
			break;
	}
	return {};
}

#pragma mark -

const Set Set::setByAddingObject(Owning<Any> ptr, CopyOption option) const
{
	if (ptr) {
		impl_trait buf(cbegin(), cend());
		buf.insert(ptr);
		return Set(buf.cbegin(), buf.cend(), option);
	}
	// Fault();
	return {};
}

const Set Set::setByAddingObjectsFromSet(const Set & set, CopyOption option) const
{
	impl_trait buf(cbegin(), cend());
	for (Set::const_iterator it = set.cbegin(); it != set.cend(); ++it) {
		buf.insert((*it));
	}
	return Set(buf.cbegin(), buf.cend(), option);
}

const Set Set::setByAddingObjectsFromOrderedSet(const OrderedSet & set, CopyOption option) const
{
	impl_trait buf(cbegin(), cend());
	for (OrderedSet::const_iterator it = set.cbegin(); it != set.cend(); ++it) {
		buf.insert((*it));
	}
	return Set(buf.cbegin(), buf.cend(), option);
}

const Set Set::setByAddingObjectsFromArray(const Array & arr, CopyOption option) const
{
	impl_trait buf(cbegin(), cend());
	for (Array::const_iterator it = arr.cbegin(); it != arr.cend(); ++it) {
		buf.insert((*it));
	}
	return Set(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

Set::iterator Set::begin() { return m_impl.begin(); }
Set::iterator Set::end() { return m_impl.end(); }

Set::const_iterator Set::begin() const { return m_impl.begin(); }
Set::const_iterator Set::end() const { return m_impl.end(); }

Set::const_iterator Set::cbegin() const { return m_impl.cbegin(); }
Set::const_iterator Set::cend() const { return m_impl.cend(); }

Set::reverse_iterator Set::rbegin() { return m_impl.rbegin(); }
Set::reverse_iterator Set::rend() { return m_impl.rend(); }

Set::const_reverse_iterator Set::rbegin() const { return m_impl.rbegin(); }
Set::const_reverse_iterator Set::rend() const { return m_impl.rend(); }

Set::const_reverse_iterator Set::crbegin() const { return m_impl.crbegin(); }
Set::const_reverse_iterator Set::crend() const { return m_impl.crend(); }

/* EOF */