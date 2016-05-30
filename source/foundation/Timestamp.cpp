//
// Timestamp.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Timestamp.hpp>
#include <coconut/foundation/Date.hpp>

using namespace coconut;

Timestamp::Timestamp() :
	Object(TimestampClass),
	m_impl(Date::absoluteTime(TimeUnitNanoSeconds))
{ /* NOP */ }

Timestamp::Timestamp(const Timestamp & tms) :
	Object(TimestampClass),
	m_impl(tms.m_impl)
{ /* NOP */ }

Timestamp::Timestamp(Timestamp && tms) noexcept :
	Object(TimestampClass),
	m_impl(tms.m_impl)
{ /* NOP */ }

Timestamp::~Timestamp()
{ /* NOP */ }

std::size_t Timestamp::hash() const
{ return std::hash<TimeInterval>()(m_impl); }

Owning<Any> Timestamp::copy() const
{ return ptr_create<Timestamp>(*this); }

ComparisonResult Timestamp::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (m_impl < ref_cast<Timestamp>(ref).m_impl) {
			return OrderedAscending;
		} else if (ref_cast<Timestamp>(ref).m_impl < m_impl) {
			return OrderedDescending;
		}
		return OrderedSame;
	}
	return OrderedDescending;
}

std::string Timestamp::stringValue() const
{ return runtime::algorithms::to_string<char>(m_impl, 24); }

double Timestamp::doubleValue() const
{ return m_impl; }

TimeInterval Timestamp::time(TimeUnitOption unit_opt) const
{ return Date::convertTime(m_impl, TimeUnitNanoSeconds, unit_opt); }

const Date Timestamp::date() const
{ return Date(m_impl, TimeUnitNanoSeconds, TimeReferenceSinceJanuary1970); }

/* EOF */