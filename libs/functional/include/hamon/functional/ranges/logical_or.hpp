/**
 *	@file	logical_or.hpp
 *
 *	@brief	ranges::logical_or クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_LOGICAL_OR_HPP
#define HAMON_FUNCTIONAL_RANGES_LOGICAL_OR_HPP

#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::logical_or
 */
struct logical_or
{
	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	HAMON_NOEXCEPT_IF_EXPR(std::declval<T>() || std::declval<U>())
	->decltype(std::forward<T>(lhs) || std::forward<U>(rhs))
	{
		return std::forward<T>(lhs) || std::forward<U>(rhs);
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_RANGES_LOGICAL_OR_HPP
