//
// JobBroker.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Types.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_JOBBROKER_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_JOBBROKER_HPP

namespace coconut
{
	template <typename T> using JobReturn = runtime::async::shall<T>;
	
	COCONUT_PUBLIC class COCONUT_VISIBLE JobPool COCONUT_FINAL
	{
	public:
		JobPool(const JobPool &) = delete;
		JobPool & operator = (const JobPool &) = delete;
		
		explicit JobPool(std::size_t count, bool start = true) :
			m_pool(count)
		{  if (start) { m_pool.start(); } }
		
		void start() { m_pool.start(); }
		void stop() { m_pool.stop(); }
		
		~JobPool() { m_pool.stop(); }
		
		template <typename FuncT, typename... ArgsT>
		inline auto operator () (FuncT && func, ArgsT &&... args)
			-> JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
		{ return m_pool.push(std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
		
	private:
		runtime::async::pool m_pool;
	};

	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(JobPolicyOption option, FuncT && func, ArgsT &&... args)
		-> JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
	{ return runtime::async::exec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(FuncT && func, ArgsT &&... args)
		-> JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
	{ return runtime::async::exec(JobPolicyAsync, std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobRun(FuncT && func, ArgsT &&... args)
		-> typename std::result_of<FuncT(ArgsT...)>::type
	{ auto job = JobExec(std::forward<FuncT>(func), std::forward<ArgsT>(args)...); return job(); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobDetach(FuncT && func, ArgsT &&... args)
		-> void
	{ runtime::async::detach(std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobDefer(FuncT && func, ArgsT &&... args)
	-> void
	{ runtime::async::detach(std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }
	
	template <typename FuncT>
	struct _defer_handler {
		_defer_handler(FuncT && f) : m_func(std::move(f)) {}
		~_defer_handler() { m_func(); }
		FuncT m_func;
	};
	
	template <typename FuncT>
	auto _defer_block(FuncT && f) -> _defer_handler<FuncT> {
		return _defer_handler<FuncT>(f);
	};
	
	
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_JOBBROKER_HPP */

/* EOF */