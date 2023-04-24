/**
 *	@file	pair_like.hpp
 *
 *	@brief	pair_like の定義
 */

#ifndef HAMON_TUPLE_CONCEPTS_PAIR_LIKE_HPP
#define HAMON_TUPLE_CONCEPTS_PAIR_LIKE_HPP

#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>
#include <tuple>

#if defined(HAMON_HAS_CXX20_CONCEPTS)

namespace hamon {

// [tuple.like], concept tuple-like
template <typename T>
concept pair_like =
	hamon::tuple_like<T> && std::tuple_size_v<hamon::remove_cvref_t<T>> == 2;

}	// namespace hamon

#else

#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace detail {

template <typename T>
struct pair_like_impl
{
	template <
		typename U,
		typename = hamon::enable_if_t<hamon::tuple_like<U>::value>,
		typename S = std::tuple_size<hamon::remove_cvref_t<U>>
	>
	static auto test(int) -> hamon::bool_constant<S::value == 2>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

// [tuple.like], concept tuple-like
template <typename T>
using pair_like =
	typename detail::pair_like_impl<T>::type;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {

template <typename T>
using pair_like_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::pair_like<T>>;
#else
	hamon::pair_like<T>;
#endif

}	// namespace hamon

#endif // HAMON_TUPLE_CONCEPTS_PAIR_LIKE_HPP
