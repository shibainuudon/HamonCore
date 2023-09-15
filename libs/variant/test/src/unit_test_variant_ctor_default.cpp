/**
 *	@file	unit_test_variant_ctor_default.cpp
 *
 *	@brief	variant() のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace ctor_default_test
{

struct DefaultConstructible
{
	constexpr DefaultConstructible() : value(42) {}
	int value;
};

struct NonDefaultConstructible
{
	constexpr NonDefaultConstructible(int) {}
};

struct Noexcept
{
	Noexcept() noexcept(true) {}
};

struct NotNoexcept
{
	NotNoexcept() noexcept(false) {}
};

static_assert( hamon::is_default_constructible<hamon::variant<int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::variant<hamon::monostate>>::value, "");
static_assert( hamon::is_default_constructible<hamon::variant<DefaultConstructible>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::variant<NonDefaultConstructible>>::value, "");
static_assert( hamon::is_default_constructible<hamon::variant<Noexcept>>::value, "");
static_assert( hamon::is_default_constructible<hamon::variant<NotNoexcept>>::value, "");
static_assert( hamon::is_default_constructible<hamon::variant<int, NonDefaultConstructible>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::variant<NonDefaultConstructible, int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::variant<hamon::monostate, NonDefaultConstructible>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::variant<NonDefaultConstructible, hamon::monostate>>::value, "");
static_assert( hamon::is_default_constructible<hamon::variant<int, char, float, hamon::monostate>>::value, "");

static_assert( hamon::is_nothrow_default_constructible<hamon::variant<int>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::variant<hamon::monostate>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::variant<Noexcept>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::variant<NotNoexcept>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::variant<int, Noexcept>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::variant<Noexcept, int>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::variant<int, NotNoexcept>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::variant<NotNoexcept, int>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::variant<hamon::monostate, NotNoexcept>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::variant<NotNoexcept, hamon::monostate>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::variant<NotNoexcept, int, char, Noexcept>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::variant<int, char, NotNoexcept, Noexcept, hamon::monostate>>::value, "");

#if !defined(HAMON_NO_EXCEPTIONS)

struct ThrowOnDefaultCtor
{
	ThrowOnDefaultCtor() { throw 42; }
};

#endif

GTEST_TEST(VariantTest, CtorDefaultTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int> v;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<DefaultConstructible> v;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v).value, 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<float, int> v;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 0.0f);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, DefaultConstructible> v;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, NonDefaultConstructible> v;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, char, float, long, double, DefaultConstructible, NonDefaultConstructible> v;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v), 0);
	}
	{
		hamon::variant<hamon::string> v;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(hamon::adl_get<0>(v).length(), 0u);
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using V = hamon::variant<ThrowOnDefaultCtor, int>;
		EXPECT_THROW(V v, int);
	}
#endif
}

}	// namespace ctor_default_test

}	// namespace hamon_variant_test
