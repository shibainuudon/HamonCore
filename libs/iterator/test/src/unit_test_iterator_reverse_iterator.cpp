/**
 *	@file	unit_test_iterator_reverse_iterator.cpp
 *
 *	@brief	reverse_iterator のテスト
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/compare/is_lt.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace reverse_iterator_test
{

struct Base {};
struct Derived : Base {};

struct X
{
public:
	HAMON_CONSTEXPR X(int v) : m_v(v){}

	HAMON_CONSTEXPR int get() const { return m_v; }

private:
	int	m_v;
};

GTEST_TEST(ReverseIteratorTest, DefaultCtorTest)
{
	{
		HAMON_CONSTEXPR hamon::reverse_iterator<int*> it;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it.base() == nullptr);
	}
	{
		HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it.base() == nullptr);
	}
}

GTEST_TEST(ReverseIteratorTest, IterCtorTest)
{
	static HAMON_CONSTEXPR char const s[] = "123";
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it(s);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it.base() == s);
}

GTEST_TEST(ReverseIteratorTest, ConvertCtorTest)
{
	static HAMON_CONSTEXPR Derived const d{};
	HAMON_CONSTEXPR hamon::reverse_iterator<Derived const*> const it1(&d);
	HAMON_CONSTEXPR hamon::reverse_iterator<Base const*> const it2(it1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it2.base() == &d);
}

inline HAMON_CXX14_CONSTEXPR bool assign_test()
{
	Derived d{};
	hamon::reverse_iterator<Derived*> const it1(&d);
	hamon::reverse_iterator<Base*> it2;
	hamon::reverse_iterator<Base*>& r = it2 = it1;
	return
		it2.base() == &d &&
		&r == &it2;
}

GTEST_TEST(ReverseIteratorTest, AssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(assign_test());
}

GTEST_TEST(ReverseIteratorTest, OpStarTest)
{
	static HAMON_CONSTEXPR char const s[] = "123456789";
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it1(s+1);
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it2(s+2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it1 == s[0]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it2 == s[1]);
}

GTEST_TEST(ReverseIteratorTest, OpArrowTest)
{
	static HAMON_CONSTEXPR X const a[] = {1,2,3,4,5,6,7,8,9};
	HAMON_CONSTEXPR hamon::reverse_iterator<X const*> it1(a+1);
	HAMON_CONSTEXPR hamon::reverse_iterator<X const*> it2(a+2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it1->get() == a[0].get());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it2->get() == a[1].get());
}

GTEST_TEST(ReverseIteratorTest, OpIndexTest)
{
	static HAMON_CONSTEXPR char const s[] = "123456789";
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it1(s+5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it1[0] == s[4]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it1[1] == s[3]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it1[2] == s[2]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it1[3] == s[1]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it1[4] == s[0]);
}

inline HAMON_CXX14_CONSTEXPR bool increment_test()
{
	char const* p = "123456789";
	hamon::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = it++;
	auto it3 = it;
	auto it4 = ++it;
	return
		*it1 == p[4] &&
		*it2 == p[4] &&
		*it3 == p[3] &&
		*it4 == p[2] &&
		*it  == p[2];
}

GTEST_TEST(ReverseIteratorTest, IncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(increment_test());
}

inline HAMON_CXX14_CONSTEXPR bool decrement_test()
{
	char const* p = "123456789";
	hamon::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = it--;
	auto it3 = it;
	auto it4 = --it;
	return
		*it1 == p[4] &&
		*it2 == p[4] &&
		*it3 == p[5] &&
		*it4 == p[6] &&
		*it  == p[6];
}

GTEST_TEST(ReverseIteratorTest, DecrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(decrement_test());
}

inline HAMON_CXX14_CONSTEXPR bool add_test()
{
	char const* p = "123456789";
	hamon::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = (it += 1);
	auto it3 = it;
	auto it4 = (it += 2);
	return
		*it1 == p[4] &&
		*it2 == p[3] &&
		*it3 == p[3] &&
		*it4 == p[1] &&
		*it  == p[1];
}

GTEST_TEST(ReverseIteratorTest, AddTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(add_test());
}

inline HAMON_CXX14_CONSTEXPR bool sub_test()
{
	char const* p = "123456789";
	hamon::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = (it -= 1);
	auto it3 = it;
	auto it4 = (it -= 2);
	return
		*it1 == p[4] &&
		*it2 == p[5] &&
		*it3 == p[5] &&
		*it4 == p[7] &&
		*it  == p[7];
}

GTEST_TEST(ReverseIteratorTest, SubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(sub_test());
}

GTEST_TEST(ReverseIteratorTest, PlusTest)
{
	static HAMON_CONSTEXPR char const s[] = "123456789";
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it(s+5);
	HAMON_CONSTEXPR auto it1 = it;
	HAMON_CONSTEXPR auto it2 = (it + 1);
	HAMON_CONSTEXPR auto it3 = (2 + it);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it1 == s[4]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it2 == s[3]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it3 == s[2]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it  == s[4]);
}

GTEST_TEST(ReverseIteratorTest, MinusTest)
{
	static HAMON_CONSTEXPR char const s[] = "123456789";
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it(s+5);
	HAMON_CONSTEXPR auto it1 = it;
	HAMON_CONSTEXPR auto it2 = (it - 1);
	HAMON_CONSTEXPR auto it3 = (it - 2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it1 == s[4]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it2 == s[5]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it3 == s[6]);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*it  == s[4]);
}

GTEST_TEST(ReverseIteratorTest, DistanceTest)
{
	static HAMON_CONSTEXPR char const s[] = "123456789";
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it1(s+1);
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it2(s+2);
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it3(s+3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it1 - it1) ==  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it1 - it2) ==  1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it1 - it3) ==  2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 - it1) == -1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 - it2) ==  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 - it3) ==  1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it3 - it1) == -2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it3 - it2) == -1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it3 - it3) ==  0);
}

GTEST_TEST(ReverseIteratorTest, CompareTest)
{
	static HAMON_CONSTEXPR char const s[] = "123456789";
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it1(s+1);
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it2(s+2);
	HAMON_CONSTEXPR hamon::reverse_iterator<char const*> it3(s+3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 == it1) == false);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 == it2) == true) ;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 == it3) == false);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 != it1) == true) ;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 != it2) == false);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 != it3) == true) ;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 <  it1) == true) ;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 <  it2) == false);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 <  it3) == false);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 >  it1) == false);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 >  it2) == false);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 >  it3) == true) ;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 <= it1) == true) ;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 <= it2) == true) ;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 <= it3) == false);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 >= it1) == false);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 >= it2) == true) ;
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((it2 >= it3) == true) ;

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON) && defined(HAMON_HAS_STD_COMPARE)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(it2 <=> it1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(it2 <=> it2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(it2 <=> it3));
#endif
}

}	// namespace reverse_iterator_test

}	// namespace hamon_iterator_test
