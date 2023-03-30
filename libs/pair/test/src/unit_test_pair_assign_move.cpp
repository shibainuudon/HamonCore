/**
 *	@file	unit_test_pair_assign_move.cpp
 *
 *	@brief	ムーブ代入のテスト
 * 
 *	constexpr pair& operator=(pair&& p) noexcept(see below);
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
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

static_assert( hamon::is_move_assignable<hamon::pair<int, int>>::value, "");
static_assert( hamon::is_move_assignable<hamon::pair<MoveAssignable,    int>>::value, "");
static_assert( hamon::is_move_assignable<hamon::pair<int,               MoveAssignable>>::value, "");
static_assert( hamon::is_move_assignable<hamon::pair<MoveAssignable,    MoveAssignable>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::pair<NonMoveAssignable, int>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::pair<int,               NonMoveAssignable>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::pair<NonMoveAssignable, NonMoveAssignable>>::value, "");

static_assert(!hamon::is_move_assignable<hamon::pair<int,  int> const>::value, "");
static_assert(!hamon::is_move_assignable<hamon::pair<int&, int> const>::value, "");
static_assert(!hamon::is_move_assignable<hamon::pair<int,  int&> const>::value, "");
static_assert( hamon::is_move_assignable<hamon::pair<int&, int&> const>::value, "");
static_assert(!hamon::is_move_assignable<hamon::pair<NonMoveAssignable&, NonMoveAssignable&> const>::value, "");
static_assert( hamon::is_move_assignable<hamon::pair<MoveAssignable&, MoveAssignable&> const>::value, "");
static_assert( hamon::is_move_assignable<hamon::pair<NothrowMoveAssignable&, NothrowMoveAssignable&> const>::value, "");

static_assert( hamon::is_nothrow_move_assignable<hamon::pair<int, int>>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::pair<NothrowMoveAssignable, int>>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::pair<int,                   NothrowMoveAssignable>>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::pair<NothrowMoveAssignable, NothrowMoveAssignable>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::pair<MoveAssignable,    int>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::pair<int,               MoveAssignable>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::pair<MoveAssignable,    MoveAssignable>>::value, "");

static_assert(!hamon::is_nothrow_move_assignable<hamon::pair<int,  int> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::pair<int&, int> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::pair<int,  int&> const>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::pair<int&, int&> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::pair<MoveAssignable&,        MoveAssignable&> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::pair<MoveAssignable&,        NothrowMoveAssignable&> const>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::pair<NothrowMoveAssignable&, MoveAssignable&> const>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::pair<NothrowMoveAssignable&, NothrowMoveAssignable&> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	// operator=(pair&& p);
	{
		hamon::pair<int, double> p1(1, 2);
		hamon::pair<int, double> p2(3, 4);

		VERIFY(p1.first  == 1);
		VERIFY(p1.second == 2);
		VERIFY(p2.first  == 3);
		VERIFY(p2.second == 4);

		auto&& r = (p1 = hamon::move(p2));
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

GTEST_TEST(PairTest, AssignMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_move_test

}	// namespace hamon_pair_test
