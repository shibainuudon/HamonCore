/**
 *	@file	unit_test_tuple_tuple_assign_tuple_like_copy.cpp
 *
 *	@brief	tuple-likeなオブジェクトのコピー代入のテスト
 *
 *	template<tuple-like UTuple> constexpr tuple& operator=(UTuple&& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_tuple_like_copy_test
{

struct CopyAssignable
{
	CopyAssignable(CopyAssignable const&) = delete;
	CopyAssignable& operator=(CopyAssignable const&);
};

struct AssignableInt
{
	AssignableInt(AssignableInt const&) = delete;
	AssignableInt& operator=(AssignableInt const&) = delete;
	AssignableInt& operator=(int const&);
};

struct NothrowAssignableInt
{
	NothrowAssignableInt(NothrowAssignableInt const&) = delete;
	NothrowAssignableInt& operator=(NothrowAssignableInt const&) = delete;
	NothrowAssignableInt& operator=(int const&) noexcept;
};

static_assert( hamon::is_assignable<hamon::tuple<int>&,   hamon::array<int, 1> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<float>&, hamon::array<int, 1> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int>&,   hamon::array<int*, 1> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<short, float>&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<short, float>&, hamon::array<int, 1> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<short, float>&, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<short, float>&, hamon::array<int*, 2> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<AssignableInt,  AssignableInt>&,  hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<CopyAssignable, AssignableInt>&,  hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt,  CopyAssignable>&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<CopyAssignable, CopyAssignable>&, hamon::array<int, 2> const&>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::tuple<int>&,   hamon::array<int, 1> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<float>&, hamon::array<int, 1> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<short, float>&, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, NothrowAssignableInt>&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        NothrowAssignableInt>&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, AssignableInt>&,        hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        AssignableInt>&,        hamon::array<int, 2> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::tuple<short, float> t((short)1, 2.0f);

		VERIFY(hamon::adl_get<0>(t) == 1);
		VERIFY(hamon::adl_get<1>(t) == 2);

		hamon::array<int, 2> const a { 3, 4 };
		auto&& r = (t = a);
		static_assert(hamon::is_same<decltype(r), hamon::tuple<short, float>&>::value, "");
		VERIFY(&r == &t);

		VERIFY(hamon::adl_get<0>(t) == 3);
		VERIFY(hamon::adl_get<1>(t) == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, AssignTupleLikeCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_tuple_like_copy_test

}	// namespace hamon_tuple_test
