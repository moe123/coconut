//
// numeric.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_NUMERIC_HPP
#define COCONUT_RUNTIME_NUMERIC_HPP

namespace coconut
{
	namespace runtime
	{
		COCONUT_PRIVATE class COCONUT_EXPORT numeric COCONUT_FINAL
		{
		COCONUT_RUNTIME_KDCL(coconut.runtime.numeric, numeric)
			
		public:
			numeric();
			numeric(const numeric & num);
			numeric(const float & value);
			numeric(const double & value);
			numeric(const long double & value);
			numeric(const bool & value);
			numeric(const char & value);
			numeric(const short & value);
			numeric(const int & value);
			numeric(const long & value);
			numeric(const long long & value);
			numeric(const unsigned char & value);
			numeric(const unsigned short & value);
			numeric(const unsigned int & value);
			numeric(const unsigned long & value);
			numeric(const unsigned long long & value);
			virtual ~numeric();
		
		public:
			numeric & operator = (const numeric & num);
			int compare(const numeric & other_num) const;
			
		private:
			template <typename T>
			T get(void * no_param = nullptr) const
			{
				COCONUT_UNUSED(no_param);
				T result = 0;
				switch (m_type)
				{
					case numeric_float :
						return unsafe_cast<T>(m_val_float);
					case numeric_double :
						return unsafe_cast<T>(m_val_double);
					case numeric_long_double :
						return unsafe_cast<T>(m_val_long_double);
					case numeric_bool :
						return unsafe_cast<T>(m_val_bool);
					case numeric_char :
						return unsafe_cast<T>(m_val_char);
					case numeric_short :
						return unsafe_cast<T>(m_val_short);
					case numeric_int :
						return unsafe_cast<T>(m_val_int);
					case numeric_long :
						return unsafe_cast<T>(m_val_long);
					case numeric_longlong :
						return unsafe_cast<T>(m_val_longlong);
					case numeric_unsigned_char :
						return unsafe_cast<T>(m_val_unsigned_char);
					case numeric_unsigned_short :
						return unsafe_cast<T>(m_val_unsigned_short);
					case numeric_unsigned_int :
						return unsafe_cast<T>(m_val_unsigned_int);
					case numeric_unsigned_long :
						return unsafe_cast<T>(m_val_unsigned_long);
					case numeric_unsigned_longlong :
						return unsafe_cast<T>(m_val_unsigned_longlong);
				}
				return result;
			}
		
		public:
			float to_float() const;
			double to_double() const;
			long double to_long_double() const;
			
			bool to_bool() const;
			
			char to_char() const;
			short to_short() const;
			int to_int() const;
			long to_long() const;
			long long to_longlong() const;
			
			unsigned char to_unsigned_char() const;
			unsigned short to_unsigned_short() const;
			unsigned int to_unsigned_int() const;
			unsigned long to_unsigned_long() const;
			unsigned long long to_unsigned_longlong() const;
			
			std::string to_string() const;
			std::size_t hash_code() const;
			
			double to_real() const;
			std::int64_t to_integer() const;
			std::uint64_t to_unsigned_integer() const;
			
			std::size_t type() const;
			std::size_t size() const;
			
		private:
			float m_val_float;
			double m_val_double;
			long double m_val_long_double;
			bool m_val_bool;
			
			char m_val_char;
			short m_val_short;
			int m_val_int;
			long m_val_long;
			long long m_val_longlong;
			
			unsigned char m_val_unsigned_char;
			unsigned short m_val_unsigned_short;
			unsigned int m_val_unsigned_int;
			unsigned long m_val_unsigned_long;
			unsigned long long m_val_unsigned_longlong;
			
		private:
			std::size_t m_type;
			std::size_t m_sizeof;
		};
	}
}

#endif /* !COCONUT_RUNTIME_NUMERIC_HPP */

/* EOF */