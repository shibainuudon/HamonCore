/**
 *	@file	unit_test_tuple_tuple_assign_tuple_copy.cpp
 *
 *	@brief	tuple<UTypes...>からのコピー代入のテスト
 *
 *	template<class... UTypes> constexpr tuple& operator=(const tuple<UTypes...>& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_tuple_copy_test
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

static_assert( hamon::is_assignable<hamon::tuple<AssignableInt>&,  hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<AssignableInt>&,  hamon::tuple<long> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt>&,  hamon::tuple<int*> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt>&,  hamon::tuple<int, int> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int, int>&, hamon::tuple<short, int> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int, int>&, hamon::tuple<int,   short> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<int, int>&, hamon::tuple<short, short> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::tuple<int*,  int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::tuple<int,   int*> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::tuple<int*,  int*> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::tuple<short, int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<int, int>&, hamon::tuple<short> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<AssignableInt,  AssignableInt>&,  hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<CopyAssignable, AssignableInt>&,  hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt,  CopyAssignable>&, hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<CopyAssignable, CopyAssignable>&, hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt,  AssignableInt>&,  hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_assignable<hamon::tuple<AssignableInt,  AssignableInt>&,  hamon::tuple<int, int, int> const&>::value, "");
static_assert( hamon::is_assignable<hamon::tuple<AssignableInt, int, float>&, hamon::tuple<int, long, double> const&>::value, "");

static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt>&, hamon::tuple<int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt>&, hamon::tuple<int> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<int, int>&, hamon::tuple<short, int> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<int, int>&, hamon::tuple<int,   short> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<int, int>&, hamon::tuple<short, short> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, NothrowAssignableInt>&, hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        NothrowAssignableInt>&, hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, AssignableInt>&,        hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::tuple<AssignableInt,        AssignableInt>&,        hamon::tuple<int, int> const&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::tuple<NothrowAssignableInt, int, float>&, hamon::tuple<int, long, double> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		hamon::tuple<short, float> p1((short)1, 2.0f);
		hamon::tuple<int, double> const p2(3, 4);

		VERIFY(get<0>(p1) == 1);
		VERIFY(get<1>(p1) == 2);
		VERIFY(get<0>(p2) == 3);
		VERIFY(get<1>(p2) == 4);

		auto&& r = (p1 = p2);
		static_assert(hamon::is_same<decltype(r), hamon::tuple<short, float>&>::value, "");
		VERIFY(&r == &p1);

		VERIFY(get<0>(p1) == 3);
		VERIFY(get<1>(p1) == 4);
		VERIFY(get<0>(p2) == 3);
		VERIFY(get<1>(p2) == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, AssignTupleCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_tuple_copy_test

}	// namespace hamon_tuple_test
