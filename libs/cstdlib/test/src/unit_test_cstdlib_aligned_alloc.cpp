/**
 *	@file	unit_test_cstdlib_aligned_alloc.cpp
 *
 *	@brief	aligned_alloc のテスト
 */

#include <hamon/cstdlib/aligned_alloc.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <gtest/gtest.h>

GTEST_TEST(CStdLibTest, AlignedAllocTest)
{
	{
		hamon::size_t align = 1024;
		hamon::size_t size = 1024;
		int* p = static_cast<int*>(hamon::aligned_alloc(align, size));
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(reinterpret_cast<hamon::uintptr_t>(p) % align == 0);
		hamon::aligned_free(p);
	}
	{
		hamon::size_t align = 16;
		hamon::size_t size = 100;
		int* p = static_cast<int*>(hamon::aligned_alloc(align, size));
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(reinterpret_cast<hamon::uintptr_t>(p) % align == 0);
		hamon::aligned_free(p);
	}
	{
		hamon::size_t align = alignof(int);
		hamon::size_t size = sizeof(int) * 4;
		int* p = static_cast<int*>(hamon::aligned_alloc(align, size));
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(reinterpret_cast<hamon::uintptr_t>(p) % align == 0);
		hamon::aligned_free(p);
	}
	{
		hamon::size_t align = alignof(short);
		hamon::size_t size = sizeof(short) * 5;
		short* p = static_cast<short*>(hamon::aligned_alloc(align, size));
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(reinterpret_cast<hamon::uintptr_t>(p) % align == 0);
		hamon::aligned_free(p);
	}
	{
		hamon::size_t align = alignof(char);
		hamon::size_t size = sizeof(char) * 13;
		char* p = static_cast<char*>(hamon::aligned_alloc(align, size));
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(reinterpret_cast<hamon::uintptr_t>(p) % align == 0);
		hamon::aligned_free(p);
	}
}
