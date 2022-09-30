/**
 *	@file	invocable.hpp
 *
 *	@brief	invocable の定義
 */

#ifndef HAMON_CONCEPTS_INVOCABLE_HPP
#define HAMON_CONCEPTS_INVOCABLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/is_invocable.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::invocable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Fn, typename... Args>
concept invocable = hamon::is_invocable<Fn, Args...>::value;

#else

template <typename Fn, typename... Args>
using invocable = hamon::is_invocable<Fn, Args...>;

#endif

}	// namespace hamon

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Fn, typename... Args>
using invocable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::invocable<Fn, Args...>>;
#else
	hamon::invocable<Fn, Args...>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_INVOCABLE_HPP
