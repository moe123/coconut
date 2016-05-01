
//
// iterators.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/defines.hpp>

#ifndef COCONUT_RUNTIME_ITERATOR_HPP
#define COCONUT_RUNTIME_ITERATOR_HPP

namespace coconut {
	namespace runtime {
		namespace iterators {

template <class MapT>
COCONUT_PRIVATE class key_map_facet : public MapT::iterator
{
public:
	typedef typename MapT::iterator facet;
	typedef typename facet::value_type::first_type key_type;
	
public:
	key_map_facet(const facet & other_it) : MapT::iterator(other_it) { /* NOP */ } ;
	key_type & operator * () const { return MapT::iterator::operator*().first; }
};

template <class MapT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
key_map_facet<MapT> key_begin(MapT & m)
{ return key_map_facet<MapT>(m.begin()); }

template <class MapT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
key_map_facet<MapT> key_end(MapT & m)
{ return key_map_facet<MapT>(m.end()); }

template <class MapT>
COCONUT_PRIVATE class value_map_facet : public MapT::iterator
{
public:
	typedef typename MapT::iterator facet;
	typedef typename facet::value_type::second_type value_type;
	
public:
	value_map_facet(const facet & other_it) : MapT::iterator(other_it) { /* NOP */ } ;
	value_type & operator * () const { return MapT::iterator::operator*().second; }
};

template <class MapT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
value_map_facet<MapT> value_begin(MapT & m)
{ return value_map_facet<MapT>(m.begin()); }

template <class MapT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
value_map_facet<MapT> value_end(MapT & m)
{ return value_map_facet<MapT>(m.end()); }

template <typename ItemT, class FriendT,
	typename std::enable_if<
		std::numeric_limits<ItemT>::is_integer
	>::type* = nullptr
>
COCONUT_PRIVATE class range_facet
{
friend FriendT;
	
protected:
	typedef range_facet<ItemT, FriendT> facet;
	typedef const range_facet<ItemT, FriendT> const_facet;
	typedef ItemT value_type;
	typedef ItemT size_type;
	typedef std::ptrdiff_t difference_type;
	
protected:
	range_facet(value_type beg) : m_val (beg) { /* NOP */ }
	
public:
	value_type & operator * () { return m_val; }
	value_type operator * () const { return m_val; }
	
	value_type * operator -> () const { return &(operator*()); }
	
	const_facet & operator ++ () noexcept { ++m_val; return *this; }
	facet operator ++ (int) noexcept { facet cpy(*this); ++m_val; return cpy; }
	
	const_facet & operator -- () noexcept { --m_val; return *this; }
	facet operator -- (int) noexcept { facet cpy(*this); --m_val; return cpy; }
	
	facet operator + (value_type n) const noexcept { return facet(m_val + n); }
	const_facet & operator += (value_type n) noexcept { m_val += n; return *this; }
	
	facet operator - (value_type n) const noexcept { return facet(m_val -n); }
	const_facet & operator -= (value_type n) noexcept { m_val -= n; return *this; }
	
	bool operator == (const_facet & other_it) const noexcept { return m_val == other_it.m_val; }
	bool operator != (const_facet & other_it) const noexcept { return m_val != other_it.m_val; }
	
private:
	value_type m_val;
};

template <typename ItemT, class FriendT,
	typename std::enable_if<
		std::numeric_limits<ItemT>::is_integer
	>::type* = nullptr
>
COCONUT_PRIVATE class range_rfacet
{
friend FriendT;
	
protected:
	typedef range_rfacet<ItemT, FriendT> facet;
	typedef const range_rfacet<ItemT, FriendT> const_facet;
	typedef ItemT value_type;
	typedef ItemT size_type;
	typedef std::ptrdiff_t difference_type;
	
protected:
	range_rfacet(value_type beg) : m_val (beg) { /* NOP */ }
	
public:
	value_type & operator * () { value_type cpy = m_val; return --cpy; }
	value_type operator * () const { value_type cpy = m_val; return --cpy; }
	
	value_type * operator -> () const { return &(operator*()); }
	
	const_facet & operator ++ () noexcept { --m_val; return *this; }
	facet operator ++ (int) noexcept { facet cpy(*this); --m_val; return cpy; }
	
	const_facet & operator -- () noexcept { ++m_val; return *this; }
	facet operator -- (int) noexcept { facet cpy(*this); ++m_val; return cpy; }
	
	facet operator + (value_type n) const noexcept { return facet(m_val - n); }
	const_facet & operator += (value_type n) noexcept { m_val -= n; return *this; }
	
	facet operator - (value_type n) const noexcept { return facet(m_val + n); }
	const_facet & operator -= (value_type n) { m_val += n; return *this; }
	
	bool operator == (const_facet & other_it) const noexcept { return m_val == other_it.m_val; }
	bool operator != (const_facet & other_it) const noexcept { return m_val != other_it.m_val; }
	
private:
	value_type m_val;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ITERATOR_HPP */

/* EOF */