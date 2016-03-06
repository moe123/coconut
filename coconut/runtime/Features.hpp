//
// Features.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Types.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_FEATURES_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_FEATURES_HPP

namespace coconut
{
	template <class T> struct _is_ptr : std::false_type {};
	template <class T> struct _is_ptr< ptr_declare<T> > : std::true_type {};
	
	template<class T> struct _plain {
		typedef typename std::remove_cv<
			typename std::remove_reference<T>::type
		>::type type;
	};
		
	template <typename T1, typename T2>
	inline auto _conforms_to(const T2 & r, std::false_type) -> bool
	{ const T1 * ptr = dynamic_cast<const T1 *>(std::addressof(r)); return (ptr != nullptr); }
	
	template <typename T1, typename T2>
	inline auto _conforms_to(ptr_declare<T2> const & r, std::true_type) -> bool
	{ if (r) { const T1 * ptr = dynamic_cast<const T1 *>(std::addressof(*r)); return (ptr != nullptr); }; return false; }
	
	template <typename T1, typename T2>
	inline auto _kind_of(const T2 & r, std::false_type) -> bool
	{ return r . template isKindOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto _kind_of(ptr_declare<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isKindOf<T1>()); }
	
	template <typename T1, typename T2>
	inline auto _subclass_of(const T2 & r, std::false_type) -> bool
	{ return r . template isSubclassOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto _subclass_of(ptr_declare<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isSubclassOf<T1>()); }

	template <typename T1, typename T2>
	inline auto _member_of(const T2 & r, std::false_type) -> bool
	{ return r . template isMemberOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto _member_of(ptr_declare<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isMemberOf<T1>()); }

	template <typename T1, typename T2>
	inline auto _ancestor_of(const T2 & r, std::false_type) -> bool
	{ return r . template  isAncestorOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto _ancestor_of(ptr_declare<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isAncestorOf<T1>()); }

	template <typename T1, typename T2>
	inline auto _parent_of(const T2 & r, std::false_type) -> bool
	{ return r . template isParenOf<T1>(); }
	
	template <typename T1, typename T2>
	inline auto _parent_of(ptr_declare<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isParenOf<T1>()); }
	
	template <typename T1, typename T2>
	inline auto _thus(const T2 & r, std::false_type)
		-> T1 &
	{ return ref_cast<T1>(r); }
	
	template <typename T1, typename T2>
	inline auto _thus(ptr_declare<T2> const & r, std::true_type)
		-> T1 &
	{ return (*(ptr_cast<T1>(r))); }

	template <typename T1, typename T2>
	inline auto _then(const T2 & r, std::false_type)
		-> T1 *
	{ return std::addressof(ref_cast<T1>(r)); }
	
	template <typename T1, typename T2>
	inline auto _then(ptr_declare<T2> const & r, std::true_type)
		-> Owning<T1>
	{ return ptr_cast<T1>(r); }

	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, T1>::value &&
			std::is_base_of<Any, T2>::value
		>::type* = nullptr
	>
	inline auto _copy(const T2 & r, std::false_type)
		-> ptr_declare<T1>
	{ return ptr_cast<T1>(r.copyKind()); }
	
	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, T1>::value &&
			std::is_base_of<Any, T2>::value
		>::type* = nullptr
	>
	inline auto _copy(ptr_declare<T2> const & r, std::true_type)
		-> ptr_declare<T1>
	{ return ptr_cast<T1>(r->copyKind()); }
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<CollT, Array>::value ||
			std::is_same<CollT, MutableArray>::value ||
			std::is_same<CollT, OrderedSet>::value ||
			std::is_same<CollT, MutableOrderedSet>::value
		>::type* = nullptr
	>
	inline void _enumerate_dispatch_aliasing
	(
		const CollT & r,
		const std::function<void(const Owning<Any> & obj)> & func,
		EnumerationOptions options
	)
	{
		ref_cast<CollT>(r).enumerateObjectsUsingFunction(
			[&func] (const Owning<Any> & obj, std::size_t index, bool & stop)
		{ func(obj); }, options);
	}

	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<CollT, Set>::value ||
			std::is_same<CollT, MutableSet>::value
		>::type* = nullptr
	>
	inline auto _enumerate_dispatch_aliasing
	(
		const CollT & r,
		const std::function<void(const Owning<Any> & obj)> & func,
		EnumerationOptions options
	) -> void
	{
		ref_cast<CollT>(r).enumerateObjectsUsingFunction(
			[&func] (const Owning<Any> & obj, bool & stop)
		{ func(obj); }, options);
	}

	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<CollT, Dictionary>::value ||
			std::is_same<CollT, MutableDictionary>::value
		>::type* = nullptr
	>
	inline auto _enumerate_dispatch_aliasing
	(
	 	const CollT & r,
		const std::function<void(const Owning<Any> & obj)> & func,
		EnumerationOptions options
	) -> void
	{
		ref_cast<CollT>(r).enumerateKeysAndObjectsUsingFunction(
			[&func] (const Owning<Any> & key, const Owning<Any> & obj, bool & stop)
		{ func(key); }, options);
	}

	template <typename TypeT, typename CollT>
	inline auto _enumerate_dispatch
	(
		const CollT & r,
		const std::function<void(const Owning<Any> & obj)> & func,
		EnumerationOptions options
	) -> void
	{ _enumerate_dispatch_aliasing<TypeT, CollT>(r, func, options); }
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<CollT, Set>::value ||
			std::is_same<CollT, MutableSet>::value
		>::type* = nullptr
	>
	inline auto _enumerate_dispatch
	(
	 	const CollT & r,
	 	const std::function<void(const Owning<Any> & obj, bool & stop)> & func,
	 	EnumerationOptions options
	) -> void
	{ ref_cast<TypeT>(r).enumerateObjectsUsingFunction(func, options); }
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<CollT, Array>::value ||
			std::is_same<CollT, MutableArray>::value ||
			std::is_same<CollT, OrderedSet>::value ||
			std::is_same<CollT, MutableOrderedSet>::value
		>::type* = nullptr
	>
	inline auto _enumerate_dispatch
	(
	 	const CollT & r,
	 	const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func,
	 	EnumerationOptions options
	) -> void
	{ ref_cast<TypeT>(r).enumerateObjectsUsingFunction(func, options); }
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<CollT, Dictionary>::value ||
			std::is_same<CollT, MutableDictionary>::value
		>::type* = nullptr
	>
	inline auto _enumerate_dispatch
	(
		const CollT & r,
	 	const std::function<void(const Owning<Any> & key, const Owning<Any> & obj, bool & stop)> & func,
	 	EnumerationOptions options
	) -> void
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
	struct COCONUT_VISIBLE OptionalReturn COCONUT_FINAL
	{
		explicit OptionalReturn() : m_success{}, m_error{}, m_valid(false) { /* NOP */ }
		
		const RetT & success() const { return m_success; }
		const ErrT & error() const { return m_error; }
		
		operator bool () const { return m_valid; }
		const RetT & operator () () const { return success(); }
		const ErrT & operator ~ () const { return error(); }
		
		void setSuccess(const RetT & success)
		{ m_success = success; m_error = {}; m_valid = true; }
		
		void setError(const ErrT & error)
		{ m_success = {}; m_error = error; m_valid = false; }

	private:
		RetT m_success;
		ErrT m_error;
		bool m_valid;
	};
	
	template <typename T>
	struct COCONUT_VISIBLE JobReturn COCONUT_FINAL
	{
		explicit JobReturn(std::future<T> && f) : m_fut(std::move(f)) { /* NOP */ }
		
		T operator () () { return m_fut.get(); }
		
	private:
		std::future<T> m_fut;
	};
	
	template <typename FuncT, typename... ArgsT>
	inline auto _JobExec(JobPolicyOption option, FuncT && func, ArgsT &&... args)
		-> decltype(runtime::async::exec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...))
	{ return runtime::async::exec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(JobPolicyOption option, FuncT && func, ArgsT &&... args)
		-> JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
	{
		return JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
		(
			_JobExec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...)
		);
	}
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(FuncT && func, ArgsT &&... args)
		-> JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
	{
		return JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
		(
			_JobExec(JobPolicyAsync, std::forward<FuncT>(func), std::forward<ArgsT>(args)...)
		);
	}
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobRun(FuncT && func, ArgsT &&... args)
		-> typename std::result_of<FuncT(ArgsT...)>::type
	{ auto job = JobExec(std::forward<FuncT>(func), std::forward<ArgsT>(args)...); return job(); }
		
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
	
	template <typename T1, typename T2>
	inline auto isParentOf(T2 && r) -> bool
	{ return _parent_of<T1>(r, _is_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename TypeT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(void * no_param = nullptr)
		-> Owning<TypeT>
	{ COCONUT_UNUSED(no_param); return ptr_create<TypeT>(); }
	
	template <typename TypeT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(const TypeT & arg)
		-> Owning<TypeT>
	{ return ptr_create<TypeT>(arg); }
	
	template <typename TypeT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(TypeT && arg)
		-> Owning<TypeT>
	{ return ptr_create<TypeT>(std::move(arg)); }

	template <typename TypeT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(const std::initializer_list< Owning<Any> > & args)
		-> Owning<TypeT>
	{ return ptr_create<TypeT>(args); }
	
	template <typename TypeT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(const std::initializer_list< std::pair< Owning<Any>, Owning<Any> > > & args)
		-> Owning<TypeT>
	{ return ptr_create<TypeT>(args); }

	template <typename TypeT, typename... ArgsT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(ArgsT &&... args)
		-> Owning<TypeT>
	{ return ptr_create<TypeT>(std::forward<ArgsT>(args)...); }
	
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