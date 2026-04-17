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
#include <hamon/bigint/bigint_algo/detail/one.hpp>
#include <hamon/bigint/bigint_algo/detail/vector_value_t.hpp>
#include <hamon/bigint/bigint_algo/detail/div.hpp>
#include <hamon/bigint/bigint_algo/detail/uint128.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_right.hpp>
#include <hamon/bigint/bigint_algo/bit_width.hpp>
#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/sub.hpp>
#include <hamon/bigint/bigint_algo/to_uint.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/bit/shr.hpp>
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

template <typename U, typename VectorType>
inline HAMON_CXX14_CONSTEXPR U
bit_shift_right_to_uint(VectorType const& vec, hamon::size_t shift)
{
	using T = detail::vector_value_t<VectorType>;
	auto const bits = static_cast<int>(hamon::bitsof<T>());
	auto const rem = static_cast<int>(shift % bits);
	auto const quo = static_cast<int>((shift + bits - 1) / bits);

	auto p = vec.data();
	auto n = static_cast<int>(vec.size());
	auto m = static_cast<int>(sizeof(U) / sizeof(T));

	U result{};

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

template <typename T>
struct make_dividend;

template <>
struct make_dividend<hamon::uint8_t> { using type = hamon::uint16_t; };
template <>
struct make_dividend<hamon::uint16_t> { using type = hamon::uint32_t; };
template <>
struct make_dividend<hamon::uint32_t> { using type = hamon::uint64_t; };
#if defined(HAMON_HAS_INT128)
template <>
struct make_dividend<hamon::uint64_t> { using type = __uint128_t; };
#else
template <>
struct make_dividend<hamon::uint64_t> { using type = detail::uint128; };
#endif

template <typename T>
using make_dividend_t = typename make_dividend<T>::type;

template <typename VectorType1, typename VectorType2,
	typename T = detail::vector_value_t<VectorType1>>
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

	// lhs と rhs を整数に変換して除算する
	// このとき、被除数は除数の倍のサイズにする。
	using D = make_dividend_t<T>;
	auto const shift = static_cast<hamon::size_t>(hamon::max(0, bigint_algo::bit_width(rhs) - (int)hamon::bitsof<T>()));
	auto l = bit_shift_right_to_uint<D>(lhs, shift);
	auto r = bit_shift_right_to_uint<T>(rhs, shift);

	T q = detail::div(l, r);

	// 得られた q は、必ず正しい商 *以上* の値になっているので、
	// デクリメントしながら正しい商を探す。
	// (正しい商なら、q * rhs <= lhs になる)

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
}

template <typename VectorType, typename T>
inline HAMON_CXX14_CONSTEXPR void
push_front(VectorType& vec, T x)
{
	if (bigint_algo::is_zero(vec))
	{
		vec.data()[0] = x;
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
	{
		auto const c = bigint_algo::compare(lhs, rhs);

		// lhs < rhs
		if (c < 0)
		{
			detail::zero(quo);
			detail::copy(rem, lhs);
			return;
		}

		// lhs == rhs
		if (c == 0)
		{
			detail::one(quo);
			detail::zero(rem);
			return;
		}
	}

	auto const p1 = lhs.data();
	auto const p2 = rhs.data();
	auto const n1 = detail::actual_size(lhs);
	auto const n2 = detail::actual_size(rhs);

	hamon::size_t i = n1;

	auto n3 = n2;
	if (p1[n1-1] < p2[n2-1])
	{
		n3++;
	}

	detail::resize(rem, n3);
	{
		auto rem_p = rem.data();
		for (hamon::size_t j = n3; j > 0; --j)
		{
			rem_p[j - 1] = p1[i - 1];
			--i;
		}
	}

	detail::resize(quo, i + 1);
	auto quo_p = quo.data();

	VectorType1 tmp{};
	for (;;)
	{
		auto const q = div1(rem, rhs, tmp);
		quo_p[i] = q;

		bigint_algo::sub(rem, tmp);

		if (i == 0)
		{
			break;
		}

		push_front(rem, p1[i - 1]);
		--i;
	}

	bigint_algo::normalize(quo);
}

}	// namespace div_mod_detail

template <typename VectorType1, typename VectorType2, typename VectorType3,
	typename T1 = detail::vector_value_t<VectorType1>,
	typename T2 = detail::vector_value_t<VectorType2>,
	typename T3 = detail::vector_value_t<VectorType3>,
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
