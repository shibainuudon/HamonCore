/**
 *	@file	unit_test_tuple_tuple_assign_pair_move.cpp
 *
 *	@brief	pair<U1, U2>からのムーブ代入のテスト
 *
 *	template<class U1, class U2> constexpr tuple& operator=(pair<U1, U2>&& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_pair_move_test
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

static_assert(!hamon::is_assignable<hamon::tuple<MovableInt>&,  hamon::pair<int, int>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<short, int>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<int,   short>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<short, short>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<int*,  int>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<int,   int*>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<int*,  int*>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<MovableInt,  MovableInt>&,  hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<MoveAssignable, MovableInt>&,  hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<MovableInt,  MoveAssignable>&, hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<MoveAssignable, MoveAssignable>&, hamon::pair<int, int>>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::tuple<int, int>&, hamon::pair<short, int>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<int, int>&, hamon::pair<int,   short>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<int, int>&, hamon::pair<short, short>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowMovableInt, NothrowMovableInt>&, hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<MovableInt,        NothrowMovableInt>&, hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<NothrowMovableInt, MovableInt>&,        hamon::pair<int, int>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<MovableInt,        MovableInt>&,        hamon::pair<int, int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::tuple<short, float> p1((short)1, 2.0f);
		hamon::pair<int, double> p2(3, 4);

		VERIFY(hamon::adl_get<0>(p1) == 1);
		VERIFY(hamon::adl_get<1>(p1) == 2);
		VERIFY(hamon::adl_get<0>(p2) == 3);
		VERIFY(hamon::adl_get<1>(p2) == 4);

		auto&& r = (p1 = hamon::move(p2));
		static_assert(hamon::is_same<decltype(r), hamon::tuple<short, float>&>::value, "");
		VERIFY(&r == &p1);

		VERIFY(hamon::adl_get<0>(p1) == 3);
		VERIFY(hamon::adl_get<1>(p1) == 4);
		VERIFY(hamon::adl_get<0>(p2) == 3);
		VERIFY(hamon::adl_get<1>(p2) == 4);
	}

	return true;
}

HAMON_WARNING_POP()

#undef VERIFY

GTEST_TEST(TupleTest, AssignPairMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_pair_move_test

}	// namespace hamon_tuple_test
