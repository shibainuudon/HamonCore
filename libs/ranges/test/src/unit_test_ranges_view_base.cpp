/**
 *	@file	unit_test_ranges_view_base.cpp
 *
 *	@brief	ranges::view_base のテスト
 */

#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <hamon/type_traits/is_empty.hpp>

static_assert(hamon::is_empty<hamon::ranges::view_base>::value, "");
static_assert(hamon::is_trivially_default_constructible<hamon::ranges::view_base>::value, "");
static_assert(hamon::is_trivially_copyable<hamon::ranges::view_base>::value, "");
static_assert(hamon::is_trivially_copy_assignable<hamon::ranges::view_base>::value, "");
