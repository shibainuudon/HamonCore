/**
 *	@file	unit_test_flat_multimap_sorted_equivalent.cpp
 *
 *	@brief	sorted_equivalent のテスト
 */

#include <hamon/flat_map/sorted_equivalent.hpp>
#include <hamon/type_traits.hpp>

static_assert( hamon::is_default_constructible<hamon::sorted_equivalent_t>::value, "");
static_assert( hamon::is_trivially_default_constructible<hamon::sorted_equivalent_t>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::sorted_equivalent_t>::value, "");
static_assert( hamon::is_same<decltype(hamon::sorted_equivalent), hamon::sorted_equivalent_t const>::value, "");
