/**
 *	@file	div_mod.hpp
 *
 *	@brief	div_mod 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DIV_MOD_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DIV_MOD_HPP

#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_right.hpp>
#include <hamon/bigint/bigint_algo/sub.hpp>
#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/array.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

template <typename T>
struct div_mod_result
{
	T	quo;	// 商
	T	rem;	// あまり
};

namespace div_mod_detail
{

template <typename VectorType, typename T = hamon::ranges::range_value_t<VectorType>>
inline HAMON_CXX14_CONSTEXPR T
div1(VectorType const& lhs, VectorType const& rhs, VectorType& x)
{
	{
		auto const c = bigint_algo::compare(lhs, rhs);

		// lhs < rhs
		if (c < 0)
		{
			detail::zero(x);
			return 0;
		}

		// lhs == rhs
		if (c == 0)
		{
			x = rhs;
			return 1;
		}
	}

	// 割り算の答えをバイナリサーチで探す
	T w = hamon::shl(T{1}, static_cast<unsigned int>(hamon::bitsof<T>() - 1));
	T q = w;
	for (;;)
	{
		w /= 2;
		auto f = bigint_algo::multiply(x, rhs, q);

		// x と lhs を比較する。ただし、乗算の結果がオーバーフローしている場合は
		// 必ず x > lhs。
		auto c = f ? 1 : bigint_algo::compare(x, lhs);

		if (c == 0)
		{
			break;
		}
		else if (c > 0)
		{
			q = static_cast<T>(q - w);
		}
		else
		{
			q = static_cast<T>(q + w);
		}

		if (w == 0)
		{
			if (c > 0)
			{
				q = static_cast<T>(q - 1);
			}
			else
			{
				break;
			}
		}
	}
	return q;
}

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR div_mod_result<VectorType>
div_mod_impl(VectorType const& lhs, VectorType const& rhs)
{
	using T = hamon::ranges::range_value_t<VectorType>;
	div_mod_result<VectorType> result
	{
		{0},
		{0},
	};
	VectorType tmp{0};
	for (hamon::size_t i = lhs.size(); i > 0; --i)
	{
		bigint_algo::bit_shift_left(result.rem, hamon::bitsof<T>());
		result.rem[0] = lhs[i-1];

		auto const q = div1(result.rem, rhs, tmp);
		bigint_algo::bit_shift_left(result.quo, hamon::bitsof<T>());
		result.quo[0] = q;

		bigint_algo::sub(result.rem, tmp);
	}
	return result;
}

}	// namespace div_mod_detail

template <typename T>
inline div_mod_result<std::vector<T>>
div_mod(std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	return div_mod_detail::div_mod_impl(lhs, rhs);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR div_mod_result<hamon::array<T, N>>
div_mod(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	return div_mod_detail::div_mod_impl(lhs, rhs);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DIV_MOD_HPP
