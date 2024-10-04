/**
 *	@file	unit_test_forward_list_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	void merge(forward_list& x);
 *	void merge(forward_list&& x);
 *	template<class Compare> void merge(forward_list& x, Compare comp);
 *	template<class Compare> void merge(forward_list&& x, Compare comp);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace merge_test
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
FORWARD_LIST_TEST_CONSTEXPR bool test1()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		ForwardList x;
		static_assert(hamon::is_same<decltype(v.merge(x)), void>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
		static_assert(!noexcept(v.merge(x)), "");
#endif
	}

	{
		ForwardList v1{1,3,3,5,9};
		ForwardList v2{2,3,4,4,7,8};
		v1.merge(v2);

		VERIFY(v2.empty());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{7});
			VERIFY(*it++ == T{8});
			VERIFY(*it++ == T{9});
			VERIFY(it == v1.end());
		}
	}
	{
		ForwardList v1{1,3,3,5,9};
		ForwardList v2;
		v1.merge(v2);

		VERIFY(v2.empty());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{9});
			VERIFY(it == v1.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test2()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		ForwardList x;
		static_assert(hamon::is_same<decltype(v.merge(hamon::move(x))), void>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
		static_assert(!noexcept(v.merge(hamon::move(x))), "");
#endif
	}

	{
		ForwardList v1{1,3,4};
		ForwardList v2{2,5,6};
		v1.merge(hamon::move(v2));

		VERIFY(v2.empty());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{6});
			VERIFY(it == v1.end());
		}
	}
	{
		ForwardList v1{2,5,6};
		ForwardList v2{1,3,4};
		v1.merge(hamon::move(v2));

		VERIFY(v2.empty());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{6});
			VERIFY(it == v1.end());
		}
	}
	{
		ForwardList v1;
		ForwardList v2{2,5,6};
		v1.merge(hamon::move(v2));

		VERIFY(v2.empty());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{6});
			VERIFY(it == v1.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test3()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		ForwardList x;
		auto comp = [](T a, T b){ return a < b; };
		static_assert(hamon::is_same<decltype(v.merge(x, comp)), void>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
		static_assert(!noexcept(v.merge(x, comp)), "");
#endif
	}

	{
		ForwardList v1{4,3,1};
		ForwardList v2{6,5,2};
		v1.merge(v2, [](T x, T y){ return x > y; });

		VERIFY(v2.empty());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test4()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		ForwardList x;
		auto comp = [](T a, T b){ return a < b; };
		static_assert(hamon::is_same<decltype(v.merge(hamon::move(x), comp)), void>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
		static_assert(!noexcept(v.merge(hamon::move(x), comp)), "");
#endif
	}

	{
		ForwardList v1{9,5,3,3,1};
		ForwardList v2{8,7,4,4,3,2};
		v1.merge(hamon::move(v2), [](T x, T y){ return x > y; });

		VERIFY(v2.empty());

		{
			auto it = v1.begin();
			VERIFY(*it++ == T{9});
			VERIFY(*it++ == T{8});
			VERIFY(*it++ == T{7});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.end());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, MergeTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());

	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3<float>());

	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test4<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test4<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test4<float>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace merge_test

}	// namespace hamon_forward_list_test
