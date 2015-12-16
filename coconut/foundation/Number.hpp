//
// Number.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_NUMBER_HPP
#define COCONUT_FOUNDATION_NUMBER_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT Number COCONUT_FINAL : public Object
	{
	COCONUT_KDCL(coconut.Number, Object.Number)
		
	public:
		Number();
		Number(const Number & num);
		Number & operator = (const Number & num) = default;
		
		Number(const float & value);
		Number(const double & value);
		Number(const long double & value);
		Number(const bool & value);
		Number(const char & value);
		Number(const short & value);
		Number(const int & value);
		Number(const long & value);
		Number(const long long & value);
		Number(const unsigned char & value);
		Number(const unsigned short & value);
		Number(const unsigned int & value);
		Number(const unsigned long & value);
		Number(const unsigned long long & value);
		virtual ~Number();
		
		COCONUT_KTOR NumberPtr with(const Number & num);
		COCONUT_KTOR NumberPtr with(const float & value);
		COCONUT_KTOR NumberPtr with(const double & value);
		COCONUT_KTOR NumberPtr with(const long double & value);
		COCONUT_KTOR NumberPtr with(const bool & value);
		COCONUT_KTOR NumberPtr with(const char & value);
		COCONUT_KTOR NumberPtr with(const short & value);
		COCONUT_KTOR NumberPtr with(const int & value);
		COCONUT_KTOR NumberPtr with(const long & value);
		COCONUT_KTOR NumberPtr with(const long long & value);
		COCONUT_KTOR NumberPtr with(const unsigned char & value);
		COCONUT_KTOR NumberPtr with(const unsigned short & value);
		COCONUT_KTOR NumberPtr with(const unsigned int & value);
		COCONUT_KTOR NumberPtr with(const unsigned long & value);
		COCONUT_KTOR NumberPtr with(const unsigned long long & value);
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual kind_ptr copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const_kind_ref ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual float floatValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual double doubleValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual long double longDoubleValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual bool boolValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual char charValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual short shortValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual int intValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual long longValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual long long longLongValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned char unsignedCharValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned short unsignedShortValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned int unsignedIntValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned long unsignedLongValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned long long unsignedLongLongValue() const
		COCONUT_FINAL_OVERRIDE;
	
	public:
		double realValue() const;
		std::int64_t integerValue() const;
		std::uint64_t unsignedIntegerValue() const;
	
	public:
		NumberType type() const;

	public:
		bool operator == (const Number & other_num) const;
		bool operator != (const Number & other_num) const;
		bool operator <  (const Number & other_num) const;
		bool operator <= (const Number & other_num) const;
		bool operator >  (const Number & other_num) const;
		bool operator >= (const Number & other_num) const;
	
	public:
		friend inline std::ostream & operator << (std::ostream & os, const NumberPtr ptr)
		{ if (ptr) { os << ptr->stringValue(); } return os; }
		
	protected:
		typedef runtime::numeric impl_type;
	
	private:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_NUMBER_HPP */

/* EOF */