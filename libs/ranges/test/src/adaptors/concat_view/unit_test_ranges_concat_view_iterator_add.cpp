/**
 *	@file	unit_test_ranges_concat_view_iterator_add.cpp
 *
 *	@brief	operator+() のテスト
 *
 *	friend constexpr iterator operator+(const iterator& it, difference_type n)
 *		requires concat-is-random-access<Const, Views...>;
 *	friend constexpr iterator operator+(difference_type n, const iterator& it)
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
namespace iterator_add_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V1 = test_random_access_common_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_plus<I const&, int>::value, "");
		static_assert( has_plus<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_plus<I const&, int>::value, "");
		static_assert(!has_plus<int, I const&>::value, "");
	}
	{
		using V1 = test_bidirectional_common_view<int>;
		using V2 = test_bidirectional_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_plus<I const&, int>::value, "");
		static_assert(!has_plus<int, I const&>::value, "");
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

		auto it1 = cv.begin() + 1;
		auto it2 = 3 + cv.begin();
		VERIFY(*it1 == 2);
		VERIFY(*it2 == 4);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewIteratorAddTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_add_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
