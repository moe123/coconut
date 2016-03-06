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
			!std::is_same<Array, TypeT>::value &&
			!std::is_same<MutableArray, TypeT>::value &&
			!std::is_same<OrderedSet, TypeT>::value &&
			!std::is_same<MutableOrderedSet, TypeT>::value &&
			!std::is_same<Set, TypeT>::value &&
			!std::is_same<MutableSet, TypeT>::value &&
			!std::is_same<Dictionary, TypeT>::value &&
			!std::is_same<MutableDictionary, TypeT>::value
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
		} else {
			os << r.stringValue();
		}
		return os;
	}
		
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			!std::is_same<Array, TypeT>::value &&
			!std::is_same<MutableArray, TypeT>::value &&
			!std::is_same<OrderedSet, TypeT>::value &&
			!std::is_same<MutableOrderedSet, TypeT>::value &&
			!std::is_same<Set, TypeT>::value &&
			!std::is_same<MutableSet, TypeT>::value &&
			!std::is_same<Dictionary, TypeT>::value &&
			!std::is_same<MutableDictionary, TypeT>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, ptr_declare<TypeT> const & r)
		-> std::ostream &
	{
		if (r) {
			if (r->isKindOf(StringClass) || r->isKindOf(PathClass) || r->isKindOf(URLClass) || r->isKindOf(DateClass)) {
				os << '"' << r->stringValue() << '"';
			} else if (r->isKindOf(ArrayClass)) {
				os << ptr_cast<Array>(r);
				return os;
			} else if (r->isKindOf(OrderedSetClass)) {
				os << ptr_cast<OrderedSet>(r);
				return os;
			} else if (r->isKindOf(SetClass)) {
				os << ptr_cast<Set>(r);
				return os;
			} else if (r->isKindOf(DictionaryClass)) {
				os << ptr_cast<Dictionary>(r);
				return os;
			} else {
				os << r->stringValue();
			}
		}
		return os;
	}
	
	template <typename TypeT,
		typename std::enable_if<
			std::is_same<Array, TypeT>::value ||
			std::is_same<MutableArray, TypeT>::value ||
			std::is_same<OrderedSet, TypeT>::value ||
			std::is_same<MutableOrderedSet, TypeT>::value ||
			std::is_same<Set, TypeT>::value ||
			std::is_same<MutableSet, TypeT>::value
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
			std::is_same<MutableArray, TypeT>::value ||
			std::is_same<OrderedSet, TypeT>::value ||
			std::is_same<MutableOrderedSet, TypeT>::value ||
			std::is_same<Set, TypeT>::value ||
			std::is_same<MutableSet, TypeT>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, ptr_declare<TypeT> const & r)
		-> std::ostream &
	{
		os << '[';
		for(auto it = r->cbegin(); it != r->cend(); ++it) {
			os << *it; if(std::next(it) != r->cend()) { os << ',' << ' '; }
		}
		os << ']';
		return os;
	}

	template <typename TypeT,
		typename std::enable_if<
			std::is_same<Dictionary, TypeT>::value ||
			std::is_same<MutableDictionary, TypeT>::value
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
			std::is_same<Dictionary, TypeT>::value ||
			std::is_same<MutableDictionary, TypeT>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, ptr_declare<TypeT> const & r)
		-> std::ostream &
	{
		os << '{';
		for(auto it = r->cbegin(); it != r->cend(); ++it) {
			os << (*it).first << ':' << ' ' << (*it).second; if(std::next(it) != r->cend()) { os << ',' << ' '; }
		}
		os << '}';
		return os;
	}
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_PRINTIFIER_HPP */

/* EOF */