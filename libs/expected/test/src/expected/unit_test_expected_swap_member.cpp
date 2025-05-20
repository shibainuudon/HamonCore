/**
 *	@file	unit_test_expected_swap_member.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(expected& rhs) noexcept(see below);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace swap_member_test
{

// Test Constraints:
template <typename T, typename E, typename = void>
struct HasMemberSwap
	: hamon::false_type{};

template <typename T, typename E>
struct HasMemberSwap<T, E, hamon::void_t<decltype(
	hamon::declval<hamon::expected<T, E>&>().swap(hamon::declval<hamon::expected<T, E>&>()))>>
	: hamon::true_type{};

static_assert(HasMemberSwap<int, int>::value, "");

struct NotSwappable {};
void swap(NotSwappable&, NotSwappable&) = delete;

// !is_swappable_v<T>
static_assert(!HasMemberSwap<NotSwappable, int>::value, "");

// !is_swappable_v<E>
static_assert(!HasMemberSwap<int, NotSwappable>::value, "");

struct NotMoveConstructible
{
	NotMoveConstructible(NotMoveConstructible&&) = delete;
	friend void swap(NotMoveConstructible&, NotMoveConstructible&) {}
};

// !is_move_constructible_v<T>
static_assert(!HasMemberSwap<NotMoveConstructible, int>::value, "");

// !is_move_constructible_v<E>
static_assert(!HasMemberSwap<int, NotMoveConstructible>::value, "");

struct MoveMayThrow
{
	MoveMayThrow(MoveMayThrow&&) noexcept(false);
	friend void swap(MoveMayThrow&, MoveMayThrow&) noexcept {}
};

// !is_nothrow_move_constructible_v<T> && is_nothrow_move_constructible_v<E>
static_assert(HasMemberSwap<MoveMayThrow, int>::value, "");

// is_nothrow_move_constructible_v<T> && !is_nothrow_move_constructible_v<E>
static_assert(HasMemberSwap<int, MoveMayThrow>::value, "");

// !is_nothrow_move_constructible_v<T> && !is_nothrow_move_constructible_v<E>
static_assert(!HasMemberSwap<MoveMayThrow, MoveMayThrow>::value, "");

// Test noexcept
template <typename T, typename E>
struct MemberSwapNoexcept : hamon::bool_constant<noexcept(
	hamon::declval<hamon::expected<T, E>&>().swap(hamon::declval<hamon::expected<T, E>&>()))>{};

static_assert(MemberSwapNoexcept<int, int>::value, "");

// !is_nothrow_move_constructible_v<T>
static_assert(!MemberSwapNoexcept<MoveMayThrow, int>::value, "");

// !is_nothrow_move_constructible_v<E>
static_assert(!MemberSwapNoexcept<int, MoveMayThrow>::value, "");

struct SwapMayThrow
{
	friend void swap(SwapMayThrow&, SwapMayThrow&) noexcept(false) {}
};

// !is_nothrow_swappable_v<T>
static_assert(!MemberSwapNoexcept<SwapMayThrow, int>::value, "");

// !is_nothrow_swappable_v<E>
static_assert(!MemberSwapNoexcept<int, SwapMayThrow>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Expected = hamon::expected<T, E>;
	static_assert(hamon::is_same<decltype(hamon::declval<Expected&>().swap(hamon::declval<Expected&>())), void>::value, "");

	{
		Expected e1{hamon::in_place, T{10}};
		Expected e2{hamon::in_place, T{20}};
		e1.swap(e2);
		VERIFY(e1.has_value());
		VERIFY(e1.value() == T{20});
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{10});
	}
	{
		Expected e1{hamon::in_place, T{11}};
		Expected e2{hamon::unexpect, E{21}};
		e1.swap(e2);
		VERIFY(!e1.has_value());
		VERIFY(e1.error() == E{21});
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{11});
	}
	{
		Expected e1{hamon::unexpect, E{12}};
		Expected e2{hamon::in_place, T{22}};
		e1.swap(e2);
		VERIFY(e1.has_value());
		VERIFY(e1.value() == T{22});
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{12});
	}
	{
		Expected e1{hamon::unexpect, E{13}};
		Expected e2{hamon::unexpect, E{23}};
		e1.swap(e2);
		VERIFY(!e1.has_value());
		VERIFY(e1.error() == E{23});
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{13});
	}
	return true;
}

struct S1
{
	int value;

	HAMON_CXX14_CONSTEXPR S1(int v) : value(v) {}
	HAMON_CXX14_CONSTEXPR S1(S1 const&) = default;
	HAMON_CXX14_CONSTEXPR S1(S1&& rhs) : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR S1& operator=(S1 const&) = default;
	HAMON_CXX14_CONSTEXPR S1& operator=(S1&&) = default;
};

HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		hamon::expected<int, S1> e1{hamon::in_place, 1};
		hamon::expected<int, S1> e2{hamon::in_place, 2};
		e1.swap(e2);
		VERIFY(e1.has_value());
		VERIFY(e1.value() == 2);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 1);
	}
	{
		hamon::expected<int, S1> e1{hamon::in_place, 3};
		hamon::expected<int, S1> e2{hamon::unexpect, 4};
		e1.swap(e2);
		VERIFY(!e1.has_value());
		VERIFY(e1.error().value == 4);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 3);
	}
	{
		hamon::expected<int, S1> e1{hamon::unexpect, 5};
		hamon::expected<int, S1> e2{hamon::in_place, 6};
		e1.swap(e2);
		VERIFY(e1.has_value());
		VERIFY(e1.value() == 6);
		VERIFY(!e2.has_value());
		VERIFY(e2.error().value == 5);
	}
	{
		hamon::expected<int, S1> e1{hamon::unexpect, 7};
		hamon::expected<int, S1> e2{hamon::unexpect, 8};
		e1.swap(e2);
		VERIFY(!e1.has_value());
		VERIFY(e1.error().value == 8);
		VERIFY(!e2.has_value());
		VERIFY(e2.error().value == 7);
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

struct S3
{
	static int default_ctor_count;
	static int copy_ctor_count;
	static int move_ctor_count;
	static int copy_assign_count;
	static int move_assign_count;
	static int dtor_count;
	static int swap_count;

	S3()
	{
		++default_ctor_count;
	}

	S3(S3 const&)
	{
		++copy_ctor_count;
	}

	S3(S3&&) noexcept
	{
		++move_ctor_count;
	}

	S3& operator=(S3 const&)
	{
		++copy_assign_count;
		return *this;
	}

	S3& operator=(S3&&)
	{
		++move_assign_count;
		return *this;
	}

	~S3()
	{
		++dtor_count;
	}

	friend void swap(S3&, S3&)
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
int S3::default_ctor_count = 0;
int S3::copy_ctor_count = 0;
int S3::move_ctor_count = 0;
int S3::copy_assign_count = 0;
int S3::move_assign_count = 0;
int S3::dtor_count = 0;
int S3::swap_count = 0;

void trase_test()
{
	S2::reset();
	S3::reset();
	{
		hamon::expected<S2, S3> e1{hamon::in_place};
		hamon::expected<S2, S3> e2{hamon::in_place};
		e1.swap(e2);
		EXPECT_EQ(2, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(0, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(0, S2::dtor_count);
		EXPECT_EQ(1, S2::swap_count);
		EXPECT_EQ(0, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
		EXPECT_EQ(0, S3::swap_count);
	}
	EXPECT_EQ(2, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(0, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(2, S2::dtor_count);
	EXPECT_EQ(1, S2::swap_count);
	EXPECT_EQ(0, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(0, S3::dtor_count);
	EXPECT_EQ(0, S3::swap_count);

	S2::reset();
	S3::reset();
	{
		hamon::expected<S2, S3> e1{hamon::in_place};
		hamon::expected<S2, S3> e2{hamon::unexpect};
		e1.swap(e2);
		EXPECT_EQ(1, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(1, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(1, S2::dtor_count);
		EXPECT_EQ(0, S2::swap_count);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(2, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(2, S3::dtor_count);
		EXPECT_EQ(0, S3::swap_count);
	}
	EXPECT_EQ(1, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(1, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(2, S2::dtor_count);
	EXPECT_EQ(0, S2::swap_count);
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(2, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(3, S3::dtor_count);
	EXPECT_EQ(0, S3::swap_count);

	S2::reset();
	S3::reset();
	{
		hamon::expected<S2, S3> e1{hamon::unexpect};
		hamon::expected<S2, S3> e2{hamon::in_place};
		e1.swap(e2);
		EXPECT_EQ(1, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(1, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(1, S2::dtor_count);
		EXPECT_EQ(0, S2::swap_count);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(2, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(2, S3::dtor_count);
		EXPECT_EQ(0, S3::swap_count);
	}
	EXPECT_EQ(1, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(1, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(2, S2::dtor_count);
	EXPECT_EQ(0, S2::swap_count);
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(2, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(3, S3::dtor_count);
	EXPECT_EQ(0, S3::swap_count);

	S2::reset();
	S3::reset();
	{
		hamon::expected<S2, S3> e1{hamon::unexpect};
		hamon::expected<S2, S3> e2{hamon::unexpect};
		e1.swap(e2);
		EXPECT_EQ(0, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(0, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(0, S2::dtor_count);
		EXPECT_EQ(0, S2::swap_count);
		EXPECT_EQ(2, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
		EXPECT_EQ(1, S3::swap_count);
	}
	EXPECT_EQ(0, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(0, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(0, S2::dtor_count);
	EXPECT_EQ(0, S2::swap_count);
	EXPECT_EQ(2, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);
	EXPECT_EQ(1, S3::swap_count);

	S2::reset();
	S3::reset();
	{
		hamon::expected<S3, S2> e1{hamon::in_place};
		hamon::expected<S3, S2> e2{hamon::unexpect};
		e1.swap(e2);
		EXPECT_EQ(1, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(1, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(1, S2::dtor_count);
		EXPECT_EQ(0, S2::swap_count);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(2, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(2, S3::dtor_count);
		EXPECT_EQ(0, S3::swap_count);
	}
	EXPECT_EQ(1, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(1, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(2, S2::dtor_count);
	EXPECT_EQ(0, S2::swap_count);
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(2, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(3, S3::dtor_count);
	EXPECT_EQ(0, S3::swap_count);

	S2::reset();
	S3::reset();
	{
		hamon::expected<S3, S2> e1{hamon::unexpect};
		hamon::expected<S3, S2> e2{hamon::in_place};
		e1.swap(e2);
		EXPECT_EQ(1, S2::default_ctor_count);
		EXPECT_EQ(0, S2::copy_ctor_count);
		EXPECT_EQ(1, S2::move_ctor_count);
		EXPECT_EQ(0, S2::copy_assign_count);
		EXPECT_EQ(0, S2::move_assign_count);
		EXPECT_EQ(1, S2::dtor_count);
		EXPECT_EQ(0, S2::swap_count);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(2, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(2, S3::dtor_count);
		EXPECT_EQ(0, S3::swap_count);
	}
	EXPECT_EQ(1, S2::default_ctor_count);
	EXPECT_EQ(0, S2::copy_ctor_count);
	EXPECT_EQ(1, S2::move_ctor_count);
	EXPECT_EQ(0, S2::copy_assign_count);
	EXPECT_EQ(0, S2::move_assign_count);
	EXPECT_EQ(2, S2::dtor_count);
	EXPECT_EQ(0, S2::swap_count);
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(2, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(3, S3::dtor_count);
	EXPECT_EQ(0, S3::swap_count);
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
		hamon::expected<ThrowOnMoveCtor, int> e1(hamon::in_place, 10);
		hamon::expected<ThrowOnMoveCtor, int> e2(hamon::in_place, 20);
		EXPECT_THROW(e1.swap(e2), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(e1.has_value());
		EXPECT_TRUE(e1.value().value == 10);
		EXPECT_TRUE(e2.has_value());
		EXPECT_TRUE(e2.value().value == 20);
	}
	{
		hamon::expected<ThrowOnMoveCtor, int> e1(hamon::in_place, 10);
		hamon::expected<ThrowOnMoveCtor, int> e2(hamon::unexpect, 20);
		EXPECT_THROW(e1.swap(e2), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(e1.has_value());
		EXPECT_TRUE(e1.value().value == 10);
		EXPECT_TRUE(!e2.has_value());
		EXPECT_TRUE(e2.error() == 20);
	}
	{
		hamon::expected<ThrowOnMoveCtor, int> e1(hamon::unexpect, 10);
		hamon::expected<ThrowOnMoveCtor, int> e2(hamon::in_place, 20);
		EXPECT_THROW(e1.swap(e2), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(!e1.has_value());
		EXPECT_TRUE(e1.error() == 10);
		EXPECT_TRUE(e2.has_value());
		EXPECT_TRUE(e2.value().value == 20);
	}
	{
		hamon::expected<ThrowOnMoveCtor, int> e1(hamon::unexpect, 10);
		hamon::expected<ThrowOnMoveCtor, int> e2(hamon::unexpect, 20);
		EXPECT_NO_THROW(e1.swap(e2));
		EXPECT_TRUE(!e1.has_value());
		EXPECT_TRUE(e1.error() == 20);
		EXPECT_TRUE(!e2.has_value());
		EXPECT_TRUE(e2.error() == 10);
	}

	{
		hamon::expected<int, ThrowOnMoveCtor> e1(hamon::in_place, 10);
		hamon::expected<int, ThrowOnMoveCtor> e2(hamon::in_place, 20);
		EXPECT_NO_THROW(e1.swap(e2));
		EXPECT_TRUE(e1.has_value());
		EXPECT_TRUE(e1.value() == 20);
		EXPECT_TRUE(e2.has_value());
		EXPECT_TRUE(e2.value() == 10);
	}
	{
		hamon::expected<int, ThrowOnMoveCtor> e1(hamon::in_place, 10);
		hamon::expected<int, ThrowOnMoveCtor> e2(hamon::unexpect, 20);
		EXPECT_THROW(e1.swap(e2), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(e1.has_value());
		EXPECT_TRUE(e1.value() == 10);
		EXPECT_TRUE(!e2.has_value());
		EXPECT_TRUE(e2.error().value == 20);
	}
	{
		hamon::expected<int, ThrowOnMoveCtor> e1(hamon::unexpect, 10);
		hamon::expected<int, ThrowOnMoveCtor> e2(hamon::in_place, 20);
		EXPECT_THROW(e1.swap(e2), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(!e1.has_value());
		EXPECT_TRUE(e1.error().value == 10);
		EXPECT_TRUE(e2.has_value());
		EXPECT_TRUE(e2.value() == 20);
	}
	{
		hamon::expected<int, ThrowOnMoveCtor> e1(hamon::unexpect, 10);
		hamon::expected<int, ThrowOnMoveCtor> e2(hamon::unexpect, 20);
		EXPECT_THROW(e1.swap(e2), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(!e1.has_value());
		EXPECT_TRUE(e1.error().value == 10);
		EXPECT_TRUE(!e2.has_value());
		EXPECT_TRUE(e2.error().value == 20);
	}
#endif
}

GTEST_TEST(ExpectedTest, SwapMemberTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));

	trase_test();

	exceptions_test();
}

}	// namespace swap_member_test

}	// namespace hamon_expected_test
