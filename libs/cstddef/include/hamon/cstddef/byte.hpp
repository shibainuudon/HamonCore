/**
 *	@file	byte.hpp
 *
 *	@brief	byte の定義
 */

#ifndef HAMON_CSTDDEF_BYTE_HPP
#define HAMON_CSTDDEF_BYTE_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 17.2.1 Header <cstddef> synopsis[cstddef.syn]
enum class byte : unsigned char {};

// 17.2.5 byte type operations[support.types.byteops]

template <typename IntType, typename = hamon::enable_if_t<hamon::is_integral_v<IntType>>>	// [support.types.byteops]/1
inline HAMON_CXX14_CONSTEXPR byte&
operator<<=(byte& b, IntType shift) HAMON_NOEXCEPT
{
	// [support.types.byteops]/2
	return b = b << shift;
}

template <typename IntType, typename = hamon::enable_if_t<hamon::is_integral_v<IntType>>>	// [support.types.byteops]/3
inline HAMON_CXX14_CONSTEXPR byte
operator<<(byte b, IntType shift) HAMON_NOEXCEPT
{
	// [support.types.byteops]/4
	return static_cast<byte>(static_cast<unsigned int>(b) << shift);
}

template <typename IntType, typename = hamon::enable_if_t<hamon::is_integral_v<IntType>>>	// [support.types.byteops]/5
inline HAMON_CXX14_CONSTEXPR byte&
operator>>=(byte& b, IntType shift) HAMON_NOEXCEPT
{
	// [support.types.byteops]/6
	return b = b >> shift;
}

template <typename IntType, typename = hamon::enable_if_t<hamon::is_integral_v<IntType>>>	// [support.types.byteops]/7
inline HAMON_CXX14_CONSTEXPR byte
operator>>(byte b, IntType shift) HAMON_NOEXCEPT
{
	// [support.types.byteops]/8
	return static_cast<byte>(static_cast<unsigned int>(b) >> shift);
}

inline HAMON_CXX14_CONSTEXPR byte
operator|(byte l, byte r) HAMON_NOEXCEPT
{
	// [support.types.byteops]/10
	return static_cast<byte>(static_cast<unsigned int>(l) | static_cast<unsigned int>(r));
}

inline HAMON_CXX14_CONSTEXPR byte&
operator|=(byte& l, byte r) HAMON_NOEXCEPT
{
	// [support.types.byteops]/9
	return l = l | r;
}

inline HAMON_CXX14_CONSTEXPR byte
operator&(byte l, byte r) HAMON_NOEXCEPT
{
	// [support.types.byteops]/12
	return static_cast<byte>(static_cast<unsigned int>(l) & static_cast<unsigned int>(r));
}

inline HAMON_CXX14_CONSTEXPR byte&
operator&=(byte& l, byte r) HAMON_NOEXCEPT
{
	// [support.types.byteops]/11
	return l = l & r;
}

inline HAMON_CXX14_CONSTEXPR byte
operator^(byte l, byte r) HAMON_NOEXCEPT
{
	// [support.types.byteops]/14
	return static_cast<byte>(static_cast<unsigned int>(l) ^ static_cast<unsigned int>(r));
}

inline HAMON_CXX14_CONSTEXPR byte&
operator^=(byte& l, byte r) HAMON_NOEXCEPT
{
	// [support.types.byteops]/13
	return l = l ^ r;
}

inline HAMON_CXX14_CONSTEXPR byte
operator~(byte b) HAMON_NOEXCEPT
{
	// [support.types.byteops]/15
	return static_cast<byte>(~static_cast<unsigned int>(b));
}

template <typename IntType, typename = hamon::enable_if_t<hamon::is_integral_v<IntType>>>	// [support.types.byteops]/16
inline HAMON_CXX14_CONSTEXPR IntType
to_integer(byte b) HAMON_NOEXCEPT
{
	// [support.types.byteops]/17
	return static_cast<IntType>(b);
}

}	// namespace hamon

#endif // HAMON_CSTDDEF_BYTE_HPP
