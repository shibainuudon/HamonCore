/**
 *	@file	unit_test_pair_assign_pair_like_move.cpp
 *
 *	@brief	pair-likeなオブジェクトからのムーブ代入のテスト
 * 
 *	template<pair-like P>
 *	constexpr pair& operator=(P&& p);
 */

#include <hamon/pair.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace assign_pair_like_move_test
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

static_assert(!hamon::is_assignable<hamon::pair<short, float>&, hamon::array<int, 1>>::value, "");
static_assert( hamon::is_assignable<hamon::pair<short, float>&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<short, float>&, hamon::array<int, 3>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<short, float>&, hamon::array<int*, 2>>::value, "");
static_assert( hamon::is_assignable<hamon::pair<MovableInt,  MovableInt>&,  hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<MoveAssignable, MovableInt>&,  hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<MovableInt,  MoveAssignable>&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<MoveAssignable, MoveAssignable>&, hamon::array<int, 2>>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::pair<int, int>&,   hamon::array<int, 2>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<float, long>&, hamon::array<int, 2>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<NothrowMovableInt, NothrowMovableInt>&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<MovableInt,        NothrowMovableInt>&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<NothrowMovableInt, MovableInt>&,        hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<MovableInt,        MovableInt>&,        hamon::array<int, 2>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::pair<short, float> p((short)1, 2.0f);

		VERIFY(hamon::adl_get<0>(p) == 1);
		VERIFY(hamon::adl_get<1>(p) == 2);

		hamon::array<int, 2> a { 3, 4 };
		auto&& r = (p = hamon::move(a));
		static_assert(hamon::is_same<decltype(r), hamon::pair<short, float>&>::value, "");
		VERIFY(&r == &p);

		VERIFY(hamon::adl_get<0>(p) == 3);
		VERIFY(hamon::adl_get<1>(p) == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, AssignPairLikeMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_pair_like_move_test

}	// namespace hamon_pair_test
