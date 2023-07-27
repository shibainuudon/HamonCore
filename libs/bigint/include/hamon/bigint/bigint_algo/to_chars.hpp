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
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/charconv/to_chars.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace to_chars_detail
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars(char* first, char* last, VectorType value, int base)
{
	using T = hamon::ranges::range_value_t<VectorType>;

	auto const base2 = VectorType{static_cast<T>(base)};

	auto p = first;
	while (p != last)
	{
		auto r = bigint_algo::div_mod(value, base2);
		value = r.quo;
		p = hamon::to_chars(p, p+1, r.rem[0], base).ptr;

		if (bigint_algo::compare(value, VectorType{0}) == 0)
		{
			break;
		}
	}

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
