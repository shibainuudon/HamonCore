/**
 *	@file	resize.hpp
 *
 *	@brief	resize 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_RESIZE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_RESIZE_HPP

#include <hamon/algorithm/min.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
resize(hamon::vector<T>& v, hamon::size_t n)
{
	v.resize(n);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
resize(hamon::inplace_vector<T, N>& v, hamon::size_t n)
{
	v.resize(hamon::min(n, N));
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
resize(hamon::array<T, N>&, hamon::size_t)
{
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_RESIZE_HPP
