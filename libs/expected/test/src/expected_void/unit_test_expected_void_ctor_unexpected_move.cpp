/**
 *	@file	unit_test_expected_void_ctor_unexpected_move.cpp
 *
 *	@brief	unexpected&& からのコンストラクタのテスト
 *
 *	template<class G>
 *	constexpr explicit(see below) expected(unexpected<G>&&);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/memory.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
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

namespace ctor_unexpected_move_test
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

struct CtorFromInt
{
	CtorFromInt(int);
};

struct ConvertibleToInt
{
	operator int() const;
};

static_assert( hamon::is_constructible<hamon::expected<void, int>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, MoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, NonMoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, NothrowMoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, TriviallyMoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, ExplicitlyMoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, ConvertibleToInt>, hamon::unexpected<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, CtorFromInt>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, int>, hamon::unexpected<CtorFromInt>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, int>, hamon::unexpected<ConvertibleToInt>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, MoveConstructible>, hamon::unexpected<MoveConstructible>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, NonMoveConstructible>, hamon::unexpected<NonMoveConstructible>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, NothrowMoveConstructible>, hamon::unexpected<NothrowMoveConstructible>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, TriviallyMoveConstructible>, hamon::unexpected<TriviallyMoveConstructible>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, ExplicitlyMoveConstructible>, hamon::unexpected<ExplicitlyMoveConstructible>&&>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, MoveConstructible>, hamon::unexpected<MoveConstructible>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, NonMoveConstructible>, hamon::unexpected<NonMoveConstructible>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, NothrowMoveConstructible>, hamon::unexpected<NothrowMoveConstructible>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, TriviallyMoveConstructible>, hamon::unexpected<TriviallyMoveConstructible>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, ExplicitlyMoveConstructible>, hamon::unexpected<ExplicitlyMoveConstructible>&&>::value, "");
#endif

static_assert( hamon::is_implicitly_constructible<hamon::expected<void, MoveConstructible>, hamon::unexpected<MoveConstructible>&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, NonMoveConstructible>, hamon::unexpected<NonMoveConstructible>&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<void, NothrowMoveConstructible>, hamon::unexpected<NothrowMoveConstructible>&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<void, TriviallyMoveConstructible>, hamon::unexpected<TriviallyMoveConstructible>&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, ExplicitlyMoveConstructible>, hamon::unexpected<ExplicitlyMoveConstructible>&&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct S1
{
	int value;
	constexpr S1(int v) : value(v) {}
};

struct S2
{
	int value;
	constexpr explicit S2(int v) : value(v) {}
};

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::unexpected<int> src{5};
		hamon::expected<Void, int> dst = hamon::move(src);
		VERIFY(!dst.has_value());
		VERIFY(dst.error() == 5);
	}
	{
		hamon::unexpected<int> src{10};
		hamon::expected<Void, double> dst = hamon::move(src);
		VERIFY(!dst.has_value());
		VERIFY(dst.error() == 10.0);
	}
	{
		hamon::unexpected<int> src{20};
		hamon::expected<Void, S1> dst = hamon::move(src);
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 20);
	}
	{
		hamon::unexpected<int> src{20};
		hamon::expected<Void, S2> dst{hamon::move(src)};
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 20);
	}
	return true;
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowOnCtor
	{
		struct Exception{};
		ThrowOnCtor(int) { throw Exception{}; }
	};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable");
	{
		hamon::unexpected<int> u{42};
		using Expected = hamon::expected<void, ThrowOnCtor>;
		EXPECT_THROW(Expected e{hamon::move(u)}, ThrowOnCtor::Exception);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedVoidTest, CtorUnexpectedMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile>()));

	exceptions_test();
}

}	// namespace ctor_unexpected_move_test

}	// namespace hamon_expected_void_test
