/**
 *	@file	unit_test_ranges_cache_latest_view_adaptor.cpp
 *
 *	@brief	views::cache_latest のテスト
 *
 *	views::cache_latest
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/adaptors/transform_view.hpp>
#include <hamon/ranges/adaptors/filter_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {1,2,3};

	{
		auto clv = hamon::views::cache_latest(a);
		static_assert(hamon::is_same<decltype(clv),
			hamon::ranges::cache_latest_view<hamon::ranges::ref_view<int[3]>>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}
	{
		auto clv = a | hamon::views::cache_latest;
		static_assert(hamon::is_same<decltype(clv),
			hamon::ranges::cache_latest_view<hamon::ranges::ref_view<int[3]>>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<int>;

	int a[] = {1,2,3};
	V v(a);

	{
		auto clv = hamon::views::cache_latest(v);
		static_assert(hamon::is_same<decltype(clv), hamon::ranges::cache_latest_view<V>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}
	{
		auto clv = v | hamon::views::cache_latest;
		static_assert(hamon::is_same<decltype(clv), hamon::ranges::cache_latest_view<V>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}

	return true;
}

HAMON_CXX17_CONSTEXPR bool test02()
{
	const int expected[] = {4, 16};
	int xs[] = {1, 2, 3, 4, 5};
	int transform_count = 0;
	auto v = xs
		| hamon::views::transform([&](int i){ ++transform_count; return i * i; })
		| hamon::views::filter([](int i){ return i % 2 == 0; });
	VERIFY(hamon::ranges::equal(v, expected));
	VERIFY(transform_count == 7);

	transform_count = 0;
	auto w = xs
		| hamon::views::transform([&](int i){ ++transform_count; return i * i; })
		| hamon::views::cache_latest
		| hamon::views::filter([](int i){ return i % 2 == 0; });
	VERIFY(hamon::ranges::equal(w, expected));
	VERIFY(transform_count == 5);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace adaptor_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
