/**
 *	@file	unit_test_tuple_tuple_ctor_alloc_copy.cpp
 *
 *	@brief	allocator_arg_t, Alloc const&, tuple const& を引数に取るコンストラクタのテスト
 *
 *	template <typename Alloc>
 *	constexpr
 *	tuple(allocator_arg_t, Alloc const& a, tuple const&);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_alloc_copy_test
{

struct MyAlloc {};

struct FirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR FirstAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR FirstAlloc(FirstAlloc const&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, FirstAlloc const&)
		: b(true) {}

	bool b;
};

struct LastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR LastAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR LastAlloc(LastAlloc const&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR LastAlloc(LastAlloc const&, MyAlloc const&)
		: b(true) {}

	bool b;
};

struct NoAlloc
{
	HAMON_CXX11_CONSTEXPR NoAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoAlloc(NoAlloc const&)
		: b(true) {}
	HAMON_CXX11_CONSTEXPR NoAlloc(hamon::allocator_arg_t, MyAlloc const&, NoAlloc const&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoAlloc(NoAlloc const&, MyAlloc const&)
		: b(false) {}

	bool b;
};

struct NoThrowFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(NoThrowFirstAlloc const&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, NoThrowFirstAlloc const&) noexcept
		: b(true) {}

	bool b;
};

struct NoThrowLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(NoThrowLastAlloc const&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(NoThrowLastAlloc const&, MyAlloc const&) noexcept
		: b(true) {}

	bool b;
};

struct NoThrowNoAlloc
{
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(NoThrowNoAlloc const&) noexcept
		: b(true) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(hamon::allocator_arg_t, MyAlloc const&, NoThrowNoAlloc const&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(NoThrowNoAlloc const&, MyAlloc const&)
		: b(false) {}

	bool b;
};

struct NoCopy
{
	HAMON_CXX11_CONSTEXPR NoCopy(NoCopy const&) = delete;
};

static_assert( hamon::is_constructible<hamon::tuple<>,                  hamon::allocator_arg_t, MyAlloc, hamon::tuple<> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<>,                  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,               hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<FirstAlloc>,        hamon::allocator_arg_t, MyAlloc, hamon::tuple<FirstAlloc> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<LastAlloc>,         hamon::allocator_arg_t, MyAlloc, hamon::tuple<LastAlloc> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoAlloc>,           hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoAlloc> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowFirstAlloc> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowLastAlloc> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowNoAlloc> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy>,            hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoCopy> const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<FirstAlloc, LastAlloc, NoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<FirstAlloc, LastAlloc, NoAlloc> const&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<NoCopy, LastAlloc, NoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<NoCopy, LastAlloc, NoAlloc> const&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<FirstAlloc, NoCopy, NoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<FirstAlloc, NoCopy, NoAlloc> const&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<FirstAlloc, LastAlloc, NoCopy>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<FirstAlloc, LastAlloc, NoCopy> const&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::tuple<>,                  hamon::allocator_arg_t, MyAlloc, hamon::tuple<> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int>,               hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<FirstAlloc>,        hamon::allocator_arg_t, MyAlloc, hamon::tuple<FirstAlloc> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<LastAlloc>,         hamon::allocator_arg_t, MyAlloc, hamon::tuple<LastAlloc> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoAlloc>,           hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoAlloc> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowFirstAlloc> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowLastAlloc> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowNoAlloc> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoCopy>,            hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoCopy> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<FirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<FirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowFirstAlloc, LastAlloc, NoThrowNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<NoThrowFirstAlloc, LastAlloc, NoThrowNoAlloc> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoAlloc> const&>::value, "");

GTEST_TEST(TupleTest, CtorAllocCopyTest)
{
	HAMON_CXX11_CONSTEXPR MyAlloc a{};
	{
		hamon::tuple<> const t1{};
		hamon::tuple<> const t2(hamon::allocator_arg, a, t1);
		(void)t2;
	}
	{
		hamon::tuple<int> const t1(42);
		hamon::tuple<int> const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t2) == 42);
	}
	{
		hamon::tuple<std::string, int> const t1("hello", 43);
		hamon::tuple<std::string, int> const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t2) == "hello");
		EXPECT_TRUE(hamon::adl_get<1>(t2) == 43);
	}
	{
		hamon::tuple<FirstAlloc> const t1;
		hamon::tuple<FirstAlloc> const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<0>(t2).b == true);
	}
	{
		hamon::tuple<LastAlloc, NoAlloc> const t1;
		hamon::tuple<LastAlloc, NoAlloc> const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<1>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<0>(t2).b == true);
		EXPECT_TRUE(hamon::adl_get<1>(t2).b == true);
	}
	{
		hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc> const t1;
		hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc> const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<1>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<2>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<0>(t2).b == true);
		EXPECT_TRUE(hamon::adl_get<1>(t2).b == true);
		EXPECT_TRUE(hamon::adl_get<2>(t2).b == true);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t1{};
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t2(hamon::allocator_arg, a, t1);
		(void)t2;
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t1(42);
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2) == 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> t1(0.5f, 43);
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2) == 0.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t2) == 43);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<FirstAlloc> t1;
		HAMON_CXX11_CONSTEXPR hamon::tuple<FirstAlloc> t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t1).b == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2).b == true);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<LastAlloc, NoAlloc> t1;
		HAMON_CXX11_CONSTEXPR hamon::tuple<LastAlloc, NoAlloc> t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t1).b == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t1).b == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2).b == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t2).b == true);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc> t1;
		HAMON_CXX11_CONSTEXPR hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc> t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t1).b == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t1).b == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t1).b == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2).b == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t2).b == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t2).b == true);
	}
}

}	// namespace ctor_alloc_copy_test

}	// namespace hamon_tuple_test
