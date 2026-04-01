/**
 *	@file	is_zero.hpp
 *
 *	@brief	is_zero 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_IS_ZERO_HPP
#define HAMON_BIGINT_BIGINT_ALGO_IS_ZERO_HPP

#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
is_zero(VectorType const& vec)
{
	return vec.size() == 1 && vec.data()[0] == 0;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
is_zero(hamon::array<T, N> const& vec)
{
	auto p = vec.data();
	for (hamon::size_t i = 0; i < N; ++i)
	{
		if (p[i] != 0)
		{
			return false;
		}
	}
	return true;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_IS_ZERO_HPP
