//
// Date.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Date.hpp>
#include <coconut/foundation/String.hpp>

using namespace coconut;

Date::Date() :
	Object(DateClass),
	m_impl(0.0L, TimeReferenceSinceCurrentTime)
{ /* NOP */ }

Date::Date(const Date & dtm) :
	Object(DateClass),
	m_impl(dtm.m_impl)
{ /* NOP */ }

Date::Date(Date && dtm) :
	Object(DateClass),
	m_impl(std::move(dtm.m_impl))
{ /* NOP */ }

Date::Date(TimeInterval seconds, TimeReferenceOption ref_opt) :
	Object(DateClass),
	m_impl(seconds, TimeUnitPlainSeconds, ref_opt)
{ /* NOP */ }

Date::Date(TimeInterval seconds, const Date & since) :
	Object(DateClass),
	m_impl(seconds, TimeUnitPlainSeconds, since.m_impl)
{ /* NOP */ }

Date::Date(TimeInterval interval, TimeUnitOption unit_opt, TimeReferenceOption ref_opt) :
	Object(DateClass),
	m_impl(interval, unit_opt, ref_opt)
{ /* NOP */ }

Date::Date(TimeInterval interval, TimeUnitOption unit_opt, const Date & since) :
	Object(DateClass),
	m_impl(interval, unit_opt, since.m_impl)
{ /* NOP */ }

Date::~Date()
{ /* NOP */ }

#pragma mark -

const String Date::UTC()
{ return String(impl_trait::utc_now()); }

const String Date::UTC(const Date & dtm)
{ return String(dtm.stringValue()); }

#pragma mark -

const Date Date::fromUTC(const String & UTC)
{
	Date dtm(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.m_impl = impl_trait::utc_parse(UTC.stringValue());
	return dtm;
}

#pragma mark -

TimeInterval Date::absoluteTime(TimeUnitOption unit_opt)
{ return impl_trait::absolute(unit_opt); }

TimeInterval Date::timestamp(TimeUnitOption unit_opt, TimestampOption stamp_opt)
{
	if (stamp_opt == TimestampSinceReferenceDate) {
		return impl_trait::reference_time(unit_opt);
	}
	return impl_trait::timestamp_1970(unit_opt);
}

#pragma mark -

const Date Date::distantFuture()
{
	Date dtm(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.m_impl = impl_trait::future();
	return dtm;
}

const Date Date::distantPast()
{
	Date dtm(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.m_impl = impl_trait::past();
	return dtm;
}

#pragma mark -

const Date Date::now()
{ return Date(); }

#pragma mark -

std::size_t Date::hash() const
{ return m_impl.hash_code(); }

#pragma mark -

Owning<Any> Date::copy() const
{ return ptr_create<Date>(*this); }

#pragma mark -

ComparisonResult Date::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return m_impl.compare(ref_cast<Date>(ref).m_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string Date::stringValue() const
{ return m_impl.to_string(); }

double Date::doubleValue() const
{ return m_impl.time_interval_since_1970(); }

#pragma mark -

TimeInterval Date::timeIntervalSinceDate(const Date & dtm, TimeUnitOption unit_opt) const
{ return m_impl.time_interval_since(dtm.m_impl, unit_opt); }

TimeInterval Date::timeIntervalSinceReference(TimeReferenceOption ref_opt, TimeUnitOption unit_opt) const
{ return m_impl.time_interval_since(ref_opt, unit_opt); }

#pragma mark -

const Date Date::dateByAddingTimeInterval(TimeInterval seconds) const
{
	Date dtm = Date(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.m_impl = std::move(m_impl.by_adding_time(seconds, TimeUnitPlainSeconds));
	return dtm;
}

const Date Date::dateByAddingTimeInterval(TimeInterval interval, TimeUnitOption unit_opt) const
{
	Date dtm = Date(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.m_impl = std::move(m_impl.by_adding_time(interval, unit_opt));
	return dtm;
}

#pragma mark -

const Date & Date::earlierDate(const Date & dtm) const
{ return timeIntervalSinceDate(dtm, TimeUnitMilliSeconds) < 0 ? *this : dtm; }

const Date & Date::laterDate(const Date & dtm) const
{ return timeIntervalSinceDate(dtm, TimeUnitMilliSeconds) > 0 ? *this : dtm; }

/* EOF */