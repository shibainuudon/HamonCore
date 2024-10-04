/**
 *	@file	unit_test_forward_list_unique.cpp
 *
 *	@brief	unique のテスト
 *
 *	size_type unique();
 *	template<class BinaryPredicate>
 *	size_type unique(BinaryPredicate binary_pred);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace unique_test
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
	using SizeType = typename ForwardList::size_type;

	{
		ForwardList v;
		static_assert(hamon::is_same<decltype(v.unique()), SizeType>::value, "");
		static_assert(!noexcept(v.unique()), "");
	}
	{
		ForwardList v{1,2,2,3,3,3,4,5,5};
		{
			auto ret = v.unique();
			VERIFY(ret == 4);

			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.unique();
			VERIFY(ret == 0);

			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
	}
	{
		ForwardList v{1,2,2,3,3,2,1,1,2};
		{
			auto ret = v.unique();
			VERIFY(ret == 3);

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
			auto ret = v.unique();
			VERIFY(ret == 0);

			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test2()
{
	using ForwardList = hamon::forward_list<T>;
	using SizeType = typename ForwardList::size_type;

	{
		ForwardList v;
		auto pred = [](T x, T y) { return x == y; };
		static_assert(hamon::is_same<decltype(v.unique(pred)), SizeType>::value, "");
		static_assert(!noexcept(v.unique(pred)), "");
	}
	{
		ForwardList v{1,2,12,23,3,2,51,1,2,2};
		{
			auto ret = v.unique([](T x, T y){ return x % 10 == y % 10; });
			VERIFY(ret == 4);

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
			auto ret = v.unique([](T x, T y){ return x % 10 == y % 10; });
			VERIFY(ret == 0);

			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{23});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{51});
			VERIFY(*it++ == T{2});
			VERIFY(it == v.end());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, UniqueTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<long>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace unique_test

}	// namespace hamon_forward_list_test
