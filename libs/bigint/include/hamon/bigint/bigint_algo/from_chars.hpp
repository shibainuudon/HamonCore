/**
 *	@file	from_chars.hpp
 *
 *	@brief	from_chars 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_FROM_CHARS_HPP
#define HAMON_BIGINT_BIGINT_ALGO_FROM_CHARS_HPP

#include <hamon/bigint/bigint_algo/detail/move.hpp>
#include <hamon/bigint/bigint_algo/detail/mulc.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/detail/vector_value_t.hpp>
#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/charconv/detail/from_chars_integer.hpp>
#include <hamon/cmath/log2.hpp>
#include <hamon/cmath/floor.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars(char const* first, char const* last, VectorType& value, int base)
{
	using T = detail::vector_value_t<VectorType>;
	static_assert(hamon::is_unsigned<T>::value, "");

	auto const ubase = static_cast<T>(base);

	auto const digits = static_cast<hamon::ptrdiff_t>(base == 10 ?
		hamon::numeric_limits<T>::digits10 :
		hamon::floor((hamon::numeric_limits<T>::digits - 1) / hamon::log2(base)));

	auto const length = last - first;

	VectorType x{0};
	detail::resize(x, static_cast<hamon::size_t>(length / digits + 1));

	auto x_p = x.data();
	hamon::size_t x_n = 1;
	hamon::size_t const x_sz = x.size();

	bool overflow = false;
	auto p = first;
	while (p != last)
	{
		auto p2 = first + hamon::min(p - first + digits, length);
		T t{};
		auto r = hamon::detail::from_chars_unsigned_integer(p, p2, t, ubase);
		if (r.ec == hamon::errc::invalid_argument)
		{
			break;
		}
		auto n = r.ptr - p;

		// x = x * pow_n(base, n) + t
		auto const pn = hamon::detail::pow_n(ubase, n);
		for (hamon::size_t i = 0; i < x_n; ++i)
		{
			x_p[i] = detail::mulc(x_p[i], pn, &t);
		}

		if (t != 0)
		{
			if (x_n == x_sz)
			{
				overflow = true;
			}
			else
			{
				x_p[x_n] = t;
				++x_n;
			}
		}

		p = r.ptr;
	};

	bigint_algo::normalize(x);

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

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_FROM_CHARS_HPP
