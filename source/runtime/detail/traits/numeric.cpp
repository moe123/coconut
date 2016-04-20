//
// numeric.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/traits/numeric.hpp>
#include <coconut/runtime/detail/core/algorithm.hpp>

using namespace coconut::runtime::traits;

numeric::numeric()
{ m_type = numeric_zero; }

numeric::numeric(const numeric & num)
{
	switch (num.m_type)
	{
		case numeric_float :
			m_val_float = num.m_val_float;
		break;
		case numeric_double :
			m_val_double = num.m_val_double;
		break;
		case numeric_long_double :
			m_val_long_double = num.m_val_long_double;
		break;
		case numeric_bool :
			m_val_bool = num.m_val_bool;
		break;
		case numeric_char :
			m_val_char = num.m_val_char;
		break;
		case numeric_short :
			m_val_short = num.m_val_short;
		break;
		case numeric_int :
			m_val_int = num.m_val_int;
		break;
		case numeric_long :
			m_val_long = num.m_val_long;
		break;
		case numeric_longlong :
			m_val_longlong = num.m_val_longlong;
		break;
		case numeric_unsigned_char :
			m_val_unsigned_char = num.m_val_unsigned_char;
		break;
		case numeric_unsigned_short :
			m_val_unsigned_short = num.m_val_unsigned_short;
		break;
		case numeric_unsigned_int :
			m_val_unsigned_int = num.m_val_unsigned_int;
		break;
		case numeric_unsigned_long :
			m_val_unsigned_long = num.m_val_unsigned_long;
		break;
		case numeric_unsigned_longlong :
			m_val_unsigned_longlong = num.m_val_unsigned_longlong;
		break;
	}
	m_type = num.m_type;
	m_signed = num.m_signed;
	m_floating = num.m_floating;
}

numeric::numeric(const float & value)
{
	m_val_float = value;
	m_type = numeric_float;
	m_signed = true;
	m_floating = true;
}

numeric::numeric(const double & value)
{
	m_val_double = value;
	m_type = numeric_double;
	m_signed = true;
	m_floating = true;
}

numeric::numeric(const long double & value)
{
	m_val_long_double = value;
	m_type = numeric_long_double;
	m_signed = true;
	m_floating = false;
}

numeric::numeric(const bool & value)
{
	m_val_bool = value;
	m_type = numeric_bool;
	m_signed = false;
	m_floating = false;
}

numeric::numeric(const char & value)
{
	m_val_char = value;
	m_type = numeric_char;
	m_signed = true;
	m_floating = false;
}

numeric::numeric(const short & value)
{
	m_val_short = value;
	m_type = numeric_short;
	m_signed = true;
	m_floating = false;
}

numeric::numeric(const int & value)
{
	m_val_int = value;
	m_type = numeric_int;
	m_signed = true;
	m_floating = false;
}

numeric::numeric(const long & value)
{
	m_val_long = value;
	m_type = numeric_long;
	m_signed = true;
	m_floating = false;
}

numeric::numeric(const long long & value)
{
	m_val_longlong = value;
	m_type = numeric_longlong;
	m_signed = true;
	m_floating = false;
}

numeric::numeric(const unsigned char & value)
{
	m_val_unsigned_char = value;
	m_type = numeric_unsigned_char;
	m_signed = false;
	m_floating = false;
}

numeric::numeric(const unsigned short & value)
{
	m_val_unsigned_short = value;
	m_type = numeric_unsigned_short;
	m_signed = false;
	m_floating = false;
}

numeric::numeric(const unsigned int & value)
{
	m_val_unsigned_int = value;
	m_type = numeric_unsigned_int;
	m_signed = false;
	m_floating = false;
}

numeric::numeric(const unsigned long & value)
{
	m_val_unsigned_long = value;
	m_type = numeric_unsigned_long;
	m_signed = false;
	m_floating = false;
}

numeric::numeric(const unsigned long long & value)
{
	m_val_unsigned_longlong = value;
	m_type = numeric_unsigned_longlong;
	m_signed = false;
	m_floating = false;
}

numeric::~numeric()
{ /* NOP */ }

#pragma mark -

numeric & numeric::operator = (const numeric & num)
{
	if (this == &num) {
		return *this;
	}
	switch (num.m_type)
	{
		case numeric_float :
			m_val_float = num.m_val_float;
		break;
		case numeric_double :
			m_val_double = num.m_val_double;
		break;
		case numeric_long_double :
			m_val_long_double = num.m_val_long_double;
		break;
		case numeric_bool :
			m_val_bool = num.m_val_bool;
		break;
		case numeric_char :
			m_val_char = num.m_val_char;
		break;
		case numeric_short :
			m_val_short = num.m_val_short;
		break;
		case numeric_int :
			m_val_int = num.m_val_int;
		break;
		case numeric_long :
			m_val_long = num.m_val_long;
		break;
		case numeric_longlong :
			m_val_longlong = num.m_val_longlong;
		break;
		case numeric_unsigned_char :
			m_val_unsigned_char = num.m_val_unsigned_char;
		break;
		case numeric_unsigned_short :
			m_val_unsigned_short = num.m_val_unsigned_short;
		break;
		case numeric_unsigned_int :
			m_val_unsigned_int = num.m_val_unsigned_int;
		break;
		case numeric_unsigned_long :
			m_val_unsigned_long = num.m_val_unsigned_long;
		break;
		case numeric_unsigned_longlong :
			m_val_unsigned_longlong = num.m_val_unsigned_longlong;
		break;
	}
	m_type = num.m_type;
	m_signed = num.m_signed;
	m_floating = num.m_floating;
	
	return *this;
}

#pragma mark -

int numeric::compare(const numeric & other_num) const
{
	if (this == &other_num) {
		return cmp_same;
	}
	if (m_signed) {
		if (m_floating) {
			if (to_double() < other_num.to_double()) {
				return cmp_ascending;
			} else if (to_double() > other_num.to_double()) {
				return cmp_descending;
			}
		} else {
			if (to_longlong() < other_num.to_longlong()) {
				return cmp_ascending;
			} else if (to_longlong() > other_num.to_longlong()) {
				return cmp_descending;
			}
		}
	} else {
		if (to_unsigned_longlong() < other_num.to_unsigned_longlong()) {
			return cmp_ascending;
		} else if (to_unsigned_longlong() > other_num.to_unsigned_longlong()) {
			return cmp_descending;
		}
	}
	return cmp_same;
}

#pragma mark -

float numeric::to_float() const
{ return get<float>(); }

double numeric::to_double() const
{ return get<double>(); }

long double numeric::to_long_double() const
{ return get<long double>(); }

#pragma mark -

bool numeric::to_bool() const
{
	if (m_type == numeric_bool) {
		return get<bool>();
	}
	if (m_signed) {
		if (m_floating) {
			return get<double>() > 0.0 ? true : false;
		}
		return get<long long>() > 0 ? true : false;
	}
	return get<unsigned long long>() > 0 ? true : false;
}

#pragma mark -

char numeric::to_char() const
{ return get<char>(); }

short numeric::to_short() const
{ return get<short>(); }

int numeric::to_int() const
{ return get<int>(); }

long numeric::to_long() const
{ return get<long>(); }

long long numeric::to_longlong() const
{ return get<long long>(); }

#pragma mark -

unsigned char numeric::to_unsigned_char() const
{ return get<unsigned char>(); }

unsigned short numeric::to_unsigned_short() const
{ return get<unsigned short>(); }

unsigned int numeric::to_unsigned_int() const
{ return get<unsigned int>(); }

unsigned long numeric::to_unsigned_long() const
{ return get<unsigned long>(); }

unsigned long long numeric::to_unsigned_longlong() const
{ return get<unsigned long long>(); }

#pragma mark -

std::string numeric::to_string() const
{
	switch (m_type)
	{
		case numeric_float :
			return algorithm::to_string<std::string>(m_val_float, 6);
		case numeric_double :
			return algorithm::to_string<std::string>(m_val_double, 24);
		case numeric_long_double :
			return algorithm::to_string<std::string>(m_val_long_double, 36);
		case numeric_bool :
			return algorithm::to_string<std::string>(m_val_bool);
		case numeric_char :
			return algorithm::to_string<std::string>(m_val_char);
		case numeric_short :
			return algorithm::to_string<std::string>(m_val_short);
		case numeric_int :
			return algorithm::to_string<std::string>(m_val_int);
		case numeric_long :
			return algorithm::to_string<std::string>(m_val_long);
		case numeric_longlong :
			return algorithm::to_string<std::string>(m_val_longlong);
		case numeric_unsigned_char :
			return algorithm::to_string<std::string>(m_val_unsigned_char);
		case numeric_unsigned_short :
			return algorithm::to_string<std::string>(m_val_unsigned_short);
		case numeric_unsigned_int :
			return algorithm::to_string<std::string>(m_val_unsigned_int);
		case numeric_unsigned_long :
			return algorithm::to_string<std::string>(m_val_unsigned_long);
		case numeric_unsigned_longlong :
			return algorithm::to_string<std::string>(m_val_unsigned_longlong);
	}
	return u8"0";
}

std::size_t numeric::hash_code() const
{
	if (m_signed) {
		if (m_floating) {
			return std::hash<double>()(to_double() + static_cast<double>(m_type));
		}
		return std::hash<long long>()(to_longlong() + static_cast<long long>(m_type));
	}
	return std::hash<unsigned long long>()(to_longlong() + static_cast<unsigned long long>(m_type));
}

#pragma mark -

double numeric::to_real() const
{ return get<double>(); }

std::int64_t numeric::to_integer() const
{ return get<std::int64_t>(); }

std::uint64_t numeric::to_unsigned_integer() const
{ return get<std::uint64_t>(); }

#pragma mark -

std::uint16_t numeric::type() const { return m_type; };

/* EOF */