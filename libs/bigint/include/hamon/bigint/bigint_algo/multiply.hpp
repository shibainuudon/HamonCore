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
#include <hamon/bigint/bigint_algo/detail/mul.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

template <typename ResultType, typename T>
inline HAMON_CXX11_CONSTEXPR ResultType
multiply1_impl(T const& x)
{
	return ResultType { detail::lo(x), detail::hi(x) };
}

template <typename ResultType, typename T>
inline HAMON_CXX11_CONSTEXPR ResultType
multiply1(T lhs, T rhs)
{
	return multiply1_impl<ResultType>(detail::mul(lhs, rhs));
}

template <typename VectorType>
struct multiply_result
{
	bool		overflow;
	VectorType	value;
};

template <typename T>
inline multiply_result<std::vector<T>>
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
			result = bigint_algo::add(result, bigint_algo::bit_shift_left(tmp, (i+j) * hamon::bitsof<T>()).value).value;
		}
	}

	return {false, result};
}

template <typename T>
inline multiply_result<std::vector<T>>
multiply(std::vector<T> const& lhs, T rhs)
{
	auto const NA = lhs.size();

	std::vector<T> result{0};

	for (hamon::size_t i = 0; i < NA; ++i)
	{
		auto tmp = multiply1<std::vector<T>>(lhs[i], rhs);
		result = bigint_algo::add(result, bigint_algo::bit_shift_left(tmp, i * hamon::bitsof<T>()).value).value;
	}

	return {false, result};
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, 1>>
multiply_helper(hamon::array<T, 2> const& t)
{
	return
	{
		t[1] != 0,
		hamon::array<T, 1>{t[0]}
	};
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, 1>>
multiply(hamon::array<T, 1> const& lhs, hamon::array<T, 1> const& rhs)
{
	return multiply_helper(multiply1<hamon::array<T, 2>>(lhs[0], rhs[0]));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, 1>>
multiply(hamon::array<T, 1> const& lhs, T rhs)
{
	return multiply_helper(multiply1<hamon::array<T, 2>>(lhs[0], rhs));
}

#if defined(HAMON_HAS_CXX14_CONSTEXPR)

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	multiply_result<hamon::array<T, N>> result{};

	for (hamon::size_t i = 0; i < N; ++i)
	{
		for (hamon::size_t j = 0; j < N; ++j)
		{
			auto tmp = multiply1<hamon::array<T, N>>(lhs[i], rhs[j]);
			auto t1 = bigint_algo::bit_shift_left(tmp, (i+j) * hamon::bitsof<T>());
			result.overflow = result.overflow || t1.overflow;
			auto t2 = bigint_algo::add(result.value, t1.value);
			result.overflow = result.overflow || t2.overflow;
			result.value = t2.value;
		}
	}

	return result;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply(hamon::array<T, N> const& lhs, T rhs)
{
	multiply_result<hamon::array<T, N>> result{};

	for (hamon::size_t i = 0; i < N; ++i)
	{
		auto tmp = multiply1<hamon::array<T, N>>(lhs[i], rhs);
		auto t1 = bigint_algo::bit_shift_left(tmp, i * hamon::bitsof<T>());
		result.overflow = result.overflow || t1.overflow;
		auto t2 = bigint_algo::add(result.value, t1.value);
		result.overflow = result.overflow || t2.overflow;
		result.value = t2.value;
	}

	return result;
}

#else

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply_impl_1_5(add_result<hamon::array<T, N>> const& t, bool overflow)
{
	return {t.overflow || overflow, t.value};
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply_impl_1_4(
	multiply_result<hamon::array<T, N>> const& result,
	bit_shift_left_result<hamon::array<T, N>> const& t)
{
	return multiply_impl_1_5(bigint_algo::add(result.value, t.value), result.overflow || t.overflow);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply_impl_1_3(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs,
	multiply_result<hamon::array<T, N>> const& result, hamon::size_t i, hamon::size_t j)
{
	return multiply_impl_1_4(
		result,
		bigint_algo::bit_shift_left(
			multiply1<hamon::array<T, N>>(lhs[i], rhs[j]),
			(i+j) * hamon::bitsof<T>()));
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply_impl_1_2(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs,
	multiply_result<hamon::array<T, N>> const& result, hamon::size_t i, hamon::size_t j)
{
	return j >= N ? result :
		multiply_impl_1_2(lhs, rhs,
			multiply_impl_1_3(lhs, rhs, result, i, j),
			i, j+1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply_impl_1_1(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs,
	multiply_result<hamon::array<T, N>> const& result, hamon::size_t i)
{
	return i >= N ? result :
		multiply_impl_1_1(lhs, rhs,
			multiply_impl_1_2(lhs, rhs, result, i, 0),
			i+1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	return multiply_impl_1_1(lhs, rhs, multiply_result<hamon::array<T, N>>{}, 0);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply_impl_2_4(add_result<hamon::array<T, N>> const& t, bool overflow)
{
	return {t.overflow || overflow, t.value};
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply_impl_2_3(
	multiply_result<hamon::array<T, N>> const& result,
	bit_shift_left_result<hamon::array<T, N>> const& t)
{
	return multiply_impl_2_4(bigint_algo::add(result.value, t.value), result.overflow || t.overflow);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply_impl_2_2(hamon::array<T, N> const& lhs, T rhs,
	multiply_result<hamon::array<T, N>> const& result, hamon::size_t i)
{
	return multiply_impl_2_3(
		result,
		bigint_algo::bit_shift_left(
			multiply1<hamon::array<T, N>>(lhs[i], rhs),
			i * hamon::bitsof<T>()));
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply_impl_2_1(hamon::array<T, N> const& lhs, T rhs,
	multiply_result<hamon::array<T, N>> const& result, hamon::size_t i)
{
	return i >= N ? result :
		multiply_impl_2_1(lhs, rhs,
			multiply_impl_2_2(lhs, rhs, result, i),
			i+1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR multiply_result<hamon::array<T, N>>
multiply(hamon::array<T, N> const& lhs, T rhs)
{
	return multiply_impl_2_1(lhs, rhs, multiply_result<hamon::array<T, N>>{}, 0);
}

#endif

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
