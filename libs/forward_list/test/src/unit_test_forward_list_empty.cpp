/**
 *	@file	unit_test_forward_list_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	bool empty() const noexcept;
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace empty_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		ForwardList const cv;
		static_assert(hamon::is_same<decltype(v.empty()), bool>::value, "");
		static_assert(hamon::is_same<decltype(cv.empty()), bool>::value, "");
		static_assert(noexcept(v.empty()), "");
		static_assert(noexcept(cv.empty()), "");
	}
	{
		ForwardList v;
		VERIFY(v.empty());
	}
	{
		ForwardList v{T{1}};
		VERIFY(!v.empty());
		v.clear();
		VERIFY(v.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, EmptyTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace empty_test

}	// namespace hamon_forward_list_test
