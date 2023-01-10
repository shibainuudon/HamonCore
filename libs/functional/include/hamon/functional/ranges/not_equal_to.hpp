/**
 *	@file	not_equal_to.hpp
 *
 *	@brief	ranges::not_equal_to クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_NOT_EQUAL_TO_HPP
#define HAMON_FUNCTIONAL_RANGES_NOT_EQUAL_TO_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_RANGES_FUNCTIONAL)

#include <functional>

namespace hamon
{
namespace ranges
{

using std::ranges::not_equal_to;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/detail/eq_builtin_ptr_cmp.hpp>
#include <hamon/concepts/equality_comparable_with.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::not_equal_to
 */
struct not_equal_to
{
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename T, typename U>
	requires
		hamon::equality_comparable_with<T, U> ||
		detail::eq_builtin_ptr_cmp<T, U>
#else
	template <typename T, typename U,
		typename = hamon::enable_if_t<
			hamon::equality_comparable_with<T, U>::value ||
			detail::eq_builtin_ptr_cmp<T, U>::value
		>
	>
#endif
	HAMON_NODISCARD HAMON_CONSTEXPR bool operator()(T&& t, U&& u) const
		HAMON_NOEXCEPT_IF_EXPR(std::declval<U>() == std::declval<T>())
	{
		return !hamon::ranges::equal_to{}(std::forward<T>(t), std::forward<U>(u));
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_RANGES_NOT_EQUAL_TO_HPP
