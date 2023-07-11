/**
 *	@file	sub.hpp
 *
 *	@brief	sub 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_SUB_HPP
#define HAMON_BIGINT_BIGINT_ALGO_SUB_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/negate.hpp>
#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/bigint/bigint_algo/detail/get.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/make_signed.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace detail
{
namespace bigint_algo
{

inline HAMON_CXX11_CONSTEXPR hamon::uint16_t
subc(hamon::uint8_t lhs, hamon::uint8_t rhs, hamon::uint8_t carry)
{
	return static_cast<hamon::uint16_t>(
		static_cast<hamon::uint16_t>(lhs) -
		static_cast<hamon::uint16_t>(rhs) +
		static_cast<hamon::uint16_t>(static_cast<hamon::int8_t>(carry)));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t
subc(hamon::uint16_t lhs, hamon::uint16_t rhs, hamon::uint16_t carry)
{
	return static_cast<hamon::uint32_t>(
		static_cast<hamon::uint32_t>(lhs) -
		static_cast<hamon::uint32_t>(rhs) +
		static_cast<hamon::uint32_t>(static_cast<hamon::int16_t>(carry)));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint64_t
subc(hamon::uint32_t lhs, hamon::uint32_t rhs, hamon::uint32_t carry)
{
	return static_cast<hamon::uint64_t>(
		static_cast<hamon::uint64_t>(lhs) -
		static_cast<hamon::uint64_t>(rhs) +
		static_cast<hamon::uint64_t>(static_cast<hamon::int32_t>(carry)));
}

#if defined(__SIZEOF_INT128__)
inline HAMON_CXX11_CONSTEXPR __uint128_t
subc(hamon::uint64_t lhs, hamon::uint64_t rhs, hamon::uint64_t carry)
{
	return static_cast<__uint128_t>(
		static_cast<__uint128_t>(lhs) -
		static_cast<__uint128_t>(rhs) +
		static_cast<__uint128_t>(static_cast<hamon::int64_t>(carry)));
}
#endif

// 上記以外の汎用的な実装(主に__uint128_tが使えない環境向け)
template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, 2>
subc(T lhs, T rhs, T carry)
{
	T const a = static_cast<T>(rhs + static_cast<hamon::make_signed_t<T>>(carry));
	T const b = static_cast<T>(lhs - a);
	T const c1 = a > rhs ? -1 : 0;
	T const c2 = b > lhs ? -1 : 0;
	return {b, static_cast<T>(c1 + c2)};
}

template <typename T>
inline std::vector<T>
sub(std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	auto const N = hamon::max(lhs.size(), rhs.size());
	std::vector<T> result(N);
	T carry = 0;
	for (hamon::size_t i = 0; i < N; ++i)
	{
		auto const x = bigint_algo::subc(
			bigint_algo::get(lhs, i),
			bigint_algo::get(rhs, i),
			carry);
		result[i] = bigint_algo::lo(x);
		carry     = bigint_algo::hi(x);
	}

	return bigint_algo::normalize(result);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
sub(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	// 固定長のときは、negateしてadd
	return bigint_algo::add(lhs, bigint_algo::negate(rhs));
}

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_SUB_HPP
