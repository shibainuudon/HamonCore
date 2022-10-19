/**
 *	@file	unit_test_functional_cref.cpp
 *
 *	@brief	cref のテスト
 */

#include <hamon/functional/cref.hpp>
#include <hamon/functional/reference_wrapper.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_functional_test
{

namespace cref_test
{

GTEST_TEST(CRefTest, TypeTest)
{
	int i = 0;
	auto r = hamon::cref(i);
	static_assert(std::is_same<decltype(r), hamon::reference_wrapper<int const>>::value, "");
}

struct F
{
	HAMON_CXX14_CONSTEXPR int operator()(int i, int j) { return i + j; }
	HAMON_CXX14_CONSTEXPR int operator()(int i, int j) const { return i * j; }
};

inline HAMON_CXX14_CONSTEXPR int
invoke_test01(int i, int j)
{
	F f{};
	return hamon::cref(f)(i, j);
}

inline HAMON_CXX14_CONSTEXPR int
invoke_test02(int i, int j)
{
	F f{};
	return hamon::cref(hamon::cref(f))(i, j);
}

GTEST_TEST(CRefTest, InvokeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test01(1, 2), 2);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test02(1, 2), 2);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test01(3, 4), 12);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test02(3, 4), 12);
}

}	// namespace cref_test

}	// namespace hamon_functional_test
