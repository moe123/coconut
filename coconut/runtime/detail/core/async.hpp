//
// async.hpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/detail/core/types.hpp>

#ifndef COCONUT_RUNTIME_ASYNC_HPP
#define COCONUT_RUNTIME_ASYNC_HPP

namespace coconut
{
	namespace runtime
	{
		namespace async
		{
			template <typename FuncT, typename... ArgsT>
			inline std::future<typename std::result_of<FuncT(ArgsT...)>::type> exec(launch_option option, FuncT && func, ArgsT &&... args)
			{
				std::launch policy = (std::launch::async | std::launch::deferred);
				switch (option) {
					case launch_any:
						// std::launch::any is implementation-defined.
					break;
					case launch_async:
						policy = std::launch::async;
					break;
					case launch_deferred:
						policy = std::launch::deferred;
					break;
					default:
						break;
				}
				auto bind = std::bind(std::forward<FuncT>(func), std::forward<ArgsT>(args)...);
				return std::async(std::move(policy), std::move(bind));
			}
			
			template <typename FuncT, typename... ArgsT>
			inline void detach(FuncT && func, ArgsT &&... args)
			{
				typedef typename std::result_of<FuncT(ArgsT...)>::type R;
				auto bind = std::bind(std::forward<FuncT>(func), std::forward<ArgsT>(args)...);
				std::packaged_task<R()> task(std::move(bind));
				std::thread thr(std::move(task));
				thr.detach();
			}
		}
	}
}

#endif /* !COCONUT_RUNTIME_ASYNC_HPP */

/* EOF */