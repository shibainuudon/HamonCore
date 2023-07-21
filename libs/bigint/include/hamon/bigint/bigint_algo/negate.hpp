/**
 *	@file	negate.hpp
 *
 *	@brief	negate 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_NEGATE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_NEGATE_HPP

#include <hamon/bigint/bigint_algo/bit_not.hpp>
#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{
namespace bigint_algo
{

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
negate(hamon::array<T, N> const& lhs)
{
	return bigint_algo::add(bigint_algo::bit_not(lhs), hamon::array<T, N>{1}).value;
}

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_NEGATE_HPP
