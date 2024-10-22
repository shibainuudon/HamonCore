/**
 *	@file	unit_test_list_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	void merge(list& x);
 *	void merge(list&& x);
 *	template<class Compare> void merge(list& x, Compare comp);
 *	template<class Compare> void merge(list&& x, Compare comp);
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace merge_test
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
		List x;
		static_assert(hamon::is_same<decltype(v.merge(x)), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert(!noexcept(v.merge(x)), "");
#endif
	}

	{
		List v1;
		List v2;
		v1.merge(v2);

		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
		VERIFY(v2.begin() == v2.end());
		VERIFY(v2.rbegin() == v2.rend());

		VERIFY(v1.empty());
		VERIFY(v1.size() == 0);
		VERIFY(v1.begin() == v1.end());
		VERIFY(v1.rbegin() == v1.rend());
	}
	{
		List v1{1,3,3,5,9};
		List v2{2,3,4,4,7,8};
		v1.merge(v2);

		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
		VERIFY(v2.begin() == v2.end());
		VERIFY(v2.rbegin() == v2.rend());

		VERIFY(v1.size() == 11);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
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
		{
			auto it = v1.rbegin();
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
			VERIFY(it == v1.rend());
		}
	}
	{
		List v1{1,3,3,5,9};
		List v2;
		v1.merge(v2);

		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
		VERIFY(v2.begin() == v2.end());
		VERIFY(v2.rbegin() == v2.rend());

		VERIFY(v1.size() == 5);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{9});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{9});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
	}
	{
		List v{1,2,3};
		v.merge(v);

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

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test2()
{
	using List = hamon::list<T>;

	{
		List v;
		List x;
		static_assert(hamon::is_same<decltype(v.merge(hamon::move(x))), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert(!noexcept(v.merge(hamon::move(x))), "");
#endif
	}

	{
		List v1{1,3,4};
		List v2{2,5,6};
		v1.merge(hamon::move(v2));

		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
		VERIFY(v2.begin() == v2.end());
		VERIFY(v2.rbegin() == v2.rend());

		VERIFY(v1.size() == 6);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
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
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
	}
	{
		List v1{2,5,6};
		List v2{1,3,4};
		v1.merge(hamon::move(v2));

		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
		VERIFY(v2.begin() == v2.end());
		VERIFY(v2.rbegin() == v2.rend());

		VERIFY(v1.size() == 6);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
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
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v1.rend());
		}
	}
	{
		List v1;
		List v2{2,5,6};
		v1.merge(hamon::move(v2));

		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
		VERIFY(v2.begin() == v2.end());
		VERIFY(v2.rbegin() == v2.rend());

		VERIFY(v1.size() == 3);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
		{
			auto it = v1.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{6});
			VERIFY(it == v1.end());
		}
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{2});
			VERIFY(it == v1.rend());
		}
	}
	{
		List v{1,2,3};
		v.merge(hamon::move(v));

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

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test3()
{
	using List = hamon::list<T>;

	{
		List v;
		List x;
		auto comp = [](T a, T b){ return a < b; };
		static_assert(hamon::is_same<decltype(v.merge(x, comp)), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert(!noexcept(v.merge(x, comp)), "");
#endif
	}

	{
		List v1{4,3,1};
		List v2{6,5,2};
		v1.merge(v2, [](T x, T y){ return x > y; });

		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
		VERIFY(v2.begin() == v2.end());
		VERIFY(v2.rbegin() == v2.rend());

		VERIFY(v1.size() == 6);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
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
		{
			auto it = v1.rbegin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{6});
			VERIFY(it == v1.rend());
		}
	}
	{
		List v{3,2,1};
		v.merge(v, [](T x, T y){ return x > y; });

		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.rend());
		}
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test4()
{
	using List = hamon::list<T>;

	{
		List v;
		List x;
		auto comp = [](T a, T b){ return a < b; };
		static_assert(hamon::is_same<decltype(v.merge(hamon::move(x), comp)), void>::value, "");
#if !defined(HAMON_USE_STD_LIST)
		static_assert(!noexcept(v.merge(hamon::move(x), comp)), "");
#endif
	}

	{
		List v1{9,5,3,3,1};
		List v2{8,7,4,4,3,2};
		v1.merge(hamon::move(v2), [](T x, T y){ return x > y; });

		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
		VERIFY(v2.begin() == v2.end());
		VERIFY(v2.rbegin() == v2.rend());

		VERIFY(v1.size() == 11);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.rbegin() != v1.rend());
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
		{
			auto it = v1.rbegin();
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
			VERIFY(it == v1.rend());
		}
	}
	{
		List v{3,2,1};
		v.merge(hamon::move(v), [](T x, T y){ return x > y; });

		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.rend());
		}
	}

	return true;
}

struct S
{
	int id;
	float value;
};

LIST_TEST_CONSTEXPR bool test5()
{
	hamon::list<S> v1
	{
		{0, 10},
		{1, 11},
		{3, 12},
		{4, 13},
	};
	hamon::list<S> v2
	{
		{1, 20},
		{1, 21},
		{2, 22},
		{3, 23},
		{4, 24},
	};
	v1.merge(v2, [](S x, S y){return x.id < y.id;});
	VERIFY(v2.empty());
	VERIFY(v1.size() == 9);
	{
		auto it = v1.begin();
		VERIFY(it->id == 0);
		VERIFY(it->value == 10);
		++it;
		VERIFY(it->id == 1);
		VERIFY(it->value == 11);
		++it;
		VERIFY(it->id == 1);
		VERIFY(it->value == 20);
		++it;
		VERIFY(it->id == 1);
		VERIFY(it->value == 21);
		++it;
		VERIFY(it->id == 2);
		VERIFY(it->value == 22);
		++it;
		VERIFY(it->id == 3);
		VERIFY(it->value == 12);
		++it;
		VERIFY(it->id == 3);
		VERIFY(it->value == 23);
		++it;
		VERIFY(it->id == 4);
		VERIFY(it->value == 13);
		++it;
		VERIFY(it->id == 4);
		VERIFY(it->value == 24);
		++it;
		VERIFY(it == v1.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, MergeTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test4<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test4<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test4<float>());

	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test5());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace merge_test

}	// namespace hamon_list_test
