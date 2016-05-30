//
// nutrt-nucleus.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-nucleus.hpp>
#include <coconut/runtime/details/nutrt-zombie.hpp>

#include <coconut/runtime/details/nutrt-algorithms.hpp>
#include <coconut/runtime/details/nutrt-async.hpp>
#include <coconut/runtime/details/nutrt-unicode.hpp>

using namespace coconut::runtime;

nucleus::nucleus()
: m_attrs()
, m_kinds()
, m_kind(classkind_anon)
, m_tag(-1000)
, m_ismutable(false)
{ /* NOP */ }

nucleus::nucleus(const nucleus & ref)
: m_attrs()
, m_kinds()
, m_kind(classkind_anon)
, m_tag(-1000)
, m_ismutable(false)
{ COCONUT_UNUSED(ref); }

nucleus & nucleus::operator = (const nucleus & ref)
{ COCONUT_UNUSED(ref); return *this; }

nucleus::nucleus(ClassKind root, ClassKind kind)
: m_attrs()
, m_kinds()
, m_kind(kind)
, m_tag(-1000)
, m_ismutable(false)
{
	m_kinds.push_back(classkind_nucleus);
	m_kinds.push_back(root);
	if (m_kind != classkind_nucleus && m_kind != root) {
		m_kinds.push_back(m_kind);
	}
}

nucleus::~nucleus()
{ m_attrs.clear(); m_kinds.clear(); }

#pragma mark -

bool nucleus::isSelectorKey(const std::string & utf8_in)
{
	if (algorithms::starts_with(utf8_in, u8"@") && !algorithms::starts_with(utf8_in, u8"@@")) {
		return true;
	}
	return false;
}

bool nucleus::isAttributeKey(const std::string & utf8_attrkey)
{
	if (algorithms::starts_with(utf8_attrkey, u8"$") && !algorithms::starts_with(utf8_attrkey, u8"$$")) {
		return true;
	}
	return false;
}

#pragma mark -

bool nucleus::respondsToSelectorKey(const std::string & utf8_selkey) const
{
	if (isSelectorKey(utf8_selkey)) {
		Owning<Any> ptr;
		if (runtime::algorithms::ends_with(utf8_selkey, u8":")) {
			ptr = valueForSelectorKey(utf8_selkey, ptr_create<zombie>());
		} else {
			ptr = valueForSelectorKey(utf8_selkey);
		}
		if (ptr) { return true; }
	}
	return false;
}

void nucleus::performSelectorKeyAfterDelay(std::uint64_t microseconds, bool wait, const std::string & utf8_selkey, Owning<Any> arg, const std::function<void(Owning<Any> result)> & completion) const noexcept(false)
{
	if (isSelectorKey(utf8_selkey)) {
		if (wait) {
			auto op = runtime::async::exec(runtime::launch_async, [this, &microseconds, &utf8_selkey, &arg, &completion]
			{
				if (microseconds) { std::this_thread::sleep_for(std::chrono::microseconds(microseconds)); }
				Owning<Any> result = valueForSelectorKey(utf8_selkey, arg);
				if (completion) {
					completion(result);
				}
			});
			op();
		} else {
			runtime::async::detach([this, microseconds, &utf8_selkey, arg, &completion]
			{
				if (microseconds) { std::this_thread::sleep_for(std::chrono::microseconds(microseconds)); }
				Owning<Any> result = valueForSelectorKey(utf8_selkey, arg);
				if (completion) {
					completion(result);
				}
			});
		}
	} else {
		doesNotRecognizeSelectorKey(utf8_selkey);
	}
}

void nucleus::performSelectorKeyAfterDelay(std::uint64_t microseconds, bool wait, const std::string & utf8_selkey, Owning<Any> arg) const noexcept(false)
{ performSelectorKeyAfterDelay(0, false, utf8_selkey, arg, {}); }

void nucleus::performSelectorKeyInBackground(const std::string & utf8_selkey, Owning<Any> arg) const
{ performSelectorKeyAfterDelay(0, false, utf8_selkey, arg, {}); }

#pragma mark -

void nucleus::performSelectorKeyInBackground(const std::string & utf8_selkey, const std::function<void(Owning<Any> result)> & completion) const noexcept(false)
{ performSelectorKeyAfterDelay(0, false, utf8_selkey, {}, completion); }

void nucleus::performSelectorKeyInBackground(const std::string & utf8_selkey, Owning<Any> arg , const std::function<void(Owning<Any> result)> & completion) const noexcept(false)
{ performSelectorKeyAfterDelay(0, false, utf8_selkey, arg, completion); }

#pragma mark -

Owning<Any> nucleus::performSelectorKey(const std::string & utf8_selkey, Owning<Any> arg) const noexcept(false)
{
	if (isSelectorKey(utf8_selkey)) {
		auto op = runtime::async::exec(runtime::launch_any, [this, &utf8_selkey, &arg]
		{ return valueForSelectorKey(utf8_selkey, arg); });
		return op();
	} else {
		doesNotRecognizeSelectorKey(utf8_selkey);
	}
	return {};
}

#pragma mark -

void nucleus::doesNotRecognizeSelectorKey(const std::string & utf8_selkey) const noexcept(false)
{
	std::stringstream ss;
	ss << u8"unrecognized selectorKey sent: ('";
	ss << utf8_selkey;
	ss << u8"', ";
	ss << std::hex << std::showbase << this;
	ss << u8")";
	
	throw std::runtime_error(ss.str());
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
{ return m_kind; }

ClassKind nucleus::parentClassKind() const
{ std::size_t n = m_kinds.size(); return n > 1 ? m_kinds[n - 2] : m_kind; }

#pragma mark -

void nucleus::conveyAttributesFrom(const Any & ref)
{ m_attrs.insert(ref.m_attrs.begin(), ref.m_attrs.end()); }

void nucleus::copyAttributesFrom(const Any & ref)
{
	for (std::map<std::string, Owning<Any> >::const_iterator it = ref.m_attrs.cbegin(); it != ref.m_attrs.cend(); ++it) {
		if ((*it).second) {
			m_attrs.insert(std::make_pair((*it).first, ((*it).second)->kindCopy()));
		}
	}
}

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

void nucleus::setTag(std::int16_t tag)
{ m_tag = tag; }

std::int16_t nucleus::tag() const
{ return m_tag; }

#pragma mark -

const std::string nucleus::className() const
{ return class_name(); }

const std::string nucleus::classTree() const
{ return class_tree(); }

#pragma mark -

const Owning<Any> nucleus::itself() const
{ return ptr_snatch<Any>(this); }

#pragma mark -

std::size_t nucleus::hash() const
{ return weak_cast<std::size_t>(sig()); }

#pragma mark -

bool nucleus::isKindOfClass(ClassKind kind) const
{ return !(std::find(m_kinds.begin(), m_kinds.end(), kind) == m_kinds.end()); }

bool nucleus::isMemberOfClass(ClassKind kind) const
{ return (m_kind == kind); }

bool nucleus::isSubclassOfClass(ClassKind kind) const
{ return (parentClassKind() == kind); }

bool nucleus::isKindOfClassNamed(const std::string & name) const
{
	std::vector<std::string> parts;
	parts = runtime::algorithms::split(name, u8".");
	for (std::vector<std::string>::reverse_iterator it = parts.rbegin(); it != parts.rend(); ++it) {
		if ((*it) == name) { return true; }
	}
	return false;
}

bool nucleus::isMemberOfClassNamed(const std::string & name) const
{ return (class_name() == name); }

#pragma mark -

bool nucleus::isKindOf(ClassKind kind) const
{ return isKindOfClass(kind); }

bool nucleus::isKindOf(const Any & ref, const Any & other_ref) const
{ return (ref.isKindOf(other_ref.classKind())); }

bool nucleus::isKindOf(const Owning<Any> & ptr, const Owning<Any> & other_ptr) const
{
	if (ptr && other_ptr) {
		return isKindOf(*ptr, *other_ptr);
	}
	return false;
}

bool nucleus::isKindOf(const Any & ref) const
{ return isKindOf(ref.classKind()); }

bool nucleus::isKindOf(const Owning<Any> & ptr) const
{
	if (ptr) {
		return isKindOf(*ptr);
	}
	return false;
}

#pragma mark -

bool nucleus::isSubclassOf(ClassKind kind) const
{ return isSubclassOfClass(kind); }

bool nucleus::isSubclassOf(const Any & ref, const Any & other_ref) const
{ return (ref.isSubclassOf(other_ref.classKind())); }

bool nucleus::isSubclassOf(const Owning<Any> & ptr, const Owning<Any> & other_ptr) const
{
	if (ptr && other_ptr) {
		return isSubclassOf(*ptr, *other_ptr);
	}
	return false;
}

bool nucleus::isSubclassOf(const Any & ref) const
{ return isSubclassOf(ref.classKind()); }

bool nucleus::isSubclassOf(const Owning<Any> & ptr) const
{
	if (ptr) {
		return isSubclassOf(*ptr);
	}
	return false;
}

#pragma mark -

bool nucleus::isMemberOf(ClassKind kind) const
{ return isMemberOfClass(kind); }

bool nucleus::isMemberOf(const Any & ref, const Any & other_ref) const
{ return (ref.classKind() == other_ref.classKind()); }

bool nucleus::isMemberOf(const Owning<Any> & ptr, const Owning<Any> & other_ptr) const
{
	if (ptr && other_ptr) {
		return isMemberOf(*ptr, *other_ptr);
	}
	return false;
}

bool nucleus::isMemberOf(const Any & ref) const
{ return isMemberOf(ref.classKind()); }

bool nucleus::isMemberOf(const Owning<Any> & ptr) const
{
	if (ptr) {
		return isMemberOf(*ptr);
	}
	return false;
}

#pragma mark -

bool nucleus::isAncestorOf(const Any & ref) const
{ return ref.isKindOf(*this); }

bool nucleus::isAncestorOf(const Owning<Any> & ptr) const
{
	if (ptr) {
		return isAncestorOf(*ptr);
	}
	return false;
}

#pragma mark -

bool nucleus::isParentOf(const Any & ref) const
{ return (ref.parentClassKind() == classKind()); }

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
	parts = algorithms::split(utf8_keypath, u8".");
	if (parts.size() >= 2) {
		Owning<Any> vv = valueForKey(parts[0]);
		if (vv) {
			parts.erase(parts.begin());
			if (parts.size() >= 2) {
				v = vv->valueForKeyPath(algorithms::join(parts, u8"."));
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
		parts = algorithms::split(utf8_keypath, u8".");
		if (parts.size() >= 2) {
			Owning<Any> vv = valueForKey(parts[0]);
			if (vv) {
				parts.erase(parts.begin());
				if (parts.size() >= 2) {
					vv->setValueForKeyPath(ptr, algorithms::join(parts, u8"."));
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

bool nucleus::isEqual(const Owning<Any> & ptr) const { if (ptr) { return isEqual(*ptr); } return false; }

#pragma mark -

ComparisonResult nucleus::compare(const Any & ref) const { return compareTo(*this, &ref); }
//ComparisonResult nucleus::compare(const Owning<Any> & ptr) const { if (ptr) { return compare(*ptr); } return cmp_descending; }

#pragma mark -

bool nucleus::doesContain(const Any & ref) const { COCONUT_UNUSED(ref); return false; }
//bool nucleus::doesContain(const Owning<Any> & ptr) const { if (ptr) { return doesContain(*ptr); } return false; }

#pragma mark -

bool nucleus::doesNotContain(const Any & ref) const { return !doesContain(ref); }
bool nucleus::doesNotContain(const Owning<Any> & ptr) const { return !doesContain(*ptr); }

#pragma mark -

bool nucleus::isIdenticalTo(const Any & ref) const { return sig() == ref.sig(); }
bool nucleus::isIdenticalTo(const Owning<Any> & ptr) const { if (ptr) { return isIdenticalTo(*ptr); } return false; }

#pragma mark -

bool nucleus::isNotIdenticalTo(const Any & ref) const { return !isIdenticalTo(ref); }
bool nucleus::isNotisIdenticalTo(Owning<Any> ptr) const { return !isIdenticalTo(ptr); }

#pragma mark -

bool nucleus::isEqualTo(const Any & ref) const { return isEqual(ref); }
bool nucleus::isEqualTo(const Owning<Any> & ptr) const { if (ptr) { return isEqualTo(*ptr); } return false; }

#pragma mark -

bool nucleus::isNotEqualTo(const Any & ref) const { return !isEqual(ref); }
bool nucleus::isNotEqualTo(const Owning<Any> & ptr) const { if (ptr) { return isNotEqualTo(*ptr); } return false; }

#pragma mark -

bool nucleus::isLessThan(const Any & ref) const { return (compare(ref) == cmp_ascending); }
bool nucleus::isLessThan(const Owning<Any> & ptr) const { if (ptr) { return isLessThan(*ptr); } return false; }

#pragma mark -

bool nucleus::isLessThanOrEqualTo(const Any & ref) const { int cmp = compare(ref); return (cmp == cmp_ascending || cmp == cmp_same); }
bool nucleus::isLessThanOrEqualTo(const Owning<Any> & ptr) const { if (ptr) { return isLessThanOrEqualTo(*ptr); } return false; }

#pragma mark -

bool nucleus::isGreaterThan(const Any & ref) const { return (compare(ref) == cmp_descending); }
bool nucleus::isGreaterThan(const Owning<Any> & ptr) const { if (ptr) { return isGreaterThan(*ptr); } return false; }

#pragma mark -

bool nucleus::isGreaterThanOrEqualTo(const Any & ref) const { int cmp = compare(ref); return (cmp == cmp_descending || cmp == cmp_same); }
bool nucleus::isGreaterThanOrEqualTo(const Owning<Any> & ptr) const { if (ptr) { return isGreaterThanOrEqualTo(*ptr); } return false; }

#pragma mark -

bool nucleus::operator &= (const Any & ref) const { return isIdenticalTo(ref); }
bool nucleus::operator &= (const Owning<Any> & ptr) const { return isIdenticalTo(ptr); }

#pragma mark -

bool nucleus::operator == (const Any & ref) const { return isEqualTo(ref); }
bool nucleus::operator == (const Owning<Any> & ptr) const { return isEqualTo(ptr); }

#pragma mark -

bool nucleus::operator != (const Any & ref) const { return isNotEqualTo(ref); }
bool nucleus::operator != (const Owning<Any> & ptr) const { return isNotEqualTo(ptr); }

#pragma mark -

bool nucleus::operator < (const Any & ref) const { return isLessThan(ref); }
bool nucleus::operator < (const Owning<Any> & ptr) const { return isLessThan(ptr); }

#pragma mark -

bool nucleus::operator <= (const Any & ref) const { return isLessThanOrEqualTo(ref); }
bool nucleus::operator <= (const Owning<Any> & ptr) const { return isLessThanOrEqualTo(ptr); }

#pragma mark -

bool nucleus::operator > (const Any & ref) const { return isGreaterThan(ref); }
bool nucleus::operator > (const Owning<Any> & ptr) const { return isGreaterThan(ptr); }

#pragma mark -

bool nucleus::operator >= (const Any & ref) const { return isGreaterThanOrEqualTo(ref); }
bool nucleus::operator >= (const Owning<Any> & ptr) const { return isGreaterThanOrEqualTo(ptr); }

#pragma mark -

const std::string nucleus::description() const
{
	std::stringstream ss; ss << std::hex << std::showbase << this;
	
	return COCONUT_DESCRIPTION_FMT(
		class_name(),
		class_tree(),
		algorithms::to_string<char>(size()),
		algorithms::to_string<char>(sig()),
		ss.str()
	);
}

#pragma mark -

std::string nucleus::stringValue() const { return u8""; }
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

std::size_t nucleus::size() const { return sizeof(*this); }

#pragma mark -

std::ptrdiff_t nucleus::sig() const
{ return weak_cast<std::ptrdiff_t>(this); }

#pragma mark -

bool nucleus::mutability() const
{ return m_ismutable; }

/* EOF */