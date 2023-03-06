/**
 *	@file	unit_test_utility_forward.cpp
 *
 *	@brief	forward のテスト
 */

#include <hamon/utility/forward.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_utility_test
{

namespace forward_test
{

struct U {};

static_assert(hamon::is_same<decltype(hamon::forward<U        >(std::declval<U>())), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U &      >(std::declval<U>())), U&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U &&     >(std::declval<U>())), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const  >(std::declval<U>())), U const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const& >(std::declval<U>())), U const&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const&&>(std::declval<U>())), U const&&>::value, "");

static_assert(hamon::is_same<decltype(hamon::forward<U        >(std::declval<U&>())), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U &      >(std::declval<U&>())), U&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U &&     >(std::declval<U&>())), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const  >(std::declval<U&>())), U const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const& >(std::declval<U&>())), U const&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const&&>(std::declval<U&>())), U const&&>::value, "");

static_assert(hamon::is_same<decltype(hamon::forward<U        >(std::declval<U&&>())), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U &      >(std::declval<U&&>())), U&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U &&     >(std::declval<U&&>())), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const  >(std::declval<U&&>())), U const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const& >(std::declval<U&&>())), U const&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const&&>(std::declval<U&&>())), U const&&>::value, "");

//static_assert(hamon::is_same<decltype(hamon::forward<U        >(std::declval<U const>())), U&&>::value, "");
//static_assert(hamon::is_same<decltype(hamon::forward<U &      >(std::declval<U const>())), U&>::value, "");
//static_assert(hamon::is_same<decltype(hamon::forward<U &&     >(std::declval<U const>())), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const  >(std::declval<U const>())), U const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const& >(std::declval<U const>())), U const&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const&&>(std::declval<U const>())), U const&&>::value, "");

//static_assert(hamon::is_same<decltype(hamon::forward<U        >(std::declval<U const&>())), U&&>::value, "");
//static_assert(hamon::is_same<decltype(hamon::forward<U &      >(std::declval<U const&>())), U&>::value, "");
//static_assert(hamon::is_same<decltype(hamon::forward<U &&     >(std::declval<U const&>())), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const  >(std::declval<U const&>())), U const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const& >(std::declval<U const&>())), U const&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const&&>(std::declval<U const&>())), U const&&>::value, "");

//static_assert(hamon::is_same<decltype(hamon::forward<U        >(std::declval<U const&&>())), U&&>::value, "");
//static_assert(hamon::is_same<decltype(hamon::forward<U &      >(std::declval<U const&&>())), U&>::value, "");
//static_assert(hamon::is_same<decltype(hamon::forward<U &&     >(std::declval<U const&&>())), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const  >(std::declval<U const&&>())), U const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const& >(std::declval<U const&&>())), U const&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward<U const&&>(std::declval<U const&&>())), U const&&>::value, "");

HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U        >(std::declval<U>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &      >(std::declval<U>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &&     >(std::declval<U>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const  >(std::declval<U>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const& >(std::declval<U>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const&&>(std::declval<U>()));

HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U        >(std::declval<U&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &      >(std::declval<U&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &&     >(std::declval<U&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const  >(std::declval<U&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const& >(std::declval<U&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const&&>(std::declval<U&>()));

HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U        >(std::declval<U&&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &      >(std::declval<U&&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &&     >(std::declval<U&&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const  >(std::declval<U&&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const& >(std::declval<U&&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const&&>(std::declval<U&&>()));

//HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U        >(std::declval<U const>()));
//HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &      >(std::declval<U const>()));
//HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &&     >(std::declval<U const>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const  >(std::declval<U const>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const& >(std::declval<U const>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const&&>(std::declval<U const>()));

//HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U        >(std::declval<U const&>()));
//HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &      >(std::declval<U const&>()));
//HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &&     >(std::declval<U const&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const  >(std::declval<U const&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const& >(std::declval<U const&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const&&>(std::declval<U const&>()));

//HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U        >(std::declval<U const&&>()));
//HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &      >(std::declval<U const&&>()));
//HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U &&     >(std::declval<U const&&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const  >(std::declval<U const&&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const& >(std::declval<U const&&>()));
HAMON_ASSERT_NOEXCEPT_TRUE(hamon::forward<U const&&>(std::declval<U const&&>()));

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool ForwardTest()
{
	{
		int x = 13;
		VERIFY(hamon::forward<int>(x) == 13);
		VERIFY(hamon::forward<int&>(x) == 13);
		VERIFY(hamon::forward<int&&>(x) == 13);
		VERIFY(hamon::forward<int const>(x) == 13);
		VERIFY(hamon::forward<int const&>(x) == 13);
		VERIFY(hamon::forward<int const&&>(x) == 13);
	}
	{
		int const x = 14;
//		VERIFY(hamon::forward<int>(x) == 14);
//		VERIFY(hamon::forward<int&>(x) == 14);
//		VERIFY(hamon::forward<int&&>(x) == 14);
		VERIFY(hamon::forward<int const>(x) == 14);
		VERIFY(hamon::forward<int const&>(x) == 14);
		VERIFY(hamon::forward<int const&&>(x) == 14);
	}
	return true;
}

GTEST_TEST(UtilityTest, ForwardTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ForwardTest());
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::forward<int>(42));
		HAMON_CXX11_CONSTEXPR int i = 42;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::forward<int const&>(i));
	}
}

#undef VERIFY

}	// namespace forward_test

}	// namespace hamon_utility_test
