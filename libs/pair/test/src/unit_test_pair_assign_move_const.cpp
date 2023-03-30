/**
 *	@file	unit_test_pair_assign_move_const.cpp
 *
 *	@brief	ムーブ代入のテスト
 * 
 *	constexpr const pair& operator=(pair&& p) const;
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
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

static_assert(!hamon::is_move_assignable<hamon::pair<int,  int> const>::value, "");
static_assert(!hamon::is_move_assignable<hamon::pair<int&, int> const>::value, "");
static_assert(!hamon::is_move_assignable<hamon::pair<int,  int&> const>::value, "");
static_assert( hamon::is_move_assignable<hamon::pair<int&, int&> const>::value, "");
static_assert(!hamon::is_move_assignable<hamon::pair<NonMoveAssignable&, NonMoveAssignable&> const>::value, "");
static_assert( hamon::is_move_assignable<hamon::pair<MoveAssignable&, MoveAssignable&> const>::value, "");
static_assert( hamon::is_move_assignable<hamon::pair<NothrowMoveAssignable&, NothrowMoveAssignable&> const>::value, "");

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
	// operator=(pair&& p) const;
	{
		int i1 = 10;
		int i2 = 11;
		double d1 = 12;
		double d2 = 13;
		hamon::pair<int&, double&> const p1(i1, d1);
		hamon::pair<int&, double&> p2(i2, d2);

		VERIFY(p1.first  == i1);
		VERIFY(p1.second == d1);
		VERIFY(p2.first  == i2);
		VERIFY(p2.second == d2);

		auto&& r = (p1 = hamon::move(p2));
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

GTEST_TEST(PairTest, AssignMoveConstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_move_const_test

}	// namespace hamon_pair_test
