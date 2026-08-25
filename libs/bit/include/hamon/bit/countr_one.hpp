/**
 *	@file	countr_one.hpp
 *
 *	@brief	countr_one 関数テンプレートの定義
 */

#ifndef HAMON_BIT_COUNTR_ONE_HPP
#define HAMON_BIT_COUNTR_ONE_HPP

#include <hamon/bit/countr_zero.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.8 Counting[bit.count]

/**
 *	@brief	最下位から1のビットが連続でいくつあるかを返す。(Count Trailing Ones)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、最下位ビットから1が何ビット続くかを返す。
 */
template <HAMON_CONSTRAINT(hamon::unsigned_integral, T)>	// [bit.count]/8
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
int countr_one(T x) HAMON_NOEXCEPT
{
	// [bit.count]/9
	return countr_zero(static_cast<T>(~x));
}

}	// namespace hamon

#endif // HAMON_BIT_COUNTR_ONE_HPP
