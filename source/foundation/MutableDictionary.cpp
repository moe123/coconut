//
// MutableDictionary.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/MutableDictionary.hpp>
#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/String.hpp>

using namespace coconut;

MutableDictionary::MutableDictionary() :
	Dictionary()
{ setClassKind(MutableDictionaryClass, true); }

MutableDictionary::MutableDictionary(const MutableDictionary & dict) :
	Dictionary(dict.cbegin(), dict.cend(), CopyNone)
{ setClassKind(MutableDictionaryClass, true); }

MutableDictionary::MutableDictionary(const MutableDictionary & dict, CopyOption option) :
	Dictionary(dict.cbegin(), dict.cend(), option)
{ setClassKind(MutableDictionaryClass, true); }

MutableDictionary::MutableDictionary(MutableDictionary && dict) noexcept :
	Dictionary(std::forward<Dictionary>(dict))
{ setClassKind(MutableDictionaryClass, true); }
		
MutableDictionary::MutableDictionary(const Dictionary & dict, CopyOption option) :
	Dictionary(dict.cbegin(), dict.cend(), option)
{ setClassKind(MutableDictionaryClass, true); }

MutableDictionary::MutableDictionary(Dictionary && dict) noexcept :
	Dictionary(std::forward<Dictionary>(dict))
{ setClassKind(MutableDictionaryClass, true); }
		
MutableDictionary::MutableDictionary(const std::initializer_list< std::pair< Owning<Any>, Owning<Any> > > & args) :
	Dictionary(args)
{ setClassKind(MutableDictionaryClass, true); }

MutableDictionary::MutableDictionary(const std::initializer_list< std::pair<Any *, Any *> > & args) :
	Dictionary(args)
{ setClassKind(MutableDictionaryClass, true); }
		
MutableDictionary::MutableDictionary(const Path & path) :
	Dictionary(path)
{ setClassKind(MutableDictionaryClass, true); }

MutableDictionary::MutableDictionary(const URL & url) :
	Dictionary(url)
{ setClassKind(MutableDictionaryClass, true); }

MutableDictionary::~MutableDictionary()
{ /* NOP */ }

#pragma mark -

void MutableDictionary::setValueForKey(Owning<Any> ptr, const std::string & utf8_key)
{
	if (ptr) {
		if (isAttributeKey(utf8_key)) {
			setAttributeForKey(ptr, utf8_key);
		} else if (isSelectorKey(utf8_key)) {
			// Fault();
		} else {
			setObject(ptr, utf8_key);
		}
	}
}

#pragma mark -

MutableDictionary & MutableDictionary::setDictionary(MutableDictionary && dict) noexcept
{ m_impl = std::move(dict.m_impl); return *this; }

MutableDictionary & MutableDictionary::setDictionary(Dictionary && dict) noexcept
{ m_impl = std::move(dict.m_impl); return *this; }

#pragma mark -

MutableDictionary & MutableDictionary::setObjectsFromDictionary(const Dictionary & dict)
{ setObjectsFromDictionary(dict, CopyNone); return *this; }

MutableDictionary & MutableDictionary::setObjectsFromDictionary(const Dictionary & dict, CopyOption option)
{
	m_impl.clear();
	for (const_iterator it = dict.cbegin(); it != dict.cend(); ++it) {
		setObject((*it).second, (*it).first, option);
	}
	return *this;
}

#pragma mark -

MutableDictionary & MutableDictionary::setObject(const Owning<Any> & obj, const std::string & utf8_key)
{ setObject(obj, utf8_key, CopyNone); return *this; }

MutableDictionary & MutableDictionary::setObject(const Owning<Any> & obj, const Any & key)
{ setObject(obj, key, CopyNone); return *this; }

MutableDictionary & MutableDictionary::setObject(const Owning<Any> & obj, Owning<Any> key)
{ setObject(obj, key, CopyNone); return *this; }

#pragma mark -

MutableDictionary & MutableDictionary::setObject(Owning<Any> obj, const std::string & utf8_key, CopyOption option)
{
	if (obj) {
		if (option != CopyNone) {
			Owning<Any> k = ptr_create<String>(utf8_key);
			Owning<Any> v = Object::copyObject(obj, option);
			m_impl[k] = v;
		} else {
			Owning<Any> k = ptr_create<String>(utf8_key);
			m_impl[k] = obj;
		}
	}
	return *this;
}

MutableDictionary & MutableDictionary::setObject(Owning<Any> obj, const Any & key, CopyOption option)
{
	if (obj) {
		if (option != CopyNone) {
			Owning<Any> k = key.kindCopy();
			Owning<Any> v = Object::copyObject(obj, option);
			m_impl[k] = v;
		} else {
			Owning<Any> k = key.kindCopy();
			m_impl[k] = obj;
		}
	}
	return *this;
}

MutableDictionary & MutableDictionary::setObject(Owning<Any> obj, Owning<Any> key, CopyOption option)
{
	if (obj && key) {
		if (option != CopyNone) {
			Owning<Any> k = Object::copyObject(key, option);
			Owning<Any> v = Object::copyObject(obj, option);
			m_impl[k] = v;
		} else {
			Owning<Any> k = key;
			m_impl[k] = obj;
		}
	}
	return *this;
}

#pragma mark -

Owning<Any> MutableDictionary::updateObject(const Owning<Any> & obj, const std::string & utf8_key)
{
	Owning<Any> old = objectForKey(utf8_key);
	setObject(obj, utf8_key);
	return old;
}

Owning<Any> MutableDictionary::updateObject(const Owning<Any> & obj, const Any & key)
{
	Owning<Any> old = objectForKey(key);
	setObject(obj, key);
	return old;
}

Owning<Any> MutableDictionary::updateObject(const Owning<Any> & obj, const Owning<Any> & key)
{
	Owning<Any> old = objectForKey(key);
	setObject(obj, key);
	return old;
}

Owning<Any> MutableDictionary::updateObject(const Owning<Any> & obj, const std::string & utf8_key, CopyOption option)
{
	Owning<Any> old = objectForKey(utf8_key);
	setObject(obj, utf8_key);
	return old;
}

Owning<Any> MutableDictionary::updateObject(const Owning<Any> & obj, const Any & key, CopyOption option)
{
	Owning<Any> old = objectForKey(key);
	setObject(obj, key, option);
	return old;
}

Owning<Any> MutableDictionary::updateObject(const Owning<Any> & obj, const Owning<Any> & key, CopyOption option)
{
	Owning<Any> old = objectForKey(key);
	setObject(obj, key, option);
	return old;
}

#pragma mark -

MutableDictionary & MutableDictionary::addEntriesFromDictionary(const Dictionary & dict)
{ addEntriesFromDictionary(dict, CopyNone); return *this; }

MutableDictionary & MutableDictionary::addEntriesFromDictionary(const Dictionary & dict, CopyOption option)
{
	for (const_iterator it = dict.cbegin(); it != dict.cend(); ++it) {
		setObject((*it).second, (*it).first, option);
	}
	return *this;
}

#pragma mark -

MutableDictionary & MutableDictionary::removeObjectForKey(const std::string & utf8_key)
{
	Owning<Any> k = ptr_create<String>(utf8_key);
	m_impl.erase(k);
	return *this;
}

MutableDictionary & MutableDictionary::removeObjectForKey(const Any & key)
{
	Owning<Any> k = key.kindCopy();
	m_impl.erase(k);
	return *this;
}

MutableDictionary & MutableDictionary::removeObjectForKey(const Owning<Any> & key)
{
	if (key) {
		Owning<Any> k = key;
		m_impl.erase(k);
	}
	return *this;
}

#pragma mark -

MutableDictionary & MutableDictionary::removeAllObjects()
{
	m_impl.clear();
	return *this;
}

#pragma mark -

MutableDictionary & MutableDictionary::removeObjectsForKeys(const Array & keys)
{
	for (Array::const_iterator it = keys.cbegin(); it != keys.cend(); ++it) {
		if ((*it)) { removeObjectForKey((*it)); }
	}
	return *this;
}

#pragma mark -

Owning<Any> & MutableDictionary::operator [] (const std::string & utf8_key)
{ return m_impl[ptr_create<String>(utf8_key)]; }

Owning<Any> & MutableDictionary::operator [] (const Any & key)
{ return m_impl[key.kindCopy()]; }

Owning<Any> & MutableDictionary::operator [] (const Owning<Any> & key)
{ return m_impl[key]; }

/* EOF */