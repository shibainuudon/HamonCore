/**
 *	@file	unit_test_span_concepts.cpp
 *
 *	@brief
 */

#include <hamon/span.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/enable_view.hpp>
#include <hamon/ranges/iterator_t.hpp>

namespace hamon_span_test
{

namespace concepts_test
{

using range = hamon::span<int>;

static_assert( hamon::same_as<hamon::ranges::iterator_t<range>, range::iterator>, "");
static_assert( hamon::ranges::common_range<range>, "");
static_assert( hamon::ranges::random_access_range<range>, "");
static_assert( hamon::ranges::contiguous_range<range>, "");
static_assert( hamon::ranges::view<range>, "");
static_assert( hamon::ranges::enable_view<range>, "");
static_assert( hamon::ranges::sized_range<range>, "");
static_assert( hamon::ranges::borrowed_range<range>, "");
static_assert( hamon::ranges::viewable_range<range>, "");

static_assert( hamon::same_as<hamon::ranges::iterator_t<range const>, range::iterator>, "");
static_assert( hamon::ranges::common_range<range const>, "");
static_assert( hamon::ranges::random_access_range<range const>, "");
static_assert( hamon::ranges::contiguous_range<range const>, "");
static_assert(!hamon::ranges::view<range const>, "");
static_assert(!hamon::ranges::enable_view<range const>, "");
static_assert( hamon::ranges::sized_range<range const>, "");
static_assert( hamon::ranges::borrowed_range<range const>, "");
static_assert( hamon::ranges::viewable_range<range const>, "");

}	// namespace concepts_test

}	// namespace hamon_span_test
