/**
 *	@file	to_chars.hpp
 *
 *	@brief	to_chars 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_HPP
#define HAMON_BIGINT_BIGINT_ALGO_TO_CHARS_HPP

#include <hamon/bigint/bigint_algo/div_mod.hpp>
#include <hamon/bigint/bigint_algo/pow_n.hpp>
#include <hamon/bigint/bigint_algo/is_zero.hpp>
#include <hamon/bigint/bigint_algo/detail/move.hpp>
#include <hamon/bigint/bigint_algo/detail/vector_value_t.hpp>
#include <hamon/algorithm/reverse.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/cmath/log2.hpp>
#include <hamon/cmath/floor.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/charconv/to_chars.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

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
	using T = detail::vector_value_t<VectorType>;
	
	auto const digits = static_cast<hamon::ptrdiff_t>(hamon::floor(hamon::numeric_limits<T>::digits / hamon::log2(base)));

	// base2 = pow_n(base, digits)
	VectorType base2{};
	bigint_algo::pow_n(base2, VectorType{static_cast<T>(base)}, static_cast<hamon::uintmax_t>(digits));

	auto p = first;
	while (p != last)
	{
		VectorType quo{};
		VectorType rem{};
		bigint_algo::div_mod(quo, rem, value, base2);
		detail::move(value, quo);
		auto p2 = hamon::min(p + digits, last);
		to_chars_reverse(p, p2, rem.data()[0], base);
		p = p2;

		if (bigint_algo::is_zero(value))
		{
			break;
		}
	}

	p = remove_trailing_zeros(first, p);

	if (p == last)
	{
		return {last, hamon::errc::value_too_large};
	}

	hamon::reverse(first, p);

	return {p, hamon::errc{}};
}

}	// namespace to_chars_detail

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars(char* first, char* last, VectorType const& value, int base = 10)
{
	return to_chars_detail::to_chars(first, last, value, base);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_to_chars_HPP
