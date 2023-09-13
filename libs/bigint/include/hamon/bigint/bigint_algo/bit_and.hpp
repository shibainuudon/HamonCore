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
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace bit_and_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
bit_and_impl(T* lhs, T const* rhs, hamon::size_t n)
{
	for (hamon::size_t i = 0; i < n; ++i)
	{
		lhs[i] = static_cast<T>(lhs[i] & rhs[i]);
	}
}

}	// namespace bit_and_detail

template <typename T>
inline void
bit_and(hamon::vector<T>& lhs, hamon::vector<T> const& rhs)
{
	auto const N = hamon::min(lhs.size(), rhs.size());
	lhs.resize(N);
	bit_and_detail::bit_and_impl(lhs.data(), rhs.data(), N);
	bigint_algo::normalize(lhs);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
bit_and(hamon::array<T, N>& lhs, hamon::array<T, N> const& rhs)
{
	bit_and_detail::bit_and_impl(lhs.data(), rhs.data(), N);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP
