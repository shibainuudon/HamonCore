/**
 *	@file	unit_test_expected_ctor_in_place.cpp
 *
 *	@brief	in_place_t を引数に取るコンストラクタのテスト
 *
 *	template<class... Args>
 *	constexpr explicit expected(in_place_t, Args&&...);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace ctor_in_place_test
{

struct S1
{
};

struct S2
{
	S2(int);
};

struct S3
{
	S3(int, int);
};

static_assert( hamon::is_constructible<hamon::expected<S1, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::in_place_t, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::in_place_t>::value, "");
static_assert( hamon::is_constructible<hamon::expected<S2, int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::in_place_t, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S3, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S3, int>, hamon::in_place_t, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<S3, int>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S3, int>, hamon::in_place_t, int, int, int>::value, "");

static_assert( hamon::is_constructible<hamon::expected<int, S1>, hamon::in_place_t>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, S1>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::in_place_t, int, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, S2>, hamon::in_place_t>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, S2>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S2>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S2>, hamon::in_place_t, int, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, S3>, hamon::in_place_t>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, S3>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S3>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S3>, hamon::in_place_t, int, int, int>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert( hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::in_place_t, int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::in_place_t, int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::in_place_t, int, int, int>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::in_place_t>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::in_place_t, int, int, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::in_place_t>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::in_place_t, int, int, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::in_place_t>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::in_place_t, int, int, int>::value, "");
#endif

static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::in_place_t, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::in_place_t, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::in_place_t, int, int, int>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::in_place_t, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::in_place_t, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::in_place_t, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::in_place_t, int, int, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		hamon::expected<T, E> x{hamon::in_place, T{10}};
		VERIFY(x.has_value());
		VERIFY(x.value() == T{10});
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	{
		hamon::expected<hamon::string, int> x {hamon::in_place, "C++", 1u};
		VERIFY(x.has_value());
		VERIFY(x.value() == "C");
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
		using Expected = hamon::expected<ThrowOnCtor, int>;
		EXPECT_THROW(Expected e(hamon::in_place, 10), ThrowOnCtor::Exception);
	}
	{
		using Expected = hamon::expected<int, ThrowOnCtor>;
		EXPECT_NO_THROW(Expected e(hamon::in_place, 10));
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorInPlaceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));

	exceptions_test();
}

}	// namespace ctor_in_place_test

}	// namespace hamon_expected_test
