/**
 *	@file	unit_test_pair_assign_pair_like_copy.cpp
 *
 *	@brief	pair-likeなオブジェクトからのコピー代入のテスト
 * 
 *	template<pair-like P>
 *	constexpr pair& operator=(P&& p);
 */

#include <hamon/pair.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace assign_pair_like_copy_test
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

static_assert(!hamon::is_assignable<hamon::pair<short, float>&, hamon::array<int, 1> const&>::value, "");
static_assert( hamon::is_assignable<hamon::pair<short, float>&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<short, float>&, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<short, float>&, hamon::array<int*, 2> const&>::value, "");
static_assert( hamon::is_assignable<hamon::pair<AssignableInt,  AssignableInt>&,  hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<CopyAssignable, AssignableInt>&,  hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<AssignableInt,  CopyAssignable>&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::pair<CopyAssignable, CopyAssignable>&, hamon::array<int, 2> const&>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::pair<int, int>&,   hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<float, long>&, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::pair<NothrowAssignableInt, NothrowAssignableInt>&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<AssignableInt,        NothrowAssignableInt>&, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<NothrowAssignableInt, AssignableInt>&,        hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::pair<AssignableInt,        AssignableInt>&,        hamon::array<int, 2> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::pair<short, float> p((short)1, 2.0f);

		VERIFY(hamon::adl_get<0>(p) == 1);
		VERIFY(hamon::adl_get<1>(p) == 2);

		hamon::array<int, 2> const a { 3, 4 };
		auto&& r = (p = a);
		static_assert(hamon::is_same<decltype(r), hamon::pair<short, float>&>::value, "");
		VERIFY(&r == &p);

		VERIFY(hamon::adl_get<0>(p) == 3);
		VERIFY(hamon::adl_get<1>(p) == 4);
	}

	return true;
}

HAMON_WARNING_POP()

#undef VERIFY

GTEST_TEST(PairTest, AssignPairLikeCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_pair_like_copy_test

}	// namespace hamon_pair_test
