/**
 *	@file	unit_test_expected_ctor_conv_copy.cpp
 *
 *	@brief	変換コピーコンストラクタのテスト
 *
 *	template<class U, class G>
 *	constexpr explicit(see below) expected(const expected<U, G>&);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
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

static_assert(CanCstrFromExpected<CtorFromInt, int, int, int>::value, "");

struct NoCtorFromInt {};

// !is_constructible_v<T, UF>
static_assert(!CanCstrFromExpected<NoCtorFromInt, int, int, int>::value, "");

// !is_constructible_v<E, GF>
static_assert(!CanCstrFromExpected<int, NoCtorFromInt, int, int>::value, "");

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

// is_constructible_v<T, expected<U, G>&>
static_assert(!CanCstrFromExpected<CtorFrom<hamon::expected<int, int>&>, int, int, int>::value, "");

// is_constructible_v<T, expected<U, G>>
static_assert(!CanCstrFromExpected<CtorFrom<hamon::expected<int, int>&&>, int, int, int>::value, "");

// is_constructible_v<T, expected<U, G>&>
// note that this is true because it is covered by the other overload
//   template<typename U = T> constexpr explicit(see below) expected(U&& v);
// The fact that it is not ambiguous proves that the overload under testing is removed
static_assert(CanCstrFromExpected<CtorFrom<hamon::expected<int, int> const&>, int, int, int>::value, "");

// is_constructible_v<T, expected<U, G>>
static_assert(!CanCstrFromExpected<CtorFrom<hamon::expected<int, int> const&&>, int, int, int>::value, "");

template <typename T>
struct ConvertFrom
{
	ConvertFrom(int);

	ConvertFrom(T);

	template <typename U>
	ConvertFrom(U&&) = delete;
};

template <>
struct ConvertFrom<int>
{
	ConvertFrom(int);

	template <typename U>
	ConvertFrom(U&&) = delete;
};

// is_convertible_v<expected<U, G>&, T>
static_assert(!CanCstrFromExpected<ConvertFrom<hamon::expected<int, int>&>, int, int, int>::value, "");

// is_convertible_v<expected<U, G>&&, T>
static_assert(!CanCstrFromExpected<ConvertFrom<hamon::expected<int, int>&&>, int, int, int>::value, "");

// is_convertible_v<const expected<U, G>&, T>
// note that this is true because it is covered by the other overload
//   template<typename U = T> constexpr explicit(see below) expected(U&& v);
// The fact that it is not ambiguous proves that the overload under testing is removed
static_assert(CanCstrFromExpected<ConvertFrom<hamon::expected<int, int> const&>, int, int, int>::value, "");

// is_convertible_v<const expected<U, G>&&, T>
static_assert(!CanCstrFromExpected<ConvertFrom<hamon::expected<int, int> const&&>, int, int, int>::value, "");

// Note for below 4 tests, because their E is constructible from cvref of hamon::expected<int, int>,
// unexpected<E> will be constructible from cvref of hamon::expected<int, int>
// is_constructible_v<unexpected<E>, expected<U, G>&>
static_assert(!CanCstrFromExpected<int, CtorFrom<hamon::expected<int, int>&>, int, int>::value, "");

// is_constructible_v<unexpected<E>, expected<U, G>>
static_assert(!CanCstrFromExpected<int, CtorFrom<hamon::expected<int, int>&&>, int, int>::value, "");

// is_constructible_v<unexpected<E>, const expected<U, G>&> is false
static_assert(!CanCstrFromExpected<int, CtorFrom<hamon::expected<int, int> const&>, int, int>::value, "");

// is_constructible_v<unexpected<E>, const expected<U, G>>
static_assert(!CanCstrFromExpected<int, CtorFrom<hamon::expected<int, int> const&&>, int, int>::value, "");

// test explicit
static_assert(hamon::is_convertible<const hamon::expected<int, int>&, hamon::expected<short, long>>::value, "");

// !is_convertible_v<UF, T>
static_assert(hamon::is_constructible<hamon::expected<CtorFrom<int>, int>, const hamon::expected<int, int>&>::value, "");
static_assert(!hamon::is_convertible<const hamon::expected<int, int>&, hamon::expected<CtorFrom<int>, int>>::value, "");

// !is_convertible_v<GF, E>.
static_assert(hamon::is_constructible<hamon::expected<int, CtorFrom<int>>, const hamon::expected<int, int>&>::value, "");
static_assert(!hamon::is_convertible<const hamon::expected<int, int>&, hamon::expected<int, CtorFrom<int>>>::value, "");

// test noexcept

#if !defined(HAMON_USE_STD_EXPECTED)
template <typename T>
struct NothrowCtorFrom
{
	explicit NothrowCtorFrom(T const&) noexcept;
	explicit NothrowCtorFrom(T&&) = delete;
};

static_assert(!hamon::is_nothrow_constructible<hamon::expected<CtorFrom<int>, CtorFrom<int>>, hamon::expected<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<CtorFrom<int>, NothrowCtorFrom<int>>, hamon::expected<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<NothrowCtorFrom<int>, CtorFrom<int>>, hamon::expected<int, int> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<NothrowCtorFrom<int>, NothrowCtorFrom<int>>, hamon::expected<int, int> const&>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> src = T{13};
		hamon::expected<double, double> dst = src;
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY(src.value() == T{13});
		VERIFY(dst.value() == 13.0);
	}
	{
		hamon::expected<T, E> src = hamon::unexpected<E>{E{14}};
		hamon::expected<double, double> dst = src;
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(src.error() == E{14});
		VERIFY(dst.error() == 14.0);
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test2()
{
	using IntPair  = hamon::pair<int, int>;
	using IntTuple = hamon::tuple<int, int>;

	{
		hamon::expected<IntPair, T> src = IntPair{1, 2};
		hamon::expected<IntTuple, T> dst = src;
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY((dst.value() == IntTuple {1, 2}));
	}
	{
		hamon::expected<T, IntPair> src{hamon::unexpect, 1, 2};
		hamon::expected<T, IntTuple> dst = src;
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY((dst.error() == IntTuple {1, 2}));
	}

	return true;
}

struct S1
{
	int value;

	HAMON_CXX14_CONSTEXPR S1(int v) : value(v) {}
};

struct S2
{
	int value;

	HAMON_CXX14_CONSTEXPR explicit S2(int v) : value(v) {}
};

HAMON_CXX14_CONSTEXPR bool test3()
{
	{
		hamon::expected<int, int> src{42};
		hamon::expected<S1, S1> dst = src;
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY(dst.value().value == 42);
	}
	{
		hamon::expected<int, int> src{42};
		hamon::expected<S1, S2> dst{src};
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY(dst.value().value == 42);
	}
	{
		hamon::expected<int, int> src{42};
		hamon::expected<S2, S1> dst{src};
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY(dst.value().value == 42);
	}
	{
		hamon::expected<int, int> src{42};
		hamon::expected<S2, S2> dst{src};
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY(dst.value().value == 42);
	}
	{
		hamon::expected<int, int> src{hamon::unexpect, 42};
		hamon::expected<S1, S1> dst = src;
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 42);
	}
	{
		hamon::expected<int, int> src{hamon::unexpect, 42};
		hamon::expected<S1, S2> dst{src};
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 42);
	}
	{
		hamon::expected<int, int> src{hamon::unexpect, 42};
		hamon::expected<S2, S1> dst{src};
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 42);
	}
	{
		hamon::expected<int, int> src{hamon::unexpect, 42};
		hamon::expected<S2, S2> dst{src};
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 42);
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
		hamon::expected<int, int> const src;
		using Expected = hamon::expected<ThrowOnCtor, int>;
		EXPECT_THROW(Expected dst{src}, ThrowOnCtor::Exception);
	}
	{
		hamon::expected<int, int> const src;
		using Expected = hamon::expected<int, ThrowOnCtor>;
		EXPECT_NO_THROW(Expected dst{src});
	}
	{
		hamon::expected<int, int> const src{hamon::unexpect};
		using Expected = hamon::expected<ThrowOnCtor, int>;
		EXPECT_NO_THROW(Expected dst{src});
	}
	{
		hamon::expected<int, int> const src{hamon::unexpect};
		using Expected = hamon::expected<int, ThrowOnCtor>;
		EXPECT_THROW(Expected dst{src}, ThrowOnCtor::Exception);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorConvCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test3()));

	exceptions_test();
}

}	// namespace ctor_conv_copy_test

}	// namespace hamon_expected_test
