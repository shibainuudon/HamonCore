/**
 *	@file	unit_test_pair_assign_copy.cpp
 *
 *	@brief	コピー代入のテスト
 * 
 *	constexpr pair& operator=(const pair& p);
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
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

static_assert( hamon::is_copy_assignable<hamon::pair<int, int>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::pair<CopyAssignable,    int>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::pair<int,               CopyAssignable>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::pair<CopyAssignable,    CopyAssignable>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::pair<NonCopyAssignable, int>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::pair<int,               NonCopyAssignable>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::pair<NonCopyAssignable, NonCopyAssignable>>::value, "");

static_assert( hamon::is_nothrow_copy_assignable<hamon::pair<int, int>>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::pair<NothrowCopyAssignable, int>>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::pair<int,                   NothrowCopyAssignable>>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::pair<NothrowCopyAssignable, NothrowCopyAssignable>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::pair<CopyAssignable,    int>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::pair<int,               CopyAssignable>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::pair<CopyAssignable,    CopyAssignable>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	// operator=(const pair& p);
	{
		hamon::pair<int, double> p1(1, 2);
		hamon::pair<int, double> const p2(3, 4);

		VERIFY(p1.first  == 1);
		VERIFY(p1.second == 2);
		VERIFY(p2.first  == 3);
		VERIFY(p2.second == 4);

		auto&& r = (p1 = p2);
		static_assert(hamon::is_same<decltype(r), hamon::pair<int, double>&>::value, "");
		VERIFY(&r == &p1);

		VERIFY(p1.first  == 3);
		VERIFY(p1.second == 4);
		VERIFY(p2.first  == 3);
		VERIFY(p2.second == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, AssignCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_copy_test

}	// namespace hamon_pair_test
