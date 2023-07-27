/**
 *	@file	countl_zero.hpp
 *
 *	@brief	countl_zero 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_COUNTL_ZERO_HPP
#define HAMON_BIGINT_BIGINT_ALGO_COUNTL_ZERO_HPP

#include <hamon/array.hpp>
#include <hamon/bit/countl_zero.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::uintmax_t
countl_zero(hamon::array<T, N> const& vec)
{
	hamon::uintmax_t result = 0;
	for (hamon::size_t i = 0; i < N; ++i)
	{
		auto const v = vec[N - i - 1];
		if (v != 0)
		{
			return result +
				static_cast<hamon::uintmax_t>(hamon::countl_zero(v));
		}
		result += hamon::bitsof<T>();
	}
	return result;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_COUNTL_ZERO_HPP
