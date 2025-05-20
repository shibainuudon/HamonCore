/**
 *	@file	unit_test_unexpected_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	constexpr unexpected(const unexpected&) = default;
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
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

static_assert( hamon::is_copy_constructible<hamon::unexpected<int>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::unexpected<CopyConstructible>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::unexpected<NonCopyConstructible>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::unexpected<NothrowCopyConstructible>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::unexpected<TriviallyCopyConstructible>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::unexpected<ExplicitlyCopyConstructible>>::value, "");

static_assert( hamon::is_nothrow_copy_constructible<hamon::unexpected<int>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::unexpected<CopyConstructible>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::unexpected<NonCopyConstructible>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::unexpected<NothrowCopyConstructible>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::unexpected<TriviallyCopyConstructible>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::unexpected<ExplicitlyCopyConstructible>>::value, "");

static_assert( hamon::is_trivially_copy_constructible<hamon::unexpected<int>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::unexpected<CopyConstructible>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::unexpected<NonCopyConstructible>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::unexpected<NothrowCopyConstructible>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::unexpected<TriviallyCopyConstructible>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::unexpected<ExplicitlyCopyConstructible>>::value, "");

static_assert( hamon::is_implicitly_copy_constructible<hamon::unexpected<int>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::unexpected<CopyConstructible>>::value, "");
static_assert(!hamon::is_implicitly_copy_constructible<hamon::unexpected<NonCopyConstructible>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::unexpected<NothrowCopyConstructible>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::unexpected<TriviallyCopyConstructible>>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<hamon::unexpected<ExplicitlyCopyConstructible>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::unexpected<E> const src{E{5}};
	hamon::unexpected<E> dst = src;
	VERIFY(dst.error() == E{5});
	return true;
}

#undef VERIFY

GTEST_TEST(UnexpectedTest, CtorCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace ctor_copy_test

}	// namespace hamon_unexpected_test
