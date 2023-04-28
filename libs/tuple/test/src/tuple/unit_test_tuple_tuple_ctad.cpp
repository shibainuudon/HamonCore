/**
 *	@file	unit_test_tuple_tuple_ctad.cpp
 *
 *	@brief	Deduction Guide のテスト
 *
 *	template<class... UTypes>
 *	tuple(UTypes...) -> tuple<UTypes...>;
 *	template<class T1, class T2>
 *	tuple(pair<T1, T2>) -> tuple<T1, T2>;
 *	template<class Alloc, class... UTypes>
 *	tuple(allocator_arg_t, Alloc, UTypes...) -> tuple<UTypes...>;
 *	template<class Alloc, class T1, class T2>
 *	tuple(allocator_arg_t, Alloc, pair<T1, T2>) -> tuple<T1, T2>;
 *	template<class Alloc, class... UTypes>
 *	tuple(allocator_arg_t, Alloc, tuple<UTypes...>) -> tuple<UTypes...>;
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

namespace ctad_test
{

struct MyAlloc {};

GTEST_TEST(TupleTest, CTADTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES) && !defined(HAMON_MSVC)
	{
		hamon::tuple t{};
		static_assert(hamon::is_same<decltype(t), hamon::tuple<>>::value, "");
		(void)t;
	}
	{
		hamon::tuple t{10};
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int>>::value, "");
		EXPECT_TRUE(hamon::adl_get<0>(t) == 10);
	}
	{
		hamon::tuple t = hamon::pair{0.5, 20};
		static_assert(hamon::is_same<decltype(t), hamon::tuple<double, int>>::value, "");
		EXPECT_TRUE(hamon::adl_get<0>(t) == 0.5);
		EXPECT_TRUE(hamon::adl_get<1>(t) == 20);
	}
	MyAlloc a{};
	{
		hamon::tuple t(hamon::allocator_arg, a);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<>>::value, "");
		(void)t;
	}
	{
		hamon::tuple t(hamon::allocator_arg, a, 1.5f);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<float>>::value, "");
		EXPECT_TRUE(hamon::adl_get<0>(t) == 1.5f);
	}
	{
		hamon::tuple t(hamon::allocator_arg, a, 3, 4L);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int, long>>::value, "");
		EXPECT_TRUE(hamon::adl_get<0>(t) == 3);
		EXPECT_TRUE(hamon::adl_get<1>(t) == 4);
	}
	{
		hamon::tuple t(hamon::allocator_arg, a, hamon::pair{0.5, 20});
		static_assert(hamon::is_same<decltype(t), hamon::tuple<double, int>>::value, "");
		EXPECT_TRUE(hamon::adl_get<0>(t) == 0.5);
		EXPECT_TRUE(hamon::adl_get<1>(t) == 20);
	}
	{
		hamon::tuple t(hamon::allocator_arg, a, hamon::tuple<>{});
		static_assert(hamon::is_same<decltype(t), hamon::tuple<>>::value, "");
		(void)t;
	}
	{
		hamon::tuple t(hamon::allocator_arg, a, hamon::tuple{42});
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int>>::value, "");
		EXPECT_TRUE(hamon::adl_get<0>(t) == 42);
	}
	{
		hamon::tuple t(hamon::allocator_arg, a, hamon::tuple{1, 2.5f});
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int, float>>::value, "");
		EXPECT_TRUE(hamon::adl_get<0>(t) == 1);
		EXPECT_TRUE(hamon::adl_get<1>(t) == 2.5f);
	}
#endif
}

}	// namespace ctad_test

}	// namespace hamon_tuple_test
