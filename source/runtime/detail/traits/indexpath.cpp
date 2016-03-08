//
// indexpath.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/traits/indexpath.hpp>
#include <coconut/runtime/detail/core/stream.hpp>

using namespace coconut::runtime;

indexpath::indexpath() :
	m_indexes()
{ /* NOP */ }

indexpath::indexpath(const indexpath & idxpath) :
	m_indexes(idxpath.cbegin(), idxpath.cend())
{ /* NOP */ }

indexpath::indexpath(std::size_t index) :
	m_indexes()
{ m_indexes.push_back(index); }

indexpath::indexpath(std::size_t * indexes, std::size_t length) :
	m_indexes()
{
	for(std::size_t i = 0; i < length; i++) {
		m_indexes.push_back(indexes[i]);
	}
}

indexpath::indexpath(const std::vector<std::size_t> & indexes) :
	m_indexes(indexes.cbegin(), indexes.cend())
{ /* NOP */ }

indexpath::indexpath(const std::vector<std::size_t> & indexes, std::size_t numitems) :
	m_indexes()
{
	std::size_t length = numitems;
	if (length > indexes.size()) {
		length = indexes.size();
	}
	for(std::size_t i = 0; i < length; i++) {
		m_indexes.push_back(indexes[i]);
	}
}

indexpath::~indexpath()
{ /* NOP */ }

#pragma mark -

indexpath & indexpath::operator = (const indexpath & idxpath)
{
	if (this == &idxpath) {
		return *this;
	}
	m_indexes.assign(idxpath.m_indexes.cbegin(), idxpath.m_indexes.cend());
	return *this;
}

#pragma mark -

int indexpath::compare(const indexpath & other_idxpath) const
{
	if (this == &other_idxpath) {
		return cmp_same;
	}
	
	if (m_indexes.size() < other_idxpath.m_indexes.size()) {
		return cmp_ascending;
	} else if (m_indexes.size() > other_idxpath.m_indexes.size()) {
		return cmp_descending;
	} else if (std::equal(
		m_indexes.begin(),
		m_indexes.end(),
		other_idxpath.m_indexes.begin()
	)) {
		return cmp_same;
	}
	return cmp_descending;
}

#pragma mark -

std::size_t indexpath::index_at(std::size_t position) const
{
	if (m_indexes.size() && position < m_indexes.size()) {
		return m_indexes[position];
	}
	return NotFound;
}

#pragma mark -

const std::vector<std::size_t> indexpath::indexes() const
{
	return m_indexes;
}

const std::size_t * indexpath::raw() const
{
	return m_indexes.data();
}

#pragma mark -

indexpath indexpath::by_adding(std::size_t index) const
{
	std::vector<std::size_t> buf;
	if (m_indexes.size()) {
		buf.assign(m_indexes.cbegin(), m_indexes.cend());
	}
	buf.push_back(index);
	indexpath idxpath(buf.cbegin(), buf.cend());
	return idxpath;
}

indexpath indexpath::by_removing_last() const
{
	std::vector<std::size_t> buf;
	if (m_indexes.size()) {
		buf.assign(m_indexes.cbegin(), m_indexes.cend());
		buf.pop_back();
	}
	indexpath idxpath(buf.cbegin(), buf.cend());
	return idxpath;
}

#pragma mark -

std::size_t indexpath::size() const
{ return m_indexes.size(); }

#pragma mark -

std::string indexpath::to_string() const
{
	std::ostringstream oss;
	if (m_indexes.size()) {
		std::copy(m_indexes.cbegin(), m_indexes.cend() -1, std::ostream_iterator<std::size_t>(oss, ", "));
		oss << m_indexes.back();
	}
	return "[" + oss.str() + "]";
}

std::size_t indexpath::hash_code() const
{ return std::hash<std::string>()(to_string()); }

#pragma mark -

indexpath::iterator indexpath::begin() { return m_indexes.begin(); }
indexpath::iterator indexpath::end() { return m_indexes.end(); }

indexpath::const_iterator indexpath::begin() const { return m_indexes.begin(); }
indexpath::const_iterator indexpath::end() const { return m_indexes.end(); }

indexpath::const_iterator indexpath::cbegin() const { return m_indexes.cbegin(); }
indexpath::const_iterator indexpath::cend() const { return m_indexes.cend(); }

indexpath::reverse_iterator indexpath::rbegin() { return m_indexes.rbegin(); }
indexpath::reverse_iterator indexpath::rend() { return m_indexes.rend(); }

indexpath::const_reverse_iterator indexpath::rbegin() const { return m_indexes.rbegin(); }
indexpath::const_reverse_iterator indexpath::rend() const { return m_indexes.rend(); }

indexpath::const_reverse_iterator indexpath::crbegin() const { return m_indexes.crbegin(); }
indexpath::const_reverse_iterator indexpath::crend() const { return m_indexes.crend(); }

/* EOF */