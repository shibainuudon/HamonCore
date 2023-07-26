/**
 *	@file	add.hpp
 *
 *	@brief	add 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_ADD_HPP
#define HAMON_BIGINT_BIGINT_ALGO_ADD_HPP

#include <hamon/bigint/bigint_algo/detail/addc.hpp>
#include <hamon/bigint/bigint_algo/detail/get.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/array.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

// bigint_algo全体的な取り決め
// * vector<T> または array<T, N> を対象
// * T は 符号なし整数型
// * 数値の格納の仕方はリトルエンディアン。つまり下位の桁を前方に格納する。
// * arrayを引数にとるものはC++14でconstexpr
// * vectorを引数にとるものはC++20でconstexpr (TODO)
// * 引数を複数取る場合、
//   arrayは要素数が同じ
//   vectorは要素数が異なる場合がある
// * 計算結果が入力より桁数が大きくなる場合、
//   arrayはオーバーフローする
//   vectorは自動的に要素数が増える
// 
// vectorの正規化ルール：
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
inline HAMON_CXX14_CONSTEXPR T
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
	return carry;
}

}	// namespace add_detail

template <typename T>
inline bool
add(std::vector<T>& lhs, std::vector<T> const& rhs)
{
	auto const N = hamon::max(lhs.size(), rhs.size());
	lhs.resize(N);
	T carry = add_detail::add_impl(&lhs[0], lhs.size(), &rhs[0], rhs.size());
	if (carry != 0)
	{
		lhs.push_back(carry);
	}
	return false;
}

template <typename T>
inline bool
add(std::vector<T>& lhs, T rhs)
{
	T carry = add_detail::add_impl(&lhs[0], lhs.size(), &rhs, 1);
	if (carry != 0)
	{
		lhs.push_back(carry);
	}
	return false;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::array<T, N>& lhs, hamon::array<T, N> const& rhs)
{
	T carry = add_detail::add_impl(&lhs[0], lhs.size(), &rhs[0], rhs.size());
	return carry != 0;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
add(hamon::array<T, N>& lhs, T rhs)
{
	T carry = add_detail::add_impl(&lhs[0], lhs.size(), &rhs, 1);
	return carry != 0;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_ADD_HPP
