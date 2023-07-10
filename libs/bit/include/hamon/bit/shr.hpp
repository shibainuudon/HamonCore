/**
 *	@file	shr.hpp
 *
 *	@brief	shr 関数テンプレートを定義
 */

#ifndef HAMON_BIT_SHR_HPP
#define HAMON_BIT_SHR_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	論理右シフト
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value
	>
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR T
shr(T x, unsigned int shift) HAMON_NOEXCEPT
{
	return shift >= hamon::bitsof<T>() ? T{} : static_cast<T>(x >> shift);
}

}	// namespace hamon

#endif // HAMON_BIT_SHR_HPP
