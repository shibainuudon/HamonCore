/**
 *	@file	unit_test_array_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_array_test
{

namespace ctor_default_test
{

struct Empty {};

struct Trivial { int i; int j; };

struct NonTrivial
{
	int i;
	int j;
	HAMON_CXX11_CONSTEXPR NonTrivial()
		: i(42), j(13) {}
};

template <typename T>
void CtorDefaultTest()
{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wmaybe-uninitialized")

	// {} を省略すると、constexprにできない
	{
		hamon::array<T, 0> a;
		EXPECT_EQ(0u, a.size());
		EXPECT_EQ(0u, a.max_size());
		EXPECT_EQ(true, a.empty());
	}
	{
		hamon::array<T, 1> a;
		EXPECT_EQ(1u, a.size());
		EXPECT_EQ(1u, a.max_size());
		EXPECT_EQ(false, a.empty());
	}
	{
		hamon::array<T, 2> a;
		EXPECT_EQ(2u, a.size());
		EXPECT_EQ(2u, a.max_size());
		EXPECT_EQ(false, a.empty());
	}
	{
		hamon::array<T, 3> a;
		EXPECT_EQ(3u, a.size());
		EXPECT_EQ(3u, a.max_size());
		EXPECT_EQ(false, a.empty());
	}

HAMON_WARNING_POP()

	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 0> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, a.max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true, a.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 1> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, a.max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 2> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, a.max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
	}
}

GTEST_TEST(ArrayTest, CtorDefaultTest)
{
	CtorDefaultTest<char>();
	CtorDefaultTest<int>();
	CtorDefaultTest<float>();
	CtorDefaultTest<double>();
	CtorDefaultTest<Empty>();
	CtorDefaultTest<Trivial>();
	CtorDefaultTest<NonTrivial>();
}

}	// namespace ctor_default_test

}	// namespace hamon_array_test
