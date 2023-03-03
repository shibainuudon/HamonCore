/**
 *	@file	invoke_r.hpp
 *
 *	@brief	invoke_r 関数の定義
 */

#ifndef HAMON_FUNCTIONAL_INVOKE_R_HPP
#define HAMON_FUNCTIONAL_INVOKE_R_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_INVOKE_R)

namespace hamon
{

using std::invoke_r;

}	// namespace hamon

#else

#include <hamon/functional/invoke.hpp>
#include <hamon/type_traits/is_invocable_r.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace detail
{

template <
	typename R,
	typename = hamon::enable_if_t<hamon::is_void<R>::value>,
	typename... Args
>
HAMON_CXX14_CONSTEXPR R
invoke_r_impl(hamon::detail::overload_priority<1>, Args&&... args)
HAMON_NOEXCEPT_IF_EXPR(hamon::invoke(std::forward<Args>(args)...))
{
	hamon::invoke(std::forward<Args>(args)...);
}

template <typename R, typename... Args>
HAMON_CXX14_CONSTEXPR R
invoke_r_impl(hamon::detail::overload_priority<0>, Args&&... args)
HAMON_NOEXCEPT_IF_EXPR(hamon::invoke(std::forward<Args>(args)...))
{
	return hamon::invoke(std::forward<Args>(args)...);
}

}	// namespace detail

template <typename R, typename F, typename... Args
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, typename = hamon::enable_if_t<hamon::is_invocable_r<R, F, Args...>::value>
#endif
>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::is_invocable_r<R, F, Args...>::value
#endif
HAMON_CXX14_CONSTEXPR R
invoke_r(F&& f, Args&&... args)
HAMON_NOEXCEPT_IF_EXPR(hamon::invoke(std::forward<F>(f), std::forward<Args>(args)...))
{
	return hamon::detail::invoke_r_impl<R>(
		hamon::detail::overload_priority<1>{},
		std::forward<F>(f), std::forward<Args>(args)...);
}

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_INVOKE_R_HPP
