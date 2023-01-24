/**
 *	@file	byte.hpp
 *
 *	@brief	byte の定義
 */

#ifndef HAMON_CSTDDEF_BYTE_HPP
#define HAMON_CSTDDEF_BYTE_HPP

#include <cstddef>

#if defined(__cpp_lib_byte) && (__cpp_lib_byte >= 201603)

namespace hamon
{

using std::byte;
using std::to_integer;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

enum class byte : unsigned char {};

template <typename IntegerType>
inline HAMON_CONSTEXPR hamon::enable_if_t<std::is_integral<IntegerType>::value, IntegerType>
to_integer(byte b) HAMON_NOEXCEPT
{
	return IntegerType(b);
}

inline HAMON_CONSTEXPR byte operator|(byte lhs, byte rhs) HAMON_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs));
}

inline HAMON_CONSTEXPR byte operator&(byte lhs, byte rhs) HAMON_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) & static_cast<unsigned char>(rhs));
}

inline HAMON_CONSTEXPR byte operator^(byte lhs, byte rhs) HAMON_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) ^ static_cast<unsigned char>(rhs));
}

inline HAMON_CONSTEXPR byte operator~(byte b) HAMON_NOEXCEPT
{
	return byte(~static_cast<unsigned char>(b));
}

inline HAMON_CXX14_CONSTEXPR byte& operator|=(byte& lhs, byte rhs) HAMON_NOEXCEPT
{
	return lhs = lhs | rhs;
}

inline HAMON_CXX14_CONSTEXPR byte& operator&=(byte& lhs, byte rhs) HAMON_NOEXCEPT
{
	return lhs = lhs & rhs;
}

inline HAMON_CXX14_CONSTEXPR byte& operator^=(byte& lhs, byte rhs) HAMON_NOEXCEPT
{
	return lhs = lhs ^ rhs;
}

template <typename IntegerType>
inline HAMON_CONSTEXPR hamon::enable_if_t<std::is_integral<IntegerType>::value, byte>
operator<<(byte lhs, IntegerType shift) HAMON_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) << shift);
}

template <typename IntegerType>
inline HAMON_CONSTEXPR hamon::enable_if_t<std::is_integral<IntegerType>::value, byte>
operator>>(byte lhs, IntegerType shift) HAMON_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) >> shift);
}

template <typename IntegerType>
inline HAMON_CXX14_CONSTEXPR hamon::enable_if_t<std::is_integral<IntegerType>::value, byte>&
operator<<=(byte& lhs, IntegerType shift) HAMON_NOEXCEPT
{
	return lhs = lhs << shift;
}

template <typename IntegerType>
inline HAMON_CXX14_CONSTEXPR hamon::enable_if_t<std::is_integral<IntegerType>::value, byte>&
operator>>=(byte& lhs, IntegerType shift) HAMON_NOEXCEPT
{
	return lhs = lhs >> shift;
}

}	// namespace hamon

#endif

#endif // HAMON_CSTDDEF_BYTE_HPP
