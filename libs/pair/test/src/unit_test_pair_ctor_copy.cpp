/**
 *	@file	unit_test_pair_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 * 
 *	pair(const pair&) = default;
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
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

static_assert( hamon::is_copy_constructible<hamon::pair<int,      int>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::pair<Copyable, int>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::pair<int,      Copyable>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::pair<Copyable, Copyable>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::pair<NonCopyable, int>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::pair<int,         NonCopyable>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::pair<NonCopyable, NonCopyable>>::value, "");

static_assert( hamon::is_nothrow_copy_constructible<hamon::pair<int,      int>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::pair<NothrowCopyable, int>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::pair<int,             NothrowCopyable>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::pair<NothrowCopyable, NothrowCopyable>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::pair<Copyable, int>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::pair<int,      Copyable>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::pair<Copyable, Copyable>>::value, "");

static_assert( hamon::is_trivially_copy_constructible<hamon::pair<int,      int>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::pair<TriviallyCopyable, int>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::pair<int,               TriviallyCopyable>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::pair<TriviallyCopyable, TriviallyCopyable>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::pair<NothrowCopyable, int>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::pair<int,             NothrowCopyable>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::pair<NothrowCopyable, NothrowCopyable>>::value, "");

GTEST_TEST(PairTest, CtorCopyTest)
{
	{
		hamon::pair<int, double> p1(1, 2);
		hamon::pair<int, double> p2(p1);
		EXPECT_EQ(1, p2.first);
		EXPECT_EQ(2, p2.second);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, double> p1(1, 2);
		HAMON_CXX11_CONSTEXPR hamon::pair<int, double> p2(p1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p2.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p2.second);
	}
}

}	// namespace ctor_copy_test

}	// namespace hamon_pair_test
