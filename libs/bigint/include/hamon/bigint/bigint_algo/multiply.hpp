/**
 *	@file	multiply.hpp
 *
 *	@brief	multiply 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
#define HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP

#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/detail/mul_addc.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace multiply_detail
{

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

			auto const r = detail::addc(p3[k], T{0}, carry);
			p3[k] = detail::lo(r);
			carry = detail::hi(r);
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

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
multiply(hamon::vector<T>& out, hamon::vector<T> const& lhs, T rhs)
{
	return multiply_detail::multiply_impl(out,
		lhs.data(), lhs.size(),
		&rhs, 1);
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
multiply(hamon::vector<T>& out, hamon::vector<T> const& lhs, hamon::vector<T> const& rhs)
{
	return multiply_detail::multiply_impl(out,
		lhs.data(), lhs.size(),
		rhs.data(), rhs.size());
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
multiply(hamon::inplace_vector<T, N>& out, hamon::inplace_vector<T, N> const& lhs, T rhs)
{
	return multiply_detail::multiply_impl(out,
		lhs.data(), lhs.size(),
		&rhs, 1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
multiply(hamon::inplace_vector<T, N>& out, hamon::inplace_vector<T, N> const& lhs, hamon::inplace_vector<T, N> const& rhs)
{
	return multiply_detail::multiply_impl(out,
		lhs.data(), lhs.size(),
		rhs.data(), rhs.size());
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
multiply(hamon::array<T, N>& out, hamon::array<T, N> const& lhs, T rhs)
{
	return multiply_detail::multiply_impl(out,
		lhs.data(), detail::actual_size(lhs),
		&rhs, 1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
multiply(hamon::array<T, N>& out, hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	return multiply_detail::multiply_impl(out,
		lhs.data(), detail::actual_size(lhs),
		rhs.data(), detail::actual_size(rhs));
}

// 利便性のために、結果を戻り値で返すバージョン(オーバーフローの情報は得られない)
template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::vector<T>
multiply(hamon::vector<T> const& lhs, hamon::vector<T> const& rhs)
{
	hamon::vector<T> result;
	bigint_algo::multiply(result, lhs, rhs);
	return result;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR hamon::array<T, N>
multiply(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	hamon::array<T, N> result{};
	bigint_algo::multiply(result, lhs, rhs);
	return result;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
