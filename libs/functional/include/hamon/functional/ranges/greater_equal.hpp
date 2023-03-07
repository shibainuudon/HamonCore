/**
 *	@file	greater_equal.hpp
 *
 *	@brief	ranges::greater_equal クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_GREATER_EQUAL_HPP
#define HAMON_FUNCTIONAL_RANGES_GREATER_EQUAL_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_RANGES_FUNCTIONAL)

#include <functional>

namespace hamon
{
namespace ranges
{

using std::ranges::greater_equal;

}	// namespace ranges
}	// namespace hamon

#else

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
 *	@brief	ranges::greater_equal
 */
struct greater_equal
{
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename T, typename U>
	requires
		hamon::totally_ordered_with<T, U> ||
		detail::less_builtin_ptr_cmp<T, U>
#else
	template <typename T, typename U,
		typename = hamon::enable_if_t<
			hamon::totally_ordered_with<T, U>::value ||
			detail::less_builtin_ptr_cmp<U, T>::value
		>
	>
#endif
	HAMON_NODISCARD HAMON_CONSTEXPR bool operator()(T&& t, U&& u) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::declval<T>() < hamon::declval<U>())
	{
		return !hamon::ranges::less{}(hamon::forward<T>(t), hamon::forward<U>(u));
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_RANGES_GREATER_EQUAL_HPP
