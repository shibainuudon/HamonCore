/**
 *	@file	addc.hpp
 *
 *	@brief	addc 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_ADDC_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_ADDC_HPP

#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

inline HAMON_CXX11_CONSTEXPR hamon::uint16_t
addc(hamon::uint8_t lhs, hamon::uint8_t rhs, hamon::uint8_t carry)
{
	return static_cast<hamon::uint16_t>(
		static_cast<hamon::uint16_t>(lhs) +
		static_cast<hamon::uint16_t>(rhs) +
		static_cast<hamon::uint16_t>(carry));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t
addc(hamon::uint16_t lhs, hamon::uint16_t rhs, hamon::uint16_t carry)
{
	return static_cast<hamon::uint32_t>(
		static_cast<hamon::uint32_t>(lhs) +
		static_cast<hamon::uint32_t>(rhs) +
		static_cast<hamon::uint32_t>(carry));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint64_t
addc(hamon::uint32_t lhs, hamon::uint32_t rhs, hamon::uint32_t carry)
{
	return static_cast<hamon::uint64_t>(
		static_cast<hamon::uint64_t>(lhs) +
		static_cast<hamon::uint64_t>(rhs) +
		static_cast<hamon::uint64_t>(carry));
}

#if defined(__SIZEOF_INT128__)
inline HAMON_CXX11_CONSTEXPR __uint128_t
addc(hamon::uint64_t lhs, hamon::uint64_t rhs, hamon::uint64_t carry)
{
	return static_cast<__uint128_t>(
		static_cast<__uint128_t>(lhs) +
		static_cast<__uint128_t>(rhs) +
		static_cast<__uint128_t>(carry));
}
#endif

// 上記以外の汎用的な実装(主に__uint128_tが使えない環境向け)
template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, 2>
addc(T lhs, T rhs, T carry)
{
	T const a = static_cast<T>(rhs + carry);
	T const b = static_cast<T>(lhs + a);
	T const c1 = a < rhs ? 1 : 0;
	T const c2 = b < lhs ? 1 : 0;
	return {b, static_cast<T>(c1 + c2)};
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_ADDC_HPP
