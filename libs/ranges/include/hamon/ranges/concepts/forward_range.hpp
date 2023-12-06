/**
 *	@file	forward_range.hpp
 *
 *	@brief	forward_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_FORWARD_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_FORWARD_RANGE_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES)
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{
namespace ranges
{

// [range.refinements]/1

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::forward_range;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept forward_range =
	ranges::input_range<T> &&
	hamon::forward_iterator<ranges::iterator_t<T>>;

#else

namespace detail
{

template <typename T>
struct forward_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<ranges::input_range<U>::value>,
		typename = hamon::enable_if_t<hamon::forward_iterator<ranges::iterator_t<U>>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using forward_range =
	typename ranges::detail::forward_range_impl<T>::type;

#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <typename T>
concept not_forward_range = !hamon::ranges::forward_range<T>;
#else
template <typename T>
using not_forward_range = hamon::negation<hamon::ranges::forward_range<T>>;
#endif

template <typename T>
using forward_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::forward_range<T>>;
#else
	hamon::ranges::forward_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_FORWARD_RANGE_HPP
