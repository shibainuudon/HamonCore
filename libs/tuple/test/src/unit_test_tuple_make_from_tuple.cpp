/**
 *	@file	unit_test_tuple_make_from_tuple.cpp
 *
 *	@brief	make_from_tuple のテスト
 *
 *	template<class T, tuple-like Tuple>
 *	constexpr T make_from_tuple(Tuple&& t);
 */

#include <hamon/tuple/make_from_tuple.hpp>
#include <hamon/tuple/make_tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace make_from_tuple_test
{

struct S1
{
	int i;
	float f;
	hamon::string s;

	S1(int x) : i(x), f(2.0f), s("hoge") {}
	S1(int x, float y) : i(x), f(y), s("fuga") {}
	S1(int x, float y, const char* z) : i(x), f(y), s(z) {}
};

struct S2
{
	hamon::size_t	arity;

	template <typename... Types>
	HAMON_CXX11_CONSTEXPR S2(Types&&...)
		: arity(sizeof...(Types)) {}
};

GTEST_TEST(TupleTest, MakeFromTupleTest)
{
	{
		auto t = hamon::make_tuple(42);
		auto s = hamon::make_from_tuple<S1>(t);
		EXPECT_EQ(42, s.i);
		EXPECT_EQ(2.0f, s.f);
		EXPECT_EQ("hoge", s.s);
	}
	{
		auto t = hamon::make_tuple(43, 0.5f);
		auto s = hamon::make_from_tuple<S1>(hamon::move(t));
		EXPECT_EQ(43, s.i);
		EXPECT_EQ(0.5f, s.f);
		EXPECT_EQ("fuga", s.s);
	}
	{
		auto t = hamon::make_pair(43, 0.5f);
		auto s = hamon::make_from_tuple<S1>(hamon::move(t));
		EXPECT_EQ(43, s.i);
		EXPECT_EQ(0.5f, s.f);
		EXPECT_EQ("fuga", s.s);
	}
	{
		auto const t = hamon::make_tuple(44, 1.5f, "hello");
		auto s = hamon::make_from_tuple<S1>(t);
		EXPECT_EQ(44, s.i);
		EXPECT_EQ(1.5f, s.f);
		EXPECT_EQ("hello", s.s);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_tuple();
		HAMON_CXX11_CONSTEXPR auto s = hamon::make_from_tuple<S2>(t);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, s.arity);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_tuple(42);
		HAMON_CXX11_CONSTEXPR auto s = hamon::make_from_tuple<S2>(hamon::move(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, s.arity);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_tuple(1.0, 2);
		HAMON_CXX11_CONSTEXPR auto s = hamon::make_from_tuple<S2>(t);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, s.arity);
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::make_pair(43, 0.5f);
		HAMON_CXX11_CONSTEXPR auto s = hamon::make_from_tuple<S2>(t);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, s.arity);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<double, 5> t {};
		HAMON_CXX11_CONSTEXPR auto s = hamon::make_from_tuple<S2>(t);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, s.arity);
	}
#if 0
	// ダングリング参照が発生するケース
	// reference_constructs_from_temporary が定義されている場合はコンパイルエラーになる。
	{
		auto s = hamon::make_from_tuple<hamon::string const&>(hamon::make_tuple("Hello"));
		(void)s;
	}
#endif
}

}	// namespace make_from_tuple_test

}	// namespace hamon_tuple_test
