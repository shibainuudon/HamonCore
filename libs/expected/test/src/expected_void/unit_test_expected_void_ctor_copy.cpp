/**
 *	@file	unit_test_expected_void_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	constexpr expected(const expected& rhs);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace ctor_copy_test
{

struct CopyConstructible
{
	int value;
	constexpr CopyConstructible(int v) : value(v) {}
	constexpr CopyConstructible(CopyConstructible const& rhs) : value(rhs.value) {}
	CopyConstructible(CopyConstructible&&) = default;
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

static_assert( hamon::is_copy_constructible<hamon::expected<void, int>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::expected<void, CopyConstructible>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::expected<void, NonCopyConstructible>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::expected<void, NothrowCopyConstructible>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::expected<void, TriviallyCopyConstructible>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::expected<void, ExplicitlyCopyConstructible>>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert( hamon::is_nothrow_copy_constructible<hamon::expected<void, int>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::expected<void, CopyConstructible>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::expected<void, NonCopyConstructible>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::expected<void, NothrowCopyConstructible>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::expected<void, TriviallyCopyConstructible>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::expected<void, ExplicitlyCopyConstructible>>::value, "");
#endif

static_assert( hamon::is_trivially_copy_constructible<hamon::expected<void, int>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::expected<void, CopyConstructible>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::expected<void, NonCopyConstructible>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::expected<void, NothrowCopyConstructible>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::expected<void, TriviallyCopyConstructible>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::expected<void, ExplicitlyCopyConstructible>>::value, "");

static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<void, int>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<void, CopyConstructible>>::value, "");
static_assert(!hamon::is_implicitly_copy_constructible<hamon::expected<void, NonCopyConstructible>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<void, NothrowCopyConstructible>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<void, TriviallyCopyConstructible>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::expected<void, ExplicitlyCopyConstructible>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test1()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, int> const x{hamon::in_place};
		hamon::expected<Void, int> y = x;
		VERIFY(x.has_value());
		VERIFY(y.has_value());
	}
	{
		hamon::expected<Void, int> const x{hamon::unexpect, 42};
		hamon::expected<Void, int> y = x;
		VERIFY(!x.has_value());
		VERIFY(!y.has_value());
		VERIFY(x.error() == 42);
		VERIFY(y.error() == 42);
	}

	return true;
}

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test2()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, CopyConstructible> const x{hamon::in_place};
		hamon::expected<Void, CopyConstructible> y = x;
		VERIFY(x.has_value());
		VERIFY(y.has_value());
	}
	{
		hamon::expected<Void, CopyConstructible> const x{hamon::unexpect, 42};
		hamon::expected<Void, CopyConstructible> y = x;
		VERIFY(!x.has_value());
		VERIFY(!y.has_value());
		VERIFY(x.error().value == 42);
		VERIFY(y.error().value == 42);
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
		hamon::expected<void, int> src;
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<void, ThrowOnCopy> src;
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<void, int> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = src);
	}
	{
		hamon::expected<void, ThrowOnCopy> src{hamon::unexpect};
		EXPECT_THROW(auto dst = src, ThrowOnCopy::Exception);
	}
	{
		hamon::expected<void, int> src;
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<void, ThrowOnCopy> src;
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<void, int> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
	{
		hamon::expected<void, ThrowOnCopy> src{hamon::unexpect};
		EXPECT_NO_THROW(auto dst = hamon::move(src));
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedVoidTest, CtorCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<void const volatile>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void const volatile>()));

	exceptions_test();
}

}	// namespace ctor_copy_test

}	// namespace hamon_expected_void_test
