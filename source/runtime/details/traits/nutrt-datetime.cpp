//
// nutrt-datetime.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-datetime.hpp>
#include <coconut/runtime/details/traits/nutrt-formatter.hpp>
#include <coconut/runtime/details/traits/nutrt-locale.hpp>
#include <coconut/runtime/details/traits/nutrt-timezone.hpp>

using namespace coconut::runtime::traits;

#include <source/runtime/builtins/nutrt-datetime_epoch.hxx>
#include <source/runtime/builtins/nutrt-datetime_format.hxx>

datetime::datetime()
: m_type(datekind_default)
, m_millitime(0.0)
{ /* NOP */ }

datetime::datetime(const datetime & dtm)
: m_type(dtm.m_type)
, m_millitime(dtm.m_millitime)
{ /* NOP */ }

datetime::datetime(double milliseconds, timeref_option ref_opt)
: m_type(datekind_default)
, m_millitime(0.0)
{
	switch (ref_opt)
	{
		case timeref_since_ref:
		{
			m_millitime = milliseconds;
		}
		break;
		case timeref_since_now:
		{
			m_millitime = datetime::reference_time(timeunit_milliseconds) + milliseconds;
		}
		break;
		case timeref_since_1970:
		{
			m_millitime = -COCONUT_APPLE_EPOCH_MILLISECONDS + milliseconds;;
		}
		break;
		default:
			break;
	}
}

datetime::datetime(double interval, timeunit_option unit_opt, timeref_option ref_opt)
: m_type(datekind_default)
, m_millitime(0.0)
{
	double milliseconds = 0.0;
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			milliseconds = interval * 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			milliseconds = interval;
		}
		break;
		case timeunit_microseconds:
		{
			milliseconds = interval / 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			milliseconds = interval / 1000000.0;
		}
		break;
		default:
			break;
	}
	
	switch (ref_opt)
	{
		case timeref_since_ref:
		{
			m_millitime = milliseconds;
		}
		break;
		case timeref_since_now:
		{
			m_millitime = datetime::reference_time(timeunit_milliseconds) + milliseconds;
		}
		break;
		case timeref_since_1970:
		{
			m_millitime = -COCONUT_APPLE_EPOCH_MILLISECONDS + milliseconds;;
		}
		break;
		default:
			break;
	}
}

datetime::datetime(double interval, timeunit_option unit_opt, const datetime & dtm)
: m_type(datekind_default)
, m_millitime(0.0)
{
	double milliseconds = 0.0;
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			milliseconds = interval * 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			milliseconds = interval;
		}
		break;
		case timeunit_microseconds:
		{
			milliseconds = interval / 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			milliseconds = interval / 1000000.0;
		}
		break;
		default:
			break;
	}
	
	m_millitime = milliseconds - dtm.m_millitime;
}

datetime::~datetime()
{ /* NOP */ }

#pragma mark -

double datetime::absolute(timeunit_option unit_opt)
{
	double result = 0.0;
	switch (unit_opt)
	{
		case timeunit_nanoseconds:
		{
			result = static_cast<double>(builtins::datetime_nanotime());
		}
		break;
		case timeunit_microseconds:
		{
			result = static_cast<double>(builtins::datetime_microtime());
		}
		break;
		case timeunit_milliseconds:
		{
			result = static_cast<double>(builtins::datetime_millitime());
		}
		break;
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			result = static_cast<double>(builtins::datetime_millitime()) * 1000.0;
		}
		break;
		default:
			break;
	}
	return result;
}

#pragma mark -

std::string datetime::utc_now()
{
	return builtins::datetime_format_utc(
		datetime::timestamp_1970(timeunit_milliseconds)
	);
}

datetime datetime::utc_parse(const std::string & utc)
{
	double milliseconds = builtins::datetime_parse_utc(utc);
	datetime dtm(milliseconds, timeref_since_1970);
	return dtm;
}

#pragma mark -

bool datetime::get_now(std::pair<std::int64_t, std::int64_t> & tm)
{
	bool result = false;
	builtins::time_spec tms;
	tm.first = 0;
 	tm.second = 0;
	if (builtins::datetime_epoch(&tms)) {
		tm.first = static_cast<std::int64_t>(tms.tv_sec);
		tm.second = static_cast<std::int64_t>(tms.tv_nsec);
		result = true;
	}
	return result;
}

#pragma mark -

double datetime::timestamp_1970(timeunit_option unit_opt)
{
	double result = 0.0;
	std::pair<std::int64_t, std::int64_t> tm;
	
	if (datetime::get_now(tm)) {
		switch (unit_opt)
		{
			case timeunit_plainseconds:
			{
				result = static_cast<double>(tm.first);
			}
			break;
			case timeunit_doubleseconds:
			{
				result = static_cast<double>(tm.first) + static_cast<double>((tm.second / 1000000) / 1000.0);
			}
			break;
			case timeunit_milliseconds:
			{
				result = static_cast<double>(tm.first * 1000.0) + static_cast<double>((tm.second / 1000000));
			}
			break;
			case timeunit_microseconds:
			{
				result = static_cast<double>(tm.first * 1000000.0) + static_cast<double>((tm.second / 1000));
			}
			break;
			case timeunit_nanoseconds:
			{
				result = static_cast<double>(tm.first * 1000000000.0) + static_cast<double>(tm.second);
			}
			break;
			default:
				break;
		}
	}
	return result;
}

double datetime::reference_time(timeunit_option unit_opt)
{
	double result = 0.0;
	
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		{
			result = -COCONUT_APPLE_EPOCH_PLAINSECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		case timeunit_doubleseconds:
		{
			result = -COCONUT_APPLE_EPOCH_DOUBLESECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		case timeunit_milliseconds:
		{
			result = -COCONUT_APPLE_EPOCH_MILLISECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		case timeunit_microseconds:
		{
			result = -COCONUT_APPLE_EPOCH_MICROSECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		case timeunit_nanoseconds:
		{
			result = -COCONUT_APPLE_EPOCH_NANOSECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		default:
			break;
	}
	return result;
}

#pragma mark -

datetime datetime::future()
{
	datetime dtm(COCONUT_FORTY_YEARS_MILLISECONDS, timeref_since_now);
	return dtm;
}

datetime datetime::past()
{
	datetime dtm(-COCONUT_FORTY_YEARS_MILLISECONDS, timeref_since_now);
	return dtm;
}

#pragma mark -

datetime & datetime::operator = (const datetime & dtm)
{
	if (this == &dtm) {
		return *this;
	}
	m_type = dtm.m_type;
	m_millitime = dtm.m_millitime;
	
	return *this;
}

#pragma mark -

int datetime::compare(const datetime & other_dtm) const
{
	if (this == &other_dtm) {
		return cmp_same;
	}
	double interval = time_interval_since(other_dtm);
	if (interval < 0.0) {
		return cmp_ascending;
	} else if (interval > 0.0) {
		return cmp_descending;
	}
	return cmp_same;
}

#pragma mark -

const datetime & datetime::earlier(const datetime & dtm) const
{
	return time_interval_since(dtm) < 0 ? *this : dtm;
}

const datetime & datetime::later(const datetime & dtm) const
{
	return time_interval_since(dtm) > 0 ? *this : dtm;
}

#pragma mark -

std::string datetime::to_string() const
{
	return builtins::datetime_format_utc(
		time_interval_since_1970()
	);
}

std::size_t datetime::hash_code() const
{
	return std::hash<double>()(m_millitime + static_cast<double>(m_type));
}

#pragma mark -

double datetime::time_interval_since(const datetime & dtm) const
{
	return m_millitime - dtm.m_millitime;
}

double datetime::time_interval_since(const datetime & dtm, timeunit_option unit_opt) const
{
	double milliseconds = time_interval_since(dtm);
	double interval = 0.0;
	
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			interval = milliseconds / 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			interval = milliseconds;
		}
		break;
		case timeunit_microseconds:
		{
			interval = milliseconds * 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			interval = milliseconds * 1000000.0;
		}
		break;
		default:
			break;
	}
	return interval;
}

double datetime::time_interval_since(timeref_option ref_opt, timeunit_option unit_opt) const
{
	double milliseconds = 0.0;
	double interval = 0.0;
	
	switch (ref_opt)
	{
		case timeref_since_ref:
		{
			milliseconds = time_interval_since_ref();
		}
		break;
		case timeref_since_now:
		{
			milliseconds = time_interval_since_now();
		}
		break;
		case timeref_since_1970:
		{
			milliseconds = time_interval_since_1970();
		}
		break;
		default:
			break;
	}
	
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			interval = milliseconds / 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			interval = milliseconds;
		}
		break;
		case timeunit_microseconds:
		{
			interval = milliseconds * 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			interval = milliseconds * 1000000.0;
		}
		break;
		default:
			break;
	}
	return interval;
}

double datetime::time_interval_since_ref() const
{
	return m_millitime;
}

double datetime::time_interval_since_now() const
{
	return m_millitime - datetime::reference_time(timeunit_milliseconds);
}

double datetime::time_interval_since_1970() const
{
	return m_millitime + COCONUT_APPLE_EPOCH_MILLISECONDS;
}

#pragma mark -

datetime datetime::by_adding_time(double milliseconds) const
{
	return datetime(m_millitime + milliseconds, timeref_since_ref);
}

datetime datetime::by_adding_time(double interval, timeunit_option unit_opt) const
{
	double milliseconds = 0.0;
	
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			milliseconds = interval * 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			milliseconds = interval;
		}
		break;
		case timeunit_microseconds:
		{
			milliseconds = interval / 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			milliseconds = interval / 1000000.0;
		}
		break;
		default:
			break;
	}
	return datetime(m_millitime + milliseconds, timeref_since_ref);
}

/* EOF */