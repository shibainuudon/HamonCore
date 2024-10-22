/**
 *	@file	unit_test_list_unique.cpp
 *
 *	@brief	unique のテスト
 *
 *	size_type unique();
 *	template<class BinaryPredicate>
 *	size_type unique(BinaryPredicate binary_pred);
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace unique_test
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
LIST_TEST_CONSTEXPR bool test1()
{
	using List = hamon::list<T>;
	using SizeType = typename List::size_type;

	{
		List v;
		static_assert(hamon::is_same<decltype(v.unique()), SizeType>::value, "");
		static_assert(!noexcept(v.unique()), "");
	}
	{
		List v;
		auto ret = v.unique();
		VERIFY(ret == 0);
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}
	{
		List v{1,2,2,3,3,3,4,5,5};
		{
			auto ret = v.unique();
			VERIFY(ret == 4);
			VERIFY(v.size() == 5);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{5});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{5});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.unique();
			VERIFY(ret == 0);
			VERIFY(v.size() == 5);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{5});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{5});
				VERIFY(*it++ == T{4});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(it == v.rend());
			}
		}
	}
	{
		List v{1,2,2,3,3,2,1,1,2};
		{
			auto ret = v.unique();
			VERIFY(ret == 3);
			VERIFY(v.size() == 6);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.unique();
			VERIFY(ret == 0);
			VERIFY(v.size() == 6);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{3});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(it == v.rend());
			}
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test2()
{
	using List = hamon::list<T>;
	using SizeType = typename List::size_type;

	{
		List v;
		auto pred = [](T x, T y) { return x == y; };
		static_assert(hamon::is_same<decltype(v.unique(pred)), SizeType>::value, "");
		static_assert(!noexcept(v.unique(pred)), "");
	}
	{
		List v{1,2,12,23,3,2,51,1,2,2};
		{
			auto ret = v.unique([](T x, T y){ return x % 10 == y % 10; });
			VERIFY(ret == 4);
			VERIFY(v.size() == 6);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{23});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{51});
				VERIFY(*it++ == T{2});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{51});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{23});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(it == v.rend());
			}
		}
		{
			auto ret = v.unique([](T x, T y){ return x % 10 == y % 10; });
			VERIFY(ret == 0);
			VERIFY(v.size() == 6);
			VERIFY(v.begin() != v.end());
			VERIFY(v.rbegin() != v.rend());
			{
				auto it = v.begin();
				VERIFY(*it++ == T{1});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{23});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{51});
				VERIFY(*it++ == T{2});
				VERIFY(it == v.end());
			}
			{
				auto it = v.rbegin();
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{51});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{23});
				VERIFY(*it++ == T{2});
				VERIFY(*it++ == T{1});
				VERIFY(it == v.rend());
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, UniqueTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<long>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace unique_test

}	// namespace hamon_list_test
