/**
 *	@file	unit_test_deque_ctor_range.cpp
 *
 *	@brief	Rangeを引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<T> R>
 *	deque(from_range_t, R&& rg, const Allocator& = Allocator());
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_deque_test
{

namespace ctor_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Allocator = std::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;
	using Range = RangeWrapper<T>;

	static_assert(!hamon::is_constructible<Deque, Range>::value, "");
	static_assert(!hamon::is_constructible<Deque, Range, Allocator>::value, "");
	static_assert( hamon::is_constructible<Deque, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_constructible<Deque, hamon::from_range_t, Range, Allocator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Deque, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Deque, hamon::from_range_t, Range, Allocator>::value, "");
	static_assert( hamon::is_implicitly_constructible<Deque, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_implicitly_constructible<Deque, hamon::from_range_t, Range, Allocator>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, hamon::from_range_t, Range, Allocator>::value, "");

	{
		T a[] = {1,2,3,4};
		Range r(a);
		Deque v(hamon::from_range, r);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 4);
	}
	{
		T a[] = {3,1,4};
		Range r(a);
		Allocator alloc;
		Deque v(hamon::from_range, r, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 3);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CtorRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_input_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_forward_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_bidirectional_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_random_access_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_contiguous_range>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_input_sized_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_forward_sized_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_bidirectional_sized_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_random_access_sized_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_contiguous_sized_range>());
}

}	// namespace ctor_range_test

}	// namespace hamon_deque_test
