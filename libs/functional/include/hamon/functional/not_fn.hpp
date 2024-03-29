﻿/**
 *	@file	not_fn.hpp
 *
 *	@brief	not_fn 関数テンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_NOT_FN_HPP
#define HAMON_FUNCTIONAL_NOT_FN_HPP

#include <hamon/functional/config.hpp>
#include <functional>

#if defined(__cpp_lib_not_fn) && (__cpp_lib_not_fn >= 201603) && defined(HAMON_CPP_LIB_CONSTEXPR_FUNCTIONAL)

namespace hamon
{

using std::not_fn;

}	// namespace hamon

#else

#include <hamon/functional/invoke.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <typename F>
class not_fn_imp
{
private:
	hamon::decay_t<F> m_fd;

public:
	not_fn_imp() = delete;

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Args&&... args) &
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			!hamon::invoke(m_fd, hamon::forward<Args>(args)...))

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Args&&... args) &&
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			!hamon::invoke(hamon::move(m_fd), hamon::forward<Args>(args)...))

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR auto
	operator()(Args&&... args) const&
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			!hamon::invoke(m_fd, hamon::forward<Args>(args)...))

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR auto
	operator()(Args&&... args) const&&
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			!hamon::invoke(hamon::move(m_fd), hamon::forward<Args>(args)...))

	template <
		typename F2,
		typename = hamon::enable_if_t<
			!hamon::is_same<hamon::decay_t<F2>, not_fn_imp>::value
		>
	>
	HAMON_CXX11_CONSTEXPR explicit
	not_fn_imp(F2&& fn)
		: m_fd(hamon::forward<F2>(fn)) {}
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

template <
	typename F,
	typename = hamon::enable_if_t<
		hamon::is_constructible<hamon::decay_t<F>, F>::value
	>
>
HAMON_CXX11_CONSTEXPR detail::not_fn_imp<F>
not_fn(F&& fn)
HAMON_NOEXCEPT_IF((
	hamon::is_nothrow_constructible<hamon::decay_t<F>, F&&>::value))
{
	return detail::not_fn_imp<F>(hamon::forward<F>(fn));
}

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_NOT_FN_HPP
