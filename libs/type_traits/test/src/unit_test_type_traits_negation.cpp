/**
 *	@file	unit_test_fnd_type_traits_negation.cpp
 *
 *	@brief	negation のテスト
 */

#include <hamon/type_traits/negation.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>

static_assert(hamon::negation<std::false_type>::value == true, "");
static_assert(hamon::negation<std::true_type>::value  == false, "");
static_assert(hamon::negation<std::is_unsigned<signed   int>>::value == true, "");
static_assert(hamon::negation<std::is_unsigned<unsigned int>>::value == false, "");

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

static_assert(hamon::negation_v<std::false_type> == true, "");
static_assert(hamon::negation_v<std::true_type>  == false, "");

#endif
