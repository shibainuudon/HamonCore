/**
 *	@file	countr_zero.hpp
 *
 *	@brief	countr_zero 関数テンプレートの定義
 */

#ifndef HAMON_BIT_COUNTR_ZERO_HPP
#define HAMON_BIT_COUNTR_ZERO_HPP

#include <hamon/bit/popcount.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.8 Counting[bit.count]

/**
 *	@brief	最下位から0のビットが連続でいくつあるかを返す。(Count Trailing Zeros)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、最下位ビットから0が何ビット続くかを返す。
 */
template <HAMON_CONSTRAINT(hamon::unsigned_integral, T)>	// [bit.count]/6
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
int countr_zero(T x) HAMON_NOEXCEPT
{
	// [bit.count]/7
	return popcount<T>(static_cast<T>((~x) & (x - 1)));
}

}	// namespace hamon

#endif // HAMON_BIT_COUNTR_ZERO_HPP
