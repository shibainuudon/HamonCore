/**
 *	@file	unit_test_ranges_concat_view_iterator_post_increment.cpp
 *
 *	@brief	後置インクリメントのテスト
 *
 *	constexpr void operator++(int);
 *	constexpr iterator operator++(int)
 *		requires all-forward<Const, Views...>;
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
namespace iterator_post_increment_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V1 = test_forward_view<int>;
		using V2 = test_forward_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_input_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V1 = test_input_view<int>;
		using V2 = test_input_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;

		int a1[] = {1,2};
		int a2[] = {3,4,5};
		V1 v1(a1);
		V2 v2(a2);

		CV cv(v1, v2);

		auto it = cv.begin();
		VERIFY(it != cv.end());
		VERIFY(*it == 1);
		it++;
		VERIFY(it != cv.end());
		VERIFY(*it == 2);
		it++;
		VERIFY(it != cv.end());
		VERIFY(*it == 3);
		it++;
		VERIFY(it != cv.end());
		VERIFY(*it == 4);
		it++;
		VERIFY(it != cv.end());
		VERIFY(*it == 5);
		it++;
		VERIFY(it == cv.end());
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_forward_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;

		int a1[] = {1,2};
		int a2[] = {3,4,5};
		V1 v1(a1);
		V2 v2(a2);

		CV cv(v1, v2);

		auto it = cv.begin();
		VERIFY(it != cv.end());
		VERIFY(*it == 1);
		auto t1 = it++;
		VERIFY(it != cv.end());
		VERIFY(*it == 2);
		VERIFY(*t1 == 1);
		VERIFY(*(it++) == 2);
		VERIFY(it != cv.end());
		VERIFY(*(it++) == 3);
		VERIFY(it != cv.end());
		VERIFY(*(it++) == 4);
		VERIFY(it != cv.end());
		VERIFY(*it == 5);
		it++;
		VERIFY(it == cv.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewIteratorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_post_increment_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
