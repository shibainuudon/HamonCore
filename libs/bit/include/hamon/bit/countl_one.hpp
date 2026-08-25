/**
 *	@file	countl_one.hpp
 *
 *	@brief	countl_one 関数テンプレートの定義
 */

#ifndef HAMON_BIT_COUNTL_ONE_HPP
#define HAMON_BIT_COUNTL_ONE_HPP

#include <hamon/bit/countl_zero.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.8 Counting[bit.count]

/**
 *	@brief	最上位から1のビットが連続でいくつあるかを返す。(Count Leading Ones)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、最上位ビットから1が何ビット続くかを返す。
 */
template <HAMON_CONSTRAINT(hamon::unsigned_integral, T)>	// [bit.count]/4
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
int countl_one(T x) HAMON_NOEXCEPT
{
	// [bit.count]/5
	return countl_zero(static_cast<T>(~x));
}

}	// namespace hamon

#endif // HAMON_BIT_COUNTL_ONE_HPP
