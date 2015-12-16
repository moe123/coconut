
//
// iterator.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/defines.hpp>

#ifndef COCONUT_RUNTIME_ITERATOR_HPP
#define COCONUT_RUNTIME_ITERATOR_HPP

namespace coconut
{
	namespace runtime
	{
		namespace iterator
		{
			template<class MapT>
			class key_map_facet : public MapT::iterator
			{
			public:
				typedef typename MapT::iterator facet;
				typedef typename facet::value_type::first_type key_type;
				
			public:
				key_map_facet(const facet & other_it) : MapT::iterator(other_it) { /* NOP */ } ;
				key_type & operator * () const { return MapT::iterator::operator*().first; }
			};

			template<class MapT>
			key_map_facet<MapT> key_begin(MapT & m)
			{ return key_map_facet<MapT>(m.begin()); }

			template<class MapT>
			key_map_facet<MapT> key_end(MapT & m)
			{ return key_map_facet<MapT>(m.end()); }

			template<class MapT>
			class value_map_facet : public MapT::iterator
			{
			public:
				typedef typename MapT::iterator facet;
				typedef typename facet::value_type::second_type value_type;
				
			public:
				value_map_facet(const facet & other_it) : MapT::iterator(other_it) { /* NOP */ } ;
				value_type & operator * () const { return MapT::iterator::operator*().second; }
			};

			template<class MapT>
			value_map_facet<MapT> value_begin(MapT & m)
			{ return value_map_facet<MapT>(m.begin()); }

			template<class MapT>
			value_map_facet<MapT> value_end(MapT & m)
			{ return value_map_facet<MapT>(m.end()); }
			
			
			template <typename ItemT, class FriendT>
			class range_adv_facet
			{
			friend FriendT;
				
			protected:
				typedef range_adv_facet<ItemT, FriendT> facet;
				typedef const range_adv_facet<ItemT, FriendT> const_facet;
				typedef ItemT value_type;
				typedef ItemT size_type;
				typedef std::ptrdiff_t difference_type;
				
			protected:
				range_adv_facet(value_type beg) : m_val (beg) { /* NOP */ }
				
			public:
				value_type operator * () const { return m_val; }
				
				const_facet & operator ++ () { ++m_val; return *this; }
				facet operator ++ (int) { facet cpy(*this); ++m_val; return cpy; }
				
				const_facet & operator -- () { --m_val; return *this; }
				facet operator -- (int) { facet cpy(*this); --m_val; return cpy; }
				
				facet operator + (value_type n) const { return facet(m_val + n); }
				const_facet & operator += (value_type n) { m_val += n; return *this; }
				
				facet operator - (value_type n) const { return facet(m_val -n); }
				const_facet & operator -= (value_type n) { m_val -= n; return *this; }
				
				bool operator == (const_facet & other_it) const { return m_val == other_it.m_val; }
				bool operator != (const_facet & other_it) const { return m_val != other_it.m_val; }
				
			private:
				value_type m_val;
			};

			template <typename ItemT, class FriendT>
			class range_rev_facet
			{
			friend FriendT;
				
			protected:
				typedef range_rev_facet<ItemT, FriendT> facet;
				typedef const range_rev_facet<ItemT, FriendT> const_facet;
				typedef ItemT value_type;
				typedef ItemT size_type;
				typedef std::ptrdiff_t difference_type;
				
			protected:
				range_rev_facet(value_type beg) : m_val (beg) { /* NOP */ }
				
			public:
				value_type operator * () const { value_type cpy = m_val; return --cpy; }
				
				const_facet & operator ++ () { --m_val; return *this; }
				facet operator ++ (int) { facet cpy(*this); --m_val; return cpy; }
				
				const_facet & operator -- () { ++m_val; return *this; }
				facet operator -- (int) { facet cpy(*this); ++m_val; return cpy; }
				
				facet operator + (value_type n) const { return facet(m_val - n); }
				const_facet & operator += (value_type n) { m_val -= n; return *this; }
				
				facet operator - (value_type n) const { return facet(m_val + n); }
				const_facet & operator -= (value_type n) { m_val += n; return *this; }
				
				bool operator == (const_facet & other_it) const { return m_val == other_it.m_val; }
				bool operator != (const_facet & other_it) const { return m_val != other_it.m_val; }
				
			private:
				value_type m_val;
			};
		}
	}
}

#endif /* !COCONUT_RUNTIME_ITERATOR_HPP */

/* EOF */