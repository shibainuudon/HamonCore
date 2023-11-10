/**
 *	@file	unit_test_tuple_tuple_assign_tuple_like_move.cpp
 *
 *	@brief	tuple-likeなオブジェクトのムーブ代入のテスト
 *
 *	template<tuple-like UTuple> constexpr tuple& operator=(UTuple&& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_tuple_like_move_test
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

static_assert( hamon::is_assignable<hamon::tuple<int>&,   hamon::array<int, 1>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<float>&, hamon::array<int, 1>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int>&,   hamon::array<int*, 1>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<short, float>&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<short, float>&, hamon::array<int, 1>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<short, float>&, hamon::array<int, 3>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<short, float>&, hamon::array<int*, 2>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<MovableInt,  MovableInt>&,  hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<MoveAssignable, MovableInt>&,  hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<MovableInt,  MoveAssignable>&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<MoveAssignable, MoveAssignable>&, hamon::array<int, 2>>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::tuple<int>&,   hamon::array<int, 1>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<float>&, hamon::array<int, 1>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<short, float>&, hamon::array<int, 2>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowMovableInt, NothrowMovableInt>&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<MovableInt,        NothrowMovableInt>&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<NothrowMovableInt, MovableInt>&,        hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<MovableInt,        MovableInt>&,        hamon::array<int, 2>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::tuple<short, float> t((short)1, 2.0f);

		VERIFY(hamon::adl_get<0>(t) == 1);
		VERIFY(hamon::adl_get<1>(t) == 2);

		hamon::array<int, 2> a { 3, 4 };
		auto&& r = (t = hamon::move(a));
		static_assert(hamon::is_same<decltype(r), hamon::tuple<short, float>&>::value, "");
		VERIFY(&r == &t);

		VERIFY(hamon::adl_get<0>(t) == 3);
		VERIFY(hamon::adl_get<1>(t) == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, AssignTupleLikeMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_tuple_like_move_test

}	// namespace hamon_tuple_test
