/**
 *	@file	from_chars.hpp
 *
 *	@brief	from_chars 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_FROM_CHARS_HPP
#define HAMON_BIGINT_BIGINT_ALGO_FROM_CHARS_HPP

#include <hamon/bigint/bigint_algo/multiply_add.hpp>
#include <hamon/bigint/bigint_algo/compare.hpp>
//#include <hamon/bigint/bigint_algo/pow_n.hpp>
#include <hamon/bigint/bigint_algo/detail/move.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/charconv/detail/from_chars_integer.hpp>
#include <hamon/cmath/log2.hpp>
#include <hamon/cmath/floor.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/system_error/errc.hpp>
//#include <hamon/utility/move.hpp>
#include <hamon/limits.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace from_chars_detail
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars(char const* first, char const* last, VectorType& value, int base)
{
	using T = hamon::ranges::range_value_t<VectorType>;

	auto const digits = static_cast<hamon::ptrdiff_t>(hamon::floor((hamon::numeric_limits<T>::digits - 1) / hamon::log2(base)));

	VectorType x{0};

	bool overflow = false;
	auto p = first;
	while (p != last)
	{
		auto p2 = first + hamon::min(p - first + digits, last - first);
		T t{};
		auto r = hamon::detail::from_chars_integer(p, p2, t, base);
		if (r.ec == hamon::errc::invalid_argument)
		{
			break;
		}
		auto n = r.ptr - p;

		// x = x * pow_n(base, n) + t
		auto const pn = hamon::detail::pow_n(static_cast<T>(base), n);
		overflow = overflow || bigint_algo::multiply_add(x, pn, t);

		p = r.ptr;
	};

	if (p == first)
	{
		return {first, hamon::errc::invalid_argument};
	}
	
	if (overflow)
	{
		return {p, hamon::errc::result_out_of_range};
	}

	detail::move(value, x);

	return {p, hamon::errc{}};
}

}	// namespace from_chars_detail

template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars(char const* first, char const* last, hamon::vector<T>& value, int base = 10)
{
	return from_chars_detail::from_chars(first, last, value, base);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars(char const* first, char const* last, hamon::inplace_vector<T, N>& value, int base = 10)
{
	return from_chars_detail::from_chars(first, last, value, base);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars(char const* first, char const* last, hamon::array<T, N>& value, int base = 10)
{
	return from_chars_detail::from_chars(first, last, value, base);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_FROM_CHARS_HPP
