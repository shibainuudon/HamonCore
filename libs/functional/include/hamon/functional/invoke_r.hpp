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
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace detail
{

template <typename R, typename... Args>
HAMON_CXX14_CONSTEXPR R
invoke_r_impl(std::true_type, Args&&... args)
HAMON_NOEXCEPT_IF_EXPR(hamon::invoke(std::forward<Args>(args)...))
{
	hamon::invoke(std::forward<Args>(args)...);
}

template <typename R, typename... Args>
HAMON_CXX14_CONSTEXPR R
invoke_r_impl(std::false_type, Args&&... args)
HAMON_NOEXCEPT_IF_EXPR(hamon::invoke(std::forward<Args>(args)...))
{
	return hamon::invoke(std::forward<Args>(args)...);
}

}	// namespace detail

template <typename R, typename F, typename... Args>
#if defined(HAMON_HAS_CXX20_CONCEPTS) &&	\
	!(defined(HAMON_APPLE_CLANG) && (HAMON_APPLE_CLANG <= 130000))
requires hamon::is_invocable_r<R, F, Args...>::value
#endif
HAMON_CXX14_CONSTEXPR R
invoke_r(F&& f, Args&&... args)
HAMON_NOEXCEPT_IF_EXPR(hamon::invoke(std::forward<F>(f), std::forward<Args>(args)...))
{
	return hamon::detail::invoke_r_impl<R>(std::is_void<R>{},
		std::forward<F>(f), std::forward<Args>(args)...);
}

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_INVOKE_R_HPP
