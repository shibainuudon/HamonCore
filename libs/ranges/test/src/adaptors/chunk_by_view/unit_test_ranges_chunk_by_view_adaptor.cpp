/**
 *	@file	unit_test_ranges_chunk_by_view_adaptor.cpp
 *
 *	@brief	views::chunk_by のテスト
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;

	int a[] = {1,2,3,3,1};
	V v(a);
	F f{};

	int const expected[] = {1,2,3};
	// views::chunk_by(v, pred)
	{
		auto cv = hamon::views::chunk_by(v, f);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(hamon::ranges::equal(*cv.begin(), expected));
	}

	// v | views::chunk_by(pred)
	{
		auto cv = v | hamon::views::chunk_by(f);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(hamon::ranges::equal(*cv.begin(), expected));
	}

	// views::chunk_by(pred)(v)
	{
		auto cv = hamon::views::chunk_by(f)(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(hamon::ranges::equal(*cv.begin(), expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<hamon::views::all_t<int(&)[5]>, F>;

	int a[] = {1,2,3,4,5};
	F f{};

	// views::chunk_by(v, pred)
	{
		auto cv = hamon::views::chunk_by(a, f);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(hamon::ranges::equal(*cv.begin(), a));
	}

	// v | views::chunk_by(pred)
	{
		auto cv = a | hamon::views::chunk_by(f);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(hamon::ranges::equal(*cv.begin(), a));
	}

	// views::chunk_by(pred)(v)
	{
		auto cv = hamon::views::chunk_by(f)(a);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(hamon::ranges::equal(*cv.begin(), a));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace adaptor_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
