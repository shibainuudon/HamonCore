/**
 *	@file	sub.hpp
 *
 *	@brief	sub 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_SUB_HPP
#define HAMON_BIGINT_BIGINT_ALGO_SUB_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/detail/subc.hpp>
#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/bigint/bigint_algo/detail/vector_value_t.hpp>
#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace sub_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
sub_impl(T* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	T carry = 0;
	hamon::size_t i = 0;
	for (; i < n2; ++i)
	{
		p1[i] = detail::subc(p1[i], p2[i], &carry);
	}
	for (; carry != 0 && i < n1; ++i)
	{
		p1[i] = detail::subc(p1[i], T{0}, &carry);
	}
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
sub_impl(T* dst, T const* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	T carry = 0;
	hamon::size_t i = 0;
	for (; i < n2; ++i)
	{
		dst[i] = detail::subc(p1[i], p2[i], &carry);
	}
	for (; carry != 0 && i < n1; ++i)
	{
		dst[i] = detail::subc(p1[i], T{0}, &carry);
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

template <typename VectorType1, typename VectorType2,
	typename T1 = detail::vector_value_t<VectorType1>,
	typename T2 = detail::vector_value_t<VectorType2>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_same<T1, T2>
	>::value>
>
inline HAMON_CXX14_CONSTEXPR void
sub(VectorType1& lhs, VectorType2 const& rhs)
{
	sub_detail::sub_impl(
		lhs.data(), lhs.size(),
		rhs.data(), detail::actual_size(rhs));
	bigint_algo::normalize(lhs);
}

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
