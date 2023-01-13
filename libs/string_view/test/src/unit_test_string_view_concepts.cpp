/**
 *	@file	unit_test_string_view_concepts.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
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
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

TYPED_TEST(StringViewTest, ConceptsTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;

	static_assert( hamon::same_as_t<hamon::ranges::iterator_t<string_view>, typename string_view::iterator>::value, "");
	static_assert( hamon::ranges::common_range_t<string_view>::value, "");
	static_assert( hamon::ranges::random_access_range_t<string_view>::value, "");
	static_assert( hamon::ranges::contiguous_range_t<string_view>::value, "");
	static_assert( hamon::ranges::view_t<string_view>::value, "");
	static_assert( HAMON_RANGES_ENABLE_VIEW(string_view), "");
	static_assert( hamon::ranges::sized_range_t<string_view>::value, "");
	static_assert( hamon::ranges::borrowed_range_t<string_view>::value, "");
	static_assert( hamon::ranges::viewable_range_t<string_view>::value, "");

	static_assert( hamon::same_as_t<hamon::ranges::iterator_t<string_view const>, typename string_view::const_iterator>::value, "");
	static_assert( hamon::ranges::common_range_t<string_view const>::value, "");
	static_assert( hamon::ranges::random_access_range_t<string_view const>::value, "");
	static_assert( hamon::ranges::contiguous_range_t<string_view const>::value, "");
	static_assert(!hamon::ranges::view_t<string_view const>::value, "");
	static_assert(!HAMON_RANGES_ENABLE_VIEW(string_view const), "");
	static_assert( hamon::ranges::sized_range_t<string_view const>::value, "");
	static_assert( hamon::ranges::borrowed_range_t<string_view const>::value, "");
	static_assert( hamon::ranges::viewable_range_t<string_view const>::value, "");
}

}	// namespace string_view_test
}	// namespace hamon_test
