/**
 *	@file	multiply.hpp
 *
 *	@brief	multiply 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
#define HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/mul_addc.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace multiply_detail
{

template <typename VectorType, typename T>
inline HAMON_CXX14_CONSTEXPR bool
multiply_impl(VectorType& out, T const* p1, hamon::size_t n1, T rhs)
{
	detail::zero(out);

	detail::resize(out, n1 + 1);
	auto const p3 = out.data();
	auto const n3 = out.size();
	bool overflow = false;
	T carry = 0;
	hamon::size_t i = 0;
	for (; i < n1; ++i)
	{
		auto const r = detail::mul_addc(p1[i], rhs, p3[i], carry);
		p3[i] = detail::lo(r);
		carry = detail::hi(r);
	}
	if (carry != 0)
	{
		if (i < n3)
		{
			p3[i] = carry;
		}
		else
		{
			overflow = true;
		}
	}
	bigint_algo::normalize(out);
	return overflow;
}

template <typename VectorType, typename T>
inline HAMON_CXX14_CONSTEXPR bool
multiply_impl(VectorType& out, T const* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	detail::zero(out);

	// アウターループよりインナーループのほうが回数が多くなるようにしたほうが高速になる
	if (n1 > n2)
	{
		hamon::swap(p1, p2);
		hamon::swap(n1, n2);
	}

	detail::resize(out, n1 + n2);
	auto const p3 = out.data();
	auto const n3 = out.size();
	bool overflow = false;
	for (hamon::size_t i = 0; i < n1; ++i)
	{
		auto const x = p1[i];
		if (x == 0)
		{
			continue;
		}

		hamon::size_t k = i;
		T carry = 0;
		for (hamon::size_t j = 0; j < n2; ++j, ++k)
		{
			if (k >= n3)
			{
				carry = 0;
				overflow = true;
				break;
			}

			auto const y = p2[j];
			auto const r = detail::mul_addc(x, y, p3[k], carry);
			p3[k] = detail::lo(r);
			carry = detail::hi(r);
		}

		for (; carry != 0; ++k)
		{
			if (k >= n3)
			{
				overflow = true;
				break;
			}

			p3[k] = carry;
			carry = T{0};
		}
	}
	bigint_algo::normalize(out);
	return overflow;
}

}	// namespace multiply_detail

// 乗算はin-placeに行うことができないので、左辺(lhs)を出力にするパターンは使えない
// 繰り返し乗算を行う場合に、その都度メモリ確保することを避けるため(とくに vector)、出力変数を外から与える
// out と lhs, out と rhs が、同じオブジェクトや同じ領域の場合の動作は未規定
// オーバーフローフラグを戻り値で返す

template <typename VectorType1, typename VectorType2, typename T3,
	typename T1 = hamon::ranges::range_value_t<VectorType1>,
	typename T2 = hamon::ranges::range_value_t<VectorType2>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_integral<T3>,
		hamon::is_same<T1, T2>,
		hamon::is_same<T1, T3>
	>::value>
>
inline HAMON_CXX14_CONSTEXPR bool
multiply(VectorType1& out, VectorType2 const& lhs, T3 rhs)
{
	return multiply_detail::multiply_impl(out,
		lhs.data(), detail::actual_size(lhs), rhs);
}

template <typename VectorType1, typename VectorType2, typename VectorType3,
	typename T1 = hamon::ranges::range_value_t<VectorType1>,
	typename T2 = hamon::ranges::range_value_t<VectorType2>,
	typename T3 = hamon::ranges::range_value_t<VectorType3>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_same<T1, T2>,
		hamon::is_same<T1, T3>
	>::value>
>
inline HAMON_CXX14_CONSTEXPR bool
multiply(VectorType1& out, VectorType2 const& lhs, VectorType3 const& rhs)
{
	return multiply_detail::multiply_impl(out,
		lhs.data(), detail::actual_size(lhs),
		rhs.data(), detail::actual_size(rhs));
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
