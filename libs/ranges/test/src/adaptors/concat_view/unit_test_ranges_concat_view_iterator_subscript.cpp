/**
 *	@file	unit_test_ranges_concat_view_iterator_subscript.cpp
 *
 *	@brief	operator[]() のテスト
 *
 *	constexpr decltype(auto) operator[](difference_type n) const
 *		requires concat-is-random-access<Const, Views...>;
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace iterator_subscript_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V1 = test_random_access_common_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), int&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), int&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V1 = test_bidirectional_common_view<int>;
		using V2 = test_bidirectional_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V1 = test_random_access_common_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;

		int a1[] = {1,2,3};
		int a2[] = {4,5};
		V1 v1(a1);
		V2 v2(a2);

		CV cv(v1, v2);

		auto it = cv.begin();
		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 3);
		VERIFY(it[3] == 4);
		VERIFY(it[4] == 5);

		it[3] = 42;

		++it;
		VERIFY(it[0] == 2);
		VERIFY(it[1] == 3);
		VERIFY(it[2] == 42);
		VERIFY(it[3] == 5);

		it[1] = 10;
		VERIFY(a1[2] == 10);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewIteratorSubscriptTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_subscript_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
