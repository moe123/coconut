//
// MutableDictionary.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
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

MutableDictionary::MutableDictionary(MutableDictionary && dict) :
	Dictionary(std::forward<Dictionary>(dict))
{ setClassKind(MutableDictionaryClass, true); }
		
MutableDictionary::MutableDictionary(const Dictionary & dict, CopyOption option) :
	Dictionary(dict.cbegin(), dict.cend(), option)
{ setClassKind(MutableDictionaryClass, true); }

MutableDictionary::MutableDictionary(Dictionary && dict) :
	Dictionary(std::forward<Dictionary>(dict))
{ setClassKind(MutableDictionaryClass, true); }
		
MutableDictionary::MutableDictionary(const std::initializer_list< std::pair<kind_ptr, kind_ptr> > & args) :
	Dictionary(args)
{ setClassKind(MutableDictionaryClass, true); }

MutableDictionary::MutableDictionary(const std::initializer_list< std::pair<kind_raw_ptr, kind_raw_ptr> > & args) :
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
		
MutableDictionaryPtr MutableDictionary::with()
{ return ptr_create<MutableDictionary>(); }

MutableDictionaryPtr MutableDictionary::with(const MutableDictionary & dict)
{ return ptr_create<MutableDictionary>(dict); }

MutableDictionaryPtr MutableDictionary::with(const MutableDictionary & dict, CopyOption option)
{ return ptr_create<MutableDictionary>(dict, option); }

MutableDictionaryPtr MutableDictionary::with(MutableDictionary && dict)
{ return ptr_create<MutableDictionary>(std::move(dict)); }

MutableDictionaryPtr MutableDictionary::with(const Dictionary & dict, CopyOption option)
{ return ptr_create<MutableDictionary>(dict, option); }

MutableDictionaryPtr MutableDictionary::with(Dictionary && dict)
{ return ptr_create<MutableDictionary>(std::move(dict)); }

MutableDictionaryPtr MutableDictionary::with(const std::initializer_list< std::pair<kind_ptr, kind_ptr> > & args)
{ return ptr_create<MutableDictionary>(args); }

MutableDictionaryPtr MutableDictionary::with(const std::initializer_list< std::pair<kind_raw_ptr, kind_raw_ptr> > & args)
{ return ptr_create<MutableDictionary>(args); }

MutableDictionaryPtr MutableDictionary::with(const Path & path)
{ return ptr_create<MutableDictionary>(path); }

MutableDictionaryPtr MutableDictionary::with(const URL & url)
{ return ptr_create<MutableDictionary>(url); }

#pragma mark -

void MutableDictionary::setValueForKey(kind_ptr ptr, const std::string & utf8_key)
{
	if (ptr) {
		if (isAttributeKey(utf8_key)) {
			setAttributeForKey(ptr, utf8_key);
		} else if(isSelectorKey(utf8_key)) {
			// Fault();
		} else {
			setObject(ptr, utf8_key);
		}
	}
}

#pragma mark -

void MutableDictionary::setDictionary(MutableDictionary && dict)
{ m_impl = std::move(dict.m_impl); }

void MutableDictionary::setDictionary(Dictionary && dict)
{ m_impl = std::move(dict.m_impl); }

#pragma mark -

void MutableDictionary::setObjectsFromDictionary(const Dictionary & dict)
{
	setObjectsFromDictionary(dict, CopyNone);
}

void MutableDictionary::setObjectsFromDictionary(const Dictionary & dict, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	m_impl.clear();
	for (const_iterator it = dict.cbegin(); it != dict.cend(); ++it) {
		setObject((*it).second, (*it).first, option);
	}
}

#pragma mark -

void MutableDictionary::setObject(kind_ptr ptr, const std::string & utf8_key)
{
	setObject(ptr, utf8_key, CopyNone);
}

void MutableDictionary::setObject(kind_ptr ptr, const_kind_ref key)
{
	setObject(ptr, key, CopyNone);
}

void MutableDictionary::setObject(kind_ptr ptr, const_kind_ptr & key)
{
	setObject(ptr, key, CopyNone);
}

#pragma mark -

void MutableDictionary::setObject(kind_ptr ptr, const std::string & utf8_key, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	if (ptr) {
		if (option != CopyNone) {
			kind_ptr k = String::with(utf8_key);
			kind_ptr v = Object::copyObject(ptr, option);
			m_impl[k] = v;
		} else {
			kind_ptr k = String::with(utf8_key);
			m_impl[k] = ptr;
		}
	}
}

void MutableDictionary::setObject(kind_ptr ptr, const_kind_ref key, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	if (ptr) {
		if (option != CopyNone) {
			kind_ptr k = key.kindCopy();
			kind_ptr v = Object::copyObject(ptr, option);
			m_impl[k] = v;
		} else {
			kind_ptr k = key.kindCopy();
			m_impl[k] = ptr;
		}
	}
}

void MutableDictionary::setObject(kind_ptr ptr, const_kind_ptr & key, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	if (ptr && key) {
		if (option != CopyNone) {
			kind_ptr k = Object::copyObject(key, option);
			kind_ptr v = Object::copyObject(ptr, option);
			m_impl[k] = v;
		} else {
			kind_ptr k = key;
			m_impl[k] = ptr;
		}
	}
}

#pragma mark -

void MutableDictionary::addEntriesFromDictionary(const Dictionary & dict)
{
	addEntriesFromDictionary(dict, CopyNone);
}

void MutableDictionary::addEntriesFromDictionary(const Dictionary & dict, CopyOption option)
{
	std::lock_guard<spin_type> lck(spin());
	for (const_iterator it = dict.cbegin(); it != dict.cend(); ++it) {
		setObject((*it).second, (*it).first, option);
	}
}

#pragma mark -

void MutableDictionary::removeObjectForKey(const std::string & utf8_key)
{
	std::lock_guard<spin_type> lck(spin());
	kind_ptr k = String::with(utf8_key);
	m_impl.erase(k);
}

void MutableDictionary::removeObjectForKey(const_kind_ref key)
{
	std::lock_guard<spin_type> lck(spin());
	kind_ptr k = key.kindCopy();
	m_impl.erase(k);
}

void MutableDictionary::removeObjectForKey(const_kind_ptr & key)
{
	std::lock_guard<spin_type> lck(spin());
	if (key) {
		kind_ptr k = key;
		m_impl.erase(k);
	}
}

#pragma mark -

void MutableDictionary::removeAllObjects()
{
	std::lock_guard<spin_type> lck(spin());
	m_impl.clear();
}

#pragma mark -

void MutableDictionary::removeObjectsForKeys(const Array & keys)
{
	std::lock_guard<spin_type> lck(spin());
	for (Array::const_iterator it = keys.cbegin(); it != keys.cend(); ++it) {
		if ((*it)) { removeObjectForKey((*it)); }
	}
}

#pragma mark -

kind_ptr & MutableDictionary::operator [] (const std::string & utf8_key)
{ return m_impl[String::with(utf8_key)]; }

kind_ptr & MutableDictionary::operator [] (const_kind_ref key)
{ return m_impl[key.kindCopy()]; }

kind_ptr & MutableDictionary::operator [] (const_kind_ptr & key)
{ return m_impl[key]; }

/* EOF */