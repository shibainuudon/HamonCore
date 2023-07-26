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
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

template <typename T>
inline void
bit_shift_right(std::vector<T>& lhs, hamon::uintmax_t rhs)
{
	auto const rem = static_cast<unsigned int>(rhs % hamon::bitsof<T>());
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());

	if (rem == 0)
	{
		for (hamon::size_t i = 0; i < lhs.size(); ++i)
		{
			lhs[i] = detail::get(lhs, i + quo);
		}
	}
	else
	{
		for (hamon::size_t i = 0; i < lhs.size(); ++i)
		{
			lhs[i] = static_cast<T>(
				hamon::shl(detail::get(lhs, i + quo + 1), static_cast<unsigned int>(hamon::bitsof<T>() - rem)) +
				hamon::shr(detail::get(lhs, i + quo), rem));
		}
	}

	bigint_algo::normalize(lhs);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
bit_shift_right(hamon::array<T, N>& lhs, hamon::uintmax_t rhs)
{
	auto const rem = static_cast<unsigned int>(rhs % hamon::bitsof<T>());
	auto const quo = static_cast<unsigned int>(rhs / hamon::bitsof<T>());

	if (rem == 0)
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			lhs[i] = detail::get(lhs, i + quo);
		}
	}
	else
	{
		for (hamon::size_t i = 0; i < N; ++i)
		{
			lhs[i] = static_cast<T>(
				hamon::shl(detail::get(lhs, i + quo + 1), static_cast<unsigned int>(hamon::bitsof<T>() - rem)) +
				hamon::shr(detail::get(lhs, i + quo), rem));
		}
	}
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_SHIFT_RIGHT_HPP
