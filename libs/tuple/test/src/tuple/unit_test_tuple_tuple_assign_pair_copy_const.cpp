/**
 *	@file	unit_test_tuple_tuple_assign_pair_copy_const.cpp
 *
 *	@brief	pair<U1, U2>からのコピー代入(プロキシ参照版)のテスト
 *
 *	template<class U1, class U2> constexpr const tuple& operator=(const pair<U1, U2>& u) const;
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_pair_copy_const_test
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

static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt> const&, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<AssignableInt, AssignableInt> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt, AssignableInt, AssignableInt> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int&> const&, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int&, int&> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int&, int&, int&> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int,  int> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int&, int> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int,  int&> const&, hamon::pair<int, int> const&>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, NothrowAssignableInt> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        NothrowAssignableInt> const&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, AssignableInt> const&,        hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        AssignableInt> const&,        hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<int&, int&> const&, hamon::pair<int, int> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		int i1 = 10;
		int i2 = 11;
		float d1 = 12;
		double d2 = 13;
		hamon::tuple<int&, float&> const p1(i1, d1);
		hamon::pair<int&, double&> const p2(i2, d2);

		VERIFY(hamon::adl_get<0>(p1) == i1);
		VERIFY(hamon::adl_get<1>(p1) == d1);
		VERIFY(hamon::adl_get<0>(p2) == i2);
		VERIFY(hamon::adl_get<1>(p2) == d2);

		auto&& r = (p1 = p2);
		static_assert(hamon::is_same<decltype(r), hamon::tuple<int&, float&> const&>::value, "");
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

HAMON_WARNING_POP()

#undef VERIFY

GTEST_TEST(TupleTest, AssignPairCopyConstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_pair_copy_const_test

}	// namespace hamon_tuple_test
