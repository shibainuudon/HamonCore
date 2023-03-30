/**
 *	@file	unit_test_pair_assign_move_pair.cpp
 *
 *	@brief	ムーブ代入のテスト
 * 
 *	template<class U1, class U2>
 *	constexpr pair& operator=(pair<U1, U2>&& p);
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace assign_move_pair_test
{

struct MoveAssignable
{
	MoveAssignable(MoveAssignable const&) = delete;
	MoveAssignable& operator=(MoveAssignable&&);
};

struct MovableInt
{
	MovableInt(MovableInt const&) = delete;
	MovableInt(MovableInt&&) = delete;
	MovableInt& operator=(MovableInt const&) = delete;
	MovableInt& operator=(MovableInt&&) = delete;
	MovableInt& operator=(int);
};

struct NothrowMovableInt
{
	NothrowMovableInt(NothrowMovableInt const&) = delete;
	NothrowMovableInt(NothrowMovableInt&&) = delete;
	NothrowMovableInt& operator=(NothrowMovableInt const&) = delete;
	NothrowMovableInt& operator=(NothrowMovableInt&&) = delete;
	NothrowMovableInt& operator=(int) noexcept;
};

static_assert( hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<short, int>>::value, "");
static_assert( hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<int,   short>>::value, "");
static_assert( hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<short, short>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<int*,  int>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<int,   int*>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int, int>&, hamon::pair<int*,  int*>>::value, "");
static_assert( hamon::is_assignable<hamon::pair<MovableInt,  MovableInt>&,  hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<MoveAssignable, MovableInt>&,  hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<MovableInt,  MoveAssignable>&, hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<MoveAssignable, MoveAssignable>&, hamon::pair<int, int>>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::pair<int, int>&, hamon::pair<short, int>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<int, int>&, hamon::pair<int,   short>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<int, int>&, hamon::pair<short, short>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<NothrowMovableInt, NothrowMovableInt>&, hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<MovableInt,        NothrowMovableInt>&, hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<NothrowMovableInt, MovableInt>&,        hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<MovableInt,        MovableInt>&,        hamon::pair<int, int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	// operator=(pair<U1, U2>&& p);
	{
		hamon::pair<short, float> p1(1, 2);
		hamon::pair<int, double> p2(3, 4);

		VERIFY(p1.first  == 1);
		VERIFY(p1.second == 2);
		VERIFY(p2.first  == 3);
		VERIFY(p2.second == 4);

		auto&& r = (p1 = hamon::move(p2));
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

GTEST_TEST(PairTest, AssignMovePairTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_move_pair_test

}	// namespace hamon_pair_test
