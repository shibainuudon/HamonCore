/**
 *	@file	exception_guard.hpp
 *
 *	@brief	exception_guard の定義
 */

#ifndef HAMON_DETAIL_EXCEPTION_GUARD_HPP
#define HAMON_DETAIL_EXCEPTION_GUARD_HPP

#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if !defined(HAMON_NO_EXCEPTIONS)

template <typename Func>
struct exception_guard
{
	exception_guard() = delete;

	HAMON_CXX11_CONSTEXPR explicit
	exception_guard(Func f)
		: m_f(hamon::move(f)), m_completed(false)
	{}

	HAMON_CXX14_CONSTEXPR
	exception_guard(exception_guard&& other)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<Func>::value)
		: m_f(hamon::move(other.m_f)), m_completed(other.m_completed)
	{
		other.m_completed = true;
	}

	exception_guard(exception_guard const&)            = delete;
	exception_guard& operator=(exception_guard const&) = delete;
	exception_guard& operator=(exception_guard&&)      = delete;

	HAMON_CXX14_CONSTEXPR void
	complete() HAMON_NOEXCEPT
	{
		m_completed = true;
	}

	HAMON_CXX20_CONSTEXPR
	~exception_guard()
	{
		if (!m_completed)
		{
			m_f();
		}
	}

private:
	Func m_f;
	bool m_completed;
};

#else

template <typename Func>
struct exception_guard
{
	exception_guard() = delete;

	HAMON_CXX11_CONSTEXPR explicit
	exception_guard(Func) {}

	HAMON_CXX14_CONSTEXPR
	exception_guard(exception_guard&& other)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<Func>::value)
		: m_completed(other.m_completed)
	{
		other.m_completed = true;
	}

	exception_guard(exception_guard const&)            = delete;
	exception_guard& operator=(exception_guard const&) = delete;
	exception_guard& operator=(exception_guard&&)      = delete;

	HAMON_CXX14_CONSTEXPR void
	complete() HAMON_NOEXCEPT
	{
		m_completed = true;
	}

	HAMON_CXX20_CONSTEXPR
	~exception_guard()
	{
		HAMON_ASSERT(m_completed);
	}

private:
	bool m_completed = false;
};

#endif

template <typename Func>
HAMON_CXX14_CONSTEXPR exception_guard<Func>
make_exception_guard(Func f)
{
	return exception_guard<Func>(hamon::move(f));
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_DETAIL_EXCEPTION_GUARD_HPP
