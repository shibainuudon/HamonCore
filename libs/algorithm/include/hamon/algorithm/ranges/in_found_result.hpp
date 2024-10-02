/**
 *	@file	in_found_result.hpp
 *
 *	@brief	ranges::in_found_result の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_IN_FOUND_RESULT_HPP
#define HAMON_ALGORITHM_RANGES_IN_FOUND_RESULT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::in_found_result;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.5 Algorithm result types[algorithms.results]

template <typename I>
struct in_found_result
{
	HAMON_NO_UNIQUE_ADDRESS I in;
	bool found;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename I2>
	requires hamon::convertible_to<I const&, I2>
#else
	template <typename I2,
		typename = hamon::enable_if_t<
			hamon::convertible_to<I const&, I2>::value
		>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_found_result<I2>() const&
	{
		return { in, found };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename I2>
	requires hamon::convertible_to<I, I2>
#else
	template <typename I2,
		typename = hamon::enable_if_t<
			hamon::convertible_to<I, I2>::value
		>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_found_result<I2>()&&
	{
		return { hamon::move(in), found };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_FOUND_RESULT_HPP
