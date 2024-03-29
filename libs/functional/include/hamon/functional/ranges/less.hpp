﻿/**
 *	@file	less.hpp
 *
 *	@brief	ranges::less クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_LESS_HPP
#define HAMON_FUNCTIONAL_RANGES_LESS_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_RANGES_FUNCTIONAL)

#include <functional>

namespace hamon
{
namespace ranges
{

using std::ranges::less;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/functional/detail/less_builtin_ptr_cmp.hpp>
#include <hamon/concepts/totally_ordered_with.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::less
 */
struct less
{
private:
	template <typename T, typename U
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			detail::less_builtin_ptr_cmp<T, U>::value
		>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires detail::less_builtin_ptr_cmp<T, U>
#endif
	static HAMON_CXX14_CONSTEXPR bool impl(hamon::detail::overload_priority<1>, T&& t, U&& u)
		HAMON_NOEXCEPT_IF_EXPR(hamon::declval<T>() < hamon::declval<U>())
	{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return t < u;
		}
#endif
		auto x = reinterpret_cast<hamon::uintptr_t>(
			static_cast<const volatile void*>(hamon::forward<T>(t)));
		auto y = reinterpret_cast<hamon::uintptr_t>(
			static_cast<const volatile void*>(hamon::forward<U>(u)));
		return x < y;
	}

	template <typename T, typename U
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			hamon::totally_ordered_with<T, U>::value
		>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::totally_ordered_with<T, U>
#endif
	static HAMON_CONSTEXPR bool impl(hamon::detail::overload_priority<0>, T&& t, U&& u)
		HAMON_NOEXCEPT_IF_EXPR(hamon::declval<T>() < hamon::declval<U>())
	{
		return hamon::forward<T>(t) < hamon::forward<U>(u);
	}

public:
	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator()(T&& t, U&& u) const
		HAMON_NOEXCEPT_IF_EXPR(impl(hamon::detail::overload_priority<1>{}, hamon::forward<T>(t), hamon::forward<U>(u)))
	->decltype(impl(hamon::detail::overload_priority<1>{}, hamon::forward<T>(t), hamon::forward<U>(u)))
	{
		return impl(hamon::detail::overload_priority<1>{}, hamon::forward<T>(t), hamon::forward<U>(u));
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_RANGES_LESS_HPP
