//
// Defer.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Types.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_DEFER_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_DEFER_HPP

namespace coconut
{
	template <typename CallableT>
	COCONUT_PRIVATE struct _defer_placeholder
	{
		_defer_placeholder(const _defer_placeholder<CallableT> &) = delete;
		_defer_placeholder & operator = (const _defer_placeholder<CallableT> &) = delete;
		
		~_defer_placeholder() { m_callable(); }
		
		_defer_placeholder(_defer_placeholder<CallableT> && dph) noexcept :
			m_callable{std::move(dph.m_callable)}
		{ /* NOP */ }
		
		_defer_placeholder & operator = (_defer_placeholder<CallableT> && dph) noexcept
		{ _defer_placeholder(std::move(dph)).swap(*this); return *this; }
	
		_defer_placeholder(CallableT && c) :
			m_callable(std::move(c))
		{ /* NOP */ }
		
	private:
		CallableT m_callable;
	};
	
	COCONUT_PRIVATE struct _defer_dispatch
	{
		inline _defer_placeholder< std::function<void()> > operator () (std::function<void()> & f)
		{ return _defer_placeholder< std::function<void()> >(std::move(f)); }
		
		template <typename FuncT, typename... ArgsT>
		inline auto operator () (FuncT && f, ArgsT &&... args)
			-> _defer_placeholder<decltype(std::bind(f, std::forward<ArgsT>(args)...))>
		{ return _defer_placeholder<decltype(std::bind(f, std::forward<ArgsT>(args)...))>(std::bind(f, std::forward<ArgsT>(args)...)); }
	};
	
	#define COCONUT_DEFER auto COCONUT_PPCAT_3(_defer, __LINE__, block) = _defer_dispatch{}
}
#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_DEFER_HPP */

/* EOF */