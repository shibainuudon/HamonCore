/**
 *	@file	unit_test_expected_op_assign_unexpected_copy.cpp
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
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
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
static_assert(hamon::is_assignable<hamon::expected<int, int>&, const hamon::unexpected<int>&>::value, "");

// !is_constructible_v<E, GF>
static_assert(!hamon::is_assignable<hamon::expected<int, NotCopyConstructible>&, const hamon::unexpected<NotCopyConstructible>&>::value, "");

// !is_assignable_v<E&, GF>
static_assert(!hamon::is_assignable<hamon::expected<int, NotCopyAssignable>&, const hamon::unexpected<NotCopyAssignable>&>::value, "");

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
static_assert(hamon::is_assignable<hamon::expected<MaybeNoexcept<false, false>, MaybeNoexcept<true, false>>&, const hamon::unexpected<int>&>::value, "");

// is_nothrow_constructible_v<E, GF> && !is_nothrow_move_constructible_v<T> &&
// !is_nothrow_move_constructible_v<E>
static_assert(hamon::is_assignable<hamon::expected<MaybeNoexcept<false, false>, MaybeNoexcept<false, true>>&, const hamon::unexpected<int>&>::value, "");

// !is_nothrow_constructible_v<E, GF> && is_nothrow_move_constructible_v<T> &&
// !is_nothrow_move_constructible_v<E>
static_assert(hamon::is_assignable<hamon::expected<MaybeNoexcept<true, true>, MaybeNoexcept<false, false>>&, const hamon::unexpected<int>&>::value, "");

// !is_nothrow_constructible_v<E, GF> && !is_nothrow_move_constructible_v<T> &&
// !is_nothrow_move_constructible_v<E>
static_assert(!hamon::is_assignable<hamon::expected<MaybeNoexcept<false, false>, MaybeNoexcept<false, false>>&, const hamon::unexpected<int>&>::value, "");

// test noexcept

#if !defined(HAMON_USE_STD_EXPECTED)
template <bool CtorNoexcept, bool AssignNoexcept>
struct MaybeNoexcept2
{
	MaybeNoexcept2(int) noexcept(CtorNoexcept);
	MaybeNoexcept2& operator=(int) noexcept(AssignNoexcept);
};

static_assert( hamon::is_nothrow_assignable<hamon::expected<int, int>&, const hamon::unexpected<int>&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<MaybeNoexcept2<true, true>, int>&, const hamon::unexpected<int>&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<MaybeNoexcept2<true, false>, int>&, const hamon::unexpected<int>&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<MaybeNoexcept2<false, true>, int>&, const hamon::unexpected<int>&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<MaybeNoexcept2<false, false>, int>&, const hamon::unexpected<int>&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::expected<int, MaybeNoexcept2<true, true>>&, const hamon::unexpected<int>&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<int, MaybeNoexcept2<true, false>>&, const hamon::unexpected<int>&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<int, MaybeNoexcept2<false, true>>&, const hamon::unexpected<int>&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::expected<int, MaybeNoexcept2<false, false>>&, const hamon::unexpected<int>&>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::unexpected<E> const src{E{3}};
		hamon::expected<T, E> dst{hamon::in_place, T{4}};
		auto& r = (dst = src);
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{3});
	}
	{
		hamon::unexpected<E> const src{E{5}};
		hamon::expected<T, E> dst{hamon::unexpect, E{6}};
		auto& r = (dst = src);
		static_assert(hamon::is_same<decltype(r), hamon::expected<T, E>&>::value, "");
		VERIFY(&r == &dst);

		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{5});
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

void trase_test()
{
	S3::reset();
	{
		hamon::unexpected<S3> const src{S3{}};
		hamon::expected<int, S3> dst{hamon::in_place};
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
		hamon::expected<int, S3> dst{hamon::unexpect};
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

	S4::reset();
	{
		hamon::unexpected<S4> const src{S4{}};
		hamon::expected<int, S4> dst{hamon::in_place};
		dst = src;
		EXPECT_EQ(1, S4::default_ctor_count);
		EXPECT_EQ(1, S4::copy_ctor_count);
		EXPECT_EQ(2, S4::move_ctor_count);
		EXPECT_EQ(0, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(2, S4::dtor_count);
	}
	EXPECT_EQ(1, S4::default_ctor_count);
	EXPECT_EQ(1, S4::copy_ctor_count);
	EXPECT_EQ(2, S4::move_ctor_count);
	EXPECT_EQ(0, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(4, S4::dtor_count);

	S4::reset();
	{
		hamon::unexpected<S4> const src{S4{}};
		hamon::expected<int, S4> dst{hamon::unexpect};
		dst = src;
		EXPECT_EQ(2, S4::default_ctor_count);
		EXPECT_EQ(0, S4::copy_ctor_count);
		EXPECT_EQ(1, S4::move_ctor_count);
		EXPECT_EQ(1, S4::copy_assign_count);
		EXPECT_EQ(0, S4::move_assign_count);
		EXPECT_EQ(1, S4::dtor_count);
	}
	EXPECT_EQ(2, S4::default_ctor_count);
	EXPECT_EQ(0, S4::copy_ctor_count);
	EXPECT_EQ(1, S4::move_ctor_count);
	EXPECT_EQ(1, S4::copy_assign_count);
	EXPECT_EQ(0, S4::move_assign_count);
	EXPECT_EQ(3, S4::dtor_count);
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
		hamon::expected<int, ThrowOnCtor> dst(hamon::in_place, 5);
		hamon::unexpected<int> const src{10};
		EXPECT_THROW(dst = src, ThrowOnCtor::Exception);
		EXPECT_TRUE(dst.has_value());
		EXPECT_TRUE(dst.value() == 5);
	}
#endif
}

GTEST_TEST(ExpectedTest, OpAssignUnexpectedCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, S1>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, S2>()));

	trase_test();

	exceptions_test();
}

}	// namespace op_assign_unexpected_copy_test

}	// namespace hamon_expected_test
