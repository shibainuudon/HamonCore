/**
 *	@file	unit_test_pair_assign_copy_pair_const.cpp
 *
 *	@brief	コピー代入のテスト
 * 
 *	template<class U1, class U2>
 *	constexpr const pair& operator=(const pair<U1, U2>& p) const;
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace assign_copy_pair_const_test
{

struct AssignableInt
{
	AssignableInt(AssignableInt const&) = delete;
	AssignableInt& operator=(AssignableInt const&) = delete;
	AssignableInt& operator=(int const&) const;
};

struct NothrowAssignableInt
{
	NothrowAssignableInt(NothrowAssignableInt const&) = delete;
	NothrowAssignableInt& operator=(NothrowAssignableInt const&) = delete;
	NothrowAssignableInt& operator=(int const&) const noexcept;
};

static_assert(!hamon::is_assignable<hamon::pair<int,  int> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int&, int> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int,  int&> const&, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_assignable<hamon::pair<int&, int&> const&, hamon::pair<int, int> const&>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::pair<NothrowAssignableInt, NothrowAssignableInt> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<AssignableInt,        NothrowAssignableInt> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<NothrowAssignableInt, AssignableInt> const&,        hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<AssignableInt,        AssignableInt> const&,        hamon::pair<int, int> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	// operator=(const pair<U1, U2>& p) const;
	{
		int i1 = 10;
		int i2 = 11;
		float d1 = 12;
		double d2 = 13;
		hamon::pair<int&, float&> const p1(i1, d1);
		hamon::pair<int&, double&> const p2(i2, d2);

		VERIFY(p1.first  == i1);
		VERIFY(p1.second == d1);
		VERIFY(p2.first  == i2);
		VERIFY(p2.second == d2);

		auto&& r = (p1 = p2);
		static_assert(hamon::is_same<decltype(r), hamon::pair<int&, float&> const&>::value, "");
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

GTEST_TEST(PairTest, AssignCopyPairConstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_copy_pair_const_test

}	// namespace hamon_pair_test
