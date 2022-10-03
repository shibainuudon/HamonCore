﻿/**
 *	@file	random_access_range.hpp
 *
 *	@brief	random_access_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_RANDOM_ACCESS_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_RANDOM_ACCESS_RANGE_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon
{
namespace ranges
{

using std::ranges::random_access_range;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{
namespace ranges
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept random_access_range =
	ranges::bidirectional_range<T> &&
	hamon::random_access_iterator<ranges::iterator_t<T>>;

#else

namespace detail
{

template <typename T>
struct random_access_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<ranges::bidirectional_range<U>::value>,
		typename = hamon::enable_if_t<hamon::random_access_iterator<ranges::iterator_t<U>>::value>
	>
	static auto test(int) -> std::true_type;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using random_access_range =
	typename ranges::detail::random_access_range_impl<T>::type;

#endif

}	// namespace ranges
}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{
namespace ranges
{

template <typename T>
using random_access_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::random_access_range<T>>;
#else
	hamon::ranges::random_access_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_RANDOM_ACCESS_RANGE_HPP
