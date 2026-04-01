/**
 *	@file	bit_shift_right.hpp
 *
 *	@brief	bit_shift_right 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace bit_shift_right_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::size_t
bit_shift_right_impl(T* lhs, hamon::size_t n, hamon::size_t rhs)
{
	auto const rem = rhs % hamon::bitsof<T>();
	auto const quo = rhs / hamon::bitsof<T>();

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
		auto const rem2 = hamon::bitsof<T>() - rem;

		for (; i + quo + 1 < n; ++i)
		{
			lhs[i] = static_cast<T>(
				(lhs[i + quo + 1] << rem2) |
				(lhs[i + quo] >> rem));
		}
		for (; i + quo < n; ++i)
		{
			lhs[i] = static_cast<T>(
				(lhs[i + quo] >> rem));
		}
	}

	return i;
}

}	// namespace bit_shift_right_detail

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR void
bit_shift_right(VectorType& lhs, hamon::size_t rhs)
{
	auto n = bit_shift_right_detail::bit_shift_right_impl(lhs.data(), lhs.size(), rhs);
	if (n == 0)
	{
		detail::zero(lhs);
	}
	else
	{
		detail::resize(lhs, n);
		bigint_algo::normalize(lhs);
	}
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
bit_shift_right(hamon::array<T, N>& lhs, hamon::size_t rhs)
{
	auto p = lhs.data();
	auto n = detail::actual_size(lhs);
	auto i = bit_shift_right_detail::bit_shift_right_impl(p, n, rhs);
	for (; i < n; ++i)
	{
		p[i] = 0;
	}
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP
