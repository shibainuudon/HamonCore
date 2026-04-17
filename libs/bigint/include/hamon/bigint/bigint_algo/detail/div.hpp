/**
 *	@file	div.hpp
 *
 *	@brief	div 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_DIV_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_DIV_HPP

#include <hamon/bigint/bigint_algo/detail/uint128.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

inline HAMON_CXX11_CONSTEXPR hamon::uint8_t
div(hamon::uint16_t lhs, hamon::uint8_t rhs)
{
	return static_cast<hamon::uint8_t>(hamon::min<hamon::uint16_t>(lhs / rhs, hamon::numeric_limits<hamon::uint8_t>::max()));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint16_t
div(hamon::uint32_t lhs, hamon::uint16_t rhs)
{
	return static_cast<hamon::uint16_t>(hamon::min<hamon::uint32_t>(lhs / rhs, hamon::numeric_limits<hamon::uint16_t>::max()));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t
div(hamon::uint64_t lhs, hamon::uint32_t rhs)
{
	return static_cast<hamon::uint32_t>(hamon::min<hamon::uint64_t>(lhs / rhs, hamon::numeric_limits<hamon::uint32_t>::max()));
}

#if defined(HAMON_HAS_INT128)
inline HAMON_CXX11_CONSTEXPR hamon::uint64_t
div(__uint128_t lhs, hamon::uint64_t rhs)
{
	return static_cast<hamon::uint64_t>(hamon::min<__uint128_t>(lhs / rhs, hamon::numeric_limits<hamon::uint64_t>::max()));
}
#else
inline HAMON_CXX11_CONSTEXPR hamon::uint64_t
div(uint128 lhs, hamon::uint64_t rhs)
{
	return static_cast<hamon::uint64_t>(hamon::min<uint128>(lhs / rhs, hamon::numeric_limits<hamon::uint64_t>::max()));
}
#endif

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_DIV_HPP
