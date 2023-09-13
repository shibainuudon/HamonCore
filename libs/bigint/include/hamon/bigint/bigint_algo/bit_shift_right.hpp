/**
 *	@file	bit_shift_right.hpp
 *
 *	@brief	bit_shift_right 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/bit/shr.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace bit_shift_right_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
bit_shift_right_impl(T* lhs, hamon::size_t n, hamon::uintmax_t rhs)
{
	auto const rem = static_cast<unsigned int>(rhs % hamon::bitsof<T>());
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());

	hamon::size_t i = 0;

	if (rem == 0)
	{
		for (; i + quo < n; ++i)
		{
			lhs[i] = lhs[i + quo];
		}
	}
	else
	{
		auto const rem2 = static_cast<unsigned int>(hamon::bitsof<T>() - rem);

		for (; i + quo + 1 < n; ++i)
		{
			lhs[i] = static_cast<T>(
				hamon::shl(lhs[i + quo + 1], rem2) +
				hamon::shr(lhs[i + quo], rem));
		}
		for (; i + quo < n; ++i)
		{
			lhs[i] = static_cast<T>(
				hamon::shr(lhs[i + quo], rem));
		}
	}

	for (; i < n; ++i)
	{
		lhs[i] = 0;
	}
}

}	// namespace bit_shift_right_detail

template <typename T>
inline void
bit_shift_right(hamon::vector<T>& lhs, hamon::uintmax_t rhs)
{
	bit_shift_right_detail::bit_shift_right_impl(lhs.data(), lhs.size(), rhs);
	bigint_algo::normalize(lhs);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
bit_shift_right(hamon::array<T, N>& lhs, hamon::uintmax_t rhs)
{
	bit_shift_right_detail::bit_shift_right_impl(lhs.data(), N, rhs);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP
