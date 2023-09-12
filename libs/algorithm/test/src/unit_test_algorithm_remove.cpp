/**
 *	@file	unit_test_algorithm_remove.cpp
 *
 *	@brief	remove のテスト
 */

#include <hamon/algorithm/remove.hpp>
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

namespace remove_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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

inline HAMON_CXX14_CONSTEXPR bool RemoveTest1()
{
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 1);
		VERIFY(ret == hamon::next(hamon::begin(a), 4));
		VERIFY(2 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(2 == a[3]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveTest2()
{
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 0);
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

inline HAMON_CXX14_CONSTEXPR bool RemoveTest3()
{
	{
		hamon::array<int, 7> a = {{1,2,3,1,3,1,2}};
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 3);
		VERIFY(ret == hamon::next(hamon::begin(a), 5));
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(1 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);
		VERIFY(7u == a.size());	// removeしてもコンテナのサイズは変わらない
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveTest4()
{
	{
		hamon::array<int, 4> a = {{1,1,1,1}};
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 1);
		VERIFY(ret == hamon::begin(a));
		VERIFY(4u == a.size());	// removeしてもコンテナのサイズは変わらない
	}
	return true;
}

GTEST_TEST(AlgorithmTest, RemoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveTest4());

	{
		using T = movable_int;
		T a[] = {1,2,3,1,3,1,2};
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 1);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 4));
		EXPECT_EQ(T(2), a[0]);
		EXPECT_EQ(T(3), a[1]);
		EXPECT_EQ(T(3), a[2]);
		EXPECT_EQ(T(2), a[3]);
	}
	{
		using T = movable_int;
		T a[] = {1,2,3,1,3,1,2};
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 2);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 5));
		EXPECT_EQ(T(1), a[0]);
		EXPECT_EQ(T(3), a[1]);
		EXPECT_EQ(T(1), a[2]);
		EXPECT_EQ(T(3), a[3]);
		EXPECT_EQ(T(1), a[4]);
	}
	{
		using T = movable_int;
		T a[] = {1,2,3,1,3,1,2};
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 0);
		EXPECT_TRUE(ret == hamon::end(a));
		EXPECT_EQ(T(1), a[0]);
		EXPECT_EQ(T(2), a[1]);
		EXPECT_EQ(T(3), a[2]);
		EXPECT_EQ(T(1), a[3]);
		EXPECT_EQ(T(3), a[4]);
		EXPECT_EQ(T(1), a[5]);
		EXPECT_EQ(T(2), a[6]);
	}
	{
		std::vector<int> a = {1,2,3,1,3,1,2,2};
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 2);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 5));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(1, a[4]);
		EXPECT_EQ(8u, a.size());	// removeしてもコンテナのサイズは変わらない
	}
	{
		std::vector<int> a;
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 2);
		EXPECT_TRUE(ret == hamon::end(a));
		EXPECT_EQ(0u, a.size());
	}
	{
		std::list<int> a = {1,2,3,1,3,1,2,1,1};
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 2);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 7));
		auto it = a.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != a.end());	// removeしてもコンテナのサイズは変わらない
	}
	{
		std::list<int> a;
		auto ret = hamon::remove(hamon::begin(a), hamon::end(a), 0);
		EXPECT_TRUE(ret == hamon::end(a));
		EXPECT_EQ(0u, a.size());
	}
}

#undef VERIFY

}	// namespace remove_test

}	// namespace hamon_algorithm_test
