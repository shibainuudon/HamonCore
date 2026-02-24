/**
 *	@file	compare.hpp
 *
 *	@brief	compare 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_COMPARE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_COMPARE_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace compare_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR int
compare_impl(T const* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	if (n1 > n2) { return  1; }
	if (n1 < n2) { return -1; }

	for (hamon::size_t i = n1; i > 0; --i)
	{
		if (p1[i - 1] > p2[i - 1]) { return  1; }
		if (p1[i - 1] < p2[i - 1]) { return -1; }
	}

	return 0;
}

}	// namespace compare_detail

template <typename VectorType1, typename VectorType2>
inline HAMON_CXX14_CONSTEXPR int
compare(VectorType1 const& lhs, VectorType2 const& rhs)
{
	return compare_detail::compare_impl(
		lhs.data(), detail::actual_size(lhs),
		rhs.data(), detail::actual_size(rhs));
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_COMPARE_HPP
