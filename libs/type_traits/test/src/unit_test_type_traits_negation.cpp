/**
 *	@file	unit_test_type_traits_negation.cpp
 *
 *	@brief	negation のテスト
 */

#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

static_assert(hamon::negation<hamon::false_type>::value == true, "");
static_assert(hamon::negation<hamon::true_type>::value  == false, "");
static_assert(hamon::negation<hamon::is_unsigned<signed   int>>::value == true, "");
static_assert(hamon::negation<hamon::is_unsigned<unsigned int>>::value == false, "");

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

static_assert(hamon::negation_v<hamon::false_type> == true, "");
static_assert(hamon::negation_v<hamon::true_type>  == false, "");

#endif
