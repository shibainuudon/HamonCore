/**
 *	@file	bit_and.hpp
 *
 *	@brief	bit_and 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/array.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

template <typename T>
inline void
bit_and(std::vector<T>& lhs, std::vector<T> const& rhs)
{
	auto const N = hamon::min(lhs.size(), rhs.size());
	lhs.resize(N);
	for (hamon::size_t i = 0; i < N; ++i)
	{
		lhs[i] = static_cast<T>(lhs[i] & rhs[i]);
	}
	bigint_algo::normalize(lhs);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
bit_and(hamon::array<T, N>& lhs, hamon::array<T, N> const& rhs)
{
	for (hamon::size_t i = 0; i < N; ++i)
	{
		lhs[i] = static_cast<T>(lhs[i] & rhs[i]);
	}
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP
