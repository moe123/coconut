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
		-> ptr_declare<T1>
	{ return ptr_cast<T1>(r); }

	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, T1>::value &&
			std::is_base_of<Any, T2>::value
		>::type* = nullptr
	>
	inline auto _copy(const T2 & r, std::false_type)
		-> ptr_declare<T1>
	{ return ptr_cast<T1>(r.kindCopy()); }
	
	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, T1>::value &&
			std::is_base_of<Any, T2>::value
		>::type* = nullptr
	>
	inline auto _copy(ptr_declare<T2> const & r, std::true_type)
		-> ptr_declare<T1>
	{ return ptr_cast<T1>(r->kindCopy()); }
	
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
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<CollT, Dictionary>::value ||
			std::is_same<CollT, MutableDictionary>::value
		>::type* = nullptr
	>
	inline auto _enumerate_dispatch_aliasing
	(
		const CollT & r,
		const std::function<void(const Owning<Any> & key, const Owning<Any> & obj)> & func,
		EnumerationOptions options
	 ) -> void
	{
		ref_cast<CollT>(r).enumerateKeysAndObjectsUsingFunction(
			[&func] (const Owning<Any> & key, const Owning<Any> & obj, bool & stop)
		{ func(key, obj); }, options);
	}
	
	template <typename TypeT, typename CollT>
	inline auto _enumerate_dispatch
	(
		const CollT & r,
		const std::function<void(const Owning<Any> & key, const Owning<Any> & obj)> & func,
		EnumerationOptions options
	) -> void
	{ _enumerate_dispatch_aliasing<TypeT, CollT>(r, func, options); }

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
	COCONUT_PUBLIC class COCONUT_VISIBLE OptionalReturn COCONUT_FINAL
	{
	public:
		OptionalReturn(const OptionalReturn &) = delete;
		OptionalReturn & operator = (const OptionalReturn &) = delete;
		~OptionalReturn() { /* NOP */ }
		
		OptionalReturn(OptionalReturn && oret) noexcept :
			m_success{std::move(oret.m_success)},
			m_error{std::move(oret.m_error)},
			m_valid{oret.m_valid}
		{ /* NOP */ }
		
		OptionalReturn & operator = (OptionalReturn && oret) noexcept
		{ OptionalReturn(std::move(oret)).swap(*this); return *this; }
		
		explicit OptionalReturn() :
			m_success{},
			m_error{},
			m_valid(false)
		{ /* NOP */ }
		
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
	
	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, typename std::decay<T2>
		>::value>::type* = nullptr
	>
	inline auto With(T2 && arg)
		-> Owning<T1>
	{ return ptr_create<T1>(std::move(arg)); }

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
	
	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, typename std::decay<T2>::type
		>::value>::type* = nullptr
	>
	inline auto Shift(T2 && r) -> decltype(std::move(r))
	{ return std::move(r); }
	
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