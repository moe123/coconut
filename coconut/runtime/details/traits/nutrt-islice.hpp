//
// nutrt-islice.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_ISLICE_HPP
#define COCONUT_RUNTIME_ISLICE_HPP

namespace coconut
{ namespace runtime
{ namespace traits
{

COCONUT_PRIVATE class COCONUT_VISIBLE islice COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.islice, islice)
	
public:
	islice();
	islice(const islice & slc);
	islice(islice && slc) noexcept;
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
	
	void do_indexes(std::size_t forlen) const;
	
	std::string to_string() const;

private:
	typedef std::vector<std::size_t> container_type;
	
public:
	/* type_traits */
	
	typedef container_type::iterator iterator;
	typedef container_type::const_iterator const_iterator;
	
	typedef container_type::reverse_iterator reverse_iterator;
	typedef container_type::const_reverse_iterator const_reverse_iterator;
	
	typedef container_type::value_type value_type;
	typedef container_type::size_type size_type;
	typedef container_type::difference_type difference_type;
	
	typedef container_type::reference reference;
	typedef container_type::const_reference const_reference;
	typedef container_type::pointer pointer;
	typedef container_type::const_pointer const_pointer;
	
public:
	/* type_iterator */
	
	iterator begin();
	iterator end();
	
	const_iterator begin() const;
	const_iterator end() const;
	
	const_iterator cbegin() const;
	const_iterator cend() const;
	
	reverse_iterator rbegin();
	reverse_iterator rend();
	
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;
	
private:
	mutable container_type m_indexes;
	std::int64_t m_start;
	std::int64_t m_stop;
	std::int64_t m_step;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ISLICE_HPP */

/* EOF */