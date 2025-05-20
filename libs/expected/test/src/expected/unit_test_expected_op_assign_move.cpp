/**
 *	@file	unit_test_expected_op_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	constexpr expected& operator=(expected&& rhs) noexcept(see below);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace op_assign_move_test
{

struct NotMoveConstructible
{
	NotMoveConstructible(NotMoveConstructible&&)            = delete;
	NotMoveConstructible& operator=(NotMoveConstructible&&) = default;
};

struct NotMoveAssignable
{
	NotMoveAssignable(NotMoveAssignable&&)            = default;
	NotMoveAssignable& operator=(NotMoveAssignable&&) = delete;
};

struct MoveCtorMayThrow
{
	MoveCtorMayThrow(MoveCtorMayThrow&&) noexcept(false) {}
	MoveCtorMayThrow& operator=(MoveCtorMayThrow&&) noexcept = default;
};

// Test constraints
static_assert(hamon::is_move_assignable<hamon::expected<int, int>>::value, "");

// !is_move_assignable_v<T>
static_assert(!hamon::is_move_assignable<hamon::expected<NotMoveAssignable, int>>::value, "");

// !is_move_constructible_v<T>
static_assert(!hamon::is_move_assignable<hamon::expected<NotMoveConstructible, int>>::value, "");

// !is_move_assignable_v<E>
static_assert(!hamon::is_move_assignable<hamon::expected<int, NotMoveAssignable>>::value, "");

// !is_move_constructible_v<E>
static_assert(!hamon::is_move_assignable<hamon::expected<int, NotMoveConstructible>>::value, "");

// !is_nothrow_move_constructible_v<T> && is_nothrow_move_constructible_v<E>
static_assert(hamon::is_move_assignable<hamon::expected<MoveCtorMayThrow, int>>::value, "");

// is_nothrow_move_constructible_v<T> && !is_nothrow_move_constructible_v<E>
static_assert(hamon::is_move_assignable<hamon::expected<int, MoveCtorMayThrow>>::value, "");

// !is_nothrow_move_constructible_v<T> && !is_nothrow_move_constructible_v<E>
static_assert(!hamon::is_move_assignable<hamon::expected<MoveCtorMayThrow, MoveCtorMayThrow>>::value, "");

struct MoveAssignMayThrow
{
	MoveAssignMayThrow(MoveAssignMayThrow&&) noexcept = default;
	MoveAssignMayThrow& operator=(MoveAssignMayThrow&&) noexcept(false) { return *this; }
};

// Test noexcept
static_assert(hamon::is_nothrow_move_assignable<hamon::expected<int, int>>::value, "");

// !is_nothrow_move_assignable_v<T>
static_assert(!hamon::is_nothrow_move_assignable<hamon::expected<MoveAssignMayThrow, int>>::value, "");

// !is_nothrow_move_constructible_v<T>
static_assert(!hamon::is_nothrow_move_assignable<hamon::expected<MoveCtorMayThrow, int>>::value, "");

// !is_nothrow_move_assignable_v<E>
static_assert(!hamon::is_nothrow_move_assignable<hamon::expected<int, MoveAssignMayThrow>>::value, "");

// !is_nothrow_move_constructible_v<E>
static_assert(!hamon::is_nothrow_move_assignable<hamon::expected<int, MoveCtorMayThrow>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> src{hamon::in_place, T{3}};
		hamon::expected<T, E> dst{hamon::in_place, T{4}};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{3});
	}
	{
		hamon::expected<T, E> src{hamon::unexpect, E{5}};
		hamon::expected<T, E> dst{hamon::in_place, T{6}};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{5});
	}
	{
		hamon::expected<T, E> src{hamon::in_place, T{7}};
		hamon::expected<T, E> dst{hamon::unexpect, E{8}};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{7});
	}
	{
		hamon::expected<T, E> src{hamon::unexpect, E{9}};
		hamon::expected<T, E> dst{hamon::unexpect, E{10}};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{9});
	}

	return true;
}

struct S1
{
	int value;

	HAMON_CXX14_CONSTEXPR S1(int v) : value(v) {}
	HAMON_CXX14_CONSTEXPR S1(S1 const& rhs) : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR S1(S1&& rhs) : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR S1& operator=(S1 const& rhs) { value = rhs.value; return *this; }
	HAMON_CXX14_CONSTEXPR S1& operator=(S1&& rhs) { value = rhs.value; return *this; }
	HAMON_CXX14_CONSTEXPR bool operator==(S1 const& rhs) const { return value == rhs.value; }
};

struct S2
{
	int value;

	HAMON_CXX14_CONSTEXPR S2(int v) : value(v) {}
	HAMON_CXX14_CONSTEXPR S2(S2 const& rhs) : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR S2(S2&& rhs) noexcept : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR S2& operator=(S2 const& rhs) { value = rhs.value; return *this; }
	HAMON_CXX14_CONSTEXPR S2& operator=(S2&& rhs) { value = rhs.value; return *this; }
	HAMON_CXX14_CONSTEXPR bool operator==(S2 const& rhs) const { return value == rhs.value; }
};

struct S3
{
	static int default_ctor_count;
	static int copy_ctor_count;
	static int move_ctor_count;
	static int copy_assign_count;
	static int move_assign_count;
	static int dtor_count;

	S3()
	{
		++default_ctor_count;
	}

	S3(S3 const&)
	{
		++copy_ctor_count;
	}

	S3(S3&&)
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

	static void reset()
	{
		default_ctor_count = 0;
		copy_ctor_count = 0;
		move_ctor_count = 0;
		copy_assign_count = 0;
		move_assign_count = 0;
		dtor_count = 0;
	}
};
int S3::default_ctor_count = 0;
int S3::copy_ctor_count = 0;
int S3::move_ctor_count = 0;
int S3::copy_assign_count = 0;
int S3::move_assign_count = 0;
int S3::dtor_count = 0;

void trase_test_1()
{
	S3::reset();
	{
		hamon::expected<S3, int> src{hamon::in_place};
		hamon::expected<S3, int> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(2, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(1, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(2, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(1, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);

	S3::reset();
	{
		hamon::expected<S3, int> src{hamon::unexpect};
		hamon::expected<S3, int> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(1, S3::dtor_count);
	}
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(1, S3::dtor_count);

	S3::reset();
	{
		hamon::expected<S3, int> src{hamon::in_place};
		hamon::expected<S3, int> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(1, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(1, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);

	S3::reset();
	{
		hamon::expected<S3, int> src{hamon::unexpect};
		hamon::expected<S3, int> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(0, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(0, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(0, S3::dtor_count);

	S3::reset();
	{
		hamon::expected<int, S3> src{hamon::in_place};
		hamon::expected<int, S3> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(0, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(0, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(0, S3::dtor_count);

	S3::reset();
	{
		hamon::expected<int, S3> src{hamon::unexpect};
		hamon::expected<int, S3> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(1, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(1, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);

	S3::reset();
	{
		hamon::expected<int, S3> src{hamon::in_place};
		hamon::expected<int, S3> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(1, S3::dtor_count);
	}
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(1, S3::dtor_count);

	S3::reset();
	{
		hamon::expected<int, S3> src{hamon::unexpect};
		hamon::expected<int, S3> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(2, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(1, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(2, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(1, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);
}

struct S4
{
	static int default_ctor_count;
	static int copy_ctor_count;
	static int move_ctor_count;
	static int copy_assign_count;
	static int move_assign_count;
	static int dtor_count;

	S4()
	{
		++default_ctor_count;
	}

	S4(S4 const&)
	{
		++copy_ctor_count;
	}

	S4(S4&&) noexcept
	{
		++move_ctor_count;
	}

	S4& operator=(S4 const&)
	{
		++copy_assign_count;
		return *this;
	}

	S4& operator=(S4&&)
	{
		++move_assign_count;
		return *this;
	}

	~S4()
	{
		++dtor_count;
	}

	static void reset()
	{
		default_ctor_count = 0;
		copy_ctor_count = 0;
		move_ctor_count = 0;
		copy_assign_count = 0;
		move_assign_count = 0;
		dtor_count = 0;
	}
};
int S4::default_ctor_count = 0;
int S4::copy_ctor_count = 0;
int S4::move_ctor_count = 0;
int S4::copy_assign_count = 0;
int S4::move_assign_count = 0;
int S4::dtor_count = 0;

void trase_test_2()
{
	S4::reset();
	{
		hamon::expected<S4, int> src{hamon::in_place};
		hamon::expected<S4, int> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(2, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(0, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(1, S4::move_assign_count);
		EXPECT_EQ(0, S4::dtor_count);
	}
	EXPECT_EQ(2, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(0, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(1, S4::move_assign_count);
	EXPECT_EQ(2, S4::dtor_count);

	S4::reset();
	{
		hamon::expected<S4, int> src{hamon::unexpect};
		hamon::expected<S4, int> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(1, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(0, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(1, S4::dtor_count);
	}
	EXPECT_EQ(1, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(0, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(1, S4::dtor_count);

	S4::reset();
	{
		hamon::expected<S4, int> src{hamon::in_place};
		hamon::expected<S4, int> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(1, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(1, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(0, S4::dtor_count);
	}
	EXPECT_EQ(1, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(1, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(2, S4::dtor_count);

	S4::reset();
	{
		hamon::expected<S4, int> src{hamon::unexpect};
		hamon::expected<S4, int> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(0, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(0, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(0, S4::dtor_count);
	}
	EXPECT_EQ(0, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(0, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(0, S4::dtor_count);

	S4::reset();
	{
		hamon::expected<int, S4> src{hamon::in_place};
		hamon::expected<int, S4> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(0, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(0, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(0, S4::dtor_count);
	}
	EXPECT_EQ(0, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(0, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(0, S4::dtor_count);

	S4::reset();
	{
		hamon::expected<int, S4> src{hamon::unexpect};
		hamon::expected<int, S4> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(1, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(1, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(0, S4::dtor_count);
	}
	EXPECT_EQ(1, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(1, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(2, S4::dtor_count);

	S4::reset();
	{
		hamon::expected<int, S4> src{hamon::in_place};
		hamon::expected<int, S4> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(1, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(0, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(1, S4::dtor_count);
	}
	EXPECT_EQ(1, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(0, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(1, S4::dtor_count);

	S4::reset();
	{
		hamon::expected<int, S4> src{hamon::unexpect};
		hamon::expected<int, S4> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(2, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(0, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(1, S4::move_assign_count);
		EXPECT_EQ(0, S4::dtor_count);
	}
	EXPECT_EQ(2, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(0, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(1, S4::move_assign_count);
	EXPECT_EQ(2, S4::dtor_count);
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowOnMoveCtor
	{
		struct Exception{};
		ThrowOnMoveCtor() = default;
		ThrowOnMoveCtor(ThrowOnMoveCtor const&) {}
		ThrowOnMoveCtor(ThrowOnMoveCtor&&) { throw Exception{}; }
		ThrowOnMoveCtor& operator=(ThrowOnMoveCtor const&) = default;
	};

	{
		hamon::expected<ThrowOnMoveCtor, int> src(hamon::in_place);
		hamon::expected<ThrowOnMoveCtor, int> dst(hamon::in_place);
		EXPECT_NO_THROW(dst = hamon::move(src));
		EXPECT_TRUE(dst.has_value());
	}
	{
		hamon::expected<ThrowOnMoveCtor, int> src(hamon::in_place);
		hamon::expected<ThrowOnMoveCtor, int> dst(hamon::unexpect, 5);
		EXPECT_THROW(dst = hamon::move(src), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(!dst.has_value());
		EXPECT_TRUE(dst.error() == 5);
	}
	{
		hamon::expected<ThrowOnMoveCtor, int> src(hamon::unexpect, 6);
		hamon::expected<ThrowOnMoveCtor, int> dst(hamon::in_place);
		EXPECT_NO_THROW(dst = hamon::move(src));
		EXPECT_TRUE(!dst.has_value());
		EXPECT_TRUE(dst.error() == 6);
	}
	{
		hamon::expected<ThrowOnMoveCtor, int> src(hamon::unexpect, 7);
		hamon::expected<ThrowOnMoveCtor, int> dst(hamon::unexpect, 8);
		EXPECT_NO_THROW(dst = hamon::move(src));
		EXPECT_TRUE(!dst.has_value());
		EXPECT_TRUE(dst.error() == 7);
	}
	{
		hamon::expected<int, ThrowOnMoveCtor> src(hamon::in_place, 10);
		hamon::expected<int, ThrowOnMoveCtor> dst(hamon::in_place, 11);
		EXPECT_NO_THROW(dst = hamon::move(src));
		EXPECT_TRUE(dst.has_value());
		EXPECT_TRUE(dst.value() == 10);
	}
	{
		hamon::expected<int, ThrowOnMoveCtor> src(hamon::in_place, 12);
		hamon::expected<int, ThrowOnMoveCtor> dst(hamon::unexpect);
		EXPECT_NO_THROW(dst = hamon::move(src));
		EXPECT_TRUE(dst.has_value());
		EXPECT_TRUE(dst.value() == 12);
	}
	{
		hamon::expected<int, ThrowOnMoveCtor> src(hamon::unexpect);
		hamon::expected<int, ThrowOnMoveCtor> dst(hamon::in_place, 13);
		EXPECT_THROW(dst = hamon::move(src), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(dst.has_value());
		EXPECT_TRUE(dst.value() == 13);
	}
	{
		hamon::expected<int, ThrowOnMoveCtor> src(hamon::unexpect);
		hamon::expected<int, ThrowOnMoveCtor> dst(hamon::unexpect);
		EXPECT_NO_THROW(dst = hamon::move(src));
		EXPECT_TRUE(!dst.has_value());
	}
#endif
}

GTEST_TEST(ExpectedTest, OpAssignMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<S1, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<S2, int>()));

	trase_test_1();
	trase_test_2();

	exceptions_test();
}

}	// namespace op_assign_move_test

}	// namespace hamon_expected_test
