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
#include <hamon/bit/shl.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
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

template <typename VectorType, typename T = hamon::ranges::range_value_t<VectorType>>
inline HAMON_CXX14_CONSTEXPR hamon::pair<T, VectorType>
div1(VectorType const& lhs, VectorType const& rhs)
{
	{
		auto const c = bigint_algo::compare(lhs, rhs);

		// lhs < rhs
		if (c < 0)
		{
			return hamon::make_pair(T{0}, VectorType{0});
		}

		// lhs == rhs
		if (c == 0)
		{
			return hamon::make_pair(T{1}, rhs);
		}
	}

	// 割り算の答えをバイナリサーチで探す
	T w = hamon::shl(T{1}, static_cast<unsigned int>(hamon::bitsof<T>() - 1));
	T q = w;
	VectorType x{0};
	for (;;)
	{
		w /= 2;
		auto t = bigint_algo::multiply(rhs, q);
		x = t.value;

		// x と lhs を比較する。ただし、乗算の結果がオーバーフローしている場合は
		// 必ず x > lhs。
		auto c = t.overflow ? 1 : bigint_algo::compare(x, lhs);

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
	return hamon::make_pair(q, x);
}

template <typename T>
inline div_mod_result<std::vector<T>>
div_mod(std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	using VectorType = std::vector<T>;

	VectorType rem{0};
	VectorType quo{0};
	for (auto it = lhs.rbegin(); it != lhs.rend(); ++it)
	{
		rem = bigint_algo::bit_shift_left(rem, hamon::bitsof<T>()).value;
		rem[0] = *it;

		auto const q = div1(rem, rhs);
		quo = bigint_algo::bit_shift_left(quo, hamon::bitsof<T>()).value;
		quo[0] = q.first;

		rem = bigint_algo::sub(rem, q.second);
	}
	return { quo, rem };
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR div_mod_result<hamon::array<T, N>>
div_mod(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	using VectorType = hamon::array<T, N>;

	VectorType rem{0};
	VectorType quo{0};
	for (auto it = lhs.rbegin(); it != lhs.rend(); ++it)
	{
		rem = bigint_algo::bit_shift_left(rem, hamon::bitsof<T>()).value;
		rem[0] = *it;

		auto const q = div1(rem, rhs);
		quo = bigint_algo::bit_shift_left(quo, hamon::bitsof<T>()).value;
		quo[0] = q.first;

		rem = bigint_algo::sub(rem, q.second);
	}
	return { quo, rem };
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DIV_MOD_HPP
