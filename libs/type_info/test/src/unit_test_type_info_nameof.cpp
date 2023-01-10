/**
 *	@file	unit_test_type_info_nameof.cpp
 *
 *	@brief	nameof のテスト
 */

#include <hamon/type_info.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_type_info_test
{

class MyClass
{
public:
	class InnerClass {};
};

struct MyStruct
{
	struct InnerStruct {};
};

template <typename T>
struct MyTemplate
{};

enum MyEnum
{};

enum class MyEnumClass
{};

GTEST_TEST(TypeInfoTest, NameofTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<int>(),   "int");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<bool>(),  "bool");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<float>(), "float");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<void>(),  "void");

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyClass>(),               "hamon_type_info_test::MyClass");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyClass::InnerClass>(),   "hamon_type_info_test::MyClass::InnerClass");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyStruct>(),              "hamon_type_info_test::MyStruct");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyStruct::InnerStruct>(), "hamon_type_info_test::MyStruct::InnerStruct");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyTemplate<int>>(),       "hamon_type_info_test::MyTemplate<int>");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyTemplate<float>>(),     "hamon_type_info_test::MyTemplate<float>");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyEnum>(),                "hamon_type_info_test::MyEnum");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyEnumClass>(),           "hamon_type_info_test::MyEnumClass");
}

}	// namespace hamon_type_info_test
