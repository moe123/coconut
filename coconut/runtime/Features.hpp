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
	template <class T> struct _is_ptr< Owning<T> > : std::true_type{};
	
	template <typename T1, typename T2>
	inline auto _conforms_to(const T2 & r, std::false_type) -> bool
	{ const T1 * ptr = dynamic_cast<const T1 *>(std::addressof(r)); return (ptr != nullptr); }
	
	template <typename T1, typename T2>
	inline auto _conforms_to(Owning<T2> const & r, std::true_type) -> bool
	{ T1 * ptr = dynamic_cast<T1 *>(std::addressof(*r)); return (ptr != nullptr); }
	
	template <typename T1, typename T2>
	inline auto _kind_of(const T2 & r, std::false_type) -> bool
	{ return r . template isKindOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto _kind_of(Owning<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isKindOf<T1>()); }
	
	template <typename T1, typename T2>
	inline auto _subclass_of(const T2 & r, std::false_type) -> bool
	{ return r . template isSubclassOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto _subclass_of(Owning<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isSubclassOf<T1>()); }

	template <typename T1, typename T2>
	inline auto _member_of(const T2 & r, std::false_type) -> bool
	{ return r . template isMemberOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto _member_of(Owning<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isMemberOf<T1>()); }

	template <typename T1, typename T2>
	inline auto _ancestor_of(const T2 & r, std::false_type) -> bool
	{ return r . template  isAncestorOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto _ancestor_of(Owning<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isAncestorOf<T1>()); }

	template <typename T1, typename T2>
	inline auto _thus(const T2 & r, std::false_type)
		-> T1 &
	{ return ref_cast<T1>(r); }
	
	template <typename T1, typename T2>
	inline auto _thus(Owning<T2> const & r, std::true_type)
		-> T1 &
	{ return (*(ptr_cast<T1>(r))); }

	template <typename T1, typename T2>
	inline auto _then(const T2 & r, std::false_type)
		-> T1 *
	{ return std::addressof(ref_cast<T1>(r)); }
	
	template <typename T1, typename T2>
	inline auto _then(Owning<T2> const & r, std::true_type)
		-> Owning<T1>
	{ return ptr_cast<T1>(r); }

	template <typename T1, typename T2>
	inline auto _copy(const T2 & r, std::false_type)
		-> Owning<T1>
	{ return ptr_cast<T1>(r.copyKind()); }
	
	template <typename T1, typename T2>
	inline auto _copy(Owning<T2> const & r, std::true_type)
		-> Owning<T1>
	{ return ptr_cast<T1>(r->copyKind()); }

	template <typename TypeT, typename CollT>
	inline auto _enumerate_dispatch(const CollT & r, const std::function<void(const Owning<Any> & obj, bool & stop)> & func, EnumerationOptions options)
		-> void
	{ ref_cast<TypeT>(r).enumerateObjectsUsingFunction(func, options); }
	
	template <typename TypeT, typename CollT>
	inline auto _enumerate_dispatch(const CollT & r, const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func, EnumerationOptions options)
		-> void
	{ ref_cast<TypeT>(r).enumerateObjectsUsingFunction(func, options); }
	
	template <typename TypeT, typename CollT>
	inline auto _enumerate_dispatch(const CollT & r, const std::function<void(const Owning<Any> & key, const Owning<Any> & obj, bool & stop)> & func, EnumerationOptions options)
		-> void
	{ ref_cast<TypeT>(r).enumerateKeysAndObjectsUsingFunction(func, options); }
	
	template <typename TypeT, typename CollT, typename FuncT>
	inline auto _enumerate(const CollT & r, const FuncT & func, EnumerationOptions options, std::false_type)
		-> void
	{ _enumerate_dispatch<TypeT>(r, func, options); }
	
	template <typename TypeT, typename CollT, typename FuncT>
	inline auto _enumerate(Owning<CollT> const & r, const FuncT & func, EnumerationOptions options, std::true_type)
		-> void
	{ if (r) { _enumerate_dispatch<TypeT>(*r, func, options); }; }

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

	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(JobPolicyOption option, FuncT && func, ArgsT &&... args)
		-> decltype(runtime::async::exec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...))
	{ return runtime::async::exec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(FuncT && func, ArgsT &&... args)
		-> decltype(runtime::async::exec(JobPolicyAsync, std::forward<FuncT>(func), std::forward<ArgsT>(args)...))
	{ return runtime::async::exec(JobPolicyAsync, std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
		
	template <typename FuncT, typename... ArgsT>
	inline auto JobDetach(FuncT && func, ArgsT &&... args)
		-> void
	{ runtime::async::detach(std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }

	template <typename T1, typename T2>
	inline auto ConformsTo(T2 && r) -> bool
	{ return _conforms_to<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto KindOf(T2 && r) -> bool
	{ return _kind_of<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }

	template <typename T1, typename T2>
	inline auto SubclassOf(T2 && r) -> bool
	{ return _subclass_of<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto MemberOf(T2 && r) -> bool
	{ return _member_of<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto AncestorOf(T2 && r) -> bool
	{ return _ancestor_of<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename TypeT>
	inline auto With(void * no_param = nullptr)
		-> Owning<TypeT>
	{ COCONUT_UNUSED(no_param); return TypeT::with(); }

	template <typename TypeT>
	inline auto With(const std::initializer_list< Owning<Any> > & args)
		-> Owning<TypeT>
	{ return TypeT::with(args); }
	
	template <typename TypeT>
	inline auto With(const std::initializer_list< std::pair< Owning<Any>, Owning<Any> > > & args)
		-> Owning<TypeT>
	{ return TypeT::with(args); }

	template <typename TypeT, typename... ArgsT>
	inline auto With(ArgsT &&... args)
		-> Owning<TypeT>
	{ return TypeT::with(std::forward<ArgsT>(args)...); }
	
	template <typename T1, typename T2>
	inline auto Thus(T2 && r)
		-> decltype(_thus<T1>(r, _is_ptr<typename std::decay<T2>::type>{}))
	{ return _thus<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto Then(T2 && r)
		-> decltype(_then<T1>(r, _is_ptr<typename std::decay<T2>::type>{}))
	{ return _then<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto Copy(T2 && r)
		-> Owning<T1>
	{ return _copy<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }

	template <typename TypeT, typename CollT, typename FuncT>
	inline auto Enumerate(CollT && r, FuncT && func, EnumerationOptions options = EnumerationDefault)
		-> void
	{ _enumerate<TypeT>(r, func, options, _is_ptr<typename std::decay<CollT>::type>{}); }
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_FEATURES_HPP */

/* EOF */