/**
 *	@file	pair_like_convertible_from.hpp
 *
 *	@brief	pair_like_convertible_from の定義
 */

#ifndef HAMON_RANGES_VIEWS_DETAIL_PAIR_LIKE_CONVERTIBLE_FROM_HPP
#define HAMON_RANGES_VIEWS_DETAIL_PAIR_LIKE_CONVERTIBLE_FROM_HPP

#include <hamon/ranges/views/detail/convertible_to_non_slicing.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/tuple/concepts/pair_like.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U, typename V>
concept pair_like_convertible_from =
	!hamon::ranges::range<T> &&
	!hamon::is_reference<T>::value &&
	hamon::pair_like<T> &&
	hamon::constructible_from<T, U, V> &&
	ranges::detail::convertible_to_non_slicing<U, hamon::tuple_element_t<0, T>> &&
	hamon::convertible_to<V, hamon::tuple_element_t<1, T>>;

#else

template <typename T, typename U, typename V>
struct pair_like_convertible_from_impl
{
private:
	template <typename T2, typename U2, typename V2,
		typename = hamon::enable_if_t<!ranges::range<T2>::value>,
		typename = hamon::enable_if_t<!hamon::is_reference<T2>::value>,
		typename = hamon::enable_if_t<hamon::pair_like<T2>::value>,
		typename = hamon::enable_if_t<hamon::constructible_from<T2, U2, V2>::value>,
		typename E0 = hamon::tuple_element_t<0, T2>,
		typename = hamon::enable_if_t<ranges::detail::convertible_to_non_slicing<U2, E0>::value>,
		typename E1 = hamon::tuple_element_t<1, T2>,
		typename = hamon::enable_if_t<hamon::convertible_to<V2, E1>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename T2, typename U2, typename V2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U, V>(0));
};

template <typename T, typename U, typename V>
using pair_like_convertible_from = typename pair_like_convertible_from_impl<T, U, V>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_PAIR_LIKE_CONVERTIBLE_FROM_HPP
