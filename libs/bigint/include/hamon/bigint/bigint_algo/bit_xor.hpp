/**
 *	@file	bit_xor.hpp
 *
 *	@brief	bit_xor 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_XOR_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_XOR_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/detail/get.hpp>
#include <hamon/array.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

template <typename T>
inline void
bit_xor(std::vector<T>& lhs, std::vector<T> const& rhs)
{
	auto const N = hamon::max(lhs.size(), rhs.size());
	lhs.resize(N);
	for (hamon::size_t i = 0; i < N; ++i)
	{
		lhs[i] = static_cast<T>(
			detail::get(lhs, i) ^
			detail::get(rhs, i));
	}
	bigint_algo::normalize(lhs);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
bit_xor(hamon::array<T, N>& lhs, hamon::array<T, N> const& rhs)
{
	for (hamon::size_t i = 0; i < N; ++i)
	{
		lhs[i] = static_cast<T>(lhs[i] ^ rhs[i]);
	}
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_XOR_HPP
