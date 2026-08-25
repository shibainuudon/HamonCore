/**
 *	@file	has_single_bit.hpp
 *
 *	@brief	has_single_bit 関数テンプレートの定義
 */

#ifndef HAMON_BIT_HAS_SINGLE_BIT_HPP
#define HAMON_BIT_HAS_SINGLE_BIT_HPP

#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.5 Integral powers of 2[bit.pow.two]

/**
 *	@brief	2の累乗かどうか取得する.
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	取得する対象となる値
 *
 *	@return	xが2の累乗ならtrueを返す。
 */
template <HAMON_CONSTRAINT(hamon::unsigned_integral, T)>	// [bit.pow.two]/1
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool has_single_bit(T x) HAMON_NOEXCEPT
{
	// [bit.pow.two]/2
	return x > 0 && ((x & (x - 1)) == 0);
}

}	// namespace hamon

#endif // HAMON_BIT_HAS_SINGLE_BIT_HPP
