/**
 *	@file	tuple_like.hpp
 *
 *	@brief	tuple_like の定義
 */

#ifndef HAMON_TUPLE_CONCEPTS_TUPLE_LIKE_HPP
#define HAMON_TUPLE_CONCEPTS_TUPLE_LIKE_HPP

#include <hamon/concepts/detail/is_specialization_of_array.hpp>
#include <hamon/concepts/detail/is_specialization_of_pair.hpp>
#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/concepts/detail/is_specialization_of_subrange.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)

namespace hamon {

// [tuple.like], concept tuple-like
template <typename T>
concept tuple_like =
	hamon::detail::is_specialization_of_array<hamon::remove_cvref_t<T>>::value ||
	hamon::detail::is_specialization_of_pair<hamon::remove_cvref_t<T>>::value ||
	hamon::detail::is_specialization_of_tuple<hamon::remove_cvref_t<T>>::value ||
	hamon::detail::is_specialization_of_subrange<hamon::remove_cvref_t<T>>::value;

}	// namespace hamon

#else

#include <hamon/type_traits/disjunction.hpp>

namespace hamon {

// [tuple.like], concept tuple-like
template <typename T>
using tuple_like = hamon::disjunction<
	hamon::detail::is_specialization_of_array<hamon::remove_cvref_t<T>>,
	hamon::detail::is_specialization_of_pair<hamon::remove_cvref_t<T>>,
	hamon::detail::is_specialization_of_tuple<hamon::remove_cvref_t<T>>,
	hamon::detail::is_specialization_of_subrange<hamon::remove_cvref_t<T>>
>;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {

template <typename T>
using tuple_like_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::tuple_like<T>>;
#else
	hamon::tuple_like<T>;
#endif

}	// namespace hamon

#endif // HAMON_TUPLE_CONCEPTS_TUPLE_LIKE_HPP
