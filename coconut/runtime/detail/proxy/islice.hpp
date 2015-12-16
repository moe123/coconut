//
// islice.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>
#include <coconut/runtime/detail/core/algorithm.hpp>
#include <coconut/runtime/detail/core/iterator.hpp>

#ifndef COCONUT_RUNTIME_RANGE_HPP
#define COCONUT_RUNTIME_RANGE_HPP

namespace coconut
{
	namespace runtime
	{
		COCONUT_PRIVATE class COCONUT_EXPORT islice COCONUT_FINAL
		{
		COCONUT_RUNTIME_KDCL(coconut.runtime.islice, islice)
			
		public:
			islice();
			islice(const islice & slc);
			islice(const std::string & slc_string);
			islice(std::int64_t start, std::int64_t stop);
			islice(std::int64_t start, std::int64_t stop, std::uint16_t step);
			virtual ~islice();
		
		public:
			islice & operator = (const islice & slc);
			int compare(const islice & other_slc) const;
			
			std::int64_t start() const;
			std::int64_t stop() const;
			std::uint16_t step() const;
			
			void set_start(std::int64_t start);
			void set_stop(std::int64_t stop);
			void set_step(std::uint16_t step);
			
			bool iszero() const;
			std::size_t max() const;
			
			std::string to_string() const;
		
		private:
			std::int64_t m_start;
			std::int64_t m_stop;
			std::uint16_t m_step;
		};
	}
}

#endif /* !COCONUT_RUNTIME_RANGE_HPP */

/* EOF */