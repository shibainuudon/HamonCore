﻿/**
 *	@file	unit_test_memory_make_unique_for_overwrite.cpp
 *
 *	@brief	make_unique_for_overwrite のテスト
 */

#include <hamon/memory/make_unique_for_overwrite.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto up = hamon::make_unique_for_overwrite<int>();
		VERIFY(up != nullptr);
	}
	{
		auto up = hamon::make_unique_for_overwrite<int[]>(4);
		VERIFY(up != nullptr);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, MakeUniqueForOverwriteTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	using hamon::make_unique_for_overwrite;
	using hamon::unique_ptr;

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

#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
	// clang-10 だと internal compiler error になってしまう
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
#endif
}

}	// namespace make_unique_for_overwrite_test

}	// namespace hamon_memory_test
