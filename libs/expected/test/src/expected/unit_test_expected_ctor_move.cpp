/**
 *	@file	unit_test_expected_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	constexpr expected(expected&&) noexcept(see below);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_implicitly_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
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

static_assert( hamon::is_move_constructible<hamon::expected<int, int>>::value, "");
static_assert( hamon::is_move_constructible<hamon::expected<MoveConstructible,    MoveConstructible>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::expected<MoveConstructible,    NonMoveConstructible>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::expected<NonMoveConstructible, MoveConstructible>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::expected<NonMoveConstructible, NonMoveConstructible>>::value, "");

static_assert( hamon::is_nothrow_move_constructible<hamon::expected<int, int>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::expected<MoveConstructible,        MoveConstructible>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::expected<MoveConstructible,        NothrowMoveConstructible>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::expected<NothrowMoveConstructible, MoveConstructible>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::expected<NothrowMoveConstructible, NothrowMoveConstructible>>::value, "");

static_assert( hamon::is_trivially_move_constructible<hamon::expected<int, int>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::expected<MoveConstructible,          MoveConstructible>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::expected<MoveConstructible,          TriviallyMoveConstructible>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::expected<TriviallyMoveConstructible, MoveConstructible>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::expected<TriviallyMoveConstructible, TriviallyMoveConstructible>>::value, "");

static_assert( hamon::is_implicitly_move_constructible<hamon::expected<int, int>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::expected<MoveConstructible,           MoveConstructible>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::expected<MoveConstructible,           ExplicitlyMoveConstructible>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::expected<ExplicitlyMoveConstructible, MoveConstructible>>::value, "");
static_assert( hamon::is_implicitly_move_constructible<hamon::expected<ExplicitlyMoveConstructible, ExplicitlyMoveConstructible>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> x = T{42};
		hamon::expected<T, E> y = hamon::move(x);
		VERIFY(x.has_value());
		VERIFY(y.has_value());
//		VERIFY(x.value() == T{42});
		VERIFY(y.value() == T{42});
	}
	{
		hamon::expected<T, E> x = hamon::unexpected<E>{E{13}};
		hamon::expected<T, E> y = hamon::move(x);
		VERIFY(!x.has_value());
		VERIFY(!y.has_value());
//		VERIFY(x.error() == E{13});
		VERIFY(y.error() == E{13});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		hamon::expected<T, hamon::string> x = T{43};
		hamon::expected<T, hamon::string> y = hamon::move(x);
		VERIFY(x.has_value());
		VERIFY(y.has_value());
//		VERIFY(x.value() == T{43});
		VERIFY(y.value() == T{43});
	}
	{
		hamon::expected<T, hamon::string> x = hamon::unexpected<hamon::string>{"Oops"};
		hamon::expected<T, hamon::string> y = hamon::move(x);
		VERIFY(!x.has_value());
		VERIFY(!y.has_value());
//		VERIFY(x.error() == "Oops");
		VERIFY(y.error() == "Oops");
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
		hamon::expected<ThrowOnMove, int> src;
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<int, ThrowOnMove> src;
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<ThrowOnMove, int> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<int, ThrowOnMove> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<ThrowOnMove, int> src;
		EXPECT_THROW(auto dst = hamon::move(src), ThrowOnMove::Exception);
	}
	{
		hamon::expected<int, ThrowOnMove> src;
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<ThrowOnMove, int> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<int, ThrowOnMove> src{hamon::unexpect};
		EXPECT_THROW(auto dst = hamon::move(src), ThrowOnMove::Exception);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<double>()));

	exceptions_test();
}

}	// namespace ctor_move_test

}	// namespace hamon_expected_test
