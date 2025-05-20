/**
 *	@file	unit_test_expected_ctor_unexpected_copy.cpp
 *
 *	@brief	unexpected const& からのコンストラクタのテスト
 *
 *	template<class G>
 *	constexpr explicit(see below) expected(const unexpected<G>&);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
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

static_assert( hamon::is_constructible<hamon::expected<int, int>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, CopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, NonCopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, NothrowCopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, TriviallyCopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, ExplicitlyCopyConstructible>, hamon::unexpected<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<CopyConstructible, int>, hamon::unexpected<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<NonCopyConstructible, int>, hamon::unexpected<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<NothrowCopyConstructible, int>, hamon::unexpected<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<TriviallyCopyConstructible, int>, hamon::unexpected<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<ExplicitlyCopyConstructible, int>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<CtorFromInt, ConvertibleToInt>, hamon::unexpected<int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<ConvertibleToInt, CtorFromInt>, hamon::unexpected<int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, int>, hamon::unexpected<CtorFromInt> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, int>, hamon::unexpected<ConvertibleToInt> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, CopyConstructible>, hamon::unexpected<CopyConstructible> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<int, NonCopyConstructible>, hamon::unexpected<NonCopyConstructible> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, NothrowCopyConstructible>, hamon::unexpected<NothrowCopyConstructible> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, TriviallyCopyConstructible>, hamon::unexpected<TriviallyCopyConstructible> const&>::value, "");
static_assert( hamon::is_constructible<hamon::expected<int, ExplicitlyCopyConstructible>, hamon::unexpected<ExplicitlyCopyConstructible> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<CopyConstructible, int>, hamon::unexpected<CopyConstructible> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<NonCopyConstructible, int>, hamon::unexpected<NonCopyConstructible> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<NothrowCopyConstructible, int>, hamon::unexpected<NothrowCopyConstructible> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<TriviallyCopyConstructible, int>, hamon::unexpected<TriviallyCopyConstructible> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<ExplicitlyCopyConstructible, int>, hamon::unexpected<ExplicitlyCopyConstructible> const&>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, CopyConstructible>, hamon::unexpected<CopyConstructible> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, NonCopyConstructible>, hamon::unexpected<NonCopyConstructible> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, NothrowCopyConstructible>, hamon::unexpected<NothrowCopyConstructible> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<int, TriviallyCopyConstructible>, hamon::unexpected<TriviallyCopyConstructible> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<int, ExplicitlyCopyConstructible>, hamon::unexpected<ExplicitlyCopyConstructible> const&>::value, "");
#endif

static_assert( hamon::is_implicitly_constructible<hamon::expected<int, CopyConstructible>, hamon::unexpected<CopyConstructible> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, NonCopyConstructible>, hamon::unexpected<NonCopyConstructible> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<int, NothrowCopyConstructible>, hamon::unexpected<NothrowCopyConstructible> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::expected<int, TriviallyCopyConstructible>, hamon::unexpected<TriviallyCopyConstructible> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<int, ExplicitlyCopyConstructible>, hamon::unexpected<ExplicitlyCopyConstructible> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		hamon::unexpected<E> const src{E{10}};
		hamon::expected<T, E> dst = src;
		VERIFY(!dst.has_value());
		VERIFY(dst.error() == E{10});
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	using IntPair  = hamon::pair<int, int>;
	using IntTuple = hamon::tuple<int, int>;
	{
		hamon::unexpected<IntPair> src{hamon::in_place, 1, 2};
		hamon::expected<int, IntTuple> dst = src;
		VERIFY(!dst.has_value());
		VERIFY((dst.error() == IntTuple{1, 2}));
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test3()
{
	{
		hamon::unexpected<hamon::string> const src{"error"};
		hamon::expected<int, hamon::string> dst = src;
		VERIFY(!dst.has_value());
		VERIFY(dst.error() == "error");
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

HAMON_CXX14_CONSTEXPR bool test4()
{
	{
		hamon::unexpected<int> src{13};
		hamon::expected<S1, S1> dst = src;
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 13);
	}
	{
		hamon::unexpected<int> src{13};
		hamon::expected<S1, S2> dst{src};
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 13);
	}
	{
		hamon::unexpected<int> src{13};
		hamon::expected<S2, S1> dst = src;
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 13);
	}
	{
		hamon::unexpected<int> src{13};
		hamon::expected<S2, S2> dst{src};
		VERIFY(!dst.has_value());
		VERIFY(dst.error().value == 13);
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
		using Expected = hamon::expected<int, ThrowOnCtor>;
		EXPECT_THROW(Expected e{u}, ThrowOnCtor::Exception);
	}
	{
		hamon::unexpected<int> u{42};
		using Expected = hamon::expected<ThrowOnCtor, int>;
		EXPECT_NO_THROW(Expected e{u});
	}
HAMON_WARNING_POP()

#endif
}

GTEST_TEST(ExpectedTest, CtorUnexpectedCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test4()));

	exceptions_test();
}

}	// namespace ctor_unexpected_copy_test

}	// namespace hamon_expected_test
