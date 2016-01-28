//
// Slice.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Slice.hpp>
#include <coconut/foundation/Range.hpp>

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
	Slice(start, stop, 1)
{ /* NOP */ }

Slice::Slice(std::int64_t start, std::int64_t stop, std::int64_t step) :
	Object(SliceClass),
	m_impl(start, stop, step)
{ /* NOP */ }

Slice::Slice(const Range & rg) :
	Slice(
		static_cast<std::int64_t>(rg.location()),
		static_cast<std::int64_t>(rg.length()),
		1
	)
{ /* NOP */ }

Slice::~Slice()
{ /* NOP */ }

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