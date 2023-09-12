/**
 *	@file	unit_test_algorithm_remove_if.cpp
 *
 *	@brief	remove_if のテスト
 */

#include <hamon/algorithm/remove_if.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace remove_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CONSTEXPR bool pred1(int x)
{
	return x == 1;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int x) const
	{
		return x > 1;
	}
};

HAMON_CONSTEXPR bool pred3(int x)
{
	return x < 0;
}

HAMON_CONSTEXPR bool pred4(int x)
{
	return x > 0;
}

struct movable_int
{
public:
	movable_int(int v) : m_value(v) {}
	movable_int(movable_int const&) = delete;
	movable_int& operator=(movable_int const&) = delete;
	movable_int(movable_int&& other) noexcept : m_value(other.m_value) { other.m_value = 0; }
	movable_int& operator=(movable_int&& other) noexcept {m_value = other.m_value; other.m_value = 0; return *this;}
	bool operator==(movable_int const& v) const { return m_value == v.m_value; }
	bool operator<(movable_int const& v) const { return m_value < v.m_value; }
private:
	int		m_value;
};

inline HAMON_CXX14_CONSTEXPR bool RemoveIfTest1()
{
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), pred1);
		VERIFY(ret == hamon::next(hamon::begin(a), 4));
		VERIFY(2 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(2 == a[3]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveIfTest2()
{
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), pred3);
		VERIFY(ret == hamon::end(a));
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(3 == a[4]);
		VERIFY(1 == a[5]);
		VERIFY(2 == a[6]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveIfTest3()
{
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), pred4);
		VERIFY(ret == hamon::begin(a));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveIfTest4()
{
	{
		hamon::array<int, 7> a = {{1,2,3,1,3,1,2}};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), pred2());
		VERIFY(ret == hamon::next(hamon::begin(a), 3));
		VERIFY(1 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(1 == a[2]);
		VERIFY(7u == a.size());	// remove_ifしてもコンテナのサイズは変わらない
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveIfTest5()
{
	{
		hamon::array<int, 4> a = {{1,1,1,1}};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), pred1);
		VERIFY(ret == hamon::begin(a));
		VERIFY(4u == a.size());	// remove_ifしてもコンテナのサイズは変わらない
	}
	return true;
}

GTEST_TEST(AlgorithmTest, RemoveIfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveIfTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveIfTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveIfTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveIfTest4());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveIfTest5());

	{
		using T = movable_int;
		T a[] = {1,2,3,1,3,1,2};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), [](T const& x) { return x == 1; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 4));
		EXPECT_EQ(T(2), a[0]);
		EXPECT_EQ(T(3), a[1]);
		EXPECT_EQ(T(3), a[2]);
		EXPECT_EQ(T(2), a[3]);
	}
	{
		using T = movable_int;
		T a[] = {3,1,4,1,5,9,2,6};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), [](T const& x) { return x < 5; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
		EXPECT_EQ(T(5), a[0]);
		EXPECT_EQ(T(9), a[1]);
		EXPECT_EQ(T(6), a[2]);
	}
	{
		using T = movable_int;
		T a[] = {3,1,4,1,5,9,2,6};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), [](T const& x) { return !(x < 5); });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 5));
		EXPECT_EQ(T(3), a[0]);
		EXPECT_EQ(T(1), a[1]);
		EXPECT_EQ(T(4), a[2]);
		EXPECT_EQ(T(1), a[3]);
		EXPECT_EQ(T(2), a[4]);
	}
	{
		std::vector<int> a = {1,2,3,1,3,1,2,2};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), [](int x) { return (x % 2) == 0; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 5));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(1, a[4]);
		EXPECT_EQ(8u, a.size());	// remove_ifしてもコンテナのサイズは変わらない
	}
	{
		std::vector<int> a;
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(ret == hamon::end(a));
		EXPECT_EQ(0u, a.size());
	}
	{
		std::list<int> a = {1,2,3,1,3,1,2,1,1};
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), [](int x) { return (x % 2) == 1; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		auto it = a.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it != a.end());	// remove_ifしてもコンテナのサイズは変わらない
	}
	{
		std::list<int> a;
		auto ret = hamon::remove_if(hamon::begin(a), hamon::end(a), [](int x) { return (x % 2) == 1; });
		EXPECT_TRUE(ret == hamon::end(a));
		EXPECT_EQ(0u, a.size());
	}
}

#undef VERIFY

}	// namespace remove_if_test

}	// namespace hamon_algorithm_test
