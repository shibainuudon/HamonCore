/**
 *	@file	unit_test_deque_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator, class Allocator = allocator<iter-value-type<InputIterator>>>
 *	deque(InputIterator, InputIterator, Allocator = Allocator())
 *		-> deque<iter-value-type<InputIterator>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator = allocator<ranges::range_value_t<R>>>
 *	deque(from_range_t, R&&, Allocator = Allocator())
 *		-> deque<ranges::range_value_t<R>, Allocator>;
 */

#include <hamon/deque.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <gtest/gtest.h>
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::deque v{T{1},T{2},T{3}};
		static_assert(hamon::is_same<decltype(v), hamon::deque<T>>::value, "");
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
	}
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {10,20,30,40,50};
		hamon::deque v(Iterator{a}, Iterator{a + 5});
		static_assert(hamon::is_same<decltype(v), hamon::deque<T>>::value, "");
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 50);
	}
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {10,20,30,40,50};
		hamon::allocator<T> alloc;
		hamon::deque v(Iterator{a}, Iterator{a + 5}, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::deque<T>>::value, "");
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 50);
	}
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1};
		Range r(a);
		hamon::deque v(hamon::from_range, r);
		static_assert(hamon::is_same<decltype(v), hamon::deque<T>>::value, "");
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 3);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 4);
		VERIFY(v[3] == 1);
	}
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1};
		Range r(a);
		hamon::allocator<T> alloc;
		hamon::deque v(hamon::from_range, r, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::deque<T>>::value, "");
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 3);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 4);
		VERIFY(v[3] == 1);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CtadTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace ctad_test

}	// namespace hamon_deque_test
