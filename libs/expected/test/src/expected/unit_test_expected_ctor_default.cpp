/**
 *	@file	unit_test_expected_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr expected();
 */

#include <hamon/expected/expected.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace ctor_default_test
{

struct DefaultConstructible
{
	int value;
	constexpr DefaultConstructible() : value(42) {}
};
static_assert(hamon::is_default_constructible<DefaultConstructible>::value, "");

struct NonDefaultConstructible
{
	int value;
	constexpr NonDefaultConstructible(int v) : value(v) {}
};
static_assert(!hamon::is_default_constructible<NonDefaultConstructible>::value, "");

struct NothrowDefaultConstructible
{
	NothrowDefaultConstructible() noexcept;
};
static_assert(hamon::is_nothrow_default_constructible<NothrowDefaultConstructible>::value, "");

struct TriviallyDefaultConstructible
{
};
static_assert(hamon::is_trivially_default_constructible<TriviallyDefaultConstructible>::value, "");

struct ExplicitlyDefaultConstructible
{
	explicit ExplicitlyDefaultConstructible();
};
static_assert( hamon::is_default_constructible<ExplicitlyDefaultConstructible>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<ExplicitlyDefaultConstructible>::value, "");

static_assert( hamon::is_default_constructible<hamon::expected<int, int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::expected<DefaultConstructible,    DefaultConstructible>>::value, "");
static_assert( hamon::is_default_constructible<hamon::expected<DefaultConstructible,    NonDefaultConstructible>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::expected<NonDefaultConstructible, DefaultConstructible>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::expected<NonDefaultConstructible, NonDefaultConstructible>>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
//static_assert( hamon::is_nothrow_default_constructible<hamon::expected<int, int>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::expected<DefaultConstructible,        DefaultConstructible>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::expected<DefaultConstructible,        NothrowDefaultConstructible>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::expected<NothrowDefaultConstructible, DefaultConstructible>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::expected<NothrowDefaultConstructible, NothrowDefaultConstructible>>::value, "");
#endif

static_assert(!hamon::is_trivially_default_constructible<hamon::expected<int, int>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::expected<DefaultConstructible,          DefaultConstructible>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::expected<DefaultConstructible,          TriviallyDefaultConstructible>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::expected<TriviallyDefaultConstructible, DefaultConstructible>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::expected<TriviallyDefaultConstructible, TriviallyDefaultConstructible>>::value, "");

static_assert( hamon::is_implicitly_default_constructible<hamon::expected<int, int>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::expected<DefaultConstructible,           DefaultConstructible>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::expected<DefaultConstructible,           ExplicitlyDefaultConstructible>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::expected<ExplicitlyDefaultConstructible, DefaultConstructible>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::expected<ExplicitlyDefaultConstructible, ExplicitlyDefaultConstructible>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test1()
{
	hamon::expected<T, E> e;
	VERIFY(e.has_value());
	VERIFY(e.value() == T{});
	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	hamon::expected<DefaultConstructible, NonDefaultConstructible> e;
	VERIFY(e.has_value());
	VERIFY(e.value().value == 42);
	return true;
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowOnDefault
	{
		struct Exception{};
		ThrowOnDefault() { throw Exception{}; }
		ThrowOnDefault(ThrowOnDefault const&) = default;
		ThrowOnDefault(ThrowOnDefault&&) = default;
	};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable");
	{
		using Expected = hamon::expected<ThrowOnDefault, int>;
		EXPECT_THROW(Expected e, ThrowOnDefault::Exception);
	}
	{
		using Expected = hamon::expected<int, ThrowOnDefault>;
		EXPECT_NO_THROW(Expected e);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, hamon::string>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<hamon::string, int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));

	exceptions_test();
}

}	// namespace ctor_default_test

}	// namespace hamon_expected_test
