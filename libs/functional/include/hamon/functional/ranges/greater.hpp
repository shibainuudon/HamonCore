/**
 *	@file	greater.hpp
 *
 *	@brief	ranges::greater クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_GREATER_HPP
#define HAMON_FUNCTIONAL_RANGES_GREATER_HPP

#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/detail/less_builtin_ptr_cmp.hpp>
#include <hamon/concepts/totally_ordered_with.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::greater
 */
struct greater
{
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename T, typename U>
	requires
		hamon::totally_ordered_with<T, U> ||
		detail::less_builtin_ptr_cmp<U, T>
#else
	template <typename T, typename U,
		typename = hamon::enable_if_t<
			hamon::totally_ordered_with<T, U> ||
			detail::less_builtin_ptr_cmp<U, T>
		>
	>
#endif
	HAMON_NODISCARD HAMON_CONSTEXPR bool operator()(T&& t, U&& u) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::declval<U>() < hamon::declval<T>())
	{
		return hamon::ranges::less{}(hamon::forward<U>(u), hamon::forward<T>(t));
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_RANGES_GREATER_HPP
