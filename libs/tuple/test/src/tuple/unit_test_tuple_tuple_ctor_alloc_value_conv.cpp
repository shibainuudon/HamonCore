/**
 *	@file	unit_test_tuple_tuple_ctor_alloc_value_conv.cpp
 *
 *	@brief	allocator_arg_t, Alloc const&, UTypes&&... を引数に取るコンストラクタのテスト
 *
 *	template <typename Alloc>
 *	constexpr explicit(see below)
 *	tuple(allocator_arg_t, Alloc const& a, UTypes&&...);
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

namespace ctor_alloc_value_conv_test
{

struct MyAlloc {};

struct ImplicitFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(int)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int i)
		: n(i) {}

	int n;
};

struct ImplicitLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int i, MyAlloc const&)
		: n(i) {}

	int n;
};

struct ImplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(int i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(hamon::allocator_arg_t, MyAlloc const&, int)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(int, MyAlloc const&)
		: n(-1) {}

	int n;
};

struct ExplicitFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ExplicitFirstAlloc(int)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int i)
		: n(i) {}

	int n;
};

struct ExplicitLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc(int)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitLastAlloc(int i, MyAlloc const&)
		: n(i) {}

	int n;
};

struct ExplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR explicit ExplicitNoAlloc(int i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(hamon::allocator_arg_t, MyAlloc const&, int)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(int, MyAlloc const&)
		: n(-1) {}

	int n;
};

struct NoThrowFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(int)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int i) noexcept
		: n(i) {}

	int n;
};

struct NoThrowLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int i, MyAlloc const&) noexcept
		: n(i) {}

	int n;
};

struct NoThrowNoAlloc
{
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(int i) noexcept
		: n(i) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(hamon::allocator_arg_t, MyAlloc const&, int)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(int, MyAlloc const&)
		: n(-1) {}

	int n;
};

struct NoCtor
{
	HAMON_CXX11_CONSTEXPR NoCtor(int) = delete;
};

static_assert(!hamon::is_constructible<hamon::tuple<>,                   hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int const>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowFirstAlloc>,  hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowLastAlloc>,   hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowNoAlloc>,     hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor>,             hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int>,           hamon::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int, int>, hamon::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, int, int>, hamon::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor, int, int>, hamon::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int, int, NoCtor>, hamon::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ExplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ExplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ExplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ExplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc>,  hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowLastAlloc>,   hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowNoAlloc>,     hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int, int>, hamon::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert( hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowLastAlloc, NoThrowLastAlloc, NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<ImplicitLastAlloc, NoThrowLastAlloc, NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowLastAlloc, NoThrowLastAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	int, int, int>::value, "");
#endif

GTEST_TEST(TupleTest, CtorAllocValueConvTest)
{
	HAMON_CXX11_CONSTEXPR MyAlloc a{};
	{
		hamon::tuple<int> t(hamon::allocator_arg, a, 42);
		EXPECT_TRUE(hamon::adl_get<0>(t) == 42);
	}
	{
		hamon::tuple<hamon::string, int> t(hamon::allocator_arg, a, "hello", 43);
		EXPECT_TRUE(hamon::adl_get<0>(t) == "hello");
		EXPECT_TRUE(hamon::adl_get<1>(t) == 43);
	}
	{
		hamon::tuple<ImplicitFirstAlloc> t(hamon::allocator_arg, a, 10);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 10);
	}
	{
		hamon::tuple<ImplicitLastAlloc, int> t(hamon::allocator_arg, a, 1, 44);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 1);
		EXPECT_TRUE(hamon::adl_get<1>(t) == 44);
	}
	{
		hamon::tuple<ImplicitNoAlloc, float, ExplicitFirstAlloc> t(hamon::allocator_arg, a, 2, 2.5f, 3);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 2);
		EXPECT_TRUE(hamon::adl_get<1>(t) == 2.5f);
		EXPECT_TRUE(hamon::adl_get<2>(t).n == 3);
	}
	{
		hamon::tuple<ExplicitLastAlloc, ExplicitNoAlloc, NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>
			t(hamon::allocator_arg, a, 1, 2, 3, 4, 5);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 1);
		EXPECT_TRUE(hamon::adl_get<1>(t).n == 2);
		EXPECT_TRUE(hamon::adl_get<2>(t).n == 3);
		EXPECT_TRUE(hamon::adl_get<3>(t).n == 4);
		EXPECT_TRUE(hamon::adl_get<4>(t).n == 5);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t(hamon::allocator_arg, a, 42);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> t(hamon::allocator_arg, a, 2.0f, 43);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t) == 43);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>
			t(hamon::allocator_arg, a, 10, 11, 12);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 10);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 11);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t).n == 12);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<ExplicitLastAlloc, ExplicitNoAlloc, NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>
			t(hamon::allocator_arg, a, 1, 2, 3, 4, 5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t).n == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<3>(t).n == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<4>(t).n == 5);
	}
}

}	// namespace ctor_alloc_value_conv_test

}	// namespace hamon_tuple_test
