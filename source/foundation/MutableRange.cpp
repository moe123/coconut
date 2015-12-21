//
// MutableRange.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/MutableRange.hpp>

using namespace coconut;

MutableRange::MutableRange() :
	Range()
{ setClassKind(MutableRangeClass, true); }

MutableRange::MutableRange(const MutableRange & rg) :
	Range(ref_cast<Range>(rg))
{ setClassKind(MutableRangeClass, true); }

MutableRange::MutableRange(const Range & rg) :
	Range(rg)
{ setClassKind(MutableRangeClass, true); }

MutableRange::MutableRange(std::size_t location, std::size_t length) :
	Range(location, length)
{ setClassKind(MutableRangeClass, true); }

MutableRange::~MutableRange()
{ setClassKind(MutableRangeClass, true); }

#pragma mark -

Owning<MutableRange> MutableRange::with()
{
	return ptr_create<MutableRange>();
}

Owning<MutableRange> MutableRange::with(const MutableRange & rg)
{
	return ptr_create<MutableRange>(rg);
}

Owning<MutableRange> MutableRange::with(const Range & rg)
{
	return ptr_create<MutableRange>(rg);
}

Owning<MutableRange> MutableRange::with(std::size_t location, std::size_t length)
{
	return ptr_create<MutableRange>(location, length);
}

#pragma mark -

void MutableRange::setLocation(std::size_t location)
{
	m_impl.set_location(location);
}

void MutableRange::setLength(std::size_t length)
{
	m_impl.set_length(length);
}

/* EOF */