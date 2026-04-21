/**
 *	@file	mulc.hpp
 *
 *	@brief	mulc 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_MULC_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_MULC_HPP

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

// x * y + carry
// 戻り値で計算結果の下位ビットを返し、carryに上位ビットを格納する
inline HAMON_CXX14_CONSTEXPR hamon::uint8_t
mulc(hamon::uint8_t x, hamon::uint8_t y, hamon::uint8_t* carry)
{
	auto t = static_cast<hamon::uint16_t>(
		static_cast<hamon::uint16_t>(x) *
		static_cast<hamon::uint16_t>(y) +
		static_cast<hamon::uint16_t>(*carry));
	*carry = static_cast<hamon::uint8_t>(t >> 8);
	return static_cast<hamon::uint8_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint16_t
mulc(hamon::uint16_t x, hamon::uint16_t y, hamon::uint16_t* carry)
{
	auto t = static_cast<hamon::uint32_t>(
		static_cast<hamon::uint32_t>(x) *
		static_cast<hamon::uint32_t>(y) +
		static_cast<hamon::uint32_t>(*carry));
	*carry = static_cast<hamon::uint16_t>(t >> 16);
	return static_cast<hamon::uint16_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint32_t
mulc(hamon::uint32_t x, hamon::uint32_t y, hamon::uint32_t* carry)
{
	auto t = static_cast<hamon::uint64_t>(
		static_cast<hamon::uint64_t>(x) *
		static_cast<hamon::uint64_t>(y) +
		static_cast<hamon::uint64_t>(*carry));
	*carry = static_cast<hamon::uint32_t>(t >> 32);
	return static_cast<hamon::uint32_t>(t);
}

#if defined(HAMON_HAS_INT128)
inline HAMON_CXX14_CONSTEXPR hamon::uint64_t
mulc(hamon::uint64_t x, hamon::uint64_t y, hamon::uint64_t* carry)
{
	auto t = static_cast<__uint128_t>(
		static_cast<__uint128_t>(x) *
		static_cast<__uint128_t>(y) +
		static_cast<__uint128_t>(*carry));
	*carry = static_cast<hamon::uint64_t>(t >> 64);
	return static_cast<hamon::uint64_t>(t);
}
#endif

template <typename T>
inline HAMON_CXX14_CONSTEXPR T
mulc(T x, T y, T* carry)
{
	auto r1 = detail::mul(x, y);
	auto r2 = detail::addc(detail::lo(r1), T{0}, carry);
	*carry += detail::hi(r1);
	return r2;
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_MULC_HPP
