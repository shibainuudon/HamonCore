/**
 *	@file	unit_test_expected_void_ctor_conv_copy.cpp
 *
 *	@brief	変換コピーコンストラクタのテスト
 *
 *	template<class U, class G>
 *	constexpr explicit(see below) expected(const expected<U, G>&);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace ctor_conv_copy_test
{

// Test Constraints:
template <typename T1, typename E1, typename T2, typename E2>
using CanCstrFromExpected = hamon::is_constructible<hamon::expected<T1, E1>, const hamon::expected<T2, E2>&>;

struct CtorFromInt
{
	CtorFromInt(int);
};

static_assert(CanCstrFromExpected<void, CtorFromInt, void, int>::value, "");

struct NoCtorFromInt {};

// !is_void_v<E>
static_assert(!CanCstrFromExpected<void, int, int, int>::value, "");

// !is_constructible_v<E, GF>
static_assert(!CanCstrFromExpected<void, NoCtorFromInt, void, int>::value, "");

template <typename T>
struct CtorFrom
{
	explicit CtorFrom(int);

	explicit CtorFrom(T);

	template <typename U>
	explicit CtorFrom(U&&) = delete;
};

template <>
struct CtorFrom<int>
{
	explicit CtorFrom(int);

	template <typename U>
	explicit CtorFrom(U&&) = delete;
};

// Note for below 4 tests, because their E is constructible from cvref of hamon::expected<void, int>,
// unexpected<E> will be constructible from cvref of hamon::expected<void, int>
// is_constructible_v<unexpected<E>, expected<U, G>&>
static_assert(!CanCstrFromExpected<void, CtorFrom<hamon::expected<void, int>&>, void, int>::value, "");

// is_constructible_v<unexpected<E>, expected<U, G>>
static_assert(!CanCstrFromExpected<void, CtorFrom<hamon::expected<void, int>&&>, void, int>::value, "");

// is_constructible_v<unexpected<E>, const expected<U, G>&> is false
static_assert(!CanCstrFromExpected<void, CtorFrom<hamon::expected<void, int> const&>, void, int>::value, "");

// is_constructible_v<unexpected<E>, const expected<U, G>>
static_assert(!CanCstrFromExpected<void, CtorFrom<hamon::expected<void, int> const&&>, void, int>::value, "");

// test explicit
static_assert(hamon::is_convertible<const hamon::expected<void, int>&, hamon::expected<void, long>>::value, "");

// !is_convertible_v<GF, E>.
static_assert(hamon::is_constructible<hamon::expected<void, CtorFrom<int>>, const hamon::expected<void, int>&>::value, "");
static_assert(!hamon::is_convertible<const hamon::expected<void, int>&, hamon::expected<void, CtorFrom<int>>>::value, "");

// test noexcept

#if !defined(HAMON_USE_STD_EXPECTED)
template <typename T>
struct NothrowCtorFrom
{
	explicit NothrowCtorFrom(T const&) noexcept;
	explicit NothrowCtorFrom(T&&);
};

static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, CtorFrom<int>>, const hamon::expected<void, int>&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, NothrowCtorFrom<int>>, const hamon::expected<void, int>&>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct S1
{
	int value;
	constexpr S1(int v) : value(v) {}
};

struct S2
{
	int value;
	constexpr explicit S2(int v) : value(v) {}
};

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, int> const src{hamon::in_place};
		hamon::expected<Void, double> dst = src;
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
	}
	{
		hamon::expected<Void, int> const src{hamon::unexpect, 5};
		hamon::expected<Void, double> dst = src;
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(src.error() == 5);
		VERIFY(dst.error() == 5.0);
	}
	{
		hamon::expected<Void, int> const src{hamon::unexpect, 10};
		hamon::expected<Void, S1> dst = src;
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(src.error() == 10);
		VERIFY(dst.error().value == 10);
	}
	{
		hamon::expected<Void, int> const src{hamon::unexpect, 10};
		hamon::expected<Void, S2> dst{src};
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(src.error() == 10);
		VERIFY(dst.error().value == 10);
	}
	return true;
}

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test2()
{
	using IntPair  = hamon::pair<int, int>;
	using IntTuple = hamon::tuple<int, int>;

	{
		hamon::expected<Void, IntPair> src{hamon::unexpect, 1, 2};
		hamon::expected<Void, IntTuple> dst = src;
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY((dst.error() == IntTuple{1, 2}));
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
		hamon::expected<void, int> const src;
		using Expected = hamon::expected<void, ThrowOnCtor>;
		EXPECT_NO_THROW(Expected dst{src});
	}
	{
		hamon::expected<void, int> const src{hamon::unexpect};
		using Expected = hamon::expected<void, ThrowOnCtor>;
		EXPECT_THROW(Expected dst{src}, ThrowOnCtor::Exception);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedVoidTest, CtorConvCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void const volatile>()));

	exceptions_test();
}

}	// namespace ctor_conv_copy_test

}	// namespace hamon_expected_void_test
