/**
 *	@file	bit_and.hpp
 *
 *	@brief	bit_and 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/detail/get.hpp>
#include <hamon/array.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace detail
{
namespace bigint_algo
{

template <typename T>
inline std::vector<T>
bit_and(std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	auto const N = hamon::max(lhs.size(), rhs.size());
	std::vector<T> result(N);
	for (hamon::size_t i = 0; i < N; ++i)
	{
		result[i] = static_cast<T>(
			bigint_algo::get(lhs, i) &
			bigint_algo::get(rhs, i));
	}
	return bigint_algo::normalize(result);
}

template <typename T, hamon::size_t N, hamon::size_t... Is>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
bit_and_impl(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs, hamon::index_sequence<Is...>)
{
	return hamon::array<T, N>{ static_cast<T>(lhs[Is] & rhs[Is])... };
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
bit_and(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	return bit_and_impl(lhs, rhs, hamon::make_index_sequence<N>{});
}

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP
