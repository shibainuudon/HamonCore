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
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

template <typename T>
inline bool
bit_shift_left(std::vector<T>& lhs, hamon::uintmax_t rhs)
{
	auto const rem = static_cast<unsigned int>(rhs % hamon::bitsof<T>());
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());

	hamon::size_t const N = lhs.size() + quo + 1;
	std::vector<T> result(N);

	if (rem == 0)
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			result[i] = detail::get(lhs, i - quo);
		}
	}
	else
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			result[i] = static_cast<T>(
				hamon::shr(detail::get(lhs, i - quo - 1), static_cast<unsigned int>(hamon::bitsof<T>() - rem)) +
				hamon::shl(detail::get(lhs, i - quo), rem));
		}
	}
	
	bigint_algo::normalize(result);
	lhs = result;

	return false;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
bit_shift_left(hamon::array<T, N>& lhs, hamon::uintmax_t rhs)
{
	bool const overflow = (rhs > bigint_algo::countl_zero(lhs));

	auto const rem = static_cast<unsigned int>(rhs % hamon::bitsof<T>());
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());

	hamon::array<T, N> result{};

	if (rem == 0)
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			result[i] = detail::get(lhs, i - quo);
		}
	}
	else
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			result[i] = static_cast<T>(
				hamon::shr(detail::get(lhs, i - quo - 1), static_cast<unsigned int>(hamon::bitsof<T>() - rem)) +
				hamon::shl(detail::get(lhs, i - quo), rem));
		}
	}
	lhs = result;
	return overflow;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_LEFT_HPP
