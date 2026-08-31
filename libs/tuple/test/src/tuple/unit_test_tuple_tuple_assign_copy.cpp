/**
 *	@file	unit_test_tuple_tuple_assign_copy.cpp
 *
 *	@brief	コピー代入のテスト
 *
 *	constexpr tuple& operator=(const tuple& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_copy_test
{

struct NonCopyAssignable
{
	NonCopyAssignable(NonCopyAssignable const&) = delete;
	NonCopyAssignable& operator=(NonCopyAssignable const&) = delete;
};

struct CopyAssignable
{
	CopyAssignable(CopyAssignable const&) = delete;
	CopyAssignable& operator=(CopyAssignable const&);
};

struct NothrowCopyAssignable
{
	NothrowCopyAssignable(NothrowCopyAssignable const&) = delete;
	NothrowCopyAssignable& operator=(NothrowCopyAssignable const&) noexcept;
};

static_assert(!hamon::is_copy_assignable<NonCopyAssignable>::value, "");
static_assert( hamon::is_copy_assignable<CopyAssignable>::value, "");
static_assert( hamon::is_copy_assignable<NothrowCopyAssignable>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<NonCopyAssignable>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<CopyAssignable>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<NothrowCopyAssignable>::value, "");

static_assert( hamon::is_copy_assignable<hamon::tuple<int, int>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::tuple<CopyAssignable,    int>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::tuple<int,               CopyAssignable>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::tuple<CopyAssignable,    CopyAssignable>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::tuple<NonCopyAssignable, int>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::tuple<int,               NonCopyAssignable>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::tuple<NonCopyAssignable, NonCopyAssignable>>::value, "");

static_assert( hamon::is_nothrow_copy_assignable<hamon::tuple<int, int>>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::tuple<NothrowCopyAssignable, int>>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::tuple<int,                   NothrowCopyAssignable>>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::tuple<NothrowCopyAssignable, NothrowCopyAssignable>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::tuple<CopyAssignable,    int>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::tuple<int,               CopyAssignable>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::tuple<CopyAssignable,    CopyAssignable>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::tuple<int, double> p1(1, 2);
		hamon::tuple<int, double> const p2(3, 4);

		VERIFY(hamon::adl_get<0>(p1) == 1);
		VERIFY(hamon::adl_get<1>(p1) == 2);
		VERIFY(hamon::adl_get<0>(p2) == 3);
		VERIFY(hamon::adl_get<1>(p2) == 4);

		auto&& r = (p1 = p2);
		static_assert(hamon::is_same<decltype(r), hamon::tuple<int, double>&>::value, "");
		VERIFY(&r == &p1);

		VERIFY(hamon::adl_get<0>(p1) == 3);
		VERIFY(hamon::adl_get<1>(p1) == 4);
		VERIFY(hamon::adl_get<0>(p2) == 3);
		VERIFY(hamon::adl_get<1>(p2) == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, AssignCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_copy_test

}	// namespace hamon_tuple_test
