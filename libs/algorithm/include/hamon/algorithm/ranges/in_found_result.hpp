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
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

template <typename Iter>
struct in_found_result
{
	HAMON_NO_UNIQUE_ADDRESS Iter in;
	bool found;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename Iter2>
	requires hamon::convertible_to<Iter const&, Iter2>
#else
	template <typename Iter2,
		typename = hamon::enable_if_t<
			hamon::convertible_to<Iter const&, Iter2>::value
		>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_found_result<Iter2>() const&
	{
		return { in, found };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename Iter2>
	requires hamon::convertible_to<Iter, Iter2>
#else
	template <typename Iter2,
		typename = hamon::enable_if_t<
			hamon::convertible_to<Iter, Iter2>::value
		>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_found_result<Iter2>()&&
	{
		return { std::move(in), found };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_FOUND_RESULT_HPP
