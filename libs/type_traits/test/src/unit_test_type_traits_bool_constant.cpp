/**
 *	@file	unit_test_type_traits_bool_constant.cpp
 *
 *	@brief	bool_constant のテスト
 */

#include <hamon/type_traits/bool_constant.hpp>
#include <gtest/gtest.h>
#include <type_traits>

static_assert(std::is_same<hamon::bool_constant<true>,  std::integral_constant<bool, true>>::value, "");
static_assert(std::is_same<hamon::bool_constant<false>, std::integral_constant<bool, false>>::value, "");
static_assert(std::is_same<hamon::bool_constant<true>,  std::true_type>::value, "");
static_assert(std::is_same<hamon::bool_constant<false>, std::false_type>::value, "");

static_assert(std::is_same<std::true_type::type,  hamon::bool_constant<true>>::value, "");
static_assert(std::is_same<std::false_type::type, hamon::bool_constant<false>>::value, "");

static_assert(std::is_same<std::true_type::value_type,  bool>::value, "");
static_assert(std::is_same<std::false_type::value_type, bool>::value, "");

static_assert(std::true_type::value  == true, "");
static_assert(std::false_type::value == false, "");

static_assert(std::true_type()  == true, "");
static_assert(std::false_type() == false, "");
