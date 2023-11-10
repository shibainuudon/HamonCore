/**
 *	@file	unit_test_tuple_tuple_ctor_alloc_default.cpp
 *
 *	@brief	
 * 
 *	template<class Alloc>
 *	constexpr explicit(see below)
 *	tuple(allocator_arg_t, const Alloc& a);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_alloc_default_test
{

struct MyAlloc {};

struct ImplicitFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc() : n(1) {}
	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&) : n(2) {}

	int n;
};

struct ImplicitLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc() : n(3) {}
	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(MyAlloc const&) : n(4) {}

	int n;
};

struct ImplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc() : n(5) {}
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(hamon::allocator_arg_t, MyAlloc const&) : n(6) {}
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(MyAlloc const&) : n(7) {}

	int n;
};

struct ExplicitFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ExplicitFirstAlloc() : n(8) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&) : n(9) {}

	int n;
};

struct ExplicitLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc() : n(10) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitLastAlloc(MyAlloc const&) : n(11) {}

	int n;
};

struct ExplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR explicit ExplicitNoAlloc() : n(12) {}
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(hamon::allocator_arg_t, MyAlloc const&) : n(13) {}
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(MyAlloc const&) : n(14) {}

	int n;
};

struct NoThrowFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc() : n(15) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&) noexcept : n(16) {}

	int n;
};

struct NoThrowLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc() : n(17) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(MyAlloc const&) noexcept : n(18) {}

	int n;
};

struct NoThrowNoAlloc
{
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc() noexcept : n(19) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(hamon::allocator_arg_t, MyAlloc const&) : n(20) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(MyAlloc const&) : n(21) {}

	int n;
};

struct NoDefault
{
	HAMON_CXX11_CONSTEXPR NoDefault(int x) : n(x) {}
	int n;
};

static_assert( hamon::is_constructible<hamon::tuple<>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowFirstAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowNoAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoDefault>, hamon::allocator_arg_t, MyAlloc>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<int>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_constructible<hamon::tuple<>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowNoAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc>::value, "");
#endif

GTEST_TEST(TupleTest, CtorAllocDefaultTest)
{
	HAMON_CXX11_CONSTEXPR MyAlloc a{};
	{
		hamon::tuple<> t(hamon::allocator_arg, a);
		(void)t;
	}
	{
		hamon::tuple<int> t(hamon::allocator_arg, a);
		EXPECT_TRUE(hamon::adl_get<0>(t) == 0);
	}
	{
		hamon::tuple<hamon::string, int> t(hamon::allocator_arg, a);
		EXPECT_TRUE(hamon::adl_get<0>(t) == "");
		EXPECT_TRUE(hamon::adl_get<1>(t) == 0);
	}
	{
		hamon::tuple<ImplicitFirstAlloc> t(hamon::allocator_arg, a);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 2);
	}
	{
		hamon::tuple<ImplicitLastAlloc, int> t(hamon::allocator_arg, a);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 4);
		EXPECT_TRUE(hamon::adl_get<1>(t) == 0);
	}
	{
		hamon::tuple<ImplicitNoAlloc> t(hamon::allocator_arg, a);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 5);
	}
	{
		hamon::tuple<float, ExplicitFirstAlloc> t(hamon::allocator_arg, a);
		EXPECT_TRUE(hamon::adl_get<0>(t) == 0.0f);
		EXPECT_TRUE(hamon::adl_get<1>(t).n == 9);
	}
	{
		hamon::tuple<ExplicitLastAlloc, ExplicitNoAlloc, NoThrowFirstAlloc> t(hamon::allocator_arg, a);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 11);
		EXPECT_TRUE(hamon::adl_get<1>(t).n == 12);
		EXPECT_TRUE(hamon::adl_get<2>(t).n == 16);
	}
	{
		hamon::tuple<NoThrowLastAlloc> t(hamon::allocator_arg, a);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 18);
	}
	{
		hamon::tuple<NoThrowNoAlloc> t(hamon::allocator_arg, a);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 19);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t(hamon::allocator_arg, a);
		(void)t;
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t(hamon::allocator_arg, a);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> t(hamon::allocator_arg, a);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 0.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t) == 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>
			t(hamon::allocator_arg, a);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t).n == 5);
	}
}

}	// namespace ctor_alloc_default_test

}	// namespace hamon_tuple_test
