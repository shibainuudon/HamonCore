/**
 *	@file	signbit.hpp
 *
 *	@brief	signbit 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_SIGNBIT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_SIGNBIT_HPP

#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR bool
signbit(hamon::array<T, N> const& vec)
{
	return (vec[N - 1] >> (hamon::bitsof<T>() - 1)) != 0;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_SIGNBIT_HPP
