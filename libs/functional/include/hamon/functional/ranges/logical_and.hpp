﻿/**
 *	@file	logical_and.hpp
 *
 *	@brief	ranges::logical_and クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_LOGICAL_AND_HPP
#define HAMON_FUNCTIONAL_RANGES_LOGICAL_AND_HPP

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::logical_and
 */
struct logical_and
{
	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	HAMON_NOEXCEPT_IF_EXPR(std::declval<T>() && std::declval<U>())
	->decltype(hamon::forward<T>(lhs) && hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) && hamon::forward<U>(rhs);
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_RANGES_LOGICAL_AND_HPP
