/**
 *	@file	unit_test_forward_list_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator, class Allocator = allocator<iter-value-type<InputIterator>>>
 *	forward_list(InputIterator, InputIterator, Allocator = Allocator())
 *		-> forward_list<iter-value-type<InputIterator>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator = allocator<ranges::range_value_t<R>>>
 *	forward_list(from_range_t, R&&, Allocator = Allocator())
 *		-> forward_list<ranges::range_value_t<R>, Allocator>;
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"

namespace hamon_forward_list_test
{

namespace ctad_test
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
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::forward_list v{T{1}, T{2}, T{3}};
		static_assert(hamon::is_same<decltype(v), hamon::forward_list<T>>::value, "");
		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(it == v.end());
	}
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {10,20,30,40,50};
		hamon::forward_list v(Iterator{a}, Iterator{a + 5});
		static_assert(hamon::is_same<decltype(v), hamon::forward_list<T>>::value, "");
		auto it = v.begin();
		VERIFY(*it++ == T{10});
		VERIFY(*it++ == T{20});
		VERIFY(*it++ == T{30});
		VERIFY(*it++ == T{40});
		VERIFY(*it++ == T{50});
		VERIFY(it == v.end());
	}
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {10,20,30,40,50};
		hamon::allocator<T> alloc;
		hamon::forward_list v(Iterator{a}, Iterator{a + 5}, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::forward_list<T, hamon::allocator<T>>>::value, "");
		auto it = v.begin();
		VERIFY(*it++ == T{10});
		VERIFY(*it++ == T{20});
		VERIFY(*it++ == T{30});
		VERIFY(*it++ == T{40});
		VERIFY(*it++ == T{50});
		VERIFY(it == v.end());
	}
#if !defined(HAMON_USE_STD_FORWARD_LIST) ||	\
	defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L)
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1};
		Range r(a);
		hamon::forward_list v(hamon::from_range, r);
		static_assert(hamon::is_same<decltype(v), hamon::forward_list<T>>::value, "");
		auto it = v.begin();
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{1});
		VERIFY(it == v.end());
	}
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1};
		Range r(a);
		hamon::allocator<T> alloc;
		hamon::forward_list v(hamon::from_range, r, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::forward_list<T, hamon::allocator<T>>>::value, "");
		auto it = v.begin();
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{1});
		VERIFY(it == v.end());
	}
#endif
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, CtadTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_forward_list_test
