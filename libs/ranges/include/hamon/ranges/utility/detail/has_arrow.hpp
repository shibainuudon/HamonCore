/**
 *	@file	has_arrow.hpp
 *
 *	@brief	has_arrow の定義
 */

#ifndef HAMON_RANGES_UTILITY_DETAIL_HAS_ARROW_HPP
#define HAMON_RANGES_UTILITY_DETAIL_HAS_ARROW_HPP

#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// 26.5.2 Helper concepts[range.utility.helpers]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename I>
concept has_arrow =
	hamon::input_iterator<I> &&
	(hamon::is_pointer_v<I> || requires(I i) { i.operator->(); });

template <typename I>
using has_arrow_t = hamon::bool_constant<has_arrow<I>>;

#else

template <typename I, typename = void>
struct has_arrow_impl
	: public hamon::false_type {};

template <typename I>
struct has_arrow_impl<I, hamon::void_t<decltype(hamon::declval<I&>().operator->())>>
	: public hamon::true_type {};

template <typename I>
using has_arrow = hamon::conjunction<
	hamon::input_iterator<I>,
	hamon::disjunction<
		hamon::is_pointer<I>,
		has_arrow_impl<I>
	>
>;

template <typename I>
using has_arrow_t = has_arrow<I>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_DETAIL_HAS_ARROW_HPP
