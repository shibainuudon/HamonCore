/**
 *	@file	unit_test_expected_void_op_assign_unexpected_copy.cpp
 *
 *	@brief	unexpected const& からの代入演算子のテスト
 *
 *	template<class G>
 *	constexpr expected& operator=(const unexpected<G>& e);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace op_assign_unexpected_copy_test
{

struct NotCopyConstructible
{
	NotCopyConstructible(const NotCopyConstructible&)            = delete;
	NotCopyConstructible& operator=(const NotCopyConstructible&) = default;
};

struct NotCopyAssignable
{
	NotCopyAssignable(const NotCopyAssignable&)            = default;
	NotCopyAssignable& operator=(const NotCopyAssignable&) = delete;
};

// Test constraints
static_assert(hamon::is_assignable<hamon::expected<void, int>&, const hamon::unexpected<int>&>::value, "");

// !is_constructible_v<E, GF>
static_assert(!hamon::is_assignable<hamon::expected<void, NotCopyConstructible>&, const hamon::unexpected<NotCopyConstructible>&>::value, "");

// !is_assignable_v<E&, GF>
static_assert(!hamon::is_assignable<hamon::expected<void, NotCopyAssignable>&, const hamon::unexpected<NotCopyAssignable>&>::value, "");
// test noexcept

#if !defined(HAMON_USE_STD_EXPECTED)
template <bool CtorNoexcept, bool AssignNoexcept>
struct MaybeNoexcept2
{
	MaybeNoexcept2(int) noexcept(CtorNoexcept);
	MaybeNoexcept2& operator=(int) noexcept(AssignNoexcept);
};

static_assert( hamon::is_nothrow_assignable<hamon::expected<void, int>&, const hamon::unexpected<int>&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<void, MaybeNoexcept2<true, true>>&, const hamon::unexpected<int>&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<void, MaybeNoexcept2<true, false>>&, const hamon::unexpected<int>&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<void, MaybeNoexcept2<false, true>>&, const hamon::unexpected<int>&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<void, MaybeNoexcept2<false, false>>&, const hamon::unexpected<int>&>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::unexpected<E> const src{E{3}};
		hamon::expected<Void, E> dst{hamon::in_place};
		auto& r = (dst = src);
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{3});
	}
	{
		hamon::unexpected<E> const src{E{5}};
		hamon::expected<Void, E> dst{hamon::unexpect, E{6}};
		auto& r = (dst = src);
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
		hamon::unexpected<S3> const src{S3{}};
		hamon::expected<void, S3> dst{hamon::in_place};
		dst = src;
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(1, S3::copy_ctor_count);
		EXPECT_EQ(1, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(1, S3::dtor_count);
	}
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(1, S3::copy_ctor_count);
	EXPECT_EQ(1, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(3, S3::dtor_count);

	S3::reset();
	{
		hamon::unexpected<S3> const src{S3{}};
		hamon::expected<void, S3> dst{hamon::unexpect};
		dst = src;
		EXPECT_EQ(2, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(1, S3::move_ctor_count);
		EXPECT_EQ(1, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(1, S3::dtor_count);
	}
	EXPECT_EQ(2, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(1, S3::move_ctor_count);
	EXPECT_EQ(1, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
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
		hamon::unexpected<int> const src{10};
		EXPECT_THROW(dst = src, ThrowOnCtor::Exception);
		EXPECT_TRUE(dst.has_value());
	}
#endif
}

GTEST_TEST(ExpectedVoidTest, OpAssignUnexpectedCopyTest)
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

}	// namespace op_assign_unexpected_copy_test

}	// namespace hamon_expected_void_test
