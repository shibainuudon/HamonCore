/**
 *	@file	make_floating_point_zero.hpp
 *
 *	@brief	make_floating_point_zero の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_ZERO_HPP
#define HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_ZERO_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
HAMON_NODISCARD inline F
make_floating_point_zero(bool negative) noexcept
{
	return negative ? F{-0.0} : F{0.0};
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_ZERO_HPP
