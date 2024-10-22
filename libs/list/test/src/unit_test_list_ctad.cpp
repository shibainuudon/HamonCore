/**
 *	@file	unit_test_list_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator, class Allocator = allocator<iter-value-type<InputIterator>>>
 *	list(InputIterator, InputIterator, Allocator = Allocator())
 *		-> list<iter-value-type<InputIterator>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator = allocator<ranges::range_value_t<R>>>
 *	list(from_range_t, R&&, Allocator = Allocator())
 *		-> list<ranges::range_value_t<R>, Allocator>;
 */

#include <hamon/list/list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"

namespace hamon_list_test
{

namespace ctad_test
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
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::list v{T{1}, T{2}, T{3}};
		static_assert(hamon::is_same<decltype(v), hamon::list<T>>::value, "");
		VERIFY(v.size() == 3);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
	}
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {10,20,30,40,50};
		hamon::list v(Iterator{a}, Iterator{a + 5});
		static_assert(hamon::is_same<decltype(v), hamon::list<T>>::value, "");
		VERIFY(v.size() == 5);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{40});
			VERIFY(*it++ == T{50});
			VERIFY(it == v.end());
		}
	}
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {10,20,30,40,50};
		hamon::allocator<T> alloc;
		hamon::list v(Iterator{a}, Iterator{a + 5}, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::list<T, hamon::allocator<T>>>::value, "");
		VERIFY(v.size() == 5);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{40});
			VERIFY(*it++ == T{50});
			VERIFY(it == v.end());
		}
	}
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1};
		Range r(a);
		hamon::list v(hamon::from_range, r);
		static_assert(hamon::is_same<decltype(v), hamon::list<T>>::value, "");
		VERIFY(v.size() == 4);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.end());
		}
	}
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1};
		Range r(a);
		hamon::allocator<T> alloc;
		hamon::list v(hamon::from_range, r, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::list<T, hamon::allocator<T>>>::value, "");
		VERIFY(v.size() == 4);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.end());
		}
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, CtadTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_list_test
