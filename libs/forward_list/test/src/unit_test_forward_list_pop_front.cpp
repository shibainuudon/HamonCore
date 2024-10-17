/**
 *	@file	unit_test_forward_list_pop_front.cpp
 *
 *	@brief	pop_front のテスト
 *
 *	void pop_front();
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace pop_front_test
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
		ForwardList v {1,2,3};

		static_assert(hamon::is_same<decltype(v.pop_front()), void>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
		static_assert( noexcept(v.pop_front()), "");
#endif

		v.pop_front();
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(it == v.end());
		}

		v.pop_front();
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == 3);
			VERIFY(it == v.end());
		}

		v.pop_front();
		VERIFY(v.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, PopFrontTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace pop_front_test

}	// namespace hamon_forward_list_test
