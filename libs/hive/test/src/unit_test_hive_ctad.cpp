/**
 *	@file	unit_test_hive_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator, class Allocator = allocator<iter-value-type<InputIterator>>>
 *	hive(InputIterator, InputIterator, Allocator = Allocator())
 *		-> hive<iter-value-type<InputIterator>, Allocator>;
 *
 *	template<class InputIterator, class Allocator = allocator<iter-value-type<InputIterator>>>
 *	hive(InputIterator, InputIterator, hive_limits, Allocator = Allocator())
 *		-> hive<iter-value-type<InputIterator>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator = allocator<ranges::range_value_t<R>>>
 *	hive(from_range_t, R&&, Allocator = Allocator())
 *		-> hive<ranges::range_value_t<R>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator = allocator<ranges::range_value_t<R>>>
 *	hive(from_range_t, R&&, hive_limits, Allocator = Allocator())
 *		-> hive<ranges::range_value_t<R>, Allocator>;
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"

namespace hamon_hive_test
{

namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::hive v{T{1},T{2},T{3}};
		static_assert(hamon::is_same<decltype(v), hamon::hive<T>>::value, "");
		VERIFY(v.size() == 3u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{6});
	}
	// InputIterator, InputIterator
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {1,2,3,4};
		hamon::hive v(Iterator{a}, Iterator{a + 4});
		static_assert(hamon::is_same<decltype(v), hamon::hive<T>>::value, "");
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{10});
	}
	// InputIterator, InputIterator, Allocator
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {1,2,3,4,5};
		hamon::allocator<T> alloc;
		hamon::hive v(Iterator{a}, Iterator{a + 5}, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::hive<T>>::value, "");
		VERIFY(v.size() == 5u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{15});
	}
	// InputIterator, InputIterator, hive_limits
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {1,2,3,4};
		hamon::hive v(Iterator{a}, Iterator{a + 4}, hamon::hive_limits{1, 100});
		static_assert(hamon::is_same<decltype(v), hamon::hive<T>>::value, "");
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{10});
	}
	// InputIterator, InputIterator, hive_limits, Allocator
	{
		using Iterator = forward_iterator_wrapper<T>;
		T a[] {1,2,3,4};
		hamon::allocator<T> alloc;
		hamon::hive v(Iterator{a}, Iterator{a + 4}, hamon::hive_limits{1, 100}, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::hive<T>>::value, "");
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{10});
	}
	// from_range_t, R&&
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1};
		Range r(a);
		hamon::hive v(hamon::from_range, r);
		static_assert(hamon::is_same<decltype(v), hamon::hive<T>>::value, "");
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{9});
	}
	// from_range_t, R&&, Allocator
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1,5};
		Range r(a);
		hamon::allocator<T> alloc;
		hamon::hive v(hamon::from_range, r, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::hive<T>>::value, "");
		VERIFY(v.size() == 5u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{14});
	}
	// from_range_t, R&&, hive_limits
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1};
		Range r(a);
		hamon::hive v(hamon::from_range, r, hamon::hive_limits{1, 100});
		static_assert(hamon::is_same<decltype(v), hamon::hive<T>>::value, "");
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{9});
	}
	// from_range_t, R&&, hive_limits, Allocator
	{
		using Range = test_input_range<T>;
		T a[] {3,1,4,1,5};
		Range r(a);
		hamon::allocator<T> alloc;
		hamon::hive v(hamon::from_range, r, hamon::hive_limits{1, 100}, alloc);
		static_assert(hamon::is_same<decltype(v), hamon::hive<T>>::value, "");
		VERIFY(v.size() == 5u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{14});
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtadTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace ctad_test

}	// namespace hamon_hive_test
