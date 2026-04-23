/**
 *	@file	rotl.hpp
 *
 *	@brief	rotl 関数テンプレートを定義
 */

#ifndef HAMON_BIT_ROTL_HPP
#define HAMON_BIT_ROTL_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_BITOPS)

#include <bit>

namespace hamon
{

using std::rotl;

}	// namespace hamon

#else

#include <hamon/bit/bitsof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
//#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <int N, typename T>
inline HAMON_CXX11_CONSTEXPR T
rotl_impl(T x, unsigned int r) HAMON_NOEXCEPT
{
	// [bit.rotate]/4
	return r == 0 ? x : static_cast<T>((x << r) | (x >> (N - r)));
}

}	// namespace detail

// 22.11.6 Rotating[bit.rotate]

/**
 *	@brief	環状左シフト(キャリーなし左ローテート)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	シフトされる値
 *	@param	s	シフトするビット数
 *
 *	符号なし整数型 T のビット数を N 、 s % N を r であるとして、
 *	 * r が0である場合は x が返る
 *	 * r が正である場合は (x << r) | (x >> (N - r)) が返る
 *	 * r が負である場合は rotr(x, -r) が返る
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value	// [bit.rotate]/2
	>,
//	int N = hamon::numeric_limits<T>::digits	// [bit.rotate]/1
	int N = hamon::bitsof<T>()
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR T
rotl(T x, int s) HAMON_NOEXCEPT
{
	return detail::rotl_impl<N>(x, static_cast<unsigned int>(s) % N);	// [bit.rotate]/3
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_ROTL_HPP
