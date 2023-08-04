/**
 *	@file	bit_not.hpp
 *
 *	@brief	bit_not 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_NOT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_NOT_HPP

#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace bit_not_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
bit_not_impl(T* lhs, hamon::size_t n)
{
	for (hamon::size_t i = 0; i < n; ++i)
	{
		lhs[i] = static_cast<T>(~lhs[i]);
	}
}

}	// namespace bit_not_detail

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
bit_not(hamon::array<T, N>& lhs)
{
	bit_not_detail::bit_not_impl(lhs.data(), N);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, N>
bit_not(hamon::array<T, N> const& lhs)
{
	hamon::array<T, N> result{lhs};
	bigint_algo::bit_not(result);
	return result;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_NOT_HPP
