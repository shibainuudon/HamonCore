/**
 *	@file	unit_test_pair_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 * 
 *	pair(pair&&) = default;
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_move_test
{

struct NonMovable
{
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

static_assert( hamon::is_move_constructible<hamon::pair<int,      int>>::value, "");
static_assert( hamon::is_move_constructible<hamon::pair<Movable, int>>::value, "");
static_assert( hamon::is_move_constructible<hamon::pair<int,      Movable>>::value, "");
static_assert( hamon::is_move_constructible<hamon::pair<Movable, Movable>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::pair<NonMovable, int>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::pair<int,         NonMovable>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::pair<NonMovable, NonMovable>>::value, "");

static_assert( hamon::is_nothrow_move_constructible<hamon::pair<int,      int>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::pair<NothrowMovable, int>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::pair<int,             NothrowMovable>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::pair<NothrowMovable, NothrowMovable>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::pair<Movable, int>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::pair<int,      Movable>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::pair<Movable, Movable>>::value, "");

static_assert( hamon::is_trivially_move_constructible<hamon::pair<int,      int>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::pair<TriviallyMovable, int>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::pair<int,               TriviallyMovable>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::pair<TriviallyMovable, TriviallyMovable>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::pair<NothrowMovable, int>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::pair<int,             NothrowMovable>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::pair<NothrowMovable, NothrowMovable>>::value, "");

GTEST_TEST(PairTest, CtorMoveTest)
{
	{
		hamon::pair<int, double> p1(1, 2);
		hamon::pair<int, double> p2(hamon::move(p1));
		EXPECT_EQ(1, p2.first);
		EXPECT_EQ(2, p2.second);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, double> p1(1, 2);
		HAMON_CXX11_CONSTEXPR hamon::pair<int, double> p2(hamon::move(p1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p2.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p2.second);
	}
}

}	// namespace ctor_move_test

}	// namespace hamon_pair_test
