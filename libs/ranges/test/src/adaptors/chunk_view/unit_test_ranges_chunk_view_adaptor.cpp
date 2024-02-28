/**
 *	@file	unit_test_ranges_chunk_view_adaptor.cpp
 *
 *	@brief	views::chunk のテスト
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using CV = hamon::ranges::chunk_view<V>;

	int a[] = {1,2,3,4,5};
	V v(a);

	// views::chunk(v, n)
	{
		auto cv = hamon::views::chunk(v, 2);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");

		int expected[] = {1,2};
		VERIFY(hamon::ranges::equal(*cv.begin(), expected));
	}

	// v | views::chunk(n)
	{
		auto cv = v | hamon::views::chunk(3);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");

		int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(*cv.begin(), expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int>;
	using CV = hamon::ranges::chunk_view<V>;

	int a[] = {1,2,3,4,5};
	V v(a);

	// views::chunk(v, n)
	{
		auto cv = hamon::views::chunk(v, 4);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");

		int expected[] = {1,2,3,4};
		VERIFY(hamon::ranges::equal(*cv.begin(), expected));
	}

	// v | views::chunk(n)
	{
		auto cv = v | hamon::views::chunk(5);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");

		int expected[] = {1,2,3,4,5};
		VERIFY(hamon::ranges::equal(*cv.begin(), expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using CV = hamon::ranges::chunk_view<hamon::views::all_t<int(&)[5]>>;

	int v[] = {1,2,3,4,5};

	// views::chunk(v, n)
	{
		auto cv = hamon::views::chunk(v, 6);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");

		int expected[] = {1,2,3,4,5};
		VERIFY(hamon::ranges::equal(*cv.begin(), expected));
	}

	// v | views::chunk(n)
	{
		auto cv = v | hamon::views::chunk(2);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");

		int expected[] = {1,2};
		VERIFY(hamon::ranges::equal(*cv.begin(), expected));
	}

	return true;
}

GTEST_TEST(RangesTest, ChunkViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace adaptor_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
