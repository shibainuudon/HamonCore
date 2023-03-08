/**
 *	@file	unit_test_cstddef_ptrdiff_t.cpp
 *
 *	@brief	ptrdiff_t のテスト
 */

#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

// ptrdiff_t は符号付き整数型
static_assert(hamon::is_integral<hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_signed<hamon::ptrdiff_t>::value, "");

// ptrdiff_t は2 つのポインタの減算の結果を示す型
static_assert(hamon::is_same<hamon::ptrdiff_t, decltype(hamon::declval<int*>() - hamon::declval<int*>())>::value, "");
static_assert(hamon::is_same<hamon::ptrdiff_t, decltype(hamon::declval<char*>() - hamon::declval<char*>())>::value, "");

// ptrdiff_t のビット幅は17以上(C++11から)
static_assert((sizeof(hamon::ptrdiff_t) * CHAR_BIT) >= 17, "");
