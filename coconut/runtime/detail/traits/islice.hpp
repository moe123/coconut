//
// islice.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_ISLICE_HPP
#define COCONUT_RUNTIME_ISLICE_HPP

namespace coconut {
	namespace runtime {
		namespace traits {

COCONUT_PRIVATE class COCONUT_VISIBLE islice COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.islice, islice)
	
public:
	islice();
	islice(const islice & slc);
	islice(const std::string & slc_string);
	islice(std::int64_t start, std::int64_t stop);
	islice(std::int64_t start, std::int64_t stop, std::int64_t step);
	~islice();

public:
	islice & operator = (const islice & slc);
	int compare(const islice & other_slc) const;
	
	std::int64_t start() const;
	std::int64_t stop() const;
	std::int64_t step() const;
	
	void set_start(std::int64_t start);
	void set_stop(std::int64_t stop);
	void set_step(std::int64_t step);
	
	void get_indexes(std::vector<std::size_t> & idxes, std::size_t forlen) const;
	
	std::string to_string() const;

private:
	std::int64_t m_start;
	std::int64_t m_stop;
	std::int64_t m_step;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ISLICE_HPP */

/* EOF */