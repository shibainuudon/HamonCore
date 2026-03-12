/**
 *	@file	div_mod.hpp
 *
 *	@brief	div_mod 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DIV_MOD_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DIV_MOD_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/bigint/bigint_algo/sub.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace div_mod_detail
{

template <typename VectorType1, typename VectorType2,
	typename T = hamon::ranges::range_value_t<VectorType1>>
inline HAMON_CXX14_CONSTEXPR T
div1(VectorType1 const& lhs, VectorType2 const& rhs, VectorType2& x)
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
		x = rhs;
		auto f = bigint_algo::multiply(x, q);

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

template <typename VectorType1, typename VectorType2, typename VectorType3>
inline HAMON_CXX14_CONSTEXPR void
div_mod_impl(VectorType1& quo, VectorType1& rem, VectorType2 const& lhs, VectorType3 const& rhs)
{
	using T = hamon::ranges::range_value_t<VectorType1>;

	detail::zero(quo);
	detail::zero(rem);

	auto const p = lhs.data();
	auto const n = detail::actual_size(lhs);

	VectorType3 tmp{0};
	for (hamon::size_t i = n; i > 0; --i)
	{
		bigint_algo::bit_shift_left(rem, hamon::bitsof<T>());
		rem[0] = p[i-1];

		auto const q = div1(rem, rhs, tmp);
		bigint_algo::bit_shift_left(quo, hamon::bitsof<T>());
		quo[0] = q;

		bigint_algo::sub(rem, tmp);
	}
}

}	// namespace div_mod_detail

template <typename VectorType1, typename VectorType2, typename VectorType3,
	typename T1 = hamon::ranges::range_value_t<VectorType1>,
	typename T2 = hamon::ranges::range_value_t<VectorType2>,
	typename T3 = hamon::ranges::range_value_t<VectorType3>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_same<T1, T2>,
		hamon::is_same<T1, T3>
	>::value>
>
inline HAMON_CXX14_CONSTEXPR void
div_mod(VectorType1& quo, VectorType1& rem,
	VectorType2 const& lhs, VectorType3 const& rhs)
{
	// pre: VectorType1 の 最大要素数は lhs、rhs の要素数以上でなければならない
	HAMON_ASSERT(quo.max_size() >= detail::actual_size(lhs));
	HAMON_ASSERT(quo.max_size() >= detail::actual_size(rhs));
	return div_mod_detail::div_mod_impl(quo, rem, lhs, rhs);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DIV_MOD_HPP
