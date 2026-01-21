/**
 *	@file	bit_scan_reverse.hpp
 *
 *	@brief	bit_scan_reverse 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_BIT_SCAN_REVERSE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_BIT_SCAN_REVERSE_HPP

#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/countl_zero.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
bit_scan_reverse(hamon::size_t* index, T v)
{
	if (v == 0)
	{
		return false;
	}

	*index = hamon::bitsof<T>() - static_cast<hamon::size_t>(hamon::countl_zero(v)) - 1;
	return true;
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_BIT_SCAN_REVERSE_HPP
