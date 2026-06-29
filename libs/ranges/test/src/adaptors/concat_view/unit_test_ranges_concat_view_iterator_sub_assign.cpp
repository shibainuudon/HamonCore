/**
 *	@file	unit_test_ranges_concat_view_iterator_sub_assign.cpp
 *
 *	@brief	operator-=() のテスト
 *
 *	constexpr iterator& operator-=(difference_type n)
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
namespace iterator_sub_assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V1 = test_random_access_common_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_minus_equal<I&, int>::value, "");
		static_assert(!has_minus_equal<I const&, int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_minus_equal<I&, int>::value, "");
		static_assert(!has_minus_equal<I const&, int>::value, "");
	}
	{
		using V1 = test_bidirectional_common_view<int>;
		using V2 = test_bidirectional_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_minus_equal<I&, int>::value, "");
		static_assert(!has_minus_equal<I const&, int>::value, "");
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
		auto t1 = (it -= -3);
		VERIFY(*t1 == 4);
		VERIFY(*it == 4);
		auto t2 = (it -= 1);
		VERIFY(*t2 == 3);
		VERIFY(*it == 3);
		VERIFY((it -= -3) == cv.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewIteratorSubAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_sub_assign_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
