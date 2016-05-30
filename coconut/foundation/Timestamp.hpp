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
		virtual ~Timestamp();

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
		
		TimeInterval time(TimeUnitOption unit_opt = TimeUnitNanoSeconds) const;
		const Date date() const;
		
	private:
		typedef TimeInterval impl_trait;
		
	private:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_TIMESTAMP_HPP */

/* EOF */