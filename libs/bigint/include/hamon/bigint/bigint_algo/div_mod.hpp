/**
 *	@file	div_mod.hpp
 *
 *	@brief	div_mod 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DIV_MOD_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DIV_MOD_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/copy.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_right.hpp>
#include <hamon/bigint/bigint_algo/bit_width.hpp>
#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/bigint/bigint_algo/sub.hpp>
#include <hamon/bigint/bigint_algo/to_uint.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/bit/shr.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/assert.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace div_mod_detail
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR hamon::uint64_t
bit_shift_right_to_uint64(VectorType const& vec, hamon::size_t shift)
{
	using T = hamon::ranges::range_value_t<VectorType>;
	auto const bits = static_cast<unsigned int>(hamon::bitsof<T>());
	auto const rem = static_cast<unsigned int>(shift % bits);
	auto const quo = static_cast<unsigned int>((shift + bits - 1) / bits);

	auto p = vec.data();
	auto n = static_cast<unsigned int>(vec.size());
	auto m = static_cast<unsigned int>(sizeof(hamon::uint64_t) / sizeof(T));

	hamon::uint64_t result{};

	auto const l = hamon::min(quo, n);
	for (auto i = hamon::min(quo + m, n); i > l; --i)
	{
		result = hamon::shl(result, bits) | p[i - 1];
	}

	if (rem != 0)
	{
		result = hamon::shl(result, bits - rem) | hamon::shr(p[l - 1], rem);
	}

	return result;
}

template <typename VectorType1, typename VectorType2,
	typename T = hamon::ranges::range_value_t<VectorType1>>
inline HAMON_CXX14_CONSTEXPR T
div1(VectorType1 const& lhs, VectorType2 const& rhs, VectorType1& x)
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
			detail::copy(x, rhs);
			return 1;
		}
	}
#if 1
	// lhs と rhs を64ビットの値に変換して除算する
	auto const shift = static_cast<hamon::size_t>(hamon::max(0, bigint_algo::bit_width(lhs) - 64));
	auto l = bit_shift_right_to_uint64(lhs, shift);
	auto r = bit_shift_right_to_uint64(rhs, shift);
	T q = static_cast<T>(hamon::min<hamon::uint64_t>(l / r, hamon::numeric_limits<T>::max()));

	// 得られた答えは、必ず正しい答え以上の値になっているので、
	// デクリメントしながら正しい答えを探す
	for (;;)
	{
		detail::copy(x, rhs);
		auto f = bigint_algo::multiply(x, q);

		// x と lhs を比較する。ただし、乗算の結果がオーバーフローしている場合は
		// 必ず x > lhs。
		auto c = f ? 1 : bigint_algo::compare(x, lhs);

		if (c > 0)
		{
			q--;
		}
		else
		{
			break;
		}
	}
	return q;
#else
	// 割り算の答えをバイナリサーチで探す
	T w = hamon::shl(T{1}, static_cast<unsigned int>(hamon::bitsof<T>() - 1));
	T q = w;
	for (;;)
	{
		w /= 2;
		detail::copy(x, rhs);
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
#endif
}

template <typename VectorType, typename T>
inline HAMON_CXX14_CONSTEXPR void
push_front(VectorType& vec, T x)
{
	if (bigint_algo::is_zero(vec))
	{
		vec[0] = x;
		return;
	}

	auto n = hamon::min(detail::actual_size(vec) + 1, vec.max_size());
	detail::resize(vec, n);
	auto p = vec.data();
	for (; n > 1; --n)
	{
		p[n - 1] = p[n - 2];
	}
	p[0] = x;
}

template <typename VectorType1, typename VectorType2, typename VectorType3>
inline HAMON_CXX14_CONSTEXPR void
div_mod_impl(VectorType1& quo, VectorType1& rem, VectorType2 const& lhs, VectorType3 const& rhs)
{
	detail::zero(quo);
	detail::zero(rem);

	auto const p = lhs.data();
	auto const n1 = detail::actual_size(lhs);
	auto const n2 = detail::actual_size(rhs);

	if (n1 < n2)
	{
		detail::copy(rem, lhs);
		return;
	}

	hamon::size_t i = n1;

	detail::resize(rem, n2);
	for (hamon::size_t j = n2; j > 0; --j)
	{
		rem[j - 1] = p[i - 1];
		--i;
	}

	if (i != 0 && bigint_algo::compare(rem, rhs) < 0)
	{
		push_front(rem, p[i - 1]);
		--i;
	}

	VectorType1 tmp{0};
	for (;;)
	{
		auto const q = div1(rem, rhs, tmp);
		push_front(quo, q);

		bigint_algo::sub(rem, tmp);

		if (i == 0)
		{
			break;
		}

		push_front(rem, p[i - 1]);
		--i;
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
