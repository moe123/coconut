//
// Printifier.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Types.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_PRINTIFIER_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_PRINTIFIER_HPP

namespace coconut
{
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			!std::is_same<TypeT, Array>::value &&
			!std::is_same<TypeT, MutableArray>::value &&
			!std::is_same<TypeT, OrderedSet>::value &&
			!std::is_same<TypeT, MutableOrderedSet>::value &&
			!std::is_same<TypeT, Set>::value &&
			!std::is_same<TypeT, MutableSet>::value &&
			!std::is_same<TypeT, Dictionary>::value &&
			!std::is_same<TypeT, MutableDictionary>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{
		if (r.isKindOf(StringClass) || r.isKindOf(PathClass) || r.isKindOf(URLClass) || r.isKindOf(DateClass)) {
			os << '"' << r.stringValue() << '"';
		} else if (r.isKindOf(ArrayClass)) {
			os << ref_cast<Array>(r);
			return os;
		} else if (r.isKindOf(OrderedSetClass)) {
			os << ref_cast<OrderedSet>(r);
			return os;
		} else if (r.isKindOf(SetClass)) {
			os << ref_cast<Set>(r);
			return os;
		} else if (r.isKindOf(DictionaryClass)) {
			os << ref_cast<Dictionary>(r);
			return os;
		} else if (r.isKindOf(DataClass)) {
			os << '"';
			runtime::hexrep::dump(os, ref_cast<Data>(r).cbegin(), ref_cast<Data>(r).cend(), 256);
			os << '"';
			return os;
		} else {
			os << r.stringValue();
		}
		return os;
	}
		
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			!std::is_same<TypeT, Array>::value &&
			!std::is_same<TypeT, MutableArray>::value &&
			!std::is_same<TypeT, OrderedSet>::value &&
			!std::is_same<TypeT, MutableOrderedSet>::value &&
			!std::is_same<TypeT, Set>::value &&
			!std::is_same<TypeT, MutableSet>::value &&
			!std::is_same<TypeT, Dictionary>::value &&
			!std::is_same<TypeT, MutableDictionary>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, ptr_declare<TypeT> const & r)
		-> std::ostream &
	{
		if (r) { os << *r; }
		return os;
	}
	
	template <typename TypeT,
		typename std::enable_if<
			std::is_same<Array, TypeT>::value ||
			std::is_same<TypeT, MutableArray>::value ||
			std::is_same<TypeT, OrderedSet>::value ||
			std::is_same<TypeT, MutableOrderedSet>::value ||
			std::is_same<TypeT, Set>::value ||
			std::is_same<TypeT, MutableSet>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{
		os << '[';
		for(auto it = r.cbegin(); it != r.cend(); ++it) {
			os << *it; if(std::next(it) != r.cend()) { os << ',' << ' '; }
		}
		os << ']';
		return os;
	}
		
	template <typename TypeT,
		typename std::enable_if<
			std::is_same<Array, TypeT>::value ||
			std::is_same<TypeT, MutableArray>::value ||
			std::is_same<TypeT, OrderedSet>::value ||
			std::is_same<TypeT, MutableOrderedSet>::value ||
			std::is_same<TypeT, Set>::value ||
			std::is_same<TypeT, MutableSet>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, ptr_declare<TypeT> const & r)
		-> std::ostream &
	{
		if (r) { os << *r; }
		return os;
	}

	template <typename TypeT,
		typename std::enable_if<
			std::is_same<TypeT, Dictionary>::value ||
			std::is_same<TypeT, MutableDictionary>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{
		os << '{';
		for(auto it = r.cbegin(); it != r.cend(); ++it) {
			os << (*it).first << ':' << ' ' << (*it).second; if(std::next(it) != r.cend()) { os << ',' << ' '; }
		}
		os << '}';
		return os;
	}
			
	template <typename TypeT,
		typename std::enable_if<
			std::is_same<TypeT, Dictionary>::value ||
			std::is_same<TypeT, MutableDictionary>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, ptr_declare<TypeT> const & r)
		-> std::ostream &
	{
		if (r) { os << *r; }
		return os;
	}
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_PRINTIFIER_HPP */

/* EOF */