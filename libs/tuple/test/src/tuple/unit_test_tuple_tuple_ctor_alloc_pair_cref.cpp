/**
 *	@file	unit_test_tuple_tuple_ctor_alloc_pair_cref.cpp
 *
 *	@brief	allocator_arg_t, Alloc const&, pair<U1, U2> const& を引数に取るコンストラクタのテスト
 *
 *	template<class Alloc, class U1, class U2>
 *	constexpr explicit(see below)
 *	tuple(allocator_arg_t, const Alloc& a, const pair<U1, U2>&);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_alloc_pair_cref_test
{

struct MyAlloc {};

struct ImplicitFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(int)
		: n(-1) {}

	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const& i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const&&) = delete;

	int n;
};

struct ImplicitLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int)
		: n(-1) {}

	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int&, MyAlloc const&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int&&, MyAlloc const&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int const& i, MyAlloc const&)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int const&&, MyAlloc const&) = delete;

	int n;
};

struct ImplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(int&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(int&&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(int const& i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(int const&&) = delete;

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

	HAMON_CXX11_CONSTEXPR ExplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR ExplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const& i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ExplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const&&)
		: n(-1) {}

	int n;
};

struct ExplicitLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc(int)
		: n(-1) {}

	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc(int&, MyAlloc const&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc(int&&, MyAlloc const&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitLastAlloc(int const& i, MyAlloc const&)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc(int const&&, MyAlloc const&)
		: n(-1) {}

	int n;
};

struct ExplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(int&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(int&&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitNoAlloc(int const& i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(int const&&)
		: n(-1) {}

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

	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const& i) noexcept
		: n(i) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const&&)
		: n(-1) {}

	int n;
};

struct NoThrowLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int)
		: n(-1) {}

	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int&, MyAlloc const&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int&&, MyAlloc const&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int const& i, MyAlloc const&) noexcept
		: n(i) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int const&&, MyAlloc const&)
		: n(-1) {}

	int n;
};

struct NoThrowNoAlloc
{
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(int&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(int&&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(int const& i) noexcept
		: n(i) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(int const&&)
		: n(-1) {}

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

static_assert(!hamon::is_constructible<hamon::tuple<int>,                                   hamon::allocator_arg_t, MyAlloc, hamon::pair<short, float> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int>,                              hamon::allocator_arg_t, MyAlloc, hamon::pair<short, float> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int, int, int>,                         hamon::allocator_arg_t, MyAlloc, hamon::pair<short, float> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> &>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> &&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitFirstAlloc, ExplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitNoAlloc, int>,                  hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor, ExplicitLastAlloc>,             hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<ExplicitFirstAlloc, NoCtor>,            hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor, int>,                           hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<int, int>,                              hamon::allocator_arg_t, MyAlloc, hamon::pair<short, float> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitNoAlloc, int>,                  hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitFirstAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc, ExplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitNoAlloc, int>,                  hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int, int>,                              hamon::allocator_arg_t, MyAlloc, hamon::pair<short, float> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc>,   hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowNoAlloc, int>,                   hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitFirstAlloc, NoThrowLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitNoAlloc, int>,                  hamon::allocator_arg_t, MyAlloc, hamon::pair<int, int> const&>::value, "");
#endif

GTEST_TEST(TupleTest, CtorAllocPairCRefTest)
{
	HAMON_CXX11_CONSTEXPR MyAlloc a{};
	{
		hamon::pair<short, float> const t1((short)1, 2.0f);
		hamon::tuple<int, double>  const t2(hamon::allocator_arg, a, t1);
		EXPECT_EQ(1, hamon::adl_get<0>(t2));
		EXPECT_EQ(2, hamon::adl_get<1>(t2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<short, float> const t1((short)1, 2.0f);
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, double>  const t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::adl_get<0>(t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::adl_get<1>(t2));
	}
	{
		hamon::pair<int, int> const t1(3, 4);
		hamon::tuple<ExplicitFirstAlloc, ExplicitLastAlloc> const t2(hamon::allocator_arg, a, t1);
		EXPECT_EQ(3, hamon::adl_get<0>(t2).n);
		EXPECT_EQ(4, hamon::adl_get<1>(t2).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> const t1(5, 6);
		HAMON_CXX11_CONSTEXPR hamon::tuple<ExplicitNoAlloc, ImplicitFirstAlloc> const t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::adl_get<0>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::adl_get<1>(t2).n);
	}
	{
		hamon::pair<int, int> const t1(7, 8);
		hamon::tuple<ImplicitLastAlloc, ImplicitNoAlloc> const t2(hamon::allocator_arg, a, t1);
		EXPECT_EQ(7, hamon::adl_get<0>(t2).n);
		EXPECT_EQ(8, hamon::adl_get<1>(t2).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> const t1(9, 10);
		HAMON_CXX11_CONSTEXPR hamon::tuple<NoThrowFirstAlloc, NoThrowLastAlloc> const t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9, hamon::adl_get<0>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::adl_get<1>(t2).n);
	}
	{
		hamon::pair<int, int> const t1(11, 12);
		hamon::tuple<NoThrowNoAlloc, int> const t2(hamon::allocator_arg, a, t1);
		EXPECT_EQ(11, hamon::adl_get<0>(t2).n);
		EXPECT_EQ(12, hamon::adl_get<1>(t2));
	}
}

}	// namespace ctor_alloc_pair_cref_test

}	// namespace hamon_tuple_test
