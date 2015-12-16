//
// SortDescriptor.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_SORTDESCRIPTOR_HPP
#define COCONUT_FOUNDATION_SORTDESCRIPTOR_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_EXPORT SortDescriptor : public Object
	{
	COCONUT_KDCL(coconut.SortDescriptor, Object.SortDescriptor)
		
	public:
		SortDescriptor();
		SortDescriptor(const SortDescriptor & sdr);
		SortDescriptor & operator = (const SortDescriptor & sdr) = default;
		
		SortDescriptor(SortDescriptor && sdr);
		
		SortDescriptor(const String & key, bool isasc = true);
		SortDescriptor(const String & key, const String & selkey, bool isasc = true);
		
		virtual ~SortDescriptor();
		
		COCONUT_KTOR SortDescriptorPtr with();
		
		COCONUT_KTOR SortDescriptorPtr with(const SortDescriptor & sdr);
		COCONUT_KTOR SortDescriptorPtr with(SortDescriptor && sdr);
		COCONUT_KTOR SortDescriptorPtr with(const String & key, bool isasc = true);
		COCONUT_KTOR SortDescriptorPtr with(const String & key, const String & selkey, bool isasc = true);
		
		virtual kind_ptr copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const_kind_ref ref) const
		COCONUT_FINAL_OVERRIDE;
		
		ComparisonResult compareObject(const_kind_ptr & a, const_kind_ptr & b) const;
		
		const SortDescriptor reversedSortDescriptor();
		
		const String key() const;
		const String selectorKey() const;
		bool ascending() const;
		
	protected:
		typedef std::tuple<std::string, std::string, bool> impl_type;
		
	private:
		impl_type m_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_SORTDESCRIPTOR_HPP */

/* EOF */