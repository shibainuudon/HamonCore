/**
 *	@file	unit_test_variant_ctor_in_place_type_args.cpp
 *
 *	@brief	variant(in_place_type_t<T>, Args&&...) のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/utility/in_place_type.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace ctor_in_place_type_args_test
{

static_assert( hamon::is_constructible<hamon::variant<int>, hamon::in_place_type_t<int>,   int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int>, hamon::in_place_type_t<float>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int>, hamon::in_place_type_t<int>,   std::string>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, int>, hamon::in_place_type_t<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, int>, hamon::in_place_type_t<float>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, long, int*>, hamon::in_place_type_t<int>, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, long, int*>, hamon::in_place_type_t<long>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, long, int*>, hamon::in_place_type_t<int*>, int*>::value, "");

static_assert( hamon::is_constructible<hamon::variant<std::string>, hamon::in_place_type_t<std::string>, char const*>::value, "");
static_assert( hamon::is_constructible<hamon::variant<std::string>, hamon::in_place_type_t<std::string>, char const*, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<std::string>, hamon::in_place_type_t<std::string>, int, char>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<std::string>, hamon::in_place_type_t<std::string>, int, char const*>::value, "");

struct Noexcept
{
	Noexcept(int) noexcept(true);
};

struct NotNoexcept
{
	NotNoexcept(int) noexcept(false);
};

static_assert( hamon::is_constructible<hamon::variant<Noexcept>,         hamon::in_place_type_t<Noexcept>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<NotNoexcept>,      hamon::in_place_type_t<NotNoexcept>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, Noexcept>,    hamon::in_place_type_t<Noexcept>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, NotNoexcept>, hamon::in_place_type_t<NotNoexcept>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, Noexcept>,    hamon::in_place_type_t<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, NotNoexcept>, hamon::in_place_type_t<int>, int>::value, "");

#if !defined(HAMON_USE_STD_VARIANT)
static_assert( hamon::is_nothrow_constructible<hamon::variant<Noexcept>,         hamon::in_place_type_t<Noexcept>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<NotNoexcept>,      hamon::in_place_type_t<NotNoexcept>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, Noexcept>,    hamon::in_place_type_t<Noexcept>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<int, NotNoexcept>, hamon::in_place_type_t<NotNoexcept>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, Noexcept>,    hamon::in_place_type_t<int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, NotNoexcept>, hamon::in_place_type_t<int>, int>::value, "");
#endif

GTEST_TEST(VariantTest, CtorInPlaceTypeArgsTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int> v(
			hamon::in_place_type_t<int>{}, 42);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, const int, long> v(
			hamon::in_place_type_t<int>{}, 45);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 45);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, const int, long> v(
			hamon::in_place_type_t<const int>{}, 46);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 1u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<1>(v), 46);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, const int, long> v(
			hamon::in_place_type_t<long>{}, 47);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 2u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<2>(v), 47);
	}
	{
		hamon::variant<std::string> v(
			hamon::in_place_type_t<std::string>{}, 3u, 'a');
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(hamon::adl_get<0>(v), "aaa");
	}
	{
		hamon::variant<int, char, std::string> v(
			hamon::in_place_type_t<int>{}, 4);
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(hamon::adl_get<0>(v), 4);
	}
	{
		hamon::variant<int, char, std::string> v(
			hamon::in_place_type_t<char>{}, 'a');
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(hamon::adl_get<1>(v), 'a');
	}
	{
		hamon::variant<int, char, std::string> v(
			hamon::in_place_type_t<std::string>{}, 4u, 'b');
		EXPECT_EQ(v.index(), 2u);
		EXPECT_EQ(hamon::adl_get<2>(v), "bbbb");
	}
}

}	// namespace ctor_in_place_type_args_test

}	// namespace hamon_variant_test
