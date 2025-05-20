/**
 *	@file	unit_test_expected_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	constexpr expected(const expected&);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace ctor_copy_test
{

struct CopyConstructible
{
	CopyConstructible(CopyConstructible const&);
};
static_assert(hamon::is_copy_constructible<CopyConstructible>::value, "");

struct NonCopyConstructible
{
	NonCopyConstructible(NonCopyConstructible const&) = delete;
};
static_assert(!hamon::is_copy_constructible<NonCopyConstructible>::value, "");

struct NothrowCopyConstructible
{
	NothrowCopyConstructible(NothrowCopyConstructible const&) noexcept;
};
static_assert(hamon::is_nothrow_copy_constructible<NothrowCopyConstructible>::value, "");

struct TriviallyCopyConstructible
{
};
static_assert(hamon::is_trivially_copy_constructible<TriviallyCopyConstructible>::value, "");

struct ExplicitlyCopyConstructible
{
	explicit ExplicitlyCopyConstructible(ExplicitlyCopyConstructible const&);
};
static_assert( hamon::is_copy_constructible<ExplicitlyCopyConstructible>::value, "");
static_assert(!hamon::is_implicitly_copy_constructible<ExplicitlyCopyConstructible>::value, "");

static_assert( hamon::is_copy_constructible<hamon::expected<int, int>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::expected<CopyConstructible,    CopyConstructible>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::expected<CopyConstructible,    NonCopyConstructible>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::expected<NonCopyConstructible, CopyConstructible>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::expected<NonCopyConstructible, NonCopyConstructible>>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert( hamon::is_nothrow_copy_constructible<hamon::expected<int, int>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::expected<CopyConstructible,        CopyConstructible>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::expected<CopyConstructible,        NothrowCopyConstructible>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::expected<NothrowCopyConstructible, CopyConstructible>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::expected<NothrowCopyConstructible, NothrowCopyConstructible>>::value, "");
#endif

static_assert( hamon::is_trivially_copy_constructible<hamon::expected<int, int>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::expected<CopyConstructible,          CopyConstructible>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::expected<CopyConstructible,          TriviallyCopyConstructible>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::expected<TriviallyCopyConstructible, CopyConstructible>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::expected<TriviallyCopyConstructible, TriviallyCopyConstructible>>::value, "");

static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<int, int>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<CopyConstructible,           CopyConstructible>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<CopyConstructible,           ExplicitlyCopyConstructible>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<ExplicitlyCopyConstructible, CopyConstructible>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<ExplicitlyCopyConstructible, ExplicitlyCopyConstructible>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> const x = T{42};
		hamon::expected<T, E> y = x;
		VERIFY(x.has_value());
		VERIFY(y.has_value());
		VERIFY(x.value() == T{42});
		VERIFY(y.value() == T{42});
	}
	{
		hamon::expected<T, E> const x = hamon::unexpected<E>{E{13}};
		hamon::expected<T, E> y = x;
		VERIFY(!x.has_value());
		VERIFY(!y.has_value());
		VERIFY(x.error() == E{13});
		VERIFY(y.error() == E{13});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		hamon::expected<T, hamon::string> x = T{43};
		hamon::expected<T, hamon::string> y = x;
		VERIFY(x.has_value());
		VERIFY(y.has_value());
		VERIFY(x.value() == T{43});
		VERIFY(y.value() == T{43});
	}
	{
		hamon::expected<T, hamon::string> x = hamon::unexpected<hamon::string>{"Oops"};
		hamon::expected<T, hamon::string> y = x;
		VERIFY(!x.has_value());
		VERIFY(!y.has_value());
		VERIFY(x.error() == "Oops");
		VERIFY(y.error() == "Oops");
	}
	return true;
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowOnCopy
	{
		struct Exception{};
		ThrowOnCopy() = default;
		ThrowOnCopy(ThrowOnCopy const&) { throw Exception{}; }
		ThrowOnCopy(ThrowOnCopy&&) = default;
	};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable");
	{
		hamon::expected<ThrowOnCopy, int> src;
		EXPECT_THROW(auto dst = src, ThrowOnCopy::Exception);
	}
	{
		hamon::expected<int, ThrowOnCopy> src;
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<ThrowOnCopy, int> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<int, ThrowOnCopy> src{hamon::unexpect};
		EXPECT_THROW(auto dst = src, ThrowOnCopy::Exception);
	}
	{
		hamon::expected<ThrowOnCopy, int> src;
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<int, ThrowOnCopy> src;
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<ThrowOnCopy, int> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<int, ThrowOnCopy> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<double>()));

	exceptions_test();
}

}	// namespace ctor_copy_test

}	// namespace hamon_expected_test
