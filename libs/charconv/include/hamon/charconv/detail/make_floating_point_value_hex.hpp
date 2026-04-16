/**
 *	@file	make_floating_point_value_hex.hpp
 *
 *	@brief	make_floating_point_value_hex の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_VALUE_HEX_HPP
#define HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_VALUE_HEX_HPP

#include <hamon/charconv/detail/copy_mantissa_digits.hpp>
#include <hamon/charconv/detail/from_chars_integer.hpp>
#include <hamon/charconv/detail/make_floating_point_value.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/limits.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
inline HAMON_CXX14_CONSTEXPR hamon::errc
make_floating_point_value_hex(
	hamon::string_view integer_part_str,
	hamon::string_view fraction_part_str,
	hamon::int64_t exponent,
	bool negative,
	F& value) HAMON_NOEXCEPT
{
	constexpr hamon::int64_t exponent_max = hamon::numeric_limits<F>::max_exponent + 4;
	constexpr hamon::int64_t exponent_min = hamon::numeric_limits<F>::min_exponent - hamon::numeric_limits<F>::digits;

	// 指数の値が範囲外のときは、result_out_of_range
	if (exponent < exponent_min || exponent_max < exponent )
	{
		return hamon::errc::result_out_of_range;
	}

	// 仮数部を1つの文字列にまとめる

	constexpr hamon::size_t mantissa_digits_length_max = 16;

	char mantissa_digits_buf[mantissa_digits_length_max] = {};
	char* mantissa_digits_first = hamon::begin(mantissa_digits_buf);
	char* mantissa_digits_last  = hamon::end(mantissa_digits_buf);

	// 文字列が途中で打ち切られたか
	// 文字列の末尾の0はあらかじめ取り除かれているので、
	// 途中で打ち切られたということはそれ以降に0以外が登場するということ。
	// これは最後の値の丸めに影響してくる。
	bool has_zero_tail = true;

	{
		char* it = mantissa_digits_first;
		it = copy_mantissa_digits(it, mantissa_digits_last, integer_part_str, &has_zero_tail);
		it = copy_mantissa_digits(it, mantissa_digits_last, fraction_part_str, &has_zero_tail);
		mantissa_digits_last = it;
	}

	auto const mantissa_digits_length = mantissa_digits_last - mantissa_digits_first;

	auto e = static_cast<hamon::int32_t>(exponent - mantissa_digits_length * 4);

	hamon::uint64_t m{};
	hamon::detail::from_chars_integer(
		mantissa_digits_first,
		mantissa_digits_last,
		m,
		16);

	return make_floating_point_value(m, e, negative, has_zero_tail, value);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_VALUE_HEX_HPP
