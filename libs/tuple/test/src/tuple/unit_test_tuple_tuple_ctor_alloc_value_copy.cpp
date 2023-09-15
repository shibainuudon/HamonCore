/**
 *	@file	unit_test_tuple_tuple_ctor_alloc_value_copy.cpp
 *
 *	@brief	allocator_arg_t, Alloc const&, Types const&... を引数に取るコンストラクタのテスト
 *
 *	template <typename Alloc>
 *	constexpr explicit(see below)
 *	tuple(allocator_arg_t, Alloc const& a, Types const&...);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_alloc_value_copy_test
{

struct MyAlloc {};

struct ImplicitFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR explicit ImplicitFirstAlloc()
		: n(0) {}
	HAMON_CXX11_CONSTEXPR explicit ImplicitFirstAlloc(ImplicitFirstAlloc const&)
		: n(1) {}
	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, ImplicitFirstAlloc const&)
		: n(2) {}

	int n;
};

struct ImplicitLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR explicit ImplicitLastAlloc()
		: n(0) {}
	HAMON_CXX11_CONSTEXPR explicit ImplicitLastAlloc(ImplicitLastAlloc const&)
		: n(3) {}
	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(ImplicitLastAlloc const&, MyAlloc const&)
		: n(4) {}

	int n;
};

struct ImplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR explicit ImplicitNoAlloc()
		: n(0) {}
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(ImplicitNoAlloc const&)
		: n(5) {}
	HAMON_CXX11_CONSTEXPR explicit ImplicitNoAlloc(hamon::allocator_arg_t, MyAlloc const&, ImplicitNoAlloc const&)
		: n(6) {}
	HAMON_CXX11_CONSTEXPR explicit ImplicitNoAlloc(ImplicitNoAlloc const&, MyAlloc const&)
		: n(7) {}

	int n;
};

struct ExplicitFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ExplicitFirstAlloc()
		: n(0) {}
	HAMON_CXX11_CONSTEXPR ExplicitFirstAlloc(ExplicitFirstAlloc const&)
		: n(8) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, ExplicitFirstAlloc const&)
		: n(9) {}

	int n;
};

struct ExplicitLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc()
		: n(0) {}
	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc(ExplicitLastAlloc const&)
		: n(10) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitLastAlloc(ExplicitLastAlloc const&, MyAlloc const&)
		: n(11) {}

	int n;
};

struct ExplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc()
		: n(0) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitNoAlloc(ExplicitNoAlloc const&)
		: n(12) {}
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(hamon::allocator_arg_t, MyAlloc const&, ExplicitNoAlloc const&)
		: n(13) {}
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(ExplicitNoAlloc const&, MyAlloc const&)
		: n(14) {}

	int n;
};

struct NoThrowFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc()
		: n(0) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(NoThrowFirstAlloc const&)
		: n(15) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, NoThrowFirstAlloc const&) noexcept
		: n(16) {}

	int n;
};

struct NoThrowLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc()
		: n(0) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(NoThrowLastAlloc const&)
		: n(17) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(NoThrowLastAlloc const&, MyAlloc const&) noexcept
		: n(18) {}

	int n;
};

struct NoThrowNoAlloc
{
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc()
		: n(0) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(NoThrowNoAlloc const&) noexcept
		: n(19) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(hamon::allocator_arg_t, MyAlloc const&, NoThrowNoAlloc const&)
		: n(20) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(NoThrowNoAlloc const&, MyAlloc const&)
		: n(21) {}

	int n;
};

struct NoCopy
{
	HAMON_CXX11_CONSTEXPR NoCopy(NoCopy const&) = delete;
};

static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, ImplicitFirstAlloc const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, ImplicitLastAlloc const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, ImplicitNoAlloc const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, ExplicitFirstAlloc const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, ExplicitLastAlloc const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, ExplicitNoAlloc const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowFirstAlloc>,  hamon::allocator_arg_t, MyAlloc, NoThrowFirstAlloc const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowLastAlloc>,   hamon::allocator_arg_t, MyAlloc, NoThrowLastAlloc const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowNoAlloc>,     hamon::allocator_arg_t, MyAlloc, NoThrowNoAlloc const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy>,             hamon::allocator_arg_t, MyAlloc, NoCopy const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int>,           hamon::allocator_arg_t, MyAlloc, int const&, int const&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitFirstAlloc const&, ImplicitLastAlloc const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitFirstAlloc const&, ImplicitLastAlloc const&, ImplicitNoAlloc const&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitFirstAlloc const&, ImplicitLastAlloc const&, ImplicitNoAlloc const&, int const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int, int>, hamon::allocator_arg_t, MyAlloc, int const&, int const&, int const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, int, int>, hamon::allocator_arg_t, MyAlloc, ImplicitFirstAlloc const&, int const&, int const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, int const&, int const&, ImplicitFirstAlloc const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy, int, int>, hamon::allocator_arg_t, MyAlloc, NoCopy const&, int const&, int const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int, int, NoCopy>, hamon::allocator_arg_t, MyAlloc, int const&, int const&, NoCopy const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitFirstAlloc const&, ImplicitFirstAlloc const&, ImplicitFirstAlloc const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ExplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	ExplicitFirstAlloc const&, ImplicitFirstAlloc const&, ImplicitFirstAlloc const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ExplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitFirstAlloc const&, ExplicitFirstAlloc const&, ImplicitFirstAlloc const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitFirstAlloc const&, ImplicitFirstAlloc const&, ExplicitFirstAlloc const&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, ImplicitFirstAlloc const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, ImplicitLastAlloc const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, ImplicitNoAlloc const&>::value, "");
#if !defined(HAMON_GCC)
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, ExplicitFirstAlloc const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, ExplicitLastAlloc const&>::value, "");
#endif
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, ExplicitNoAlloc const&>::value, "");
static_assert( hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitFirstAlloc const&, ImplicitFirstAlloc const&, ImplicitFirstAlloc const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ExplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	ExplicitFirstAlloc const&, ImplicitFirstAlloc const&, ImplicitFirstAlloc const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ExplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitFirstAlloc const&, ExplicitFirstAlloc const&, ImplicitFirstAlloc const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitFirstAlloc const&, ImplicitFirstAlloc const&, ExplicitFirstAlloc const&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, int const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc>,  hamon::allocator_arg_t, MyAlloc, NoThrowFirstAlloc const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowLastAlloc>,   hamon::allocator_arg_t, MyAlloc, NoThrowLastAlloc const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowNoAlloc>,     hamon::allocator_arg_t, MyAlloc, NoThrowNoAlloc const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, ImplicitFirstAlloc const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, ImplicitLastAlloc const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, ImplicitNoAlloc const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int, int>, hamon::allocator_arg_t, MyAlloc, int const&, int const&>::value, "");
static_assert( hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowLastAlloc, NoThrowLastAlloc, NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	NoThrowLastAlloc const&, NoThrowLastAlloc const&, NoThrowLastAlloc const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<ImplicitLastAlloc, NoThrowLastAlloc, NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	ImplicitLastAlloc const&, NoThrowLastAlloc const&, NoThrowLastAlloc const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowLastAlloc, NoThrowLastAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	NoThrowLastAlloc const&, NoThrowLastAlloc const&, ImplicitLastAlloc const&>::value, "");

GTEST_TEST(TupleTest, CtorAllocValueCopyTest)
{
	HAMON_CXX11_CONSTEXPR MyAlloc a{};
	{
		int const i = 42;
		hamon::tuple<int> t(hamon::allocator_arg, a, i);
		EXPECT_TRUE(hamon::adl_get<0>(t) == 42);
	}
	{
		hamon::string const s = "hello";
		int const i = 43;
		hamon::tuple<hamon::string, int> t(hamon::allocator_arg, a, s, i);
		EXPECT_TRUE(hamon::adl_get<0>(t) == "hello");
		EXPECT_TRUE(hamon::adl_get<1>(t) == 43);
	}
	{
		ImplicitFirstAlloc const x;
		hamon::tuple<ImplicitFirstAlloc> t(hamon::allocator_arg, a, x);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 2);
	}
	{
		ImplicitLastAlloc const x;
		int const i = 44;
		hamon::tuple<ImplicitLastAlloc, int> t(hamon::allocator_arg, a, x, i);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 4);
		EXPECT_TRUE(hamon::adl_get<1>(t) == 44);
	}
	{
		ImplicitNoAlloc const x;
		float const f = 2.5f;
		ExplicitFirstAlloc const y;
		hamon::tuple<ImplicitNoAlloc, float, ExplicitFirstAlloc> t(hamon::allocator_arg, a, x, f, y);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 5);
		EXPECT_TRUE(hamon::adl_get<1>(t) == 2.5f);
		EXPECT_TRUE(hamon::adl_get<2>(t).n == 9);
	}
	{
		ExplicitLastAlloc const x1;
		ExplicitNoAlloc   const x2;
		NoThrowFirstAlloc const x3;
		NoThrowLastAlloc  const x4;
		NoThrowNoAlloc    const x5;
		hamon::tuple<ExplicitLastAlloc, ExplicitNoAlloc, NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>
			t(hamon::allocator_arg, a, x1, x2, x3, x4, x5);
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 11);
		EXPECT_TRUE(hamon::adl_get<1>(t).n == 12);
		EXPECT_TRUE(hamon::adl_get<2>(t).n == 16);
		EXPECT_TRUE(hamon::adl_get<3>(t).n == 18);
		EXPECT_TRUE(hamon::adl_get<4>(t).n == 19);
	}
	{
		HAMON_CXX11_CONSTEXPR int const i = 42;
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t(hamon::allocator_arg, a, i);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 42);
	}
	{
		HAMON_CXX11_CONSTEXPR float const f = 2.5f;
		HAMON_CXX11_CONSTEXPR int const i = 43;
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> t(hamon::allocator_arg, a, f, i);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 2.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t) == 43);
	}
	{
		HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc const x;
		HAMON_CXX11_CONSTEXPR ImplicitLastAlloc const y;
		HAMON_CXX11_CONSTEXPR ImplicitNoAlloc const z;
		HAMON_CXX11_CONSTEXPR hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>
			t(hamon::allocator_arg, a, x, y, z);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t).n == 5);
	}
}

}	// namespace ctor_alloc_value_copy_test

}	// namespace hamon_tuple_test
