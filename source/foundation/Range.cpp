//
// Range.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Range.hpp>
#include <coconut/foundation/MutableRange.hpp>

using namespace coconut;

Range::Range() :
	Object(RangeClass),
	m_impl()
{ /* NOP */ }

Range::Range(const Range & rg) :
	Object(RangeClass),
	m_impl(rg.m_impl)
{ /* NOP */ }

Range::Range(std::size_t location, std::size_t length) :
	Object(RangeClass),
	m_impl(location, length)
{ /* NOP */ }

Range::~Range()
{ /* NOP */ }

#pragma mark -

Owning<Range> Range::with()
{ return ptr_create<Range>(); }

Owning<Range> Range::with(const Range & rg)
{ return ptr_create<Range>(rg); }

Owning<Range> Range::with(std::size_t location, std::size_t length)
{ return ptr_create<Range>(location, length); }

#pragma mark -

std::size_t Range::hash() const
{ return maxRange(); }

#pragma mark -

Owning<Any> Range::copy() const
{ return ptr_create<Range>(*this); }

Owning<Any> Range::mutableCopy() const
{ return ptr_create<MutableRange>(*this); }

#pragma mark -

ComparisonResult Range::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return m_impl.compare(ref_cast<Range>(ref).m_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string Range::stringValue() const
{ return m_impl.to_string(); }

#pragma mark -

std::size_t Range::location() const
{ return m_impl.location(); }

std::size_t Range::length() const
{ return m_impl.length(); }

#pragma mark -

bool Range::isZeroRange() const
{ return m_impl.iszero(); }

std::size_t Range::maxRange() const
{ return m_impl.max(); }

#pragma mark -

bool Range::locationInRange(std::size_t location) const
{ return m_impl.in(location); }

const Range Range::intersectionRange(const Range & other_rg) const
{
	impl_type rg = m_impl.intxn(other_rg.m_impl);
	return Range(rg.location(), rg.length());
}

const Range Range::unionRange(const Range & other_rg) const
{
	impl_type rg = m_impl.merge(other_rg.m_impl);
	return Range(rg.location(), rg.length());
}

#pragma mark -

Range::iterator Range::begin() { return m_impl.begin(); }
Range::iterator Range::end() { return m_impl.end(); }

Range::const_iterator Range::begin() const { return m_impl.begin(); }
Range::const_iterator Range::end() const { return m_impl.end(); }

Range::const_iterator Range::cbegin() const { return m_impl.cbegin(); }
Range::const_iterator Range::cend() const { return m_impl.cend(); }

Range::reverse_iterator Range::rbegin() { return m_impl.rbegin(); }
Range::reverse_iterator Range::rend() { return m_impl.rend(); }

Range::const_reverse_iterator Range::rbegin() const { return m_impl.rbegin(); }
Range::const_reverse_iterator Range::rend() const { return m_impl.rend(); }

Range::const_reverse_iterator Range::crbegin() const { return m_impl.crbegin(); }
Range::const_reverse_iterator Range::crend() const { return m_impl.crend(); }

#pragma mark -

bool EqualRanges(const Range & rg1, const Range & rg2)
{ return rg1.isEqual(rg2); }

Range IntersectionRange(const Range & rg1, const Range & rg2)
{ return rg1.intersectionRange(rg2); }

bool LocationInRange(std::size_t location, const Range & rg)
{ return rg.locationInRange(location); }

Range MakeRange(std::size_t location, std::size_t length)
{ return Range(location, length); }

std::size_t MaxRange(const Range & rg)
{ return rg.maxRange(); }

Range UnionRange(const Range & rg1, const Range & rg2)
{ return rg1.unionRange(rg2); }
	
/* EOF */