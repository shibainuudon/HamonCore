/**
 *	@file	scope_guard.hpp
 *
 *	@brief	scope_guard の定義
 */

#ifndef HAMON_DETAIL_SCOPE_GUARD_HPP
#define HAMON_DETAIL_SCOPE_GUARD_HPP

#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Func>
class scope_guard
{
	Func m_f;

public:
	HAMON_CXX11_CONSTEXPR explicit
	scope_guard(Func f)
		: m_f(hamon::move(f))
	{}

	HAMON_CXX20_CONSTEXPR
	~scope_guard()
	{
		m_f();
	}

	scope_guard(scope_guard const&)            = delete;
	scope_guard& operator=(scope_guard const&) = delete;
	scope_guard& operator=(scope_guard&&)      = delete;

#if !defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)
	scope_guard(scope_guard&&);
#else
	scope_guard(scope_guard&&) = delete;
#endif
};

template <typename Func>
HAMON_CXX14_CONSTEXPR scope_guard<Func>
make_scope_guard(Func f)
{
	return scope_guard<Func>(hamon::move(f));
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_DETAIL_SCOPE_GUARD_HPP
