/**
 *	@file	unit_test_type_traits_bool_constant.cpp
 *
 *	@brief	bool_constant のテスト
 */

#include <hamon/type_traits/bool_constant.hpp>
#include <gtest/gtest.h>
#include <type_traits>

static_assert(std::is_same<hamon::bool_constant<true>,  hamon::integral_constant<bool, true>>::value, "");
static_assert(std::is_same<hamon::bool_constant<false>, hamon::integral_constant<bool, false>>::value, "");
static_assert(std::is_same<hamon::bool_constant<true>,  hamon::true_type>::value, "");
static_assert(std::is_same<hamon::bool_constant<false>, hamon::false_type>::value, "");

static_assert(std::is_same<hamon::true_type::type,  hamon::bool_constant<true>>::value, "");
static_assert(std::is_same<hamon::false_type::type, hamon::bool_constant<false>>::value, "");

static_assert(std::is_same<hamon::true_type::value_type,  bool>::value, "");
static_assert(std::is_same<hamon::false_type::value_type, bool>::value, "");

static_assert(hamon::true_type::value  == true, "");
static_assert(hamon::false_type::value == false, "");

static_assert(hamon::true_type()  == true, "");
static_assert(hamon::false_type() == false, "");
