/**
 *	@file	add.hpp
 *
 *	@brief	add 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_ADD_HPP
#define HAMON_BIGINT_BIGINT_ALGO_ADD_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/addc.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

// bigint_algo全体的な取り決め
// * vector<T> または inplace_vector<T, N> または array<T, N> が対象
// * T は 符号なし整数型
// * 数値の格納の仕方はリトルエンディアン。つまり下位の桁を前方に格納する。
// * array/inplace_vectorを引数にとるものはC++14でconstexpr
// * vectorを引数にとるものはC++20でconstexpr
// * 計算結果が入力より桁数が大きくなる場合、
//   arrayはオーバーフローする
//   vectorは自動的に要素数が増える
//   inplace_vectorは自動的に要素数が増えるが、最大要素数を超えた場合はオーバーフローする
// 
// vector/inplace_vectorの正規化ルール：
// * 上位桁の0を削除する。
// * 空の場合は {0} にする。
//   { 1, 0, 0 } -> { 1 }
//   { 0, 1, 0 } -> { 0, 1 }
//   { 0, 0, 1 } -> { 0, 0, 1 }
//   { 0, 0, 0 } -> { 0 }
//   { 0, 1 } -> { 0, 1 }
//   { 1, 0 } -> { 1 }
//   { 0, 0 } -> { 0 }
//   { 0 } -> { 0 }
//   {} -> { 0 }
// * 出力は自動的に正規化する。
// * 入力は正規化されていると想定する。正規化されていない値を渡されたときの動作は未規定。

namespace add_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
add_impl(T* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	T carry = 0;
	hamon::size_t i = 0;

	for (; i < n2; ++i)
	{
		auto const x = detail::addc(p1[i], p2[i], carry);
		p1[i] = detail::lo(x);
		carry = detail::hi(x);
	}
	for (; carry != 0 && i < n1; ++i)
	{
		auto const x = detail::addc(p1[i], T{0}, carry);
		p1[i] = detail::lo(x);
		carry = detail::hi(x);
	}

	return carry != 0;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
add_impl(T* p3, hamon::size_t n3, T const* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	T carry = 0;
	hamon::size_t i = 0;

	for (; i < n2; ++i)
	{
		auto const x = detail::addc(p1[i], p2[i], carry);
		p3[i] = detail::lo(x);
		carry = detail::hi(x);
	}
	for (; carry != 0 && i < n1; ++i)
	{
		auto const x = detail::addc(p1[i], T{0}, carry);
		p3[i] = detail::lo(x);
		carry = detail::hi(x);
	}
	for (; i < n1; ++i)
	{
		p3[i] = p1[i];
	}
	for (; i < n3; ++i)
	{
		p3[i] = carry;
		carry = T{0};
	}

	return carry != 0;
}

}	// namespace add_detail

template <typename VectorType1, typename VectorType2,
	typename T1 = hamon::ranges::range_value_t<VectorType1>,
	typename T2 = hamon::ranges::range_value_t<VectorType2>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_same<T1, T2>
	>::value>
>
inline HAMON_CXX14_CONSTEXPR bool
add(VectorType1& lhs, VectorType2 const& rhs)
{
	auto n1 = detail::actual_size(lhs);
	auto n2 = detail::actual_size(rhs);
	detail::resize(lhs, hamon::max(n1, n2) + 1);
	auto overflow = add_detail::add_impl(lhs.data(), lhs.size(), rhs.data(), n2);
	bigint_algo::normalize(lhs);
	return overflow;
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
add(VectorType1& out, VectorType2 const& lhs, VectorType3 const& rhs)
{
	auto n1 = detail::actual_size(lhs);
	auto n2 = detail::actual_size(rhs);
	detail::resize(out, hamon::max(n1, n2) + 1);
	auto overflow = add_detail::add_impl(out.data(), out.size(), lhs.data(), n1, rhs.data(), n2);
	bigint_algo::normalize(out);
	return overflow;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_ADD_HPP
