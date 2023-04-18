/**
 *	@file	unit_test_tuple_tuple_assign_tuple_like_copy_const.cpp
 *
 *	@brief	tuple-likeなオブジェクトのコピー代入(プロキシ参照版)のテスト
 *
 *	template<tuple-like UTuple> constexpr const tuple& operator=(UTuple&& u) const;
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_tuple_like_copy_const_test
{

struct AssignableInt
{
	AssignableInt(AssignableInt const&) = delete;
	AssignableInt& operator=(AssignableInt const&) = delete;
	AssignableInt& operator=(int const&) const;
};

struct NothrowAssignableInt
{
	NothrowAssignableInt(NothrowAssignableInt const&) = delete;
	NothrowAssignableInt& operator=(NothrowAssignableInt const&) = delete;
	NothrowAssignableInt& operator=(int const&) const noexcept;
};

static_assert(!hamon::is_assignable<hamon::tuple<int> const&,  hamon::array<int, 1> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int*> const&, hamon::array<int, 1> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int&> const&, hamon::array<int, 1> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int&, int&> const&, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int&, float&> const&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int&> const&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int&, int> const&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt> const&, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<AssignableInt, AssignableInt> const&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt, AssignableInt, AssignableInt> const&, hamon::array<int, 2> const&>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::tuple<int&, int&> const&, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, NothrowAssignableInt> const&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        NothrowAssignableInt> const&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, AssignableInt> const&,        hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        AssignableInt> const&,        hamon::array<int, 2> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		int i = 13;
		float f = 14;
		hamon::tuple<int&, float&> const t(i, f);

		VERIFY(get<0>(t) == 13);
		VERIFY(get<1>(t) == 14);
		VERIFY(i == 13);
		VERIFY(f == 14);

		hamon::array<int, 2> const a { 15, 16 };

		auto&& r = (t = a);
		static_assert(hamon::is_same<decltype(r), hamon::tuple<int&, float&> const&>::value, "");
		VERIFY(&r == &t);

		VERIFY(get<0>(t) == 15);
		VERIFY(get<1>(t) == 16);
		VERIFY(i == 15);
		VERIFY(f == 16);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, AssignTupleLikeCopyConstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_tuple_like_copy_const_test

}	// namespace hamon_tuple_test
