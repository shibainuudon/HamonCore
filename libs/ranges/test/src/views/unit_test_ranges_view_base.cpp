/**
 *	@file	unit_test_ranges_view_base.cpp
 *
 *	@brief	ranges::view_base のテスト
 */

#include <hamon/ranges/views/view_base.hpp>
#include <hamon/type_traits/is_trivial.hpp>
#include <hamon/type_traits/is_empty.hpp>

static_assert(hamon::is_empty<hamon::ranges::view_base>::value, "");
static_assert(hamon::is_trivial<hamon::ranges::view_base>::value, "");
