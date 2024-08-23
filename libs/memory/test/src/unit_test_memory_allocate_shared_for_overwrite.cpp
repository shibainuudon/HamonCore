/**
 *	@file	unit_test_memory_allocate_shared_for_overwrite.cpp
 *
 *	@brief	allocate_shared_for_overwrite のテスト
 *
 *	template<class T, class A>
 *	shared_ptr<T> allocate_shared_for_overwrite(const A& a);
 *
 *	template<class T, class A>
 *	shared_ptr<T> allocate_shared_for_overwrite(const A& a, size_t N);
 */

#include <hamon/memory/allocate_shared_for_overwrite.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace allocate_shared_for_overwrite_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	hamon::allocator<char> alloc;

	// (1)
	{
		auto sp = hamon::allocate_shared_for_overwrite<int>(alloc);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::allocate_shared_for_overwrite<double[3]>(alloc);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<double[3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::allocate_shared_for_overwrite<int[2][3]>(alloc);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int[2][3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::allocate_shared_for_overwrite<float[4][3][2]>(alloc);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<float[4][3][2]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}

	// (2)
	{
		auto sp = hamon::allocate_shared_for_overwrite<long[]>(alloc, 3);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<long[]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::allocate_shared_for_overwrite<long[][2]>(alloc, 3);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<long[][2]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	{
		auto sp = hamon::allocate_shared_for_overwrite<int[][2][3]>(alloc, 4);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int[][2][3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
	}
	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000)) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(MemoryTest, AllocateSharedForOverwriteTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace allocate_shared_for_overwrite_test

}	// namespace hamon_memory_test
