/**
 *	@file	unit_test_ranges_chunk_view_reserve_hint.cpp
 *
 *	@brief	reserve_hint() のテスト
 *
 *	constexpr auto reserve_hint() requires approximately_sized_range<V>;
 *	constexpr auto reserve_hint() const requires approximately_sized_range<const V>;
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/concepts/approximately_sized_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace reserve_hint_test
{

template <typename D1, typename D2, typename Iterator>
struct TestApproximatelySizedView : hamon::ranges::view_base
{
	using Sentinel = test_sentinel<Iterator>;
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;

	D1 reserve_hint() noexcept;
	D2 reserve_hint() const noexcept;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Iterator>
HAMON_CXX14_CONSTEXPR bool test00()
{
	// approximately_sized_range<V> && approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<int, short, Iterator>;
		static_assert( hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert( hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert( has_reserve_hint<CV&>::value, "");
		static_assert( has_reserve_hint<CV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().reserve_hint()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().reserve_hint()), hamon::uintptr_t>::value, "");
	}

	// !approximately_sized_range<V> && approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<void, unsigned int, Iterator>;
		static_assert(!hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert( hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert( has_reserve_hint<CV&>::value, "");
		static_assert( has_reserve_hint<CV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().reserve_hint()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().reserve_hint()), hamon::uintptr_t>::value, "");
	}

	// approximately_sized_range<V> && !approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<long, void, Iterator>;
		static_assert( hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert( has_reserve_hint<CV&>::value, "");
		static_assert(!has_reserve_hint<CV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().reserve_hint()), hamon::uintptr_t>::value, "");
	}

	// !approximately_sized_range<V> && !approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<void, void, Iterator>;
		static_assert(!hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert(!has_reserve_hint<CV&>::value, "");
		static_assert(!has_reserve_hint<CV const&>::value, "");
	}
	return true;
}

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {0,1,2,3,4,5,6,7,8,9};

	using V = View<int>;
	V v(a);

	using CV = hamon::ranges::chunk_view<V>;
	{
		CV cv{v, 1};
		CV const& ccv = cv;
		VERIFY(cv.reserve_hint()  == 10);
		VERIFY(ccv.reserve_hint() == 10);
	}
	{
		CV cv{v, 2};
		CV const& ccv = cv;
		VERIFY(cv.reserve_hint()  == 5);
		VERIFY(ccv.reserve_hint() == 5);
	}
	{
		CV cv{v, 3};
		CV const& ccv = cv;
		VERIFY(cv.reserve_hint()  == 4);
		VERIFY(ccv.reserve_hint() == 4);
	}
	{
		CV cv{v, 4};
		CV const& ccv = cv;
		VERIFY(cv.reserve_hint()  == 3);
		VERIFY(ccv.reserve_hint() == 3);
	}
	{
		CV cv{v, 5};
		CV const& ccv = cv;
		VERIFY(cv.reserve_hint()  == 2);
		VERIFY(ccv.reserve_hint() == 2);
	}
	{
		CV cv{v, 6};
		CV const& ccv = cv;
		VERIFY(cv.reserve_hint()  == 2);
		VERIFY(ccv.reserve_hint() == 2);
	}
	{
		CV cv{v, 9};
		CV const& ccv = cv;
		VERIFY(cv.reserve_hint()  == 2);
		VERIFY(ccv.reserve_hint() == 2);
	}
	{
		CV cv{v, 10};
		CV const& ccv = cv;
		VERIFY(cv.reserve_hint()  == 1);
		VERIFY(ccv.reserve_hint() == 1);
	}
	{
		CV cv{v, 11};
		CV const& ccv = cv;
		VERIFY(cv.reserve_hint()  == 1);
		VERIFY(ccv.reserve_hint() == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkViewReserveHintTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<input_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<forward_iterator_wrapper<int>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_input_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_forward_sized_view>());
}

}	// namespace reserve_hint_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
