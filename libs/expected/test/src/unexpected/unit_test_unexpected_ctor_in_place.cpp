/**
 *	@file	unit_test_unexpected_ctor_in_place.cpp
 *
 *	@brief	in_place_t を引数に取るコンストラクタのテスト
 *
 *	template<class... Args>
 *	constexpr explicit unexpected(in_place_t, Args&&...);
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace ctor_in_place_test
{

// Test Constraints:
static_assert(hamon::is_constructible<hamon::unexpected<int>, hamon::in_place_t, int>::value, "");
#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(hamon::is_nothrow_constructible<hamon::unexpected<int>, hamon::in_place_t, int>::value, "");
#endif

struct CstrFromInt
{
	CstrFromInt(int);
};
static_assert(hamon::is_constructible<hamon::unexpected<CstrFromInt>, hamon::in_place_t, int>::value, "");
#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::unexpected<CstrFromInt>, hamon::in_place_t, int>::value, "");
#endif

// !is_constructible_v<E, Args...>
struct Foo {};
static_assert(!hamon::is_constructible<hamon::unexpected<Foo>, hamon::in_place_t, int>::value, "");

// test explicit
static_assert(!hamon::is_implicitly_constructible<hamon::unexpected<int>, hamon::in_place_t, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Arg
{
	int i;
	HAMON_CXX14_CONSTEXPR Arg(int ii) : i(ii) {}
	HAMON_CXX14_CONSTEXPR Arg(const Arg& other) : i(other.i) {}
	HAMON_CXX14_CONSTEXPR Arg(Arg&& other) : i(other.i) { other.i = 0; }
};

struct Error
{
	Arg arg;
	HAMON_CXX14_CONSTEXPR explicit Error(const Arg& a) : arg(a) {}
	HAMON_CXX14_CONSTEXPR explicit Error(Arg&& a) : arg(hamon::move(a)) {}
	Error(std::initializer_list<Error>) :arg(0){ HAMON_ASSERT(false); }
};

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	// lvalue
	{
		Arg a {5};
		hamon::unexpected<Error> unex(hamon::in_place, a);
		VERIFY(unex.error().arg.i == 5);
		VERIFY(a.i == 5);
	}

	// rvalue
	{
		Arg a {5};
		hamon::unexpected<Error> unex(hamon::in_place, hamon::move(a));
		VERIFY(unex.error().arg.i == 5);
		VERIFY(a.i == 0);
	}

	// Direct-non-list-initializes: does not trigger initializer_list overload
	{
		Error e(5);
		hamon::unexpected<Error> unex(hamon::in_place, e);
		(void)unex;
	}

	return true;
}

#undef VERIFY

void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowOnCtor
	{
		struct Exception {};
		ThrowOnCtor(int) { throw Exception{}; }
		ThrowOnCtor(int, int) {}
		ThrowOnCtor(int, int, int) { throw Exception{}; }
	};

	EXPECT_THROW   (hamon::unexpected<ThrowOnCtor> u(hamon::in_place, 0), ThrowOnCtor::Exception);
	EXPECT_NO_THROW(hamon::unexpected<ThrowOnCtor> u(hamon::in_place, 0, 0));
	EXPECT_THROW   (hamon::unexpected<ThrowOnCtor> u(hamon::in_place, 0, 0, 0), ThrowOnCtor::Exception);
#endif
}

GTEST_TEST(UnexpectedTest, CtorInPlaceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));

	test_exceptions();
}

}	// namespace ctor_in_place_test

}	// namespace hamon_unexpected_test
