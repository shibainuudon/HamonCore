/**
 *	@file	unit_test_expected_void_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	constexpr expected(expected&& rhs) noexcept(is_nothrow_move_constructible_v<E>);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_implicitly_move_constructible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace ctor_move_test
{

struct MoveConstructible
{
	int value;
	constexpr MoveConstructible(int v) : value(v) {}
	constexpr MoveConstructible(MoveConstructible&& rhs) : value(rhs.value) {}
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

static_assert( hamon::is_move_constructible<hamon::expected<void, int>>::value, "");
static_assert( hamon::is_move_constructible<hamon::expected<void, MoveConstructible>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::expected<void, NonMoveConstructible>>::value, "");
static_assert( hamon::is_move_constructible<hamon::expected<void, NothrowMoveConstructible>>::value, "");
static_assert( hamon::is_move_constructible<hamon::expected<void, TriviallyMoveConstructible>>::value, "");
static_assert( hamon::is_move_constructible<hamon::expected<void, ExplicitlyMoveConstructible>>::value, "");

static_assert( hamon::is_nothrow_move_constructible<hamon::expected<void, int>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::expected<void, MoveConstructible>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::expected<void, NonMoveConstructible>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::expected<void, NothrowMoveConstructible>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::expected<void, TriviallyMoveConstructible>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::expected<void, ExplicitlyMoveConstructible>>::value, "");

static_assert( hamon::is_trivially_move_constructible<hamon::expected<void, int>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::expected<void, MoveConstructible>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::expected<void, NonMoveConstructible>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::expected<void, NothrowMoveConstructible>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::expected<void, TriviallyMoveConstructible>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::expected<void, ExplicitlyMoveConstructible>>::value, "");

static_assert( hamon::is_implicitly_move_constructible<hamon::expected<void, int>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::expected<void, MoveConstructible>>::value, "");
static_assert(!hamon::is_implicitly_move_constructible<hamon::expected<void, NonMoveConstructible>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::expected<void, NothrowMoveConstructible>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::expected<void, TriviallyMoveConstructible>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::expected<void, ExplicitlyMoveConstructible>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test1()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, int> x{hamon::in_place};
		hamon::expected<Void, int> y = hamon::move(x);
		VERIFY(x.has_value());
		VERIFY(y.has_value());
	}
	{
		hamon::expected<Void, int> x{hamon::unexpect, 42};
		hamon::expected<Void, int> y = hamon::move(x);
		VERIFY(!x.has_value());
		VERIFY(!y.has_value());
//		VERIFY(x.error() == 42);
		VERIFY(y.error() == 42);
	}

	return true;
}

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test2()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, MoveConstructible> x{hamon::in_place};
		hamon::expected<Void, MoveConstructible> y = hamon::move(x);
		VERIFY(x.has_value());
		VERIFY(y.has_value());
	}
	{
		hamon::expected<Void, MoveConstructible> x{hamon::unexpect, 42};
		hamon::expected<Void, MoveConstructible> y = hamon::move(x);
		VERIFY(!x.has_value());
		VERIFY(!y.has_value());
//		VERIFY(x.error().value == 42);
		VERIFY(y.error().value == 42);
	}

	return true;
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowOnMove
	{
		struct Exception{};
		ThrowOnMove() = default;
		ThrowOnMove(ThrowOnMove const&) = default;
		ThrowOnMove(ThrowOnMove&&) { throw Exception{}; }
	};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable");
	{
		hamon::expected<void, int> src;
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<void, ThrowOnMove> src;
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<void, int> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<void, ThrowOnMove> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<void, int> src;
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<void, ThrowOnMove> src;
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<void, int> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<void, ThrowOnMove> src{hamon::unexpect};
		EXPECT_THROW(auto dst = hamon::move(src), ThrowOnMove::Exception);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedVoidTest, CtorMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<void const volatile>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<void>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<void const>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<void volatile>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<void const volatile>()));

	exceptions_test();
}

}	// namespace ctor_move_test

}	// namespace hamon_expected_void_test
