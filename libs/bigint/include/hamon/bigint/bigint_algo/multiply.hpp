/**
 *	@file	multiply.hpp
 *
 *	@brief	multiply 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
#define HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP

#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace detail
{
namespace bigint_algo
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

	auto const h  = mul(hi(lhs), hi(rhs));
	auto const m1 = mul(hi(lhs), lo(rhs));
	auto const m2 = mul(lo(lhs), hi(rhs));
	auto const l  = mul(lo(lhs), lo(rhs));

	auto const a1 = ResultType{l};
	auto const a2 = bigint_algo::bit_shift_left(ResultType{m1}, 32);
	auto const a3 = bigint_algo::bit_shift_left(ResultType{m2}, 32);
	auto const a4 = ResultType{0, h};

	return
		bigint_algo::add(a1,
		bigint_algo::add(a2,
		bigint_algo::add(a3, a4)));
}

template <typename ResultType, typename T>
inline HAMON_CXX11_CONSTEXPR ResultType
multiply1_impl(T const& x)
{
	return ResultType { lo(x), hi(x) };
}

template <typename ResultType, typename T>
inline HAMON_CXX11_CONSTEXPR ResultType
multiply1(T lhs, T rhs)
{
	return multiply1_impl<ResultType>(mul(lhs, rhs));
}

template <typename T>
inline std::vector<T>
multiply(std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	auto const NA = lhs.size();
	auto const NB = rhs.size();

	std::vector<T> result{0};

	for (hamon::size_t i = 0; i < NA; ++i)
	{
		for (hamon::size_t j = 0; j < NB; ++j)
		{
			auto tmp = multiply1<std::vector<T>>(lhs[i], rhs[j]);
			result = bigint_algo::add(result, bigint_algo::bit_shift_left(tmp, (i+j) * hamon::bitsof<T>()));
		}
	}

	return result;
}

template <hamon::size_t N, typename T, hamon::size_t M, hamon::size_t... Is>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
resized_impl(hamon::array<T, M> const& a, hamon::index_sequence<Is...>)
{
	return hamon::array<T, N>{a[Is]...};
}

template <hamon::size_t N, typename T, hamon::size_t M>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
resized(hamon::array<T, M> const& a)
{
	return resized_impl<N>(a, hamon::make_index_sequence<(N < M) ? N : M>{});
}

#if defined(HAMON_HAS_CXX14_CONSTEXPR)

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, N>
multiply(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	hamon::array<T, N> result{0};

	for (hamon::size_t i = 0; i < N; ++i)
	{
		for (hamon::size_t j = 0; j < N; ++j)
		{
			auto tmp = resized<N>(multiply1<hamon::array<T, 2>>(lhs[i], rhs[j]));
			result = bigint_algo::add(result, bigint_algo::bit_shift_left(tmp, (i+j) * hamon::bitsof<T>()));
		}
	}

	return result;
}

#else

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
multiply_impl_2(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs,
	hamon::array<T, N> const& result, hamon::size_t i, hamon::size_t j)
{
	return j >= N ? result :
		multiply_impl_2(lhs, rhs,
			bigint_algo::add(result,
				bigint_algo::bit_shift_left(
					resized<N>(multiply1<hamon::array<T, 2>>(lhs[i], rhs[j])),
					(i+j) * hamon::bitsof<T>())),
			i, j+1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
multiply_impl_1(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs,
	hamon::array<T, N> const& result, hamon::size_t i)
{
	return i >= N ? result :
		multiply_impl_1(lhs, rhs,
			multiply_impl_2(lhs, rhs, result, i, 0),
			i+1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
multiply(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	return multiply_impl_1(lhs, rhs, hamon::array<T, N>{}, 0);
}

#endif

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
