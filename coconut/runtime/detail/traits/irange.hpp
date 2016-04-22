//
// irange.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>
#include <coconut/runtime/detail/core/iterators.hpp>

#ifndef COCONUT_RUNTIME_IRANGE_HPP
#define COCONUT_RUNTIME_IRANGE_HPP

namespace coconut {
	namespace runtime {
		namespace traits {

COCONUT_PRIVATE class COCONUT_VISIBLE irange COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.irange, irange)
	
public:
	irange();
	irange(const irange & rg);
	irange(const std::string & rg_string);
	irange(std::size_t location, std::size_t length);
	~irange();

public:
	irange & operator = (const irange & rg);
	int compare(const irange & other_rg) const;
	
	std::size_t location() const;
	std::size_t length() const;
	
	void set_location(std::size_t location);
	void set_length(std::size_t length);
	
	bool iszero() const;
	std::size_t max() const;
	
	bool in(std::size_t location) const;
	const irange intxn(const irange & other_rg) const;
	const irange merge(const irange & other_rg) const;
	
	std::string to_string() const;

private:
	typedef iterators::range_adv_facet<std::size_t, irange> iter_adv_facet;
	typedef const iterators::range_adv_facet<std::size_t, irange> const_iter_adv_facet;
	
	typedef iterators::range_rev_facet<std::size_t, irange> iter_rev_facet;
	typedef const iterators::range_rev_facet<std::size_t, irange> const_iter_rev_facet;

public:
	typedef iter_adv_facet iterator;
	typedef const_iter_adv_facet const_iterator;
	
	typedef iter_rev_facet reverse_iterator;
	typedef const_iter_rev_facet const_reverse_iterator;

	typedef std::size_t value_type;
	typedef std::size_t size_type;
	typedef std::size_t difference_type;
	
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
	std::size_t m_loc;
	std::size_t m_len;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_IRANGE_HPP */

/* EOF */