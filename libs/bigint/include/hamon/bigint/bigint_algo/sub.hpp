/**
 *	@file	sub.hpp
 *
 *	@brief	sub 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_SUB_HPP
#define HAMON_BIGINT_BIGINT_ALGO_SUB_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/negate.hpp>
#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/bigint/bigint_algo/detail/get.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/subc.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

template <typename T>
inline std::vector<T>
sub(std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	auto const N = hamon::max(lhs.size(), rhs.size());
	std::vector<T> result(N);
	T carry = 0;
	for (hamon::size_t i = 0; i < N; ++i)
	{
		auto const x = detail::subc(
			detail::get(lhs, i),
			detail::get(rhs, i),
			carry);
		result[i] = detail::lo(x);
		carry     = detail::hi(x);
	}

	return bigint_algo::normalize(result);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
sub(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	// 固定長のときは、negateしてadd
	return bigint_algo::add(lhs, bigint_algo::negate(rhs)).value;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_SUB_HPP
