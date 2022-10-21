/**
 *	@file	divides.hpp
 *
 *	@brief	ranges::divides クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_DIVIDES_HPP
#define HAMON_FUNCTIONAL_RANGES_DIVIDES_HPP

#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::divides
 */
struct divides
{
	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	HAMON_NOEXCEPT_IF_EXPR(std::declval<T>() / std::declval<U>())
	->decltype(std::forward<T>(lhs) / std::forward<U>(rhs))
	{
		return std::forward<T>(lhs) / std::forward<U>(rhs);
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_RANGES_DIVIDES_HPP
