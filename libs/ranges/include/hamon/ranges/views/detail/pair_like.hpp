/**
 *	@file	pair_like.hpp
 *
 *	@brief	pair_like の定義
 */

#ifndef HAMON_RANGES_VIEWS_DETAIL_PAIR_LIKE_HPP
#define HAMON_RANGES_VIEWS_DETAIL_PAIR_LIKE_HPP

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_const.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept pair_like =
	!hamon::is_reference<T>::value &&
	requires(T t)
	{
		typename std::tuple_size<T>::type;
		requires hamon::derived_from<std::tuple_size<T>, std::integral_constant<std::size_t, 2>>;
		typename hamon::tuple_element_t<0, hamon::remove_const_t<T>>;
		typename hamon::tuple_element_t<1, hamon::remove_const_t<T>>;
		{ get<0>(t) } -> hamon::convertible_to<hamon::tuple_element_t<0, T> const&>;
		{ get<1>(t) } -> hamon::convertible_to<hamon::tuple_element_t<1, T> const&>;
	};

#else

template <std::size_t> void get(void) = delete;

template <typename T>
struct pair_like_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<!hamon::is_reference<U>::value>,
		typename = typename std::tuple_size<U>::type,
		typename = hamon::enable_if_t<
			hamon::derived_from<std::tuple_size<U>, std::integral_constant<std::size_t, 2>>::value
		>,
		typename = hamon::tuple_element_t<0, hamon::remove_const_t<U>>,
		typename = hamon::tuple_element_t<1, hamon::remove_const_t<U>>,
		typename E0 = decltype(get<0>(std::declval<U>())),
		typename E1 = decltype(get<1>(std::declval<U>())),
		typename = hamon::enable_if_t<
			hamon::convertible_to<E0, hamon::tuple_element_t<0, U> const&>::value
		>,
		typename = hamon::enable_if_t<
			hamon::convertible_to<E1, hamon::tuple_element_t<1, U> const&>::value
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using pair_like = typename pair_like_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_PAIR_LIKE_HPP
