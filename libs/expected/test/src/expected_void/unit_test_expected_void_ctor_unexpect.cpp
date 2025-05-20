/**
 *	@file	unit_test_expected_void_ctor_unexpect.cpp
 *
 *	@brief	unexpect_t を引数に取るコンストラクタのテスト
 *
 *	template<class... Args>
 *	constexpr explicit expected(unexpect_t, Args&&...);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace ctor_unexpect_test
{

struct S1
{
};

struct S2
{
	int value;
	constexpr S2(int v) : value(v) {}
};

struct S3
{
	int value;
	constexpr S3(int v) noexcept : value(v) {}
};

static_assert( hamon::is_constructible<hamon::expected<void, int>, hamon::unexpect_t>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, int>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, int>, hamon::unexpect_t, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, S1>, hamon::unexpect_t>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, S1>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, S1>, hamon::unexpect_t, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, S2>, hamon::unexpect_t>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, S2>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, S2>, hamon::unexpect_t, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, S3>, hamon::unexpect_t>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, S3>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, S3>, hamon::unexpect_t, int, int>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, int>, hamon::unexpect_t>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, int>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, int>, hamon::unexpect_t, int, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, S1>, hamon::unexpect_t>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, S1>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, S1>, hamon::unexpect_t, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, S2>, hamon::unexpect_t>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, S2>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, S2>, hamon::unexpect_t, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, S3>, hamon::unexpect_t>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, S3>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, S3>, hamon::unexpect_t, int, int>::value, "");
#endif

static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, int>, hamon::unexpect_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, int>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, int>, hamon::unexpect_t, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S1>, hamon::unexpect_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S1>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S1>, hamon::unexpect_t, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S2>, hamon::unexpect_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S2>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S2>, hamon::unexpect_t, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S3>, hamon::unexpect_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S3>, hamon::unexpect_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S3>, hamon::unexpect_t, int, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, int> x{hamon::unexpect};
		VERIFY(!x.has_value());
		VERIFY(x.error() == 0);
	}
	{
		hamon::expected<Void, int> x{hamon::unexpect, 10};
		VERIFY(!x.has_value());
		VERIFY(x.error() == 10);
	}
	{
		hamon::expected<Void, S2> x{hamon::unexpect, 13};
		VERIFY(!x.has_value());
		VERIFY(x.error().value == 13);
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
		using Expected = hamon::expected<void, ThrowOnCtor>;
		EXPECT_THROW(Expected e(hamon::unexpect, 10), ThrowOnCtor::Exception);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedVoidTest, CtorUnexpectTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile>()));

	exceptions_test();
}

}	// namespace ctor_unexpect_test

}	// namespace hamon_expected_void_test
