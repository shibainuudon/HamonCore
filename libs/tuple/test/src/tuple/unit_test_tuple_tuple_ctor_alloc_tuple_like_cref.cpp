/**
 *	@file	unit_test_tuple_tuple_ctor_alloc_tuple_like_cref.cpp
 *
 *	@brief	allocator_arg_t, Alloc const&, tuple-likeなオブジェクトからのコンストラクタのテスト
 *
 *	template<class Alloc, tuple-like UTuple>
 *	constexpr explicit(see below)
 *	tuple(allocator_arg_t, const Alloc& a, UTuple&&);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/array.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_alloc_tuple_like_cref_test
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

static_assert( hamon::is_constructible<hamon::tuple<>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 0> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 1> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int>,           hamon::allocator_arg_t, MyAlloc, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int>,      hamon::allocator_arg_t, MyAlloc, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int, int, int>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int, int>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
#if !defined(HAMON_USE_STD_TUPLE)
static_assert(!hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 1> &>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 1> &&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 1> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 1> const&&>::value, "");
#endif
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor,             ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, NoCtor,            ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, NoCtor         >, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 0> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<int, int>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
#if !defined(HAMON_USE_STD_TUPLE)
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc, ExplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
#endif
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ExplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_constructible<hamon::tuple<>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 0> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int, int>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc,  NoThrowLastAlloc,  NoThrowNoAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ExplicitFirstAlloc, NoThrowLastAlloc,  NoThrowNoAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc,  ExplicitLastAlloc, NoThrowNoAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc,  NoThrowLastAlloc,  ExplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::array<int, 3> const&>::value, "");
#endif

GTEST_TEST(TupleTest, CtorAllocTupleLikeCRefTest)
{
	HAMON_CXX11_CONSTEXPR MyAlloc a{};
	{
		hamon::array<int, 0> const t1{};
		hamon::tuple<> const t2(hamon::allocator_arg, a, t1);
		(void)t2;
	}
	{
		hamon::array<int, 2> const t1{1, 2};
		hamon::tuple<int, double> const t2(hamon::allocator_arg, a, t1);
		EXPECT_EQ(1, hamon::adl_get<0>(t2));
		EXPECT_EQ(2, hamon::adl_get<1>(t2));
	}
	{
		hamon::array<int, 3> const t1{3, 4, 5};
		hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>  const t2(hamon::allocator_arg, a, t1);
		EXPECT_EQ(3, hamon::adl_get<0>(t2).n);
		EXPECT_EQ(4, hamon::adl_get<1>(t2).n);
		EXPECT_EQ(5, hamon::adl_get<2>(t2).n);
	}
	{
		hamon::array<int, 4> const t1{3, 4, 5, 6};
		hamon::tuple<ExplicitFirstAlloc, int, ExplicitLastAlloc, ExplicitNoAlloc>  const t2(hamon::allocator_arg, a, t1);
		EXPECT_EQ(3, hamon::adl_get<0>(t2).n);
		EXPECT_EQ(4, hamon::adl_get<1>(t2));
		EXPECT_EQ(5, hamon::adl_get<2>(t2).n);
		EXPECT_EQ(6, hamon::adl_get<3>(t2).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 0> const t1{};
		HAMON_CXX11_CONSTEXPR hamon::tuple<> const t2(hamon::allocator_arg, a, t1);
		(void)t2;
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> const t1{1, 2};
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, double> const t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::adl_get<0>(t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::adl_get<1>(t2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 3> const t1{3, 4, 5};
		HAMON_CXX11_CONSTEXPR hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>  const t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::adl_get<0>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::adl_get<1>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::adl_get<2>(t2).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 4> const t1{3, 4, 5, 6};
		HAMON_CXX11_CONSTEXPR hamon::tuple<ExplicitFirstAlloc, int, ExplicitLastAlloc, ExplicitNoAlloc>  const t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::adl_get<0>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::adl_get<1>(t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::adl_get<2>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::adl_get<3>(t2).n);
	}
}

}	// namespace ctor_alloc_tuple_like_cref_test

}	// namespace hamon_tuple_test
