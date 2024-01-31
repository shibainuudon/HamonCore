/**
 *	@file	unit_test_ranges_lazy_split_view_inner_iterator_post_increment.cpp
 *
 *	@brief	後置インクリメントのテスト
 *
 *	constexpr decltype(auto) operator++(int);
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace inner_iterator_post_increment_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());

	static_assert(hamon::is_same<decltype(hamon::declval<I>()++), I>::value, "");

	int a1[] = {0,0,1,2,3,0,4,0,0,0,5,6,7,8,9,0,0};
	int a2[] = {0,0};

	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	{
		auto inner = *i;
		auto ii = inner.begin();
		VERIFY(ii == inner.end());
	}
	++i;
	{
		auto inner = *i;
		auto ii = inner.begin();
		VERIFY(ii != inner.end());
		VERIFY(*ii == 1);
		auto t = ii++;
		VERIFY(*ii == 2);
		VERIFY(*t == 1);
		VERIFY(*ii++ == 2);
		VERIFY(*ii++ == 3);
		VERIFY(*ii++ == 0);
		VERIFY(*ii++ == 4);
		VERIFY(ii == inner.end());
	}
	++i;
	{
		auto inner = *i;
		auto ii = inner.begin();
		VERIFY(ii != inner.end());
		VERIFY(*ii++ == 0);
		VERIFY(*ii++ == 5);
		VERIFY(*ii++ == 6);
		VERIFY(*ii++ == 7);
		VERIFY(*ii++ == 8);
		VERIFY(*ii++ == 9);
		VERIFY(ii == inner.end());
	}
	++i;
	{
		auto inner = *i;
		auto ii = inner.begin();
		VERIFY(ii == inner.end());
	}
	++i;
	VERIFY(i == rv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<int>;
	using P = test_forward_static_sized_view<int, 1>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());

	static_assert(hamon::is_same<decltype(hamon::declval<I>()++), void>::value, "");

	int a1[] = {1,2,3,0,4,5};
	int a2[] = {0};

	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	{
		auto inner = *i;
		auto ii = inner.begin();
		VERIFY(ii != inner.end());
		VERIFY(*ii == 1);
		ii++;
		VERIFY(*ii == 2);
		ii++;
		VERIFY(*ii == 3);
		ii++;
		VERIFY(ii == inner.end());
	}
	++i;
	{
		auto inner = *i;
		auto ii = inner.begin();
		VERIFY(ii != inner.end());
		VERIFY(*ii == 4);
		ii++;
		VERIFY(*ii == 5);
		ii++;
		VERIFY(ii == inner.end());
	}
	++i;
	VERIFY(i == rv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewInnerIteratorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace inner_iterator_post_increment_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
