﻿/**
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
namespace bigint_algo
{

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
negate(hamon::array<T, N>& lhs)
{
	bigint_algo::bit_not(lhs);
	bigint_algo::add(lhs, T{1});
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, N>
negate(hamon::array<T, N> const& lhs)
{
	hamon::array<T, N> result{lhs};
	bigint_algo::negate(result);
	return result;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_NEGATE_HPP
