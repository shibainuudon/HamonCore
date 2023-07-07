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
namespace detail
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

#if defined(HAMON_HAS_CXX14_CONSTEXPR)

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

#else

template <hamon::size_t I>
struct compare_impl
{
	template <typename T, hamon::size_t N>
	static HAMON_CXX11_CONSTEXPR int
	invoke(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
	{
		return
			lhs[I - 1] > rhs[I - 1] ?  1 :
			lhs[I - 1] < rhs[I - 1] ? -1 :
			compare_impl<I - 1>::invoke(lhs, rhs);
	}
};

template <>
struct compare_impl<0>
{
	template <typename T, hamon::size_t N>
	static HAMON_CXX11_CONSTEXPR int
	invoke(hamon::array<T, N> const&, hamon::array<T, N> const&)
	{
		return 0;
	}
};

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR int
compare(hamon::array<T, N> const& lhs, hamon::array<T, N> const& rhs)
{
	return compare_impl<N>::invoke(lhs, rhs);
}

#endif

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_COMPARE_HPP
