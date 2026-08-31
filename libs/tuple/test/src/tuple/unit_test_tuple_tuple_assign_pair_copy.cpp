/**
 *	@file	unit_test_tuple_tuple_assign_pair_copy.cpp
 *
 *	@brief	pair<U1, U2>からのコピー代入のテスト
 *
 *	template<class U1, class U2> constexpr tuple& operator=(const pair<U1, U2>& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_pair_copy_test
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

static_assert( hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<short, int> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<int,   short> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<short, short> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<int*,  int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<int,   int*> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::pair<int*,  int*> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<AssignableInt,  AssignableInt>&,  hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<CopyAssignable, AssignableInt>&,  hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt,  CopyAssignable>&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<CopyAssignable, CopyAssignable>&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int, long>&, hamon::pair<short, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int>&, hamon::pair<short, int> const&>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::tuple<int, int>&, hamon::pair<short, int> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<int, int>&, hamon::pair<int,   short> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<int, int>&, hamon::pair<short, short> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, NothrowAssignableInt>&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        NothrowAssignableInt>&, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, AssignableInt>&,        hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        AssignableInt>&,        hamon::pair<int, int> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::tuple<short, float> p1((short)1, 2.0f);
		hamon::pair<int, double> const p2(3, 4);

		VERIFY(hamon::adl_get<0>(p1) == 1);
		VERIFY(hamon::adl_get<1>(p1) == 2);
		VERIFY(hamon::adl_get<0>(p2) == 3);
		VERIFY(hamon::adl_get<1>(p2) == 4);

		auto&& r = (p1 = p2);
		static_assert(hamon::is_same<decltype(r), hamon::tuple<short, float>&>::value, "");
		VERIFY(&r == &p1);

		VERIFY(hamon::adl_get<0>(p1) == 3);
		VERIFY(hamon::adl_get<1>(p1) == 4);
		VERIFY(hamon::adl_get<0>(p2) == 3);
		VERIFY(hamon::adl_get<1>(p2) == 4);
	}

	return true;
}

HAMON_WARNING_POP()

#undef VERIFY

GTEST_TEST(TupleTest, AssignPairCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_pair_copy_test

}	// namespace hamon_tuple_test
