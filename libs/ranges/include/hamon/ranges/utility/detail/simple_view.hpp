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
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// 26.5.2 Helper concepts[range.utility.helpers]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename R>
concept simple_view =
	hamon::ranges::view<R> &&
	hamon::ranges::range<R const> &&
	hamon::same_as<hamon::ranges::iterator_t<R>, hamon::ranges::iterator_t<R const>> &&
	hamon::same_as<hamon::ranges::sentinel_t<R>, hamon::ranges::sentinel_t<R const>>;

template <typename R>
using simple_view_t = hamon::bool_constant<simple_view<R>>;

template <typename R>
concept not_simple_view = !simple_view<R>;

#else

template <typename R>
struct simple_view_impl
{
private:
	template <typename R2,
		typename = hamon::enable_if_t<hamon::ranges::view<R2>::value>,
		typename = hamon::enable_if_t<hamon::ranges::range<R2 const>::value>,
		typename = hamon::enable_if_t<hamon::same_as<hamon::ranges::iterator_t<R2>, hamon::ranges::iterator_t<R2 const>>::value>,
		typename = hamon::enable_if_t<hamon::same_as<hamon::ranges::sentinel_t<R2>, hamon::ranges::sentinel_t<R2 const>>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename R2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<R>(0));
};

template <typename R>
using simple_view =
	typename simple_view_impl<R>::type;

template <typename R>
using simple_view_t = simple_view<R>;

template <typename R>
using not_simple_view = hamon::negation<simple_view<R>>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_DETAIL_SIMPLE_VIEW_HPP
