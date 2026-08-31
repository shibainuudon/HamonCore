/**
 *	@file	unit_test_tuple_tuple_assign_copy_const.cpp
 *
 *	@brief	コピー代入(プロキシ参照版)のテスト
 *
 *	constexpr const tuple& operator=(const tuple& u) const;
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_copy_const_test
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

static_assert(!hamon::is_copy_assignable<hamon::tuple<int,  int> const>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::tuple<int&, int> const>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::tuple<int,  int&> const>::value, "");
static_assert( hamon::is_copy_assignable<hamon::tuple<int&, int&> const>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::tuple<CopyAssignable,         CopyAssignable> const>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::tuple<NonCopyAssignable&,     NonCopyAssignable&> const>::value, "");
static_assert( hamon::is_copy_assignable<hamon::tuple<CopyAssignable&,        CopyAssignable&> const>::value, "");
static_assert( hamon::is_copy_assignable<hamon::tuple<NothrowCopyAssignable&, NothrowCopyAssignable&> const>::value, "");

static_assert(!hamon::is_nothrow_copy_assignable<hamon::tuple<int,  int> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::tuple<int&, int> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::tuple<int,  int&> const>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::tuple<int&, int&> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::tuple<CopyAssignable&,        CopyAssignable&> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::tuple<CopyAssignable&,        NothrowCopyAssignable&> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::tuple<NothrowCopyAssignable&, CopyAssignable&> const>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::tuple<NothrowCopyAssignable&, NothrowCopyAssignable&> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		int i1 = 10;
		int i2 = 11;
		double d1 = 12;
		double d2 = 13;
		hamon::tuple<int&, double&> const p1(i1, d1);
		hamon::tuple<int&, double&> const p2(i2, d2);

		VERIFY(hamon::adl_get<0>(p1) == i1);
		VERIFY(hamon::adl_get<1>(p1) == d1);
		VERIFY(hamon::adl_get<0>(p2) == i2);
		VERIFY(hamon::adl_get<1>(p2) == d2);

		auto&& r = (p1 = p2);
		static_assert(hamon::is_same<decltype(r), hamon::tuple<int&, double&> const&>::value, "");
		VERIFY(&r == &p1);

		VERIFY(hamon::adl_get<0>(p1) == i2);
		VERIFY(hamon::adl_get<1>(p1) == d2);
		VERIFY(hamon::adl_get<0>(p2) == i1);
		VERIFY(hamon::adl_get<1>(p2) == d1);

		VERIFY(i1 == 11);
		VERIFY(i2 == 11);
		VERIFY(d1 == 13);
		VERIFY(d2 == 13);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, AssignCopyConstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_copy_const_test

}	// namespace hamon_tuple_test
