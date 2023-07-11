/**
 *	@file	lo.hpp
 *
 *	@brief	lo 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_LO_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_LO_HPP

#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{
namespace bigint_algo
{

inline HAMON_CXX11_CONSTEXPR hamon::uint8_t lo(hamon::uint16_t x)
{
	return static_cast<hamon::uint8_t>(x);
}

inline HAMON_CXX11_CONSTEXPR hamon::uint16_t lo(hamon::uint32_t x)
{
	return static_cast<hamon::uint16_t>(x);
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t lo(hamon::uint64_t x)
{
	return static_cast<hamon::uint32_t>(x);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T lo(hamon::array<T, 2> const& x)
{
	return x[0];
}

#if defined(__SIZEOF_INT128__)
inline HAMON_CXX11_CONSTEXPR hamon::uint64_t lo(__uint128_t x)
{
	return static_cast<hamon::uint64_t>(x);
}
#endif

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_LO_HPP
