/**
 *	@file	unit_test_expected_void_op_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	constexpr expected& operator=(const expected&);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace op_assign_copy_test
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
static_assert(hamon::is_copy_assignable<hamon::expected<void, int>>::value, "");

// !is_copy_assignable_v<E>
static_assert(!hamon::is_copy_assignable<hamon::expected<void, NotCopyAssignable>>::value, "");

// !is_copy_constructible_v<E>
static_assert(!hamon::is_copy_assignable<hamon::expected<void, NotCopyConstructible>>::value, "");

struct CopyCtorMayThrow
{
	CopyCtorMayThrow(CopyCtorMayThrow const&) noexcept(false) {}
	CopyCtorMayThrow(CopyCtorMayThrow &&) noexcept = default;
	CopyCtorMayThrow& operator=(CopyCtorMayThrow const&) noexcept = default;
	CopyCtorMayThrow& operator=(CopyCtorMayThrow &&) noexcept = default;
};

struct CopyAssignMayThrow
{
	CopyAssignMayThrow(CopyAssignMayThrow const&) noexcept = default;
	CopyAssignMayThrow(CopyAssignMayThrow &&) noexcept = default;
	CopyAssignMayThrow& operator=(CopyAssignMayThrow const&) noexcept(false) { return *this; }
	CopyAssignMayThrow& operator=(CopyAssignMayThrow &&) noexcept = default;
};

// Test noexcept
#if !defined(HAMON_USE_STD_EXPECTED)
static_assert( hamon::is_nothrow_copy_assignable<hamon::expected<void, int>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::expected<void, CopyAssignMayThrow>>::value, "");
static_assert(!hamon::is_nothrow_copy_assignable<hamon::expected<void, CopyCtorMayThrow>>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, E> const src{hamon::in_place};
		hamon::expected<Void, E> dst{hamon::in_place};
		auto& r = (dst = src);
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
	}
	{
		hamon::expected<Void, E> const src{hamon::unexpect, E{5}};
		hamon::expected<Void, E> dst{hamon::in_place};
		auto& r = (dst = src);
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{5});
	}
	{
		hamon::expected<Void, E> const src{hamon::in_place};
		hamon::expected<Void, E> dst{hamon::unexpect, E{8}};
		auto& r = (dst = src);
		static_assert(hamon::is_same<decltype(r), hamon::expected<Void, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(dst.has_value());
	}
	{
		hamon::expected<Void, E> const src{hamon::unexpect, E{9}};
		hamon::expected<Void, E> dst{hamon::unexpect, E{10}};
		auto& r = (dst = src);
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
		hamon::expected<void, S3> const src{hamon::in_place};
		hamon::expected<void, S3> dst{hamon::in_place};
		dst = src;
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
		hamon::expected<void, S3> const src{hamon::unexpect};
		hamon::expected<void, S3> dst{hamon::in_place};
		dst = src;
		EXPECT_EQ(1, S3::default_ctor_count);
		EXPECT_EQ(1, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(0, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(1, S3::default_ctor_count);
	EXPECT_EQ(1, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(0, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);

	S3::reset();
	{
		hamon::expected<void, S3> const src{hamon::in_place};
		hamon::expected<void, S3> dst{hamon::unexpect};
		dst = src;
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
		hamon::expected<void, S3> const src{hamon::unexpect};
		hamon::expected<void, S3> dst{hamon::unexpect};
		dst = src;
		EXPECT_EQ(2, S3::default_ctor_count);
		EXPECT_EQ(0, S3::copy_ctor_count);
		EXPECT_EQ(0, S3::move_ctor_count);
		EXPECT_EQ(1, S3::copy_assign_count);
		EXPECT_EQ(0, S3::move_assign_count);
		EXPECT_EQ(0, S3::dtor_count);
	}
	EXPECT_EQ(2, S3::default_ctor_count);
	EXPECT_EQ(0, S3::copy_ctor_count);
	EXPECT_EQ(0, S3::move_ctor_count);
	EXPECT_EQ(1, S3::copy_assign_count);
	EXPECT_EQ(0, S3::move_assign_count);
	EXPECT_EQ(2, S3::dtor_count);
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowOnCopyCtor
	{
		struct Exception{};
		ThrowOnCopyCtor() = default;
		ThrowOnCopyCtor(ThrowOnCopyCtor const&) { throw Exception{}; }
		ThrowOnCopyCtor(ThrowOnCopyCtor&&) {}
		ThrowOnCopyCtor& operator=(ThrowOnCopyCtor const&) = default;
	};

	{
		hamon::expected<void, ThrowOnCopyCtor> const src(hamon::in_place);
		hamon::expected<void, ThrowOnCopyCtor> dst(hamon::in_place);
		EXPECT_NO_THROW(dst = src);
		EXPECT_TRUE(dst.has_value());
	}
	{
		hamon::expected<void, ThrowOnCopyCtor> const src(hamon::in_place);
		hamon::expected<void, ThrowOnCopyCtor> dst(hamon::unexpect);
		EXPECT_NO_THROW(dst = src);
		EXPECT_TRUE(dst.has_value());
	}
	{
		hamon::expected<void, ThrowOnCopyCtor> const src(hamon::unexpect);
		hamon::expected<void, ThrowOnCopyCtor> dst(hamon::in_place);
		EXPECT_THROW(dst = src, ThrowOnCopyCtor::Exception);
		EXPECT_TRUE(dst.has_value());
	}
	{
		hamon::expected<void, ThrowOnCopyCtor> const src(hamon::unexpect);
		hamon::expected<void, ThrowOnCopyCtor> dst(hamon::unexpect);
		EXPECT_NO_THROW(dst = src);
		EXPECT_TRUE(!dst.has_value());
	}
#endif
}

GTEST_TEST(ExpectedVoidTest, OpAssignCopyTest)
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

}	// namespace op_assign_copy_test

}	// namespace hamon_expected_void_test
