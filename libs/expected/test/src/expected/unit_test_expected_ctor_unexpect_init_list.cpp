/**
 *	@file	unit_test_expected_ctor_unexpect_init_list.cpp
 *
 *	@brief	unexpect_t と initializer_list を引数に取るコンストラクタのテスト
 *
 *	template<class U, class... Args>
 *	constexpr explicit expected(unexpect_t, initializer_list<U>, Args&&...);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace ctor_unexpect_init_list_test
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

static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");

static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");

static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
#endif

static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S2, int>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S1>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S2>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, S3>, hamon::unexpect_t, std::initializer_list<int>, int, int, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		hamon::expected<int, S2> x{hamon::unexpect, {1,2,3}};
		VERIFY(!x.has_value());
	}
	{
		hamon::expected<double, S3> x{hamon::unexpect, {1,2,3}, 5};
		VERIFY(!x.has_value());
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
		hamon::expected<int, ComplexType> x {hamon::unexpect, {5, 6, 7, 8}, "Steps"};
		VERIFY(!x.has_value());
		VERIFY(x.error().data == "Steps");
		VERIFY((x.error().seq == hamon::vector<int>{5, 6, 7, 8}));
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
		using Expected = hamon::expected<int, ThrowOnCtor>;
		EXPECT_THROW(Expected e(hamon::unexpect, {1,2,3}), ThrowOnCtor::Exception);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorUnexpectInitListTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));

	exceptions_test();
}

}	// namespace ctor_unexpect_init_list_test

}	// namespace hamon_expected_test
