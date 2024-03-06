/**
 *	@file	div_ceil.hpp
 *
 *	@brief	div_ceil の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_DIV_CEIL_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_DIV_CEIL_HPP

#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

template <typename I>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
I div_ceil(I num, I denom) HAMON_NOEXCEPT	// noexcept as an extension
{
	return static_cast<I>((num / denom) + ((num % denom) ? 1 : 0));
}

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_DIV_CEIL_HPP
