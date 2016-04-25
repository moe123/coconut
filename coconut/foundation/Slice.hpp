//
// Slice.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_SLICE_HPP
#define COCONUT_FOUNDATION_SLICE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Slice : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Slice, Object.Slice)
		
	public:
		Slice();
		Slice(const Slice & slc);
		Slice & operator = (const Slice & slc) = default;
		Slice(std::int64_t start, std::int64_t stop);
		Slice(std::int64_t start, std::int64_t stop, std::int64_t step);
		Slice(const Range & rg);
		virtual ~Slice();
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		std::int64_t start() const;
		std::int64_t stop() const;
		std::int64_t step() const;
		
		void indexesForLength(std::size_t length) const;

	protected:
		typedef runtime::traits::islice impl_trait;
		
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
}

#endif /* !COCONUT_FOUNDATION_SLICE_HPP */

/* EOF */