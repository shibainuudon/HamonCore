/**
 *	@file	unit_test_ranges_subrange_make_subrange.cpp
 *
 *	@brief	ranges::make_subrange のテスト
 */

#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/subrange_kind.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace make_subrange_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1,2,3,4,5,6,7,8,9};
	{
		using Iter = forward_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		auto sr = hamon::ranges::make_subrange(Iter{a}, Sent{a+2});
		static_assert(hamon::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::unsized>>::value, "");
		VERIFY(sr.begin() == Iter{a});
	}
	{
		using Iter = random_access_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		auto sr = hamon::ranges::make_subrange(Iter{a}, Sent{a+3});
		static_assert(hamon::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		VERIFY(sr.begin() == Iter{a});
		VERIFY(sr.size() == 3);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1,2,3,4,5,6,7,8,9};
	{
		using Iter = forward_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		auto sr = hamon::ranges::make_subrange(Iter{a}, Sent{a+4}, 4);
		static_assert(hamon::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		VERIFY(sr.begin() == Iter{a});
		VERIFY(sr.size() == 4);
	}
	{
		using Iter = random_access_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		auto sr = hamon::ranges::make_subrange(Iter{a}, Sent{a+5}, 5);
		static_assert(hamon::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		VERIFY(sr.begin() == Iter{a});
		VERIFY(sr.size() == 5);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[] = {1,2,3,4,5,6,7,8,9};
	{
		using Range = test_forward_range<int>;
		using Iter = Range::iterator;
		using Sent = Range::sentinel;
		Range r(a, a+5);
		auto sr = hamon::ranges::make_subrange(r);
		static_assert(hamon::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::unsized>>::value, "");
		VERIFY(sr.begin() == Iter{a});
	}
	{
		using Range = test_random_access_range<int>;
		using Iter = Range::iterator;
		using Sent = Range::sentinel;
		Range r(a, a+5);
		auto sr = hamon::ranges::make_subrange(r);
		static_assert(hamon::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		VERIFY(sr.begin() == Iter{a});
		VERIFY(sr.size() == 5);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[] = {1,2,3,4,5,6,7,8,9};
	{
		using Range = test_forward_range<int>;
		using Iter = Range::iterator;
		using Sent = Range::sentinel;
		Range r(a, a+6);
		auto sr = hamon::ranges::make_subrange(r, 6);
		static_assert(hamon::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		VERIFY(sr.begin() == Iter{a});
		VERIFY(sr.size() == 6);
	}
	{
		using Range = test_random_access_range<int>;
		using Iter = Range::iterator;
		using Sent = Range::sentinel;
		Range r(a, a+7);
		auto sr = hamon::ranges::make_subrange(r, 7);
		static_assert(hamon::is_same<decltype(sr), hamon::ranges::subrange<Iter, Sent, hamon::ranges::subrange_kind::sized>>::value, "");
		VERIFY(sr.begin() == Iter{a});
		VERIFY(sr.size() == 7);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeAdvanceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace make_subrange_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
