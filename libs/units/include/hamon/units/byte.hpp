/**
 *	@file	byte.hpp
 *
 *	@brief	byte の定義
 */

#ifndef HAMON_UNITS_BYTE_HPP
#define HAMON_UNITS_BYTE_HPP

#include <hamon/units/bit.hpp>
#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/detail/binary_prefix.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// バイト
template <typename T> using byte  = decltype(bit<T>() * hamon::ratio<8>());
template <typename T> using bytes = byte<T>;
HAMON_UNITS_SI_PREFIX(byte);
HAMON_UNITS_SI_PREFIX(bytes);
HAMON_UNITS_BINARY_PREFIX(byte);
HAMON_UNITS_BINARY_PREFIX(bytes);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BYTE_HPP
