/**
 *	@file	less_equal.hpp
 *
 *	@brief	ranges::less_equal クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_LESS_EQUAL_HPP
#define HAMON_FUNCTIONAL_RANGES_LESS_EQUAL_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_RANGES_FUNCTIONAL)

#include <functional>

namespace hamon
{
namespace ranges
{

using std::ranges::less_equal;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/detail/less_builtin_ptr_cmp.hpp>
#include <hamon/concepts/totally_ordered_with.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::less_equal
 */
struct less_equal
{
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename T, typename U>
	requires
		hamon::totally_ordered_with<T, U> ||
		detail::less_builtin_ptr_cmp<U, T>
#else
	template <typename T, typename U,
		typename = hamon::enable_if_t<
			hamon::totally_ordered_with<T, U>::value ||
			detail::less_builtin_ptr_cmp<U, T>::value
		>
	>
#endif
	HAMON_NODISCARD HAMON_CONSTEXPR bool operator()(T&& t, U&& u) const
		HAMON_NOEXCEPT_IF_EXPR(std::declval<U>() < std::declval<T>())
	{
		return !hamon::ranges::less{}(std::forward<U>(u), std::forward<T>(t));
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_RANGES_LESS_EQUAL_HPP
