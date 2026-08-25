/**
 *	@file	popcount.hpp
 *
 *	@brief	popcount 関数テンプレートの定義
 */

#ifndef HAMON_BIT_POPCOUNT_HPP
#define HAMON_BIT_POPCOUNT_HPP

#include <hamon/bit/detail/popcount_impl.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.8 Counting[bit.count]

/**
 *	@brief	1になっているビットを数える。(Population Count)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、1 となるビットの個数を返す。
 */
template <HAMON_CONSTRAINT(hamon::unsigned_integral, T)>	// [bit.count]/10
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
int popcount(T x) HAMON_NOEXCEPT
{
	// [bit.count]/11
	return detail::popcount_impl(x);
}

}	// namespace hamon

#endif // HAMON_BIT_POPCOUNT_HPP
