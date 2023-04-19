/**
 *	@file	unit_test_tuple_tuple_cat.cpp
 *
 *	@brief	tuple_cat のテスト
 *
 *	template<tuple-like... Tuples>
 *	constexpr tuple<CTypes...> tuple_cat(Tuples&&... tpls);
 */

#include <hamon/tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace tuple_cat_test
{

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat()),
	hamon::tuple<>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<>>())),
	hamon::tuple<>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<>>(),
		hamon::declval<hamon::tuple<>>())),
	hamon::tuple<>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<>>(),
		hamon::declval<hamon::tuple<>>(),
		hamon::declval<hamon::tuple<>>())),
	hamon::tuple<>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<>&>())),
	hamon::tuple<>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<> const>())),
	hamon::tuple<>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<> const&>())),
	hamon::tuple<>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<int>>())),
	hamon::tuple<int>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<int>&>())),
	hamon::tuple<int>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<int> const>())),
	hamon::tuple<int>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<int> const&>())),
	hamon::tuple<int>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<int const>>())),
	hamon::tuple<int const>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<int&>>())),
	hamon::tuple<int&>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<int const&>>())),
	hamon::tuple<int const&>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::pair<int, bool>>())),
	hamon::tuple<int, bool>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::pair<int const, bool>&>())),
	hamon::tuple<int const, bool>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::pair<int, bool&> const>())),
	hamon::tuple<int, bool&>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::pair<int, bool> const&>())),
	hamon::tuple<int, bool>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::array<int, 3>>())),
	hamon::tuple<int, int, int>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::array<float, 3>&>())),
	hamon::tuple<float, float, float>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::array<long, 3> const>())),
	hamon::tuple<long, long, long>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::array<double, 3> const&>())),
	hamon::tuple<double, double, double>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::array<int const, 3>>())),
	hamon::tuple<int const, int const, int const>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::array<float&, 2>>())),
	hamon::tuple<float&, float&>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<>>(),
		hamon::declval<hamon::array<char, 0>>(),
		hamon::declval<hamon::array<int, 0>>(),
		hamon::declval<hamon::tuple<>>())),
	hamon::tuple<>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<int>>(),
		hamon::declval<hamon::tuple<double>>())),
	hamon::tuple<int, double>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::tuple<int>>(),
		hamon::declval<hamon::tuple<double>>(),
		hamon::declval<hamon::tuple<const long&>>())),
	hamon::tuple<int, double, const long&>>::value, "");

static_assert(hamon::is_same<
	decltype(hamon::tuple_cat(
		hamon::declval<hamon::array<wchar_t, 3>&>(),
		hamon::declval<hamon::tuple<double>>(),
		hamon::declval<hamon::tuple<>>(),
		hamon::declval<hamon::tuple<unsigned&>>(),
		hamon::declval<hamon::pair<bool, std::nullptr_t>>())),
	hamon::tuple<wchar_t, wchar_t, wchar_t, double, unsigned&, bool, std::nullptr_t>>::value, "");

GTEST_TEST(TupleTest, TupleCatTest)
{
	using std::get;
	{
		hamon::tuple<> t1;
		auto t2 = hamon::tuple_cat(t1);
		static_assert(hamon::is_same<decltype(t2), hamon::tuple<>>::value, "");
	}
	{
		hamon::tuple<int>          t1(1);
		hamon::tuple<char, double> t2('a', 3.5);
		auto t3 = hamon::tuple_cat(t1, t2);
		static_assert(hamon::is_same<decltype(t3), hamon::tuple<int, char, double>>::value, "");
		EXPECT_TRUE(get<0>(t3) == 1);
		EXPECT_TRUE(get<1>(t3) == 'a');
		EXPECT_TRUE(get<2>(t3) == 3.5);
	}
	{
		hamon::array<int, 3> a {{1,2,3}};
		hamon::pair<float, char> p { 0.5f, 'b' };
		hamon::tuple<double, short, long> t(1.5, 4, 5);
		auto t2 = hamon::tuple_cat(a, hamon::move(p), t);
		static_assert(hamon::is_same<decltype(t2),
			hamon::tuple<int, int, int, float, char, double, short, long>>::value, "");
		EXPECT_TRUE(get<0>(t2) == 1);
		EXPECT_TRUE(get<1>(t2) == 2);
		EXPECT_TRUE(get<2>(t2) == 3);
		EXPECT_TRUE(get<3>(t2) == 0.5f);
		EXPECT_TRUE(get<4>(t2) == 'b');
		EXPECT_TRUE(get<5>(t2) == 1.5);
		EXPECT_TRUE(get<6>(t2) == 4);
		EXPECT_TRUE(get<7>(t2) == 5);
	}

	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t1;
		HAMON_CXX11_CONSTEXPR auto t2 = hamon::tuple_cat(t1);
		static_assert(hamon::is_same<decltype(t2), hamon::tuple<> const>::value, "");
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int>          t1(1);
		HAMON_CXX11_CONSTEXPR hamon::tuple<char, double> t2('a', 3.5);
		HAMON_CXX11_CONSTEXPR auto t3 = hamon::tuple_cat(t1, t2);
		static_assert(hamon::is_same<decltype(t3), hamon::tuple<int, char, double> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t3) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t3) == 'a');
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<2>(t3) == 3.5);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 3> a {{1,2,3}};
		HAMON_CXX11_CONSTEXPR hamon::pair<float, char> p { 0.5f, 'b' };
		HAMON_CXX11_CONSTEXPR hamon::tuple<double, short, long> t(1.5, 4, 5);
		HAMON_CXX11_CONSTEXPR auto t2 = hamon::tuple_cat(a, hamon::move(p), t);
		static_assert(hamon::is_same<decltype(t2),
			hamon::tuple<int, int, int, float, char, double, short, long> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t2) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t2) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<2>(t2) == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<3>(t2) == 0.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<4>(t2) == 'b');
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<5>(t2) == 1.5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<6>(t2) == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<7>(t2) == 5);
	}
}

}	// namespace tuple_cat_test

}	// namespace hamon_tuple_test
