/**
 *	@file	unit_test_list_size.cpp
 *
 *	@brief	size のテスト
 *
 *	size_type size() const noexcept;
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace size_test
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
	using SizeType = typename List::size_type;

	{
		List v;
		List const cv;
		static_assert(hamon::is_same<decltype(v.size()), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(cv.size()), SizeType>::value, "");
		static_assert(noexcept(v.size()), "");
		static_assert(noexcept(cv.size()), "");
	}
	{
		List const v;
		VERIFY(v.size() == 0);
	}
	{
		List const v{10};
		VERIFY(v.size() == 1);
	}
	{
		List const v{41,42};
		VERIFY(v.size() == 2);
	}
	{
		List const v{1,2,3};
		VERIFY(v.size() == 3);
	}
	{
		List const v{1,2,3,4,5,6,7,8,9};
		VERIFY(v.size() == 9);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, SizeTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace size_test

}	// namespace hamon_list_test
