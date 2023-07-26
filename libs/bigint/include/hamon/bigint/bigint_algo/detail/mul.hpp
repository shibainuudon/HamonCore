/**
 *	@file	mul.hpp
 *
 *	@brief	mul 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_MUL_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_MUL_HPP

#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
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
mul(hamon::uint8_t lhs, hamon::uint8_t rhs)
{
	return static_cast<hamon::uint16_t>(
		static_cast<hamon::uint16_t>(lhs) *
		static_cast<hamon::uint16_t>(rhs));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t
mul(hamon::uint16_t lhs, hamon::uint16_t rhs)
{
	return static_cast<hamon::uint32_t>(
		static_cast<hamon::uint32_t>(lhs) *
		static_cast<hamon::uint32_t>(rhs));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint64_t
mul(hamon::uint32_t lhs, hamon::uint32_t rhs)
{
	return static_cast<hamon::uint64_t>(
		static_cast<hamon::uint64_t>(lhs) *
		static_cast<hamon::uint64_t>(rhs));
}

#if defined(__SIZEOF_INT128__)
inline HAMON_CXX11_CONSTEXPR __uint128_t
mul(hamon::uint64_t lhs, hamon::uint64_t rhs)
{
	return static_cast<__uint128_t>(
		static_cast<__uint128_t>(lhs) *
		static_cast<__uint128_t>(rhs));
}
#endif

template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, 2>
mul(T lhs, T rhs)
{
	using ResultType = hamon::array<T, 2>;

	auto const h  = mul(detail::hi(lhs), detail::hi(rhs));
	auto const m1 = mul(detail::hi(lhs), detail::lo(rhs));
	auto const m2 = mul(detail::lo(lhs), detail::hi(rhs));
	auto const l  = mul(detail::lo(lhs), detail::lo(rhs));

	auto const a1 = ResultType{l};
	auto const a2 = bigint_algo::bit_shift_left(ResultType{m1}, 32).value;
	auto const a3 = bigint_algo::bit_shift_left(ResultType{m2}, 32).value;
	auto const a4 = ResultType{0, h};

	ResultType result{0};
	bigint_algo::add(result, a1);
	bigint_algo::add(result, a2);
	bigint_algo::add(result, a3);
	bigint_algo::add(result, a4);
	return result;
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_MUL_HPP
