/**
 *	@file	unit_test_ranges_cache_latest_view_size.cpp
 *
 *	@brief	size() のテスト
 *
 *	constexpr auto size() requires sized_range<V>;
 *	constexpr auto size() const requires sized_range<const V>;
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace size_test
{

template <typename D1, typename D2>
struct TestSizedView : hamon::ranges::view_base
{
	using Iterator = bidirectional_iterator_wrapper<int>;
	using Sentinel = test_sentinel<Iterator>;
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;

	D1 size() noexcept;
	D2 size() const noexcept;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	//  sized_range<V> && sized_range<const V>
	{
		using V = TestSizedView<int, short>;
		static_assert( hamon::ranges::sized_range<V>, "");
		static_assert( hamon::ranges::sized_range<V const>, "");

		using CLV = hamon::ranges::cache_latest_view<V>;
		static_assert( has_size<CLV&>::value, "");
		static_assert( has_size<CLV const&>::value, "");

		using D  = decltype(hamon::declval<CLV&>().size());
		static_assert(hamon::is_same<D, int>::value, "");

		using CD = decltype(hamon::declval<CLV const&>().size());
		static_assert(hamon::is_same<CD, short>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	//  sized_range<V> && !sized_range<const V>
	{
		using V = TestSizedView<char, void>;
		static_assert( hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::sized_range<V const>, "");

		using CLV = hamon::ranges::cache_latest_view<V>;
		static_assert( has_size<CLV&>::value, "");
		static_assert(!has_size<CLV const&>::value, "");

		using D  = decltype(hamon::declval<CLV&>().size());
		static_assert(hamon::is_same<D, char>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	//  !sized_range<V> && sized_range<const V>
	{
		using V = TestSizedView<void, long>;
		static_assert(!hamon::ranges::sized_range<V>, "");
		static_assert( hamon::ranges::sized_range<V const>, "");

		using CLV = hamon::ranges::cache_latest_view<V>;
		static_assert( has_size<CLV&>::value, "");
		static_assert( has_size<CLV const&>::value, "");

		using D  = decltype(hamon::declval<CLV&>().size());
		static_assert(hamon::is_same<D, long>::value, "");

		using CD = decltype(hamon::declval<CLV const&>().size());
		static_assert(hamon::is_same<CD, long>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	//  !sized_range<V> && !sized_range<const V>
	{
		using V = TestSizedView<void, void>;
		static_assert(!hamon::ranges::sized_range<V>, "");
		static_assert(!hamon::ranges::sized_range<V const>, "");

		using CLV = hamon::ranges::cache_latest_view<V>;
		static_assert(!has_size<CLV&>::value, "");
		static_assert(!has_size<CLV const&>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	using V = test_random_access_view<int>;
	using CLV = hamon::ranges::cache_latest_view<V>;

	{
		int a[] = {1, 2};
		V v(a);
		{
			CLV clv {v};
			VERIFY(clv.size() == 2);
		}
		{
			CLV const clv {v};
			VERIFY(clv.size() == 2);
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	using V = test_input_sized_view<int>;
	using CLV = hamon::ranges::cache_latest_view<V>;

	{
		int a[] = {3, 1, 4, 1, 5};
		V v(a);
		{
			CLV clv {v};
			VERIFY(clv.size() == 5);
		}
		{
			CLV const clv {v};
			VERIFY(clv.size() == 5);
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace size_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
