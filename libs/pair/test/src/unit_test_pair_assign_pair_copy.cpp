/**
 *	@file	unit_test_pair_assign_pair_copy.cpp
 *
 *	@brief	pair<U1, U2>からのコピー代入のテスト
 * 
 *	template<class U1, class U2>
 *	constexpr pair& operator=(const pair<U1, U2>& p);
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace assign_pair_copy_test
{

struct CopyAssignable
{
	CopyAssignable(CopyAssignable const&) = delete;
	CopyAssignable& operator=(CopyAssignable const&);
};

struct AssignableInt
{
	AssignableInt(AssignableInt const&) = delete;
	AssignableInt& operator=(AssignableInt const&) = delete;
	AssignableInt& operator=(int const&);
};

struct NothrowAssignableInt
{
	NothrowAssignableInt(NothrowAssignableInt const&) = delete;
	NothrowAssignableInt& operator=(NothrowAssignableInt const&) = delete;
	NothrowAssignableInt& operator=(int const&) noexcept;
};

static_assert( hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<short, int> const&>::value, "");
static_assert( hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<int,   short> const&>::value, "");
static_assert( hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<short, short> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<int*,  int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<int,   int*> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<int*,  int*> const&>::value, "");
static_assert( hamon::is_assignable<hamon::pair<AssignableInt,  AssignableInt>&,  hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<CopyAssignable, AssignableInt>&,  hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<AssignableInt,  CopyAssignable>&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<CopyAssignable, CopyAssignable>&, hamon::pair<int, int> const&>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::pair<int, int>&, hamon::pair<short, int> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<int, int>&, hamon::pair<int,   short> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<int, int>&, hamon::pair<short, short> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<NothrowAssignableInt, NothrowAssignableInt>&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<AssignableInt,        NothrowAssignableInt>&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<NothrowAssignableInt, AssignableInt>&,        hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<AssignableInt,        AssignableInt>&,        hamon::pair<int, int> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	// operator=(const pair<U1, U2>& p);
	{
		hamon::pair<short, float> p1(1, 2);
		hamon::pair<int, double> const p2(3, 4);

		VERIFY(p1.first  == 1);
		VERIFY(p1.second == 2);
		VERIFY(p2.first  == 3);
		VERIFY(p2.second == 4);

		auto&& r = (p1 = p2);
		static_assert(hamon::is_same<decltype(r), hamon::pair<short, float>&>::value, "");
		VERIFY(&r == &p1);

		VERIFY(p1.first  == 3);
		VERIFY(p1.second == 4);
		VERIFY(p2.first  == 3);
		VERIFY(p2.second == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, AssignPairCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_pair_copy_test

}	// namespace hamon_pair_test
