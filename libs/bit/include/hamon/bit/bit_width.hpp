/**
 *	@file	bit_width.hpp
 *
 *	@brief	bit_width 関数テンプレートの定義
 */

#ifndef HAMON_BIT_BIT_WIDTH_HPP
#define HAMON_BIT_BIT_WIDTH_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_INT_POW2)

#include <bit>

namespace hamon
{

using std::bit_width;

}	// namespace hamon

#else

#include <hamon/bit/countl_zero.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	値を表現するために必要なビット幅を求める。
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x == 0である場合、0を返す。
 *			そうでない場合、2を底としてxの対数を求めて、それに1を足した値を返す。
 *			その際、小数点以下の値は破棄される。
 *
 *	戻り値に1を足す理由は、対数を求められない0を引数として許容することでnoexceptとし、
 *	かつx == 1である場合と区別するためである。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR T
bit_width(T x) HAMON_NOEXCEPT
{
	return static_cast<T>(bitsof(x) - static_cast<hamon::size_t>(countl_zero(x)));
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_BIT_WIDTH_HPP
