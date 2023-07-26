﻿/**
 *	@file	from_chars.hpp
 *
 *	@brief	from_chars 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_FROM_CHARS_HPP
#define HAMON_BIGINT_BIGINT_ALGO_FROM_CHARS_HPP

#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/charconv/from_chars.hpp>
#include <hamon/cmath/log2.hpp>
#include <hamon/cmath/floor.hpp>
//#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/config.hpp>
#include <system_error>

namespace hamon
{
namespace bigint_algo
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars(char const* first, char const* last, VectorType& value, int base = 10)
{
	using T = hamon::ranges::range_value_t<VectorType>;

	auto const digits = static_cast<hamon::ptrdiff_t>(hamon::floor(std::numeric_limits<T>::digits / hamon::log2(base)));

	VectorType x{0};

	bool overflowed = false;
	auto p = first;
	while (p != last)
	{
		auto p2 = first + hamon::min(p - first + digits, last - first);
		T t{};
		auto r = hamon::from_chars(p, p2, t, base);
		if (r.ec == std::errc::invalid_argument)
		{
			break;
		}
		auto n = r.ptr - p;
		p = r.ptr;

		// x *= pow(base, n)
		for (decltype(n) j = 0; j < n; ++j)
		{
			auto tt = bigint_algo::multiply(x, T(base));
			x = tt.value;
			overflowed = overflowed || tt.overflow;
		}

		{
			auto of = bigint_algo::add(x, VectorType{t});
			overflowed = overflowed || of;
		}
	};

	if (p == first)
	{
		return {first, std::errc::invalid_argument};
	}
	
	if (overflowed)
	{
		return {p, std::errc::result_out_of_range};
	}

	value = x;

	return {p, std::errc{}};
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_FROM_CHARS_HPP