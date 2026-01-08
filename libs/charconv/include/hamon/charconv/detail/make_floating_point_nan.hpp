/**
 *	@file	make_floating_point_nan.hpp
 *
 *	@brief	make_floating_point_nan の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_NAN_HPP
#define HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_NAN_HPP

#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
HAMON_NODISCARD inline F
make_floating_point_nan(bool negative) noexcept
{
	static_assert(hamon::numeric_limits<F>::has_quiet_NaN, "");

	if (negative)
	{
		return -hamon::numeric_limits<F>::quiet_NaN();
	}
	else
	{
		return hamon::numeric_limits<F>::quiet_NaN();
	}
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_NAN_HPP
