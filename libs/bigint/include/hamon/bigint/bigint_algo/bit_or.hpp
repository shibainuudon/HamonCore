/**
 *	@file	bit_or.hpp
 *
 *	@brief	bit_or 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_OR_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_OR_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/array.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace bit_or_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
bit_or_impl(T* lhs, T const* rhs, hamon::size_t n)
{
	for (hamon::size_t i = 0; i < n; ++i)
	{
		lhs[i] = static_cast<T>(lhs[i] | rhs[i]);
	}
}

}	// namespace bit_or_detail

template <typename T>
inline void
bit_or(hamon::vector<T>& lhs, hamon::vector<T> const& rhs)
{
	auto const N = hamon::max(lhs.size(), rhs.size());
	lhs.resize(N);
	bit_or_detail::bit_or_impl(lhs.data(), rhs.data(), rhs.size());
	bigint_algo::normalize(lhs);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
bit_or(hamon::array<T, N>& lhs, hamon::array<T, N> const& rhs)
{
	bit_or_detail::bit_or_impl(lhs.data(), rhs.data(), N);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_OR_HPP
