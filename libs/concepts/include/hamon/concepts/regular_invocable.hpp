/**
 *	@file	regular_invocable.hpp
 *
 *	@brief	regular_invocable の定義
 */

#ifndef HAMON_CONCEPTS_REGULAR_INVOCABLE_HPP
#define HAMON_CONCEPTS_REGULAR_INVOCABLE_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/invocable.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::regular_invocable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Fn, typename... Args>
concept regular_invocable = hamon::invocable<Fn, Args...>;

#else

template <typename Fn, typename... Args>
using regular_invocable = hamon::invocable<Fn, Args...>;

#endif

template <typename Fn, typename... Args>
using regular_invocable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::regular_invocable<Fn, Args...>>;
#else
	hamon::regular_invocable<Fn, Args...>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_REGULAR_INVOCABLE_HPP
