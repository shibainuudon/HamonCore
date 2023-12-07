/**
 *	@file	unit_test_ranges_all.cpp
 *
 *	@brief	views::all のテスト
 */

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/adaptors/owning_view.hpp>
#include <hamon/ranges/factories/repeat_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/concepts.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace all_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// [range.all.general]/2
	// (2.1) decay-copy(E) if the decayed type of E models view.
	{
		auto r = hamon::views::repeat(13, 3);
		using R = decltype(r);
		auto v1 = r | hamon::views::all;
		auto v2 = hamon::views::all(r);
		auto v3 = r | hamon::views::all | hamon::views::all;
		auto v4 = r | (hamon::views::all | hamon::views::all);
		static_assert(hamon::same_as_t<decltype(v1), decltype(v2)>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), decltype(v3)>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), decltype(v4)>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), R>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), hamon::views::all_t<R>>::value, "");
	}
	// (2.2) Otherwise, ref_view{E} if that expression is well-formed.
	{
		int a[] = {1, 2, 3, 4, 5};
		auto v1 = a | hamon::views::all;
		auto v2 = hamon::views::all(a);
		auto v3 = a | hamon::views::all | hamon::views::all;
		auto v4 = a | (hamon::views::all | hamon::views::all);
		static_assert(hamon::same_as_t<decltype(v1), decltype(v2)>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), decltype(v3)>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), decltype(v4)>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), hamon::ranges::ref_view<int[5]>>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), hamon::views::all_t<int(&)[5]>>::value, "");
	}
	// (2.3) Otherwise, owning_view{E}.
	{
		int a[] = {1, 2, 3, 4, 5};
		using R = test_random_access_range<int>;
		R r(a);
		auto v1 = hamon::move(r) | hamon::views::all;
		auto v2 = hamon::views::all(hamon::move(r));
		auto v3 = hamon::move(r) | hamon::views::all | hamon::views::all;
		auto v4 = hamon::move(r) | (hamon::views::all | hamon::views::all);
		static_assert(hamon::same_as_t<decltype(v1), decltype(v2)>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), decltype(v3)>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), decltype(v4)>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), hamon::ranges::owning_view<R>>::value, "");
		static_assert(hamon::same_as_t<decltype(v1), hamon::views::all_t<R>>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1, 2, 3, 4, 5};
	using R = test_random_access_range<int>;
	R r(a);
	auto v1 = hamon::views::all(r);
	auto v2 = hamon::views::all(hamon::move(r));
	auto v3 = hamon::views::all(hamon::as_const(r));
	static_assert(hamon::same_as_t<decltype(v1), hamon::ranges::ref_view<R>>::value, "");
	static_assert(hamon::same_as_t<decltype(v2), hamon::ranges::owning_view<R>>::value, "");
	static_assert(hamon::same_as_t<decltype(v3), hamon::ranges::ref_view<R const>>::value, "");

	static_assert( hamon::is_invocable<decltype(hamon::views::all), R &>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::views::all), R &&>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::views::all), R const&>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::views::all), R const&&>::value, "");

	VERIFY(hamon::ranges::begin(v1) == r.begin());
	VERIFY(hamon::ranges::begin(v2) == r.begin());
	VERIFY(hamon::ranges::begin(v3) == r.begin());

	VERIFY(hamon::ranges::end(v1) == r.begin() + 5);
	VERIFY(hamon::ranges::end(v2) == r.begin() + 5);
	VERIFY(hamon::ranges::end(v3) == r.begin() + 5);

	VERIFY(&v1.base() == &r);
	VERIFY(&v2.base() != &r);
	VERIFY(&v3.base() == &r);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// TODO adaptor | views::all のテスト
	{
	}

	// TODO views::all | adaptor のテスト
	{
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AllTest)
{
	static_assert(hamon::same_as_t<
		decltype(hamon::views::all),
		decltype(hamon::ranges::views::all)>::value, "");

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace all_test
}	// namespace hamon_ranges_test
