/**
 *	@file	has_single_bit.hpp
 *
 *	@brief	has_single_bit 関数テンプレートの定義
 */

#ifndef HAMON_BIT_HAS_SINGLE_BIT_HPP
#define HAMON_BIT_HAS_SINGLE_BIT_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_INT_POW2)

#include <bit>

namespace hamon
{

using std::has_single_bit;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	2の累乗かどうか取得する.
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	取得する対象となる値
 *
 *	@return	xが2の累乗ならtrueを返す。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		std::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR bool
has_single_bit(T x) HAMON_NOEXCEPT
{
	return x > 0 && ((x & (x - 1)) == 0);
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_HAS_SINGLE_BIT_HPP
