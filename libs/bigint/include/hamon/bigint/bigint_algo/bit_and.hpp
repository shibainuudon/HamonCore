/**
 *	@file	bit_and.hpp
 *
 *	@brief	bit_and 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/detail/vector_value_t.hpp>
#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace bit_and_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
bit_and_impl(T* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	hamon::size_t i = 0;
	for (; i < n2; ++i)
	{
		p1[i] = static_cast<T>(p1[i] & p2[i]);
	}
	for (; i < n1; ++i)
	{
		p1[i] = T{0};
	}
}

}	// namespace bit_and_detail

template <typename VectorType1, typename VectorType2,
	typename T1 = detail::vector_value_t<VectorType1>,
	typename T2 = detail::vector_value_t<VectorType2>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_same<T1, T2>
	>::value>
>
inline HAMON_CXX14_CONSTEXPR void
bit_and(VectorType1& lhs, VectorType2 const& rhs)
{
	auto const n = hamon::min(detail::actual_size(lhs), detail::actual_size(rhs));
	detail::resize(lhs, n);
	bit_and_detail::bit_and_impl(lhs.data(), lhs.size(), rhs.data(), n);
	bigint_algo::normalize(lhs);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_AND_HPP
