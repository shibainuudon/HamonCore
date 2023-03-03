/**
 *	@file	unit_test_type_traits_conditional.cpp
 *
 *	@brief	conditional のテスト
 */

#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>

static_assert(hamon::is_same<int,  hamon::conditional<true,  int, char>::type>::value, "");
static_assert(hamon::is_same<char, hamon::conditional<false, int, char>::type>::value, "");

static_assert(hamon::is_same<double, hamon::conditional_t<true,  double, int>>::value, "");
static_assert(hamon::is_same<int,    hamon::conditional_t<false, double, int>>::value, "");
