//
// Slice.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Slice.hpp>

using namespace coconut;

Slice::Slice() :
	Object(SliceClass),
	m_impl()
{ /* NOP */ }

Slice::Slice(const Slice & slc) :
	Object(SliceClass),
	m_impl(slc.m_impl)
{ /* NOP */ }

Slice::Slice(std::int64_t start, std::int64_t stop) :
	Object(SliceClass),
	m_impl(start, stop)
{ /* NOP */ }

Slice::Slice(std::int64_t start, std::int64_t stop, std::int64_t step) :
	Object(SliceClass),
	m_impl(start, stop, step)
{ /* NOP */ }

Slice::~Slice()
{ /* NOP */ }

Owning<Slice> Slice::with()
{ return ptr_create<Slice>(); }

Owning<Slice> Slice::with(const Slice & slc)
{ return ptr_create<Slice>(slc); }

Owning<Slice> Slice::with(std::int64_t start, std::int64_t stop)
{ return ptr_create<Slice>(start, stop); }

Owning<Slice> Slice::with(std::int64_t start, std::int64_t stop, std::int64_t step)
{ return ptr_create<Slice>(start, stop, step); }

#pragma mark -

std::size_t Slice::hash() const
{ return m_impl.start() + m_impl.stop() + m_impl.step(); }

#pragma mark -

Owning<Any> Slice::copy() const
{ return ptr_create<Slice>(*this); }

#pragma mark -

ComparisonResult Slice::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return m_impl.compare(ref_cast<Slice>(ref).m_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string Slice::stringValue() const
{ return m_impl.to_string(); }

#pragma mark -

std::int64_t Slice::start() const
{ return m_impl.start(); }

std::int64_t Slice::stop() const
{ return m_impl.stop(); }

std::int64_t Slice::step() const
{ return m_impl.step(); }

/* EOF */