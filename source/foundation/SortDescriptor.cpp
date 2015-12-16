//
// SortDescriptor.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/foundation/SortDescriptor.hpp>
#include <coconut/foundation/None.hpp>
#include <coconut/foundation/Number.hpp>
#include <coconut/foundation/String.hpp>

using namespace coconut;

SortDescriptor::SortDescriptor() :
	Object(SortDescriptorClass),
	m_impl{ u8"<none>", u8"<none>", true }
{ /* NOP */ }

SortDescriptor::SortDescriptor(const SortDescriptor & sdr) :
	Object(SortDescriptorClass),
	m_impl(sdr.m_impl)
{ /* NOP */ }

SortDescriptor::SortDescriptor(SortDescriptor && sdr) :
	Object(SortDescriptorClass),
	m_impl(std::move(sdr.m_impl))
{ /* NOP */ }

SortDescriptor::SortDescriptor(const String & key, bool isasc) :
	Object(SortDescriptorClass),
	m_impl{ key.stringValue(), u8"@compare:", isasc }
{ /* NOP */ }

SortDescriptor::SortDescriptor(const String & key, const String & selkey, bool isasc) :
	Object(SortDescriptorClass),
	m_impl{ key.stringValue(), selkey.stringValue(), isasc }
{ /* NOP */ }

SortDescriptor::~SortDescriptor()
{ /* NOP */ }

#pragma mark -

SortDescriptorPtr SortDescriptor::with()
{ return ptr_create<SortDescriptor>(); }

SortDescriptorPtr SortDescriptor::with(const SortDescriptor & sdr)
{ return ptr_create<SortDescriptor>(sdr); }

SortDescriptorPtr SortDescriptor::with(SortDescriptor && sdr)
{ return ptr_create<SortDescriptor>(std::move(sdr)); }

SortDescriptorPtr SortDescriptor::with(const String & key, bool isasc)
{ return ptr_create<SortDescriptor>(key, isasc); }

SortDescriptorPtr SortDescriptor::with(const String & key, const String & selkey, bool isasc)
{ return ptr_create<SortDescriptor>(key, selkey, isasc); }

#pragma mark -

kind_ptr SortDescriptor::copy() const
{ return ptr_create<SortDescriptor>(*this); }

#pragma mark -

ComparisonResult SortDescriptor::compare(const_kind_ref ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		std::string binL = std::get<0>(m_impl);
					binL += std::get<1>(m_impl);
					binL += std::get<2>(m_impl);
		
		std::string binR = std::get<0>(ref_cast<SortDescriptor>(ref).m_impl);
					binR += std::get<1>(ref_cast<SortDescriptor>(ref).m_impl);
					binR += std::get<2>(ref_cast<SortDescriptor>(ref).m_impl);
		
		return runtime::algorithm::icmp(binL, binR);
	}
	return OrderedDescending;
}

#pragma mark -

ComparisonResult SortDescriptor::compareObject(const_kind_ptr & a, const_kind_ptr & b) const
{
	if (a && b) {
		kind_ptr aa = a->valueForKeyPath(std::get<0>(m_impl));
		kind_ptr bb = b->valueForKeyPath(std::get<0>(m_impl));
		if (aa && bb) {
			if (std::get<2>(m_impl)) {
				if (std::get<1>(m_impl) != u8"@compare:") {
					kind_ptr sel_cmp = aa->valueForSelectorKey(std::get<1>(m_impl), bb);
					return sel_cmp ? sel_cmp->intValue() : aa->compare(*bb);
				}
				return aa->compare(*bb);
			} else {
				if (std::get<1>(m_impl) != u8"@compare:") {
					kind_ptr sel_cmp = bb->valueForSelectorKey(std::get<1>(m_impl), aa);
					return sel_cmp ? sel_cmp->intValue() : bb->compare(*aa);
				}
				return bb->compare(*aa);
			}
		}
	}
	return OrderedDescending;
}

#pragma mark -

const SortDescriptor SortDescriptor::reversedSortDescriptor()
{ return SortDescriptor(std::get<0>(m_impl), std::get<1>(m_impl), !std::get<2>(m_impl)); }

#pragma mark -

const String SortDescriptor::key() const
{ return String(std::get<0>(m_impl)); }

const String SortDescriptor::selectorKey() const
{ return String(std::get<1>(m_impl)); }

bool SortDescriptor::ascending() const
{ return std::get<2>(m_impl); }

/* EOF */