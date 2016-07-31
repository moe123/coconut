//
// nutrt-async.hpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>
#include <coconut/runtime/details/nutrt-nucleus.hpp>

#ifndef COCONUT_RUNTIME_ASYNC_HPP
#define COCONUT_RUNTIME_ASYNC_HPP

namespace coconut
{ namespace runtime
{

template <typename PromiseT>
COCONUT_PRIVATE class COCONUT_VISIBLE promise COCONUT_FINAL : public nucleus
{
COCONUT_CLASSDECLARE(coconut.runtime.promise, nucleus.promise)

public:
	promise(const promise &) = delete;
	promise & operator = (const promise &) = delete;
	~promise() { /* NOP */ }
	
	promise(promise && s) noexcept
	: nucleus(classkind_anon, classkind_hidden)
	, m_fut{std::move(s.m_fut)}
	{ /* NOP */ }
	
	promise & operator = (promise && s) noexcept
	{ promise(std::move(s)).swap(*this); return *this; }
	
	explicit promise(std::future<PromiseT> && fut) noexcept
	: nucleus(classkind_anon, classkind_hidden)
	, m_fut{std::move(fut)}
	{ /* NOP */ }
	
	PromiseT operator () () noexcept { return m_fut.get(); }
	
	virtual Owning<Any> copy() const COCONUT_FINAL_OVERRIDE
	{
		return ptr_create< promise<PromiseT> >(
			std::future<PromiseT>(std::move(m_fut))
		);
	}
	
private:
	mutable std::future<PromiseT> m_fut;
};
	
}} /* EONS */
	
namespace coconut
{ namespace runtime
{ namespace async
{

template <typename FuncT, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
promise<typename std::result_of<FuncT(ArgsT...)>::type> exec(launch_option option, FuncT && func, ArgsT &&... args)
{
	std::launch policy = (std::launch::async | std::launch::deferred);
	switch (option) {
		case launch_any:
#if defined(__clang__)
			policy = std::launch::any;
#endif
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
	return promise<typename std::result_of<FuncT(ArgsT...)>::type>(
		std::async(policy, std::move(bind))
	);
}

template <typename FuncT, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void detach(FuncT && func, ArgsT &&... args)
{
	using R = typename std::result_of<FuncT(ArgsT...)>::type;
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

COCONUT_PRIVATE class COCONUT_VISIBLE pool COCONUT_FINAL
{
public:
	pool()
	: m_mutex()
	, m_cond()
	, m_tasks()
	, m_threads()
	, m_count(0)
	, m_stop(false)
	, m_run(false)
	{ /* NOP */ }
	
	pool(std::size_t count)
	: m_mutex()
	, m_cond()
	, m_tasks()
	, m_threads()
	, m_count(count)
	, m_stop(false)
	, m_run(false)
	{ /* NOP */ }
	
	void set_count(std::size_t count)
	{ m_count = count; }
	
	void start()
	{
		bool can_start = false;
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			can_start = !m_run && m_count && !m_threads.size();
		}
		if (can_start) {
			for (std::size_t i = 0; i < m_count; i++) {
				std::function<void(void)> f = std::bind(&pool::main, this);
				m_threads.push_back(std::move(std::thread(f)));
			}
			m_run = true;
		}
	}
	
	bool is_running() { return m_run; }
	
	void stop()
	{
		if (m_run) {
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_run = false;
				m_stop = true;
			}
			m_cond.notify_all();
			
			for (std::vector<std::thread>::iterator it = m_threads.begin(); it != m_threads.end(); ++it) {
				m_cond.notify_one();
				(*it).join();
			}
			m_threads.clear();
			m_tasks.clear();
		}
	}
	
	~pool() { /* NOP */ }
	
	template <typename FuncT, typename... ArgsT>
	promise<typename std::result_of<FuncT(ArgsT...)>::type> push(FuncT f, ArgsT... args)
	{
		if (!m_run) { throw; }
		using Ret = typename std::result_of<FuncT(ArgsT...)>::type;
		std::shared_ptr< std::promise<Ret> > p = std::make_shared< std::promise<Ret> >();
		auto task_wrapper = [p](FuncT && ff, ArgsT... aargs) { p->set_value(ff(aargs...)); };
		auto ret_wrapper = [p]() -> Ret { return p->get_future().get(); };
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_tasks.emplace_back(
				std::async(std::launch::deferred, task_wrapper, std::move(f), args...)
			);
		}
		m_cond.notify_one();
		return promise<Ret>(
			std::async(std::launch::deferred, ret_wrapper)
		);
	}
	
	template <typename FuncT>
	promise<typename std::result_of<FuncT()>::type> push(FuncT f)
	{
		if (!m_run) { throw; }
		using Ret = typename std::result_of<FuncT()>::type;
		std::shared_ptr< std::promise<Ret> > p = std::make_shared< std::promise<Ret> >();
		auto task_wrapper = [p](FuncT && ff) { p->set_value(ff()); };
		auto ret_wrapper = [p]() -> Ret { return p->get_future().get(); };
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_tasks.emplace_back(
				std::async(std::launch::deferred, task_wrapper, std::move(f))
			);
		}
		m_cond.notify_one();
		return promise<Ret>(
			std::async(std::launch::deferred, ret_wrapper)
		);
	}
	
	template <typename... ArgsT>
	promise<void> push(const std::function<void(ArgsT...)> f, ArgsT... args)
	{
		if (!m_run) { throw; }
		using Ret = void;
		std::shared_ptr< std::promise<Ret> > p = std::make_shared< std::promise<Ret> >();
		auto task_wrapper = [p](const std::function<Ret(ArgsT...)> & ff, ArgsT... aargs) { ff(aargs...); p->set_value(); };
		auto ret_wrapper = [p]() -> Ret { p->get_future().get(); };
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_tasks.emplace_back(
				std::async(std::launch::deferred, task_wrapper, std::move(f), args...)
			);
		}
		m_cond.notify_one();
		return promise<Ret>(
			std::async(std::launch::deferred, ret_wrapper)
		);
	}
	
	promise<void> push(const std::function<void()> f)
	{
		if (!m_run) { throw; }
		using Ret = void;
		std::shared_ptr< std::promise<Ret> > p = std::make_shared< std::promise<Ret> >();
		auto task_wrapper = [p](const std::function<Ret()> & ff) { ff(); p->set_value(); };
		auto ret_wrapper = [p]() -> Ret { p->get_future().get(); };
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_tasks.emplace_back(
				std::async(std::launch::deferred, task_wrapper, std::move(f))
			);
		}
		m_cond.notify_one();
		return promise<Ret>(
			std::async(std::launch::deferred, ret_wrapper)
		);
	}

protected:
	void main()
	{
		for (;;) {
			std::future<void> fut;
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_cond.wait(lock, [this] {
					return m_stop || !m_tasks.empty();
				});
				
				if (m_stop && m_tasks.empty()) {
					return;
				} else if (!m_tasks.empty()) {
					fut = std::move(m_tasks.front());
					m_tasks.pop_front();
				}
			}
			fut.get();
		}
	}
	
private:
	std::mutex m_mutex;
	std::condition_variable m_cond;
	std::deque< std::future<void> > m_tasks;
	std::vector<std::thread> m_threads;
	
	std::size_t m_count;
	bool m_stop;
	bool m_run;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ASYNC_HPP */

/* EOF */