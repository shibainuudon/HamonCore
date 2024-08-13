/**
 *	@file	unit_test_variant_ctor_in_place_type_init_list_args.cpp
 *
 *	@brief	variant(in_place_type_t<T>, initializer_list<U>, Args&&...) のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/utility/in_place_type_t.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace ctor_in_place_type_init_list_args_test
{

struct X
{
	hamon::size_t m_size;
	HAMON_CXX14_CONSTEXPR X(std::initializer_list<int> il)
		: m_size(il.size()) {}
};

struct Y
{
	hamon::size_t m_size;
	int           m_value;
	HAMON_CXX14_CONSTEXPR Y(std::initializer_list<int> il, int v)
		: m_size(il.size()), m_value(v) {}
};

static_assert(!hamon::is_constructible<hamon::variant<int>, hamon::in_place_type_t<int>, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int>, hamon::in_place_type_t<char>, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<X>, hamon::in_place_type_t<X>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<X>, hamon::in_place_type_t<X>, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<X>, hamon::in_place_type_t<int>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<Y>, hamon::in_place_type_t<Y>, std::initializer_list<int>>::value, "");
static_assert( hamon::is_constructible<hamon::variant<Y>, hamon::in_place_type_t<Y>, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<Y>, hamon::in_place_type_t<int>, std::initializer_list<int>, int>::value, "");

static_assert(!hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<int>, std::initializer_list<int>>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<X>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<X>, std::initializer_list<char>>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<Y>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<long>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<int>, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<X>, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<Y>, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<Y>, std::initializer_list<int>, char>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<Y>, std::initializer_list<char>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<int, X, Y>, hamon::in_place_type_t<long>, std::initializer_list<int>, int>::value, "");

static_assert(!hamon::is_constructible<hamon::variant<X, int, X>, hamon::in_place_type_t<X>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::variant<Y, Y, int>, hamon::in_place_type_t<Y>, std::initializer_list<int>, int>::value, "");

struct Noexcept1
{
	Noexcept1(std::initializer_list<int>) noexcept(true);
	Noexcept1(std::initializer_list<int>, int) noexcept(false);
};

struct Noexcept2
{
	Noexcept2(std::initializer_list<int>) noexcept(false);
	Noexcept2(std::initializer_list<int>, int) noexcept(true);
};

static_assert( hamon::is_constructible<hamon::variant<Noexcept1>, hamon::in_place_type_t<Noexcept1>, std::initializer_list<int>>::value, "");
static_assert( hamon::is_constructible<hamon::variant<Noexcept2>, hamon::in_place_type_t<Noexcept2>, std::initializer_list<int>>::value, "");
static_assert( hamon::is_constructible<hamon::variant<Noexcept1>, hamon::in_place_type_t<Noexcept1>, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<Noexcept2>, hamon::in_place_type_t<Noexcept2>, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, Noexcept1>, hamon::in_place_type_t<Noexcept1>, std::initializer_list<int>>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, Noexcept2>, hamon::in_place_type_t<Noexcept2>, std::initializer_list<int>>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, Noexcept1>, hamon::in_place_type_t<Noexcept1>, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::variant<int, Noexcept2>, hamon::in_place_type_t<Noexcept2>, std::initializer_list<int>, int>::value, "");

#if !defined(HAMON_USE_STD_VARIANT)
static_assert( hamon::is_nothrow_constructible<hamon::variant<Noexcept1>, hamon::in_place_type_t<Noexcept1>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<Noexcept2>, hamon::in_place_type_t<Noexcept2>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<Noexcept1>, hamon::in_place_type_t<Noexcept1>, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<Noexcept2>, hamon::in_place_type_t<Noexcept2>, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, Noexcept1>, hamon::in_place_type_t<Noexcept1>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<int, Noexcept2>, hamon::in_place_type_t<Noexcept2>, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::variant<int, Noexcept1>, hamon::in_place_type_t<Noexcept1>, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::variant<int, Noexcept2>, hamon::in_place_type_t<Noexcept2>, std::initializer_list<int>, int>::value, "");
#endif

GTEST_TEST(VariantTest, CtorInPlaceTypeInitListArgsTest)
{
	{
		HAMON_CXX14_CONSTEXPR hamon::variant<int, X, Y> v(hamon::in_place_type_t<X>{}, {1,2,3});
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(v.index(), 1u);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::adl_get<1>(v).m_size, 3u);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::variant<int, X, Y> v(hamon::in_place_type_t<Y>{}, {1,2,3}, 42);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(v.index(), 2u);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::adl_get<2>(v).m_size, 3u);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::adl_get<2>(v).m_value, 42);
	}
	{
		hamon::variant<hamon::string> v(hamon::in_place_type_t<hamon::string>{}, {'H', 'e', 'l', 'l', 'o'});
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(hamon::adl_get<0>(v), "Hello");
	}
	{
		hamon::variant<hamon::string> v(hamon::in_place_type_t<hamon::string>{}, {'H', 'e', 'l', 'l', 'o'}, hamon::allocator<char>{});
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(hamon::adl_get<0>(v), "Hello");
	}
	{
		hamon::variant<int, hamon::string> v(hamon::in_place_type_t<hamon::string>{}, {'H', 'e', 'l', 'l', 'o'});
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(hamon::adl_get<1>(v), "Hello");
	}
	{
		hamon::variant<int, char, hamon::string> v(hamon::in_place_type_t<hamon::string>{}, {'H', 'e', 'l', 'l', 'o'}, hamon::allocator<char>{});
		EXPECT_EQ(v.index(), 2u);
		EXPECT_EQ(hamon::adl_get<2>(v), "Hello");
	}
}

}	// namespace ctor_in_place_type_init_list_args_test

}	// namespace hamon_variant_test
