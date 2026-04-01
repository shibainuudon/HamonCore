/**
 *	@file	one.hpp
 *
 *	@brief	one 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_ONE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_ONE_HPP

#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR void
one(VectorType& v)
{
	v.resize(1);
	v.data()[0] = 1;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
one(hamon::array<T, N>& v)
{
	auto p = v.data();
	p[0] = 1;
	for (hamon::size_t i = 1; i < N; ++i)
	{
		p[i] = 0;
	}
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_ONE_HPP
