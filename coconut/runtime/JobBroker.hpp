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
	template <typename CallableT>
	struct COCONUT_VISIBLE JobReturn COCONUT_FINAL
	{
		explicit JobReturn(std::future<CallableT> && promise) :
			m_promise(std::move(promise))
		{ /* NOP */ }
		
		CallableT operator () () { return m_promise.get(); }
		
	private:
		std::future<CallableT> m_promise;
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
		( _JobExec(option, std::forward<FuncT>(func), std::forward<ArgsT>(args)...) );
	}
	
	template <typename FuncT, typename... ArgsT>
	inline auto JobExec(FuncT && func, ArgsT &&... args)
		-> JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
	{
		return JobReturn<typename std::result_of<FuncT(ArgsT...)>::type>
		( _JobExec(JobPolicyAsync, std::forward<FuncT>(func), std::forward<ArgsT>(args)...) );
	}
	
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