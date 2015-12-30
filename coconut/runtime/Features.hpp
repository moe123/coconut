//
// Features.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Types.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_FEATURES_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_FEATURES_HPP

namespace coconut
{
	template <class T> struct _is_ptr : std::false_type{};
	template <class T> struct _is_ptr< ptr_declare<T> > : std::true_type{};
	
	template <typename T1, typename T2>
	inline auto InstanceOf(T2 & r, std::false_type) -> bool
	{ T1 * ptr = dynamic_cast<T1 *>(std::addressof(r)); return (ptr != nullptr); }
	
	template <typename T1, typename T2>
	inline auto InstanceOf(ptr_declare<T2> const & r, std::true_type) -> bool
	{ T1 * ptr = dynamic_cast<T1 *>(std::addressof(*r)); return (ptr != nullptr); }
	
	template <typename T1, typename T2>
	inline auto InstanceOf(T2 && r) -> bool
	{ return InstanceOf<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto KindOf(T2 & r, std::false_type) -> bool
	{ return r . template isKindOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto KindOf(ptr_declare<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isKindOf<T1>()); }
	
	template <typename T1, typename T2>
	inline auto KindOf(T2 && r) -> bool
	{ return KindOf<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto SubclassOf(T2 & r, std::false_type) -> bool
	{ return r . template isSubclassOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto SubclassOf(ptr_declare<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isSubclassOf<T1>()); }
	
	template <typename T1, typename T2>
	inline auto SubclassOf(T2 && r) -> bool
	{ return SubclassOf<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto MemberOf(T2 & r, std::false_type) -> bool
	{ return r . template isMemberOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto MemberOf(ptr_declare<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isMemberOf<T1>()); }
	
	template <typename T1, typename T2>
	inline auto MemberOf(T2 && r) -> bool
	{ return MemberOf<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto AncestorOf(T2 & r, std::false_type) -> bool &
	{ return r . template  isAncestorOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto AncestorOf(ptr_declare<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isAncestorOf<T1>()); }
	
	template <typename T1, typename T2>
	inline auto AncestorOf(T2 && r) -> bool
	{ return AncestorOf<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(JobPolicyOption option, FuncT && func, ArgsT &&... args)
		-> decltype(runtime::async::exec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...))
	{ return runtime::async::exec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(FuncT && func, ArgsT &&... args)
		-> decltype(runtime::async::exec(JobPolicyAsync, std::forward<FuncT>(func), std::forward<ArgsT>(args)...))
	{ return runtime::async::exec(JobPolicyAsync, std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
		
	template <typename FuncT, typename... ArgsT>
	inline void JobDetach(FuncT && func, ArgsT &&... args)
	{ runtime::async::detach(std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename RetT, typename ErrT>
	struct OptionalReturn
	{
		operator bool () const { return valid; }

		RetT operator () () const { return success; }
		ErrT operator ~ () const { return error; }

		RetT success;
		ErrT error;
		bool valid;
	};
	
	template<typename TypeT, typename... ArgsT>
	inline auto With(ArgsT &&... args) -> ptr_declare<TypeT>
	{ return TypeT::with(std::forward<ArgsT>(args)...); }

	/** unwrapping for checking
	template<typename TypeT>
	inline auto With() -> ptr_declare<TypeT>
	{ return TypeT::with(); }
	
	template<typename TypeT, typename A0>
	inline auto With(A0 a0) -> ptr_declare<TypeT>
	{ return TypeT::with(a0); }

	template<typename TypeT, typename A0, typename A1>
	inline auto With(A0 a0, A1 a1) -> ptr_declare<TypeT>
	{ return TypeT::with(a0, a1); }

	template<typename TypeT, typename A0, typename A1, typename A2>
	inline auto With(A0 a0, A1 a1, A2 a2) -> ptr_declare<TypeT>
	{ return TypeT::with(a0, a1, a2); }

	template<typename TypeT, typename A0, typename A1, typename A2, typename A3>
	inline auto With(A0 a0, A1 a1, A2 a2, A3 a3) -> ptr_declare<TypeT>
	{ return TypeT::with(a0, a1, a2, a3); }
	
	template<typename TypeT, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline auto With(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) -> ptr_declare<TypeT>
	{ return TypeT::with(a0, a1, a2, a4); }
	
	template<typename TypeT, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline auto With(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) -> ptr_declare<TypeT>
	{ return TypeT::with(a0, a1, a2, a4, a5); }
	**/

	template<typename TypeT>
	inline auto With(const std::initializer_list< ptr_declare<Any> > & args) -> ptr_declare<TypeT>
	{ return TypeT::with(args); }
	
	template<typename TypeT>
	inline auto With(const std::initializer_list< std::pair< ptr_declare<Any>, ptr_declare<Any> > > & args) -> ptr_declare<TypeT>
	{ return TypeT::with(args); }

	template <typename T1, typename T2>
	inline auto Thus(T2 & r, std::false_type) -> T1 &
	{ return ref_cast<T1>(r); }
	
	template <typename T1, typename T2>
	inline auto Thus(ptr_declare<T2> const & r, std::true_type) -> T1 &
	{ return (*(ptr_cast<T1>(r))); }
	
	template <typename T1, typename T2>
	inline auto Thus(T2 && r)
		-> decltype(Thus<T1>(r, _is_ptr<typename std::decay<T2>::type>{}))
	{ return Thus<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }

	template <typename T1, typename T2>
	inline auto Then(T2 & r, std::false_type) -> T1 &
	{ return ref_cast<T1>(r); }
	
	template <typename T1, typename T2>
	inline auto Then(ptr_declare<T2> const & r, std::true_type) -> ptr_declare<T1>
	{ return ptr_cast<T1>(r); }
	
	template <typename T1, typename T2>
	inline auto Then(T2 && r)
		-> decltype(Then<T1>(r, _is_ptr<typename std::decay<T2>::type>{}))
	{ return Then<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_FEATURES_HPP */

/* EOF */