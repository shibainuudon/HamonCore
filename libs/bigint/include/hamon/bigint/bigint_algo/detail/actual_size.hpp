/**
 *	@file	actual_size.hpp
 *
 *	@brief	actual_size 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_ACTUAL_SIZE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_ACTUAL_SIZE_HPP

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
inline HAMON_CXX14_CONSTEXPR hamon::size_t
actual_size_impl(T const* p, hamon::size_t n)
{
	for (hamon::size_t i = n; i > 0; --i)
	{
		if (p[i - 1] != 0)
		{
			return i;
		}
	}
	return 0;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::size_t
actual_size(hamon::array<T, N> const& v)
{
	return actual_size_impl(v.data(), N);
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::size_t
actual_size(hamon::vector<T> const& v)
{
	return v.size();
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::size_t
actual_size(hamon::inplace_vector<T, N> const& v)
{
	return v.size();
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_ACTUAL_SIZE_HPP
