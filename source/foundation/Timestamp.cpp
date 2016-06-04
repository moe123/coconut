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

Timestamp::Timestamp(const Date & dtm) :
	Object(TimestampClass),
	m_impl(dtm.timeIntervalSinceReference(TimeReferenceSinceJanuary1970, TimeUnitNanoSeconds))
{ /* NOP */ }

Timestamp::Timestamp(TimeInterval nanoseconds) :
	Object(TimestampClass),
	m_impl(nanoseconds)
{ /* NOP */ }

Timestamp::Timestamp(TimeInterval interval, TimeUnitOption unit_opt) :
	Object(TimestampClass),
	m_impl(Date::convertTime(interval, unit_opt, TimeUnitNanoSeconds))
{ /* NOP */ }

Timestamp::~Timestamp()
{ /* NOP */ }

#pragma mark -

const Timestamp Timestamp::now()
{ return Timestamp(); }

#pragma mark -

std::size_t Timestamp::hash() const
{ return std::hash<long long>()(longLongValue()); }

#pragma mark -

Owning<Any> Timestamp::copy() const
{ return ptr_create<Timestamp>(*this); }

#pragma mark -

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

#pragma mark -

std::string Timestamp::stringValue() const
{ return runtime::algorithms::to_string<char>(longLongValue()); }

double Timestamp::doubleValue() const
{ return m_impl; }

long long Timestamp::longLongValue() const
{ return weak_cast<long long>(m_impl); }

#pragma mark -

TimeInterval Timestamp::time() const
{ return m_impl; }

TimeInterval Timestamp::time(TimeUnitOption unit_opt) const
{ return Date::convertTime(m_impl, TimeUnitNanoSeconds, unit_opt); }

const Date Timestamp::date() const
{ return Date(m_impl, TimeUnitNanoSeconds, TimeReferenceSinceJanuary1970); }

#pragma mark -

const Timestamp Timestamp::timestampByAddingTimeInterval(TimeInterval nanoseconds) const
{ return Timestamp(m_impl + nanoseconds); }

const Timestamp Timestamp::timestampByAddingTimeInterval(TimeInterval interval, TimeUnitOption unit_opt) const
{
	TimeInterval nanoseconds = Date::convertTime(interval, unit_opt, TimeUnitNanoSeconds);
	return Timestamp(m_impl + nanoseconds);
}

#pragma mark -

const Timestamp & Timestamp::earlierTimestamp(const Timestamp & tms) const
{ return (longLongValue() > tms.longLongValue()) ? tms : *this; }

const Timestamp & Timestamp::laterTimestamp(const Timestamp & tms) const
{ return (tms.longLongValue() > longLongValue()) ? tms : *this; }

#pragma mark -

TimeInterval Timestamp::elapsed() const
{
	return Date::absoluteTime(TimeUnitNanoSeconds) - m_impl;
}

TimeInterval Timestamp::elapsed(TimeUnitOption unit_opt) const
{
	return Date::convertTime(
		(Date::absoluteTime(TimeUnitNanoSeconds) - m_impl),
		TimeUnitNanoSeconds,
		unit_opt
	);
}

#pragma mark -

bool Timestamp::after(const Timestamp & tms) const
{ return longLongValue() > tms.longLongValue(); }

bool Timestamp::before(const Timestamp & tms) const
{ return tms.longLongValue() > longLongValue(); }

/* EOF */