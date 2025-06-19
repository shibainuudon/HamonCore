/**
 *	@file	unit_test_memory_assume_aligned.cpp
 *
 *	@brief	assume_aligned のテスト
 */

#include <hamon/memory/assume_aligned.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace assume_aligned_test
{


GTEST_TEST(MemoryTest, AssumeAlignedTest)
{
	char* buf = new char[32];
	float* data = (float*)(((hamon::uint64_t)buf + 0x0f) >> 4 << 4);
	auto aligned_data = hamon::assume_aligned<16>(data);
	for (int i = 0; i < 4; ++i)
	{
		aligned_data[i] = 0;
	}
	delete[] buf;
}

}	// namespace assume_aligned_test

}	// namespace hamon_memory_test
