//
// islice.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/traits/islice.hpp>
#include <coconut/runtime/detail/core/algorithm.hpp>

using namespace coconut::runtime::traits;

islice::islice()
: m_indexes()
, m_start(0)
, m_stop(0)
, m_step(1)
{ /* NOP */ }

islice::islice(const islice & slc)
: m_indexes(slc.m_indexes)
, m_start(slc.m_start)
, m_stop(slc.m_stop)
, m_step(slc.m_step)
{ /* NOP */ }

islice::islice(islice && slc) noexcept
: m_indexes(std::move(slc.m_indexes))
, m_start(slc.m_start)
, m_stop(slc.m_stop)
, m_step(slc.m_step)
{ /* NOP */ }

islice::islice(const std::string & slc_string)
: m_indexes()
, m_start(0)
, m_stop(0)
, m_step(1)
{
	try {
		std::regex regex
		{	R"(\{\"\#\{slice\}\": \{\"start\": ([0-9]+), \"stop\": ([0-9]+), \"step\": ([0-9]+)\}\})",
			std::regex::icase
		};
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

islice::islice(std::int64_t start, std::int64_t stop)
: m_indexes()
, m_start(start)
, m_stop(stop)
, m_step(1)
{ /* NOP */ }

islice::islice(std::int64_t start, std::int64_t stop, std::int64_t step)
: m_indexes()
, m_start(start)
, m_stop(stop)
, m_step(step <= 0 ? 1 : step)
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
		u8"{\"#{slice}\": {\"start\": %" PRId64 ", \"stop\": %" PRId64 ", \"step\": %" PRId64 "}}}",
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

void islice::do_indexes(std::size_t forlen) const
{
	std::int64_t start = m_start < 0 ? m_start + forlen : m_start;
	std::int64_t stop = start + (m_stop < 0 ? m_stop + forlen : m_stop);
	std::int64_t step = m_step;
#if COCONUT_DEBUG
	std::cerr << " + start  + : " << start << std::endl;
	std::cerr << " + stop  + : " << stop << std::endl;
#endif
	m_indexes.clear();
	for(std::int64_t i = start; (i < stop && step > 0) || (i > stop && step < 0); i += step) {
		m_indexes.push_back(weak_cast<std::size_t>(i));
	}
#if COCONUT_DEBUG
	for (const auto & idx : m_indexes) {
		std::cerr << " + idx  + : " << idx << std::endl;
	}
#endif
}

#pragma mark -

islice::iterator islice::begin() { return m_indexes.begin(); }
islice::iterator islice::end() { return m_indexes.end(); }

islice::const_iterator islice::begin() const { return m_indexes.begin(); }
islice::const_iterator islice::end() const { return m_indexes.end(); }

islice::const_iterator islice::cbegin() const { return m_indexes.cbegin(); }
islice::const_iterator islice::cend() const { return m_indexes.cend(); }

islice::reverse_iterator islice::rbegin() { return m_indexes.rbegin(); }
islice::reverse_iterator islice::rend() { return m_indexes.rend(); }

islice::const_reverse_iterator islice::rbegin() const { return m_indexes.rbegin(); }
islice::const_reverse_iterator islice::rend() const { return m_indexes.rend(); }

islice::const_reverse_iterator islice::crbegin() const { return m_indexes.crbegin(); }
islice::const_reverse_iterator islice::crend() const { return m_indexes.crend(); }

/* EOF */