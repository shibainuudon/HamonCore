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

template <typename T>
inline int
compare(std::vector<T> const& lhs, std::vector<T> const& rhs)
{
	auto const NA = lhs.size();
	auto const NB = rhs.size();

	if (NA > NB) { return  1; }
	if (NA < NB) { return -1; }

	for (hamon::size_t i = NA; i > 0; --i)
	{
		if (lhs[i - 1] > rhs[i - 1]) { return  1; }
		if (lhs[i - 1] < rhs[i - 1]) { return -1; }
	}

	return 0;
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR int
compare(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	for (hamon::size_t i = N; i > 0; --i)
	{
		if (lhs[i - 1] > rhs[i - 1]) { return  1; }
		if (lhs[i - 1] < rhs[i - 1]) { return -1; }
	}

	return 0;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_COMPARE_HPP
