/**
 *	@file	addc.hpp
 *
 *	@brief	addc 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_ADDC_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_ADDC_HPP

#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

// x + y + carry
// 戻り値で計算結果の下位ビットを返し、carryに上位ビットを格納する

inline HAMON_CXX14_CONSTEXPR hamon::uint8_t
addc(hamon::uint8_t x, hamon::uint8_t y, hamon::uint8_t* carry)
{
	auto t = static_cast<hamon::uint16_t>(
		static_cast<hamon::uint16_t>(x) +
		static_cast<hamon::uint16_t>(y) +
		static_cast<hamon::uint16_t>(*carry));
	*carry = static_cast<hamon::uint8_t>(t >> 8);
	return static_cast<hamon::uint8_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint16_t
addc(hamon::uint16_t x, hamon::uint16_t y, hamon::uint16_t* carry)
{
	auto t = static_cast<hamon::uint32_t>(
		static_cast<hamon::uint32_t>(x) +
		static_cast<hamon::uint32_t>(y) +
		static_cast<hamon::uint32_t>(*carry));
	*carry = static_cast<hamon::uint16_t>(t >> 16);
	return static_cast<hamon::uint16_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint32_t
addc(hamon::uint32_t x, hamon::uint32_t y, hamon::uint32_t* carry)
{
	auto t = static_cast<hamon::uint64_t>(
		static_cast<hamon::uint64_t>(x) +
		static_cast<hamon::uint64_t>(y) +
		static_cast<hamon::uint64_t>(*carry));
	*carry = static_cast<hamon::uint32_t>(t >> 32);
	return static_cast<hamon::uint32_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint64_t
addc(hamon::uint64_t x, hamon::uint64_t y, hamon::uint64_t* carry)
{
#if defined(HAMON_HAS_INT128)
	auto t = static_cast<__uint128_t>(
		static_cast<__uint128_t>(x) +
		static_cast<__uint128_t>(y) +
		static_cast<__uint128_t>(*carry));
	*carry = static_cast<hamon::uint64_t>(t >> 64);
	return static_cast<hamon::uint64_t>(t);
#else
	auto const a = static_cast<hamon::uint64_t>(y + *carry);
	auto const b = static_cast<hamon::uint64_t>(x + a);
	auto const c1 = a < y ? 1 : 0;
	auto const c2 = b < x ? 1 : 0;
	*carry = static_cast<hamon::uint64_t>(c1 + c2);
	return b;
#endif
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_ADDC_HPP
