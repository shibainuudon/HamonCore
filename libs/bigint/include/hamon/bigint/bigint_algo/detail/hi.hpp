/**
 *	@file	hi.hpp
 *
 *	@brief	hi 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_HI_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_HI_HPP

#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

inline HAMON_CXX11_CONSTEXPR hamon::uint8_t hi(hamon::uint16_t x)
{
	return static_cast<hamon::uint8_t>(x >> 8);
}

inline HAMON_CXX11_CONSTEXPR hamon::uint16_t hi(hamon::uint32_t x)
{
	return static_cast<hamon::uint16_t>(x >> 16);
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t hi(hamon::uint64_t x)
{
	return static_cast<hamon::uint32_t>(x >> 32);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T hi(hamon::array<T, 2> const& x)
{
	return x[1];
}

#if defined(__SIZEOF_INT128__)
inline HAMON_CXX11_CONSTEXPR hamon::uint64_t hi(__uint128_t x)
{
	return static_cast<hamon::uint64_t>(x >> 64);
}
#endif

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_HI_HPP
