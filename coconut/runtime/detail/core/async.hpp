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
			class COCONUT_VISIBLE shall COCONUT_FINAL
			{
			public:
				shall(const shall &) = delete;
				shall & operator = (const shall &) = delete;
				
				~shall() { /* NOP */ }
				
				shall(shall && res) noexcept :
				m_fut{std::move(res.m_fut)}
				{ /* NOP */ }
				
				shall & operator = (shall && res) noexcept
				{ shall(std::move(res)).swap(*this); return *this; }
				
				explicit shall(std::future<T> && fut) noexcept :
				m_fut{std::move(fut)}
				{ /* NOP */ }
				
				T operator () () noexcept { return m_fut.get(); }
				
			private:
				std::future<T> m_fut;
			};
			
			template <typename FuncT, typename... ArgsT>
			inline shall<typename std::result_of<FuncT(ArgsT...)>::type> exec(launch_option option, FuncT && func, ArgsT &&... args)
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
				return shall<typename std::result_of<FuncT(ArgsT...)>::type>(
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
			
			// //////////////////////////////////////////////////////////
			// @based on thread_pool.hpp, thread_pool.cpp
			// Copyright (C) 2015 Tyler Hardin. All rights reserved.
			// @see https://github.com/Tyler-Hardin/thread_pool
			//
			
			/**
				@note:
					However we keept the std::promise workaround ; that is still
					happening on older vers. TODO explain: moved join flag to
					an atomic barrier, some stuff are now overkilling, but doesn't
					hurt much.
			**/
			class pool
			{
			public:
				pool(std::size_t count) :
					m_count(count),
					m_join(false),
					m_mutex(),
					m_tasks(),
					m_threads()
				{
					m_mutex.lock();
					for (std::size_t i = 0; i < m_count; i++) {
						std::function<void(void)> f = std::bind(&pool::main, this);
						m_threads.push_back(std::move(std::thread(f)));
					}
					m_mutex.unlock();
				}
				
				~pool()
				{
					m_mutex.lock();
					m_join = true;
					m_mutex.unlock();
					for (std::list<std::thread>::iterator it = m_threads.begin(); it != m_threads.end(); ++it) {
						(*it).join();
					}
				}
				
				template<typename Ret, typename... Args>
				shall<Ret> push(std::function<Ret(Args...)> f, Args... args)
				{
					typedef std::function<Ret(Args...)> F;
					
					std::shared_ptr< std::atomic<bool> > ready = std::make_shared< std::atomic<bool> >(false);
					std::shared_ptr< std::promise<Ret> > p = std::make_shared< std::promise<Ret> >();
					
					auto task_wrapper = [p, ready](F && ff, Args... aargs) {
						p->set_value(ff(aargs...));
						ready->store(true);
					};
					
					auto ret_wrapper = [p, ready]() -> Ret{
						while(!ready->load()) {
							std::this_thread::yield();
						}
						auto temp = p->get_future().get();
						return temp;
					};
					
					m_mutex.lock();
					m_tasks.emplace_back(std::async(std::launch::deferred,
													task_wrapper, std::move(f), args...));
					m_mutex.unlock();
					
					return shall<Ret>(
						std::async(std::launch::deferred, ret_wrapper)
					);
				}
				
				template<typename Ret>
				shall<Ret> push(std::function<Ret()> f)
				{
					typedef std::function<Ret()> F;
					
					std::shared_ptr< std::atomic<bool> > ready = std::make_shared< std::atomic<bool> >(false);
					std::promise<Ret> *p = new std::promise<Ret>;
					
					auto task_wrapper = [p, ready](F && ff) {
						p->set_value(ff());
						ready->store(true);
					};
					
					auto ret_wrapper = [p, ready]() -> Ret{
						while(!ready->load()) {
							std::this_thread::yield();
						}
						auto temp = p->get_future().get();
						return temp;
					};
					
					m_mutex.lock();
					m_tasks.emplace_back(std::async(std::launch::deferred, task_wrapper, std::move(f)));
					m_mutex.unlock();
					
					return shall<Ret>(
						std::async(std::launch::deferred, ret_wrapper)
					);
				}
				
				template<typename... Args>
				shall<void> push(std::function<void(Args...)> f, Args... args)
				{
					typedef std::function<void(Args...)> F;
					
					std::shared_ptr< std::atomic<bool> > ready = std::make_shared< std::atomic<bool> >(false);
					std::promise<void> *p = new std::promise<void>;
					
					auto task_wrapper = [p, ready](F && ff, Args... aargs){
						ff(aargs...);
						p->set_value();
						ready->store(true);
					};
					
					auto ret_wrapper = [p, ready]() {
						while(!ready->load()) {
							std::this_thread::yield();
						}
						p->get_future().get();
						return;
					};
					
					m_mutex.lock();
					m_tasks.emplace_back(std::async(std::launch::deferred, task_wrapper, std::move(f), args...));
					m_mutex.unlock();
					
					return shall<void>(
						std::async(std::launch::deferred, ret_wrapper)
					);
				}
				
				shall<void> push(std::function<void()> f)
				{
					typedef std::function<void()> F;
					
					std::shared_ptr< std::atomic<bool> > ready = std::make_shared< std::atomic<bool> >(false);
					std::promise<void> *p = new std::promise<void>;
					
					auto task_wrapper = [p, ready](F && ff){
						ff();
						p->set_value();
						ready->store(true);
					};
					
					auto ret_wrapper = [p, ready](){
						while(!ready->load()) {
							std::this_thread::yield();
						}
						p->get_future().get();
						return;
					};
					
					m_mutex.lock();
					m_tasks.emplace_back(std::async(std::launch::deferred, task_wrapper, std::move(f)));
					m_mutex.unlock();
					
					return shall<void> (
						std::async(std::launch::deferred, ret_wrapper)
					);
				}
				
			protected:
				void main()
				{
					for (;;) {
						m_mutex.lock();
						if (m_tasks.empty() && !m_join.load()) {
							m_mutex.unlock();
							std::this_thread::yield();
							continue;
						} else if (!m_tasks.empty()) {
							auto f = std::move(m_tasks.front());
							m_tasks.pop_front();
							m_mutex.unlock();
							f.get();
						} else if (m_join.load()) {
							m_mutex.unlock();
							return;
						}
					}
				}
				
			private:
				std::size_t m_count;
				std::atomic<bool> m_join;
				
				std::mutex m_mutex;
				std::deque<std::future<void>> m_tasks;
				std::list<std::thread> m_threads;
			};
		}
	}
}

#endif /* !COCONUT_RUNTIME_ASYNC_HPP */

/* EOF */