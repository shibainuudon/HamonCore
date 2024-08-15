/**
 *	@file	unit_test_memory_make_unique.cpp
 *
 *	@brief	make_unique のテスト
 */

#include <hamon/memory/make_unique.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace make_unique_test
{

class Foo
{
public:
	static unsigned int instances;

	Foo(
		int v1 = 0,
		int v2 = 0,
		int v3 = 0,
		int v4 = 0,
		int v5 = 0,
		int v6 = 0,
		int v7 = 0,
		int v8 = 0,
		int v9 = 0)
		: sum(v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + v9)
	{
		instances++;
	}

	~Foo()
	{
		instances--;
	}

	const int sum;

private:
	Foo(const Foo&);
	Foo& operator=(const Foo&);
};

unsigned int Foo::instances = 0;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test1()
{
	{
		auto up = hamon::make_unique<int>(42);
		VERIFY(*up == 42);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, MakeUniqueArgsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());

	using hamon::make_unique;
	using hamon::unique_ptr;

	EXPECT_EQ(0u, Foo::instances);
	{
		unique_ptr<Foo> x = make_unique<Foo>();
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(0, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5, 6);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5 + 6, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5, 6, 7);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5 + 6 + 7, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5, 6, 7, 8);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5 + 6 + 7 + 8, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
	{
		unique_ptr<Foo> x = make_unique<Foo>(1, 2, 3, 4, 5, 6, 7, 8, 9);
		EXPECT_EQ(1u, Foo::instances);
		EXPECT_EQ(1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9, x->sum);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test2()
{
	{
		auto up = hamon::make_unique<int[]>(4);
		VERIFY(up[0] == 0);
		VERIFY(up[1] == 0);
		VERIFY(up[2] == 0);
		VERIFY(up[3] == 0);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, MakeUniqueArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());

	using hamon::make_unique;
	using hamon::unique_ptr;

	{
		unique_ptr<int[]> a1 = make_unique<int[]>(3);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(0, a1[0]);
		EXPECT_EQ(0, a1[1]);
		EXPECT_EQ(0, a1[2]);
	}

	{
		unique_ptr<int[][2]> a1 = make_unique<int[][2]>(2);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(0, a1[0][0]);
		EXPECT_EQ(0, a1[0][1]);
		EXPECT_EQ(0, a1[1][0]);
		EXPECT_EQ(0, a1[1][1]);
	}

	{
		unique_ptr<const int[]> a1 = make_unique<const int[]>(3);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(0, a1[0]);
		EXPECT_EQ(0, a1[1]);
		EXPECT_EQ(0, a1[2]);
	}

	{
		unique_ptr<const int[][2]> a1 = make_unique<const int[][2]>(2);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(0, a1[0][0]);
		EXPECT_EQ(0, a1[0][1]);
		EXPECT_EQ(0, a1[1][0]);
		EXPECT_EQ(0, a1[1][1]);
	}

	EXPECT_EQ(0u, Foo::instances);
	{
		unique_ptr<Foo[]> a1 = make_unique<Foo[]>(3);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(3u, Foo::instances);
		a1.reset();
		EXPECT_EQ(0u, Foo::instances);
	}

	{
		unique_ptr<Foo[][2]> a1 = make_unique<Foo[][2]>(2);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(4u, Foo::instances);
	}
	EXPECT_EQ(0u, Foo::instances);

	{
		unique_ptr<const Foo[]> a1 = make_unique<const Foo[]>(3);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(3u, Foo::instances);
		a1.reset();
		EXPECT_EQ(0u, Foo::instances);
	}

	{
		unique_ptr<const Foo[][2]> a1 = make_unique<const Foo[][2]>(2);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(4u, Foo::instances);
	}
	EXPECT_EQ(0u, Foo::instances);
}

}	// namespace make_unique_test

}	// namespace hamon_memory_test
