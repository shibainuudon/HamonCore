/**
 *	@file	countr_zero.hpp
 *
 *	@brief	countr_zero 関数テンプレートの定義
 */

#ifndef HAMON_BIT_COUNTR_ZERO_HPP
#define HAMON_BIT_COUNTR_ZERO_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_BITOPS)

#include <bit>

namespace hamon
{

using std::countr_zero;

}	// namespace hamon

#else

#include <hamon/bit/popcount.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	最下位から0のビットが連続でいくつあるかを返す。(Count Trailing Zeros)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、最下位ビットから0が何ビット続くかを返す。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		std::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR int
countr_zero(T x) HAMON_NOEXCEPT
{
	return popcount<T>(static_cast<T>((~x) & (x - 1)));
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_COUNTR_ZERO_HPP
