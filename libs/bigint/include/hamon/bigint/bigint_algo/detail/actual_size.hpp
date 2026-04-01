/**
 *	@file	actual_size.hpp
 *
 *	@brief	actual_size 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_ACTUAL_SIZE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_ACTUAL_SIZE_HPP

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
inline HAMON_CXX14_CONSTEXPR hamon::size_t
actual_size(VectorType const& v)
{
	return v.size();
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::size_t
actual_size(hamon::array<T, N> const& v)
{
	auto p = v.data();
	for (hamon::size_t i = N; i > 0; --i)
	{
		if (p[i - 1] != 0)
		{
			return i;
		}
	}
	return 1;
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_ACTUAL_SIZE_HPP
