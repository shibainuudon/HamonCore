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

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
bit_not(hamon::array<T, N>& lhs)
{
	for (hamon::size_t i = 0; i < N; ++i)
	{
		lhs[i] = static_cast<T>(~lhs[i]);
	}
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_NOT_HPP
