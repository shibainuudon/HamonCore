/**
 *	@file	unit_test_tuple_tuple_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	tuple(const tuple& u) = default;
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
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

static_assert( hamon::is_copy_constructible<hamon::tuple<int,      int>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::tuple<Copyable, int>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::tuple<int,      Copyable>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::tuple<Copyable, Copyable>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::tuple<NonCopyable, int>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::tuple<int,         NonCopyable>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::tuple<NonCopyable, NonCopyable>>::value, "");

static_assert( hamon::is_nothrow_copy_constructible<hamon::tuple<int,      int>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::tuple<NothrowCopyable, int>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::tuple<int,             NothrowCopyable>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::tuple<NothrowCopyable, NothrowCopyable>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::tuple<Copyable, int>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::tuple<int,      Copyable>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::tuple<Copyable, Copyable>>::value, "");

static_assert( hamon::is_trivially_copy_constructible<hamon::tuple<int,      int>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::tuple<TriviallyCopyable, int>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::tuple<int,               TriviallyCopyable>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::tuple<TriviallyCopyable, TriviallyCopyable>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::tuple<NothrowCopyable, int>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::tuple<int,             NothrowCopyable>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::tuple<NothrowCopyable, NothrowCopyable>>::value, "");

GTEST_TEST(TupleTest, CtorCopyTest)
{
	using std::get;
	{
		hamon::tuple<int, double> t1(1, 2);
		hamon::tuple<int, double> t2(t1);
		EXPECT_EQ(1, get<0>(t2));
		EXPECT_EQ(2, get<1>(t2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, double> t1(1, 2);
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, double> t2(t1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, get<0>(t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, get<1>(t2));
	}
}

}	// namespace ctor_copy_test

}	// namespace hamon_tuple_test
