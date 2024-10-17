/**
 *	@file	unit_test_forward_list_sort.cpp
 *
 *	@brief	sort のテスト
 *
 *	void sort();
 *	template<class Compare>
 *	void sort(Compare comp);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace sort_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

struct S
{
	int id;
	float value;

	HAMON_CXX20_CONSTEXPR bool
	operator<(S const& rhs) const
	{
		return id < rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test1()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		static_assert(hamon::is_same<decltype(v.sort()), void>::value, "");
		static_assert(!noexcept(v.sort()), "");
	}
	{
		ForwardList v;
		v.sort();
		VERIFY(v.empty());
	}
	{
		ForwardList v{3};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{3});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{1,2};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{2,1};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{3,2,1};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{4,3,2,1};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{4});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{5,4,3,2,1};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{5});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{6,5,4,3,2,1};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{5});
		VERIFY(*it++ == T{6});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{7,6,5,4,3,2,1};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{5});
		VERIFY(*it++ == T{6});
		VERIFY(*it++ == T{7});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{8,7,6,5,4,3,2,1};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{5});
		VERIFY(*it++ == T{6});
		VERIFY(*it++ == T{7});
		VERIFY(*it++ == T{8});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{9,8,7,6,5,4,3,2,1};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{5});
		VERIFY(*it++ == T{6});
		VERIFY(*it++ == T{7});
		VERIFY(*it++ == T{8});
		VERIFY(*it++ == T{9});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{5,3,9,2,8,7,6,1,4};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{5});
		VERIFY(*it++ == T{6});
		VERIFY(*it++ == T{7});
		VERIFY(*it++ == T{8});
		VERIFY(*it++ == T{9});
		VERIFY(it == v.end());
	}
	{
		ForwardList v{8,7,5,9,0,1,3,2,6,4};
		v.sort();

		auto it = v.begin();
		VERIFY(*it++ == T{0});
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{5});
		VERIFY(*it++ == T{6});
		VERIFY(*it++ == T{7});
		VERIFY(*it++ == T{8});
		VERIFY(*it++ == T{9});
		VERIFY(it == v.end());
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test2()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		auto comp = [](T a, T b){ return a < b; };
		static_assert(hamon::is_same<decltype(v.sort(comp)), void>::value, "");
		static_assert(!noexcept(v.sort(comp)), "");
	}
	{
		ForwardList v{8,7,5,9,0,1,3,2,6,4};
		auto comp = [](T a, T b){ return a > b; };
		v.sort(comp);

		auto it = v.begin();
		VERIFY(*it++ == T{9});
		VERIFY(*it++ == T{8});
		VERIFY(*it++ == T{7});
		VERIFY(*it++ == T{6});
		VERIFY(*it++ == T{5});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{0});
		VERIFY(it == v.end());
	}

	return true;
}

FORWARD_LIST_TEST_CONSTEXPR bool test3()
{
	hamon::forward_list<S> v
	{
		S{0, 10},
		S{1, 20},
		S{0, 30},
		S{2, 40},
		S{1, 50},
	};

	v.sort();

	auto it = v.begin();
	VERIFY(it->id == 0);
	VERIFY(it->value == 10);
	++it;
	VERIFY(it->id == 0);
	VERIFY(it->value == 30);
	++it;
	VERIFY(it->id == 1);
	VERIFY(it->value == 20);
	++it;
	VERIFY(it->id == 1);
	VERIFY(it->value == 50);
	++it;
	VERIFY(it->id == 2);
	VERIFY(it->value == 40);
	++it;
	VERIFY(it == v.end());

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, SortTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());

	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace sort_test

}	// namespace hamon_forward_list_test
