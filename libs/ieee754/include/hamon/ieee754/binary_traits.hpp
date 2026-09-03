/**
 *	@file	binary_traits.hpp
 *
 *	@brief	binary_traits の定義
 */

#ifndef HAMON_IEEE754_BINARY_TRAITS_HPP
#define HAMON_IEEE754_BINARY_TRAITS_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/limits.hpp>

namespace hamon
{

namespace ieee754
{

namespace detail
{

template <hamon::size_t Digits>
struct binary_traits_impl;

// 単精度浮動小数点数(binary32)
template <>
struct binary_traits_impl<24>
{
	static int constexpr sign_bits     = 1;
	static int constexpr exponent_bits = 8;
	static int constexpr fraction_bits = 23;
	static int constexpr padding_bits  = 0;
	static bool constexpr has_fraction_implicit_bits = true;
};

// 倍精度浮動小数点数(binary64)
template <>
struct binary_traits_impl<53>
{
	static int constexpr sign_bits     = 1;
	static int constexpr exponent_bits = 11;
	static int constexpr fraction_bits = 52;
	static int constexpr padding_bits  = 0;
	static bool constexpr has_fraction_implicit_bits = true;
};

// 拡張倍精度浮動小数点数(binary80)
template <>
struct binary_traits_impl<64>
{
	static int constexpr sign_bits     = 1;
	static int constexpr exponent_bits = 15;
	static int constexpr fraction_bits = 64;
	static int constexpr padding_bits  = 48;
	static bool constexpr has_fraction_implicit_bits = false;
};

// 四倍精度浮動小数点数(binary128)
template <>
struct binary_traits_impl<113>
{
	static int constexpr sign_bits     = 1;
	static int constexpr exponent_bits = 15;
	static int constexpr fraction_bits = 112;
	static int constexpr padding_bits  = 0;
	static bool constexpr has_fraction_implicit_bits = true;
};

}	// namespace detail

template <typename T>
struct binary_traits
	: public detail::binary_traits_impl<hamon::numeric_limits<T>::digits>
{};

}	// namespace ieee754

}	// namespace hamon

#endif // HAMON_IEEE754_BINARY_TRAITS_HPP
