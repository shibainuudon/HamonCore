/**
 *	@file	unit_test_optional_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	constexpr optional& operator=(optional&& rhs) noexcept(see below);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace assign_move_test
{

struct NonMovable
{
	NonMovable(NonMovable &&) = delete;
	NonMovable& operator=(NonMovable &&) = delete;
};
static_assert(!hamon::is_move_assignable<NonMovable>::value, "");
static_assert(!hamon::is_move_constructible<NonMovable>::value, "");

struct NonMoveAssignable
{
	NonMoveAssignable(NonMoveAssignable &&);
	NonMoveAssignable& operator=(NonMoveAssignable &&) = delete;
};
static_assert(!hamon::is_move_assignable<NonMoveAssignable>::value, "");
static_assert( hamon::is_move_constructible<NonMoveAssignable>::value, "");

struct NonMoveConstructible
{
	NonMoveConstructible(NonMoveConstructible &&) = delete;
	NonMoveConstructible& operator=(NonMoveConstructible &&);
};
static_assert( hamon::is_move_assignable<NonMoveConstructible>::value, "");
static_assert(!hamon::is_move_constructible<NonMoveConstructible>::value, "");

struct Movable
{
	Movable(Movable &&);
	Movable& operator=(Movable &&);
};
static_assert( hamon::is_move_assignable<Movable>::value, "");
static_assert( hamon::is_move_constructible<Movable>::value, "");

struct Trivial
{
};
static_assert( hamon::is_trivially_move_constructible<Trivial>::value, "");
static_assert( hamon::is_trivially_move_assignable<Trivial>::value, "");
static_assert( hamon::is_trivially_destructible<Trivial>::value, "");

struct NonTrivialMoveCtor
{
	NonTrivialMoveCtor(NonTrivialMoveCtor &&);
	NonTrivialMoveCtor& operator=(NonTrivialMoveCtor &&) = default;
};
static_assert(!hamon::is_trivially_move_constructible<NonTrivialMoveCtor>::value, "");
static_assert( hamon::is_trivially_move_assignable<NonTrivialMoveCtor>::value, "");
static_assert( hamon::is_trivially_destructible<NonTrivialMoveCtor>::value, "");

struct NonTrivialMoveAssign
{
	NonTrivialMoveAssign(NonTrivialMoveAssign &&) = default;
	NonTrivialMoveAssign& operator=(NonTrivialMoveAssign &&);
};
static_assert( hamon::is_trivially_move_constructible<NonTrivialMoveAssign>::value, "");
static_assert(!hamon::is_trivially_move_assignable<NonTrivialMoveAssign>::value, "");
static_assert( hamon::is_trivially_destructible<NonTrivialMoveAssign>::value, "");

struct NonTrivialDtor
{
	~NonTrivialDtor();
};
static_assert(!hamon::is_trivially_move_constructible<NonTrivialDtor>::value, "");
static_assert( hamon::is_trivially_move_assignable<NonTrivialDtor>::value, "");
static_assert(!hamon::is_trivially_destructible<NonTrivialDtor>::value, "");

struct Nothrow
{
	Nothrow(Nothrow &&) noexcept;
	Nothrow& operator=(Nothrow &&) noexcept;
};
static_assert( hamon::is_nothrow_move_constructible<Nothrow>::value, "");
static_assert( hamon::is_nothrow_move_assignable<Nothrow>::value, "");

struct MayThrowMoveCtor
{
	MayThrowMoveCtor(MayThrowMoveCtor &&) noexcept(false);
	MayThrowMoveCtor& operator=(MayThrowMoveCtor &&) noexcept;
};
static_assert(!hamon::is_nothrow_move_constructible<MayThrowMoveCtor>::value, "");
static_assert( hamon::is_nothrow_move_assignable<MayThrowMoveCtor>::value, "");

struct MayThrowMoveAssign
{
	MayThrowMoveAssign(MayThrowMoveAssign &&) noexcept;
	MayThrowMoveAssign& operator=(MayThrowMoveAssign &&) noexcept(false);
};
static_assert( hamon::is_nothrow_move_constructible<MayThrowMoveAssign>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<MayThrowMoveAssign>::value, "");

struct MayThrow
{
	MayThrow(MayThrow &&) noexcept(false);
	MayThrow& operator=(MayThrow &&) noexcept(false);
};
static_assert(!hamon::is_nothrow_move_constructible<MayThrow>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<MayThrow>::value, "");

// [optional.assign]/8
// Constraints: is_move_constructible_v<T> is true and is_move_assignable_v<T> is true.
static_assert( hamon::is_move_assignable<hamon::optional<int>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::optional<NonMovable>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::optional<NonMoveAssignable>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::optional<NonMoveConstructible>>::value, "");
static_assert( hamon::is_move_assignable<hamon::optional<Movable>>::value, "");

// [optional.assign]/13
// If is_trivially_move_constructible_v<T> && is_trivially_move_assignable_v<T> &&
// is_trivially_destructible_v<T> is true, this assignment operator is trivial.
static_assert( hamon::is_trivially_move_assignable<hamon::optional<int>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::optional<Trivial>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::optional<NonTrivialMoveCtor>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::optional<NonTrivialMoveAssign>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::optional<NonTrivialDtor>>::value, "");

// [optional.assign]/12
static_assert( hamon::is_nothrow_move_assignable<hamon::optional<int>>::value, "");
static_assert( hamon::is_nothrow_move_assignable<hamon::optional<Nothrow>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::optional<MayThrowMoveCtor>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::optional<MayThrowMoveAssign>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::optional<MayThrow>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	// *this contains a value, rhs contains a value
	{
		hamon::optional<int> o1 {42};
		hamon::optional<int> o2 {13};
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		auto& r = (o1 = hamon::move(o2));
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		VERIFY(o1.value() == 13);
		VERIFY(*o1 == 13);
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<int> o1 {42};
		hamon::optional<int> o2;
		VERIFY(o1.has_value());
		VERIFY(!o2.has_value());
		auto& r = (o1 = hamon::move(o2));
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<int> o1;
		hamon::optional<int> o2 {13};
		VERIFY(!o1.has_value());
		VERIFY(o2.has_value());
		auto& r = (o1 = hamon::move(o2));
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		VERIFY(o1.value() == 13);
		VERIFY(*o1 == 13);
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<int> o1;
		hamon::optional<int> o2;
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
		auto& r = (o1 = hamon::move(o2));
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	return true;
}

#undef VERIFY

static int s_move_assign_count = 0;
static int s_move_ctor_count = 0;
static int s_dtor_count = 0;

struct S
{
	S(int)
	{
	}

	S(S &&)
	{
		++s_move_ctor_count;
	}

	S& operator=(S &&)
	{
		++s_move_assign_count;
		return *this;
	}

	~S()
	{
		++s_dtor_count;
	}
};

void InvokeCountTest()
{
	s_move_assign_count = 0;
	s_move_ctor_count = 0;
	s_dtor_count = 0;

	// *this contains a value, rhs contains a value
	{
		hamon::optional<S> o1 {42};
		hamon::optional<S> o2 {13};
		o1 = hamon::move(o2);
		EXPECT_EQ(1, s_move_assign_count);
		EXPECT_EQ(0, s_move_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
	}

	s_move_assign_count = 0;
	s_move_ctor_count = 0;
	s_dtor_count = 0;

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<S> o1 {42};
		hamon::optional<S> o2;
		o1 = hamon::move(o2);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(0, s_move_ctor_count);
		EXPECT_EQ(1, s_dtor_count);
	}

	s_move_assign_count = 0;
	s_move_ctor_count = 0;
	s_dtor_count = 0;

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<S> o1;
		hamon::optional<S> o2 {13};
		o1 = hamon::move(o2);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(1, s_move_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
	}

	s_move_assign_count = 0;
	s_move_ctor_count = 0;
	s_dtor_count = 0;

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<S> o1;
		hamon::optional<S> o2;
		o1 = hamon::move(o2);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(0, s_move_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
	}
}

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnMove1
{
	int value = -1;

	ThrowOnMove1(int v) : value(v) {}

	ThrowOnMove1(ThrowOnMove1 && rhs)
		: value(rhs.value)
	{
		throw 42;
	}

	ThrowOnMove1& operator=(ThrowOnMove1 && rhs)
	{
		value = rhs.value;
		throw 42;
	}
};

struct ThrowOnMove2
{
	int value = -1;

	ThrowOnMove2(int v) : value(v) {}

	ThrowOnMove2(ThrowOnMove2 &&)
	{
		throw 42;
	}

	ThrowOnMove2& operator=(ThrowOnMove2 &&)
	{
		throw 42;
	}
};

void ThrowOnMoveTest()
{
	// *this contains a value, rhs contains a value
	{
		hamon::optional<ThrowOnMove1> o1 {42};
		hamon::optional<ThrowOnMove1> o2 {13};
		EXPECT_ANY_THROW(o1 = hamon::move(o2));
		EXPECT_TRUE( o1.has_value());
		EXPECT_TRUE( o2.has_value());
		EXPECT_EQ(13, o1.value().value);
		EXPECT_EQ(13, o2.value().value);
		EXPECT_EQ(13, o1->value);
		EXPECT_EQ(13, o2->value);
	}
	{
		hamon::optional<ThrowOnMove2> o1 {42};
		hamon::optional<ThrowOnMove2> o2 {13};
		EXPECT_ANY_THROW(o1 = hamon::move(o2));
		EXPECT_TRUE( o1.has_value());
		EXPECT_TRUE( o2.has_value());
		EXPECT_EQ(42, o1.value().value);
		EXPECT_EQ(13, o2.value().value);
		EXPECT_EQ(42, o1->value);
		EXPECT_EQ(13, o2->value);
	}

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnMove1> o1 {42};
		hamon::optional<ThrowOnMove1> o2;
		EXPECT_NO_THROW(o1 = hamon::move(o2));
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE(!o2.has_value());
	}
	{
		hamon::optional<ThrowOnMove2> o1 {42};
		hamon::optional<ThrowOnMove2> o2;
		EXPECT_NO_THROW(o1 = hamon::move(o2));
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE(!o2.has_value());
	}

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<ThrowOnMove1> o1;
		hamon::optional<ThrowOnMove1> o2 {13};
		EXPECT_ANY_THROW(o1 = hamon::move(o2));
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE( o2.has_value());
		EXPECT_EQ(13, o2.value().value);
		EXPECT_EQ(13, o2->value);
	}
	{
		hamon::optional<ThrowOnMove2> o1;
		hamon::optional<ThrowOnMove2> o2 {13};
		EXPECT_ANY_THROW(o1 = hamon::move(o2));
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE( o2.has_value());
		EXPECT_EQ(13, o2.value().value);
		EXPECT_EQ(13, o2->value);
	}

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnMove1> o1;
		hamon::optional<ThrowOnMove1> o2;
		EXPECT_NO_THROW(o1 = hamon::move(o2));
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE(!o2.has_value());
	}
	{
		hamon::optional<ThrowOnMove2> o1;
		hamon::optional<ThrowOnMove2> o2;
		EXPECT_NO_THROW(o1 = hamon::move(o2));
		EXPECT_TRUE(!o1.has_value());
		EXPECT_TRUE(!o2.has_value());
	}
}
#endif

GTEST_TEST(OptionalTest, AssignMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
	InvokeCountTest();
#if !defined(HAMON_NO_EXCEPTIONS)
	ThrowOnMoveTest();
#endif
}

}	// namespace assign_move_test

}	// namespace hamon_optional_test
