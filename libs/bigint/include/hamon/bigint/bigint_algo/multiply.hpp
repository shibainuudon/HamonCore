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
			bigint_algo::bit_shift_left(tmp, (i+j) * hamon::bitsof<T>());
			bigint_algo::add(result, tmp);
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
		bigint_algo::bit_shift_left(tmp, i * hamon::bitsof<T>());
		bigint_algo::add(result, tmp);
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
			auto f1 = bigint_algo::bit_shift_left(tmp, (i+j) * hamon::bitsof<T>());
			result.overflow = result.overflow || f1;
			auto f2 = bigint_algo::add(result.value, tmp);
			result.overflow = result.overflow || f2;
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
		auto f1 = bigint_algo::bit_shift_left(tmp, i * hamon::bitsof<T>());
		result.overflow = result.overflow || f1;
		auto f2 = bigint_algo::add(result.value, tmp);
		result.overflow = result.overflow || f2;
	}

	return result;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
