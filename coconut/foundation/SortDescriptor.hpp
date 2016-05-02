//
// SortDescriptor.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_SORTDESCRIPTOR_HPP
#define COCONUT_FOUNDATION_SORTDESCRIPTOR_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE SortDescriptor COCONUT_FINAL : public Object
	{
	COCONUT_CLASSDECLARE(coconut.SortDescriptor, Object.SortDescriptor)
		
	public:
		SortDescriptor();
		SortDescriptor(const SortDescriptor & sdr);
		SortDescriptor & operator = (const SortDescriptor & sdr) = default;
		SortDescriptor(SortDescriptor && sdr) noexcept;
		SortDescriptor(const String & key, bool isasc = true);
		SortDescriptor(const String & key, const String & selkey, bool isasc = true);
		virtual ~SortDescriptor();
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		ComparisonResult compareObject(const Any & a, const Any & b) const;
		
		const SortDescriptor reversedSortDescriptor();
		
		const String key() const;
		const String selectorKey() const;
		bool ascending() const;
		
	protected:
		typedef std::tuple<std::string, std::string, bool> impl_trait;
		
	private:
		impl_trait m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_SORTDESCRIPTOR_HPP */

/* EOF */