/**
 *	@file	bit_shift_left.hpp
 *
 *	@brief	bit_shift_left 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/countl_zero.hpp>
#include <hamon/bigint/bigint_algo/detail/get.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/bit/shr.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace detail
{
namespace bigint_algo
{

template <typename VectorType>
struct bit_shift_left_result
{
	bool		overflow;
	VectorType	value;
};

template <typename T>
inline bit_shift_left_result<std::vector<T>>
bit_shift_left(std::vector<T> const& lhs, hamon::uintmax_t rhs)
{
	auto const rem = static_cast<unsigned int>(rhs % hamon::bitsof<T>());
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());

	hamon::size_t const N = lhs.size() + quo + 1;
	std::vector<T> result(N);

	if (rem == 0)
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			result[i] = bigint_algo::get(lhs, i - quo);
		}
	}
	else
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			result[i] = static_cast<T>(
				hamon::shr(bigint_algo::get(lhs, i - quo - 1), static_cast<unsigned int>(hamon::bitsof<T>() - rem)) +
				hamon::shl(bigint_algo::get(lhs, i - quo), rem));
		}
	}

	return {false, bigint_algo::normalize(result)};
}

template <typename T, hamon::size_t N, hamon::size_t... Is>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
bit_shift_left_impl(hamon::array<T, N> const& lhs,
	unsigned int rem, unsigned int quo,
	hamon::index_sequence<Is...>)
{
	return
		rem == 0 ?
		hamon::array<T, N> { bigint_algo::get(lhs, Is - quo)... } :
		hamon::array<T, N> { static_cast<T>(
			hamon::shr(bigint_algo::get(lhs, Is - quo - 1), static_cast<unsigned int>(hamon::bitsof<T>() - rem)) +
			hamon::shl(bigint_algo::get(lhs, Is - quo), rem))...
		};
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR bit_shift_left_result<hamon::array<T, N>>
bit_shift_left(hamon::array<T, N> const& lhs, hamon::uintmax_t rhs)
{
	return
	{
		rhs > bigint_algo::countl_zero(lhs),
		bit_shift_left_impl(lhs,
			static_cast<unsigned int>(rhs % hamon::bitsof<T>()),
			static_cast<unsigned int>(rhs / hamon::bitsof<T>()),
			hamon::make_index_sequence<N>{})
	};
}

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP
