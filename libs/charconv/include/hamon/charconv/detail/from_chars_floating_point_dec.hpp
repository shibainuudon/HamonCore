/**
 *	@file	from_chars_floating_point_dec.hpp
 *
 *	@brief	from_chars_floating_point_dec の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_DEC_HPP
#define HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_DEC_HPP

#include <hamon/charconv/chars_format.hpp>
#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/charconv/detail/from_chars_integer.hpp>
#include <hamon/charconv/detail/remove_leading_zeros.hpp>
#include <hamon/charconv/detail/remove_trailing_zeros.hpp>
#include <hamon/charconv/detail/make_floating_point_value.hpp>
#include <hamon/charconv/detail/make_floating_point_zero.hpp>
#include <hamon/bigint.hpp>
#include <hamon/cctype/isdigit.hpp>
#include <hamon/cctype/tolower.hpp>
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
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_floating_point_dec(const char* first, const char* last, F& value, hamon::chars_format fmt, bool negative, const char* ptr) HAMON_NOEXCEPT
{
	// pre:
	// first は from_chars に渡された文字列の最初
	// ptr は'-'記号を除いた文字列の最初

	// 仮数部のうちの整数部の文字列を得る
	const char* integer_part_first = ptr;
	for (; ptr != last; ++ptr)
	{
		if (!hamon::isdigit(*ptr))
		{
			break;
		}
	}
	hamon::string_view integer_part_str{integer_part_first, ptr};

	// 小数点 '.' を飛ばす
	if (ptr != last && *ptr == '.')
	{
		++ptr;
	}

	// 仮数部のうちの小数部の文字列を得る
	const char* fraction_part_first = ptr;
	for (; ptr != last; ++ptr)
	{
		if (!hamon::isdigit(*ptr))
		{
			break;
		}
	}
	hamon::string_view fraction_part_str{fraction_part_first, ptr};

	// 整数部も小数部も空の場合は、無効な引数
	if (integer_part_str.empty() && fraction_part_str.empty())
	{
		return {first, hamon::errc::invalid_argument};
	}

	// 指数部の値を得る
	bool found_exponent = false;
	const char exponent_prefix = 'e';
	hamon::int64_t exponent = 0;

	// [charconv.from.chars]/6.3
	if (fmt != hamon::chars_format::fixed)
	{
		if (ptr != last && hamon::tolower(*ptr) == exponent_prefix)
		{
			auto p = ptr;
			++p;

			// 指数部は仮数部と違って'+'記号があっても良い
			auto ret = hamon::detail::from_chars_integer(p, last, exponent, 10, true/*allow_plus_sign*/);
			if (ret.ec == hamon::errc::result_out_of_range)
			{
				return ret;
			}

			if (ret.ec == hamon::errc{})
			{
				ptr = ret.ptr;
				found_exponent = true;
			}
		}
	}

	// [charconv.from.chars]/6.2
	if (fmt == hamon::chars_format::scientific)
	{
		if (!found_exponent)
		{
			return {first, hamon::errc::invalid_argument};
		}
	}

	// 整数部の先頭の0と、小数部の末尾の0は無条件で取り除ける
	integer_part_str = remove_leading_zeros(integer_part_str);
	fraction_part_str = remove_trailing_zeros(fraction_part_str);

	// 仮数部の整数部も小数部も0のとき、指数の値にかかわらず全体としての値も0になる。
	// (ptrを正しく更新しないといけないため、指数部のスキャンが終わってからリターンする)
	if (integer_part_str.empty() && fraction_part_str.empty())
	{
		value = make_floating_point_zero<F>(negative);
		return {ptr, hamon::errc{}};
	}

	// 指数を調整しつつ、可能な限り文字列を切り詰める
	if (!integer_part_str.empty())
	{
		exponent += static_cast<hamon::int64_t>(integer_part_str.length());
		if (fraction_part_str.empty())
		{
			// 小数部が0のときは、整数部の末尾の0を削除する
			integer_part_str = remove_trailing_zeros(integer_part_str);
		}
	}
	else
	{
		// 整数部が0のときは、小数部の先頭の0を削除する
		exponent -= static_cast<hamon::int64_t>(fraction_part_str.length());
		fraction_part_str = remove_leading_zeros(fraction_part_str);
		exponent += static_cast<hamon::int64_t>(fraction_part_str.length());
	}

	constexpr hamon::int64_t exponent10_max = hamon::numeric_limits<F>::max_exponent10 + 1;
	constexpr hamon::int64_t exponent10_min = hamon::numeric_limits<F>::min_exponent10 - hamon::numeric_limits<F>::max_digits10;

	// 指数の値が範囲外のときは、result_out_of_range
	if (exponent < exponent10_min || exponent10_max < exponent)
	{
		return {ptr, hamon::errc::result_out_of_range};
	}

	// 仮数部を1つの文字列にまとめ、指数を調整する
	constexpr hamon::size_t mantissa_digits_length_max = 768;	// TODO: 何文字まで見るか

	char mantissa_digits[mantissa_digits_length_max] = {};
	char* mantissa_digits_first = hamon::begin(mantissa_digits);
	char* mantissa_digits_last  = hamon::end(mantissa_digits);
	char* mantissa_digits_it = mantissa_digits_first;

	// 文字列が途中で打ち切られたか
	// 文字列の末尾の0はあらかじめ取り除かれているので、
	// 途中で打ち切られたということはそれ以降に0以外が登場するということ。
	// これは最後の値の丸めに影響してくる。
	bool has_zero_tail = true;

	auto p = static_cast<int>(exponent);

	for (auto it = integer_part_str.begin(); it != integer_part_str.end(); ++it)
	{
		if (mantissa_digits_it == mantissa_digits_last)
		{
			has_zero_tail = false;
			break;
		}
		*mantissa_digits_it++ = *it;
		p--;
	}

	for (auto it = fraction_part_str.begin(); it != fraction_part_str.end(); ++it)
	{
		if (mantissa_digits_it == mantissa_digits_last)
		{
			has_zero_tail = false;
			break;
		}
		*mantissa_digits_it++ = *it;
		p--;
	}

//	HAMON_ASSERT(p >= -1091);
//	HAMON_ASSERT(p <= 308);

	constexpr auto shift_space = hamon::numeric_limits<F>::digits + 1;	// mantissa_bits + 2

	using BigInt = hamon::inplace_bigint<
		2552	// ceil(log2(10^768))
		+ shift_space
	>;

	BigInt d{};
	hamon::from_chars(
		mantissa_digits_first,
		mantissa_digits_it,
		d,
		10);

	// この時点で、10進での仮数(d)と指数(p)が得られた。
	// d * pow(10, p) が最終的に求めたい値である。
	//
	// これを、2進での仮数(m)と指数(e)に変換したい
	// d * pow(10, p) == d * pow(5, p) * pow(2, p)　なので、
	// m == d * pow(5, p)
	// e == p
	// となる。

	hamon::int32_t e = p;

	if (p >= 0)
	{
		BigInt s{};
		hamon::pow_n(s, BigInt{5}, static_cast<hamon::uintmax_t>(p));
		d *= s;
	}
	else
	{
		BigInt denominator{};
		hamon::pow_n(denominator, BigInt{5}, static_cast<hamon::uintmax_t>(-p));

		// d のビット数が denominator のビット数+shift_space を上回るようにする
		// (そうしないと、割り算をした結果の精度が不足するため)
		int const shift = hamon::bit_width(denominator) + shift_space - hamon::bit_width(d);
		if (shift > 0)
		{
			d <<= static_cast<hamon::size_t>(shift);
			e -= shift;
		}

		auto quo = d / denominator;
		if (quo * denominator != d)	// if (d % denominator != 0)
		{
			has_zero_tail = false;
		}
		d = quo;
	}

	// 上位ビットだけにする
	int shift = hamon::bit_width(d) - shift_space;
	if (shift > 0)
	{
		if (shift > hamon::countr_zero(d))
		{
			has_zero_tail = false;
		}
		d >>= static_cast<hamon::size_t>(shift);
		e += shift;
	}

	hamon::uint64_t m = static_cast<hamon::uint64_t>(d);

	auto const ec = make_floating_point_value(m, e, negative, has_zero_tail, value);
	return {ptr, ec};
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_DEC_HPP
