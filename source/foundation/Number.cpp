//
// Number.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/Number.hpp>

using namespace coconut;

Number::Number() :
	Object(NumberClass),
	m_impl()
{ /* NOP */ }

Number::Number(const Number & num) :
	Object(NumberClass),
	m_impl(num.m_impl)
{ /* NOP */ }

Number::Number(const float & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const double & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const long double & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const bool & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const char & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const short & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const int & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const long & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const long long & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const unsigned char & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const unsigned short & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const unsigned int & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const unsigned long & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::Number(const unsigned long long & value) :
	Object(NumberClass),
	m_impl(value)
{ /* NOP */ }

Number::~Number()
{ /* NOP */ }

#pragma mark -

NumberPtr Number::with(const Number & num)
{ return ptr_create<Number>(num); }

NumberPtr Number::with(const float & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const double & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const long double & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const bool & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const char & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const short & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const int & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const long & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const long long & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const unsigned char & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const unsigned short & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const unsigned int & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const unsigned long & value)
{ return ptr_create<Number>(value); }

NumberPtr Number::with(const unsigned long long & value)
{ return ptr_create<Number>(value); }

#pragma mark -

std::size_t Number::hash() const
{ return m_impl.hash_code(); }

#pragma mark -

kind_ptr Number::copy() const
{ return ptr_create<Number>(*this); }

#pragma mark -

ComparisonResult Number::compare(const_kind_ref ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return m_impl.compare(ref_cast<Number>(ref).m_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string Number::stringValue() const
{ return m_impl.to_string(); }

#pragma mark -

float Number::floatValue() const
{ return m_impl.to_float(); }

double Number::doubleValue() const
{ return m_impl.to_double(); }

long double Number::longDoubleValue() const
{ return m_impl.to_long_double(); }

bool Number::boolValue() const
{ return m_impl.to_bool(); }

char Number::charValue() const
{ return m_impl.to_char(); }

short Number::shortValue() const
{ return m_impl.to_short(); }

int Number::intValue() const
{ return m_impl.to_int(); }

long Number::longValue() const
{ return m_impl.to_long(); }

long long Number::longLongValue() const
{ return m_impl.to_longlong(); }

unsigned char Number::unsignedCharValue() const
{ return m_impl.to_unsigned_char(); }

unsigned short Number::unsignedShortValue() const
{ return m_impl.to_unsigned_short(); }

unsigned int Number::unsignedIntValue() const
{ return m_impl.to_unsigned_int(); }

unsigned long Number::unsignedLongValue() const
{ return m_impl.to_unsigned_long(); }

unsigned long long Number::unsignedLongLongValue() const
{ return m_impl.to_unsigned_longlong(); }

#pragma mark -

double Number::realValue() const
{ return m_impl.to_real(); }

std::int64_t Number::integerValue() const
{ return m_impl.to_integer(); }

std::uint64_t Number::unsignedIntegerValue() const
{ return m_impl.to_unsigned_integer(); }

#pragma mark -

NumberType Number::type() const
{ return m_impl.type(); }

#pragma mark -

bool Number::operator == (const Number & other_num) const
{ return (compare(other_num) == OrderedSame); }

bool Number::operator != (const Number & other_num) const
{ return (compare(other_num) != OrderedSame); }

bool Number::operator < (const Number & other_num) const
{ return (compare(other_num) == OrderedAscending); }

bool Number::operator <= (const Number & other_num) const
{
	ComparisonResult cmp = compare(other_num);
	return (cmp == OrderedAscending || cmp == OrderedSame);
}

bool Number::operator > (const Number & other_num) const
{ return (compare(other_num) == OrderedDescending); }

bool Number::operator >= (const Number & other_num) const
{
	ComparisonResult cmp = compare(other_num);
	return (cmp == OrderedDescending || cmp == OrderedSame);
}

/* EOF */