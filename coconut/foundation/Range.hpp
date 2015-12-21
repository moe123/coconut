//
// Range.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_RANGE_HPP
#define COCONUT_FOUNDATION_RANGE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT Range : public Object
	{
	COCONUT_KDCL(coconut.Range, Object.Range)
		
	public:
		Range();
		Range(const Range & rg);
		Range & operator = (const Range & rg) = default;
		Range(std::size_t location, std::size_t length);
		virtual ~Range();
		
		COCONUT_KTOR RangePtr with();
		COCONUT_KTOR RangePtr with(const Range & rg);
		COCONUT_KTOR RangePtr with(std::size_t location, std::size_t length);
		
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

	public:
		friend inline std::ostream & operator << (std::ostream & os, const RangePtr ptr)
		{ if (ptr) { os << ptr->stringValue(); } return os; }
		
	protected:
		friend class Path;
		friend class String;
		
	protected:
		typedef runtime::irange impl_type;

	public:
		typedef impl_type::iterator iterator;
		typedef impl_type::const_iterator const_iterator;
		
		typedef impl_type::reverse_iterator reverse_iterator;
		typedef impl_type::const_reverse_iterator const_reverse_iterator;
		
		typedef impl_type::value_type value_type;
		typedef impl_type::size_type size_type;
		typedef impl_type::difference_type difference_type;
	
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
		impl_type m_impl;
	};
	
	COCONUT_EXPORT
	bool EqualRanges(const Range & rg1, const Range & rg2);
	
	COCONUT_EXPORT
	Range IntersectionRange(const Range & rg1, const Range & rg2);
	
	COCONUT_EXPORT
	bool LocationInRange(std::size_t location, const Range & rg);
	
	COCONUT_EXPORT
	Range MakeRange(std::size_t location, std::size_t length);
	
	COCONUT_EXPORT
	std::size_t MaxRange(const Range & rg);
	
	COCONUT_EXPORT
	Range UnionRange(const Range & rg1, const Range & rg2);
}

#endif /* !COCONUT_FOUNDATION_RANGE_HPP */

/* EOF */