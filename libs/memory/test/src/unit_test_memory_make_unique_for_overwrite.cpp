/**
 *	@file	unit_test_memory_make_unique_for_overwrite.cpp
 *
 *	@brief	make_unique_for_overwrite のテスト
 */

#include <hamon/memory/make_unique_for_overwrite.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace make_unique_for_overwrite_test
{

class Foo
{
public:
	static unsigned int instances;

	Foo()
	{
		instances++;
	}

	~Foo()
	{
		instances--;
	}

private:
	Foo(const Foo&);
	Foo& operator=(const Foo&);
};

unsigned int Foo::instances = 0;

GTEST_TEST(MemoryTest, MakeUniqueForOverwriteTest)
{
	using hamon::make_unique_for_overwrite;
	using std::unique_ptr;

	{
		unique_ptr<int[]> a1 = make_unique_for_overwrite<int[]>(3);
		EXPECT_TRUE(a1.get() != nullptr);
	}

	{
		unique_ptr<int[][2]> a1 = make_unique_for_overwrite<int[][2]>(2);
		EXPECT_TRUE(a1.get() != nullptr);
	}

	EXPECT_EQ(0u, Foo::instances);
	{
		unique_ptr<Foo> x = make_unique_for_overwrite<Foo>();
		EXPECT_EQ(1u, Foo::instances);
		x.reset();
		EXPECT_EQ(0u, Foo::instances);
	}

	EXPECT_EQ(0u, Foo::instances);
	{
		unique_ptr<Foo[]> a1 = make_unique_for_overwrite<Foo[]>(3);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(3u, Foo::instances);
		a1.reset();
		EXPECT_EQ(0u, Foo::instances);
	}

	EXPECT_EQ(0u, Foo::instances);
	{
		unique_ptr<Foo[][2]> a1 = make_unique_for_overwrite<Foo[][2]>(2);
		EXPECT_TRUE(a1.get() != nullptr);
		EXPECT_EQ(4u, Foo::instances);
	}
	EXPECT_EQ(0u, Foo::instances);
}

}	// namespace make_unique_for_overwrite_test

}	// namespace hamon_memory_test
