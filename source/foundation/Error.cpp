//
// Error.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Error.hpp>

using namespace coconut;

Error::Error() :
	Object(ErrorClass),
	m_impl{ u8"<none>", NotFound, {} }
{ /* NOP */ }

Error::Error(const Error & err) :
	Object(ErrorClass),
	m_impl(err.m_impl)
{ /* NOP */ }

Error::Error(Error && err) :
	Object(ErrorClass),
	m_impl(std::move(err.m_impl))
{ /* NOP */ }

Error::Error(std::size_t code) :
	Object(ErrorClass),
	m_impl{ u8"<none>", code, {} }
{ /* NOP */ }

Error::Error(const String & domain, std::size_t code) :
	Object(ErrorClass),
	m_impl{ domain, code, {} }
{ /* NOP */ }

Error::Error(const String & domain, std::size_t code, const Dictionary & userInfo) :
	Object(ErrorClass),
	m_impl{ domain, code, userInfo }
{ /* NOP */ }

Error::~Error()
{ /* NOP */ }

#pragma mark -

ErrorPtr Error::with()
{ return ptr_create<Error>(); }

ErrorPtr Error::with(const Error & err)
{ return ptr_create<Error>(err); }

ErrorPtr Error::with(Error && err)
{ return ptr_create<Error>(std::move(err)); }

ErrorPtr Error::with(std::size_t code)
{ return ptr_create<Error>(code); }

ErrorPtr Error::with(const String & domain, std::size_t code)
{ return ptr_create<Error>(domain, code); }

ErrorPtr Error::with(const String & domain, std::size_t code, const Dictionary & userInfo)
{ return ptr_create<Error>(domain, code, userInfo); }

#pragma mark -

std::size_t Error::hash() const
{ return std::get<0>(m_impl).hash() + std::get<1>(m_impl); }

#pragma mark -

Owning<Any> Error::copy() const
{ return ptr_create<Error>(*this); }

#pragma mark -

ComparisonResult Error::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (code() < ref_cast<Error>(ref).code()) {
			return OrderedAscending;
		} else if (code() > ref_cast<Error>(ref).code()) {
			return OrderedDescending;
		}
		return OrderedSame;
	}
	return OrderedDescending;
}

#pragma mark -

std::string Error::stringValue() const
{ return std::get<0>(m_impl).stringValue(); }

std::size_t Error::code() const
{ return std::get<1>(m_impl); }

const String Error::domain() const
{ return std::get<0>(m_impl); }

const Dictionary Error::userInfo() const
{ return std::get<2>(m_impl); }

/* EOF */