/**
 *	@file	mul_addc.hpp
 *
 *	@brief	mul_addc 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_MUL_ADDC_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_MUL_ADDC_HPP

#include <hamon/bigint/bigint_algo/detail/mul.hpp>
#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

// x * y + z + carry

inline HAMON_CXX11_CONSTEXPR hamon::uint16_t
mul_addc(hamon::uint8_t x, hamon::uint8_t y, hamon::uint8_t z, hamon::uint8_t carry)
{
	return static_cast<hamon::uint16_t>(
		static_cast<hamon::uint16_t>(x) *
		static_cast<hamon::uint16_t>(y) +
		static_cast<hamon::uint16_t>(z) +
		static_cast<hamon::uint16_t>(carry));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t
mul_addc(hamon::uint16_t x, hamon::uint16_t y, hamon::uint16_t z, hamon::uint16_t carry)
{
	return static_cast<hamon::uint32_t>(
		static_cast<hamon::uint32_t>(x) *
		static_cast<hamon::uint32_t>(y) +
		static_cast<hamon::uint32_t>(z) +
		static_cast<hamon::uint32_t>(carry));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint64_t
mul_addc(hamon::uint32_t x, hamon::uint32_t y, hamon::uint32_t z, hamon::uint32_t carry)
{
	return static_cast<hamon::uint64_t>(
		static_cast<hamon::uint64_t>(x) *
		static_cast<hamon::uint64_t>(y) +
		static_cast<hamon::uint64_t>(z) +
		static_cast<hamon::uint64_t>(carry));
}

#if defined(__SIZEOF_INT128__)
inline HAMON_CXX11_CONSTEXPR __uint128_t
mul_addc(hamon::uint64_t x, hamon::uint64_t y, hamon::uint64_t z, hamon::uint64_t carry)
{
	return static_cast<__uint128_t>(
		static_cast<__uint128_t>(x) *
		static_cast<__uint128_t>(y) +
		static_cast<__uint128_t>(z) +
		static_cast<__uint128_t>(carry));
}
#endif

template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, 2>
mul_addc(T x, T y, T z, T carry)
{
	auto r = detail::mul(x, y);
	bigint_algo::add(r, z);
	bigint_algo::add(r, carry);
	return r;
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_MUL_ADDC_HPP
