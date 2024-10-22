/**
 *	@file	unit_test_list_pop_back.cpp
 *
 *	@brief	pop_back のテスト
 *
 *	void pop_back();
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace pop_back_test
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
		List v {1,2,3};

		static_assert(hamon::is_same<decltype(v.pop_back()), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert( noexcept(v.pop_back()), "");
#endif

		VERIFY(v.size() == 3);
		v.pop_back();
		VERIFY(!v.empty());
		VERIFY(v.size() == 2);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 1);
			VERIFY(it == v.rend());
		}

		v.pop_back();
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == 1);
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == 1);
			VERIFY(it == v.rend());
		}

		v.pop_back();
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, PopBackTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace pop_back_test

}	// namespace hamon_list_test
