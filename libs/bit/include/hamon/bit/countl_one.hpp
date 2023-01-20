/**
 *	@file	countl_one.hpp
 *
 *	@brief	countl_one 関数テンプレートの定義
 */

#ifndef HAMON_BIT_COUNTL_ONE_HPP
#define HAMON_BIT_COUNTL_ONE_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_BITOPS)

#include <bit>

namespace hamon
{

using std::countl_one;

}	// namespace hamon

#else

#include <hamon/bit/countl_zero.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	最上位から1のビットが連続でいくつあるかを返す。(Count Leading Ones)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、最上位ビットから1が何ビット続くかを返す。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		std::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR int
countl_one(T x) HAMON_NOEXCEPT
{
	return countl_zero(static_cast<T>(~x));
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_COUNTL_ONE_HPP
