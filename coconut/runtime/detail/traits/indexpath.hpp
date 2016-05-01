//
// indexpath.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_INDEXPATH_HPP
#define COCONUT_RUNTIME_INDEXPATH_HPP

namespace coconut {
	namespace runtime {
		namespace traits {
	
COCONUT_PRIVATE class COCONUT_VISIBLE indexpath COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.indexpath, indexpath)
	
public:
	indexpath();
	indexpath(const indexpath & idxpath);
	indexpath(indexpath && idxpath) noexcept;
	indexpath(std::size_t index);
	indexpath(std::size_t * indexes, std::size_t length);
	indexpath(const std::vector<std::size_t> & indexes);
	indexpath(const std::vector<std::size_t> & indexes, std::size_t numitems);
	
	template <typename IterT>
	indexpath(IterT && beg, IterT && end)
	: m_indexes(std::forward<IterT>(beg), std::forward<IterT>(end))
	{ /* NOP */ }
	
	~indexpath();

public:
	indexpath & operator = (const indexpath & idxpath);
	int compare(const indexpath & other_idxpath) const;
	
	std::size_t index_at(std::size_t position) const;
	const std::vector<std::size_t> indexes() const;
	const std::size_t * raw() const;
	
	indexpath by_adding(std::size_t index) const;
	indexpath by_removing_last() const;
	
	std::size_t size() const;
	
	std::string to_string() const;
	std::size_t hash_code() const;

public:
	typedef std::vector<std::size_t>::iterator iterator;
	typedef std::vector<std::size_t>::const_iterator const_iterator;
	
	typedef std::vector<std::size_t>::reverse_iterator reverse_iterator;
	typedef std::vector<std::size_t>::const_reverse_iterator const_reverse_iterator;
	
	typedef std::vector<std::size_t>::value_type value_type;
	typedef std::vector<std::size_t>::size_type size_type;
	typedef std::vector<std::size_t>::difference_type difference_type;

public:
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
	std::vector<std::size_t> m_indexes;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_INDEXPATH_HPP */

/* EOF */