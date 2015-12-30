//
// nucleus.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/nucleus.hpp>
#include <coconut/runtime/detail/zombie.hpp>

#include <coconut/runtime/detail/core/algorithm.hpp>
#include <coconut/runtime/detail/core/async.hpp>
#include <coconut/runtime/detail/core/unicode.hpp>

using namespace coconut::runtime;

nucleus::nucleus() :
	m_attrs(),
	m_kinds(),
	m_addr("0x00"),
	m_kind(classkind_anon),
	m_tag(-1000LL),
	m_ismutable(false),
	m_spinlock()
{ /* NOP */ }

nucleus::nucleus(const nucleus & ref) :
	m_attrs(),
	m_kinds(),
	m_addr("0x00"),
	m_kind(classkind_anon),
	m_tag(-1000LL),
	m_ismutable(false),
	m_spinlock()
{ COCONUT_UNUSED(ref); }

nucleus & nucleus::operator = (const nucleus & ref)
{ COCONUT_UNUSED(ref); return *this; }

nucleus::nucleus(ClassKind root, ClassKind kind) :
	m_attrs(),
	m_kinds(),
	m_addr(),
	m_kind(kind),
	m_tag(-1000LL),
	m_ismutable(false),
	m_spinlock()
{
	m_kinds.push_back(classkind_nucleus);
	m_kinds.push_back(root);
	if (m_kind != classkind_nucleus && m_kind != root) {
		m_kinds.push_back(m_kind);
	}
	std::stringstream ss; ss << std::hex << std::showbase << this;
	m_addr.assign(ss.str());
}

nucleus::~nucleus()
{ m_attrs.clear(); m_kinds.clear(); }

#pragma mark -

bool nucleus::isSelectorKey(const std::string & utf8_in)
{
	if (algorithm::starts_with<std::string>(utf8_in, u8"@") && !algorithm::starts_with<std::string>(utf8_in, u8"@@")) {
		return true;
	}
	return false;
}

bool nucleus::isAttributeKey(const std::string & utf8_attrkey)
{
	if (algorithm::starts_with<std::string>(utf8_attrkey, u8"$") && !algorithm::starts_with<std::string>(utf8_attrkey, u8"$$")) {
		return true;
	}
	return false;
}

#pragma mark -

bool nucleus::respondsToSelectorKey(const std::string & utf8_selkey) const
{
	if (isSelectorKey(utf8_selkey)) {
		Owning<Any> ptr;
		if (runtime::algorithm::ends_with<std::string>(utf8_selkey, u8":")) {
			ptr = valueForSelectorKey(utf8_selkey, ptr_create<zombie>());
		} else {
			ptr = valueForSelectorKey(utf8_selkey);
		}
		if (ptr) { return true; }
	}
	return false;
}

void nucleus::performSelectorKeyAfterDelay(uint64_t microseconds, bool wait, const std::string & utf8_selkey, Owning<Any> arg) const
{
	if (isSelectorKey(utf8_selkey)) {
		if (wait) {
			auto op = runtime::async::exec(runtime::launch_async, [this, &microseconds, &utf8_selkey, &arg]
			{
				if (microseconds) { std::this_thread::sleep_for(std::chrono::microseconds(microseconds)); }
				valueForSelectorKey(utf8_selkey, arg);
			});
			op.get();
		} else {
			runtime::async::detach([this, microseconds, utf8_selkey, arg]
			{
				if (microseconds) { std::this_thread::sleep_for(std::chrono::microseconds(microseconds)); }
				valueForSelectorKey(utf8_selkey, arg);
			});
		}
	}
}

void nucleus::performSelectorKeyInBackground(const std::string & utf8_selkey, Owning<Any> arg) const
{
	performSelectorKeyAfterDelay(0, false, utf8_selkey, arg);
}

Owning<Any> nucleus::performSelectorKey(const std::string & utf8_selkey, Owning<Any> arg) const
{
	if (isSelectorKey(utf8_selkey)) {
		auto op = runtime::async::exec(runtime::launch_any, [this, &utf8_selkey, &arg]
		{ return valueForSelectorKey(utf8_selkey, arg); });
		return op.get();
	}
	// Fault();
	return {};
}

#pragma mark -

void nucleus::setClassKind(ClassKind kind, bool ismutable)
{
	if (m_kind != kind) {
		m_kind = kind;
		m_kinds.push_back(m_kind);
	}
	m_ismutable = ismutable;
}

ClassKind nucleus::classKind() const
{
	return m_kind;
}

ClassKind nucleus::parentClassKind() const
{
	std::size_t n = m_kinds.size();
	return n > 1 ? m_kinds[n - 2] : m_kind;
}

#pragma mark -

void nucleus::conveyAttributesFrom(const Any & ref)
{ m_attrs.insert(ref.m_attrs.cbegin(), ref.m_attrs.cend()); }

void nucleus::removeAllAttributes()
{ m_attrs.clear();}

bool nucleus::setAttributeForKey(Owning<Any> ptr, const std::string & utf8_attrkey)
{ if (ptr) { m_attrs[utf8_attrkey] = ptr; return true; } return false; }

bool nucleus::removeAttributeForKey(const std::string & utf8_attrkey)
{ if (m_attrs.size() != 0 && m_attrs.count(utf8_attrkey) != 0) { m_attrs.erase(utf8_attrkey); return true; } return false; }

bool nucleus::hasAttributeForKey(const std::string & utf8_attrkey) const
{ return (m_attrs.size() != 0 && m_attrs.count(utf8_attrkey) != 0); }

Owning<Any> nucleus::attributeForKey(const std::string & utf8_attrkey) const
{ if (m_attrs.count(utf8_attrkey) != 0) { return m_attrs.at(utf8_attrkey); } return {}; }

#pragma mark -

void nucleus::setTag(std::int64_t tag)
{ m_tag = tag; }

std::int64_t nucleus::tag() const
{ return m_tag; }

#pragma mark -

const std::string nucleus::className() const
{
	return class_name();
}

const std::string nucleus::classTree() const
{
	return class_tree();
}

#pragma mark -

const Any * nucleus::itself() const { return this; }

#pragma mark -

std::size_t nucleus::hash() const
{
	return unsafe_cast<std::size_t>(sig());
}

#pragma mark -

bool nucleus::isKindOf(ClassKind kind) const
{
	return !(std::find(m_kinds.begin(), m_kinds.end(), kind) == m_kinds.end());
}

bool nucleus::isKindOf(const Any & ref, const Any & other_ref) const
{
	return (ref.isKindOf(other_ref.classKind()));
}

bool nucleus::isKindOf(const Owning<Any> & ptr, const Owning<Any> & other_ptr) const
{
	if (ptr && other_ptr) {
		return isKindOf(*ptr, *other_ptr);
	}
	return false;
}

bool nucleus::isKindOf(const Any & ref) const
{
	return isKindOf(ref.classKind());
}

bool nucleus::isKindOf(const Owning<Any> & ptr) const
{
	if (ptr) {
		return isKindOf(*ptr);
	}
	return false;
}

#pragma mark -

bool nucleus::isSubclassOf(ClassKind kind) const
{
	return (parentClassKind() == kind);
}

bool nucleus::isSubclassOf(const Any & ref, const Any & other_ref) const
{
	return (ref.isSubclassOf(other_ref.classKind()));
}

bool nucleus::isSubclassOf(const Owning<Any> & ptr, const Owning<Any> & other_ptr) const
{
	if (ptr && other_ptr) {
		return isSubclassOf(*ptr, *other_ptr);
	}
	return false;
}

bool nucleus::isSubclassOf(const Any & ref) const
{
	return isSubclassOf(ref.classKind());
}

bool nucleus::isSubclassOf(const Owning<Any> & ptr) const
{
	if (ptr) {
		return isSubclassOf(*ptr);
	}
	return false;
}

#pragma mark -

bool nucleus::isMemberOf(ClassKind kind) const
{
	return (m_kind == kind);
}

bool nucleus::isMemberOf(const Any & ref, const Any & other_ref) const
{
	return (ref.classKind() == other_ref.classKind());
}

bool nucleus::isMemberOf(const Owning<Any> & ptr, const Owning<Any> & other_ptr) const
{
	if (ptr && other_ptr) {
		return isMemberOf(*ptr, *other_ptr);
	}
	return false;
}

bool nucleus::isMemberOf(const Any & ref) const
{
	return (m_kind == ref.classKind());
}

bool nucleus::isMemberOf(const Owning<Any> & ptr) const
{
	if (ptr) {
		return isMemberOf(*ptr);
	}
	return false;
}

#pragma mark -

bool nucleus::isAncestorOf(const Any & ref) const
{
	return ref.isKindOf(*this);
}

bool nucleus::isAncestorOf(const Owning<Any> & ptr) const
{
	if (ptr) {
		return isAncestorOf(*ptr);
	}
	return false;
}

#pragma mark -

bool nucleus::isParentOf(const Any & ref) const
{
	return (ref.parentClassKind() == classKind());
}

bool nucleus::isParentOf(const Owning<Any> & ptr) const
{
	if (ptr) {
		return isParentOf(*ptr);
	}
	return false;
}

#pragma mark -

Owning<Any> nucleus::copy() const { return {}; }
Owning<Any> nucleus::mutableCopy() const { return copy(); }

Owning<Any> nucleus::kindCopy() const
{ return m_ismutable ? mutableCopy() : copy(); }

#pragma mark -

Owning<Any> nucleus::valueForKey(const std::string & utf8_key) const
{
	Owning<Any> v;
	if (isSelectorKey(utf8_key)) {
		v = valueForSelectorKey(utf8_key, nullptr);
	} else if (isAttributeKey(utf8_key)) {
		v = attributeForKey(utf8_key);
	}
	return v;
}

void nucleus::setValueForKey(Owning<Any> ptr, const std::string & utf8_key)
{
	if (ptr && isAttributeKey(utf8_key)) {
		setAttributeForKey(ptr, utf8_key);
	}
}

#pragma mark -

Owning<Any> nucleus::valueForKeyPath(const std::string & utf8_keypath) const
{
	Owning<Any> v;
	std::vector<std::string> parts;
	parts = algorithm::split<std::string>(utf8_keypath, u8".");
	if (parts.size() >= 2) {
		Owning<Any> vv = valueForKey(parts[0]);
		if (vv) {
			parts.erase(parts.begin());
			if (parts.size() >= 2) {
				v = vv->valueForKeyPath(algorithm::join<std::string>(parts, u8"."));
			} else if (parts.size() == 1) {
				v = vv->valueForKey(parts[0]);
			}
		}
	} else {
		v = valueForKey(utf8_keypath);
	}
	return v;
}

void nucleus::setValueForKeyPath(Owning<Any> ptr, const std::string & utf8_keypath)
{
	if (ptr) {
		std::vector<std::string> parts;
		parts = algorithm::split<std::string>(utf8_keypath, u8".");
		if (parts.size() >= 2) {
			Owning<Any> vv = valueForKey(parts[0]);
			if (vv) {
				parts.erase(parts.begin());
				if (parts.size() >= 2) {
					vv->setValueForKeyPath(ptr, algorithm::join<std::string>(parts, u8"."));
				} else if (parts.size() == 1) {
					vv->setValueForKey(ptr, parts[0]);
				}
			}
		} else {
			setValueForKey(ptr, utf8_keypath);
		}
	}
}

#pragma mark -

Owning<Any> nucleus::valueForSelectorKey(const std::string & utf8_selkey, Owning<Any> arg) const
{ COCONUT_UNUSED(utf8_selkey); COCONUT_UNUSED(arg); return {}; }

#pragma mark -

Owning<Any> nucleus::valueForKey(const Any & key) const
{ return valueForKeyPath(key.stringValue()); }

Owning<Any> nucleus::valueForKey(const Owning<Any> & key) const
{ if (key) { return valueForKeyPath(key->stringValue()); } return {}; }

void nucleus::setValueForKey(Owning<Any> ptr, const Any & key)
{ setValueForKey(ptr, key.stringValue()); }

void nucleus::setValueForKey(Owning<Any> ptr, const Owning<Any> & key)
{ if (key) { setValueForKey(ptr, key->stringValue()); } }

#pragma mark -

Owning<Any> nucleus::valueForKeyPath(const Any & keypath) const
{ return valueForKeyPath(keypath.stringValue()); }

Owning<Any> nucleus::valueForKeyPath(const Owning<Any> & keypath) const
{ if (keypath) { return valueForKeyPath(keypath->stringValue()); } return {}; }

void nucleus::setValueForKeyPath(Owning<Any> ptr, const Any & keypath)
{ setValueForKeyPath(ptr, keypath.stringValue()); }

void nucleus::setValueForKeyPath(Owning<Any> ptr, const Owning<Any> & keypath)
{ if (keypath) { setValueForKeyPath(ptr, keypath->stringValue()); } }

#pragma mark -

Owning<Any> nucleus::valueForSelectorKey(const Any & selkey, Owning<Any> arg) const
{ return valueForSelectorKey(selkey.stringValue(), arg); }

Owning<Any> nucleus::valueForSelectorKey(const Owning<Any> & selkey, Owning<Any> arg) const
{ if (selkey) { return valueForSelectorKey(selkey->stringValue(), arg); } return {}; }

#pragma mark -

bool nucleus::isEqual(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return true;
	}
	if (isKindOf(ref)) {
		return (compare(ref) == cmp_same);
	}
	return false;
}

bool nucleus::isEqual(Owning<Any> ptr) const { if (ptr) { return isEqual(*ptr); } return false; }

#pragma mark -

ComparisonResult nucleus::compare(const Any & ref) const { return compareTo(*this, &ref); }
ComparisonResult nucleus::compare(Owning<Any> ptr) const { if (ptr) { return compare(*ptr); } return cmp_descending; }

#pragma mark -

bool nucleus::doesContain(const Any & ref) const { COCONUT_UNUSED(ref); return false; }
bool nucleus::doesContain(Owning<Any> ptr) const { if (ptr) { return doesContain(*ptr); } return false; }

#pragma mark -

bool nucleus::doesNotContain(const Any & ref) const { return !doesContain(ref); }
bool nucleus::doesNotContain(Owning<Any> ptr) const { return !doesContain(ptr); }

#pragma mark -

bool nucleus::isIdenticalTo(const Any & ref) const { return sig() == ref.sig(); }
bool nucleus::isIdenticalTo(Owning<Any> ptr) const { if (ptr) { return isIdenticalTo(*ptr); } return false; }

#pragma mark -

bool nucleus::isNotIdenticalTo(const Any & ref) const { return !isIdenticalTo(ref); }
bool nucleus::isNotisIdenticalTo(Owning<Any> ptr) const { return !isIdenticalTo(ptr); }

#pragma mark -

bool nucleus::isEqualTo(const Any & ref) const { return isEqual(ref); }
bool nucleus::isEqualTo(Owning<Any> ptr) const { if (ptr) { return isEqualTo(*ptr); } return false; }

#pragma mark -

bool nucleus::isNotEqualTo(const Any & ref) const { return !isEqual(ref); }
bool nucleus::isNotEqualTo(Owning<Any> ptr) const { if (ptr) { return isNotEqualTo(*ptr); } return false; }

#pragma mark -

bool nucleus::isLessThan(const Any & ref) const { return (compare(ref) == cmp_ascending); }
bool nucleus::isLessThan(Owning<Any> ptr) const { if (ptr) { return isLessThan(*ptr); } return false; }

#pragma mark -

bool nucleus::isLessThanOrEqualTo(const Any & ref) const { int cmp = compare(ref); return (cmp == cmp_ascending || cmp == cmp_same); }
bool nucleus::isLessThanOrEqualTo(Owning<Any> ptr) const { if (ptr) { return isLessThanOrEqualTo(*ptr); } return false; }

#pragma mark -

bool nucleus::isGreaterThan(const Any & ref) const { return (compare(ref) == cmp_descending); }
bool nucleus::isGreaterThan(Owning<Any> ptr) const { if (ptr) { return isGreaterThan(*ptr); } return false; }

#pragma mark -

bool nucleus::isGreaterThanOrEqualTo(const Any & ref) const { int cmp = compare(ref); return (cmp == cmp_descending || cmp == cmp_same); }
bool nucleus::isGreaterThanOrEqualTo(Owning<Any> ptr) const { if (ptr) { return isGreaterThanOrEqualTo(*ptr); } return false; }

#pragma mark -

bool nucleus::operator &= (const Any & ref) const { return isIdenticalTo(ref); }
bool nucleus::operator == (const Any & ref) const { return isEqualTo(ref); }
bool nucleus::operator != (const Any & ref) const { return isNotEqualTo(ref); }
bool nucleus::operator < (const Any & ref) const { return isLessThan(ref); }
bool nucleus::operator <= (const Any & ref) const { return isLessThanOrEqualTo(ref); }
bool nucleus::operator > (const Any & ref) const { return isGreaterThan(ref); }
bool nucleus::operator >= (const Any & ref) const { return isGreaterThanOrEqualTo(ref); }

#pragma mark -

const std::string nucleus::description() const
{
	return COCONUT_DESCRIPTION_FMT(
		class_name(),
		class_tree(),
		algorithm::to_string<std::string>(size()),
		algorithm::to_string<std::string>(sig()),
		addr()
	);
}

#pragma mark -

std::string nucleus::stringValue() const { return u8"<none>"; }
std::u16string nucleus::string16Value() const { return unicode::utf8_to_utf16(stringValue()); }
std::u32string nucleus::string32Value() const { return unicode::utf8_to_utf32(stringValue()); }

#pragma mark -

float nucleus::floatValue() const { return 0.0f; }
double nucleus::doubleValue() const { return 0.0; }
long double nucleus::longDoubleValue() const { return 0.0L; }

bool nucleus::boolValue() const { return false; }

char nucleus::charValue() const { return 0; }
short nucleus::shortValue() const { return 0; }
int nucleus::intValue() const { return 0; }
long nucleus::longValue() const { return 0L; }
long long nucleus::longLongValue() const { return 0LL; }

unsigned char nucleus::unsignedCharValue() const { return 0; }
unsigned short nucleus::unsignedShortValue() const { return 0; }
unsigned int nucleus::unsignedIntValue() const { return 0; }
unsigned long nucleus::unsignedLongValue() const { return 0UL; }
unsigned long long nucleus::unsignedLongLongValue() const { return 0ULL; }

#pragma mark -

std::size_t nucleus::size() const { return 0LL; }

#pragma mark -

uintptr_t nucleus::sig() const
{
	return unsafe_cast<uintptr_t>(this);
}

const std::string nucleus::addr() const
{
	return m_addr;
}

#pragma mark -

bool nucleus::mutability() const
{
	return m_ismutable;
}

/* EOF */