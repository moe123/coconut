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
	using JobPool = runtime::async::pool;
			
	template <typename FuncT, typename... ArgsT>
	inline auto JobPush(JobPool & pool, FuncT && func, ArgsT &&... args)
		-> JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
	{ return pool.push(std::forward<FuncT>(func), std::forward<ArgsT>(args)...); }

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
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_JOBBROKER_HPP */

/* EOF */