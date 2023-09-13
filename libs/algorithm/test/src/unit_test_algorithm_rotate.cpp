/**
 *	@file	unit_test_algorithm_rotate.cpp
 *
 *	@brief	rotate のテスト
 */

#include <hamon/algorithm/rotate.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include <forward_list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace rotate_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

class Foo
{
public:
	Foo(int value) : m_value(value) {}
	Foo(Foo&& other) noexcept : m_value(hamon::move(other.m_value)) {}
	Foo& operator=(Foo&& other) noexcept { m_value = hamon::move(other.m_value); return *this; }
	int get() const { return m_value; }
private:
	int	m_value;
};

inline HAMON_CXX14_CONSTEXPR bool RotateTest1()
{
	{
		int a[] { 1,2,3 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 0), hamon::end(a));
		VERIFY(ret == hamon::next(hamon::begin(a), 3));
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RotateTest2()
{
	{
		int a[] { 1,2,3 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 1), hamon::end(a));
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
		VERIFY(2 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(1 == a[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RotateTest3()
{
	{
		int a[] { 1,2,3 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 2), hamon::end(a));
		VERIFY(ret == hamon::next(hamon::begin(a), 1));
		VERIFY(3 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RotateTest4()
{
	{
		int a[] { 1,2,3 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 3), hamon::end(a));
		VERIFY(ret == hamon::next(hamon::begin(a), 0));
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RotateTest5()
{
	{
		int a[] { 42 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 0), hamon::end(a));
		VERIFY(ret == hamon::next(hamon::begin(a), 1));
		VERIFY(42 == a[0]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RotateTest6()
{
	{
		hamon::array<int, 4> a {{ 1,2,3,4 }};
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 2), hamon::end(a));
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
		VERIFY(3 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(1 == a[2]);
		VERIFY(2 == a[3]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RotateTest7()
{
	{
		hamon::array<int, 4> a {{ 1,2,3,4 }};
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 4), hamon::end(a));
		VERIFY(ret == hamon::next(hamon::begin(a), 0));
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(4 == a[3]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, RotateTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateTest4());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateTest5());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateTest6());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateTest7());

	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 0), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 4));
		EXPECT_EQ(1, a[0].get());
		EXPECT_EQ(2, a[1].get());
		EXPECT_EQ(3, a[2].get());
		EXPECT_EQ(4, a[3].get());
	}
	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 1), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
		EXPECT_EQ(2, a[0].get());
		EXPECT_EQ(3, a[1].get());
		EXPECT_EQ(4, a[2].get());
		EXPECT_EQ(1, a[3].get());
	}
	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 2), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		EXPECT_EQ(3, a[0].get());
		EXPECT_EQ(4, a[1].get());
		EXPECT_EQ(1, a[2].get());
		EXPECT_EQ(2, a[3].get());
	}
	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 3), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
		EXPECT_EQ(4, a[0].get());
		EXPECT_EQ(1, a[1].get());
		EXPECT_EQ(2, a[2].get());
		EXPECT_EQ(3, a[3].get());
	}
	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 4), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
		EXPECT_EQ(1, a[0].get());
		EXPECT_EQ(2, a[1].get());
		EXPECT_EQ(3, a[2].get());
		EXPECT_EQ(4, a[3].get());
	}
	{
		hamon::vector<int> a { 1,2,3,4,5 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 4), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(4, a[4]);
	}
	{
		hamon::vector<int> a;
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 0), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
		EXPECT_TRUE(a.empty());
	}
	{
		std::list<int> a { 1, 2 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 1), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
		auto it = a.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::list<int> a { 1, 2, 3, 4 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 3), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
		auto it = a.begin();
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::list<int> a { 1, 2, 3, 4 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 2), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		auto it = a.begin();
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::list<int> a;
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 0), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
		EXPECT_TRUE(a.empty());
	}
	{
		std::forward_list<int> a { 1,2,3,4,5 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 1), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 4));
		auto it = a.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::forward_list<int> a { 1,2,3,4,5 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 2), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
		auto it = a.begin();
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::forward_list<int> a { 1,2,3,4,5 };
		auto ret = hamon::rotate(hamon::begin(a), hamon::next(hamon::begin(a), 4), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
		auto it = a.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == a.end());
	}
}

#undef VERIFY

}	// namespace rotate_test

}	// namespace hamon_algorithm_test
