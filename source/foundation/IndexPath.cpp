//
// IndexPath.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/foundation/IndexPath.hpp>

using namespace coconut;

IndexPath::IndexPath() :
	Object(IndexPathClass),
	m_impl()
{ /* NOP */ }

IndexPath::IndexPath(const IndexPath & idxp) :
	Object(IndexPathClass),
	m_impl(idxp.m_impl)
{ /* NOP */ }

IndexPath::IndexPath(IndexPath && idxp) :
	Object(IndexPathClass),
	m_impl(std::move(idxp.m_impl))
{ /* NOP */ }

IndexPath::IndexPath(const std::initializer_list<std::size_t> & args) :
	Object(IndexPathClass),
	m_impl(args.begin(), args.end())
{ /* NOP */ }

IndexPath::IndexPath(std::size_t index) :
	Object(IndexPathClass),
	m_impl(index)
{ /* NOP */ }

IndexPath::~IndexPath()
{ /* NOP */ }

#pragma mark -

Owning<IndexPath> IndexPath::with()
{ return ptr_create<IndexPath>(); }
		   
Owning<IndexPath> IndexPath::with(const IndexPath & idxp)
{ return ptr_create<IndexPath>(idxp); }

Owning<IndexPath> IndexPath::with(const std::initializer_list<std::size_t> & args)
{ return ptr_create<IndexPath>(args); }
		   
Owning<IndexPath> IndexPath::with(std::size_t index)
{ return ptr_create<IndexPath>(index); }

#pragma mark -

std::size_t IndexPath::hash() const
{ return m_impl.hash_code(); }

#pragma mark -

Owning<Any> IndexPath::copy() const
{ return ptr_create<IndexPath>(*this); }

#pragma mark -

ComparisonResult IndexPath::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return m_impl.compare(ref_cast<IndexPath>(ref).m_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string IndexPath::stringValue() const
{ return m_impl.to_string(); }

#pragma mark -

std::size_t IndexPath::size() const
{ return m_impl.size(); }

#pragma mark -

std::size_t IndexPath::indexAtPosition(std::size_t node) const
{ return m_impl.index_at(node); }

#pragma mark -

const IndexPath IndexPath::indexPathByAddingIndex(std::size_t index) const
{
	IndexPath idxp;
	idxp.m_impl = m_impl.by_adding(index);
	return idxp;
}

const IndexPath IndexPath::indexPathByRemovingLastIndex() const
{
	IndexPath idxp;
	idxp.m_impl = m_impl.by_removing_last();
	return idxp;
}

#pragma mark -

bool IndexPath::getIndexes(std::vector<std::size_t> & indexes) const
{
	indexes.assign(m_impl.cbegin(), m_impl.cend());
	return (indexes.size() > 0);
}

#pragma mark -

IndexPath::iterator IndexPath::begin() { return m_impl.begin(); }
IndexPath::iterator IndexPath::end() { return m_impl.end(); }

IndexPath::const_iterator IndexPath::begin() const { return m_impl.begin(); }
IndexPath::const_iterator IndexPath::end() const { return m_impl.end(); }

IndexPath::const_iterator IndexPath::cbegin() const { return m_impl.cbegin(); }
IndexPath::const_iterator IndexPath::cend() const { return m_impl.cend(); }

IndexPath::reverse_iterator IndexPath::rbegin() { return m_impl.rbegin(); }
IndexPath::reverse_iterator IndexPath::rend() { return m_impl.rend(); }

IndexPath::const_reverse_iterator IndexPath::rbegin() const { return m_impl.rbegin(); }
IndexPath::const_reverse_iterator IndexPath::rend() const { return m_impl.rend(); }

IndexPath::const_reverse_iterator IndexPath::crbegin() const { return m_impl.crbegin(); }
IndexPath::const_reverse_iterator IndexPath::crend() const { return m_impl.crend(); }

/* EOF */