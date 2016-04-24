//
// _defer.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#ifndef COCONUT_RUNTIME_DEFER_HPP
#define COCONUT_RUNTIME_DEFER_HPP

namespace coconut { namespace runtime { namespace defer {

template <typename CallableT>
COCONUT_PRIVATE struct COCONUT_VISIBLE scope_holder COCONUT_FINAL
{
	scope_holder(const scope_holder &) = delete;
	scope_holder & operator = (const scope_holder &) = delete;
	~scope_holder() { commit(); }
	
	scope_holder(scope_holder && sh) noexcept
	: m_callable{std::move(sh.m_callable)}
	, m_called(false)
	{ /* NOP */ }
	
	scope_holder & operator = (scope_holder && sh) noexcept
	{ scope_holder(std::move(sh)).swap(*this); return *this; }

	scope_holder(CallableT && c)
	: m_callable{std::move(c)}
	, m_called(false)
	{ /* NOP */ }

private:
	void commit() noexcept
	{
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

COCONUT_PRIVATE struct COCONUT_VISIBLE dispatcher COCONUT_FINAL
{
	template <typename FuncT>
	inline auto operator () (FuncT && f)
		-> scope_holder<typename std::decay<FuncT>::type>
	{ return scope_holder<typename std::decay<FuncT>::type>(std::move(f)); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto operator () (FuncT && f, ArgsT &&... args)
		-> scope_holder<decltype(
			std::bind(std::forward<FuncT>(f), std::forward<ArgsT>(args)...)
		)>
	{
		return scope_holder<decltype(
			std::bind(std::forward<FuncT>(f), std::forward<ArgsT>(args)...)
		)>(std::bind(std::forward<FuncT>(f), std::forward<ArgsT>(args)...));
	}
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_DEFER_HPP */

/* EOF */