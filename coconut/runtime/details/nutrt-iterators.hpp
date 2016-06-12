//
// nutrt-iterators.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_ITERATORS_HPP
#define COCONUT_RUNTIME_ITERATORS_HPP

namespace coconut
{ namespace runtime
{ namespace iterators
{

template <class MapT>
COCONUT_PRIVATE class COCONUT_VISIBLE key_map_facet COCONUT_FINAL : public MapT::iterator
{
public:
	typedef typename MapT::iterator facet;
	typedef const facet const_facet;
	typedef typename facet::value_type::first_type key_type;
	
public:
	key_map_facet(const_facet & other_it) : MapT::iterator(other_it) { /* NOP */ } ;
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
COCONUT_PRIVATE class COCONUT_VISIBLE value_map_facet COCONUT_FINAL : public MapT::iterator
{
public:
	typedef typename MapT::iterator facet;
	typedef const facet const_facet;
	typedef typename facet::value_type::second_type value_type;
	
public:
	value_map_facet(const_facet & other_it) : MapT::iterator(other_it) { /* NOP */ } ;
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

template <class T>
COCONUT_PRIVATE struct COCONUT_VISIBLE integer_facet_traits COCONUT_FINAL : type_traits<T>
{ typedef std::random_access_iterator_tag iterator_category; };
	
template <typename ItemT, class FriendT
	, typename Traits = integer_facet_traits<ItemT>
	, typename std::enable_if<
		std::numeric_limits<ItemT>::is_integer
	>::type* = nullptr
>
COCONUT_PRIVATE class COCONUT_VISIBLE integer_facet COCONUT_FINAL
{
friend FriendT;
	
protected:
	typedef integer_facet<ItemT, FriendT> this_type;
	typedef const this_type const_this_type;
	typedef Traits traits_type;
	
	typedef typename traits_type::value_type value_type;
	typedef typename traits_type::size_type size_type;
	typedef typename traits_type::difference_type difference_type;
	
	typedef typename traits_type::reference reference;
	typedef typename traits_type::const_reference const_reference;
	typedef typename traits_type::pointer pointer;
	typedef typename traits_type::const_pointer const_pointer;
	
	typedef typename traits_type::iterator_category iterator_category;
	
protected:
	integer_facet(const_reference first) : m_offset(first) { /* NOP */ }
	
public:
	reference operator * () { return m_offset; }
	const_reference operator * () const { return m_offset; }
	
	pointer operator -> () const { return &(operator*()); }
	
	const_this_type & operator ++ () noexcept { ++m_offset; return *this; }
	this_type operator ++ (int) noexcept { this_type cpy(*this); ++m_offset; return cpy; }
	
	const_this_type & operator -- () noexcept { --m_offset; return *this; }
	this_type operator -- (int) noexcept { this_type cpy(*this); --m_offset; return cpy; }
	
	this_type operator + (value_type n) const noexcept { return facet(m_offset + n); }
	const_this_type & operator += (value_type n) noexcept { m_offset += n; return *this; }
	
	this_type operator - (value_type n) const noexcept { return facet(m_offset -n); }
	const_this_type & operator -= (value_type n) noexcept { m_offset -= n; return *this; }
	
	bool operator == (const_this_type & other_it) const noexcept { return m_offset == other_it.m_offset; }
	bool operator != (const_this_type & other_it) const noexcept { return m_offset != other_it.m_offset; }
	
	operator this_type() const { return const_this_type(m_offset); }
	operator const_this_type() const { return const_this_type(m_offset); }
	
private:
	value_type m_offset;
};
	
template <typename ItemT, class FriendT
	, typename traits_type = integer_facet_traits<ItemT>
	, typename std::enable_if<
		std::numeric_limits<ItemT>::is_integer
	>::type* = nullptr
>
using const_integer_facet = typename integer_facet<ItemT, FriendT, traits_type>::const_this_type;

template <typename ItemT, class FriendT
	, typename Traits = integer_facet_traits<ItemT>
	, typename std::enable_if<
		std::numeric_limits<ItemT>::is_integer
	>::type* = nullptr
>
COCONUT_PRIVATE class COCONUT_VISIBLE integer_reverse_facet COCONUT_FINAL
{
friend FriendT;
	
protected:
	typedef integer_reverse_facet<ItemT, FriendT> this_type;
	typedef const this_type const_this_type;
	typedef Traits traits_type;
	
	typedef typename traits_type::value_type value_type;
	typedef typename traits_type::size_type size_type;
	typedef typename traits_type::difference_type difference_type;
	
	typedef typename traits_type::reference reference;
	typedef typename traits_type::const_reference const_reference;
	typedef typename traits_type::pointer pointer;
	typedef typename traits_type::const_pointer const_pointer;
	
	typedef typename traits_type::iterator_category iterator_category;
	
protected:
	integer_reverse_facet(const_reference first) : m_offset(first) { /* NOP */ }
	
public:
	reference operator * () { value_type cpy = m_offset; return --cpy; }
	const_reference operator * () const { value_type cpy = m_offset; return --cpy; }
	
	pointer operator -> () const { return &(operator*()); }
	
	const_this_type & operator ++ () noexcept { --m_offset; return *this; }
	this_type operator ++ (int) noexcept { this_type cpy(*this); --m_offset; return cpy; }
	
	const_this_type & operator -- () noexcept { ++m_offset; return *this; }
	this_type operator -- (int) noexcept { this_type cpy(*this); ++m_offset; return cpy; }
	
	this_type operator + (value_type n) const noexcept { return facet(m_offset - n); }
	const_this_type & operator += (value_type n) noexcept { m_offset -= n; return *this; }
	
	this_type operator - (value_type n) const noexcept { return facet(m_offset + n); }
	const_this_type & operator -= (value_type n) { m_offset += n; return *this; }
	
	bool operator == (const_this_type & other_it) const noexcept { return m_offset == other_it.m_offset; }
	bool operator != (const_this_type & other_it) const noexcept { return m_offset != other_it.m_offset; }
	
	operator this_type() const { return const_this_type(m_offset); }
	operator const_this_type() const { return const_this_type(m_offset); }
	
private:
	value_type m_offset;
};
	
template <typename ItemT, class FriendT
	, typename Traits = integer_facet_traits<ItemT>
	, typename std::enable_if<
		std::numeric_limits<ItemT>::is_integer
	>::type* = nullptr
>
using const_integer_reverse_facet = typename integer_reverse_facet<ItemT, FriendT, Traits>::const_this_type;

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ITERATORS_HPP */

/* EOF */