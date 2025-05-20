/**
 *	@file	unit_test_unexpected_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	constexpr unexpected(unexpected&&) = default;
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_implicitly_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace ctor_move_test
{

struct MoveConstructible
{
	MoveConstructible(MoveConstructible&&);
};
static_assert(hamon::is_move_constructible<MoveConstructible>::value, "");

struct NonMoveConstructible
{
	NonMoveConstructible(NonMoveConstructible&&) = delete;
};
static_assert(!hamon::is_move_constructible<NonMoveConstructible>::value, "");

struct NothrowMoveConstructible
{
	NothrowMoveConstructible(NothrowMoveConstructible&&) noexcept;
};
static_assert(hamon::is_nothrow_move_constructible<NothrowMoveConstructible>::value, "");

struct TriviallyMoveConstructible
{
};
static_assert(hamon::is_trivially_move_constructible<TriviallyMoveConstructible>::value, "");

struct ExplicitlyMoveConstructible
{
	explicit ExplicitlyMoveConstructible(ExplicitlyMoveConstructible&&);
};
static_assert( hamon::is_move_constructible<ExplicitlyMoveConstructible>::value, "");
static_assert(!hamon::is_implicitly_move_constructible<ExplicitlyMoveConstructible>::value, "");

static_assert( hamon::is_move_constructible<hamon::unexpected<int>>::value, "");
static_assert( hamon::is_move_constructible<hamon::unexpected<MoveConstructible>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::unexpected<NonMoveConstructible>>::value, "");
static_assert( hamon::is_move_constructible<hamon::unexpected<NothrowMoveConstructible>>::value, "");
static_assert( hamon::is_move_constructible<hamon::unexpected<TriviallyMoveConstructible>>::value, "");
static_assert( hamon::is_move_constructible<hamon::unexpected<ExplicitlyMoveConstructible>>::value, "");

static_assert( hamon::is_nothrow_move_constructible<hamon::unexpected<int>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::unexpected<MoveConstructible>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::unexpected<NonMoveConstructible>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::unexpected<NothrowMoveConstructible>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::unexpected<TriviallyMoveConstructible>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::unexpected<ExplicitlyMoveConstructible>>::value, "");

static_assert( hamon::is_trivially_move_constructible<hamon::unexpected<int>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::unexpected<MoveConstructible>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::unexpected<NonMoveConstructible>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::unexpected<NothrowMoveConstructible>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::unexpected<TriviallyMoveConstructible>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::unexpected<ExplicitlyMoveConstructible>>::value, "");

static_assert( hamon::is_implicitly_move_constructible<hamon::unexpected<int>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::unexpected<MoveConstructible>>::value, "");
static_assert(!hamon::is_implicitly_move_constructible<hamon::unexpected<NonMoveConstructible>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::unexpected<NothrowMoveConstructible>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::unexpected<TriviallyMoveConstructible>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::unexpected<ExplicitlyMoveConstructible>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::unexpected<E> src{E{5}};
	hamon::unexpected<E> dst = hamon::move(src);
	VERIFY(dst.error() == E{5});
	return true;
}

#undef VERIFY

GTEST_TEST(UnexpectedTest, CtorMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace ctor_move_test

}	// namespace hamon_unexpected_test
