/**
 *	@file	shl.hpp
 *
 *	@brief	shl 関数テンプレートを定義
 */

#ifndef HAMON_BIT_SHL_HPP
#define HAMON_BIT_SHL_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	論理左シフト
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	シフトされる値
 *	@param	s	シフトするビット数
 *
 *	 * s が0である場合は x が返る
 *	 * s が正である場合は x << s が返る
 *	 * s が負である場合は x >> -s が返る
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value
	>,
	int N = hamon::numeric_limits<T>::digits
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR T
shl(T x, int s) HAMON_NOEXCEPT
{
	return (s >= N || s <= -N) ? T{} :
		s >= 0 ?
			static_cast<T>(x << s) :
			static_cast<T>(x >> -s);
}

}	// namespace hamon

#endif // HAMON_BIT_SHL_HPP
