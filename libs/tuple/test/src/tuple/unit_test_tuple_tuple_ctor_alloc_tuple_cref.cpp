/**
 *	@file	unit_test_tuple_tuple_ctor_alloc_tuple_cref.cpp
 *
 *	@brief	allocator_arg_t, Alloc const&, tuple<UTypes...> const& を引数に取るコンストラクタのテスト
 *
 *	template<class Alloc, class... UTypes>
 *	constexpr explicit(see below)
 *	tuple(allocator_arg_t, const Alloc& a, const tuple<UTypes...>&);
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

namespace ctor_alloc_tuple_cref_test
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

static_assert(!hamon::is_constructible<hamon::tuple<>,                   hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<float> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int&> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int&&> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int const> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int const&> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int const&&> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowFirstAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowLastAlloc>,   hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowNoAlloc>,     hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor>,             hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int>,           hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, long> const&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int> const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int, int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int, int>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, long, float> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, int, int>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, long, int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<double, int, int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor, int, int>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, int, int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int, int, NoCtor>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, int, int> const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ExplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ExplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<float> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ExplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ExplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<float> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowLastAlloc>,   hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowNoAlloc>,     hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int, int>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, long> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowLastAlloc, NoThrowLastAlloc, NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<ImplicitLastAlloc, NoThrowLastAlloc, NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowLastAlloc, NoThrowLastAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int> const&>::value, "");
#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

GTEST_TEST(TupleTest, CtorAllocTupleCRefTest)
{
	HAMON_CXX11_CONSTEXPR MyAlloc a{};
	{
		hamon::tuple<char> const t1(42);
		hamon::tuple<int>  const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t2) == 42);
	}
	{
		hamon::tuple<const char*, int>  const t1("hello", 43);
		hamon::tuple<hamon::string, long> const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t2) == "hello");
		EXPECT_TRUE(hamon::adl_get<1>(t2) == 43);
	}
	{
		hamon::tuple<int>                const t1(10);
		hamon::tuple<ImplicitFirstAlloc> const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t2).n == 10);
	}
	{
		hamon::tuple<int, int>               const t1(11, 12);
		hamon::tuple<ImplicitLastAlloc, int> const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t2).n == 11);
		EXPECT_TRUE(hamon::adl_get<1>(t2) == 12);
	}
	{
		hamon::tuple<int, int, int>                              const t1(3, 4, 5);
		hamon::tuple<ImplicitNoAlloc, float, ExplicitFirstAlloc> const t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t2).n == 3);
		EXPECT_TRUE(hamon::adl_get<1>(t2) == 4.0f);
		EXPECT_TRUE(hamon::adl_get<2>(t2).n == 5);
	}
	{
		hamon::tuple<int, int, int, int, int> const t1(1, 2, 3, 4, 5);
		hamon::tuple<ExplicitLastAlloc, ExplicitNoAlloc, NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>
			t2(hamon::allocator_arg, a, t1);
		EXPECT_TRUE(hamon::adl_get<0>(t2).n == 1);
		EXPECT_TRUE(hamon::adl_get<1>(t2).n == 2);
		EXPECT_TRUE(hamon::adl_get<2>(t2).n == 3);
		EXPECT_TRUE(hamon::adl_get<3>(t2).n == 4);
		EXPECT_TRUE(hamon::adl_get<4>(t2).n == 5);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<char> const t1(42);
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> const t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2) == 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> const t1(43.0f, 44);
		HAMON_CXX11_CONSTEXPR hamon::tuple<double, long> const t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2) == 43);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t2) == 44);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, int, int, int, int> const t1(1, 2, 3, 4, 5);
		HAMON_CXX11_CONSTEXPR hamon::tuple<ExplicitLastAlloc, ExplicitNoAlloc, NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>
			t2(hamon::allocator_arg, a, t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t2).n == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t2).n == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t2).n == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<3>(t2).n == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<4>(t2).n == 5);
	}
}

HAMON_WARNING_POP()

}	// namespace ctor_alloc_tuple_cref_test

}	// namespace hamon_tuple_test
