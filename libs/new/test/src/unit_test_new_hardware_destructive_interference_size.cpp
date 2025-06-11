/**
 *	@file	unit_test_new_hardware_destructive_interference_size.cpp
 *
 *	@brief	hardware_destructive_interference_size のテスト
 */

#include <hamon/new/hardware_destructive_interference_size.hpp>
#include <hamon/cstddef/max_align_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000)
HAMON_WARNING_DISABLE_GCC("-Winterference-size")
#endif

static_assert(hamon::hardware_destructive_interference_size >= alignof(hamon::max_align_t), "");
static_assert(hamon::is_same<decltype(hamon::hardware_destructive_interference_size), hamon::size_t const>::value, "");

HAMON_WARNING_POP()
