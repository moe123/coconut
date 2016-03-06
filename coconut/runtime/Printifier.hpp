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
			!std::is_same<MutableOrderedSet, TypeT>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{
		if (r.isKindOf(StringClass) || r.isKindOf(PathClass) || r.isKindOf(URLClass)) {
			os << '"' << r.stringValue() << '"';
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
			!std::is_same<MutableOrderedSet, TypeT>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, ptr_declare<TypeT> const & r)
		-> std::ostream &
	{
		if (r) {
			if (r->isKindOf(StringClass) || r->isKindOf(PathClass) || r->isKindOf(URLClass)) {
				os << '"' << *r << '"';
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
			std::is_same<MutableOrderedSet, TypeT>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
	-> std::ostream &
	{
		os << '[';
		for(auto it = r.cbegin(); it != r.cend(); ++it) {
			os << *(*it); if(std::next(it) != r.cend()) { os << ',' << ' '; }
		}
		os << ']';
		return os;
	}
		
	template <typename TypeT,
		typename std::enable_if<
			std::is_same<Array, TypeT>::value ||
			std::is_same<MutableArray, TypeT>::value ||
			std::is_same<OrderedSet, TypeT>::value ||
			std::is_same<MutableOrderedSet, TypeT>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, ptr_declare<TypeT> const & r)
	-> std::ostream &
	{
		os << '[';
		if (r) {
			for(auto it = r->cbegin(); it != r->cend(); ++it) {
				os << *(*it); if(std::next(it) != r->cend()) { os << ',' << ' '; }
			}
		}
		os << ']';
		return os;
	}

#if 0
	template<typename TypeT, template<typename, typename...> class CollT, typename... Args,
		typename std::enable_if<
			std::is_same<TypeT,
				std::deque<
					typename TypeT::value_type,
					typename TypeT::allocator_type
				>
			>::value ||
			std::is_same<TypeT,
				std::forward_list<
					typename TypeT::value_type,
					typename TypeT::allocator_type
				>
			>::value ||
			std::is_same<TypeT,
				std::list<
					typename TypeT::value_type,
					typename TypeT::allocator_type
				>
			>::value ||
			std::is_same<TypeT,
				std::set<
					typename TypeT::value_type,
					typename TypeT::allocator_type
				>
			>::value ||
			std::is_same<TypeT,
				std::unordered_set<
					typename TypeT::value_type,
					typename TypeT::allocator_type
				>
			>::value ||
			std::is_same<TypeT,
				std::vector<
					typename TypeT::value_type,
					typename TypeT::allocator_type
				>
			>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const CollT<TypeT, Args...> & r)
		-> std::ostream &
	{
		os << '[';
		for(auto it = r.cbegin(); it != r.cend(); ++it) {
			os << *it; if(std::next(it) != r.cend()) { os << ',' << ' '; }
		}
		os << ']';
		return os;
	}
#endif
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_PRINTIFIER_HPP */

/* EOF */