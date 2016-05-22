//
// nutrt-indexset.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>
#include <coconut/runtime/details/nutrt-allocators.hpp>

#ifndef COCONUT_RUNTIME_INDEXSET_HPP
#define COCONUT_RUNTIME_INDEXSET_HPP

namespace coconut
{ namespace runtime
{ namespace traits
{

COCONUT_CLASSFORWARD_DCL(irange)
		
COCONUT_PRIVATE class COCONUT_VISIBLE indexset COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.indexset, indexset)
	
public:
	indexset();
	indexset(const indexset & idxset);
	indexset(const irange & rg);
	indexset(std::size_t loc, std::size_t len);
	indexset(std::size_t idx);
	~indexset();

private:
	COCONUT_CLASSMETHOD std::size_t pos_greater_eq_loc(const std::vector<irange> & rgs, std::size_t location);
	COCONUT_CLASSMETHOD std::size_t pos_greater_less_loc(const std::vector<irange> & rgs, std::size_t location);
	COCONUT_CLASSMETHOD void remove_range_at_pos(std::vector<irange> & rgs, std::size_t position);
	COCONUT_CLASSMETHOD void insert_range_at_pos(std::vector<irange> & rgs, const irange & rg, std::size_t position);
	COCONUT_CLASSMETHOD std::size_t find_pos_for_index(const std::vector<irange> & rgs, std::size_t index);
	
public:
	indexset & operator = (const indexset & idxset);
	int compare(const indexset & other_idxset) const;
	
	std::string to_string() const;
	
	std::size_t count() const;
	std::size_t count_in(const irange & rg) const;
	std::size_t count_in(std::size_t loc, std::size_t len) const;
	
	bool contains(const indexset & idxset) const;
	bool contains(const irange & rg) const;
	bool contains(std::size_t loc, std::size_t len) const;
	bool contains(std::size_t idx = 0) const;
	
	std::size_t first_index() const;
	std::size_t last_index() const;
	
	std::size_t greater(std::size_t idx = 0) const;
	std::size_t greater_equal(std::size_t idx = 0) const;
	std::size_t less(std::size_t idx = 0) const;
	std::size_t less_equal(std::size_t idx = 0) const;
	
	bool intersects(const irange & rg) const;
	bool intersects(std::size_t loc, std::size_t len) const;
	
	void add(const indexset & idxset);
	void add(const irange & rg);
	void add(std::size_t loc, std::size_t len);
	void add(std::size_t idx = 0);
	
	void remove();
	void remove(const indexset & idxset);
	void remove(const irange & rg);
	void remove(std::size_t loc, std::size_t len);
	void remove(std::size_t idx = 0);

private:
	/* private traits */
	
	using item_type = irange;
	using this_type = indexset;
	
	typedef std::vector<item_type> container_type;
	
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
	
	typedef allocators::builtins<this_type> allocator_type;
	
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
	std::size_t m_len;
	container_type m_ranges;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_INDEXSET_HPP */

/* EOF */