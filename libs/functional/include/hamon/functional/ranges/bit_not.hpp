/**
 *	@file	bit_not.hpp
 *
 *	@brief	ranges::bit_not クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_BIT_NOT_HPP
#define HAMON_FUNCTIONAL_RANGES_BIT_NOT_HPP

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::bit_not
 */
struct bit_not
{
	template <typename T>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator()(T&& x) const
	HAMON_NOEXCEPT_IF_EXPR(~std::declval<T>())
	->decltype(~hamon::forward<T>(x))
	{
		return ~hamon::forward<T>(x);
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_RANGES_BIT_NOT_HPP
