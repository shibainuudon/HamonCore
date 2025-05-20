/**
 *	@file	unit_test_unexpected_ctor_in_place_init_list.cpp
 *
 *	@brief	in_place_t と initializer_list を引数に取るコンストラクタのテスト
 *
 *	template<class U, class... Args>
 *	constexpr explicit unexpected(in_place_t, initializer_list<U>, Args&&...);
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace ctor_in_place_init_list_test
{

struct Arg
{
	int i;
	HAMON_CXX14_CONSTEXPR Arg(int ii) : i(ii) {}
	HAMON_CXX14_CONSTEXPR Arg(const Arg& other) : i(other.i) {}
	HAMON_CXX14_CONSTEXPR Arg(Arg&& other) : i(other.i) { other.i = 0; }
};

struct Error
{
	std::initializer_list<int> list;
	Arg arg;
	HAMON_CXX14_CONSTEXPR explicit Error(std::initializer_list<int> l, const Arg& a) : list(l), arg(a) {}
	HAMON_CXX14_CONSTEXPR explicit Error(std::initializer_list<int> l, Arg&& a) noexcept : list(l), arg(hamon::move(a)) {}
};

// Test Constraints:
static_assert( hamon::is_constructible<hamon::unexpected<Error>, hamon::in_place_t, std::initializer_list<int>, Arg const&>::value, "");
static_assert( hamon::is_constructible<hamon::unexpected<Error>, hamon::in_place_t, std::initializer_list<int>, Arg &&>::value, "");
#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::unexpected<Error>, hamon::in_place_t, std::initializer_list<int>, Arg const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::unexpected<Error>, hamon::in_place_t, std::initializer_list<int>, Arg &&>::value, "");
#endif

// !is_constructible_v<E, initializer_list<U>&, Args...>
struct Foo {};
static_assert(!hamon::is_constructible<hamon::unexpected<Error>, hamon::in_place_t, std::initializer_list<double>, Arg>::value, "");

// test explicit
static_assert(!hamon::is_implicitly_constructible<hamon::unexpected<Error>, hamon::in_place_t, std::initializer_list<int>, Arg>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	// lvalue
	{
		Arg a {5};
		auto l = {1, 2, 3};
		hamon::unexpected<Error> unex(hamon::in_place, l, a);
		VERIFY(unex.error().arg.i == 5);
		VERIFY(hamon::ranges::equal(unex.error().list, l));
		VERIFY(a.i == 5);
	}

	// rvalue
	{
		Arg a {5};
		auto l = {1, 2, 3};
		hamon::unexpected<Error> unex(hamon::in_place, l, hamon::move(a));
		VERIFY(unex.error().arg.i == 5);
		VERIFY(hamon::ranges::equal(unex.error().list, l));
		VERIFY(a.i == 0);
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
		ThrowOnCtor(std::initializer_list<int>) { throw Exception{}; }
		ThrowOnCtor(std::initializer_list<int>, int) { throw Exception{}; }
		ThrowOnCtor(std::initializer_list<int>, int, int) {}
	};

	EXPECT_THROW   (hamon::unexpected<ThrowOnCtor> u(hamon::in_place, {1,2}), ThrowOnCtor::Exception);
	EXPECT_THROW   (hamon::unexpected<ThrowOnCtor> u(hamon::in_place, {1,2}, 0), ThrowOnCtor::Exception);
	EXPECT_NO_THROW(hamon::unexpected<ThrowOnCtor> u(hamon::in_place, {1,2}, 0, 0));
#endif
}

GTEST_TEST(UnexpectedTest, CtorInPlaceInitListTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));

	test_exceptions();
}

}	// namespace ctor_in_place_init_list_test

}	// namespace hamon_unexpected_test
