/**
 *	@file	unit_test_expected_void_swap_free.cpp
 *
 *	@brief	swap のテスト
 *
 *	friend constexpr void swap(expected& x, expected& y) noexcept(noexcept(x.swap(y)));
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace swap_free_test
{

// Test constraint
static_assert(hamon::is_swappable<hamon::expected<void, int>>::value, "");

struct NotSwappable
{
	NotSwappable& operator=(const NotSwappable&) = delete;
};
void swap(NotSwappable&, NotSwappable&) = delete;

// !is_swappable_v<E>
static_assert(!hamon::is_swappable<hamon::expected<void, NotSwappable>>::value, "");

struct NotMoveConstructible
{
	NotMoveConstructible(NotMoveConstructible&&) = delete;
	friend void swap(NotMoveConstructible&, NotMoveConstructible&) {}
};

// !is_move_constructible_v<E>
static_assert(!hamon::is_swappable<hamon::expected<void, NotMoveConstructible>>::value, "");

// Test noexcept
struct MoveMayThrow
{
	MoveMayThrow(MoveMayThrow&&) noexcept(false);
	friend void swap(MoveMayThrow&, MoveMayThrow&) noexcept {}
};

static_assert(hamon::is_nothrow_swappable<hamon::expected<void, int>>::value, "");

// !is_nothrow_move_constructible_v<E>
static_assert(!hamon::is_nothrow_swappable<hamon::expected<void, MoveMayThrow>>::value, "");

struct SwapMayThrow
{
	friend void swap(SwapMayThrow&, SwapMayThrow&) noexcept(false) {}
};

// !is_nothrow_swappable_v<E>
static_assert(!hamon::is_nothrow_swappable<hamon::expected<void, SwapMayThrow>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");

	using Expected = hamon::expected<Void, E>;

	using hamon::swap;
	static_assert(hamon::is_same<decltype(swap(hamon::declval<Expected&>(), hamon::declval<Expected&>())), void>::value, "");

	{
		Expected e1{hamon::in_place};
		Expected e2{hamon::in_place};
		swap(e1, e2);
		VERIFY(e1.has_value());
		VERIFY(e2.has_value());
	}
	{
		Expected e1{hamon::in_place};
		Expected e2{hamon::unexpect, E{21}};
		swap(e1, e2);
		VERIFY(!e1.has_value());
		VERIFY(e1.error() == E{21});
		VERIFY(e2.has_value());
	}
	{
		Expected e1{hamon::unexpect, E{12}};
		Expected e2{hamon::in_place};
		swap(e1, e2);
		VERIFY(e1.has_value());
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{12});
	}
	{
		Expected e1{hamon::unexpect, E{13}};
		Expected e2{hamon::unexpect, E{23}};
		swap(e1, e2);
		VERIFY(!e1.has_value());
		VERIFY(e1.error() == E{23});
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{13});
	}
	return true;
}

struct S2
{
	static int default_ctor_count;
	static int copy_ctor_count;
	static int move_ctor_count;
	static int copy_assign_count;
	static int move_assign_count;
	static int dtor_count;
	static int swap_count;

	S2()
	{
		++default_ctor_count;
	}

	S2(S2 const&)
	{
		++copy_ctor_count;
	}

	S2(S2&&)
	{
		++move_ctor_count;
	}

	S2& operator=(S2 const&)
	{
		++copy_assign_count;
		return *this;
	}

	S2& operator=(S2&&)
	{
		++move_assign_count;
		return *this;
	}

	~S2()
	{
		++dtor_count;
	}

	friend void swap(S2&, S2&)
	{
		++swap_count;
	}

	static void reset()
	{
		default_ctor_count = 0;
		copy_ctor_count = 0;
		move_ctor_count = 0;
		copy_assign_count = 0;
		move_assign_count = 0;
		dtor_count = 0;
		swap_count = 0;
	}
};
int S2::default_ctor_count = 0;
int S2::copy_ctor_count = 0;
int S2::move_ctor_count = 0;
int S2::copy_assign_count = 0;
int S2::move_assign_count = 0;
int S2::dtor_count = 0;
int S2::swap_count = 0;

void trase_test()
{
	S2::reset();
	{
		hamon::expected<void, S2> e1{hamon::in_place};
		hamon::expected<void, S2> e2{hamon::in_place};
		swap(e1, e2);
		EXPECT_EQ(0, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(0, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(0, S2::dtor_count);
		EXPECT_EQ(0, S2::swap_count);
	}
	EXPECT_EQ(0, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(0, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(0, S2::dtor_count);
	EXPECT_EQ(0, S2::swap_count);

	S2::reset();
	{
		hamon::expected<void, S2> e1{hamon::in_place};
		hamon::expected<void, S2> e2{hamon::unexpect};
		swap(e1, e2);
		EXPECT_EQ(1, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(1, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(1, S2::dtor_count);
		EXPECT_EQ(0, S2::swap_count);
	}
	EXPECT_EQ(1, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(1, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(2, S2::dtor_count);
	EXPECT_EQ(0, S2::swap_count);

	S2::reset();
	{
		hamon::expected<void, S2> e1{hamon::unexpect};
		hamon::expected<void, S2> e2{hamon::in_place};
		swap(e1, e2);
		EXPECT_EQ(1, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(1, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(1, S2::dtor_count);
		EXPECT_EQ(0, S2::swap_count);
	}
	EXPECT_EQ(1, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(1, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(2, S2::dtor_count);
	EXPECT_EQ(0, S2::swap_count);

	S2::reset();
	{
		hamon::expected<void, S2> e1{hamon::unexpect};
		hamon::expected<void, S2> e2{hamon::unexpect};
		swap(e1, e2);
		EXPECT_EQ(2, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(0, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(0, S2::dtor_count);
		EXPECT_EQ(1, S2::swap_count);
	}
	EXPECT_EQ(2, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(0, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(2, S2::dtor_count);
	EXPECT_EQ(1, S2::swap_count);
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowOnMoveCtor
	{
		struct Exception{};
		int value;
		ThrowOnMoveCtor(int v) : value(v) {}
		ThrowOnMoveCtor(ThrowOnMoveCtor const&) = default;
		ThrowOnMoveCtor(ThrowOnMoveCtor&&) { throw Exception{}; }
		ThrowOnMoveCtor& operator=(ThrowOnMoveCtor const&) = default;
	};

	{
		hamon::expected<void, ThrowOnMoveCtor> e1(hamon::in_place);
		hamon::expected<void, ThrowOnMoveCtor> e2(hamon::in_place);
		EXPECT_NO_THROW(swap(e1, e2));
		EXPECT_TRUE(e1.has_value());
		EXPECT_TRUE(e2.has_value());
	}
	{
		hamon::expected<void, ThrowOnMoveCtor> e1(hamon::in_place);
		hamon::expected<void, ThrowOnMoveCtor> e2(hamon::unexpect, 20);
		EXPECT_THROW(swap(e1, e2), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(e1.has_value());
		EXPECT_TRUE(!e2.has_value());
		EXPECT_TRUE(e2.error().value == 20);
	}
	{
		hamon::expected<void, ThrowOnMoveCtor> e1(hamon::unexpect, 10);
		hamon::expected<void, ThrowOnMoveCtor> e2(hamon::in_place);
		EXPECT_THROW(swap(e1, e2), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(!e1.has_value());
		EXPECT_TRUE(e1.error().value == 10);
		EXPECT_TRUE(e2.has_value());
	}
	{
		hamon::expected<void, ThrowOnMoveCtor> e1(hamon::unexpect, 10);
		hamon::expected<void, ThrowOnMoveCtor> e2(hamon::unexpect, 20);
		EXPECT_THROW(swap(e1, e2), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(!e1.has_value());
		EXPECT_TRUE(e1.error().value == 10);
		EXPECT_TRUE(!e2.has_value());
		EXPECT_TRUE(e2.error().value == 20);
	}
#endif
}

GTEST_TEST(ExpectedVoidTest, SwapFreeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, float>()));

	trase_test();

	exceptions_test();
}

}	// namespace swap_free_test

}	// namespace hamon_expected_void_test
