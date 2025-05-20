/**
 *	@file	unit_test_expected_void_op_assign_unexpected_move.cpp
 *
 *	@brief	unexpected&& からの代入演算子のテスト
 *
 *	template<class G>
 *	constexpr expected& operator=(unexpected<G>&& e);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace op_assign_unexpected_move_test
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

struct MoveMayThrow
{
	MoveMayThrow(MoveMayThrow const&)            = default;
	MoveMayThrow& operator=(const MoveMayThrow&) = default;
	MoveMayThrow(MoveMayThrow&&) noexcept(false) {}
	MoveMayThrow& operator=(MoveMayThrow&&) noexcept(false) { return *this; }
};

// Test constraints
static_assert(hamon::is_assignable<hamon::expected<int, int>&, hamon::unexpected<int>&&>::value, "");

// !is_constructible_v<E, GF>
static_assert(!hamon::is_assignable<hamon::expected<int, NotMoveConstructible>&, hamon::unexpected<NotMoveConstructible>&&>::value, "");

// !is_assignable_v<E&, GF>
static_assert(!hamon::is_assignable<hamon::expected<int, NotMoveAssignable>&, hamon::unexpected<NotMoveAssignable>&&>::value, "");

template <bool moveNoexcept, bool convertNoexcept>
struct MaybeNoexcept
{
	explicit MaybeNoexcept(int) noexcept(convertNoexcept);
	MaybeNoexcept(MaybeNoexcept&&) noexcept(moveNoexcept);
	MaybeNoexcept& operator=(MaybeNoexcept&&) = default;
	MaybeNoexcept& operator=(int);
};

// !is_nothrow_constructible_v<E, GF> && !is_nothrow_move_constructible_v<T> &&
// is_nothrow_move_constructible_v<E>
static_assert(hamon::is_assignable<hamon::expected<MaybeNoexcept<false, false>, MaybeNoexcept<true, false>>&, hamon::unexpected<int>&&>::value, "");

// is_nothrow_constructible_v<E, GF> && !is_nothrow_move_constructible_v<T> &&
// !is_nothrow_move_constructible_v<E>
static_assert(hamon::is_assignable<hamon::expected<MaybeNoexcept<false, false>, MaybeNoexcept<false, true>>&, hamon::unexpected<int>&&>::value, "");

// !is_nothrow_constructible_v<E, GF> && is_nothrow_move_constructible_v<T> &&
// !is_nothrow_move_constructible_v<E>
static_assert(hamon::is_assignable<hamon::expected<MaybeNoexcept<true, true>, MaybeNoexcept<false, false>>&, hamon::unexpected<int>&&>::value, "");

// !is_nothrow_constructible_v<E, GF> && !is_nothrow_move_constructible_v<T> &&
// !is_nothrow_move_constructible_v<E>
static_assert(!hamon::is_assignable<hamon::expected<MaybeNoexcept<false, false>, MaybeNoexcept<false, false>>&, hamon::unexpected<int>&&>::value, "");

// test noexcept

#if !defined(HAMON_USE_STD_EXPECTED)
template <bool CtorNoexcept, bool AssignNoexcept>
struct MaybeNoexcept2
{
	MaybeNoexcept2(int) noexcept(CtorNoexcept);
	MaybeNoexcept2& operator=(int) noexcept(AssignNoexcept);
};

static_assert( hamon::is_nothrow_assignable<hamon::expected<void, int>&, hamon::unexpected<int>&&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<void, MaybeNoexcept2<true, true>>&, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<void, MaybeNoexcept2<true, false>>&, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<void, MaybeNoexcept2<false, true>>&, hamon::unexpected<int>&&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<void, MaybeNoexcept2<false, false>>&, hamon::unexpected<int>&&>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::unexpected<E> src{E{3}};
		hamon::expected<Void, E> dst{hamon::in_place};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{3});
	}
	{
		hamon::unexpected<E> src{E{5}};
		hamon::expected<Void, E> dst{hamon::unexpect, E{6}};
		auto& r = (dst = hamon::move(src));
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{5});
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
		hamon::unexpected<S3> src{S3{}};
		hamon::expected<void, S3> dst{hamon::in_place};
		dst = hamon::move(src);
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(2, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(1, S3::dtor_count);
	}
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(2, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(3, S3::dtor_count);

	S3::reset();
	{
		hamon::unexpected<S3> src{S3{}};
		hamon::expected<void, S3> dst{hamon::unexpect};
		dst = hamon::move(src);
		EXPECT_EQ(2, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(1, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(1, S3::move_assign_count);
		EXPECT_EQ(1, S3::dtor_count);
	}
	EXPECT_EQ(2, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(1, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(1, S3::move_assign_count);
	EXPECT_EQ(3, S3::dtor_count);
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

	{
		hamon::expected<void, ThrowOnCtor> dst(hamon::in_place);
		hamon::unexpected<int> src{10};
		EXPECT_THROW(dst = hamon::move(src), ThrowOnCtor::Exception);
		EXPECT_TRUE(dst.has_value());
	}
#endif
}

GTEST_TEST(ExpectedVoidTest, OpAssignUnexpectedMoveTest)
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

}	// namespace op_assign_unexpected_move_test

}	// namespace hamon_expected_void_test
