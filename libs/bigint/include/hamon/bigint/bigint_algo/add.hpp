/**
 *	@file	add.hpp
 *
 *	@brief	add 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_ADD_HPP
#define HAMON_BIGINT_BIGINT_ALGO_ADD_HPP

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
namespace detail
{
namespace bigint_algo
{

// bigint_algo全体的な取り決め
// * vector<T> または array<T, N> を対象
// * T は 符号なし整数型
// * 数値の格納の仕方はリトルエンディアン。つまり下位の桁を前方に格納する。
// * arrayを引数にとるものはC++11でconstexpr
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

inline HAMON_CXX11_CONSTEXPR hamon::uint16_t
addc(hamon::uint8_t lhs, hamon::uint8_t rhs, hamon::uint8_t carry)
{
	return static_cast<hamon::uint16_t>(
		static_cast<hamon::uint16_t>(lhs) +
		static_cast<hamon::uint16_t>(rhs) +
		static_cast<hamon::uint16_t>(carry));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t
addc(hamon::uint16_t lhs, hamon::uint16_t rhs, hamon::uint16_t carry)
{
	return static_cast<hamon::uint32_t>(
		static_cast<hamon::uint32_t>(lhs) +
		static_cast<hamon::uint32_t>(rhs) +
		static_cast<hamon::uint32_t>(carry));
}

inline HAMON_CXX11_CONSTEXPR hamon::uint64_t
addc(hamon::uint32_t lhs, hamon::uint32_t rhs, hamon::uint32_t carry)
{
	return static_cast<hamon::uint64_t>(
		static_cast<hamon::uint64_t>(lhs) +
		static_cast<hamon::uint64_t>(rhs) +
		static_cast<hamon::uint64_t>(carry));
}

#if defined(__SIZEOF_INT128__)
inline HAMON_CXX11_CONSTEXPR __uint128_t
addc(hamon::uint64_t lhs, hamon::uint64_t rhs, hamon::uint64_t carry)
{
	return static_cast<__uint128_t>(
		static_cast<__uint128_t>(lhs) +
		static_cast<__uint128_t>(rhs) +
		static_cast<__uint128_t>(carry));
}
#endif

// 上記以外の汎用的な実装(主に__uint128_tが使えない環境向け)
template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, 2>
addc(T lhs, T rhs, T carry)
{
	T const a = static_cast<T>(rhs + carry);
	T const b = static_cast<T>(lhs + a);
	T const c1 = a < rhs ? 1 : 0;
	T const c2 = b < lhs ? 1 : 0;
	return {b, static_cast<T>(c1 + c2)};
}

template <typename T>
inline std::vector<T>
add(std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	auto const N = hamon::max(lhs.size(), rhs.size());
	std::vector<T> result(N);
	T carry = 0;
	for (hamon::size_t i = 0; i < N; ++i)
	{
		auto const x = bigint_algo::addc(
			bigint_algo::get(lhs, i),
			bigint_algo::get(rhs, i),
			carry);
		result[i] = bigint_algo::lo(x);
		carry     = bigint_algo::hi(x);
	}

	if (carry != 0)
	{
		result.push_back(carry);
	}

	return result;
}

#if defined(HAMON_HAS_CXX14_CONSTEXPR)

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, N>
add(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	hamon::array<T, N> result{};
	T carry = 0;
	for (hamon::size_t i = 0; i < N; ++i)
	{
		auto const x = bigint_algo::addc(lhs[i], rhs[i], carry);
		result[i] = bigint_algo::lo(x);
		carry     = bigint_algo::hi(x);
	}
	return result;
}

#else

template <typename T, hamon::size_t N, hamon::size_t I>
struct add_impl
{
private:
	template <typename U, hamon::size_t... Js>
	static HAMON_CXX11_CONSTEXPR hamon::array<T, N>
	invoke_impl(
		hamon::array<T, N> const& lhs,
		hamon::array<T, N> const& rhs,
		hamon::array<T, N> const& result,
		U x,
		hamon::index_sequence<Js...>)
	{
		return add_impl<T, N, I + 1>::invoke(
			lhs,
			rhs,
			hamon::array<T, N>{result[Js]..., bigint_algo::lo(x)},
			bigint_algo::hi(x));
	}

public:
	static HAMON_CXX11_CONSTEXPR hamon::array<T, N>
	invoke(
		hamon::array<T, N> const& lhs,
		hamon::array<T, N> const& rhs,
		hamon::array<T, N> const& result,
		T carry)
	{
		return invoke_impl(
			lhs,
			rhs,
			result,
			bigint_algo::addc(lhs[I], rhs[I], carry),
			hamon::make_index_sequence<I>{});
	}
};

template <typename T, hamon::size_t N>
struct add_impl<T, N, N>
{
	static HAMON_CXX11_CONSTEXPR hamon::array<T, N>
	invoke(
		hamon::array<T, N> const&,
		hamon::array<T, N> const&,
		hamon::array<T, N> const& result,
		T)
	{
		return result;
	}
};

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR hamon::array<T, N>
add(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	return add_impl<T, N, 0>::invoke(lhs, rhs, hamon::array<T, N>{}, T{});
}

#endif

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_ADD_HPP
