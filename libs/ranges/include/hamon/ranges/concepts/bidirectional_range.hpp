/**
 *	@file	bidirectional_range.hpp
 *
 *	@brief	bidirectional_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_BIDIRECTIONAL_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_BIDIRECTIONAL_RANGE_HPP

#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
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
HAMON_CONCEPT_OR_BOOL bidirectional_range =
	ranges::forward_range<T> &&
	hamon::bidirectional_iterator<ranges::iterator_t<T>>;

#else

namespace detail
{

template <typename T>
struct bidirectional_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			ranges::forward_range<U>
		>,
		typename = hamon::enable_if_t<
			hamon::bidirectional_iterator<ranges::iterator_t<U>>
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
HAMON_CONCEPT_OR_BOOL bidirectional_range =
	ranges::detail::bidirectional_range_impl<T>::type::value;

#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_BIDIRECTIONAL_RANGE_HPP
