/**
 *	@file	tuple_like.hpp
 *
 *	@brief	tuple_like の定義
 */

#ifndef HAMON_TUPLE_CONCEPTS_TUPLE_LIKE_HPP
#define HAMON_TUPLE_CONCEPTS_TUPLE_LIKE_HPP

#include <hamon/concepts/detail/is_specialization_of_array.hpp>
#include <hamon/concepts/detail/is_specialization_of_complex.hpp>
#include <hamon/concepts/detail/is_specialization_of_pair.hpp>
#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/concepts/detail/is_specialization_of_subrange.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [tuple.like], concept tuple-like
template <typename T>
HAMON_CONCEPT_OR_BOOL tuple_like =
	hamon::detail::is_specialization_of_array<hamon::remove_cvref_t<T>>::value ||
	hamon::detail::is_specialization_of_complex<hamon::remove_cvref_t<T>>::value ||
	hamon::detail::is_specialization_of_pair<hamon::remove_cvref_t<T>>::value ||
	hamon::detail::is_specialization_of_tuple<hamon::remove_cvref_t<T>>::value ||
	hamon::detail::is_specialization_of_subrange<hamon::remove_cvref_t<T>>::value;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TUPLE_CONCEPTS_TUPLE_LIKE_HPP
