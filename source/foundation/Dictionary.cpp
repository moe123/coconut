//
// Dictionary.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Dictionary.hpp>
#include <coconut/foundation/MutableDictionary.hpp>
#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/None.hpp>
#include <coconut/foundation/Number.hpp>
#include <coconut/foundation/Path.hpp>
#include <coconut/foundation/Set.hpp>
#include <coconut/foundation/String.hpp>
#include <coconut/foundation/URL.hpp>

using namespace coconut;

Dictionary::Dictionary() :
	Object(DictionaryClass),
	m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
	{ return (a->compare(*b) == OrderedAscending); })
{ /* NOP */ }

Dictionary::Dictionary(const Dictionary & dict) :
	Dictionary(dict.cbegin(), dict.cend(), CopyNone)
{ /* NOP */ }

Dictionary::Dictionary(const Dictionary & dict, CopyOption option) :
	Dictionary(dict.cbegin(), dict.cend(), option)
{ /* NOP */ }

Dictionary::Dictionary(Dictionary && dict) :
	Object(DictionaryClass),
	m_impl(std::move(dict.m_impl))
{ /* NOP */ }

Dictionary::Dictionary(const std::initializer_list< std::pair< Owning<Any>, Owning<Any> > > & args) :
	Dictionary(args.begin(), args.end(), CopyNone)
{ /* NOP */ }

Dictionary::Dictionary(const std::initializer_list< std::pair<Any *, Any *> > & args) :
	Object(DictionaryClass),
	m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
	{ return (a->compare(*b) == OrderedAscending); })
{
	for (const std::pair<Any *, Any *> & pair : args) {
		if (dynamic_cast<Any *>(pair.first) != nullptr && dynamic_cast<Any *>(pair.second) != nullptr) { m_impl.insert(std::make_pair(pair.first->kindCopy(), pair.second->kindCopy())); }
	}
}

Dictionary::Dictionary(const Path & path) :
	Object(DictionaryClass),
	m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
	{ return (a->compare(*b) == OrderedAscending); })
{ /* TODO SERIALIZATION */ }

Dictionary::Dictionary(const URL & url) :
	Object(DictionaryClass),
	m_impl([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
	{ return (a->compare(*b) == OrderedAscending); })
{ /* TODO SERIALIZATION */ }

Dictionary::~Dictionary()
{ /* NOP */ }

#pragma mark -

std::size_t Dictionary::hash() const
{
	std::size_t seed = 0;
	std::size_t tau = sizeof(std::size_t) >= 8 ? 0x278DDE6E5FD29E00ULL : 0x9E3779B9UL;
	const_iterator it = cbegin();
	while (it != cend()) {
		if ((*it).first && (*it).second) {
			seed ^= ((*it).first)->hash() + tau + (seed << 6) + (seed >> 2);
			seed ^= ((*it).second)->hash() + tau + (seed << 6) + (seed >> 2);
		}
		++it;
	}
	return seed;
}

#pragma mark -

Owning<Any> Dictionary::copy() const
{ return ptr_create<Dictionary>(cbegin(), cend(), CopyKind); }

Owning<Any> Dictionary::mutableCopy() const
{ return ptr_create<MutableDictionary>(cbegin(), cend(), CopyKind); }

#pragma mark -

ComparisonResult Dictionary::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (size() < ref_cast<Dictionary>(ref).size()) {
			return OrderedAscending;
		} else if (size() > ref_cast<Dictionary>(ref).size()) {
			return OrderedDescending;
		} else if (
			std::equal(cbegin(), cend(), ref_cast<Dictionary>(ref).cbegin(), [] (const std::pair< Owning<Any>, Owning<Any> > & a, const std::pair< Owning<Any>, Owning<Any> > & b) -> bool
			{
				if (a.first && a.second && b.first && b.second) {
					if (((a.first)->compare(*(b.first)) == OrderedSame)) {
						return ((a.second)->compare(*(b.second)) == OrderedSame);
					}
				}
				return false;
			})
		) {
			return OrderedSame;
		}
	}
	return OrderedDescending;
}

bool Dictionary::doesContain(const Any & ref) const
{ return containsKey(ref); }

#pragma mark -

std::string Dictionary::stringValue() const
{ return description(); }

#pragma mark -

std::size_t Dictionary::size() const
{ return m_impl.size(); }

#pragma mark -

Owning<Any> Dictionary::valueForKey(const std::string & utf8_key) const
{
	if(isSelectorKey(utf8_key)) {
		return Object::valueForSelectorKey(utf8_key);
	} else if(isAttributeKey(utf8_key)) {
		return Object::valueForKey(utf8_key);
	}
	
	return objectForKey(utf8_key);
}

#pragma mark -

const Array Dictionary::makeKeysPerformSelectorKey(const std::string & utf8_selkey, Owning<Any> arg) const
{
	Array::impl_trait buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		Owning<Any> k = (*it).first;
		Owning<Any> v;
		if (k) {
			v = k->valueForSelectorKey(utf8_selkey, arg);
		}
		if (!v) { v = ptr_create<None>(); }
		buf.push_back(v);
	}
	return Array(buf.cbegin(), buf.cend());
}

#pragma mark -

void Dictionary::enumerateKeysAndObjectsUsingFunction(const std::function<void(const Owning<Any> & key, const Owning<Any> & obj, bool & stop)> & func) const
{ enumerateKeysAndObjectsUsingFunction(func, EnumerationDefault); }

void Dictionary::enumerateKeysAndObjectsUsingFunction(const std::function<void(const Owning<Any> & key, const Owning<Any> & obj, bool & stop)> & func, EnumerationOptions options) const
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
					if ((*it).first && (*it).second) {
						func((*it).first, (*it).second, stop);
						if (stop) { break; }
					} else {
						// Fault();
					}
				}
			}
			break;
			case IterationAsyncAscending:
			{
				auto op = runtime::async::exec(runtime::launch_async, [this, &stop, &func]
				{
					for (const_iterator it = cbegin(); it != cend(); ++it) {
						if ((*it).first && (*it).second) {
							func((*it).first, (*it).second, stop);
							if (stop) { break; }
						} else {
							// Fault();
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
						if ((*it).first && (*it).second) {
							func((*it).first, (*it).second, stop);
							if (stop) { break; }
						} else {
							// Fault();
						}
					}
				});
				op.get();
			}
			break;
			case IterationDescending:
			{
				for (const_reverse_iterator it = crbegin(); it != crend(); ++it) {
					if ((*it).first && (*it).second) {
						func((*it).first, (*it).second, stop);
						if (stop) { break; }
					} else {
						// Fault();
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

bool Dictionary::containsKey(const std::string & utf8_key) const
{ return containsKey(String(utf8_key)); }

bool Dictionary::containsKey(const Any & key) const
{
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it).first && (*it).second) {
			if((*it).first->compare(key) == OrderedSame) {
				return true;
			}
		} else {
			// Fault();
		}
	}
	return false;
}

bool Dictionary::containsKey(const Owning<Any> & key) const
{ if (key) { return containsKey(*key); } return false; }

#pragma mark -

const Owning<Any> Dictionary::objectForKey(const std::string & utf8_key) const
{ return objectForKey(String(utf8_key)); }

const Owning<Any> Dictionary::objectForKey(const Any & key) const
{
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it).first && (*it).second) {
			if((*it).first->compare(key) == OrderedSame) {
				return (*it).second;
			}
		} else {
			// Fault();
		}
	}
	// Fault();
	return {};
}

const Owning<Any> Dictionary::objectForKey(const Owning<Any> & key) const
{ if (key) { return objectForKey(*key); } return {}; }

#pragma mark -

const Owning<Any> Dictionary::objectForCaseInsensitiveKey(const std::string & utf8_key) const
{
	return objectForCaseInsensitiveKey(String(utf8_key));
}

const Owning<Any> Dictionary::objectForCaseInsensitiveKey(const Any & key) const
{
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it).first && (*it).second) {
			if((*it).first->isKindOf(StringClass) && key.isKindOf(StringClass)) {
				if(ref_cast<String>(*((*it).first)).caseInsensitiveCompare(ref_cast<String>(key)) == OrderedSame) {
					return (*it).second;
				}
			} else {
				if((*it).first->compare(key) == OrderedSame) {
					return (*it).second;
				}
			}
		} else {
			// Fault();
		}
	}
	// Fault();
	return {};
}

const Owning<Any> Dictionary::objectForCaseInsensitiveKey(const Owning<Any> & key) const
{ if (key) { return objectForCaseInsensitiveKey(*key); } return {}; }

#pragma mark -

const Array Dictionary::objectsForKeys(const Array & keys, Owning<Any> notFoundMarker) const
{
	Array::impl_trait buf;
	for (Array::const_iterator it = keys.cbegin(); it != keys.cend(); ++it) {
		if ((*it)) {
			Owning<Any> v;
			if (!(v = objectForKey(*(*it)))) {
				if (notFoundMarker) { v = notFoundMarker; } else { v = ptr_create<None>(); }
			}
			buf.push_back(v);
		} else {
			// Fault();
		}
	}
	return Array(buf.cbegin(), buf.cend());
}

#pragma mark -

const Array Dictionary::objectsForKeys(const Set & keys, Owning<Any> notFoundMarker) const
{
	Array::impl_trait buf;
	for (Set::const_iterator it = keys.cbegin(); it != keys.cend(); ++it) {
		if ((*it)) {
			Owning<Any> v;
			if (!(v = objectForKey(*(*it)))) {
				if (notFoundMarker) { v = notFoundMarker; } else { v = ptr_create<None>(); }
			}
			buf.push_back(v);
		} else {
			// Fault();
		}
	}
	return Array(buf.cbegin(), buf.cend());
}

#pragma mark -

const Array Dictionary::allKeys(CopyOption option) const
{
	Array::impl_trait buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it).first) {
			buf.push_back((*it).first);
		} else {
			// Fault();
		}
	}
	return Array(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

const Array Dictionary::allKeysForObject(const Any & obj, CopyOption option) const
{
	Array::impl_trait buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it).first && (*it).second) {
			if ((*it).second->isEqual(obj)) { buf.push_back((*it).first); }
		} else {
			// Fault();
		}
	}
	return Array(buf.cbegin(), buf.cend(), option);
}

const Array Dictionary::allKeysForObject(const Owning<Any> & obj, CopyOption option) const
{ if (obj) { return allKeysForObject(*obj, option); } return {}; }

#pragma mark -

const Array Dictionary::allValues(CopyOption option) const
{
	Array::impl_trait buf;
	for (const_iterator it = cbegin(); it != cend(); ++it) {
		if ((*it).second) {
			buf.push_back((*it).second);
		} else {
			// Fault();
		}
	}
	return Array(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

const Array Dictionary::keysSortedByValueUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, CopyOption option) const
{
	Array::impl_trait buf;
	Array values = allValues().sortedArrayUsingFunction(func);
	for (Array::const_iterator it0 = values.cbegin(); it0 != values.cend(); ++it0) {
		Array items = allKeysForObject(*(*it0));
		for (Array::const_iterator it1 = items.cbegin(); it1 != items.cend(); ++it1) {
			buf.push_back((*it1));
		}
	}
	return Array(buf.cbegin(), buf.cend(), option);
}

const Array Dictionary::keysSortedByValueAscending(CopyOption option) const
{
	return keysSortedByValueUsingFunction([] (const Owning<Any> & a, const Owning<Any> & b) -> bool
	{
		if (a && b) { return (a->compare(*b) == OrderedAscending); } return false;
	}, option);
}

const Array Dictionary::keysSortedByValueDescending(CopyOption option) const
{
	return keysSortedByValueUsingFunction([] (const Owning<Any> & a, const Owning<Any> & b)
	{
		if (a && b) { return (a->compare(*b) == OrderedDescending); } return false;
	}, option);
}

#pragma mark -

const Array Dictionary::keysSortedUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, CopyOption option) const
{ return allKeys().sortedArrayUsingFunction(func, option, SortConcurrent|SortDefault); }

const Array Dictionary::keysSortedUsingFunction(const std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> & func, CopyOption option, SortOptions options) const
{ return allKeys().sortedArrayUsingFunction(func, option, options); }

#pragma mark -

const Array Dictionary::keysSortedAscending(CopyOption option) const
{ return allKeys().sortedArrayAscending(option, SortConcurrent|SortDefault); }

const Array Dictionary::keysSortedAscending(CopyOption option, SortOptions options) const
{ return allKeys().sortedArrayAscending(option, options); }

#pragma mark -

const Array Dictionary::keysSortedDescending(CopyOption option) const
{ return allKeys().sortedArrayDescending(option, SortConcurrent|SortDefault); }

const Array Dictionary::keysSortedDescending(CopyOption option, SortOptions options) const
{ return allKeys().sortedArrayDescending(option, options); }

#pragma mark -

const Array Dictionary::keysSortedUsingSelectorKey(const std::string & utf8_selkey, CopyOption option) const
{ return allKeys().sortedArrayUsingSelectorKey(utf8_selkey, option, false, SortConcurrent|SortDefault); }

const Array Dictionary::keysSortedUsingSelectorKey(const std::string & utf8_selkey, CopyOption option, bool descending) const
{ return allKeys().sortedArrayUsingSelectorKey(utf8_selkey, option, descending, SortConcurrent|SortDefault); }

const Array Dictionary::keysSortedUsingSelectorKey(const std::string & utf8_selkey, CopyOption option, bool descending, SortOptions options) const
{ return allKeys().sortedArrayUsingSelectorKey(utf8_selkey, option, descending, options); }

#pragma mark -

const Array Dictionary::keysSortedUsingDescriptor(const SortDescriptor & descriptor, CopyOption option) const
{ return allKeys().sortedArrayUsingDescriptor(descriptor, option, SortConcurrent|SortStable); }

const Array Dictionary::keysSortedUsingDescriptor(const SortDescriptor & descriptor, CopyOption option, SortOptions options) const
{ return allKeys().sortedArrayUsingDescriptor(descriptor, option, options); }

#pragma mark -

const Array Dictionary::keysSortedUsingDescriptors(const Array & descriptors, CopyOption option) const
{ return allKeys().sortedArrayUsingDescriptors(descriptors, option, SortConcurrent|SortStable); }

const Array Dictionary::keysSortedUsingDescriptors(const Array & descriptors, CopyOption option, SortOptions options) const
{ return allKeys().sortedArrayUsingDescriptors(descriptors, option, options); }

#pragma mark -

const Set Dictionary::keysOfEntriesPassingTest(const std::function<bool(const Owning<Any> & key, bool & stop)> & func, CopyOption option) const
{
	Set::impl_trait buf;
	if (size()) {
		bool stop = false, ret = false;
		auto op = runtime::async::exec(runtime::launch_any, [this, &buf, &stop, &ret, &func]
		{
			for (const_iterator it = cbegin(); it != cend(); ++it) {
				if ((*it).first && (*it).second) {
					ret = func((*it).second, stop);
					if (ret) { buf.insert((*it).second); }
					if (stop) { break; }
				}
			}
		});
		op.get();
	}
	return Set(buf.cbegin(), buf.cend(), option);
}

#pragma mark -

bool Dictionary::writeToFile(const Path & path, bool atomically) const
{
	return false;
}

bool Dictionary::writeToURL(const URL & url, bool atomically) const
{
	return false;
}

#pragma mark -

const Owning<Any> Dictionary::operator [] (const std::string & utf8_key) const
{ return objectForKey(String(utf8_key)); }

const Owning<Any> Dictionary::operator [] (const Any & key) const
{ return objectForKey(key); }

const Owning<Any> Dictionary::operator [] (const Owning<Any> & key) const
{ return objectForKey(key); }

#pragma mark -

Dictionary::iterator Dictionary::begin() { return m_impl.begin(); }
Dictionary::iterator Dictionary::end() { return m_impl.end(); }

Dictionary::const_iterator Dictionary::begin() const { return m_impl.begin(); }
Dictionary::const_iterator Dictionary::end() const { return m_impl.end(); }

Dictionary::const_iterator Dictionary::cbegin() const { return m_impl.cbegin(); }
Dictionary::const_iterator Dictionary::cend() const { return m_impl.cend(); }

Dictionary::reverse_iterator Dictionary::rbegin() { return m_impl.rbegin(); }
Dictionary::reverse_iterator Dictionary::rend() { return m_impl.rend(); }

Dictionary::const_reverse_iterator Dictionary::rbegin() const { return m_impl.rbegin(); }
Dictionary::const_reverse_iterator Dictionary::rend() const { return m_impl.rend(); }

Dictionary::const_reverse_iterator Dictionary::crbegin() const { return m_impl.crbegin(); }
Dictionary::const_reverse_iterator Dictionary::crend() const { return m_impl.crend(); }

/* EOF */