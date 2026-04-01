/**
 *	@file	bit_shift_left.hpp
 *
 *	@brief	bit_shift_left 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/countl_zero.hpp>
#include <hamon/bigint/bigint_algo/is_zero.hpp>
#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/detail/vector_value_t.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace bit_shift_left_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
bit_shift_left_impl(T* lhs, hamon::size_t n, hamon::size_t rhs)
{
	auto const rem = rhs % hamon::bitsof<T>();
	auto const quo = rhs / hamon::bitsof<T>();

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
		auto const rem2 = hamon::bitsof<T>() - rem;

		for (; i > quo + 1; --i)
		{
			lhs[i - 1] = static_cast<T>(
				(lhs[i - quo - 2] >> rem2) |
				(lhs[i - quo - 1] << rem));
		}
		for (; i > quo; --i)
		{
			lhs[i - 1] = static_cast<T>(
				(lhs[i - quo - 1] << rem));
		}
	}

	for (; i > 0; --i)
	{
		lhs[i - 1] = 0;
	}
}

}	// namespace bit_shift_left_detail

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
bit_shift_left(VectorType& lhs, hamon::size_t rhs)
{
	using T = detail::vector_value_t<VectorType>;

	if (bigint_algo::is_zero(lhs) || rhs == 0)
	{
		return false;
	}

	bool const overflow = (rhs > static_cast<hamon::size_t>(bigint_algo::countl_zero(lhs)));
	auto const quo = (rhs + hamon::bitsof<T>() - 1) / hamon::bitsof<T>();
	hamon::size_t const n = hamon::min(detail::actual_size(lhs) + quo, lhs.max_size());
	detail::resize(lhs, n);
	bit_shift_left_detail::bit_shift_left_impl(lhs.data(), n, rhs);
	bigint_algo::normalize(lhs);
	return overflow;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP
