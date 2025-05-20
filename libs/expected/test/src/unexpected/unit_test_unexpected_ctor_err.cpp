/**
 *	@file	unit_test_unexpected_ctor_err.cpp
 *
 *	@brief	Err からのコンストラクタのテスト
 *
 *	template<class Err = E>
 *	constexpr explicit unexpected(Err&&);
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace ctor_err_test
{

// Test Constraints:
static_assert(hamon::is_constructible<hamon::unexpected<int>, int>::value, "");
#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(hamon::is_nothrow_constructible<hamon::unexpected<int>, int>::value, "");
#endif

struct CstrFromInt
{
	CstrFromInt(int);
};
static_assert(hamon::is_constructible<hamon::unexpected<CstrFromInt>, int>::value, "");
#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::unexpected<CstrFromInt>, int>::value, "");
#endif

// is_same_v<remove_cvref_t<Err>, unexpected>
struct CstrFromUnexpected
{
	CstrFromUnexpected(CstrFromUnexpected const&) = delete;
	CstrFromUnexpected(hamon::unexpected<CstrFromUnexpected> const&);
};
static_assert(!hamon::is_constructible<hamon::unexpected<CstrFromUnexpected>, hamon::unexpected<CstrFromUnexpected>>::value, "");

// is_same_v<remove_cvref_t<Err>, in_place_t>
struct CstrFromInplace
{
	CstrFromInplace(hamon::in_place_t);
};
static_assert(!hamon::is_constructible<hamon::unexpected<CstrFromInplace>, hamon::in_place_t>::value, "");

// !is_constructible_v<E, Err>
struct Foo {};
static_assert(!hamon::is_constructible<hamon::unexpected<Foo>, int>::value, "");

// test explicit
static_assert(hamon::is_convertible<int, int>::value, "");
static_assert(!hamon::is_convertible<int, hamon::unexpected<int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Error
{
	int i;
	HAMON_CXX14_CONSTEXPR Error(int ii) : i(ii) {}
	HAMON_CXX14_CONSTEXPR Error(const Error& other) : i(other.i) {}
	HAMON_CXX14_CONSTEXPR Error(Error&& other) : i(other.i) { other.i = 0; }
	Error(std::initializer_list<Error>) { HAMON_ASSERT(false); }
};

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	// lvalue
	{
		Error e(5);
		hamon::unexpected<Error> unex(e);
		VERIFY(unex.error().i == 5);
		VERIFY(e.i == 5);
	}

	// rvalue
	{
		Error e(5);
		hamon::unexpected<Error> unex(hamon::move(e));
		VERIFY(unex.error().i == 5);
		VERIFY(e.i == 0);
	}

	// Direct-non-list-initializes: does not trigger initializer_list overload
	{
		Error e(5);
		hamon::unexpected<Error> unex(e);
		(void)unex;
	}

	// Test default template argument.
	// Without it, the template parameter cannot be deduced from an initializer list
	{
		struct Bar
		{
			int i;
			int j;
			constexpr Bar(int ii, int jj) : i(ii), j(jj) {}
		};
		hamon::unexpected<Bar> ue({5, 6});
		VERIFY(ue.error().i == 5);
		VERIFY(ue.error().j == 6);
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
	};

	EXPECT_THROW(hamon::unexpected<ThrowOnCtor> u(0), ThrowOnCtor::Exception);
#endif
}

GTEST_TEST(UnexpectedTest, CtorErrTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));

	test_exceptions();
}

}	// namespace ctor_err_test

}	// namespace hamon_unexpected_test
