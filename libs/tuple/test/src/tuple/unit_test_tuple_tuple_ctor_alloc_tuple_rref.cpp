/**
 *	@file	unit_test_tuple_tuple_ctor_alloc_tuple_rref.cpp
 *
 *	@brief	allocator_arg_t, Alloc const&, tuple<UTypes...>&& を引数に取るコンストラクタのテスト
 *
 *	template<class Alloc, class... UTypes>
 *	constexpr explicit(see below)
 *	tuple(allocator_arg_t, const Alloc& a, tuple<UTypes...>&&);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_alloc_tuple_rref_test
{

struct MyAlloc {};

struct ImplicitFirstAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(int)
		: n(-1) {}

	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&& i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const&&) = delete;

	int n;
};

struct ImplicitLastAlloc
{
	using allocator_type = MyAlloc;

	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int)
		: n(-1) {}

	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int&, MyAlloc const&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int&& i, MyAlloc const&)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int const&, MyAlloc const&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitLastAlloc(int const&&, MyAlloc const&) = delete;

	int n;
};

struct ImplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(int&) = delete;
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(int&& i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ImplicitNoAlloc(int const&) = delete;
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
	HAMON_CXX11_CONSTEXPR explicit ExplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&& i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ExplicitFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const&)
		: n(-1) {}
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
	HAMON_CXX11_CONSTEXPR explicit ExplicitLastAlloc(int&& i, MyAlloc const&)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc(int const& i, MyAlloc const&)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ExplicitLastAlloc(int const&&, MyAlloc const&)
		: n(-1) {}

	int n;
};

struct ExplicitNoAlloc
{
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(int&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR explicit ExplicitNoAlloc(int&& i)
		: n(i) {}
	HAMON_CXX11_CONSTEXPR ExplicitNoAlloc(int const&)
		: n(-1) {}
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
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int&& i) noexcept
		: n(i) {}
	HAMON_CXX11_CONSTEXPR NoThrowFirstAlloc(hamon::allocator_arg_t, MyAlloc const&, int const&)
		: n(-1) {}
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
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int&& i, MyAlloc const&) noexcept
		: n(i) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int const&, MyAlloc const&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowLastAlloc(int const&&, MyAlloc const&)
		: n(-1) {}

	int n;
};

struct NoThrowNoAlloc
{
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(int&)
		: n(-1) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(int&& i) noexcept
		: n(i) {}
	HAMON_CXX11_CONSTEXPR NoThrowNoAlloc(int const&)
		: n(-1) {}
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

static_assert(!hamon::is_constructible<hamon::tuple<>,                   hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<float>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int&>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int&&>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int const>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int const&>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int const&&>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ExplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowFirstAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowLastAlloc>,   hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrowNoAlloc>,     hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor>,             hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int>,           hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, long>&&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int>&&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
static_assert(!hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitLastAlloc, ImplicitNoAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int, int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int, int>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, long, float>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<ImplicitFirstAlloc, int, int>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, long, int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int, int, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<double, int, int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor, int, int>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, int, int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int, int, NoCtor>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, int, int>&&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ExplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ExplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
static_assert( hamon::is_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<float>&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
#if !defined(HAMON_USE_STD_TUPLE)
#if !defined(HAMON_GCC)
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<ExplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
#endif
static_assert( hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ExplicitFirstAlloc, ImplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ExplicitFirstAlloc, ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<
	hamon::tuple<ImplicitFirstAlloc, ImplicitFirstAlloc, ExplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
#endif

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int>,                hamon::allocator_arg_t, MyAlloc, hamon::tuple<float>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowFirstAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowLastAlloc>,   hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrowNoAlloc>,     hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitFirstAlloc>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitLastAlloc>,  hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<ImplicitNoAlloc>,    hamon::allocator_arg_t, MyAlloc, hamon::tuple<int>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int, int>, hamon::allocator_arg_t, MyAlloc, hamon::tuple<int, long>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowLastAlloc, NoThrowLastAlloc, NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<ImplicitLastAlloc, NoThrowLastAlloc, NoThrowLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::tuple<NoThrowLastAlloc, NoThrowLastAlloc, ImplicitLastAlloc>, hamon::allocator_arg_t, MyAlloc,
	hamon::tuple<int, int, int>&&>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

inline HAMON_CXX14_CONSTEXPR bool test()
{
	HAMON_CXX11_CONSTEXPR MyAlloc a{};
	{
		hamon::tuple<char> t1(42);
		hamon::tuple<int> t2(hamon::allocator_arg, a, hamon::move(t1));
		VERIFY(hamon::adl_get<0>(t2) == 42);
	}
	{
		hamon::tuple<float, int> t1(43.0f, 44);
		hamon::tuple<double, long> t2(hamon::allocator_arg, a, hamon::move(t1));
		VERIFY(hamon::adl_get<0>(t2) == 43);
		VERIFY(hamon::adl_get<1>(t2) == 44);
	}
	{
		hamon::tuple<int, int, int> t1(3, 4, 5);
		hamon::tuple<ImplicitNoAlloc, float, ExplicitFirstAlloc>
			t2(hamon::allocator_arg, a, hamon::move(t1));
		VERIFY(hamon::adl_get<0>(t2).n == 3);
		VERIFY(hamon::adl_get<1>(t2) == 4.0f);
		VERIFY(hamon::adl_get<2>(t2).n == 5);
	}
	{
		hamon::tuple<int, int, int, int, int> t1(1, 2, 3, 4, 5);
		hamon::tuple<ExplicitLastAlloc, ExplicitNoAlloc, NoThrowFirstAlloc, NoThrowLastAlloc, NoThrowNoAlloc>
			t2(hamon::allocator_arg, a, hamon::move(t1));
		VERIFY(hamon::adl_get<0>(t2).n == 1);
		VERIFY(hamon::adl_get<1>(t2).n == 2);
		VERIFY(hamon::adl_get<2>(t2).n == 3);
		VERIFY(hamon::adl_get<3>(t2).n == 4);
		VERIFY(hamon::adl_get<4>(t2).n == 5);
	}
	return true;
}

HAMON_WARNING_POP()

#undef VERIFY

GTEST_TEST(TupleTest, CtorAllocTupleRRefTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_alloc_tuple_rref_test

}	// namespace hamon_tuple_test
