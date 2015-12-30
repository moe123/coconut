//
// islice.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/proxy/islice.hpp>
#include <coconut/runtime/detail/core/algorithm.hpp>

using namespace coconut::runtime;

islice::islice() :
	m_start(0),
	m_stop(0),
	m_step(1)
{ /* NOP */ }

islice::islice(const islice & slc) :
	m_start(slc.m_start),
	m_stop(slc.m_stop),
	m_step(slc.m_step)
{ /* NOP */ }

islice::islice(const std::string & slc_string) :
	m_start(0),
	m_stop(0),
	m_step(1)
{
	try {
		std::regex regex("\\{\"start\" : ([0-9]+), \"stop\" : ([0-9]+), \"step\" : ([0-9]+)\\}", std::regex::icase);
		std::smatch match;
		std::ssub_match sub_match;
		if (std::regex_match(slc_string, match, regex)) {
			if (match.size() == 4) {
				sub_match = match[1];
				m_start = algorithm::to_numeric<std::int64_t>(sub_match.str());
				sub_match = match[2];
				m_stop = algorithm::to_numeric<std::int64_t>(sub_match.str());
				sub_match = match[3];
				m_step = algorithm::to_numeric<std::int64_t>(sub_match.str());
			}
		}
	}
	catch (std::regex_error e) { /* NOP */ }
}

islice::islice(std::int64_t start, std::int64_t stop) :
	m_start(start),
	m_stop(stop),
	m_step(1)
{ /* NOP */ }

islice::islice(std::int64_t start, std::int64_t stop, std::int64_t step) :
	m_start(start),
	m_stop(stop),
m_step(step == 0 ? 1 : step)
{ /* NOP */ }

islice::~islice()
{ /* NOP */ }

#pragma mark -

islice & islice::operator = (const islice & slc)
{
	if (this == &slc) {
		return *this;
	}
	m_start = slc.m_start;
	m_stop = slc.m_stop;
	m_step = slc.m_step;
	
	return *this;
}

int islice::compare(const islice & other_slc) const
{
	if (this == &other_slc) {
		return cmp_same;
	} else if (m_start == other_slc.m_start && m_stop == other_slc.m_stop && m_step == other_slc.m_step) {
		return cmp_same;
	}
	return cmp_descending; 
}

std::string islice::to_string() const
{
	return algorithm::format
	(
		"{\"start\" : %ll, \"stop\" : %ll, \"step\" : %u}",
			m_start,
			m_stop,
	 		m_step
	 );
}

#pragma mark -

std::int64_t islice::start() const
{ return m_start; }

std::int64_t islice::stop() const
{ return m_stop; }

std::int64_t islice::step() const
{ return m_step; }

void islice::set_start(std::int64_t start)
{ m_start = start; }

void islice::set_stop(std::int64_t stop)
{ m_stop = stop; }

void islice::set_step(std::int64_t step)
{ m_step = step == 0 ? 1 : step; }

#pragma mark -

void islice::get_indexes(std::vector<std::size_t> & idxes, std::size_t forlen) const
{
	std::int64_t start = m_start < 0 ? m_start + forlen : m_start;
	std::int64_t stop = start + (m_stop < 0 ? m_stop + forlen : m_stop);
	std::int64_t step = m_step;
	
	std::cerr << " + start  + : " << start << std::endl;
	std::cerr << " + stop  + : " << stop << std::endl;
	
	idxes.clear();
	for(std::int64_t i = start; (i < stop && step > 0) || (i > stop && step < 0); i += step) {
		idxes.push_back(unsafe_cast<std::size_t>(i));
	}
	
	for (const auto & idx : idxes) {
		std::cerr << " + idx  + : " << idx << std::endl;
	}
}

/* EOF */