/**
 *	@file	unit_test_any_ctor_value.cpp
 *
 *	@brief	値コンストラクタのテスト
 *
 *	template<class T>
 *	any(T&& value);
 */

#include <hamon/any.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <gtest/gtest.h>
#include <string>

namespace hamon_any_test
{

namespace ctor_value_test
{

struct S1
{
	S1(S1 const&) = default;
	S1(S1 &&)     = default;
};

struct S2
{
	S2(S2 const&) = delete;
	S2(S2 &&)     = default;
};

struct S3
{
	S3(S3 const&) = default;
	S3(S3 &&)     = delete;
};

struct S4
{
	S4(S4 const&) = delete;
	S4(S4 &&)     = delete;
};

static_assert( hamon::is_constructible<hamon::any, int>::value, "");
static_assert( hamon::is_constructible<hamon::any, float>::value, "");
static_assert( hamon::is_constructible<hamon::any, void*>::value, "");
static_assert( hamon::is_constructible<hamon::any, std::string>::value, "");
static_assert( hamon::is_constructible<hamon::any, S1>::value, "");
static_assert(!hamon::is_constructible<hamon::any, S2>::value, "");
static_assert( hamon::is_constructible<hamon::any, S3>::value, "");
static_assert(!hamon::is_constructible<hamon::any, S4>::value, "");

GTEST_TEST(AnyTest, CtorValueTest)
{
	{
		hamon::any a{3};
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ(3, hamon::any_cast<int>(a));
	}
	{
		hamon::any a{std::string("Hello")};
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ("Hello", hamon::any_cast<std::string>(a));
	}
}

}	// namespace ctor_value_test

}	// namespace hamon_any_test
