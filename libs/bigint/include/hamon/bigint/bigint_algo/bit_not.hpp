/**
 *	@file	bit_not.hpp
 *
 *	@brief	bit_not 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_NOT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_NOT_HPP

#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{
namespace bigint_algo
{

template <typename T, hamon::size_t N, hamon::size_t... Is>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
bit_not_impl(hamon::array<T, N> const& lhs, hamon::index_sequence<Is...>)
{
	return hamon::array<T, N>{ static_cast<T>(~lhs[Is])... };
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
bit_not(hamon::array<T, N> const& lhs)
{
	return bit_not_impl(lhs, hamon::make_index_sequence<N>{});
}

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_NOT_HPP
