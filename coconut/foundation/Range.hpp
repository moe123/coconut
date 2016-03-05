//
// Range.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_RANGE_HPP
#define COCONUT_FOUNDATION_RANGE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Range : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Range, Object.Range)
		
	public:
		Range();
		Range(const Range & rg);
		Range & operator = (const Range & rg) = default;
		Range(std::size_t location, std::size_t length);
		virtual ~Range();
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> mutableCopy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		std::size_t location() const;
		std::size_t length() const;
		
		bool isZeroRange() const;
		
		std::size_t maxRange() const;
		
		bool locationInRange(std::size_t location) const;
		const Range intersectionRange(const Range & other_rg) const;
		const Range unionRange(const Range & other_rg) const;
		
	protected:
		friend class Path;
		friend class String;
		
	protected:
		typedef runtime::irange impl_trait;

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

	protected:
		impl_trait m_impl;
	};
	
	COCONUT_VISIBLE
	bool EqualRanges(const Range & rg1, const Range & rg2);
	
	COCONUT_VISIBLE
	Range IntersectionRange(const Range & rg1, const Range & rg2);
	
	COCONUT_VISIBLE
	bool LocationInRange(std::size_t location, const Range & rg);
	
	COCONUT_VISIBLE
	Range MakeRange(std::size_t location, std::size_t length);
	
	COCONUT_VISIBLE
	std::size_t MaxRange(const Range & rg);
	
	COCONUT_VISIBLE
	Range UnionRange(const Range & rg1, const Range & rg2);
}

#endif /* !COCONUT_FOUNDATION_RANGE_HPP */

/* EOF */