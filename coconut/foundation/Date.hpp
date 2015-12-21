//
// Date.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_DATE_HPP
#define COCONUT_FOUNDATION_DATE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT Date : public Object
	{
	COCONUT_KDCL(coconut.Date, Object.Date)
		
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
		
		COCONUT_KTOD const String UTC();
		COCONUT_KTOD const String UTC(const Date & dtm);
		COCONUT_KTOD const Date fromUTC(const String & UTC);
		
		COCONUT_KTOD TimeInterval absoluteTime(TimeUnitOption unit_opt = TimeUnitNanoSeconds);
		COCONUT_KTOD TimeInterval timestamp(TimeUnitOption unit_opt, TimestampOption stamp_opt = TimestampSinceJanuary1970);
		
		COCONUT_KTOD const Date distantFuture();
		COCONUT_KTOD const Date distantPast();
		COCONUT_KTOD const Date now();
		
		COCONUT_KTOR DatePtr with();
		COCONUT_KTOR DatePtr with(const Date & dtm);
		COCONUT_KTOR DatePtr with(Date && dtm);
		COCONUT_KTOR DatePtr with(TimeInterval seconds, TimeReferenceOption ref_opt);
		COCONUT_KTOR DatePtr with(TimeInterval seconds, const Date & since);
		COCONUT_KTOR DatePtr with(TimeInterval interval, TimeUnitOption unit_opt, TimeReferenceOption ref_opt);
		COCONUT_KTOR DatePtr with(TimeInterval interval, TimeUnitOption unit_opt, const Date & since);
		
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
		friend inline std::ostream & operator << (std::ostream & os, const DatePtr ptr)
		{ if (ptr) { os << ptr->stringValue(); } return os; }
		
	public:
		typedef runtime::datetime impl_type;
	
	protected:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_DATE_HPP */

/* EOF */