/**
 *	@file	maybe_borrowed_range.hpp
 *
 *	@brief	maybe_borrowed_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_DETAIL_MAYBE_BORROWED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_DETAIL_MAYBE_BORROWED_RANGE_HPP

#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept maybe_borrowed_range =
	std::is_lvalue_reference<T>::value ||
	HAMON_RANGES_ENABLE_BORROWED_RANGE(hamon::remove_cvref_t<T>);

#else

template <typename T>
using maybe_borrowed_range =
	hamon::bool_constant<
		std::is_lvalue_reference<T>::value ||
		HAMON_RANGES_ENABLE_BORROWED_RANGE(hamon::remove_cvref_t<T>)
	>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_DETAIL_MAYBE_BORROWED_RANGE_HPP
