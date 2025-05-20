/**
 *	@file	unit_test_expected_void_ctor_unexpected_copy.cpp
 *
 *	@brief	unexpected const& からのコンストラクタのテスト
 *
 *	template<class G>
 *	constexpr explicit(see below) expected(const unexpected<G>&);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace ctor_unexpected_copy_test
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

struct CtorFromInt
{
	CtorFromInt(int);
};

struct ConvertibleToInt
{
	operator int() const;
};

static_assert( hamon::is_constructible<hamon::expected<void, int>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, CopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, NonCopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, NothrowCopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, TriviallyCopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, ExplicitlyCopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, CtorFromInt>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, ConvertibleToInt>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, int>, hamon::unexpected<CtorFromInt> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, int>, hamon::unexpected<ConvertibleToInt> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, CopyConstructible>, hamon::unexpected<CopyConstructible> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, NonCopyConstructible>, hamon::unexpected<NonCopyConstructible> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, NothrowCopyConstructible>, hamon::unexpected<NothrowCopyConstructible> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, TriviallyCopyConstructible>, hamon::unexpected<TriviallyCopyConstructible> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, ExplicitlyCopyConstructible>, hamon::unexpected<ExplicitlyCopyConstructible> const&>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, CopyConstructible>, hamon::unexpected<CopyConstructible> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, NonCopyConstructible>, hamon::unexpected<NonCopyConstructible> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, NothrowCopyConstructible>, hamon::unexpected<NothrowCopyConstructible> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, TriviallyCopyConstructible>, hamon::unexpected<TriviallyCopyConstructible> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, ExplicitlyCopyConstructible>, hamon::unexpected<ExplicitlyCopyConstructible> const&>::value, "");
#endif

static_assert( hamon::is_implicitly_constructible<hamon::expected<void, CopyConstructible>, hamon::unexpected<CopyConstructible> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, NonCopyConstructible>, hamon::unexpected<NonCopyConstructible> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<void, NothrowCopyConstructible>, hamon::unexpected<NothrowCopyConstructible> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<void, TriviallyCopyConstructible>, hamon::unexpected<TriviallyCopyConstructible> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, ExplicitlyCopyConstructible>, hamon::unexpected<ExplicitlyCopyConstructible> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct S1
{
	int value;
	constexpr S1(int v) : value(v) {}
};

struct S2
{
	int value;
	constexpr explicit S2(int v) : value(v) {}
};

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::unexpected<int> const src{5};
		hamon::expected<Void, int> dst = src;
		VERIFY(!dst.has_value());
		VERIFY(dst.error() == 5);
	}
	{
		hamon::unexpected<int> const src{10};
		hamon::expected<Void, double> dst = src;
		VERIFY(!dst.has_value());
		VERIFY(dst.error() == 10.0);
	}
	{
		hamon::unexpected<int> const src{20};
		hamon::expected<Void, S1> dst = src;
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 20);
	}
	{
		hamon::unexpected<int> const src{20};
		hamon::expected<Void, S2> dst{src};
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 20);
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
		hamon::unexpected<int> u{42};
		using Expected = hamon::expected<void, ThrowOnCtor>;
		EXPECT_THROW(Expected e{u}, ThrowOnCtor::Exception);
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedVoidTest, CtorUnexpectedCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile>()));

	exceptions_test();
}

}	// namespace ctor_unexpected_copy_test

}	// namespace hamon_expected_void_test
