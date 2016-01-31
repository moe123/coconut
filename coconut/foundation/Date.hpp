//
// Date.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_DATE_HPP
#define COCONUT_FOUNDATION_DATE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT Date : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Date, Object.Date)
		
	public:
		Date();
		Date(const Date & dtm);
		Date & operator = (const Date & dtm) = default;
		Date(Date && dtm);
		Date(TimeInterval seconds, TimeReferenceOption ref_opt);
		Date(TimeInterval seconds, const Date & since);
		Date(TimeInterval interval, TimeUnitOption unit_opt, TimeReferenceOption ref_opt);
		Date(TimeInterval interval, TimeUnitOption unit_opt, const Date & since);
		virtual ~Date();
		
		COCONUT_CLASSMETHOD const String UTC();
		COCONUT_CLASSMETHOD const String UTC(const Date & dtm);
		COCONUT_CLASSMETHOD const Date fromUTC(const String & UTC);
		
		COCONUT_CLASSMETHOD TimeInterval absoluteTime(TimeUnitOption unit_opt = TimeUnitNanoSeconds);
		COCONUT_CLASSMETHOD TimeInterval timestamp(TimeUnitOption unit_opt, TimestampOption stamp_opt = TimestampSinceJanuary1970);
		
		COCONUT_CLASSMETHOD const Date distantFuture();
		COCONUT_CLASSMETHOD const Date distantPast();
		COCONUT_CLASSMETHOD const Date now();
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual double doubleValue() const
		COCONUT_FINAL_OVERRIDE;
		
		TimeInterval timeIntervalSinceDate(const Date & dtm, TimeUnitOption unit_opt = TimeUnitPlainSeconds) const;
		TimeInterval timeIntervalSinceReference(TimeReferenceOption ref_opt, TimeUnitOption unit_opt = TimeUnitPlainSeconds) const;
		
		const Date dateByAddingTimeInterval(TimeInterval seconds) const;
		const Date dateByAddingTimeInterval(TimeInterval interval, TimeUnitOption unit_opt) const;
		
		const Date & earlierDate(const Date & dtm) const;
		const Date & laterDate(const Date & dtm) const;

	public:
		friend inline std::ostream & operator << (std::ostream & os, const Owning<Date> & ptr)
		{ if (ptr) { os << ptr->stringValue(); } return os; }
		
	public:
		typedef runtime::datetime impl_type;
	
	protected:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_DATE_HPP */

/* EOF */