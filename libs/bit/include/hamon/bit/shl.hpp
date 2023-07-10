/**
 *	@file	shl.hpp
 *
 *	@brief	shl 関数テンプレートを定義
 */

#ifndef HAMON_BIT_SHL_HPP
#define HAMON_BIT_SHL_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	論理左シフト
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value
	>
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR T
shl(T x, unsigned int shift) HAMON_NOEXCEPT
{
	return shift >= hamon::bitsof<T>() ? T{} : static_cast<T>(x << shift);
}

}	// namespace hamon

#endif // HAMON_BIT_SHL_HPP
