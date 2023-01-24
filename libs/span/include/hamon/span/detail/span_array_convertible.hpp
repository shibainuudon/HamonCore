/**
 *	@file	span_array_convertible.hpp
 *
 *	@brief
 */

#ifndef HAMON_SPAN_DETAIL_SPAN_ARRAY_CONVERTIBLE_HPP
#define HAMON_SPAN_DETAIL_SPAN_ARRAY_CONVERTIBLE_HPP

#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
concept span_array_convertible =
	std::is_convertible<From(*)[], To(*)[]>::value;

#else

template <typename From, typename To>
using span_array_convertible =
	std::is_convertible<From(*)[], To(*)[]>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SPAN_DETAIL_SPAN_ARRAY_CONVERTIBLE_HPP
