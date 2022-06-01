/**
 *	@file	unit_test_tuple_tuple_element.cpp
 *
 *	@brief	tuple_element のテスト
 */

#include <hamon/tuple/tuple_element.hpp>
#include <tuple>
#include <type_traits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

static_assert(std::is_same<hamon::tuple_element_t<0, std::tuple<int>               >, int               >::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, std::tuple<int> const         >, int const         >::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, std::tuple<int>       volatile>, int       volatile>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, std::tuple<int> const volatile>, int const volatile>::value, "");

static_assert(std::is_same<hamon::tuple_element_t<0, std::tuple<float, int>               >, float               >::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, std::tuple<float, int> const         >, float const         >::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, std::tuple<float, int>       volatile>, float       volatile>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, std::tuple<float, int> const volatile>, float const volatile>::value, "");

static_assert(std::is_same<hamon::tuple_element_t<1, std::tuple<float, int>               >, int               >::value, "");
static_assert(std::is_same<hamon::tuple_element_t<1, std::tuple<float, int> const         >, int const         >::value, "");
static_assert(std::is_same<hamon::tuple_element_t<1, std::tuple<float, int>       volatile>, int       volatile>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<1, std::tuple<float, int> const volatile>, int const volatile>::value, "");
