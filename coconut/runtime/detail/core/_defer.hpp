//
// _defer.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#ifndef COCONUT_RUNTIME_DEFER_HPP
#define COCONUT_RUNTIME_DEFER_HPP

namespace coconut
{
	namespace runtime
	{
		template <typename CallableT>
		struct _defer_placeholder
		{
			_defer_placeholder(const _defer_placeholder &) = delete;
			_defer_placeholder & operator = (const _defer_placeholder &) = delete;
			
			~_defer_placeholder() { commit(); }
			
			_defer_placeholder(_defer_placeholder && dph) noexcept :
				m_callable{std::move(dph.m_callable)},
				m_called(false)
			{ /* NOP */ }
			
			_defer_placeholder & operator = (_defer_placeholder && dph) noexcept
			{ _defer_placeholder(std::move(dph)).swap(*this); return *this; }
		
			_defer_placeholder(CallableT && c) :
				m_callable{std::move(c)},
				m_called(false)
			{ /* NOP */ }
		
		private:
			void commit() noexcept {
				if (!m_called) {
					m_called = true;
					try { m_callable(); }
					catch(const std::exception &) { /* NOP */ }
					catch(...) { /* NOP */ }
				}
			}
			
		private:
			CallableT m_callable;
			bool m_called;
		};
		
		struct _defer_dispatch
		{
			template <typename FuncT>
			inline auto operator () (FuncT && f)
				-> _defer_placeholder<typename std::decay<FuncT>::type>
			{ return _defer_placeholder<typename std::decay<FuncT>::type>(std::move(f)); }
			
			template <typename FuncT, typename... ArgsT>
			inline auto operator () (FuncT && f, ArgsT &&... args)
				-> _defer_placeholder<decltype(std::bind(f, std::forward<ArgsT>(args)...))>
			{ return _defer_placeholder<decltype(std::bind(f, std::forward<ArgsT>(args)...))>(std::bind(f, std::forward<ArgsT>(args)...)); }
		};
	}
}

#endif /* !COCONUT_RUNTIME_DEFER_HPP */

/* EOF */