/**
 *	@file	unit_test_tuple_tuple_assign_move.cpp
 *
 *	@brief	ムーブ代入のテスト
 *
 *	constexpr tuple& operator=(tuple&& u) noexcept(see below);
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

namespace assign_move_test
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

static_assert(!hamon::is_move_assignable<NonMoveAssignable>::value, "");
static_assert( hamon::is_move_assignable<MoveAssignable>::value, "");
static_assert( hamon::is_move_assignable<NothrowMoveAssignable>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<NonMoveAssignable>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<MoveAssignable>::value, "");
static_assert( hamon::is_nothrow_move_assignable<NothrowMoveAssignable>::value, "");

static_assert( hamon::is_move_assignable<hamon::tuple<int, int>>::value, "");
static_assert( hamon::is_move_assignable<hamon::tuple<MoveAssignable,    int>>::value, "");
static_assert( hamon::is_move_assignable<hamon::tuple<int,               MoveAssignable>>::value, "");
static_assert( hamon::is_move_assignable<hamon::tuple<MoveAssignable,    MoveAssignable>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::tuple<NonMoveAssignable, int>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::tuple<int,               NonMoveAssignable>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::tuple<NonMoveAssignable, NonMoveAssignable>>::value, "");

static_assert( hamon::is_nothrow_move_assignable<hamon::tuple<int, int>>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::tuple<NothrowMoveAssignable, int>>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::tuple<int,                   NothrowMoveAssignable>>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::tuple<NothrowMoveAssignable, NothrowMoveAssignable>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::tuple<MoveAssignable,    int>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::tuple<int,               MoveAssignable>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::tuple<MoveAssignable,    MoveAssignable>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::tuple<int, double> p1(1, 2);
		hamon::tuple<int, double> p2(3, 4);

		VERIFY(hamon::adl_get<0>(p1) == 1);
		VERIFY(hamon::adl_get<1>(p1) == 2);
		VERIFY(hamon::adl_get<0>(p2) == 3);
		VERIFY(hamon::adl_get<1>(p2) == 4);

		auto&& r = (p1 = hamon::move(p2));
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

GTEST_TEST(TupleTest, AssignMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_move_test

}	// namespace hamon_tuple_test
