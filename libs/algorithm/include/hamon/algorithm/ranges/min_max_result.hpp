/**
 *	@file	min_max_result.hpp
 *
 *	@brief	ranges::min_max_result の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_MIN_MAX_RESULT_HPP
#define HAMON_ALGORITHM_RANGES_MIN_MAX_RESULT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::min_max_result;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

template <typename T>
struct min_max_result
{
	HAMON_NO_UNIQUE_ADDRESS T min;
	HAMON_NO_UNIQUE_ADDRESS T max;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename T2>
	requires hamon::convertible_to<T const&, T2>
#else
	template <typename T2,
		typename = hamon::enable_if_t<
			hamon::convertible_to<T const&, T2>::value
		>
	>
#endif
	HAMON_CXX14_CONSTEXPR operator min_max_result<T2>() const&
	{
		return { min, max };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename T2>
	requires hamon::convertible_to<T, T2>
#else
	template <typename T2,
		typename = hamon::enable_if_t<
			hamon::convertible_to<T, T2>::value
		>
	>
#endif
	HAMON_CXX14_CONSTEXPR operator min_max_result<T2>() &&
	{
		return { std::move(min), std::move(max) };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_MIN_MAX_RESULT_HPP
