/**
 *	@file	add.hpp
 *
 *	@brief	add 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_ADD_HPP
#define HAMON_BIGINT_BIGINT_ALGO_ADD_HPP

#include <hamon/bigint/bigint_algo/detail/addc.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/array.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
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
// * 引数を複数取る場合、
//   arrayは要素数が同じ
//   vector/inplace_vectorは要素数が異なる場合がある
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

template <typename VectorType, typename T>
inline HAMON_CXX14_CONSTEXPR bool
add_impl(VectorType& lhs, T const* p2, hamon::size_t n2)
{
	detail::resize(lhs, hamon::max(lhs.size(), n2) + 1);

	auto const p1 = lhs.data();
	auto const n1 = lhs.size();

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

	bigint_algo::normalize(lhs);
	return carry != 0;
}

template <typename VectorType, typename T>
inline HAMON_CXX14_CONSTEXPR bool
add_impl(VectorType& out, T const* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	detail::resize(out, hamon::max(n1, n2) + 1);

	auto const p3 = out.data();
	auto const n3 = out.size();

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
	for (; carry != 0 && i < n3; ++i)
	{
		auto const x = detail::addc(p3[i], T{0}, carry);
		p3[i] = detail::lo(x);
		carry = detail::hi(x);
	}

	bigint_algo::normalize(out);
	return carry != 0;
}

}	// namespace add_detail

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::vector<T>& lhs, hamon::vector<T> const& rhs)
{
	return add_detail::add_impl(lhs, rhs.data(), rhs.size());
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::vector<T>& lhs, T rhs)
{
	return add_detail::add_impl(lhs, &rhs, 1);
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::vector<T>& out, hamon::vector<T> const& lhs, T rhs)
{
	return add_detail::add_impl(out, lhs.data(), lhs.size(), &rhs, 1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::inplace_vector<T, N>& lhs, hamon::inplace_vector<T, N> const& rhs)
{
	return add_detail::add_impl(lhs, rhs.data(), rhs.size());
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::inplace_vector<T, N>& lhs, T rhs)
{
	return add_detail::add_impl(lhs, &rhs, 1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::inplace_vector<T, N>& out, hamon::inplace_vector<T, N> const& lhs, T rhs)
{
	return add_detail::add_impl(out, lhs.data(), lhs.size(), &rhs, 1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::array<T, N>& lhs, hamon::array<T, N> const& rhs)
{
	return add_detail::add_impl(lhs, rhs.data(), detail::actual_size(rhs));
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::array<T, N>& lhs, T rhs)
{
	return add_detail::add_impl(lhs, &rhs, 1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::array<T, N>& out, hamon::array<T, N> const& lhs, T rhs)
{
	detail::zero(out);
	return add_detail::add_impl(out, lhs.data(), lhs.size(), &rhs, 1);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_ADD_HPP
