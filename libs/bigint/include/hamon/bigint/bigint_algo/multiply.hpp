/**
 *	@file	multiply.hpp
 *
 *	@brief	multiply 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
#define HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP

#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/mul.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

namespace multiply_detail
{

template <typename VectorType, typename T>
inline HAMON_CXX14_CONSTEXPR bool
multiply_impl(VectorType& out, T const* lhs, hamon::size_t n1, T const* rhs, hamon::size_t n2)
{
	detail::zero(out);
	VectorType tmp{0};
	bool overflow = false;
	for (hamon::size_t i = n1; i > 0; --i)
	{
		detail::zero(tmp);
		for (hamon::size_t j = n2; j > 0; --j)
		{
			auto const t = detail::mul(lhs[i-1], rhs[j-1]);
			auto const f1 = bigint_algo::add(tmp, detail::hi(t));
			auto const f2 = bigint_algo::bit_shift_left(tmp, hamon::bitsof<T>());
			tmp[0] = detail::lo(t);
			overflow = overflow || f1 || f2;
		}
		auto const f1 = bigint_algo::bit_shift_left(out, hamon::bitsof<T>());
		auto const f2 = bigint_algo::add(out, tmp);
		overflow = overflow || f1 || f2;
	}
	return overflow;
}

}	// namespace multiply_detail

// 乗算はin-placeに行うことができないので、左辺(lhs)を出力にするパターンは使えない
// 繰り返し乗算を行う場合に、その都度メモリ確保することを避けるため(とくにstd::vector)、出力変数を外から与える
// out と lhs, out と rhs が、同じオブジェクトや同じ領域の場合の動作は未規定

template <typename T>
inline bool
multiply(std::vector<T>& out, std::vector<T> const& lhs, T rhs)
{
	return multiply_detail::multiply_impl(out, lhs.data(), lhs.size(), &rhs, 1);
}

template <typename T>
inline bool
multiply(std::vector<T>& out, std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	return multiply_detail::multiply_impl(out, lhs.data(), lhs.size(), rhs.data(), rhs.size());
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
multiply(hamon::array<T, N>& out, hamon::array<T, N> const& lhs, T rhs)
{
	return multiply_detail::multiply_impl(out, lhs.data(), lhs.size(), &rhs, 1);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
multiply(hamon::array<T, N>& out, hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	return multiply_detail::multiply_impl(out, lhs.data(), lhs.size(), rhs.data(), rhs.size());
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
