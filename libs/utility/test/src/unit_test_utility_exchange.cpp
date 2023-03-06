/**
 *	@file	unit_test_utility_exchange.cpp
 *
 *	@brief	exchange のテスト
 */

#include <hamon/utility/exchange.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_utility_test
{

namespace exchange_test
{

int f() { return 31; }

HAMON_CXX14_CONSTEXPR bool test_constexpr()
{
	int v = 12;

	if (12 != hamon::exchange(v, 23) || v != 23)
	{
		return false;
	}

	if (23 != hamon::exchange(v, static_cast<short>(67)) || v != 67)
	{
		return false;
	}

	if (67 != hamon::exchange<int, short>(v, {}) || v != 0)
	{
		return false;
	}

	return true;
}

template <bool Move, bool Assign>
struct TestNoexcept
{
	TestNoexcept() = default;
	TestNoexcept(const TestNoexcept&);
	TestNoexcept(TestNoexcept&&) noexcept(Move);
	TestNoexcept& operator=(const TestNoexcept&);
	TestNoexcept& operator=(TestNoexcept&&) noexcept(Assign);
};

void test_noexcept()
{
	{
		int x = 42;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::exchange(x, 42));
	}
	{
		TestNoexcept<true, true> x;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::exchange(x, hamon::move(x)));
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::exchange(x, x)); // copy-assignment is not noexcept
	}
	{
		TestNoexcept<true, false> x;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::exchange(x, hamon::move(x)));
	}
	{
		TestNoexcept<false, true> x;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::exchange(x, hamon::move(x)));
	}
}

GTEST_TEST(UtilityTest, ExchangeTest)
{
	{
		int n = 42;
		int t = hamon::exchange(n, 10);
		EXPECT_EQ(10, n);
		EXPECT_EQ(42, t);
		t = hamon::exchange(n, 20);
		EXPECT_EQ(20, n);
		EXPECT_EQ(10, t);
	}
	{
		std::vector<int> v;
		auto t = hamon::exchange(v, {1, 2, 3, 4});

		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_EQ(4, v[3]);
		EXPECT_EQ(0u, t.size());

		t = hamon::exchange(v, {10, 20, 30});
		EXPECT_EQ(4u, t.size());
		EXPECT_EQ(1, t[0]);
		EXPECT_EQ(2, t[1]);
		EXPECT_EQ(3, t[2]);
		EXPECT_EQ(4, t[3]);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0]);
		EXPECT_EQ(20, v[1]);
		EXPECT_EQ(30, v[2]);
	}
	{
		int (*fun)();
		hamon::exchange(fun, f);
		EXPECT_EQ(31, fun());
	}

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_constexpr());

	test_noexcept();
}

}	// namespace exchange_test

}	// namespace hamon_utility_test
