/**
 *	@file	unit_test_cstddef_size_t.cpp
 *
 *	@brief	size_t のテスト
 */

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

// size_t は符号なし整数型
static_assert(hamon::is_integral<hamon::size_t>::value, "");
static_assert(hamon::is_unsigned<hamon::size_t>::value, "");

// size_t は sizeof 演算子の結果の型
static_assert(hamon::is_same<hamon::size_t, decltype(sizeof(int))>::value, "");
static_assert(hamon::is_same<hamon::size_t, decltype(sizeof(void*))>::value, "");

// size_t のビット幅は16以上(C++11から)
static_assert((sizeof(hamon::size_t) * CHAR_BIT) >= 16, "");
