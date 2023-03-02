/**
 *	@file	unit_test_type_traits_integral_constant.cpp
 *
 *	@brief	integral_constant のテスト
 */

#include <hamon/type_traits/integral_constant.hpp>
#include <type_traits>
#include <gtest/gtest.h>

namespace hamon_type_traits_test
{

namespace integral_constant_test
{

using Type1 = hamon::integral_constant<int, 0>;
static_assert(Type1::value == 0, "");
static_assert(std::is_same<Type1::value_type, int>::value, "");
static_assert(std::is_same<Type1::type, Type1>::value, "");
static_assert(Type1() == 0, "");
static_assert(Type1()() == 0, "");
static_assert(noexcept((int)(Type1())), "");
static_assert(noexcept(Type1()()), "");

using Type2 = hamon::integral_constant<int, 42>;
static_assert(Type2::value == 42, "");
static_assert(std::is_same<Type2::value_type, int>::value, "");
static_assert(std::is_same<Type2::type, Type2>::value, "");
static_assert(Type2{} == 42, "");
static_assert(Type2{}() == 42, "");
static_assert(noexcept((int)(Type2{})), "");
static_assert(noexcept(Type2{}()), "");

using Type3 = hamon::integral_constant<unsigned char, 1>;
static_assert(Type3::value == 1, "");
static_assert(std::is_same<Type3::value_type, unsigned char>::value, "");
static_assert(std::is_same<Type3::type, Type3>::value, "");
static_assert(Type3{} == 1, "");
static_assert(Type3{}() == 1, "");
static_assert(noexcept((unsigned char)(Type3{})), "");
static_assert(noexcept(Type3{}()), "");

}	// namespace integral_constant_test

}	// namespace hamon_type_traits_test
