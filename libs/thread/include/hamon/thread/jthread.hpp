/**
 *	@file	jthread.hpp
 *
 *	@brief	jthread の定義
 */

#ifndef HAMON_THREAD_JTHREAD_HPP
#define HAMON_THREAD_JTHREAD_HPP

#include <hamon/thread/thread.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/detail/all.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_range.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.4.4 Class jthread[thread.jthread.class]

class jthread
{
public:
	// types
	using id = hamon::thread::id;

	using native_handle_type = hamon::thread::native_handle_type;

	template <typename T>
	using name_hint = hamon::thread::name_hint<T>;

	using stack_size_hint = hamon::thread::stack_size_hint;

	// [thread.jthread.cons], constructors, move, and assignment
	jthread() noexcept
		// [thread.jthread.cons]/1
		: m_ssource(hamon::nostopstate)
	{}

private:
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wunused-but-set-parameter")
	template <typename... Attrs, hamon::size_t... Js, typename F, typename... FArgs,
		hamon::enable_if_t<hamon::is_invocable_v<hamon::decay_t<F>, hamon::stop_token, hamon::decay_t<FArgs>...>>* = nullptr
	>
	hamon::thread do_create_thread_impl(hamon::tuple<Attrs...> attrs, hamon::index_sequence<Js...>, F&& f, FArgs&&... fargs)
	{
		return hamon::thread(
			hamon::forward<hamon::nth_t<Js, Attrs...>>(hamon::get<Js>(attrs))...,
			hamon::forward<F>(f),
			get_stop_token(),
			hamon::forward<FArgs>(fargs)...);
	}

	template <typename... Attrs, hamon::size_t... Js, typename F, typename... FArgs,
		hamon::enable_if_t<!hamon::is_invocable_v<hamon::decay_t<F>, hamon::stop_token, hamon::decay_t<FArgs>...>>* = nullptr
	>
	hamon::thread do_create_thread_impl(hamon::tuple<Attrs...> attrs, hamon::index_sequence<Js...>, F&& f, FArgs&&... fargs)
	{
		return hamon::thread(
			hamon::forward<hamon::nth_t<Js, Attrs...>>(hamon::get<Js>(attrs))...,
			hamon::forward<F>(f),
			hamon::forward<FArgs>(fargs)...);
	}
HAMON_WARNING_POP()

	template <typename... Attrs, hamon::size_t... Js, typename F, typename... FArgs>
	hamon::thread do_create_thread(hamon::tuple<Attrs...> attrs, hamon::index_sequence<Js...> js, F&& f, FArgs&&... fargs)
	{
		// [thread.jthread.cons]/5.1
		static_assert(hamon::is_constructible_v<hamon::decay_t<F>, F>, "");
		// [thread.jthread.cons]/5.2
		static_assert(hamon::detail::all_v<hamon::is_constructible_v<hamon::decay_t<FArgs>, FArgs>...>, "");
		// [thread.jthread.cons]/5.3
		static_assert(
			hamon::is_invocable_v<hamon::decay_t<F>, hamon::decay_t<FArgs>...> ||
			hamon::is_invocable_v<hamon::decay_t<F>, hamon::stop_token, hamon::decay_t<FArgs>...>, "");

		// [thread.jthread.cons]/5.4
		// TODO: no type is present more than once in the pack remove_cvref_t<Attrs>.

		// [thread.jthread.cons]/6
		return do_create_thread_impl(hamon::move(attrs), js, hamon::forward<F>(f), hamon::forward<FArgs>(fargs)...);
	}

	template <typename... Args, hamon::size_t... Js, hamon::size_t... Ks>
	hamon::thread create_thread(hamon::tuple<Args...> args, hamon::index_sequence<Js...> js, hamon::index_sequence<Ks...>)
	{
		return do_create_thread(
			hamon::forward_as_tuple(hamon::forward<hamon::nth_t<Js, Args...>>(hamon::get<Js>(args))...),
			js,
			hamon::forward<hamon::nth_t<Ks, Args...>>(hamon::get<Ks>(args))...
		);
	}

public:
	template <typename... Args,
		typename = hamon::enable_if_t<sizeof...(Args) != 0>,	// [thread.jthread.cons]/3.1
		typename = hamon::enable_if_t<!hamon::is_same_v<hamon::remove_cvref_t<hamon::nth_t<0, Args...>>, jthread>>,// [thread.jthread.cons]/3.2
		// [thread.jthread.cons]/4
		hamon::size_t i = hamon::detail::count_thread_attribute<hamon::decay_t<Args>...>::value
	>
	explicit jthread(Args&&... args)
		: m_ssource()
		, m_thread(create_thread(
			hamon::forward_as_tuple(hamon::forward<Args>(args)...),
			hamon::make_index_range<0, i>{},
			hamon::make_index_range<i, sizeof...(Args)>{}))
	{
		// [thread.jthread.cons]/5
		static_assert(i < sizeof...(Args), "");
	}

	~jthread()
	{
		// [thread.jthread.cons]/12
		if (joinable())
		{
			request_stop();
			join();
		}
	}

	jthread(jthread const&) = delete;

	jthread(jthread&&) noexcept = default;

	jthread& operator=(jthread const&) = delete;

	jthread& operator=(jthread&& x) noexcept
	{
		// [thread.jthread.cons]/13
		if (&x != this)
		{
			if (joinable())
			{
				request_stop();
				join();
			}
			m_ssource = hamon::move(x.m_ssource);
			m_thread = hamon::move(x.m_thread);
		}

		// [thread.jthread.cons]/15
	    return *this;
	}

	// [thread.jthread.mem], members
	void swap(jthread& x) noexcept
	{
		// [thread.jthread.mem]/1
		hamon::swap(m_ssource, x.m_ssource);
		hamon::swap(m_thread, x.m_thread);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	bool joinable() const noexcept
	{
		// [thread.jthread.mem]/2
		return get_id() != id();
	}

	void join()
	{
		// [thread.jthread.mem]/3
		m_thread.join();
	}

	void detach()
	{
		// [thread.jthread.mem]/8
		m_thread.detach();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	id get_id() const noexcept
	{
		// [thread.jthread.mem]/12
		return m_thread.get_id();
	}

	native_handle_type native_handle()	// see [thread.req.native]
	{
		return m_thread.native_handle();
	}

	// [thread.jthread.stop], stop token handling
	hamon::stop_source get_stop_source() noexcept
	{
		// [thread.jthread.stop]/1
		return m_ssource;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	hamon::stop_token get_stop_token() const noexcept
	{
		// [thread.jthread.stop]/2
		return m_ssource.get_token();
	}

	bool request_stop() noexcept
	{
		// [thread.jthread.stop]/3
		return m_ssource.request_stop();
	}

	// [thread.jthread.special], specialized algorithms
	friend void swap(jthread& x, jthread& y) noexcept
	{
		// [thread.jthread.special]/1
		x.swap(y);
	}

	// [thread.jthread.static], static members
	HAMON_NODISCARD	// nodiscard as an extension
	static unsigned int hardware_concurrency() noexcept
	{
		// [thread.jthread.static]/1
		return thread::hardware_concurrency();
	}

private:
	hamon::stop_source m_ssource;
	hamon::thread m_thread;
};

}	// namespace hamon

#endif // HAMON_THREAD_JTHREAD_HPP
