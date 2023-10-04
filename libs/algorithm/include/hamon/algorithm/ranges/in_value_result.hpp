/**
 *	@file	in_value_result.hpp
 *
 *	@brief	ranges::in_value_result の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_IN_VALUE_RESULT_HPP
#define HAMON_ALGORITHM_RANGES_IN_VALUE_RESULT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_fold) && (__cpp_lib_ranges_fold >= 202207L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::in_value_result;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

template <typename I, typename T>
struct in_value_result
{
	HAMON_NO_UNIQUE_ADDRESS I in;
	HAMON_NO_UNIQUE_ADDRESS T value;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename I2, typename T2>
	requires
		hamon::convertible_to<I const&, I2> &&
		hamon::convertible_to<T const&, T2>
#else
	template <typename I2, typename T2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I const&, I2>,
			hamon::convertible_to<T const&, T2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR operator in_value_result<I2, T2>() const&
	{
		return { in, value };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename I2, typename T2>
	requires
		hamon::convertible_to<I, I2> &&
		hamon::convertible_to<T, T2>
#else
	template <typename I2, typename T2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I, I2>,
			hamon::convertible_to<T, T2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR operator in_value_result<I2, T2>() &&
	{
		return { hamon::move(in), hamon::move(value) };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_VALUE_RESULT_HPP
