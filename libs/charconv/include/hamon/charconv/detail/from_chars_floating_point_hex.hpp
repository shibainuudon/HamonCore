/**
 *	@file	from_chars_floating_point_hex.hpp
 *
 *	@brief	from_chars_floating_point_hex の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HEX_HPP
#define HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HEX_HPP

#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/charconv/detail/from_chars_integer.hpp>
#include <hamon/charconv/detail/remove_leading_zeros.hpp>
#include <hamon/charconv/detail/remove_trailing_zeros.hpp>
#include <hamon/charconv/detail/make_floating_point_value.hpp>
#include <hamon/charconv/detail/make_floating_point_zero.hpp>
#include <hamon/cctype/isxdigit.hpp>
#include <hamon/cctype/tolower.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_floating_point_hex(const char* first, const char* last, F& value, bool negative, const char* ptr) HAMON_NOEXCEPT
{
	// pre:
	// first は from_chars に渡された文字列の最初
	// ptr は'-'記号を除いた文字列の最初

	// 仮数部のうちの整数部の文字列を得る
	const char* integer_part_first = ptr;
	for (; ptr != last; ++ptr)
	{
		if (!hamon::isxdigit(*ptr))
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
		if (!hamon::isxdigit(*ptr))
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
	const char exponent_prefix = 'p';
	hamon::int64_t exponent = 0;

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
		exponent += integer_part_str.length() * 4;
		if (fraction_part_str.empty())
		{
			// 小数部が0のときは、整数部の末尾の0を削除する
			integer_part_str = remove_trailing_zeros(integer_part_str);
		}
	}
	else
	{
		// 整数部が0のときは、小数部の先頭の0を削除する
		exponent -= fraction_part_str.length() * 4;
		fraction_part_str = remove_leading_zeros(fraction_part_str);
		exponent += fraction_part_str.length() * 4;
	}

	//if (hamon::numeric_limits<F>::max_exponent < exponent )
	//{
	//	return {ptr, hamon::errc::result_out_of_range};
	//}
	//if (exponent < hamon::numeric_limits<F>::min_exponent)
	//{
	//	return {ptr, hamon::errc::result_out_of_range};
	//}

	// 仮数部を1つの文字列にまとめ、指数を調整する
	constexpr hamon::size_t mantissa_digits_length_max = 16;

	char mantissa_digits[mantissa_digits_length_max] = {};
	char* mantissa_digits_first = hamon::begin(mantissa_digits);
	char* mantissa_digits_last  = hamon::end(mantissa_digits);
	char* mantissa_digits_it = mantissa_digits_first;

	// 文字列が途中で打ち切られたか
	// 文字列の末尾の0はあらかじめ取り除かれているので、
	// 途中で打ち切られたということはそれ以降に0以外が登場するということ。
	// これは最後の値の丸めに影響してくる。
	bool has_zero_tail = true;

	auto e = static_cast<int>(exponent);

	for (auto it = integer_part_str.begin(); it != integer_part_str.end(); ++it)
	{
		if (mantissa_digits_it == mantissa_digits_last)
		{
			has_zero_tail = false;
			break;
		}
		*mantissa_digits_it++ = *it;
		e -= 4;
	}

	for (auto it = fraction_part_str.begin(); it != fraction_part_str.end(); ++it)
	{
		if (mantissa_digits_it == mantissa_digits_last)
		{
			has_zero_tail = false;
			break;
		}
		*mantissa_digits_it++ = *it;
		e -= 4;
	}

	hamon::uint64_t m{};
	hamon::detail::from_chars_integer(
		mantissa_digits_first,
		mantissa_digits_it,
		m,
		16);

	auto const ec = make_floating_point_value(m, e, negative, has_zero_tail, value);
	return {ptr, ec};
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HEX_HPP
