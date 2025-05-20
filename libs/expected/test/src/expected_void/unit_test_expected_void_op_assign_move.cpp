/**
 *	@file	unit_test_expected_void_op_assign_move.cpp
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
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
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

// Test constraints
static_assert(hamon::is_move_assignable<hamon::expected<void, int>>::value, "");

// !is_move_assignable_v<E>
static_assert(!hamon::is_move_assignable<hamon::expected<void, NotMoveAssignable>>::value, "");

// !is_move_constructible_v<E>
static_assert(!hamon::is_move_assignable<hamon::expected<void, NotMoveConstructible>>::value, "");

// Test noexcept
struct MoveCtorMayThrow
{
	MoveCtorMayThrow(MoveCtorMayThrow&&) noexcept(false) {}
	MoveCtorMayThrow& operator=(MoveCtorMayThrow&&) noexcept = default;
};

struct MoveAssignMayThrow
{
	MoveAssignMayThrow(MoveAssignMayThrow&&) noexcept = default;
	MoveAssignMayThrow& operator=(MoveAssignMayThrow&&) noexcept(false) { return *this; }
};

// Test noexcept
static_assert(hamon::is_nothrow_move_assignable<hamon::expected<void, int>>::value, "");

// !is_nothrow_move_assignable_v<E>
static_assert(!hamon::is_nothrow_move_assignable<hamon::expected<void, MoveAssignMayThrow>>::value, "");

// !is_nothrow_move_constructible_v<E>
static_assert(!hamon::is_nothrow_move_assignable<hamon::expected<void, MoveCtorMayThrow>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, E> src{hamon::in_place};
		hamon::expected<Void, E> dst{hamon::in_place};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
	}
	{
		hamon::expected<Void, E> src{hamon::unexpect, E{5}};
		hamon::expected<Void, E> dst{hamon::in_place};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{5});
	}
	{
		hamon::expected<Void, E> src{hamon::in_place};
		hamon::expected<Void, E> dst{hamon::unexpect, E{8}};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
	}
	{
		hamon::expected<Void, E> src{hamon::unexpect, E{9}};
		hamon::expected<Void, E> dst{hamon::unexpect, E{10}};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{9});
	}

	return true;
}

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

void trase_test()
{
	S3::reset();
	{
		hamon::expected<void, S3> src{hamon::in_place};
		hamon::expected<void, S3> dst{hamon::in_place};
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
		hamon::expected<void, S3> src{hamon::unexpect};
		hamon::expected<void, S3> dst{hamon::in_place};
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
		hamon::expected<void, S3> src{hamon::in_place};
		hamon::expected<void, S3> dst{hamon::unexpect};
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
		hamon::expected<void, S3> src{hamon::unexpect};
		hamon::expected<void, S3> dst{hamon::unexpect};
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
		hamon::expected<void, ThrowOnMoveCtor> src(hamon::in_place);
		hamon::expected<void, ThrowOnMoveCtor> dst(hamon::in_place);
		EXPECT_NO_THROW(dst = hamon::move(src));
		EXPECT_TRUE(dst.has_value());
	}
	{
		hamon::expected<void, ThrowOnMoveCtor> src(hamon::in_place);
		hamon::expected<void, ThrowOnMoveCtor> dst(hamon::unexpect);
		EXPECT_NO_THROW(dst = hamon::move(src));
		EXPECT_TRUE(dst.has_value());
	}
	{
		hamon::expected<void, ThrowOnMoveCtor> src(hamon::unexpect);
		hamon::expected<void, ThrowOnMoveCtor> dst(hamon::in_place);
		EXPECT_THROW(dst = hamon::move(src), ThrowOnMoveCtor::Exception);
		EXPECT_TRUE(dst.has_value());
	}
	{
		hamon::expected<void, ThrowOnMoveCtor> src(hamon::unexpect);
		hamon::expected<void, ThrowOnMoveCtor> dst(hamon::unexpect);
		EXPECT_NO_THROW(dst = hamon::move(src));
		EXPECT_TRUE(!dst.has_value());
	}
#endif
}

GTEST_TEST(ExpectedVoidTest, OpAssignMoveTest)
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

}	// namespace op_assign_move_test

}	// namespace hamon_expected_void_test
