/**
 *	@file	unit_test_pair_assign_pair_like_move_const.cpp
 *
 *	@brief	pair-likeなオブジェクトからのムーブ代入(プロキシ参照版)のテスト
 * 
 *	template<pair-like P>
 *	constexpr const pair& operator=(P&& p) const;
 */

#include <hamon/pair.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace assign_pair_like_move_const_test
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

static_assert(!hamon::is_assignable<hamon::pair<int&, int&> const&, hamon::array<int, 1>>::value, "");
static_assert( hamon::is_assignable<hamon::pair<int&, int&> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int&, int&> const&, hamon::array<int, 3>>::value, "");
static_assert( hamon::is_assignable<hamon::pair<int&, float&> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int, int&> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<int&, int> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<AssignableInt, AssignableInt> const&, hamon::array<int, 1>>::value, "");
static_assert( hamon::is_assignable<hamon::pair<AssignableInt, AssignableInt> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<AssignableInt, AssignableInt> const&, hamon::array<int, 3>>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::pair<int&, int&> const&, hamon::array<int, 2>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<float&, long&> const&, hamon::array<int, 2>>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<NothrowAssignableInt, NothrowAssignableInt> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<AssignableInt,        NothrowAssignableInt> const&, hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<NothrowAssignableInt, AssignableInt> const&,        hamon::array<int, 2>>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<AssignableInt,        AssignableInt> const&,        hamon::array<int, 2>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		int i = 13;
		float f = 14;
		hamon::pair<int&, float&> const p(i, f);

		VERIFY(hamon::adl_get<0>(p) == 13);
		VERIFY(hamon::adl_get<1>(p) == 14);
		VERIFY(i == 13);
		VERIFY(f == 14);

		hamon::array<int, 2> a { 15, 16 };

		auto&& r = (p = hamon::move(a));
		static_assert(hamon::is_same<decltype(r), hamon::pair<int&, float&> const&>::value, "");
		VERIFY(&r == &p);

		VERIFY(hamon::adl_get<0>(p) == 15);
		VERIFY(hamon::adl_get<1>(p) == 16);
		VERIFY(i == 15);
		VERIFY(f == 16);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, AssignPairLikemoveConstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_pair_like_move_const_test

}	// namespace hamon_pair_test
