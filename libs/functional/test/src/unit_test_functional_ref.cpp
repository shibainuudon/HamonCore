/**
 *	@file	unit_test_functional_ref.cpp
 *
 *	@brief	ref のテスト
 */

#include <hamon/functional/ref.hpp>
#include <hamon/functional/reference_wrapper.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_functional_test
{

namespace ref_test
{

GTEST_TEST(RefTest, TypeTest)
{
	int i = 0;
	auto r = hamon::ref(i);
	static_assert(std::is_same<decltype(r), hamon::reference_wrapper<int>>::value, "");
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
	return hamon::ref(f)(i, j);
}

inline HAMON_CXX14_CONSTEXPR int
invoke_test02(int i, int j)
{
	F f{};
	return hamon::ref(hamon::ref(f))(i, j);
}

GTEST_TEST(RefTest, InvokeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test01(1, 2), 3);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test02(1, 2), 3);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test01(3, 4), 7);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(invoke_test02(3, 4), 7);
}

}	// namespace ref_test

}	// namespace hamon_functional_test
