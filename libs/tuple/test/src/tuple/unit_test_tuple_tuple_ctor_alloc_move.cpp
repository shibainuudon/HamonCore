/**
 *	@file	unit_test_tuple_tuple_ctor_alloc_move.cpp
 *
 *	@brief	allocator_arg_t, Alloc const&, tuple&& を引数に取るコンストラクタのテスト
 *
 *	template <typename Alloc>
 *	constexpr
 *	tuple(allocator_arg_t, Alloc const& a, tuple&&);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_alloc_move_test
{

struct MyAlloc {};

struct FirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR FirstAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR FirstAlloc(FirstAlloc&&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR FirstAlloc(hamon::allocator_arg_t, MyAlloc const&, FirstAlloc&&)
		: b(true) {}

	bool b;
};

struct LastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR LastAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR LastAlloc(LastAlloc&&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR LastAlloc(LastAlloc&&, MyAlloc const&)
		: b(true) {}

	bool b;
};

struct NoAlloc
{
	HAMON_CXX11_CONSTEXPR NoAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoAlloc(NoAlloc&&)
		: b(true) {}
	HAMON_CXX11_CONSTEXPR NoAlloc(hamon::allocator_arg_t, MyAlloc const&, NoAlloc&&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoAlloc(NoAlloc&&, MyAlloc const&)
		: b(false) {}

	bool b;
};

struct NoThrowFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(NoThrowFirstAlloc&&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, NoThrowFirstAlloc&&) noexcept
		: b(true) {}

	bool b;
};

struct NoThrowLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(NoThrowLastAlloc&&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(NoThrowLastAlloc&&, MyAlloc const&) noexcept
		: b(true) {}

	bool b;
};

struct NoThrowNoAlloc
{
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc()
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(NoThrowNoAlloc&&) noexcept
		: b(true) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(hamon::allocator_arg_t, MyAlloc const&, NoThrowNoAlloc&&)
		: b(false) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(NoThrowNoAlloc&&, MyAlloc const&)
		: b(false) {}

	bool b;
};

struct NoMove
{
	HAMON_CXX11_CONSTEXPR NoMove(NoMove&&) = delete;
};

static_assert( hamon::is_constructible<hamon::tuple<>,                  hamon::allocator_arg_t, MyAlloc, hamon::tuple<>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<>,                  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,               hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<FirstAlloc>,        hamon::allocator_arg_t, MyAlloc, hamon::tuple<FirstAlloc>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<LastAlloc>,         hamon::allocator_arg_t, MyAlloc, hamon::tuple<LastAlloc>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoAlloc>,           hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoAlloc>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowFirstAlloc>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowLastAlloc>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowNoAlloc>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoMove>,            hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoMove>&&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<FirstAlloc, LastAlloc, NoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<FirstAlloc, LastAlloc, NoAlloc>&&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<NoMove, LastAlloc, NoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<NoMove, LastAlloc, NoAlloc>&&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<FirstAlloc, NoMove, NoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<FirstAlloc, NoMove, NoAlloc>&&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<FirstAlloc, LastAlloc, NoMove>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<FirstAlloc, LastAlloc, NoMove>&&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::tuple<>,                  hamon::allocator_arg_t, MyAlloc, hamon::tuple<>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int>,               hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<FirstAlloc>,        hamon::allocator_arg_t, MyAlloc, hamon::tuple<FirstAlloc>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<LastAlloc>,         hamon::allocator_arg_t, MyAlloc, hamon::tuple<LastAlloc>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoAlloc>,           hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoAlloc>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowFirstAlloc>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowLastAlloc>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoThrowNoAlloc>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoMove>,            hamon::allocator_arg_t, MyAlloc, hamon::tuple<NoMove>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<FirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<FirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowFirstAlloc, LastAlloc, NoThrowNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<NoThrowFirstAlloc, LastAlloc, NoThrowNoAlloc>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoAlloc>&&>::value, "");

GTEST_TEST(TupleTest, CtorAllocMoveTest)
{
	HAMON_CXX11_CONSTEXPR MyAlloc a{};
	{
		hamon::tuple<> t1{};
		hamon::tuple<> t2(hamon::allocator_arg, a, hamon::move(t1));
		(void)t2;
	}
	{
		hamon::tuple<int> t1(42);
		hamon::tuple<int> t2(hamon::allocator_arg, a, hamon::move(t1));
		EXPECT_TRUE(hamon::adl_get<0>(t2) == 42);
	}
	{
		hamon::tuple<std::string, int> t1("hello", 43);
		hamon::tuple<std::string, int> t2(hamon::allocator_arg, a, hamon::move(t1));
		EXPECT_TRUE(hamon::adl_get<0>(t2) == "hello");
		EXPECT_TRUE(hamon::adl_get<1>(t2) == 43);
	}
	{
		hamon::tuple<FirstAlloc> t1;
		hamon::tuple<FirstAlloc> t2(hamon::allocator_arg, a, hamon::move(t1));
		EXPECT_TRUE(hamon::adl_get<0>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<0>(t2).b == true);
	}
	{
		hamon::tuple<LastAlloc, NoAlloc> t1;
		hamon::tuple<LastAlloc, NoAlloc> t2(hamon::allocator_arg, a, hamon::move(t1));
		EXPECT_TRUE(hamon::adl_get<0>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<1>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<0>(t2).b == true);
		EXPECT_TRUE(hamon::adl_get<1>(t2).b == true);
	}
	{
		hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc> t1;
		hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc> t2(hamon::allocator_arg, a, hamon::move(t1));
		EXPECT_TRUE(hamon::adl_get<0>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<1>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<2>(t1).b == false);
		EXPECT_TRUE(hamon::adl_get<0>(t2).b == true);
		EXPECT_TRUE(hamon::adl_get<1>(t2).b == true);
		EXPECT_TRUE(hamon::adl_get<2>(t2).b == true);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t1{};
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t2(hamon::allocator_arg, a, hamon::move(t1));
		(void)t2;
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t1(42);
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t2(hamon::allocator_arg, a, hamon::move(t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2) == 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> t1(0.5f, 43);
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> t2(hamon::allocator_arg, a, hamon::move(t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2) == 0.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t2) == 43);
	}
}

}	// namespace ctor_alloc_move_test

}	// namespace hamon_tuple_test
