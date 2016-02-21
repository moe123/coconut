//
// numeric.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/traits/numeric.hpp>
#include <coconut/runtime/detail/core/algorithm.hpp>

using namespace coconut::runtime;

numeric::numeric()
{
	m_type = numeric_zero;
	m_sizeof = 0;
}

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
	m_sizeof = num.m_sizeof;
}

numeric::numeric(const float & value)
{
	m_val_float = value;
	m_type = numeric_float;
	m_sizeof = sizeof(m_val_float);
}

numeric::numeric(const double & value)
{
	m_val_double = value;
	m_type = numeric_double;
	m_sizeof = sizeof(m_val_double);
}

numeric::numeric(const long double & value)
{
	m_val_long_double = value;
	m_type = numeric_long_double;
	m_sizeof = sizeof(m_val_long_double);
}

numeric::numeric(const bool & value)
{
	m_val_bool = value;
	m_type = numeric_bool;
	m_sizeof = sizeof(m_val_bool);
}

numeric::numeric(const char & value)
{
	m_val_char = value;
	m_type = numeric_char;
	m_sizeof = sizeof(m_val_char);
}

numeric::numeric(const short & value)
{
	m_val_short = value;
	m_type = numeric_short;
	m_sizeof = sizeof(m_val_short);
}

numeric::numeric(const int & value)
{
	m_val_int = value;
	m_type = numeric_int;
	m_sizeof = sizeof(m_val_int);
}

numeric::numeric(const long & value)
{
	m_val_long = value;
	m_type = numeric_long;
	m_sizeof = sizeof(m_val_long);
}

numeric::numeric(const long long & value)
{
	m_val_longlong = value;
	m_type = numeric_longlong;
	m_sizeof = sizeof(m_val_longlong);
}

numeric::numeric(const unsigned char & value)
{
	m_val_unsigned_char = value;
	m_type = numeric_unsigned_char;
	m_sizeof = sizeof(m_val_unsigned_char);
}
numeric::numeric(const unsigned short & value)
{
	m_val_unsigned_short = value;
	m_type = numeric_unsigned_short;
	m_sizeof = sizeof(m_val_unsigned_short);
}

numeric::numeric(const unsigned int & value)
{
	m_val_unsigned_int = value;
	m_type = numeric_unsigned_int;
	m_sizeof = sizeof(m_val_unsigned_int);
}

numeric::numeric(const unsigned long & value)
{
	m_val_unsigned_long = value;
	m_type = numeric_unsigned_long;
	m_sizeof = sizeof(m_val_unsigned_long);
}

numeric::numeric(const unsigned long long & value)
{
	m_val_unsigned_longlong = value;
	m_type = numeric_unsigned_longlong;
	m_sizeof = sizeof(m_val_unsigned_longlong);
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
	m_sizeof = num.m_sizeof;
	
	return *this;
}

#pragma mark -

int numeric::compare(const numeric & other_num) const
{
	if (this == &other_num) {
		return cmp_same;
	} else if (to_double() < other_num.to_double()) {
		return cmp_ascending;
	} else if (to_double() > other_num.to_double()) {
		return cmp_descending;
	}
	return cmp_same;
}

#pragma mark -

float numeric::to_float() const
{
	return get<float>();
}

double numeric::to_double() const
{
	return get<double>();
}

long double numeric::to_long_double() const
{
	return get<long double>();
}

#pragma mark -

bool numeric::to_bool() const
{
	if (m_type == numeric_bool) {
		return get<bool>();
	}
	return get<double>() > 0.0 ? true : false;
}

#pragma mark -

char numeric::to_char() const
{
	return get<char>();
}

short numeric::to_short() const
{
	return get<short>();
}

int numeric::to_int() const
{
	return get<int>();
}

long numeric::to_long() const
{
	return get<long>();
}

long long numeric::to_longlong() const
{
	return get<long long>();
}

#pragma mark -

unsigned char numeric::to_unsigned_char() const
{
	return get<unsigned char>();
}

unsigned short numeric::to_unsigned_short() const
{
	return get<unsigned short>();
}

unsigned int numeric::to_unsigned_int() const
{
	return get<unsigned int>();
}

unsigned long numeric::to_unsigned_long() const
{
	return get<unsigned long>();
}

unsigned long long numeric::to_unsigned_longlong() const
{
	return get<unsigned long long>();
}

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
	return std::hash<double>()(to_double() + static_cast<double>(m_type));
}

#pragma mark -

double numeric::to_real() const
{
	return get<double>();
}

std::int64_t numeric::to_integer() const
{
	return get<std::int64_t>();
}

std::uint64_t numeric::to_unsigned_integer() const
{
	return get<std::uint64_t>();
}

#pragma mark -

std::size_t numeric::type() const { return m_type; };
std::size_t numeric::size() const { return m_sizeof; }

/* EOF */