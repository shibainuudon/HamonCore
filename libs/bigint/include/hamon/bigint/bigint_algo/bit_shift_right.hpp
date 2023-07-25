/**
 *	@file	bit_shift_right.hpp
 *
 *	@brief	bit_shift_right 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
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
namespace bigint_algo
{

template <typename T>
inline std::vector<T>
bit_shift_right(std::vector<T> const& lhs, hamon::uintmax_t rhs)
{
	auto const rem = static_cast<unsigned int>(rhs % hamon::bitsof<T>());
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());

	if (quo > lhs.size())
	{
		return {0};
	}

	hamon::size_t const N = lhs.size() - quo;
	std::vector<T> result(N);

	if (rem == 0)
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			result[i] = detail::get(lhs, i + quo);
		}
	}
	else
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			result[i] = static_cast<T>(
				hamon::shl(detail::get(lhs, i + quo + 1), static_cast<unsigned int>(hamon::bitsof<T>() - rem)) +
				hamon::shr(detail::get(lhs, i + quo), rem));
		}
	}

	return bigint_algo::normalize(result);
}

template <typename T, hamon::size_t N, hamon::size_t... Is>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
bit_shift_right_impl(hamon::array<T, N> const& lhs,
	unsigned int rem, unsigned int quo,
	hamon::index_sequence<Is...>)
{
	return
		rem == 0 ?
		hamon::array<T, N> { detail::get(lhs, Is + quo)... } :
		hamon::array<T, N> { static_cast<T>(
			hamon::shl(detail::get(lhs, Is + quo + 1), static_cast<unsigned int>(hamon::bitsof<T>() - rem)) +
			hamon::shr(detail::get(lhs, Is + quo), rem))...
		};
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
bit_shift_right(hamon::array<T, N> const& lhs, hamon::uintmax_t rhs)
{
	return bit_shift_right_impl(lhs,
		static_cast<unsigned int>(rhs % hamon::bitsof<T>()),
		static_cast<unsigned int>(rhs / hamon::bitsof<T>()),
		hamon::make_index_sequence<N>{});
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP
