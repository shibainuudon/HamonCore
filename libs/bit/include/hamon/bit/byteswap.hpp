/**
 *	@file	byteswap.hpp
 *
 *	@brief	byteswap 関数テンプレートの定義
 */

#ifndef HAMON_BIT_BYTESWAP_HPP
#define HAMON_BIT_BYTESWAP_HPP

#include <hamon/bit/detail/byteswap_impl.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.4 byteswap[bit.byteswap]

template <HAMON_CONSTRAINT(hamon::integral, T)>	// [bit.byteswap]/1
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T byteswap(T value) HAMON_NOEXCEPT
{
	// [bit.byteswap]/4
	return detail::byteswap_impl(value);
}

}	// namespace hamon

#endif // HAMON_BIT_BYTESWAP_HPP
