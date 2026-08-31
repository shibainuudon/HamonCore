/**
 *	@file	forward_range.hpp
 *
 *	@brief	forward_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_FORWARD_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_FORWARD_RANGE_HPP

#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

// [range.refinements]/1

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL forward_range =
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
		typename = hamon::enable_if_t<ranges::input_range<U>>,
		typename = hamon::enable_if_t<hamon::forward_iterator<ranges::iterator_t<U>>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
HAMON_CONCEPT_OR_BOOL forward_range =
	ranges::detail::forward_range_impl<T>::type::value;

#endif

template <typename T>
HAMON_CONCEPT_OR_BOOL not_forward_range = !hamon::ranges::forward_range<T>;

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_FORWARD_RANGE_HPP
