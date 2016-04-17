//
// IndexPath.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_DATE_HPP
#define COCONUT_FOUNDATION_DATE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE IndexPath : public Object
	{
	COCONUT_CLASSDECLARE(coconut.IndexPath, Object.IndexPath)
		
	public:
		IndexPath();
		IndexPath(const IndexPath & idxp);
		IndexPath & operator = (const IndexPath & idxp) = default;
		IndexPath(IndexPath && idxp) noexcept;
		IndexPath(const std::initializer_list<std::size_t> & args);
		IndexPath(std::size_t index);
		
		template <typename IterT>
		IndexPath(IterT && beg, IterT && end) :
			m_impl(std::forward<IterT>(beg), std::forward<IterT>(end))
		{ /* NOP */ }
		
		virtual ~IndexPath();

		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
		
		std::size_t indexAtPosition(std::size_t node) const;
		
		const IndexPath indexPathByAddingIndex(std::size_t index) const;
		const IndexPath indexPathByRemovingLastIndex() const;
		
		bool getIndexes(std::vector<std::size_t> & indexes) const;
		
	public:
		typedef runtime::traits::indexpath impl_trait;

	public:
		typedef impl_trait::iterator iterator;
		typedef impl_trait::const_iterator const_iterator;
		
		typedef impl_trait::reverse_iterator reverse_iterator;
		typedef impl_trait::const_reverse_iterator const_reverse_iterator;
		
		typedef impl_trait::value_type value_type;
		typedef impl_trait::size_type size_type;
		typedef impl_trait::difference_type difference_type;
		
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
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_DATE_HPP */

/* EOF */