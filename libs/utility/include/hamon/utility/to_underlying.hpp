/**
 *	@file	to_underlying.hpp
 *
 *	@brief	to_underlying を定義
 */

#ifndef HAMON_UTILITY_TO_UNDERLYING_HPP
#define HAMON_UTILITY_TO_UNDERLYING_HPP

#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.8 Function template to_underlying[utility.underlying]

/**
 *	@biref	列挙型Tの値を基底型に変換する。
 */
template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::underlying_type_t<T>
to_underlying(T value) HAMON_NOEXCEPT
{
	// [utility.underlying]/1
	return static_cast<hamon::underlying_type_t<T>>(value);
}

}	// namespace hamon

#endif // HAMON_UTILITY_TO_UNDERLYING_HPP
