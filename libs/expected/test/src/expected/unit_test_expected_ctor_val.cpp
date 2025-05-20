/**
 *	@file	unit_test_expected_ctor_val.cpp
 *
 *	@brief	正常値からのコンストラクタのテスト
 *
 *	template<class U = remove_cv_t<T>>
 *	constexpr explicit(see below) expected(U&& v);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/memory.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace ctor_val_test
{

static_assert( hamon::is_constructible<hamon::expected<int, int>, int>::value, "");
#if !defined(HAMON_USE_STD_EXPECTED)
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, int>, int>::value, "");
#endif
static_assert(!hamon::is_trivially_constructible<hamon::expected<int, int>, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<int, int>, int>::value, "");

// is_same_v<remove_cvref_t<U>, in_place_t>
struct FromJustInplace
{
	FromJustInplace(hamon::in_place_t);
};
static_assert(!hamon::is_constructible<hamon::expected<FromJustInplace, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<FromJustInplace, int>, hamon::in_place_t const&>::value, "");

// is_same_v<expected, remove_cvref_t<U>>
// Note that result is true because it is covered by the constructors that take expected
static_assert(hamon::is_constructible<hamon::expected<int, int>, hamon::expected<int, int>&>::value, "");

// remove_cvref_t<U> is a specialization of unexpected
// Note that result is true because it is covered by the constructors that take unexpected
static_assert(hamon::is_constructible<hamon::expected<int, int>, hamon::unexpected<int>&>::value, "");

struct S1
{
};

struct S2
{
	int value;
	HAMON_CXX14_CONSTEXPR S2(int v) : value(v) {};
};

struct S3
{
	int value;
	HAMON_CXX14_CONSTEXPR explicit S3(int v) : value(v) {};
};

struct S4
{
	S4(int) noexcept;
};

static_assert(!hamon::is_constructible<hamon::expected<S1, int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<S2, int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<S3, int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<S4, int>, int>::value, "");
#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S1, int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S2, int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<S3, int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<S4, int>, int>::value, "");
#endif
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S1, int>, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<S2, int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<S3, int>, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<S4, int>, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		T const src{17};
		hamon::expected<T, E> dst = src;
		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{17});
	}
	{
		hamon::expected<T, E> dst{T{18}};
		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{18});
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	using IntPair  = hamon::pair<int, int>;
	using IntTuple = hamon::tuple<int, int>;
	{
		IntPair const src{1, 2};
		hamon::expected<IntTuple, int> dst = src;
		VERIFY(dst.has_value());
		VERIFY((dst.value() == IntTuple{1, 2}));
	}
	{
		IntPair src{1, 2};
		hamon::expected<IntTuple, int> dst = hamon::move(src);
		VERIFY(dst.has_value());
		VERIFY((dst.value() == IntTuple{1, 2}));
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test3()
{
	{
		hamon::expected<S2, S2> x = 43;
		VERIFY(x.has_value());
		VERIFY(x.value().value == 43);
	}
	{
		hamon::expected<S2, S3> x = 43;
		VERIFY(x.has_value());
		VERIFY(x.value().value == 43);
	}
	{
		hamon::expected<S3, S2> x{43};
		VERIFY(x.has_value());
		VERIFY(x.value().value == 43);
	}
	{
		hamon::expected<S3, S3> x{43};
		VERIFY(x.has_value());
		VERIFY(x.value().value == 43);
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test4()
{
	using UniquePtr = hamon::unique_ptr<int>;
	using SharedPtr = hamon::shared_ptr<int>;
	{
		UniquePtr src = hamon::make_unique<int>(42);
		hamon::expected<SharedPtr, int> dst = hamon::move(src);
		VERIFY(dst.has_value());
		VERIFY(*dst.value() == 42);
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
		EXPECT_THROW(Expected dst{13}, ThrowOnCtor::Exception);
	}
	{
		using Expected = hamon::expected<int, ThrowOnCtor>;
		EXPECT_NO_THROW(Expected dst{13});
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorValTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test3()));

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test4()));
#else
	EXPECT_TRUE((test4()));
#endif

	exceptions_test();
}

}	// namespace ctor_val_test

}	// namespace hamon_expected_test
