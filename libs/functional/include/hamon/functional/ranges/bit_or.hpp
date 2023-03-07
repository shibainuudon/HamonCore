﻿/**
 *	@file	bit_or.hpp
 *
 *	@brief	ranges::bit_or クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_BIT_OR_HPP
#define HAMON_FUNCTIONAL_RANGES_BIT_OR_HPP

#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::bit_or
 */
struct bit_or
{
	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	HAMON_NOEXCEPT_IF_EXPR(hamon::declval<T>() | hamon::declval<U>())
	->decltype(hamon::forward<T>(lhs) | hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) | hamon::forward<U>(rhs);
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_RANGES_BIT_OR_HPP
