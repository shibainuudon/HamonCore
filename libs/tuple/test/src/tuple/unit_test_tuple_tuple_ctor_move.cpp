/**
 *	@file	unit_test_tuple_tuple_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	tuple(tuple&& u) = default;
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

namespace ctor_move_test
{

struct NonMovable
{
	NonMovable() {}
	NonMovable(NonMovable const&) = delete;
	NonMovable& operator=(NonMovable const&) = delete;
	NonMovable(NonMovable &&) = delete;
	NonMovable& operator=(NonMovable &&) = delete;
};

struct Movable
{
	Movable(Movable const&) = delete;
	Movable& operator=(Movable const&) = delete;
	Movable(Movable &&);
};

struct NothrowMovable
{
	NothrowMovable(NothrowMovable const&) = delete;
	NothrowMovable& operator=(NothrowMovable const&) = delete;
	NothrowMovable(NothrowMovable &&) noexcept;
};

struct TriviallyMovable
{
	TriviallyMovable(TriviallyMovable const&) = delete;
	TriviallyMovable& operator=(TriviallyMovable const&) = delete;
	TriviallyMovable(TriviallyMovable &&) = default;
};

static_assert(!hamon::is_move_constructible<NonMovable>::value, "");
static_assert( hamon::is_move_constructible<Movable>::value, "");
static_assert( hamon::is_move_constructible<NothrowMovable>::value, "");
static_assert( hamon::is_move_constructible<TriviallyMovable>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<NonMovable>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<Movable>::value, "");
static_assert( hamon::is_nothrow_move_constructible<NothrowMovable>::value, "");
static_assert( hamon::is_nothrow_move_constructible<TriviallyMovable>::value, "");
static_assert(!hamon::is_trivially_move_constructible<NonMovable>::value, "");
static_assert(!hamon::is_trivially_move_constructible<Movable>::value, "");
static_assert(!hamon::is_trivially_move_constructible<NothrowMovable>::value, "");
static_assert( hamon::is_trivially_move_constructible<TriviallyMovable>::value, "");

static_assert( hamon::is_move_constructible<hamon::tuple<int,     int>>::value, "");
static_assert( hamon::is_move_constructible<hamon::tuple<Movable, int>>::value, "");
static_assert( hamon::is_move_constructible<hamon::tuple<int,     Movable>>::value, "");
static_assert( hamon::is_move_constructible<hamon::tuple<Movable, Movable>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::tuple<NonMovable, int>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::tuple<int,        NonMovable>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::tuple<NonMovable, NonMovable>>::value, "");

static_assert( hamon::is_nothrow_move_constructible<hamon::tuple<int,      int>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::tuple<NothrowMovable, int>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::tuple<int,            NothrowMovable>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::tuple<NothrowMovable, NothrowMovable>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::tuple<Movable, int>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::tuple<int,     Movable>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::tuple<Movable, Movable>>::value, "");

static_assert( hamon::is_trivially_move_constructible<hamon::tuple<int,      int>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::tuple<TriviallyMovable, int>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::tuple<int,              TriviallyMovable>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::tuple<TriviallyMovable, TriviallyMovable>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::tuple<NothrowMovable, int>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::tuple<int,            NothrowMovable>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::tuple<NothrowMovable, NothrowMovable>>::value, "");

GTEST_TEST(TupleTest, CtorMoveTest)
{
	{
		hamon::tuple<int, double> t1(1, 2);
		hamon::tuple<int, double> t2(hamon::move(t1));
		EXPECT_EQ(1, hamon::adl_get<0>(t2));
		EXPECT_EQ(2, hamon::adl_get<1>(t2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, double> t1(1, 2);
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, double> t2(hamon::move(t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::adl_get<0>(t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::adl_get<1>(t2));
	}
}

}	// namespace ctor_move_test

}	// namespace hamon_tuple_test
