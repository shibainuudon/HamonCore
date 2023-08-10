/**
 *	@file	bit_shift_left.hpp
 *
 *	@brief	bit_shift_left 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/countl_zero.hpp>
#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/bit/shr.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

namespace bit_shift_left_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
bit_shift_left_impl(T* lhs, hamon::size_t n, hamon::uintmax_t rhs)
{
	auto const rem = static_cast<unsigned int>(rhs % hamon::bitsof<T>());
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());

	hamon::size_t i = n;

	if (rem == 0)
	{
		for (; i > quo; --i)
		{
			lhs[i - 1] = lhs[i - quo - 1];
		}
	}
	else
	{
		auto const rem2 = static_cast<unsigned int>(hamon::bitsof<T>() - rem);

		for (; i > quo + 1; --i)
		{
			lhs[i - 1] = static_cast<T>(
				hamon::shr(lhs[i - quo - 2], rem2) +
				hamon::shl(lhs[i - quo - 1], rem));
		}
		for (; i > quo; --i)
		{
			lhs[i - 1] = static_cast<T>(
				hamon::shl(lhs[i - quo - 1], rem));
		}
	}

	for (; i > 0; --i)
	{
		lhs[i - 1] = 0;
	}
}

}	// namespace bit_shift_left_detail

template <typename T>
inline bool
bit_shift_left(std::vector<T>& lhs, hamon::uintmax_t rhs)
{
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());
	hamon::size_t const N = lhs.size() + quo + 1;
	lhs.resize(N);
	bit_shift_left_detail::bit_shift_left_impl(lhs.data(), N, rhs);
	bigint_algo::normalize(lhs);

	return false;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
bit_shift_left(hamon::array<T, N>& lhs, hamon::uintmax_t rhs)
{
	bool const overflow = (rhs > bigint_algo::countl_zero(lhs));
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());
	hamon::size_t const n = hamon::min(detail::actual_size(lhs) + quo + 1, N);
	bit_shift_left_detail::bit_shift_left_impl(lhs.data(), n, rhs);
	return overflow;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP
