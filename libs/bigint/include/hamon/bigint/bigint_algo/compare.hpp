/**
 *	@file	compare.hpp
 *
 *	@brief	compare 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_COMPARE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_COMPARE_HPP

#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

namespace compare_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR int
compare_impl(T const* lhs, T const* rhs, hamon::size_t n)
{
	for (hamon::size_t i = n; i > 0; --i)
	{
		if (lhs[i - 1] > rhs[i - 1]) { return  1; }
		if (lhs[i - 1] < rhs[i - 1]) { return -1; }
	}

	return 0;
}

}	// namespace compare_detail

template <typename T>
inline int
compare(std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	auto const NA = lhs.size();
	auto const NB = rhs.size();

	if (NA > NB) { return  1; }
	if (NA < NB) { return -1; }

	return compare_detail::compare_impl(lhs.data(), rhs.data(), NA);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR int
compare(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	return compare_detail::compare_impl(lhs.data(), rhs.data(), N);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_COMPARE_HPP
