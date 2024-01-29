/**
 *	@file	unit_test_ranges_join_with_view_adaptor.cpp
 *
 *	@brief	views::join_with のテスト
 *
 *	hamon::views::join_with
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace adaptor_test
{

template <typename View, typename T, typename = void>
struct CanBePiped
	: hamon::false_type {};

template <typename View, typename T>
struct CanBePiped<View, T, hamon::void_t<decltype(hamon::declval<View>() | hamon::declval<T>())>>
	: hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using A = hamon::array<hamon::array<int, 2>, 3>;
	A a
	{{
		{{11, 12}},
		{{21, 22}},
		{{31, 32}},
	}};

	using JV = hamon::ranges::join_with_view<hamon::ranges::ref_view<A>, hamon::ranges::single_view<int>>;

	// views::join_with(v)
	{
		auto jv = hamon::views::join_with(a, 0);
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(*jv.begin() == 11);
		VERIFY(*hamon::ranges::next(jv.begin(), 2) == 0);
	}
	// v | views::join_with
	{
		auto jv = a | hamon::views::join_with(42);
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(*jv.begin() == 11);
		VERIFY(*hamon::ranges::next(jv.begin(), 2) == 42);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using InnerView = test_forward_view<int>;
	using View = test_forward_view<InnerView>;
	using Pattern = test_forward_view<int>;
	using JV = hamon::ranges::join_with_view<View, Pattern>;

	int a0[] = {1};
	int a1[] = {2,3};
	int a2[] = {4,5,6};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	int a3[] = {-1,-2};
	Pattern pat(a3);

	// views::join_with(v)
	{
		auto jv = hamon::views::join_with(v, pat);
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(*jv.begin() == 1);
		VERIFY(*hamon::ranges::next(jv.begin(), 1) == -1);
	}
	// v | views::join_with
	{
		auto jv = v | hamon::views::join_with(pat);
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(*jv.begin() == 1);
		VERIFY(*hamon::ranges::next(jv.begin(), 1) == -1);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using A = hamon::array<hamon::array<hamon::array<int, 4>, 3>, 2>;
	A a
	{{
		{{
			{{11, 12, 13, 14}},
			{{21, 22, 23, 24}},
			{{31, 32, 33, 34}},
		}},
		{{
			{{11, 12, 13, 14}},
			{{21, 22, 23, 24}},
			{{31, 32, 33, 34}},
		}},
	}};

	using JV =
		hamon::ranges::join_with_view<
			hamon::ranges::join_view<hamon::ranges::ref_view<A>>,
			hamon::ranges::single_view<int>
		>;

	int const expected[] = {
		11, 12, 13, 14, -1,
		21, 22, 23, 24, -1,
		31, 32, 33, 34, -1,
		11, 12, 13, 14, -1,
		21, 22, 23, 24, -1,
		31, 32, 33, 34,
	};

	// nesting
	{
		auto jv_partial = a | hamon::views::join;
		auto jv = jv_partial | hamon::views::join_with(-1);
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(hamon::ranges::equal(jv, expected));
	}
	{
		auto jv = a | hamon::views::join | hamon::views::join_with(-1);
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(hamon::ranges::equal(jv, expected));
	}
	{
		auto join_twice = hamon::views::join | hamon::views::join_with(-1);
		auto jv = a | join_twice;
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(hamon::ranges::equal(jv, expected));

		static_assert(!CanBePiped<int(&)[2], decltype((join_twice))>::value, "");
		static_assert(!CanBePiped<int(&)[2][2], decltype((join_twice))>::value, "");
		static_assert( CanBePiped<int(&)[2][2][2], decltype((join_twice))>::value, "");
	}

	static_assert(!CanBePiped<int(&)[2], decltype((hamon::views::join_with(0)))>::value, "");
	static_assert( CanBePiped<int(&)[2][2], decltype((hamon::views::join_with(0)))>::value, "");
	static_assert(!CanBePiped<int(&)[2][2][2], decltype((hamon::views::join_with(0)))>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewAdaptorTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test02());
#else
	EXPECT_TRUE(test00());
	EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
#endif
}

}	// namespace adaptor_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
