/**
 *	@file	thread.hpp
 *
 *	@brief	thread の定義
 */

#ifndef HAMON_THREAD_THREAD_HPP
#define HAMON_THREAD_THREAD_HPP

#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/ostream/basic_ostream.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.4.3 Class thread[thread.thread.class]

class thread
{
public:
	// [thread.thread.id], class thread​::​id
	class id;

	// 32.4.3.2.2 Class thread​::​name_hint[thread.attributes.hint]
	template <HAMON_CONSTRAINT(hamon::same_as, char, T)>
	class name_hint
	{
	public:
		constexpr explicit
		name_hint(hamon::basic_string_view<T> n) noexcept;

		name_hint(name_hint&&) = delete;
		name_hint(name_hint const&) = delete;

	private:
		hamon::basic_string_view<T> name;
	};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	template <typename T>
	name_hint(T const*) -> name_hint<T>;

	template <typename T>
	name_hint(hamon::basic_string<T>) -> name_hint<T>;
#endif

	// 32.4.3.2.3 Class thread​::​stack_size_hint[thread.attributes.size]
	class stack_size_hint
	{
	public:
		constexpr explicit stack_size_hint(hamon::size_t s) noexcept;

	private:
		hamon::size_t size;
	};

	using native_handle_type = hamon::detail::thread_t;         // see [thread.req.native]

	// construct/copy/destroy
	thread() noexcept
		// [thread.thread.constr]/1
		: m_handle()
	{}

	template <typename... Args,
		typename = hamon::enable_if_t<sizeof...(Args) != 0>,	// [thread.thread.constr]/3.1
		typename = hamon::enable_if_t<!hamon::is_same_v<hamon::remove_cvref_t<hamon::nth_t<0, Args...>>, thread>>// [thread.thread.constr]/3.2
	>
	explicit thread(Args&&... args)
	{}

private:
	template <typename F, typename... FArgs>
	thread(F&& f, FArgs&&... fargs)
	{
	}

public:
	~thread()
	{
		// [thread.thread.destr]/1
		if (joinable())
		{
			std::terminate();
		}
	}

	thread(thread const&) = delete;

	thread(thread&& x) noexcept
		: m_handle(hamon::exchange(x.m_handle, native_handle_type{}))
	{}

	thread& operator=(thread const&) = delete;

	thread& operator=(thread&& x) noexcept
	{
		// [thread.thread.assign]/1
		if (joinable())
		{
			std::terminate();
		}

		m_handle = hamon::exchange(x.m_handle, native_handle_type{});

		// [thread.thread.assign]/3
		return *this;
	}

	// [thread.thread.member], members
	void swap(thread& x) noexcept
	{
		// [thread.thread.member]/1
		hamon::swap(_Thr, x._Thr);
	}

	bool joinable() const noexcept
	{
		// [thread.thread.member]/2
		return get_id() != id();
	}

	void join()
	{
		// [thread.thread.member]/7.1

		// [thread.thread.member]/7.2

		// [thread.thread.member]/7.3
		if (!joinable())
		{
		}

		// [thread.thread.member]/5
		m_handle = {};
	}

	void detach()
	{
		// [thread.thread.member]/11.1

		// [thread.thread.member]/11.2
		if (!joinable())
		{
		}

		// [thread.thread.member]/9
		m_handle = {};
	}

	id get_id() const noexcept
	{
		return hamon::detail::thread_get_id(&m_handle);
	}

	native_handle_type native_handle()                         // see [thread.req.native]
	{
		return m_handle;
	}

	// static members
	static unsigned int hardware_concurrency() noexcept
	{
		// [thread.thread.static]/1
		return hamon::detail::thread_hardware_concurrency();
	}

private:
	native_handle_type	m_handle;
};

inline void swap(thread& x, thread& y) noexcept
{
	// [thread.thread.algorithm]/1
	x.swap(y);
}

// 32.4.3.3 Class thread​::​id[thread.thread.id]

class thread::id
{
public:
	id() noexcept
		// [thread.thread.id]/5
		: m_id(0)
	{}

private:
	hamon::detail::thread_id	m_id;
};

inline bool operator==(thread::id x, thread::id y) noexcept
{
	// [thread.thread.id]/6
	return x.m_id == y.m_id;
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

inline hamon::strong_ordering operator<=>(thread::id x, thread::id y) noexcept
{
	return x.m_id <=> y.m_id;
}

#else

#endif

template <typename charT, typename traits>
hamon::basic_ostream<charT, traits>&
operator<<(hamon::basic_ostream<charT, traits>& out, thread::id id);

#if 0	// TODO
template <typename charT>
struct formatter<thread::id, charT>;
#endif

#if 0	// TODO
// hash support
template <typename T>
struct hash;

template <>
struct hash<thread::id>;
#endif

}	// namespace hamon

#endif // HAMON_THREAD_THREAD_HPP
