﻿/**
 *	@file	span_compatible_range.hpp
 *
 *	@brief
 */

#ifndef HAMON_SPAN_DETAIL_SPAN_COMPATIBLE_RANGE_HPP
#define HAMON_SPAN_DETAIL_SPAN_COMPATIBLE_RANGE_HPP

#include <hamon/span/span_fwd.hpp>
#include <hamon/concepts/detail/is_specialization_of_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_std_span
	: public hamon::false_type {};

template <typename T, hamon::size_t N>
struct is_std_span<hamon::span<T, N>>
	: public hamon::true_type {};

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Range, typename ElementType>
concept span_compatible_range =
	hamon::ranges::contiguous_range<Range> &&
	hamon::ranges::sized_range<Range> &&
	(hamon::ranges::borrowed_range<Range> || hamon::is_const<ElementType>::value) &&
	!detail::is_std_span<hamon::remove_cvref_t<Range>>::value  &&
	!detail::is_specialization_of_array<hamon::remove_cvref_t<Range>>::value &&
	!hamon::is_array<hamon::remove_cvref_t<Range>>::value &&
	hamon::is_convertible<hamon::remove_reference_t<hamon::ranges::range_reference_t<Range>>(*)[], ElementType(*)[]>::value;

#else

template <typename Range, typename ElementType>
using span_compatible_range = hamon::conjunction<
	hamon::ranges::contiguous_range<Range>,
	hamon::ranges::sized_range<Range>,
	hamon::disjunction<hamon::ranges::borrowed_range<Range>, hamon::is_const<ElementType>>,
	hamon::negation<detail::is_std_span<hamon::remove_cvref_t<Range>>>,
	hamon::negation<detail::is_specialization_of_array<hamon::remove_cvref_t<Range>>>,
	hamon::negation<hamon::is_array<hamon::remove_cvref_t<Range>>>,
	hamon::is_convertible<hamon::remove_reference_t<hamon::ranges::range_reference_t<Range>>(*)[], ElementType(*)[]>
>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SPAN_DETAIL_SPAN_COMPATIBLE_RANGE_HPP
