/**
 *	@file	to_chars_floating_point_precision_fixed.hpp
 *
 *	@brief	to_chars_floating_point_precision_fixed の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_FIXED_HPP
#define HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_FIXED_HPP

#include <hamon/charconv/to_chars_result.hpp>
#include <hamon/charconv/detail/ryu/d2fixed.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/system_error/errc.hpp>

namespace hamon
{

namespace detail
{

template <typename Floating>
inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result
to_chars_floating_point_precision_fixed(char* first, char* last, Floating value, int precision) noexcept
{
	// C11 7.21.6.1 "The fprintf function"/5:
	// "A negative precision argument is taken as if the precision were omitted."
	// /8: "f,F [...] If the precision is missing, it is taken as 6"

	if (precision < 0)
	{
		precision = 6;
	}
	else if (precision >= 1000000000)
	{
		// Avoid integer overflow.
		// (This defensive check is slightly nonconformant; it can be carefully improved in the future.)
		return { last, hamon::errc::value_too_large };
	}

	return ryu::d2fixed_buffered_n(first, last, value, static_cast<hamon::uint32_t>(precision));
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_FIXED_HPP
