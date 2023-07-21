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
namespace detail
{
namespace bigint_algo
{

namespace to_chars_detail
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars(char* first, char* last, VectorType value, VectorType const& base)
{
	auto p = first;
	while (p != last)
	{
		auto r = bigint_algo::div_mod(value, base);
		value = r.quo;
		p = hamon::to_chars(p, p+1, r.rem[0], static_cast<int>(base[0])).ptr;

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

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars(char* first, char* last, VectorType const& value, int base = 10)
{
	using T = hamon::ranges::range_value_t<VectorType>;
	return to_chars_detail::to_chars(first, last, value, VectorType{static_cast<T>(base)});
}

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_to_chars_HPP
