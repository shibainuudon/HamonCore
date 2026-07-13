/**
 *	@file	maybe_borrowed_range.hpp
 *
 *	@brief	maybe_borrowed_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_DETAIL_MAYBE_BORROWED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_DETAIL_MAYBE_BORROWED_RANGE_HPP

#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

template <typename T>
HAMON_CONCEPT_OR_BOOL maybe_borrowed_range =
	hamon::is_lvalue_reference<T>::value ||
	hamon::ranges::enable_borrowed_range<hamon::remove_cvref_t<T>>;

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_DETAIL_MAYBE_BORROWED_RANGE_HPP
