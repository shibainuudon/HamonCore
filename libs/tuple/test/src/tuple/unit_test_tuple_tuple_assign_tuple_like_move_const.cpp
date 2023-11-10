/**
 *	@file	unit_test_tuple_tuple_assign_tuple_like_move_const.cpp
 *
 *	@brief	tuple-likeなオブジェクトのムーブ代入(プロキシ参照版)のテスト
 *
 *	template<tuple-like UTuple> constexpr const tuple& operator=(UTuple&& u) const;
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_tuple_like_move_const_test
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

static_assert(!hamon::is_assignable<hamon::tuple<int> const&,  hamon::array<int, 1>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int*> const&, hamon::array<int, 1>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int&> const&, hamon::array<int, 1>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int&, int&> const&, hamon::array<int, 2>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int&, float&> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int&> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int&, int> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt> const&, hamon::array<int, 2>>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<AssignableInt, AssignableInt> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt, AssignableInt, AssignableInt> const&, hamon::array<int, 2>>::value, "");

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_assignable<hamon::tuple<int&, int&> const&, hamon::array<int, 2>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, NothrowAssignableInt> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        NothrowAssignableInt> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, AssignableInt> const&,        hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        AssignableInt> const&,        hamon::array<int, 2>>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		int i = 13;
		float f = 14;
		hamon::tuple<int&, float&> const t(i, f);

		VERIFY(hamon::adl_get<0>(t) == 13);
		VERIFY(hamon::adl_get<1>(t) == 14);
		VERIFY(i == 13);
		VERIFY(f == 14);

		hamon::array<int, 2> a { 15, 16 };

		auto&& r = (t = hamon::move(a));
		static_assert(hamon::is_same<decltype(r), hamon::tuple<int&, float&> const&>::value, "");
		VERIFY(&r == &t);

		VERIFY(hamon::adl_get<0>(t) == 15);
		VERIFY(hamon::adl_get<1>(t) == 16);
		VERIFY(i == 15);
		VERIFY(f == 16);
	}

	return true;
}

HAMON_WARNING_POP()

#undef VERIFY

GTEST_TEST(TupleTest, AssignTupleLikeMoveConstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_tuple_like_move_const_test

}	// namespace hamon_tuple_test
