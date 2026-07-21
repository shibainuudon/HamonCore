/**
 *	@file	simple_view.hpp
 *
 *	@brief	simple_view の定義
 */

#ifndef HAMON_RANGES_UTILITY_DETAIL_SIMPLE_VIEW_HPP
#define HAMON_RANGES_UTILITY_DETAIL_SIMPLE_VIEW_HPP

#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// 26.5.2 Helper concepts[range.utility.helpers]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename R>
HAMON_CONCEPT_OR_BOOL simple_view =
	hamon::ranges::view<R> &&
	hamon::ranges::range<R const> &&
	hamon::same_as<hamon::ranges::iterator_t<R>, hamon::ranges::iterator_t<R const>> &&
	hamon::same_as<hamon::ranges::sentinel_t<R>, hamon::ranges::sentinel_t<R const>>;

#else

template <typename R, typename = void>
struct simple_view_impl
	: public hamon::false_type
{};

template <typename R>
struct simple_view_impl<R, hamon::enable_if_t<
	hamon::ranges::view<R> &&
	hamon::ranges::range<R const> &&
	hamon::same_as<hamon::ranges::iterator_t<R>, hamon::ranges::iterator_t<R const>> &&
	hamon::same_as<hamon::ranges::sentinel_t<R>, hamon::ranges::sentinel_t<R const>>
>> : public hamon::true_type
{};

template <typename R>
HAMON_CONCEPT_OR_BOOL simple_view = simple_view_impl<R>::value;

#endif

template <typename R>
HAMON_CONCEPT_OR_BOOL not_simple_view = !simple_view<R>;

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_DETAIL_SIMPLE_VIEW_HPP
