/**
 *	@file	rotr.hpp
 *
 *	@brief	rotr 関数テンプレートを定義
 */

#ifndef HAMON_BIT_ROTR_HPP
#define HAMON_BIT_ROTR_HPP

#include <hamon/bit/detail/rotr_impl.hpp>
#include <hamon/bit/detail/rotl_impl.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.7 Rotating[bit.rotate]

/**
 *	@brief	環状右シフト(キャリーなし右ローテート)
 *
 *	@tparam	T		xの型(符号なし整数型)
 *
 *	@param	x	シフトされる値
 *	@param	s	シフトするビット数
 *
 *	符号なし整数型 T のビット数を N 、 s % N を r であるとして、
 *	 * r が0である場合は x が返る
 *	 * r が正である場合は (x >> r) | (x << (N - r)) が返る
 *	 * r が負である場合は rotl(x, -r) が返る
 */
template <HAMON_CONSTRAINT(hamon::unsigned_integral, T)>	// [bit.rotate]/5
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T rotr(T x, int s) HAMON_NOEXCEPT
{
	int N = hamon::numeric_limits<T>::digits;	// [bit.rotate]/1
	int r = s % N;	// [bit.rotate]/6

	// [bit.rotate]/7
	return
		r == 0 ?
			x :
		r > 0 ?
			hamon::detail::rotr_impl(x, N, r) :
			hamon::detail::rotl_impl(x, N, -r);
}

}	// namespace hamon

#endif // HAMON_BIT_ROTR_HPP
