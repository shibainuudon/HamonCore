/**
 *	@file	unit_test_ranges_join_view_adaptor.cpp
 *
 *	@brief	views::join のテスト
 *
 *	hamon::views::join
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
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
namespace join_view_test
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

	using JV = hamon::ranges::join_view<hamon::ranges::ref_view<A>>;

	// views::join(v)
	{
		auto jv = hamon::views::join(a);
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(*jv.begin() == 11);
		VERIFY(*hamon::ranges::next(jv.begin(), 2) == 21);
		VERIFY(hamon::ranges::next(jv.begin(), 6) == jv.end());
	}
	// v | views::join
	{
		auto jv = a | hamon::views::join;
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(*jv.begin() == 11);
		VERIFY(*hamon::ranges::next(jv.begin(), 2) == 21);
		VERIFY(hamon::ranges::next(jv.begin(), 6) == jv.end());
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a0[] = {1,2,3};
	int a1[] = {4,5};
	int a2[] = {6,7,8,9};
	using InnerView = test_forward_view<int>;
	using View = test_forward_view<InnerView>;
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	
	using JV = hamon::ranges::join_view<View>;
	
	// views::join(v)
	{
		auto jv = hamon::views::join(v);
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(*jv.begin() == 1);
		VERIFY(hamon::ranges::next(jv.begin(), 9) == jv.end());
	}
	// v | views::join
	{
		auto jv = v | hamon::views::join;
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(*jv.begin() == 1);
		VERIFY(hamon::ranges::next(jv.begin(), 9) == jv.end());
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

	using JV = hamon::ranges::join_view<hamon::ranges::join_view<hamon::ranges::ref_view<A>>>;

	// nesting
	{
		auto jv_partial = a | hamon::views::join;
		auto jv = jv_partial | hamon::views::join;
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(&(*jv.begin()) == &a[0][0][0]);
		VERIFY(hamon::ranges::next(jv.begin(), 24) == jv.end());
	}
	{
		auto jv = a | hamon::views::join | hamon::views::join;
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(&(*jv.begin()) == &a[0][0][0]);
		VERIFY(hamon::ranges::next(jv.begin(), 24) == jv.end());
	}
	{
		auto join_twice = hamon::views::join | hamon::views::join;
		auto jv = a | join_twice;
		static_assert(hamon::is_same<decltype(jv), JV>::value, "");
		VERIFY(&(*jv.begin()) == &a[0][0][0]);
		VERIFY(hamon::ranges::next(jv.begin(), 24) == jv.end());

		static_assert(!CanBePiped<int(&)[2], decltype((join_twice))>::value, "");
		static_assert(!CanBePiped<int(&)[2][2], decltype((join_twice))>::value, "");
		static_assert( CanBePiped<int(&)[2][2][2], decltype((join_twice))>::value, "");
	}

	static_assert(!CanBePiped<int(&)[2], decltype((hamon::views::join))>::value, "");
	static_assert( CanBePiped<int(&)[2][2], decltype((hamon::views::join))>::value, "");
	static_assert( CanBePiped<int(&)[2][2][2], decltype((hamon::views::join))>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace adaptor_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
