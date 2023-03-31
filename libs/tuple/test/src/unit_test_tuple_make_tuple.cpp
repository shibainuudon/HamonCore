/**
 *	@file	unit_test_tuple_make_tuple.cpp
 *
 *	@brief	make_tuple のテスト
 *
 *	template<class... TTypes>
 *	constexpr tuple<unwrap_ref_decay_t<TTypes>...>
 *	make_tuple(TTypes&&... t);
 */

#include <hamon/tuple.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace make_tuple_test
{

GTEST_TEST(TupleTest, MakeTupleTest)
{
	using std::get;
	{
		auto t = hamon::make_tuple();
		static_assert(hamon::is_same<decltype(t), hamon::tuple<>>::value, "");
		(void)t;
	}
	{
		int x = 3;
		std::string y = "hello";
		auto t = hamon::make_tuple(x, y);	// make_tupleは引数をコピーする
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int, std::string>>::value, "");
		EXPECT_TRUE(get<0>(t) == 3);
		EXPECT_TRUE(get<1>(t) == "hello");
		y = "world";
		EXPECT_TRUE(get<1>(t) == "hello");	// コピーなので変更されない
	}
	{
		int x = 3;
		std::string y = "hello";
		auto t = hamon::make_tuple(x, hamon::ref(y));	// ref, cref で明示的に参照にすることができる
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int, std::string&>>::value, "");
		EXPECT_TRUE(get<0>(t) == 3);
		EXPECT_TRUE(get<1>(t) == "hello");
		y = "world";
		EXPECT_TRUE(get<1>(t) == "world");	// 参照なので変更される
	}
	{
		auto t = hamon::make_tuple(1, 'a', 0.5f);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int, char, float>>::value, "");
		EXPECT_TRUE(get<0>(t) == 1);
		EXPECT_TRUE(get<1>(t) == 'a');
		EXPECT_TRUE(get<2>(t) == 0.5f);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_tuple();
		static_assert(hamon::is_same<decltype(t), hamon::tuple<> const>::value, "");
		(void)t;
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_tuple(1.5);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<double> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t) == 1.5);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_tuple(2, 3);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int, int> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t) == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_tuple(1, 'a', 0.5f);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int, char, float> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t) == 'a');
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<2>(t) == 0.5f);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_tuple(1,2,3,4,5,6,7,8,9,10);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int,int,int,int,int,int,int,int,int,int> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<2>(t) == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<3>(t) == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<4>(t) == 5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<5>(t) == 6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<6>(t) == 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<7>(t) == 8);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<8>(t) == 9);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<9>(t) == 10);
	}
}

}	// namespace make_tuple_test

}	// namespace hamon_tuple_test
