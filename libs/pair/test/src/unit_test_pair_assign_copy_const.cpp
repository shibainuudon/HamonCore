/**
 *	@file	unit_test_pair_assign_copy_const.cpp
 *
 *	@brief	コピー代入(プロキシ参照版)のテスト
 * 
 *	constexpr const pair& operator=(const pair& p) const;
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
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

static_assert(!hamon::is_copy_assignable<hamon::pair<int,  int> const>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::pair<int&, int> const>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::pair<int,  int&> const>::value, "");
static_assert( hamon::is_copy_assignable<hamon::pair<int&, int&> const>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::pair<CopyAssignable,         CopyAssignable> const>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::pair<NonCopyAssignable&,     NonCopyAssignable&> const>::value, "");
static_assert( hamon::is_copy_assignable<hamon::pair<CopyAssignable&,        CopyAssignable&> const>::value, "");
static_assert( hamon::is_copy_assignable<hamon::pair<NothrowCopyAssignable&, NothrowCopyAssignable&> const>::value, "");

static_assert(!hamon::is_nothrow_copy_assignable<hamon::pair<int,  int> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::pair<int&, int> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::pair<int,  int&> const>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::pair<int&, int&> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::pair<CopyAssignable&,        CopyAssignable&> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::pair<CopyAssignable&,        NothrowCopyAssignable&> const>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::pair<NothrowCopyAssignable&, CopyAssignable&> const>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::pair<NothrowCopyAssignable&, NothrowCopyAssignable&> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	// operator=(const pair& p) const;
	{
		int i1 = 10;
		int i2 = 11;
		double d1 = 12;
		double d2 = 13;
		hamon::pair<int&, double&> const p1(i1, d1);
		hamon::pair<int&, double&> const p2(i2, d2);

		VERIFY(p1.first  == i1);
		VERIFY(p1.second == d1);
		VERIFY(p2.first  == i2);
		VERIFY(p2.second == d2);

		auto&& r = (p1 = p2);
		static_assert(hamon::is_same<decltype(r), hamon::pair<int&, double&> const&>::value, "");
		VERIFY(&r == &p1);

		VERIFY(p1.first  == i2);
		VERIFY(p1.second == d2);
		VERIFY(p2.first  == i1);
		VERIFY(p2.second == d1);

		VERIFY(i1 == 11);
		VERIFY(i2 == 11);
		VERIFY(d1 == 13);
		VERIFY(d2 == 13);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, AssignCopyConstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_copy_const_test

}	// namespace hamon_pair_test
