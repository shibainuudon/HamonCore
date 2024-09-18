/**
 *	@file	unit_test_static_typeinfo_nameof.cpp
 *
 *	@brief	nameof のテスト
 */

#include <hamon/static_typeinfo.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_static_typeinfo_test
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

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyClass>(),               "hamon_static_typeinfo_test::MyClass");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyClass::InnerClass>(),   "hamon_static_typeinfo_test::MyClass::InnerClass");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyStruct>(),              "hamon_static_typeinfo_test::MyStruct");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyStruct::InnerStruct>(), "hamon_static_typeinfo_test::MyStruct::InnerStruct");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyTemplate<int>>(),       "hamon_static_typeinfo_test::MyTemplate<int>");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyTemplate<float>>(),     "hamon_static_typeinfo_test::MyTemplate<float>");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyEnum>(),                "hamon_static_typeinfo_test::MyEnum");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::nameof<MyEnumClass>(),           "hamon_static_typeinfo_test::MyEnumClass");
}

}	// namespace hamon_static_typeinfo_test
