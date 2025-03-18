/**
 *	@file	unit_test_chrono_month.cpp
 *
 *	@brief	month のテスト
 */

#include <hamon/chrono/month.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace month_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::chrono::month m{0};
	VERIFY(unsigned{m} == 0);
	VERIFY(!m.ok());

	{
		auto& t = ++m;
		VERIFY(&t == &m);
		VERIFY(unsigned{m} == 1);
		VERIFY(m.ok());
	}
	{
		auto t = m++;
		VERIFY(&t != &m);
		VERIFY(unsigned{t} == 1);
		VERIFY(unsigned{m} == 2);
		VERIFY(m.ok());
	}
	{
		auto& t = --m;
		VERIFY(&t == &m);
		VERIFY(unsigned{m} == 1);
		VERIFY(m.ok());
	}
	{
		auto t = m--;
		VERIFY(&t != &m);
		VERIFY(unsigned{t} == 1);
		VERIFY(unsigned{m} == 12);
		VERIFY(m.ok());
	}
	{
		auto& t = m += hamon::chrono::months{3};
		VERIFY(&t == &m);
		VERIFY(unsigned{m} == 3);
		VERIFY(m.ok());
	}
	{
		auto& t = m += hamon::chrono::months{11};
		VERIFY(&t == &m);
		VERIFY(unsigned{m} == 2);
		VERIFY(m.ok());
	}
	{
		auto& t = m -= hamon::chrono::months{2};
		VERIFY(&t == &m);
		VERIFY(unsigned{m} == 12);
		VERIFY(m.ok());
	}
	{
		auto& t = ++m;
		VERIFY(&t == &m);
		VERIFY(unsigned{m} == 1);
		VERIFY(m.ok());
	}
	{
		auto& t = --m;
		VERIFY(&t == &m);
		VERIFY(unsigned{m} == 12);
		VERIFY(m.ok());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ChronoTest, MonthTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

	{
		HAMON_CXX11_CONSTEXPR hamon::chrono::month m{12};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12u, unsigned{m});
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(m.ok());
	}

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::month{ 0}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::month{ 1}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::month{12}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::month{13}.ok());

	{
		HAMON_CXX11_CONSTEXPR hamon::chrono::month m1{3};
		HAMON_CXX11_CONSTEXPR hamon::chrono::month m2{3};
		HAMON_CXX11_CONSTEXPR hamon::chrono::month m3{4};
		HAMON_CXX11_CONSTEXPR hamon::chrono::month m4{2};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 <  m1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 <  m2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 <  m3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 <  m4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 >  m1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 >  m2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 >  m3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 >  m4);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 <= m1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 <= m2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 <= m3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 <= m4);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 >= m1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 >= m2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 >= m3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 >= m4);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(m1 <=> m1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(m1 <=> m2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(m1 <=> m3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(m1 <=> m4));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(m1 <=> m1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(m1 <=> m2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(m1 <=> m3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(m1 <=> m4));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(m1 <=> m1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(m1 <=> m2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(m1 <=> m3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(m1 <=> m4));
#endif
	}

	// month + months
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::month{0} + hamon::chrono::months{3} == hamon::chrono::month{3});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::month{1} + hamon::chrono::months{5} == hamon::chrono::month{6});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::month{5} + hamon::chrono::months{30} == hamon::chrono::month{11});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::January + hamon::chrono::months{2} == hamon::chrono::March);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::February + hamon::chrono::months{11} == hamon::chrono::January);

	// months + month
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{2} + hamon::chrono::month{4} == hamon::chrono::month{6});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{5} + hamon::chrono::month{4} == hamon::chrono::month{9});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{25} + hamon::chrono::month{9} == hamon::chrono::month{10});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{2} + hamon::chrono::January == hamon::chrono::March);

	// month - months
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::month{5} - hamon::chrono::months{1} == hamon::chrono::month{4});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::month{12} - hamon::chrono::months{2} == hamon::chrono::month{10});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::March - hamon::chrono::months{2} == hamon::chrono::January);

	// month - month
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::month{5} - hamon::chrono::month{1} == hamon::chrono::months{4});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::month{5} - hamon::chrono::month{10} == hamon::chrono::months{7});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::March - hamon::chrono::February == hamon::chrono::months{1});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::January - hamon::chrono::February == hamon::chrono::months{11});
}

}	// namespace month_test

}	// namespace hamon_chrono_test
