/**
 *	@file	unit_test_list_max_size.cpp
 *
 *	@brief	max_size のテスト
 *
 *	size_type max_size() const noexcept;
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace max_size_test
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
		static_assert(hamon::is_same<decltype(v.max_size()), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(cv.max_size()), SizeType>::value, "");
		static_assert(noexcept(v.max_size()), "");
		static_assert(noexcept(cv.max_size()), "");
	}
	{
		List const v;
		auto n = v.max_size();
		VERIFY(n > 0);
	}
	{
		List const v{1,2,3};
		auto n = v.max_size();
		VERIFY(n > 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, MaxSizeTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace max_size_test

}	// namespace hamon_list_test
