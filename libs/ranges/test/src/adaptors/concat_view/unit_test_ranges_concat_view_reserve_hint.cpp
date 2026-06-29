/**
 *	@file	unit_test_ranges_concat_view_reserve_hint.cpp
 *
 *	@brief	reserve_hint() のテスト
 *
 *	constexpr auto reserve_hint() requires (approximately_sized_range<Views> && ...);
 *	constexpr auto reserve_hint() const requires (approximately_sized_range<const Views> && ...);
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/iterator/detail/is_unsigned_integer_like.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace reserve_hint_test
{

template <typename D1, typename D2>
struct TestApproximatelySizedView : hamon::ranges::view_base
{
	using Iterator = bidirectional_iterator_wrapper<int>;
	using Sentinel = test_sentinel<Iterator>;
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;

	D1 reserve_hint() noexcept;
	D2 reserve_hint() const noexcept;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	//  (approximately_sized_range<Views> && ...) &&
	//  (approximately_sized_range<const Views> && ...)
	{
		using V1 = TestApproximatelySizedView<int, short>;
		using V2 = TestApproximatelySizedView<char, int>;
		static_assert( hamon::ranges::approximately_sized_range<V1>, "");
		static_assert( hamon::ranges::approximately_sized_range<V2>, "");
		static_assert( hamon::ranges::approximately_sized_range<V1 const>, "");
		static_assert( hamon::ranges::approximately_sized_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_reserve_hint<CV&>::value, "");
		static_assert( has_reserve_hint<CV const&>::value, "");

		using D  = decltype(hamon::declval<CV&>().reserve_hint());
		using CD = decltype(hamon::declval<CV const&>().reserve_hint());
		static_assert(hamon::detail::is_unsigned_integer_like<D>, "");
		static_assert(hamon::detail::is_unsigned_integer_like<CD>, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	//  (approximately_sized_range<Views> && ...) &&
	// !(approximately_sized_range<const Views> && ...)
	{
		using V1 = TestApproximatelySizedView<int, short>;
		using V2 = TestApproximatelySizedView<char, void>;
		static_assert( hamon::ranges::approximately_sized_range<V1>, "");
		static_assert( hamon::ranges::approximately_sized_range<V2>, "");
		static_assert( hamon::ranges::approximately_sized_range<V1 const>, "");
		static_assert(!hamon::ranges::approximately_sized_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_reserve_hint<CV&>::value, "");
		static_assert(!has_reserve_hint<CV const&>::value, "");

		using D = decltype(hamon::declval<CV&>().reserve_hint());
		static_assert(hamon::detail::is_unsigned_integer_like<D>, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// !(approximately_sized_range<Views> && ...) &&
	//  (approximately_sized_range<const Views> && ...)
	{
		using V1 = TestApproximatelySizedView<void, short>;
		using V2 = TestApproximatelySizedView<char, int>;
		static_assert(!hamon::ranges::approximately_sized_range<V1>, "");
		static_assert( hamon::ranges::approximately_sized_range<V2>, "");
		static_assert( hamon::ranges::approximately_sized_range<V1 const>, "");
		static_assert( hamon::ranges::approximately_sized_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_reserve_hint<CV&>::value, "");
		static_assert( has_reserve_hint<CV const&>::value, "");

		using D  = decltype(hamon::declval<CV&>().reserve_hint());
		using CD = decltype(hamon::declval<CV const&>().reserve_hint());
		static_assert(hamon::detail::is_unsigned_integer_like<D>, "");
		static_assert(hamon::detail::is_unsigned_integer_like<CD>, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// !(approximately_sized_range<Views> && ...) &&
	// !(approximately_sized_range<const Views> && ...)
	{
		using V1 = TestApproximatelySizedView<void, short>;
		using V2 = TestApproximatelySizedView<char, void>;
		static_assert(!hamon::ranges::approximately_sized_range<V1>, "");
		static_assert( hamon::ranges::approximately_sized_range<V2>, "");
		static_assert( hamon::ranges::approximately_sized_range<V1 const>, "");
		static_assert(!hamon::ranges::approximately_sized_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert(!has_reserve_hint<CV&>::value, "");
		static_assert(!has_reserve_hint<CV const&>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<int>;
	using CV = hamon::ranges::concat_view<V1, V2>;

	{
		int a1[] = {1, 2};
		int a2[] = {1, 2, 3};
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv {v1, v2};
			VERIFY(cv.reserve_hint() == 5);
		}
		{
			CV const cv {v1, v2};
			VERIFY(cv.reserve_hint() == 5);
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	using V1 = test_input_approximately_sized_view<int>;
	using V2 = test_input_approximately_sized_view<int>;
	using CV = hamon::ranges::concat_view<V1, V2>;

	{
		int a1[] = {3, 1, 4, 1, 5};
		int a2[] = {1, 2, 3};
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv {v1, v2};
			VERIFY(cv.reserve_hint() == 8);
		}
		{
			CV const cv {v1, v2};
			VERIFY(cv.reserve_hint() == 8);
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewReserveHintTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace reserve_hint_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
