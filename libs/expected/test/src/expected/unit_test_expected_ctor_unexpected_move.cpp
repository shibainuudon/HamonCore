/**
 *	@file	unit_test_expected_ctor_unexpected_move.cpp
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
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
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

static_assert( hamon::is_constructible<hamon::expected<int, int>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, MoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, NonMoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, NothrowMoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, TriviallyMoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, ExplicitlyMoveConstructible>, hamon::unexpected<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<MoveConstructible, int>, hamon::unexpected<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<NonMoveConstructible, int>, hamon::unexpected<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<NothrowMoveConstructible, int>, hamon::unexpected<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<TriviallyMoveConstructible, int>, hamon::unexpected<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<ExplicitlyMoveConstructible, int>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<CtorFromInt, ConvertibleToInt>, hamon::unexpected<int>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<ConvertibleToInt, CtorFromInt>, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, int>, hamon::unexpected<CtorFromInt>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, int>, hamon::unexpected<ConvertibleToInt>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, MoveConstructible>, hamon::unexpected<MoveConstructible>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, NonMoveConstructible>, hamon::unexpected<NonMoveConstructible>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, NothrowMoveConstructible>, hamon::unexpected<NothrowMoveConstructible>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, TriviallyMoveConstructible>, hamon::unexpected<TriviallyMoveConstructible>&&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, ExplicitlyMoveConstructible>, hamon::unexpected<ExplicitlyMoveConstructible>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<MoveConstructible, int>, hamon::unexpected<MoveConstructible>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<NonMoveConstructible, int>, hamon::unexpected<NonMoveConstructible>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<NothrowMoveConstructible, int>, hamon::unexpected<NothrowMoveConstructible>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<TriviallyMoveConstructible, int>, hamon::unexpected<TriviallyMoveConstructible>&&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<ExplicitlyMoveConstructible, int>, hamon::unexpected<ExplicitlyMoveConstructible>&&>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, MoveConstructible>, hamon::unexpected<MoveConstructible>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, NonMoveConstructible>, hamon::unexpected<NonMoveConstructible>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, NothrowMoveConstructible>, hamon::unexpected<NothrowMoveConstructible>&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, TriviallyMoveConstructible>, hamon::unexpected<TriviallyMoveConstructible>&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, ExplicitlyMoveConstructible>, hamon::unexpected<ExplicitlyMoveConstructible>&&>::value, "");
#endif

static_assert( hamon::is_implicitly_constructible<hamon::expected<int, MoveConstructible>, hamon::unexpected<MoveConstructible>&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, NonMoveConstructible>, hamon::unexpected<NonMoveConstructible>&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<int, NothrowMoveConstructible>, hamon::unexpected<NothrowMoveConstructible>&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<int, TriviallyMoveConstructible>, hamon::unexpected<TriviallyMoveConstructible>&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, ExplicitlyMoveConstructible>, hamon::unexpected<ExplicitlyMoveConstructible>&&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		hamon::unexpected<E> src{E{10}};
		hamon::expected<T, E> dst = hamon::move(src);
		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{10});
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	using IntPair  = hamon::pair<int, int>;
	using IntTuple = hamon::tuple<int, int>;
	{
		hamon::unexpected<IntPair> src{hamon::in_place, 1, 2};
		hamon::expected<int, IntTuple> dst = hamon::move(src);
		VERIFY(!dst.has_value());
		VERIFY((dst.error() == IntTuple{1, 2}));
	}
	return true;
}

struct S1
{
	int value;

	HAMON_CXX14_CONSTEXPR S1(int v) : value(v) {}
};

struct S2
{
	int value;

	HAMON_CXX14_CONSTEXPR explicit S2(int v) : value(v) {}
};

HAMON_CXX14_CONSTEXPR bool test3()
{
	{
		hamon::unexpected<int> src{13};
		hamon::expected<S1, S1> dst = hamon::move(src);
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 13);
	}
	{
		hamon::unexpected<int> src{13};
		hamon::expected<S1, S2> dst{hamon::move(src)};
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 13);
	}
	{
		hamon::unexpected<int> src{13};
		hamon::expected<S2, S1> dst = hamon::move(src);
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 13);
	}
	{
		hamon::unexpected<int> src{13};
		hamon::expected<S2, S2> dst{hamon::move(src)};
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 13);
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test4()
{
	using UniquePtr = hamon::unique_ptr<int>;
	using SharedPtr = hamon::shared_ptr<int>;
	{
		hamon::unexpected<UniquePtr> src{hamon::make_unique<int>(42)};
		hamon::expected<int, SharedPtr> dst = hamon::move(src);
		VERIFY(!dst.has_value());
		VERIFY(*dst.error() == 42);
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
		using Expected = hamon::expected<int, ThrowOnCtor>;
		EXPECT_THROW(Expected e{hamon::move(u)}, ThrowOnCtor::Exception);
	}
	{
		hamon::unexpected<int> u{42};
		using Expected = hamon::expected<ThrowOnCtor, int>;
		EXPECT_NO_THROW(Expected e{hamon::move(u)});
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorUnexpectedMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test3()));

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test4()));
#else
	EXPECT_TRUE((test4()));
#endif

	exceptions_test();
}

}	// namespace ctor_unexpected_move_test

}	// namespace hamon_expected_test
