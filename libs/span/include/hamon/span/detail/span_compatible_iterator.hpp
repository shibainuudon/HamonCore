/**
 *	@file	span_compatible_iterator.hpp
 *
 *	@brief
 */

#ifndef HAMON_SPAN_DETAIL_SPAN_COMPATIBLE_ITERATOR_HPP
#define HAMON_SPAN_DETAIL_SPAN_COMPATIBLE_ITERATOR_HPP

#include <hamon/span/detail/span_array_convertible.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename It, typename T>
concept span_compatible_iterator =
	hamon::contiguous_iterator<It> &&
	detail::span_array_convertible<hamon::remove_reference_t<hamon::iter_reference_t<It>>, T>;

#else

template <typename It, typename T>
using span_compatible_iterator = hamon::conjunction<
	hamon::contiguous_iterator<It>,
	detail::span_array_convertible<hamon::remove_reference_t<hamon::iter_reference_t<It>>, T>
>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SPAN_DETAIL_SPAN_COMPATIBLE_ITERATOR_HPP
