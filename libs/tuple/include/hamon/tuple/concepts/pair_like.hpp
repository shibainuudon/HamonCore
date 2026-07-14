/**
 *	@file	pair_like.hpp
 *
 *	@brief	pair_like の定義
 */

#ifndef HAMON_TUPLE_CONCEPTS_PAIR_LIKE_HPP
#define HAMON_TUPLE_CONCEPTS_PAIR_LIKE_HPP

#include <hamon/tuple/tuple_size.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>

// [tuple.like], concept tuple-like

namespace hamon {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL pair_like =
	hamon::detail::tuple_like<T> &&
	hamon::tuple_size_v<hamon::remove_cvref_t<T>> == 2;

#else

template <typename T>
struct pair_like_impl
{
	template <
		typename U,
		typename = hamon::enable_if_t<hamon::detail::tuple_like<U>>,
		typename S = hamon::tuple_size<hamon::remove_cvref_t<U>>
	>
	static auto test(int) -> hamon::bool_constant<S::value == 2>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL pair_like =
	detail::pair_like_impl<T>::type::value;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TUPLE_CONCEPTS_PAIR_LIKE_HPP
