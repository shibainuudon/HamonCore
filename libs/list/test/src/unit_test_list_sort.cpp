/**
 *	@file	unit_test_list_sort.cpp
 *
 *	@brief	sort のテスト
 *
 *	void sort();
 *	template<class Compare> void sort(Compare comp);
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace sort_test
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

	{
		List v;
		static_assert(hamon::is_same<decltype(v.sort()), void>::value, "");
		static_assert(!noexcept(v.sort()), "");
	}
	{
		List v;
		v.sort();
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}
	{
		List v{3};
		v.sort();
		VERIFY(v.size() == 1);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{3});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{1,2};
		v.sort();
		VERIFY(v.size() == 2);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{2,1};
		v.sort();
		VERIFY(v.size() == 2);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{3,2,1};
		v.sort();
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{4,3,2,1};
		v.sort();
		VERIFY(v.size() == 4);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{5,4,3,2,1};
		v.sort();
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
		List v{6,5,4,3,2,1};
		v.sort();
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
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
			auto it = v.rbegin();
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{7,6,5,4,3,2,1};
		v.sort();
		VERIFY(v.size() == 7);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
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
			auto it = v.rbegin();
			VERIFY(*it++ == T{7});
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{8,7,6,5,4,3,2,1};
		v.sort();
		VERIFY(v.size() == 8);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
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
			auto it = v.rbegin();
			VERIFY(*it++ == T{8});
			VERIFY(*it++ == T{7});
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{9,8,7,6,5,4,3,2,1};
		v.sort();
		VERIFY(v.size() == 9);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
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
			auto it = v.rbegin();
			VERIFY(*it++ == T{9});
			VERIFY(*it++ == T{8});
			VERIFY(*it++ == T{7});
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{5,3,9,2,8,7,6,1,4};
		v.sort();
		VERIFY(v.size() == 9);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
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
			auto it = v.rbegin();
			VERIFY(*it++ == T{9});
			VERIFY(*it++ == T{8});
			VERIFY(*it++ == T{7});
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}
	}
	{
		List v{8,7,5,9,0,1,3,2,6,4};
		v.sort();
		VERIFY(v.size() == 10);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
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
		{
			auto it = v.rbegin();
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
			VERIFY(it == v.rend());
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test2()
{
	using List = hamon::list<T>;

	{
		List v;
		auto comp = [](T a, T b){ return a < b; };
		static_assert(hamon::is_same<decltype(v.sort(comp)), void>::value, "");
		static_assert(!noexcept(v.sort(comp)), "");
	}
	{
		List v{8,7,5,9,0,1,3,2,6,4};
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

struct S
{
	int id;
	float value;
};

LIST_TEST_CONSTEXPR bool test3()
{
	hamon::list<S> v
	{
		S{0, 10},
		S{1, 20},
		S{0, 30},
		S{2, 40},
		S{1, 50},
		S{1, 60},
		S{2, 70},
		S{0, 80},
		S{0, 90},
	};

	v.sort([](S x, S y){return x.id < y.id;});

	auto it = v.begin();
	VERIFY(it->id == 0);
	VERIFY(it->value == 10);
	++it;
	VERIFY(it->id == 0);
	VERIFY(it->value == 30);
	++it;
	VERIFY(it->id == 0);
	VERIFY(it->value == 80);
	++it;
	VERIFY(it->id == 0);
	VERIFY(it->value == 90);
	++it;
	VERIFY(it->id == 1);
	VERIFY(it->value == 20);
	++it;
	VERIFY(it->id == 1);
	VERIFY(it->value == 50);
	++it;
	VERIFY(it->id == 1);
	VERIFY(it->value == 60);
	++it;
	VERIFY(it->id == 2);
	VERIFY(it->value == 40);
	++it;
	VERIFY(it->id == 2);
	VERIFY(it->value == 70);
	++it;
	VERIFY(it == v.end());

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, SortTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace sort_test

}	// namespace hamon_list_test
