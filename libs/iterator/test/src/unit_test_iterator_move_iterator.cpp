/**
 *	@file	unit_test_iterator_move_iterator.cpp
 *
 *	@brief	move_iterator のテスト
 */

#include <hamon/iterator/move_iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace move_iterator_test
{

struct Base {};
struct Derived : Base {};

struct Movable
{
public:
	HAMON_CXX14_CONSTEXPR Movable(int v) : m_value(v){}
	HAMON_CXX14_CONSTEXPR Movable(Movable&& other) noexcept : m_value(other.m_value) { other.m_value = 0; }
	HAMON_CXX14_CONSTEXPR Movable& operator=(Movable&& other) noexcept { m_value = other.m_value; other.m_value = 0; return *this; }
	HAMON_CXX14_CONSTEXPR int value() const { return m_value; }
private:
	Movable(Movable const&) = delete;
	Movable& operator=(Movable const&) = delete;
	int	m_value;
};

GTEST_TEST(MoveIteratorTest, DefaultCtorTest)
{
	{
		hamon::move_iterator<char*> it;
		(void)it;
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::move_iterator<char*> it;
		(void)it;
	}
}

inline HAMON_CXX14_CONSTEXPR bool iter_ctor_test()
{
	char s[] = "123";
	hamon::move_iterator<char*> it(s);
	return it.base() == s;
}

GTEST_TEST(MoveIteratorTest, IterCtorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(iter_ctor_test());
}

inline HAMON_CXX14_CONSTEXPR bool convert_ctor_test()
{
	Derived d{};
	hamon::move_iterator<Derived*> const it1(&d);
	hamon::move_iterator<Base*> it2(it1);
	return it2.base() == &d;
}

GTEST_TEST(MoveIteratorTest, ConvertCtorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(convert_ctor_test());
}

inline HAMON_CXX14_CONSTEXPR bool assign_test()
{
	Derived d{};
	hamon::move_iterator<Derived*> const it1(&d);
	hamon::move_iterator<Base*> it2;
	hamon::move_iterator<Base*>& r = it2 = it1;
	return
		it2.base() == &d &&
		&r == &it2;
}

GTEST_TEST(MoveIteratorTest, AssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(assign_test());
}

template <int n>
inline HAMON_CXX14_CONSTEXPR bool op_star_test()
{
	Movable x(n);
	hamon::move_iterator<Movable*> p(&x);
	Movable y(*p);
	return
		0 == x.value() &&
		n == y.value();
}

GTEST_TEST(MoveIteratorTest, OpStarTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(op_star_test<43>());
}

inline HAMON_CXX14_CONSTEXPR bool op_index_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	hamon::move_iterator<Movable*> p(&a[1]);
	Movable y(*p);
	return
		1 == a[0].value() &&
		0 == a[1].value() &&
		3 == a[2].value() &&
		2 == y.value();
}

GTEST_TEST(MoveIteratorTest, OpIndexTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(op_index_test());
}

inline HAMON_CXX14_CONSTEXPR bool increment_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	hamon::move_iterator<Movable*> p(&a[0]);
	Movable y(*(p++));
	Movable z(*(++p));
	return
		0 == a[0].value() &&
		2 == a[1].value() &&
		0 == a[2].value() &&
		1 == y.value() &&
		3 == z.value() &&
		p.base() == &a[2];
}

GTEST_TEST(MoveIteratorTest, IncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(increment_test());
}

inline HAMON_CXX14_CONSTEXPR bool decrement_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	hamon::move_iterator<Movable*> p(&a[2]);
	Movable y(*(p--));
	Movable z(*(--p));
	return
		0 == a[0].value() &&
		2 == a[1].value() &&
		0 == a[2].value() &&
		3 == y.value() &&
		1 == z.value() &&
		p.base() == &a[0];
}

GTEST_TEST(MoveIteratorTest, DecrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(decrement_test());
}

inline HAMON_CXX14_CONSTEXPR bool add_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	hamon::move_iterator<Movable*> p(&a[0]);
	Movable y(*(p += 2));
	return
		1 == a[0].value() &&
		2 == a[1].value() &&
		0 == a[2].value() &&
		3 == y.value() &&
		p.base() == &a[2];
}

GTEST_TEST(MoveIteratorTest, AddTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(add_test());
}

inline HAMON_CXX14_CONSTEXPR bool sub_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	hamon::move_iterator<Movable*> p(&a[2]);
	Movable y(*(p -= 2));
	return
		0 == a[0].value() &&
		2 == a[1].value() &&
		3 == a[2].value() &&
		1 == y.value() &&
		p.base() == &a[0];
}

GTEST_TEST(MoveIteratorTest, SubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(sub_test());
}

inline HAMON_CXX14_CONSTEXPR bool plus_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	hamon::move_iterator<Movable*> p(&a[0]);
	Movable y(*(p + 1));
	Movable z(*(2 + p));
	return
		1 == a[0].value() &&
		0 == a[1].value() &&
		0 == a[2].value() &&
		2 == y.value() &&
		3 == z.value() &&
		p.base() == &a[0];
}

GTEST_TEST(MoveIteratorTest, PlusTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(plus_test());
}

inline HAMON_CXX14_CONSTEXPR bool minus_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	hamon::move_iterator<Movable*> p(&a[2]);
	Movable y(*(p - 1));
	Movable z(*(p - 2));
	return
		0 == a[0].value() &&
		0 == a[1].value() &&
		3 == a[2].value() &&
		2 == y.value() &&
		1 == z.value() &&
		p.base() == &a[2];
}

GTEST_TEST(MoveIteratorTest, MinusTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(minus_test());
}

inline HAMON_CXX14_CONSTEXPR bool distance_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	hamon::move_iterator<Movable*> it1(&a[0]);
	hamon::move_iterator<Movable*> it2(&a[1]);
	hamon::move_iterator<Movable*> it3(&a[2]);
	return
		((it1 - it1) ==  0) &&
		((it1 - it2) == -1) &&
		((it1 - it3) == -2) &&
		((it2 - it1) ==  1) &&
		((it2 - it2) ==  0) &&
		((it2 - it3) == -1) &&
		((it3 - it1) ==  2) &&
		((it3 - it2) ==  1) &&
		((it3 - it3) ==  0);
}

GTEST_TEST(MoveIteratorTest, DistanceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(distance_test());
}

inline HAMON_CXX14_CONSTEXPR bool compare_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	hamon::move_iterator<Movable*> it1(&a[0]);
	hamon::move_iterator<Movable*> it2(&a[1]);
	hamon::move_iterator<Movable*> it3(&a[2]);
	return
		((it2 == it1) == false) &&
		((it2 == it2) == true)  &&
		((it2 == it3) == false) &&
		((it2 != it1) == true)  &&
		((it2 != it2) == false) &&
		((it2 != it3) == true)  &&
		((it2 <  it1) == false) &&
		((it2 <  it2) == false) &&
		((it2 <  it3) == true)  &&
		((it2 >  it1) == true)  &&
		((it2 >  it2) == false) &&
		((it2 >  it3) == false) &&
		((it2 <= it1) == false) &&
		((it2 <= it2) == true)  &&
		((it2 <= it3) == true)  &&
		((it2 >= it1) == true)  &&
		((it2 >= it2) == true)  &&
		((it2 >= it3) == false);
}

GTEST_TEST(MoveIteratorTest, CompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(compare_test());
}

}	// namespace move_iterator_test

}	// namespace hamon_iterator_test
