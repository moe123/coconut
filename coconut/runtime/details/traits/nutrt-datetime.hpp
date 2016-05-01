//
// nutrt-datetime.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_DATETIME_HPP
#define COCONUT_RUNTIME_DATETIME_HPP

namespace coconut {
	namespace runtime {
		namespace traits {

COCONUT_PRIVATE class COCONUT_VISIBLE datetime COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.datetime, datetime)
	
public:
	datetime();
	datetime(const datetime & dtm);
	datetime(double milliseconds, timeref_option ref_opt = timeref_since_ref);
	datetime(double interval, timeunit_option unit_opt, timeref_option ref_opt);
	datetime(double interval, timeunit_option unit_opt, const datetime & dtm);	
	~datetime();

public:
	COCONUT_CLASSMETHOD double absolute(timeunit_option unit_opt);
	
	COCONUT_CLASSMETHOD std::string utc_now();
	COCONUT_CLASSMETHOD datetime utc_parse(const std::string & utc);
	
	COCONUT_CLASSMETHOD bool get_now(std::pair<std::int64_t, std::int64_t> & tm);
	
	COCONUT_CLASSMETHOD double timestamp_1970(timeunit_option unit_opt);
	COCONUT_CLASSMETHOD double reference_time(timeunit_option unit_opt);
	
	COCONUT_CLASSMETHOD datetime past();
	COCONUT_CLASSMETHOD datetime future();

public:
	datetime & operator = (const datetime & dtm);
	int compare(const datetime & other_dtm) const;
	
	const datetime & earlier(const datetime & dtm) const;
	const datetime & later(const datetime & dtm) const;
	
	std::string to_string() const;
	std::size_t hash_code() const;
	
	double time_interval_since(const datetime & dtm) const;
	double time_interval_since(const datetime & dtm, timeunit_option unit_opt) const;
	double time_interval_since(timeref_option ref_opt, timeunit_option unit_opt) const;
	
	double time_interval_since_ref() const;
	double time_interval_since_now() const;
	double time_interval_since_1970() const;
	
	datetime by_adding_time(double milliseconds) const;
	datetime by_adding_time(double interval, timeunit_option unit_opt) const;
	
private:
	std::size_t m_type;
	double m_millitime;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_DATETIME_HPP */

/* EOF */