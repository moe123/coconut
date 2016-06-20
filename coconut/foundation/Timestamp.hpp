//
// Timestamp.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_TIMESTAMP_HPP
#define COCONUT_FOUNDATION_TIMESTAMP_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Timestamp COCONUT_FINAL : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Timestamp, Object.Timestamp)
		
	public:
		Timestamp();
		Timestamp(const Timestamp & tms);
		Timestamp & operator = (const Timestamp & tms) = default;
		Timestamp(Timestamp && tms) noexcept;
		Timestamp(const Date & dtm);
		Timestamp(TimeInterval nanoseconds);
		Timestamp(TimeInterval interval, TimeUnitOption unit_opt);
		virtual ~Timestamp();
		
		COCONUT_CLASSMETHOD const Timestamp distantFuture();
		COCONUT_CLASSMETHOD const Timestamp distantPast();
		COCONUT_CLASSMETHOD const Timestamp now();
		
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
		
		virtual long long longLongValue() const
		COCONUT_FINAL_OVERRIDE;
		
		TimeInterval time() const;
		TimeInterval time(TimeUnitOption unit_opt) const;
		
		const Date date() const;
		
		const Timestamp timestampByAddingTimeInterval(TimeInterval nanoseconds) const;
		const Timestamp timestampByAddingTimeInterval(TimeInterval interval, TimeUnitOption unit_opt) const;
		
		const Timestamp & earlierTimestamp(const Timestamp & tms) const;
		const Timestamp & laterTimestamp(const Timestamp & tms) const;
		
		TimeInterval elapsed() const;
		TimeInterval elapsed(TimeUnitOption unit_opt) const;
		
		bool isElapsed(TimeInterval nanoseconds) const;
		bool isElapsed(TimeInterval interval, TimeUnitOption unit_opt) const;
		
		bool after(const Timestamp & tms) const;
		bool before(const Timestamp & tms) const;
	
	private:
		typedef TimeInterval impl_trait;
		
	private:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_TIMESTAMP_HPP */

/* EOF */