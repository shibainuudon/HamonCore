/**
 *	@file	unit_test_list_resize.cpp
 *
 *	@brief	resize のテスト
 *
 *	void      resize(size_type sz);
 *	void      resize(size_type sz, const T& c);
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace resize_test
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
	using SizeType = typename List::size_type;

	{
		List v;
		SizeType sz;
		T const c{};
		static_assert(hamon::is_same<decltype(v.resize(sz)), void>::value, "");
		static_assert(hamon::is_same<decltype(v.resize(sz, c)), void>::value, "");
		static_assert(!noexcept(v.resize(sz)), "");
		static_assert(!noexcept(v.resize(sz, c)), "");
	}
	{
		List v;
		VERIFY(v.empty());

		v.resize(3);
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.rend());
		}

		v.resize(3);
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.rend());
		}

		v.resize(5);
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.rend());
		}

		v.resize(0);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}
	{
		List v;
		VERIFY(v.empty());

		v.resize(3, T{10});
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.rend());
		}

		v.resize(5, T{20});
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.rend());
		}

		v.resize(5, T{99});
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.rend());
		}

		v.resize(4, T{30});
		VERIFY(v.size() == 4);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.rend());
		}

		v.resize(0, T{40});
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, ResizeTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace resize_test

}	// namespace hamon_list_test
