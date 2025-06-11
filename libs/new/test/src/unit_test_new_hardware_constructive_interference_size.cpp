/**
 *	@file	unit_test_new_hardware_constructive_interference_size.cpp
 *
 *	@brief	hardware_constructive_interference_size のテスト
 */

#include <hamon/new/hardware_constructive_interference_size.hpp>
#include <hamon/cstddef/max_align_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>

static_assert(hamon::hardware_constructive_interference_size >= alignof(hamon::max_align_t), "");
static_assert(hamon::is_same<decltype(hamon::hardware_constructive_interference_size), hamon::size_t const>::value, "");
