//
// URL.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/URL.hpp>
#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/MutableDictionary.hpp>
#include <coconut/foundation/Path.hpp>
#include <coconut/foundation/String.hpp>

using namespace coconut;

URL::URL() :
	Object(URLClass),
	m_impl()
{ /* NOP */ }

URL::URL(const URL & url) :
	Object(URLClass),
	m_impl(url.m_impl, false)
{ /* NOP */ }

URL::URL(URL && url) noexcept :
	Object(URLClass),
	m_impl(std::move(url.m_impl), false)
{ /* NOP */ }

URL::URL(const Path & path) :
	Object(URLClass),
	m_impl(path.stringValue(), true, false)
{ /* NOP */ }

URL::URL(const String & in) :
	Object(URLClass),
	m_impl(in.stringValue())
{ /* NOP */ }

URL::URL(const String & in, const URL & url) :
	Object(URLClass),
	m_impl(in.stringValue(), url.m_impl, false)
{ /* NOP */ }

URL::URL(const String & scheme, const String & host, const String & path) :
	Object(URLClass),
	m_impl(scheme.stringValue(), host.stringValue(), path.stringValue(), false)
{ /* NOP */ }

URL::URL(const char * in) :
	Object(URLClass),
	m_impl(in)
{ /* NOP */ }

URL::~URL()
{ /* NOP */ }

#pragma mark -

const String URL::percentEscapesEncode(const String & in, bool space_as_plus)
{ return {impl_trait::escape(in.stringValue(), space_as_plus)}; }

const String URL::percentEscapesDecode(const String & in, bool plus_as_space)
{ return {impl_trait::unescape(in.stringValue(), plus_as_space)}; }

#pragma mark -

Owning<Any> URL::copy() const
{ return ptr_create<URL>(*this); }

#pragma mark -

ComparisonResult URL::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return m_impl.compare(ref_cast<URL>(ref).m_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string URL::stringValue() const
{ return m_impl.to_string(); }

#pragma mark -

bool URL::isFileURL() const
{ return m_impl.is_file_url(); }

#pragma mark -

const URL URL::normalizedURL() const
{
	URL ret;
	ret.m_impl = impl_trait(m_impl, true);
	return ret;
}

const String URL::specifier() const
{ return String{m_impl.specifier()}; }

#pragma mark -

const String URL::scheme() const
{ return {m_impl.scheme()}; }

const String URL::host() const
{ return {m_impl.scheme()}; }

std::size_t URL::port() const
{ return m_impl.port(); }

const String URL::user() const
{ return {m_impl.user()}; }

const String URL::password() const
{ return {m_impl.password()}; }

const String URL::path() const
{ return {m_impl.path()}; }

const String URL::parameter() const
{ return {m_impl.parameter()}; }

const String URL::query() const
{ return {m_impl.query()}; }

const String URL::fragment() const
{ return {m_impl.fragment()}; }

#pragma mark -

const Dictionary URL::queryParameters() const
{
	Dictionary::impl_trait buf;
	auto parameters = m_impl.parameters();
	for (auto & kv : parameters) {
		buf.insert(std::make_pair(ptr_create<String>(kv.first), ptr_create<String>(kv.second)));
	}
	return Dictionary(buf.cbegin(), buf.cend());
}

#pragma mark -

const Path URL::fileSystemRepresentation() const
{ return {m_impl.path().c_str()}; }

/* EOF */