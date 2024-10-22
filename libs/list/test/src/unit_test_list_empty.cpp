/**
 *	@file	unit_test_list_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	bool empty() const noexcept;
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace empty_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
LIST_TEST_CONSTEXPR bool test()
{
	using List = hamon::list<T>;

	{
		List v;
		List const cv;
		static_assert(hamon::is_same<decltype(v.empty()), bool>::value, "");
		static_assert(hamon::is_same<decltype(cv.empty()), bool>::value, "");
		static_assert(noexcept(v.empty()), "");
		static_assert(noexcept(cv.empty()), "");
	}
	{
		List v;
		VERIFY(v.empty());
	}
	{
		List v{T{1}};
		VERIFY(!v.empty());
		v.clear();
		VERIFY(v.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, EmptyTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace empty_test

}	// namespace hamon_list_test
