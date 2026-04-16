/**
 *	@file	from_chars_floating_point_ordinary.hpp
 *
 *	@brief	from_chars_floating_point_ordinary の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_ORDINARY_HPP
#define HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_ORDINARY_HPP

#include <hamon/charconv/chars_format.hpp>
#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/charconv/detail/from_chars_integer.hpp>
#include <hamon/charconv/detail/remove_leading_zeros.hpp>
#include <hamon/charconv/detail/remove_trailing_zeros.hpp>
#include <hamon/charconv/detail/make_floating_point_zero.hpp>
#include <hamon/charconv/detail/make_floating_point_value_hex.hpp>
#include <hamon/charconv/detail/make_floating_point_value_dec.hpp>
#include <hamon/cctype/isdigit.hpp>
#include <hamon/cctype/isxdigit.hpp>
#include <hamon/cctype/tolower.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

inline HAMON_CXX14_CONSTEXPR hamon::string_view
parse_digit_string(const char* first, const char* last)
{
	const char* ptr = first;
	for (; ptr != last; ++ptr)
	{
		if (!hamon::isdigit(*ptr))
		{
			break;
		}
	}
	return {first, ptr};
}

inline HAMON_CXX14_CONSTEXPR hamon::string_view
parse_xdigit_string(const char* first, const char* last)
{
	const char* ptr = first;
	for (; ptr != last; ++ptr)
	{
		if (!hamon::isxdigit(*ptr))
		{
			break;
		}
	}
	return {first, ptr};
}

inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
parse_exponent(const char* first, const char* last, hamon::int64_t& exponent, hamon::chars_format fmt)
{
	char const exponent_prefix = (fmt == hamon::chars_format::hex) ? 'p' : 'e';

	// [charconv.from.chars]/6.3
	if (fmt != hamon::chars_format::fixed)
	{
		if (first != last && hamon::tolower(*first) == exponent_prefix)
		{
			// 指数部は仮数部と違って'+'記号があっても良い
			auto ret = hamon::detail::from_chars_integer(first + 1, last, exponent, 10, true/*allow_plus_sign*/);
			if (ret.ec != hamon::errc::invalid_argument)
			{
				return ret;
			}
		}
	}

	// [charconv.from.chars]/6.2
	if (fmt == hamon::chars_format::scientific)
	{
		return {first, hamon::errc::invalid_argument};
	}

	return {first, hamon::errc{}};
}

template <typename F>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_floating_point_ordinary(const char* first, const char* last, F& value, hamon::chars_format fmt, bool negative) HAMON_NOEXCEPT
{
	// pre: first は'-'記号を除いた文字列の最初を指している

	// 仮数部のうちの整数部の文字列を得る
	hamon::string_view integer_part_str;
	if (fmt == hamon::chars_format::hex)
	{
		integer_part_str = parse_xdigit_string(first, last);
	}
	else
	{
		integer_part_str = parse_digit_string(first, last);
	}
	first += integer_part_str.length();

	// 小数点 '.' を飛ばす
	if (first != last && *first == '.')
	{
		++first;
	}
	
	// 仮数部のうちの小数部の文字列を得る
	hamon::string_view fraction_part_str;
	if (fmt == hamon::chars_format::hex)
	{
		fraction_part_str = parse_xdigit_string(first, last);
	}
	else
	{
		fraction_part_str = parse_digit_string(first, last);
	}
	first += fraction_part_str.length();

	// 整数部も小数部も空の場合は、無効な引数
	if (integer_part_str.empty() && fraction_part_str.empty())
	{
		return {first, hamon::errc::invalid_argument};
	}

	// 指数部の値を得る
	hamon::int64_t exponent = 0;
	{
		auto ret = parse_exponent(first, last, exponent, fmt);
		if (!ret)
		{
			return ret;
		}
		first = ret.ptr;
	}

	// 整数部の先頭の0と、小数部の末尾の0は無条件で取り除ける
	integer_part_str = remove_leading_zeros(integer_part_str);
	fraction_part_str = remove_trailing_zeros(fraction_part_str);

	// 仮数部の整数部も小数部も0のとき、指数の値にかかわらず全体としての値も0になる。
	// (firstを正しく更新しないといけないため、指数部のスキャンが終わってからリターンする)
	if (integer_part_str.empty() && fraction_part_str.empty())
	{
		value = make_floating_point_zero<F>(negative);
		return {first, hamon::errc{}};
	}

	int const exponent_multiplier = (fmt == hamon::chars_format::hex) ? 4 : 1;

	// 指数を調整しつつ、可能な限り文字列を切り詰める
	if (!integer_part_str.empty())
	{
		exponent += static_cast<hamon::int64_t>(integer_part_str.length()) * exponent_multiplier;
		if (fraction_part_str.empty())
		{
			// 小数部が0のときは、整数部の末尾の0を削除する
			integer_part_str = remove_trailing_zeros(integer_part_str);
		}
	}
	else
	{
		// 整数部が0のときは、小数部の先頭の0を削除する
		exponent -= static_cast<hamon::int64_t>(fraction_part_str.length()) * exponent_multiplier;
		fraction_part_str = remove_leading_zeros(fraction_part_str);
		exponent += static_cast<hamon::int64_t>(fraction_part_str.length()) * exponent_multiplier;
	}

	if (fmt == hamon::chars_format::hex)
	{
		auto const ec = make_floating_point_value_hex(integer_part_str, fraction_part_str, exponent, negative, value);
		return {first, ec};
	}
	else
	{
		auto const ec = make_floating_point_value_dec(integer_part_str, fraction_part_str, exponent, negative, value);
		return {first, ec};
	}
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_ORDINARY_HPP
