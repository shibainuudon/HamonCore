/**
 *	@file	make_floating_point_value_dec.hpp
 *
 *	@brief	make_floating_point_value_dec の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_VALUE_DEC_HPP
#define HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_VALUE_DEC_HPP

#include <hamon/charconv/detail/big_int.hpp>
#include <hamon/charconv/detail/copy_mantissa_digits.hpp>
#include <hamon/charconv/detail/make_floating_point_value.hpp>
#include <hamon/cstddef.hpp>
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
make_floating_point_value_dec(
	hamon::string_view integer_part_str,
	hamon::string_view fraction_part_str,
	hamon::int64_t exponent,
	bool negative,
	F& value) HAMON_NOEXCEPT
{
	constexpr hamon::int64_t exponent10_max = hamon::numeric_limits<F>::max_exponent10 + 1;
	constexpr hamon::int64_t exponent10_min = hamon::numeric_limits<F>::min_exponent10 - hamon::numeric_limits<F>::max_digits10 + 1;

	// 指数の値が範囲外のときは、result_out_of_range
	if (exponent < exponent10_min || exponent10_max < exponent)
	{
		return hamon::errc::result_out_of_range;
	}

	// 仮数部を1つの文字列にまとめ、指数を調整する

	constexpr hamon::size_t mantissa_digits_length_max = 768;	// TODO: 何文字まで見るか

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

	hamon::int64_t const p = exponent - mantissa_digits_length;
//	HAMON_ASSERT(p >= -1091);
//	HAMON_ASSERT(p <= 308);

	// mantissaのために必要なビット数
	constexpr auto required_mantissa_bits = hamon::numeric_limits<F>::digits + 1;	// +1 は roundingのために必要

	using namespace from_chars_detail;
	using BigInt = big_int<
		2552	// ceil(log2(10^768))
		+ required_mantissa_bits
	>;

	BigInt d{};
	unchecked_from_chars_dec(mantissa_digits_first, mantissa_digits_last, d);

	// この時点で、10進での仮数(d)と指数(p)が得られた。
	// d * pow(10, p) が最終的に求めたい値である。
	//
	// これを、2進での仮数(m)と指数(e)に変換したい
	// d * pow(10, p) == d * pow(5, p) * pow(2, p)　なので、
	// m == d * pow(5, p)
	// e == p
	// となる。

	auto e = static_cast<hamon::int32_t>(p);

	if (e < 0)
	{
		BigInt const denominator = pow5<BigInt>(-e);

		// d のビット数が denominator のビット数+required_mantissa_bits になるようにする
		// 理由：
		// d のビット数が小さすぎる場合、割り算をした結果の精度が不足する
		// d のビット数が大きすぎる場合、割り算の計算量が不必要に大きくなる
		int const shift = bit_width(denominator) + required_mantissa_bits - bit_width(d);
		if (shift > 0)
		{
			d <<= shift;
			e -= shift;
		}
		else if (shift < 0)
		{
			if (-shift > countr_zero(d))
			{
				has_zero_tail = false;
			}
			d >>= -shift;
			e -= shift;
		}

		// quo = d / denominator;
		// rem = d % denominator;
		BigInt quo;
		BigInt rem = div_mod(d, denominator, &quo);
		if (!is_zero(rem))
		{
			has_zero_tail = false;
		}

		d = quo;
	}
	else
	{
		if (e > 0)
		{
			d *= from_chars_detail::pow5<BigInt>(e);
		}

		// 上位ビットだけにする
		int const shift = bit_width(d) - required_mantissa_bits;
		if (shift > 0)
		{
			if (shift > countr_zero(d))
			{
				has_zero_tail = false;
			}
			d >>= shift;
			e += shift;
		}
	}

	HAMON_ASSERT(bit_width(d) <= 64);
	hamon::uint64_t m = d.to_uint64();

	return make_floating_point_value(m, e, negative, has_zero_tail, value);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_VALUE_DEC_HPP
