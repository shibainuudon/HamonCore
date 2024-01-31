/**
 *	@file	unit_test_ranges_lazy_split_view_adaptor.cpp
 *
 *	@brief	views::lazy_split のテスト
 *
 *	inline constexpr unspecified lazy_split = unspecified;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using A = hamon::array<int, 10>;
	A a {{ 1, 2, 3, 0, 4, 5, 0, 0, 6, 0}};

	using RV = hamon::ranges::lazy_split_view<
		hamon::ranges::ref_view<A>,
		hamon::ranges::single_view<int>>;

	// views::lazy_split(R, hamon::ranges::range_value_t<R>)
	{
		auto rv = hamon::views::lazy_split(a, 0);
		static_assert(hamon::is_same<decltype(rv), RV>::value, "");
		auto it = rv.begin();
		{
			int expected[] = {1, 2, 3};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		{
			int expected[] = {4, 5};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		{
			VERIFY((*it).begin() == (*it).end());
		}
		++it;
		{
			int expected[] = {6};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		{
			VERIFY((*it).begin() == (*it).end());
		}
		++it;
		VERIFY(it == rv.end());
	}
	// R | views::lazy_split(hamon::ranges::range_value_t<R>)
	{
		auto rv = a | hamon::views::lazy_split(4);
		static_assert(hamon::is_same<decltype(rv), RV>::value, "");
		auto it = rv.begin();
		{
			int expected[] = {1, 2, 3, 0};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		{
			int expected[] = {5, 0, 0, 6, 0};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		VERIFY(it == rv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<char>;
	using RV = hamon::ranges::lazy_split_view<V, P>;

	int a1[] = {1, 0, 2, 0, 0, 3, 4, 0, 0, 0, 5};
	char a2[] = {0, 0};
	V v(a1);
	P p(a2);

	// views::lazy_split(R, P)
	{
		auto rv = hamon::views::lazy_split(v, p);
		static_assert(hamon::is_same<decltype(rv), RV>::value, "");
		auto it = rv.begin();
		{
			int expected[] = {1, 0, 2};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		{
			int expected[] = {3, 4};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		{
			int expected[] = {0, 5};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		VERIFY(it == rv.end());
	}
	// R | views::lazy_split(P)
	{
		auto rv = v | hamon::views::lazy_split(p);
		static_assert(hamon::is_same<decltype(rv), RV>::value, "");
		auto it = rv.begin();
		{
			int expected[] = {1, 0, 2};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		{
			int expected[] = {3, 4};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		{
			int expected[] = {0, 5};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		++it;
		VERIFY(it == rv.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace adaptor_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
