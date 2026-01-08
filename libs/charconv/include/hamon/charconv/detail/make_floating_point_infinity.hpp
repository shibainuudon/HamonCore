/**
 *	@file	make_floating_point_infinity.hpp
 *
 *	@brief	make_floating_point_infinity の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_INFINITY_HPP
#define HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_INFINITY_HPP

#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
HAMON_NODISCARD inline F
make_floating_point_infinity(bool negative) noexcept
{
	static_assert(hamon::numeric_limits<F>::has_infinity, "");

	if (negative)
	{
		return -hamon::numeric_limits<F>::infinity();
	}
	else
	{
		return hamon::numeric_limits<F>::infinity();
	}
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_INFINITY_HPP
