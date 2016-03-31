//
// async.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
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
			template <typename T>
			class COCONUT_VISIBLE return_wrapper COCONUT_FINAL
			{
			public:
				return_wrapper(const return_wrapper &) = delete;
				return_wrapper & operator = (const return_wrapper &) = delete;
				
				~return_wrapper() { /* NOP */ }
				
				return_wrapper(return_wrapper && jret) noexcept :
				m_fut{std::move(jret.m_fut)}
				{ /* NOP */ }
				
				return_wrapper & operator = (return_wrapper && jret) noexcept
				{ return_wrapper(std::move(jret)).swap(*this); return *this; }
				
				explicit return_wrapper(std::future<T> && fut) noexcept :
				m_fut{std::move(fut)}
				{ /* NOP */ }
				
				T operator () () noexcept { return m_fut.get(); }
				
			private:
				std::future<T> m_fut;
			};
			
			template <typename FuncT, typename... ArgsT>
			inline return_wrapper<typename std::result_of<FuncT(ArgsT...)>::type> exec(launch_option option, FuncT && func, ArgsT &&... args)
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
				return return_wrapper<typename std::result_of<FuncT(ArgsT...)>::type>(
					std::async(std::move(policy), std::move(bind))
				);
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