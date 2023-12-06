/**
 *	@file	common_range.hpp
 *
 *	@brief	common_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_COMMON_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_COMMON_RANGE_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES)
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{
namespace ranges
{

// [range.refinements]/4

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::common_range;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept common_range =
	ranges::range<T> &&
	hamon::same_as<ranges::iterator_t<T>, ranges::sentinel_t<T>>;

#else

namespace detail
{

template <typename T>
struct common_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			ranges::range<U>::value
		>,
		typename = hamon::enable_if_t<
			hamon::same_as<
				ranges::iterator_t<U>,
				ranges::sentinel_t<U>
			>::value
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using common_range =
	typename ranges::detail::common_range_impl<T>::type;

#endif

template <typename T>
using common_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::common_range<T>>;
#else
	hamon::ranges::common_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_COMMON_RANGE_HPP
