/**
 *	@file	unit_test_variant_ctor_in_place_index_args.cpp
 *
 *	@brief	variant(in_place_index_t<I>, Args&&...) のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/utility/in_place_index.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace ctor_in_place_index_args_test
{

static_assert( hamon::is_constructible<hamon::variant<int>, hamon::in_place_index_t<0>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int>, hamon::in_place_index_t<1>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int>, hamon::in_place_index_t<0>, std::string>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, int>, hamon::in_place_index_t<0>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, int>, hamon::in_place_index_t<1>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, int>, hamon::in_place_index_t<2>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, long, int*>, hamon::in_place_index_t<0>, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, long, int*>, hamon::in_place_index_t<1>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, long, int*>, hamon::in_place_index_t<2>, int*>::value, "");

static_assert( hamon::is_constructible<hamon::variant<std::string>, hamon::in_place_index_t<0>, char const*>::value, "");
static_assert( hamon::is_constructible<hamon::variant<std::string>, hamon::in_place_index_t<0>, char const*, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<std::string>, hamon::in_place_index_t<0>, int, char>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<std::string>, hamon::in_place_index_t<0>, int, char const*>::value, "");

struct Noexcept
{
	Noexcept(int) noexcept(true);
};

struct NotNoexcept
{
	NotNoexcept(int) noexcept(false);
};

static_assert( hamon::is_constructible<hamon::variant<Noexcept>,         hamon::in_place_index_t<0>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<NotNoexcept>,      hamon::in_place_index_t<0>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, Noexcept>,    hamon::in_place_index_t<0>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, NotNoexcept>, hamon::in_place_index_t<0>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, Noexcept>,    hamon::in_place_index_t<1>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, NotNoexcept>, hamon::in_place_index_t<1>, int>::value, "");

#if !defined(HAMON_USE_STD_VARIANT)
static_assert( hamon::is_nothrow_constructible<hamon::variant<Noexcept>,         hamon::in_place_index_t<0>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<NotNoexcept>,      hamon::in_place_index_t<0>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, Noexcept>,    hamon::in_place_index_t<0>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, NotNoexcept>, hamon::in_place_index_t<0>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, Noexcept>,    hamon::in_place_index_t<1>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<int, NotNoexcept>, hamon::in_place_index_t<1>, int>::value, "");
#endif

struct Vec2
{
	HAMON_CXX11_CONSTEXPR
	Vec2(float xx, float yy)
		: x(xx), y(yy) {}

	float x;
	float y;
};

GTEST_TEST(VariantTest, CtorInPlaceIndexArgsTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int> v(
			hamon::in_place_index_t<0>{}, 42);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, int> v(
			hamon::in_place_index_t<0>{}, 43);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 43);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, int> v(
			hamon::in_place_index_t<1>{}, 44);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 1u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<1>(v), 44);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, const int, long> v(
			hamon::in_place_index_t<0>{}, 45);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 45);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, const int, long> v(
			hamon::in_place_index_t<1>{}, 46);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 1u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<1>(v), 46);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, const int, long> v(
			hamon::in_place_index_t<2>{}, 47);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 2u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<2>(v), 47);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<Vec2> v(
			hamon::in_place_index_t<0>{}, 2.0f, 3.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v).x, 2.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v).y, 3.0f);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, Vec2> v(
			hamon::in_place_index_t<1>{}, 4.0f, 5.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 1u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<1>(v).x, 4.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<1>(v).y, 5.0f);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<float, int, Vec2> v(
			hamon::in_place_index_t<1>{}, 6);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 1u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<1>(v), 6);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<float, int, Vec2> v(
			hamon::in_place_index_t<2>{}, 6.0f, 7.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 2u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<2>(v).x, 6.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<2>(v).y, 7.0f);
	}
	{
		hamon::variant<std::string> v(
			hamon::in_place_index_t<0>{}, "hoge");
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(hamon::adl_get<0>(v), "hoge");
	}
	{
		hamon::variant<std::string> v(
			hamon::in_place_index_t<0>{}, 3u, 'a');
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(hamon::adl_get<0>(v), "aaa");
	}
	{
		hamon::variant<std::string, int> v(
			hamon::in_place_index_t<0>{}, 3u, 'a');
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(hamon::adl_get<0>(v), "aaa");
	}
	{
		hamon::variant<int, std::string, int> v(
			hamon::in_place_index_t<1>{}, 4u, 'b');
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(hamon::adl_get<1>(v), "bbbb");
	}
	{
		hamon::variant<int, char, std::string> v(
			hamon::in_place_index_t<2>{}, 4u, 'b');
		EXPECT_EQ(v.index(), 2u);
		EXPECT_EQ(hamon::adl_get<2>(v), "bbbb");
	}
	{
		hamon::variant<int, char, std::string, float> v(
			hamon::in_place_index_t<2>{}, 4u, 'b');
		EXPECT_EQ(v.index(), 2u);
		EXPECT_EQ(hamon::adl_get<2>(v), "bbbb");
	}
}

}	// namespace ctor_in_place_index_args_test

}	// namespace hamon_variant_test
