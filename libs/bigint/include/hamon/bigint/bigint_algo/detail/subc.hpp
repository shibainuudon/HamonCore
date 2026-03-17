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

// x - y + borrow
// 戻り値で計算結果の下位ビットを返し、borrowに上位ビットを格納する

inline HAMON_CXX14_CONSTEXPR hamon::uint8_t
subc(hamon::uint8_t x, hamon::uint8_t y, hamon::uint8_t* borrow)
{
	auto t = static_cast<hamon::uint16_t>(
		static_cast<hamon::uint16_t>(x) -
		static_cast<hamon::uint16_t>(y) +
		static_cast<hamon::uint16_t>(static_cast<hamon::int8_t>(*borrow)));
	*borrow = static_cast<hamon::uint8_t>(t >> 8);
	return static_cast<hamon::uint8_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint16_t
subc(hamon::uint16_t x, hamon::uint16_t y, hamon::uint16_t* borrow)
{
	auto t = static_cast<hamon::uint32_t>(
		static_cast<hamon::uint32_t>(x) -
		static_cast<hamon::uint32_t>(y) +
		static_cast<hamon::uint32_t>(static_cast<hamon::int16_t>(*borrow)));
	*borrow = static_cast<hamon::uint16_t>(t >> 16);
	return static_cast<hamon::uint16_t>(t);
}

inline HAMON_CXX14_CONSTEXPR hamon::uint32_t
subc(hamon::uint32_t x, hamon::uint32_t y, hamon::uint32_t* borrow)
{
	auto t = static_cast<hamon::uint64_t>(
		static_cast<hamon::uint64_t>(x) -
		static_cast<hamon::uint64_t>(y) +
		static_cast<hamon::uint64_t>(static_cast<hamon::int32_t>(*borrow)));
	*borrow = static_cast<hamon::uint32_t>(t >> 32);
	return static_cast<hamon::uint32_t>(t);
}

#if defined(__SIZEOF_INT128__)
inline HAMON_CXX14_CONSTEXPR hamon::uint64_t
subc(hamon::uint64_t x, hamon::uint64_t y, hamon::uint64_t* borrow)
{
	auto t = static_cast<__uint128_t>(
		static_cast<__uint128_t>(x) -
		static_cast<__uint128_t>(y) +
		static_cast<__uint128_t>(static_cast<hamon::int64_t>(*borrow)));
	*borrow = static_cast<hamon::uint64_t>(t >> 64);
	return static_cast<hamon::uint64_t>(t);
}
#endif

// 上記以外の汎用的な実装(主に__uint128_tが使えない環境向け)
template <typename T>
inline HAMON_CXX14_CONSTEXPR T
subc(T x, T y, T* borrow)
{
	T const a = static_cast<T>(y + static_cast<T>(static_cast<hamon::make_signed_t<T>>(*borrow)));
	T const b = static_cast<T>(x - a);
	T const c1 = a > y ? T(-1) : 0;
	T const c2 = b > x ? T(-1) : 0;
	*borrow = static_cast<T>(c1 + c2);
	return b;
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_SUBC_HPP
