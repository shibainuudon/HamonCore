/**
 *	@file	unit_test_tuple_tuple_assign_move_const.cpp
 *
 *	@brief	ムーブ代入(プロキシ参照版)のテスト
 *
 *	constexpr const tuple& operator=(tuple&& u) const;
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_move_const_test
{

struct NonMoveAssignable
{
	NonMoveAssignable(NonMoveAssignable const&) = delete;
	NonMoveAssignable& operator=(NonMoveAssignable const&) = delete;
};

struct MoveAssignable
{
	MoveAssignable(MoveAssignable const&) = delete;
	MoveAssignable& operator=(MoveAssignable const&);
};

struct NothrowMoveAssignable
{
	NothrowMoveAssignable(NothrowMoveAssignable const&) = delete;
	NothrowMoveAssignable& operator=(NothrowMoveAssignable const&) noexcept;
};

static_assert(!hamon::is_move_assignable<hamon::tuple<int,  int> const>::value, "");
static_assert(!hamon::is_move_assignable<hamon::tuple<int&, int> const>::value, "");
static_assert(!hamon::is_move_assignable<hamon::tuple<int,  int&> const>::value, "");
static_assert( hamon::is_move_assignable<hamon::tuple<int&, int&> const>::value, "");
static_assert(!hamon::is_move_assignable<hamon::tuple<NonMoveAssignable&, NonMoveAssignable&> const>::value, "");
static_assert( hamon::is_move_assignable<hamon::tuple<MoveAssignable&, MoveAssignable&> const>::value, "");
static_assert( hamon::is_move_assignable<hamon::tuple<NothrowMoveAssignable&, NothrowMoveAssignable&> const>::value, "");

static_assert(!hamon::is_nothrow_move_assignable<hamon::tuple<int,  int> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::tuple<int&, int> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::tuple<int,  int&> const>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::tuple<int&, int&> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::tuple<MoveAssignable&,        MoveAssignable&> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::tuple<MoveAssignable&,        NothrowMoveAssignable&> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::tuple<NothrowMoveAssignable&, MoveAssignable&> const>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::tuple<NothrowMoveAssignable&, NothrowMoveAssignable&> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		int i1 = 10;
		int i2 = 11;
		double d1 = 12;
		double d2 = 13;
		hamon::tuple<int&, double&> const p1(i1, d1);
		hamon::tuple<int&, double&> p2(i2, d2);

		VERIFY(hamon::adl_get<0>(p1) == i1);
		VERIFY(hamon::adl_get<1>(p1) == d1);
		VERIFY(hamon::adl_get<0>(p2) == i2);
		VERIFY(hamon::adl_get<1>(p2) == d2);

		auto&& r = (p1 = hamon::move(p2));
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

GTEST_TEST(TupleTest, AssignMoveConstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_move_const_test

}	// namespace hamon_tuple_test
