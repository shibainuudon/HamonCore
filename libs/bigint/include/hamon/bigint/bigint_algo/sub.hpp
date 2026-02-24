/**
 *	@file	sub.hpp
 *
 *	@brief	sub 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_SUB_HPP
#define HAMON_BIGINT_BIGINT_ALGO_SUB_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/subc.hpp>
#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace sub_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
sub_impl(T* dst, T const* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	T carry = 0;
	hamon::size_t i = 0;
	for (; i < n2; ++i)
	{
		auto const x = detail::subc(p1[i], p2[i], carry);
		dst[i] = detail::lo(x);
		carry  = detail::hi(x);
	}
	for (; carry != 0 && i < n1; ++i)
	{
		auto const x = detail::subc(p1[i], T{0}, carry);
		dst[i] = detail::lo(x);
		carry  = detail::hi(x);
	}
	for (; i < n1; ++i)
	{
		dst[i] = p1[i];
	}
}

}	// namespace sub_detail

// lhs - rhs を計算する
// 
// bigint_algo は unsigned な世界であるため、lhs >= rhs になっていなければならない。
// そのため、オーバーフローも起こらない。
// lhs < rhs を与えたときの挙動は未規定。

template <typename VectorType1, typename VectorType2>
inline HAMON_CXX14_CONSTEXPR void
sub(VectorType1& lhs, VectorType2 const& rhs)
{
	sub_detail::sub_impl(
		lhs.data(),
		lhs.data(), lhs.size(),
		rhs.data(), detail::actual_size(rhs));
	bigint_algo::normalize(lhs);
}

template <typename VectorType1, typename VectorType2, typename VectorType3>
inline HAMON_CXX14_CONSTEXPR void
sub(VectorType1& out, VectorType2 const& lhs, VectorType3 const& rhs)
{
	detail::zero(out);
	detail::resize(out, lhs.size());
	sub_detail::sub_impl(
		out.data(),
		lhs.data(), lhs.size(),
		rhs.data(), detail::actual_size(rhs));
	bigint_algo::normalize(out);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_SUB_HPP
