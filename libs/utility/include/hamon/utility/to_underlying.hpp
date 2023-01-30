/**
 *	@file	to_underlying.hpp
 *
 *	@brief	to_underlying を定義
 */

#ifndef HAMON_UTILITY_TO_UNDERLYING_HPP
#define HAMON_UTILITY_TO_UNDERLYING_HPP

#include <utility>

#if defined(__cpp_lib_to_underlying) && (__cpp_lib_to_underlying >= 202102)

namespace hamon
{

using std::to_underlying;

}	// namespace hamon

#else

#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@biref	列挙型Tの値を基底型に変換する。
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::underlying_type_t<T>
to_underlying(T value) HAMON_NOEXCEPT
{
	return static_cast<hamon::underlying_type_t<T>>(value);
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_TO_UNDERLYING_HPP
