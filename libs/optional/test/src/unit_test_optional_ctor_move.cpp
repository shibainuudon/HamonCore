/**
 *	@file	unit_test_optional_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	constexpr optional(optional&& rhs) noexcept(see below);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
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

static_assert( hamon::is_move_constructible<hamon::optional<int>>::value, "");
static_assert( hamon::is_move_constructible<hamon::optional<Movable>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::optional<NonMovable>>::value, "");

static_assert( hamon::is_nothrow_move_constructible<hamon::optional<int>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::optional<NothrowMovable>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::optional<Movable>>::value, "");

static_assert( hamon::is_trivially_move_constructible<hamon::optional<int>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::optional<TriviallyMovable>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::optional<NothrowMovable>>::value, "");

GTEST_TEST(OptionalTest, CtorMoveTest)
{
	{
		hamon::optional<int> t1 = 3;
		hamon::optional<int> t2(hamon::move(t1));
		EXPECT_EQ(3, t2.value());
		EXPECT_EQ(3, *t2);
	}
	{
		hamon::optional<hamon::string> t1 = "Hello";
		hamon::optional<hamon::string> t2(hamon::move(t1));
		EXPECT_EQ("Hello", t2.value());
		EXPECT_EQ("Hello", *t2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> t1 = 3;
		HAMON_CXX11_CONSTEXPR hamon::optional<int> t2(hamon::move(t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, t2.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, *t2);
	}
}

}	// namespace ctor_move_test

}	// namespace hamon_optional_test
