﻿/**
 *	@file	unit_test_list_back.cpp
 *
 *	@brief	back のテスト
 *
 *	reference       back();
 *	const_reference back() const;
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace back_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool
operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
LIST_TEST_CONSTEXPR bool test()
{
	using List = hamon::list<T>;
	using Reference = typename List::reference;
	using ConstReference = typename List::const_reference;

	{
		List v;
		List const cv;
		static_assert(hamon::is_same<decltype(v.back()), Reference>::value, "");
		static_assert(hamon::is_same<decltype(cv.back()), ConstReference>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert( noexcept(v.back()), "");
		static_assert( noexcept(cv.back()), "");
#endif
	}
	{
		List v{T{1},T{2},T{3}};
		VERIFY(v.back() == T{3});

		v.back() = T{42};

		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{42});
			VERIFY(it == v.end());
		}
	}
	{
		List const v{T{10},T{20},T{30}};
		VERIFY(v.back() == T{30});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, BackTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<S1>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace back_test

}	// namespace hamon_list_test
