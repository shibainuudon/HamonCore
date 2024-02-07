/**
 *	@file	unit_test_ranges_reverse_view_adaptor.cpp
 *
 *	@brief	views::reverse のテスト
 *
 *	namespace views { inline constexpr unspecified reverse = unspecified; }
 */

#include <hamon/ranges/adaptors/reverse_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/rbegin.hpp>
#include <hamon/ranges/rend.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace reverse_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// V is a specialization of reverse_view

	using R = test_bidirectional_range<int>;
	int a[] = {1,2,3};
	R r(a);
	auto v = r | hamon::views::reverse;

	// views::reverse(v)
	{
		auto rv = hamon::views::reverse(v);
		static_assert(hamon::is_same<decltype(rv), hamon::views::all_t<R&>>::value, "");
		VERIFY(hamon::ranges::equal(rv, a));
	}
	// v | views::reverse
	{
		auto rv = v | hamon::views::reverse;
		static_assert(hamon::is_same<decltype(rv), hamon::views::all_t<R&>>::value, "");
		VERIFY(hamon::ranges::equal(rv, a));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// V is a reversed subrange (sized)

	using R = test_random_access_common_range<int>;
	int a[] = {1,2,3,4};
	R r(a);
	auto sr = hamon::ranges::make_subrange(hamon::ranges::rbegin(r), hamon::ranges::rend(r));

	using RV = hamon::ranges::subrange<
		random_access_iterator_wrapper<int>,
		random_access_iterator_wrapper<int>,
		hamon::ranges::subrange_kind::sized>;

	// views::reverse(v)
	{
		auto rv = hamon::views::reverse(sr);
		static_assert(hamon::is_same<decltype(rv), RV>::value, "");
		VERIFY(hamon::ranges::equal(rv, a));
	}
	// v | views::reverse
	{
		auto rv = sr | hamon::views::reverse;
		static_assert(hamon::is_same<decltype(rv), RV>::value, "");
		VERIFY(hamon::ranges::equal(rv, a));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// V is a reversed subrange (unsized)

	using R = test_bidirectional_common_range<int>;
	int a[] = {3,1,4,1,5};
	R r(a);
	auto sr = hamon::ranges::make_subrange(hamon::ranges::rbegin(r), hamon::ranges::rend(r));

	using RV = hamon::ranges::subrange<
		bidirectional_iterator_wrapper<int>,
		bidirectional_iterator_wrapper<int>,
		hamon::ranges::subrange_kind::unsized>;

	// views::reverse(v)
	{
		auto rv = hamon::views::reverse(sr);
		static_assert(hamon::is_same<decltype(rv), RV>::value, "");
		VERIFY(hamon::ranges::equal(rv, a));
	}
	// v | views::reverse
	{
		auto rv = sr | hamon::views::reverse;
		static_assert(hamon::is_same<decltype(rv), RV>::value, "");
		VERIFY(hamon::ranges::equal(rv, a));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// Otherwise
	{
		using V = test_bidirectional_view<int>;
		int a[] = {1,2,3};
		V v(a);

		int const expected[] = {3,2,1};

		// views::reverse(v)
		{
			auto rv = hamon::views::reverse(v);
			static_assert(hamon::is_same<decltype(rv), hamon::ranges::reverse_view<V>>::value, "");
			VERIFY(hamon::ranges::equal(rv, expected));
		}
		// v | views::reverse
		{
			auto rv = v | hamon::views::reverse;
			static_assert(hamon::is_same<decltype(rv), hamon::ranges::reverse_view<V>>::value, "");
			VERIFY(hamon::ranges::equal(rv, expected));
		}
	}
	{
		using R = test_bidirectional_range<int>;
		int a[] = {10,9,8,7};
		R r(a);

		int const expected[] = {7,8,9,10};

		// views::reverse(v)
		{
			auto rv = hamon::views::reverse(r);
			static_assert(hamon::is_same<decltype(rv), hamon::ranges::reverse_view<hamon::views::all_t<R&>>>::value, "");
			VERIFY(hamon::ranges::equal(rv, expected));
		}
		// v | views::reverse
		{
			auto rv = r | hamon::views::reverse;
			static_assert(hamon::is_same<decltype(rv), hamon::ranges::reverse_view<hamon::views::all_t<R&>>>::value, "");
			VERIFY(hamon::ranges::equal(rv, expected));
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ReverseViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace adaptor_test
}	// namespace reverse_view_test
}	// namespace hamon_ranges_test
