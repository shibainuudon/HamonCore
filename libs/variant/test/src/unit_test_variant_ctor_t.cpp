/**
 *	@file	unit_test_variant_ctor_t.cpp
 *
 *	@brief	variant(T&&) のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <string>
#include <memory>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace ctor_t_test
{

static_assert( hamon::is_constructible<hamon::variant<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int>, unsigned int>::value, "narrowing conversions");
static_assert(!hamon::is_constructible<hamon::variant<unsigned int>, int>::value, "narrowing conversions");
static_assert( hamon::is_constructible<hamon::variant<int, long>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, long>, long>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, int>, int>::value, "repeated");
static_assert(!hamon::is_constructible<hamon::variant<int, float, int>, int>::value, "repeated");
static_assert( hamon::is_constructible<hamon::variant<int, float, int>, float>::value, "");
static_assert( hamon::is_constructible<hamon::variant<long>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<long long>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<long, long long>, int>::value, "ambiguous");
static_assert( hamon::is_constructible<hamon::variant<std::string>, const char*>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<std::string, std::string>, const char*>::value, "ambiguous");
static_assert(!hamon::is_constructible<hamon::variant<std::string, void*>, int>::value, "no matching constructor");
static_assert(!hamon::is_constructible<hamon::variant<std::unique_ptr<int>, bool>, std::unique_ptr<char>>::value, "no explicit bool in constructor");
static_assert(!hamon::is_constructible<hamon::variant<std::unique_ptr<int>, int>, void*>::value, "");

struct X {};
struct Y { operator X(); };
static_assert( hamon::is_constructible<hamon::variant<X>, Y>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<Y>, X>::value, "");

struct Noexcept
{
	Noexcept(int) noexcept(true) {}
};

struct NotNoexcept
{
	NotNoexcept(int) noexcept(false) {}
};

static_assert( hamon::is_constructible<hamon::variant<Noexcept>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<NotNoexcept>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<Noexcept>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<NotNoexcept>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, Noexcept>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, NotNoexcept>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, Noexcept>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, NotNoexcept>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<float, Noexcept>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<float, NotNoexcept>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<float, Noexcept>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<float, NotNoexcept>, int>::value, "");

struct AnyConstructible { template <typename T> constexpr AnyConstructible(T&&) {} };
struct NoConstructible { NoConstructible() = delete; };

static_assert( hamon::is_constructible<hamon::variant<AnyConstructible>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<NoConstructible>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<AnyConstructible, NoConstructible>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<AnyConstructible, NoConstructible>, float>::value, "");
static_assert( hamon::is_constructible<hamon::variant<AnyConstructible, NoConstructible>, std::string>::value, "");
static_assert( hamon::is_constructible<hamon::variant<NoConstructible, AnyConstructible>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<NoConstructible, AnyConstructible>, float>::value, "");
static_assert( hamon::is_constructible<hamon::variant<NoConstructible, AnyConstructible>, std::string>::value, "");

template <typename T>
struct RValueConvertibleFrom { constexpr RValueConvertibleFrom(T&&) {} };

GTEST_TEST(VariantTest, CtorTTest)
{
	using std::get;
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int> v(42);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(get<0>(v), 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<float> v{2.5f};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(get<0>(v), 2.5f);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v{43};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(get<0>(v), 43);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v{3.5f};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 1u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(get<1>(v), 3.5f);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<bool const, int> v = true;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(get<0>(v), true);
	}
	{
		hamon::variant<std::string, int const> v("foo");
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v), "foo");
	}
	{
		hamon::variant<float, std::unique_ptr<int>> v(nullptr);
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(get<1>(v), nullptr);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<RValueConvertibleFrom<int>> v(42);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 0u);
	}
	{
		HAMON_CXX11_CONSTEXPR int x = 42;
		HAMON_CXX11_CONSTEXPR hamon::variant<RValueConvertibleFrom<int>, AnyConstructible> v(x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v.index(), 1u);
	}
}

}	// namespace ctor_t_test

}	// namespace hamon_variant_test
