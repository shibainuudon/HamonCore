/**
 *	@file	unit_test_expected_ctor_in_place_init_list.cpp
 *
 *	@brief	in_place_t と initializer_list を引数に取るコンストラクタのテスト
 *
 *	template<class U, class... Args>
 *	constexpr explicit expected(in_place_t, initializer_list<U>, Args&&...);
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

namespace ctor_in_place_init_list_test
{

struct S1
{
	S1();
};

struct S2
{
	HAMON_CXX14_CONSTEXPR S2(std::initializer_list<int>) noexcept {}
};

struct S3
{
	HAMON_CXX14_CONSTEXPR S3(std::initializer_list<int>, int) {}
	HAMON_CXX14_CONSTEXPR S3(std::initializer_list<int>, int, int) noexcept {}
};

static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert( hamon::is_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");

static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
#endif

static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::in_place_t, std::initializer_list<int>, int, int, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		hamon::expected<S2, int> x{hamon::in_place, {1,2,3}};
		VERIFY(x.has_value());
	}
	{
		hamon::expected<S3, double> x{hamon::in_place, {1,2,3}, 4};
		VERIFY(x.has_value());
	}
	return true;
}

struct ComplexType
{
	hamon::string data;
	hamon::vector<int> seq;

	HAMON_CXX14_CONSTEXPR
	ComplexType(std::initializer_list<int> il, hamon::string_view sv)
		: data(sv), seq(il) {}
};

HAMON_CXX20_CONSTEXPR bool test2()
{
	{
		hamon::expected<ComplexType, int> x {hamon::in_place, {5, 6, 7, 8}, "Steps"};
		VERIFY(x.has_value());
		VERIFY(x.value().data == "Steps");
		VERIFY((x.value().seq == hamon::vector<int>{5, 6, 7, 8}));
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
		ThrowOnCtor(std::initializer_list<int>) { throw Exception{}; }
	};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable");
	{
		using Expected = hamon::expected<ThrowOnCtor, int>;
		EXPECT_THROW(Expected e(hamon::in_place, {1,2,3}), ThrowOnCtor::Exception);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorInPlaceInitListTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));

	exceptions_test();
}

}	// namespace ctor_in_place_init_list_test

}	// namespace hamon_expected_test
