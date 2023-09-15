/**
 *	@file	unit_test_optional_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	constexpr optional(const optional& rhs);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace ctor_copy_test
{

struct NonCopyable
{
	NonCopyable(NonCopyable const&) = delete;
	NonCopyable& operator=(NonCopyable const&) = delete;
};

struct Copyable
{
	Copyable(Copyable const&);
};

struct NothrowCopyable
{
	NothrowCopyable(NothrowCopyable const&) noexcept;
};

struct TriviallyCopyable
{
	TriviallyCopyable(TriviallyCopyable const&) = default;
};

static_assert(!hamon::is_copy_constructible<NonCopyable>::value, "");
static_assert( hamon::is_copy_constructible<Copyable>::value, "");
static_assert( hamon::is_copy_constructible<NothrowCopyable>::value, "");
static_assert( hamon::is_copy_constructible<TriviallyCopyable>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<NonCopyable>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<Copyable>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<NothrowCopyable>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<TriviallyCopyable>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<NonCopyable>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<Copyable>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<NothrowCopyable>::value, "");
static_assert( hamon::is_trivially_copy_constructible<TriviallyCopyable>::value, "");

static_assert( hamon::is_copy_constructible<hamon::optional<int>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::optional<Copyable>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::optional<NonCopyable>>::value, "");

// extension
#if !defined(HAMON_USE_STD_OPTIONAL)
static_assert( hamon::is_nothrow_copy_constructible<hamon::optional<int>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::optional<NothrowCopyable>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::optional<Copyable>>::value, "");
#endif

static_assert( hamon::is_trivially_copy_constructible<hamon::optional<int>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::optional<TriviallyCopyable>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::optional<NothrowCopyable>>::value, "");

GTEST_TEST(OptionalTest, CtorCopyTest)
{
	{
		hamon::optional<int> t1 = 3;
		hamon::optional<int> t2(t1);
		EXPECT_EQ(3, t2.value());
		EXPECT_EQ(3, *t2);
	}
	{
		hamon::optional<hamon::string> t1 = "Hello";
		hamon::optional<hamon::string> t2(t1);
		EXPECT_EQ("Hello", t2.value());
		EXPECT_EQ("Hello", *t2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> t1 = 3;
		HAMON_CXX11_CONSTEXPR hamon::optional<int> t2(t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, t2.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, *t2);
	}
}

}	// namespace ctor_copy_test

}	// namespace hamon_optional_test
