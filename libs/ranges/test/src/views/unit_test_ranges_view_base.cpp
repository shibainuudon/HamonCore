﻿/**
 *	@file	unit_test_ranges_view_base.cpp
 *
 *	@brief	ranges::view_base のテスト
 */

#include <hamon/ranges/views/view_base.hpp>
#include <type_traits>

static_assert(std::is_empty<hamon::ranges::view_base>::value, "");
static_assert(std::is_trivial<hamon::ranges::view_base>::value, "");