/**
 *	@file	to_chars.hpp
 *
 *	@brief	to_chars 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_HPP
#define HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_HPP

#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/bigint/bigint_algo/div_mod.hpp>
#include <hamon/algorithm/reverse.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/cmath/log2.hpp>
#include <hamon/cmath/floor.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/charconv/to_chars.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{
namespace bigint_algo
{

namespace to_chars_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
to_chars_reverse(char* first, char* last, T value, int base)
{
	for (char* p = first; p != last; ++p)
	{
		auto c = value % static_cast<T>(base);
		value = value / static_cast<T>(base);
		*p = "0123456789abcdefghijklmnopqrstuvwxyz"[c];
	}
}

inline HAMON_CXX14_CONSTEXPR char*
remove_trailing_zeros(char* first, char* last)
{
	char* p = last - 1;
	while (p > first)
	{
		if (*p != '0')
		{
			break;
		}
		--p;
	}
	return p+1;
}

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars(char* first, char* last, VectorType value, int base)
{
	using T = hamon::ranges::range_value_t<VectorType>;
	
	auto const digits = static_cast<hamon::ptrdiff_t>(hamon::floor(std::numeric_limits<T>::digits / hamon::log2(base)));

	// base2 = pow_n(base, digits)
	auto base2 = VectorType{1};
	VectorType tmp;
	for (int i = 0; i < digits; ++i)
	{
		bigint_algo::multiply(tmp, base2, static_cast<T>(base));
		base2 = tmp;
	}

	auto p = first;
	while (p != last)
	{
		auto r = bigint_algo::div_mod(value, base2);
		value = r.quo;
		auto p2 = hamon::min(p + digits, last);
		to_chars_reverse(p, p2, r.rem[0], base);
		p = p2;

		if (bigint_algo::compare(value, VectorType{0}) == 0)
		{
			break;
		}
	}

	p = remove_trailing_zeros(first, p);

	if (p == last)
	{
		return {last, std::errc::value_too_large};
	}

	hamon::reverse(first, p);

	return {p, std::errc{}};
}

}	// namespace to_chars_detail

template <typename T>
inline hamon::to_chars_result
to_chars(char* first, char* last, std::vector<T> const& value, int base = 10)
{
	return to_chars_detail::to_chars(first, last, value, base);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars(char* first, char* last, hamon::array<T, N> const& value, int base = 10)
{
	return to_chars_detail::to_chars(first, last, value, base);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_to_chars_HPP
