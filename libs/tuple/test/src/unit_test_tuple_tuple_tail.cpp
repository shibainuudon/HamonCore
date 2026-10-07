/**
 *	@file	unit_test_tuple_tuple_tail.cpp
 *
 *	@brief	tuple_tail のテスト
 */

#include <hamon/tuple/tuple_tail.hpp>
#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <tuple>

namespace hamon_tuple_test
{

namespace tuple_tail_test
{

struct MoveOnly
{
	int val;

	constexpr MoveOnly(int v) : val(v) {}
	constexpr MoveOnly(MoveOnly&& rhs) : val(rhs.val) {}
	constexpr MoveOnly(MoveOnly const&) = delete;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename...> class Tuple>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		Tuple<> t1;
		auto t2 = hamon::tuple_tail(t1);
		static_assert(hamon::is_same_v<decltype(t2), Tuple<>>, "");
	}
	{
		Tuple<int> const t1(10);
		auto t2 = hamon::tuple_tail(t1);
		static_assert(hamon::is_same_v<decltype(t2), Tuple<>>, "");
	}
	{
		Tuple<int, float> t1(10, 2.5f);
		auto t2 = hamon::tuple_tail(t1);
		static_assert(hamon::is_same_v<decltype(t2), Tuple<float>>, "");
		VERIFY(hamon::adl_get<0>(t2) == 2.5f);
	}
	{
		int i = 42;
		float f = 1.5f;
		Tuple<char, int const&, float*> const t1(10, i, &f);
		auto t2 = hamon::tuple_tail(t1);
		static_assert(hamon::is_same_v<decltype(t2), Tuple<int const&, float*>>, "");
		VERIFY(hamon::adl_get<0>(t2) == i);
		VERIFY(hamon::adl_get<1>(t2) == &f);
	}
	{
		int i = 42;
		float f = 1.5f;
		const char* s = "test";
		Tuple<char, int const&, float&, const char*, MoveOnly> t1(10, i, f, s, MoveOnly{13});
		auto t2 = hamon::tuple_tail(hamon::move(t1));
		static_assert(hamon::is_same_v<decltype(t2), Tuple<int const&, float&, const char*, MoveOnly>>, "");
		VERIFY(hamon::adl_get<0>(t2) == i);
		VERIFY(hamon::adl_get<1>(t2) == f);
		VERIFY(hamon::adl_get<2>(t2) == s);
		VERIFY(hamon::adl_get<3>(t2).val == 13);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, TupleTailTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<std::tuple>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::tuple>());
}

}	// namespace tuple_tail_test

}	// namespace hamon_tuple_test
