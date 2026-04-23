/**
 *	@file	subc.hpp
 *
 *	@brief	subc 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_SUBC_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_SUBC_HPP

#include <hamon/type_traits/make_signed.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

// x - y - borrow
// 戻り値で計算結果を返し、borrowにボローフラグを格納する

inline HAMON_CXX14_CONSTEXPR hamon::uint8_t
subc(hamon::uint8_t x, hamon::uint8_t y, hamon::uint8_t* borrow)
{
	auto t = static_cast<hamon::uint16_t>(
		static_cast<hamon::uint16_t>(x) -
		static_cast<hamon::uint16_t>(y) -
		static_cast<hamon::uint16_t>(*borrow));
	*borrow = ((t >> 8) != 0);
	return static_cast<hamon::uint8_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint16_t
subc(hamon::uint16_t x, hamon::uint16_t y, hamon::uint16_t* borrow)
{
	auto t = static_cast<hamon::uint32_t>(
		static_cast<hamon::uint32_t>(x) -
		static_cast<hamon::uint32_t>(y) -
		static_cast<hamon::uint32_t>(*borrow));
	*borrow = ((t >> 16) != 0);
	return static_cast<hamon::uint16_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint32_t
subc(hamon::uint32_t x, hamon::uint32_t y, hamon::uint32_t* borrow)
{
	auto t = static_cast<hamon::uint64_t>(
		static_cast<hamon::uint64_t>(x) -
		static_cast<hamon::uint64_t>(y) -
		static_cast<hamon::uint64_t>(*borrow));
	*borrow = ((t >> 32) != 0);
	return static_cast<hamon::uint32_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint64_t
subc(hamon::uint64_t x, hamon::uint64_t y, hamon::uint64_t* borrow)
{
#if defined(HAMON_HAS_INT128)
	auto t = static_cast<__uint128_t>(
		static_cast<__uint128_t>(x) -
		static_cast<__uint128_t>(y) -
		static_cast<__uint128_t>(*borrow));
	*borrow = ((t >> 64) != 0);
	return static_cast<hamon::uint64_t>(t);
#else
	auto const b = *borrow;
	auto const result = x - y - b;
	*borrow = ((b != 0) ? (result >= x) : (result > x));
	return result;
#endif
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_SUBC_HPP
