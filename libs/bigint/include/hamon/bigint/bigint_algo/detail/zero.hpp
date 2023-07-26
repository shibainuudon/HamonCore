/**
 *	@file	zero.hpp
 *
 *	@brief	zero 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_ZERO_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_ZERO_HPP

#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

template <typename T>
inline void
zero(std::vector<T>& v)
{
	v.resize(1);
	v[0] = 0;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
zero(hamon::array<T, N>& v)
{
	for (hamon::size_t i = 0; i < N; ++i)
	{
		v[i] = 0;
	}
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_ZERO_HPP
